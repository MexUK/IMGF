#pragma warning(disable : 4005)

#include "DumpManager.h"
#include "IMGF.h"
#include "Globals.h"
#include "GUI/Editor/Editors/IMGEditor.h"
#include "GUI/Editor/Editors/Tab/IMGEditorTab.h"
#include "Format/IMG/Regular/IMGFormat.h"
#include "Static/Input.h"
#include "Static/Path.h"
#include "Static/String.h"
#include "Static/File.h"
#include "Format/IMG/Regular/IMGManager.h"
#include "Format/IMG/Regular/IMGEntry.h"
#include "Format/DAT/Loader/DATLoaderManager.h"
#include "Format/DAT/Loader/DATLoaderFormat.h"
#include "Format/DAT/Loader/DATLoaderEntry.h"
#include "Format/TXD/TXDManager.h"
#include "Format/TXD/TXDFormat.h"
#include "Format/RW/Sections/RWSection_TextureNative.h"
#include "Format/Image/BMP/BMPManager.h"
#include "Format/Image/BMP/BMPFormat.h"
#include "Format/Image/CUR/CURManager.h"
#include "Format/Image/CUR/CURFormat.h"
#include "Format/Image/ICO/ICOManager.h"
#include "Format/Image/ICO/ICOFormat.h"
#include "Bitmap.h"
#include "Static/Debug.h"
#include "Static/StdVector.h"
#include "Task/TaskManager.h"
#include "Task/Tasks/Tasks.h"
#include "Format/WTD/WTDManager.h"
#include "Format/WTD/WTDFormat.h"
#include "Format/WTD/WTDEntry.h"
#include "Image/ImageManager.h"
#include "Format/Image/DDS/DDSFormat.h"
#include "Localization/LocalizationManager.h"
#include "Settings/SettingsManager.h"
#include "GUI/Window/WindowManager.h"
#include "GUI/Layer/Layers/DumpWindow/DumpWindowResult.h"
#include "Format/EFileType.h"
#include "GUI/Window/Windows/MainWindow/MainWindow.h"
#include <gdiplus.h>

using namespace std;
using namespace bxcf;
using namespace bxcf::fileType;
using namespace bxgi;
using namespace imgf;
using namespace Gdiplus;

INT GetEncoderClsid(const WCHAR* format, CLSID* pClsid);  // helper function

int GetEncoderClsid(const WCHAR* format, CLSID* pClsid)
{
	UINT  num = 0;          // number of image encoders
	UINT  size = 0;         // size of the image encoder array in bytes

	ImageCodecInfo* pImageCodecInfo = NULL;

	GetImageEncodersSize(&num, &size);
	if (size == 0)
		return -1;  // Failure

	pImageCodecInfo = (ImageCodecInfo*)(malloc(size));
	if (pImageCodecInfo == NULL)
		return -1;  // Failure

	GetImageEncoders(num, size, pImageCodecInfo);

	for (UINT j = 0; j < num; ++j)
	{
		if (wcscmp(pImageCodecInfo[j].MimeType, format) == 0)
		{
			*pClsid = pImageCodecInfo[j].Clsid;
			free(pImageCodecInfo);
			return j;  // Success
		}
	}

	free(pImageCodecInfo);
	return -1;  // Failure
}

bool		DumpManager::process(void)
{
	getIMGF()->getTaskManager()->onPauseTask();
	DumpWindowResult dumpWindowResult = getIMGF()->getWindowManager()->showDumpWindow();
	getIMGF()->getTaskManager()->onResumeTask();

	if (dumpWindowResult.m_bCancelled)
	{
		return false;
	}

	IMGEditorTab *pActiveEditorTab = getIMGF()->getWindowManager()->getMainWindow()->getIMGEditor()->getActiveTab();

	// choose img files
	vector<IMGFormat*> vecIMGFormats;
	if (dumpWindowResult.m_uiDumpType == 0) // All entries in active tab
	{
		if (pActiveEditorTab == nullptr)
		{
			getIMGF()->getTaskManager()->onTaskEnd("onRequestDump", true);
			return false;
		}

		vecIMGFormats.push_back(pActiveEditorTab->getIMGFile());
	}
	else if (dumpWindowResult.m_uiDumpType == 1) // Selected entries in active tab
	{
		if (pActiveEditorTab == nullptr)
		{
			getIMGF()->getTaskManager()->onTaskEnd("onRequestDump", true);
			return false;
		}

		vecIMGFormats.push_back(pActiveEditorTab->getIMGFile());
	}
	else if (dumpWindowResult.m_uiDumpType == 2) // All entries in all tabs
	{
		vecIMGFormats = getIMGF()->getIMGEditor()->getAllMainWindowTabsIMGFiles();
	}
	else if (dumpWindowResult.m_uiDumpType == 3) // DAT file
	{
		vector<string> vecDATFilePaths = dumpWindowResult.m_vecDATFilePaths;
		for (string& strDATFilePath : vecDATFilePaths)
		{
			DATLoaderFormat datFile(strDATFilePath);
			if (!datFile.unserialize())
			{
				StdVector::addToVector(vecIMGFormats, datFile.parseIMGFiles(dumpWindowResult.m_strGameFolderPath));
			}
			datFile.unload();
		}
	}
	else if (dumpWindowResult.m_uiDumpType == 4) // Game IMGs
	{
		vector<string> vecIMGFilePaths = File::getFilePaths(dumpWindowResult.m_strGameFolderPath, true, false, "IMG,DIR", true);
		for (string& strIMGFilePath : vecIMGFilePaths)
		{
			IMGFormat *pIMGFile = IMGManager::unserializeFile(strIMGFilePath);
			if(pIMGFile)
			{
				vecIMGFormats.push_back(pIMGFile);
			}
		}
	}

	// progress bar
	uint32 uiProgressMaxTicks = 0;
	for (auto pIMGFile : vecIMGFormats)
	{
		uiProgressMaxTicks += pIMGFile->getEntryCount();
	}
	getIMGF()->getTaskManager()->setTaskMaxProgressTickCount(uiProgressMaxTicks);

	// dump
	vector<string>
		vecDumpedEntryNames,
		vecTextureNames,
		vecCorruptTXDs,
		vecTooLargeTXDs,
		vecInvalidResolutionTXDs,
		vecInvalidTextureNames,
		vecTXDsContainingTooManyTextures,
		vecMipmapSkippedEntries;
	uint32
		uiIMGsEntryCount = 0,
		uiDumpedTextureCount = 0;
		//uiMipmapSkippedCount = 0;

	for (IMGFormat *pIMGFile : vecIMGFormats)
	{
		// choose IMG entries to dump
		vector<IMGEntry*> vecIMGEntries;
		if (dumpWindowResult.m_uiDumpType == 4) // selected entries
		{
			vecIMGEntries = (vector<IMGEntry*>&)pActiveEditorTab->getSelectedEntries();
		}
		else
		{
			vecIMGEntries = pIMGFile->getEntries();
		}

		// dump IMG entries
		for (IMGEntry *pIMGEntry : vecIMGEntries)
		{
			string strExtension = String::toUpperCase(Path::getFileExtension(pIMGEntry->getEntryName()));
			if (pIMGEntry->getFileType() == COLLISION)
			{
				if (std::find(dumpWindowResult.m_vecEntryTypes.begin(), dumpWindowResult.m_vecEntryTypes.end(), "Collision") != dumpWindowResult.m_vecEntryTypes.end())
				{
					vecDumpedEntryNames.push_back(pIMGEntry->getEntryName());
					pIMGFile->exportSingle(pIMGEntry, dumpWindowResult.m_strOutputFolderPath + strExtension + "/");
				}
			}
			else if (pIMGEntry->getFileType() == MODEL)
			{
				if (std::find(dumpWindowResult.m_vecEntryTypes.begin(), dumpWindowResult.m_vecEntryTypes.end(), "Model") != dumpWindowResult.m_vecEntryTypes.end())
				{
					vecDumpedEntryNames.push_back(pIMGEntry->getEntryName());
					pIMGFile->exportSingle(pIMGEntry, dumpWindowResult.m_strOutputFolderPath + strExtension + "/");
				}
			}
			else if (pIMGEntry->getFileType() == ITEM_PLACEMENT)
			{
				if (std::find(dumpWindowResult.m_vecEntryTypes.begin(), dumpWindowResult.m_vecEntryTypes.end(), "Item Placement") != dumpWindowResult.m_vecEntryTypes.end())
				{
					vecDumpedEntryNames.push_back(pIMGEntry->getEntryName());
					pIMGFile->exportSingle(pIMGEntry, dumpWindowResult.m_strOutputFolderPath + strExtension + "/");
				}
			}
			else if (pIMGEntry->getFileType() == TEXTURE) // todo - rename to TEXTURE_SET
			{
				if (std::find(dumpWindowResult.m_vecEntryTypes.begin(), dumpWindowResult.m_vecEntryTypes.end(), "Texture Set") != dumpWindowResult.m_vecEntryTypes.end())
				{
					vecDumpedEntryNames.push_back(pIMGEntry->getEntryName());
					pIMGFile->exportSingle(pIMGEntry, dumpWindowResult.m_strOutputFolderPath + strExtension + "/");

					string strTXDData = pIMGEntry->getEntryData();
					if (!TXDFormat::isTXDSizeValid(strTXDData.size()))
					{
						vecTooLargeTXDs.push_back(LocalizationManager::get()->getTranslatedFormattedText("Log_TXD_MaxSize", pIMGEntry->getEntryName().c_str()));
					}

					TXDFormat *pTXDFile = TXDManager::get()->unserializeMemory(strTXDData);
					if (pTXDFile->doesHaveError())
					{
						vecCorruptTXDs.push_back(pIMGEntry->getEntryName());
					}

					if (!TXDFormat::isTextureCountValid(pTXDFile->getTextures().size(), pTXDFile->getPlatformedGames()))
					{
						vecTXDsContainingTooManyTextures.push_back(LocalizationManager::get()->getTranslatedFormattedText("Log_TextureCount", pIMGEntry->getEntryName().c_str(), pTXDFile->getTextures().size()));
					}

					uint32 uiTextureIndex = 0;
					for (auto pTexture : pTXDFile->getTextures())
					{
						if (!TXDFormat::isTextureResolutionValid((uint16)pTexture->getImageSize().x, (uint16)pTexture->getImageSize().y, pTXDFile->getPlatformedGames()))
						{
							vecInvalidResolutionTXDs.push_back("[" + pIMGEntry->getEntryName() + "] " + pTexture->getDiffuseName() + " (" + String::toString(pTexture->getImageSize().x) + " x " + String::toString(pTexture->getImageSize().y) + ")");
						}

						if (!TXDFormat::isTextureNameValid(pTexture->getDiffuseName()) || !TXDFormat::isTextureNameValid(pTexture->getAlphaName(), true))
						{
							vecInvalidTextureNames.push_back(LocalizationManager::get()->getTranslatedFormattedText("Log_TextureIndex", pIMGEntry->getEntryName().c_str(), uiTextureIndex + 1));
						}

						uiTextureIndex++;
					}
					
					pTXDFile->unload();
					delete pTXDFile;
				}

				if (std::find(dumpWindowResult.m_vecEntryTypes.begin(), dumpWindowResult.m_vecEntryTypes.end(), "Texture Images") != dumpWindowResult.m_vecEntryTypes.end())
				{
					//vector<IMGEntry*> vecIMGEntries;
					//vecIMGEntries.push_back(pIMGEntry);
					//IMGManager::get()->exportEntries(pIMGFile, vecIMGEntries, dumpWindowResult.m_strOutputFolderPath + strExtension + "/");

					string strEntryExtensionUpper = String::toUpperCase(Path::getFileExtension(pIMGEntry->getEntryName()));
					if (strEntryExtensionUpper != "TXD" && strEntryExtensionUpper != "WTD")
					{
						getIMGF()->getTaskManager()->onTaskProgressTick();
						continue;
					}


					if (strEntryExtensionUpper == "TXD")
					{
						string strTXDData = pIMGEntry->getEntryData();

						if (!TXDFormat::isTXDSizeValid(strTXDData.size()))
						{
							vecTooLargeTXDs.push_back(LocalizationManager::get()->getTranslatedFormattedText("Log_TXD_MaxSize", pIMGEntry->getEntryName().c_str()));
						}
						TXDFormat *pTXDFile = TXDManager::get()->unserializeMemory(strTXDData);
						if (pTXDFile->doesHaveError())
						{
							vecCorruptTXDs.push_back(pIMGEntry->getEntryName());
							getIMGF()->getTaskManager()->onTaskProgressTick();
							continue;
						}
						if (!TXDFormat::isTextureCountValid(pTXDFile->getTextures().size(), pTXDFile->getPlatformedGames()))
						{
							vecTXDsContainingTooManyTextures.push_back(LocalizationManager::get()->getTranslatedFormattedText("Log_TextureCount", pIMGEntry->getEntryName().c_str(), pTXDFile->getTextures().size()));
						}

						for (string& strImageType : dumpWindowResult.m_vecTextureImageOutputFormats)
						{
							uint32 uiTextureIndex = 0;
							for (auto pTexture : pTXDFile->getTextures())
							{
								if (pTexture->getDiffuseName().length() == 0)
								{
									continue;
								}

								/*
								todo
								Debugger::log("pTexture->m_strDiffuseName: [" + pIMGEntry->getEntryName() + "] " + pTexture->getDiffuseName());
								Debugger::log("pTexture->m_usWidth: " + String::toString(pTexture->getImageSize(true)));
								Debugger::log("pTexture->m_usHeight: " + String::toString(pTexture->getImageSize(false)));
								Debugger::log("pTexture->m_uiRasterFormat: " + String::toString(pTexture->getRasterFormat()));
								Debugger::log("pTexture->m_ucBPP: " + String::toString(pTexture->getBPP()));
								*/

								if (!TXDFormat::isTextureResolutionValid((uint16)pTexture->getImageSize().x, (uint16)pTexture->getImageSize().y, pTXDFile->getPlatformedGames()))
								{
									vecInvalidResolutionTXDs.push_back("[" + pIMGEntry->getEntryName() + "] " + pTexture->getDiffuseName() + " (" + String::toString(pTexture->getImageSize().x) + " x " + String::toString(pTexture->getImageSize().y) + ")");
								}

								if (!TXDFormat::isTextureNameValid(pTexture->getDiffuseName()) || !TXDFormat::isTextureNameValid(pTexture->getAlphaName(), true))
								{
									vecInvalidTextureNames.push_back(LocalizationManager::get()->getTranslatedFormattedText("Log_TextureIndex", pIMGEntry->getEntryName().c_str(), uiTextureIndex + 1));
								}

								string strTextureNamesLogLine;
								if (pTexture->doesHaveDiffuse())
								{
									if (pTexture->doesHaveAlpha())
									{
										strTextureNamesLogLine = pTexture->getDiffuseName() + " (" + LocalizationManager::get()->getTranslatedFormattedText("Log_AlphaTextureName", pTexture->getAlphaName().c_str()) + ")";
									}
									else
									{
										strTextureNamesLogLine = pTexture->getDiffuseName();
									}
								}
								else
								{
									if (pTexture->doesHaveAlpha())
									{
										strTextureNamesLogLine = LocalizationManager::get()->getTranslatedFormattedText("Log_AlphaTextureName", pTexture->getAlphaName().c_str());
									}
									else
									{
										strTextureNamesLogLine = LocalizationManager::get()->getTranslatedText("Log_TextureNameNotFound");
									}
								}
								vecTextureNames.push_back(strTextureNamesLogLine);

								// choose whether to dump all mipmaps in the texture, or just the first mipmap in the texture
								vector<RWEntry_TextureNative_MipMap*> vecTextureMipmapsToDump;
								if (dumpWindowResult.m_bDumpAllTextureMipmaps)
								{
									vecTextureMipmapsToDump = pTexture->getMipMaps().getEntries();
								}
								else
								{
									if (pTexture->getEntryCount() > 0)
									{
										vecTextureMipmapsToDump.push_back(pTexture->getMipMaps().getEntries()[0]);
									}
								}

								// dump mipmap(s)
								uint32 uiMipmapIndex = 0;
								for (auto pMipmap : vecTextureMipmapsToDump)
								{
									string strImageDataBGRA = pMipmap->getRasterDataBGRA32();
									if (strImageDataBGRA == "")
									{
										vecMipmapSkippedEntries.push_back(LocalizationManager::get()->getTranslatedFormattedText("Log_TextureInfo", pIMGEntry->getEntryName().c_str(), uiTextureIndex + 1, pTexture->getDiffuseName().c_str(), uiMipmapIndex + 1, pMipmap->getImageSize().x, pMipmap->getImageSize().y));
										//uiMipmapSkippedCount++;
										uiMipmapIndex++;
										continue;
									}

									BMPFormat *pBMPFile = new BMPFormat;
									pBMPFile->setWidth(pMipmap->getImageSize().x);
									pBMPFile->setHeight(pMipmap->getImageSize().y);
									pBMPFile->setBPP(32);

									pBMPFile->setRasterData(strImageDataBGRA);
									pBMPFile->swapRows();

									if (strImageType == "BMP")
									{
										string strBMPFilePath;
										if (dumpWindowResult.m_bDumpTextureImagesAsFolders)
										{
											strBMPFilePath = dumpWindowResult.m_strOutputFolderPath + "Texture Images/" + Path::removeFileExtension(pIMGEntry->getEntryName()) + "/" + pTexture->getDiffuseName() + ".BMP";
										}
										else
										{
											strBMPFilePath = dumpWindowResult.m_strOutputFolderPath + "Texture Images/" + pTexture->getDiffuseName() + ".BMP";
										}
										strBMPFilePath = Path::getNextFileName(strBMPFilePath, uiMipmapIndex, "-Mipmap");

										pBMPFile->setBMPVersion(3);
										pBMPFile->serialize(strBMPFilePath);
									}
									else if (strImageType == "ICO")
									{
										string strICOFilePath;
										if (dumpWindowResult.m_bDumpTextureImagesAsFolders)
										{
											strICOFilePath = dumpWindowResult.m_strOutputFolderPath + "Texture Images/" + Path::removeFileExtension(pIMGEntry->getEntryName()) + "/" + pTexture->getDiffuseName() + ".ICO";
										}
										else
										{
											strICOFilePath = dumpWindowResult.m_strOutputFolderPath + "Texture Images/" + pTexture->getDiffuseName() + ".ICO";
										}
										strICOFilePath = Path::getNextFileName(strICOFilePath, uiMipmapIndex, "-Mipmap");

										ICOFormat *pICOFormat = ICOManager::get()->createFormatFromBMP(pBMPFile);
										pICOFormat->serialize(strICOFilePath);
										pICOFormat->unload();
										delete pICOFormat;
									}
									else if (strImageType == "CUR")
									{
										string strCURFilePath;
										if (dumpWindowResult.m_bDumpTextureImagesAsFolders)
										{
											strCURFilePath = dumpWindowResult.m_strOutputFolderPath + "Texture Images/" + Path::removeFileExtension(pIMGEntry->getEntryName()) + "/" + pTexture->getDiffuseName() + ".CUR";
										}
										else
										{
											strCURFilePath = dumpWindowResult.m_strOutputFolderPath + "Texture Images/" + pTexture->getDiffuseName() + ".CUR";
										}
										strCURFilePath = Path::getNextFileName(strCURFilePath, uiMipmapIndex, "-Mipmap");
										
										CURFormat *pCURFormat = CURManager::get()->createFormatFromBMP(pBMPFile);
										pCURFormat->serialize(strCURFilePath);
										pCURFormat->unload();
										delete pCURFormat;
									}
									else if (strImageType == "DDS")
									{
										string strDDSFilePath;
										if (dumpWindowResult.m_bDumpTextureImagesAsFolders)
										{
											strDDSFilePath = dumpWindowResult.m_strOutputFolderPath + "Texture Images/" + Path::removeFileExtension(pIMGEntry->getEntryName()) + "/" + pTexture->getDiffuseName() + ".DDS";
										}
										else
										{
											strDDSFilePath = dumpWindowResult.m_strOutputFolderPath + "Texture Images/" + pTexture->getDiffuseName() + ".DDS";
										}
										strDDSFilePath = Path::getNextFileName(strDDSFilePath, uiMipmapIndex, "-Mipmap");

										DDSFormat ddsFile;
										ddsFile.m_uiWidth = pMipmap->getImageSize().x;
										ddsFile.m_uiHeight = pMipmap->getImageSize().y;
										//ddsFile.m_strRasterData = ImageManager::swapRowsAndColumns(ImageManager::convertBGRA32ToRGBA32(strImageDataBGRA), ddsFile.m_uiWidth, ddsFile.m_uiHeight);
										ddsFile.m_strRasterData = ImageManager::convertBGRA32ToDXT(ImageManager::swapRowsAndColumns(strImageDataBGRA, ddsFile.m_uiWidth, ddsFile.m_uiHeight), DXT_1, ddsFile.m_uiWidth, ddsFile.m_uiHeight);
										ddsFile.serialize(strDDSFilePath);
									}
									else if (strImageType == "TGA")
									{
										string
											strTempBMPPath,
											strImagePath;
										if (dumpWindowResult.m_bDumpTextureImagesAsFolders)
										{
											strTempBMPPath = dumpWindowResult.m_strOutputFolderPath + "Texture Images/" + Path::removeFileExtension(pIMGEntry->getEntryName()) + "/" + "__TEMP_" + pTexture->getDiffuseName() + ".BMP";
											strImagePath = dumpWindowResult.m_strOutputFolderPath + "Texture Images/" + Path::removeFileExtension(pIMGEntry->getEntryName()) + "/" + pTexture->getDiffuseName() + "." + strImageType;
										}
										else
										{
											strTempBMPPath = dumpWindowResult.m_strOutputFolderPath + "Texture Images/__TEMP_" + pTexture->getDiffuseName() + ".BMP";
											strImagePath = dumpWindowResult.m_strOutputFolderPath + "Texture Images/" + pTexture->getDiffuseName() + "." + strImageType;
										}
										strImagePath = Path::getNextFileName(strImagePath, uiMipmapIndex, "-Mipmap");

										pBMPFile->setBMPVersion(3);
										pBMPFile->serialize(strTempBMPPath);

										DHPOBitmap *pBmp = new DHPOBitmap;
										pBmp->loadImage(String::convertStdStringToStdWString(strTempBMPPath).c_str());
										pBmp->saveImage(String::convertStdStringToStdWString(strImagePath).c_str());
										delete pBmp;

										File::removeFile(strTempBMPPath);
									}
									else
									{
										// PNG
										string
											strTempBMPPath,
											strImagePath;
										if (dumpWindowResult.m_bDumpTextureImagesAsFolders)
										{
											strTempBMPPath = dumpWindowResult.m_strOutputFolderPath + "Texture Images/" + Path::removeFileExtension(pIMGEntry->getEntryName()) + "/" + "__TEMP_" + pTexture->getDiffuseName() + ".BMP";
											strImagePath = dumpWindowResult.m_strOutputFolderPath + "Texture Images/" + Path::removeFileExtension(pIMGEntry->getEntryName()) + "/" + pTexture->getDiffuseName() + "." + strImageType;
										}
										else
										{
											strTempBMPPath = dumpWindowResult.m_strOutputFolderPath + "Texture Images/__TEMP_" + pTexture->getDiffuseName() + ".BMP";
											strImagePath = dumpWindowResult.m_strOutputFolderPath + "Texture Images/" + pTexture->getDiffuseName() + "." + strImageType;
										}
										strImagePath = Path::getNextFileName(strImagePath, uiMipmapIndex, "-Mipmap");

										pBMPFile->setBMPVersion(3);
										pBMPFile->serialize(strTempBMPPath);

										GdiplusStartupInput gdiplusStartupInput;
										ULONG_PTR gdiplusToken;
										GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

										// Create an Image object based on a PNG file.
										Image  *image = new Image(String::convertStdStringToStdWString(strTempBMPPath).c_str());

										// Save the image.
										CLSID gifClsid;
										GetEncoderClsid(String::convertStdStringToStdWString(getEncoderClassIdFromImageExtension(strImageType)).c_str(), &gifClsid);
										image->Save(String::convertStdStringToStdWString(strImagePath).c_str(), &gifClsid, NULL);

										delete image;
										GdiplusShutdown(gdiplusToken);

										File::removeFile(strTempBMPPath);
									}

									pBMPFile->unload();
									delete pBMPFile;
									uiMipmapIndex++;
								}
								uiTextureIndex++;
							}
						}

						pTXDFile->unload();
						delete pTXDFile;
					}
					else if (strEntryExtensionUpper == "WTD")
					{
						WTDFormat *pWTDFile = WTDManager::get()->unserializeMemory(pIMGEntry->getEntryData());
						
						if (pWTDFile->doesHaveError())
						{
							vecCorruptTXDs.push_back(pIMGEntry->getEntryName());
							getIMGF()->getTaskManager()->onTaskProgressTick();
							continue;
						}

						for (string& strImageType : dumpWindowResult.m_vecTextureImageOutputFormats)
						{
							uint32 uiTextureIndex = 0;
							for (WTDEntry *pWTDEntry : pWTDFile->getEntries())
							{
								if (pWTDEntry->getEntryName().length() == 0)
								{
									continue;
								}

								string strTextureNamesLogLine = pWTDEntry->getEntryName();
								vecTextureNames.push_back(strTextureNamesLogLine);

								// choose whether to dump all mipmaps in the texture, or just the first mipmap in the texture
								vector<WTDMipmap*> vecTextureMipmapsToDump;
								if (dumpWindowResult.m_bDumpAllTextureMipmaps)
								{
									vecTextureMipmapsToDump = pWTDEntry->getEntries();
								}
								else
								{
									if (pWTDEntry->getEntryCount() > 0)
									{
										vecTextureMipmapsToDump.push_back(pWTDEntry->getEntries()[0]);
									}
								}

								// dump mipmap(s)
								uint32 uiMipmapIndex = 0;
								for (WTDMipmap *pMipmap : vecTextureMipmapsToDump)
								{
									string strImageDataBGRA = pMipmap->getRasterDataBGRA32();
									if (strImageDataBGRA == "")
									{
										vecMipmapSkippedEntries.push_back(LocalizationManager::get()->getTranslatedFormattedText("Log_TextureInfo", pIMGEntry->getEntryName().c_str(), uiTextureIndex + 1, pWTDEntry->getEntryName().c_str(), uiMipmapIndex + 1, pMipmap->getImageSize(true), pMipmap->getImageSize(false)));
										//uiMipmapSkippedCount++;
										uiMipmapIndex++;
										continue;
									}

									BMPFormat *pBMPFile = new BMPFormat;
									pBMPFile->setWidth(pMipmap->getImageSize(true));
									pBMPFile->setHeight(pMipmap->getImageSize(false));
									pBMPFile->setBPP(32);

									pBMPFile->setRasterData(strImageDataBGRA);
									pBMPFile->swapRows();

									if (strImageType == "BMP")
									{
										string strBMPFilePath;
										if (dumpWindowResult.m_bDumpTextureImagesAsFolders)
										{
											strBMPFilePath = dumpWindowResult.m_strOutputFolderPath + "Texture Images/" + Path::removeFileExtension(pIMGEntry->getEntryName()) + "/" + pWTDEntry->getEntryName() + ".BMP";
										}
										else
										{
											strBMPFilePath = dumpWindowResult.m_strOutputFolderPath + "Texture Images/" + pWTDEntry->getEntryName() + ".BMP";
										}
										strBMPFilePath = Path::getNextFileName(strBMPFilePath, uiMipmapIndex, "-Mipmap");
										
										pBMPFile->setBMPVersion(3);
										pBMPFile->serialize(strBMPFilePath);
									}
									else if (strImageType == "ICO")
									{
										string strICOFilePath;
										if (dumpWindowResult.m_bDumpTextureImagesAsFolders)
										{
											strICOFilePath = dumpWindowResult.m_strOutputFolderPath + "Texture Images/" + Path::removeFileExtension(pIMGEntry->getEntryName()) + "/" + pWTDEntry->getEntryName() + ".ICO";
										}
										else
										{
											strICOFilePath = dumpWindowResult.m_strOutputFolderPath + "Texture Images/" + pWTDEntry->getEntryName() + ".ICO";
										}
										strICOFilePath = Path::getNextFileName(strICOFilePath, uiMipmapIndex, "-Mipmap");

										string strICOHeaderData = "";
										strICOHeaderData += String::packUint16(0, false);
										strICOHeaderData += String::packUint16(1, false); // 1 for icon, 2 for cursor
										strICOHeaderData += String::packUint16(1, false); // image count
										strICOHeaderData += String::packUint8((uint8)pBMPFile->getWidth());
										strICOHeaderData += String::packUint8((uint8)pBMPFile->getHeight());
										strICOHeaderData += String::packUint8(0); // palette colour count
										strICOHeaderData += String::packUint8(0); // reserved
										strICOHeaderData += String::packUint16(0, false); // colour planes
										strICOHeaderData += String::packUint16(32, false); // BPP
										strICOHeaderData += String::packUint32((pBMPFile->getWidth() * pBMPFile->getHeight()) * (32 / 8), false); // BPP
										strICOHeaderData += String::packUint32(22, false); // offset to BMP data from beginning of file
										
										pBMPFile->setSkipBMPFileHeaderForSerialize(true);
										pBMPFile->setBMPVersion(3);
										File::storeFile(strICOFilePath, strICOHeaderData + pBMPFile->serialize(), false, true);
									}
									else if (strImageType == "CUR")
									{
										string strCURFilePath;
										if (dumpWindowResult.m_bDumpTextureImagesAsFolders)
										{
											strCURFilePath = dumpWindowResult.m_strOutputFolderPath + "Texture Images/" + Path::removeFileExtension(pIMGEntry->getEntryName()) + "/" + pWTDEntry->getEntryName() + ".CUR";
										}
										else
										{
											strCURFilePath = dumpWindowResult.m_strOutputFolderPath + "Texture Images/" + pWTDEntry->getEntryName() + ".CUR";
										}
										strCURFilePath = Path::getNextFileName(strCURFilePath, uiMipmapIndex, "-Mipmap");

										string strCURHeaderData = "";
										strCURHeaderData += String::packUint16(0, false);
										strCURHeaderData += String::packUint16(2, false); // 1 for icon, 2 for cursor
										strCURHeaderData += String::packUint16(1, false); // image count
										strCURHeaderData += String::packUint8((uint8)pBMPFile->getWidth());
										strCURHeaderData += String::packUint8((uint8)pBMPFile->getHeight());
										strCURHeaderData += String::packUint8(0); // palette colour count
										strCURHeaderData += String::packUint8(0); // reserved
										strCURHeaderData += String::packUint16((uint8)pBMPFile->getWidth() / 2, false); // x hotspot
										strCURHeaderData += String::packUint16((uint8)pBMPFile->getHeight() / 2, false); // y hotspot
										strCURHeaderData += String::packUint32((pBMPFile->getWidth() * pBMPFile->getHeight()) * (32 / 8), false); // BPP
										strCURHeaderData += String::packUint32(22, false); // offset to BMP data from beginning of file
										
										pBMPFile->setSkipBMPFileHeaderForSerialize(true);
										pBMPFile->setBMPVersion(3);
										File::storeFile(strCURFilePath, strCURHeaderData + pBMPFile->serialize(), false, true);
									}
									else if (strImageType == "DDS")
									{
										string strDDSFilePath;
										if (dumpWindowResult.m_bDumpTextureImagesAsFolders)
										{
											strDDSFilePath = dumpWindowResult.m_strOutputFolderPath + "Texture Images/" + Path::removeFileExtension(pIMGEntry->getEntryName()) + "/" + pWTDEntry->getEntryName() + ".DDS";
										}
										else
										{
											strDDSFilePath = dumpWindowResult.m_strOutputFolderPath + "Texture Images/" + pWTDEntry->getEntryName() + ".DDS";
										}

										strDDSFilePath = Path::getNextFileName(strDDSFilePath, uiMipmapIndex, "-Mipmap");

										DDSFormat ddsFile;
										ddsFile.m_uiWidth = pMipmap->getImageSize(true);
										ddsFile.m_uiHeight = pMipmap->getImageSize(false);
										//ddsFile.m_strRasterData = ImageManager::swapRowsAndColumns(ImageManager::convertBGRA32ToRGBA32(strImageDataBGRA), ddsFile.m_uiWidth, ddsFile.m_uiHeight);
										ddsFile.m_strRasterData = ImageManager::convertBGRA32ToDXT(ImageManager::swapRowsAndColumns(strImageDataBGRA, ddsFile.m_uiWidth, ddsFile.m_uiHeight), DXT_1, ddsFile.m_uiWidth, ddsFile.m_uiHeight);
										ddsFile.serialize(strDDSFilePath);
									}
									else if (strImageType == "TGA")
									{
										string
											strTempBMPPath,
											strImagePath;
										if (dumpWindowResult.m_bDumpTextureImagesAsFolders)
										{
											strTempBMPPath = dumpWindowResult.m_strOutputFolderPath + "Texture Images/" + Path::removeFileExtension(pIMGEntry->getEntryName()) + "/" + "__TEMP_" + pWTDEntry->getEntryName() + ".BMP";
											strImagePath = dumpWindowResult.m_strOutputFolderPath + "Texture Images/" + Path::removeFileExtension(pIMGEntry->getEntryName()) + "/" + pWTDEntry->getEntryName() + "." + strImageType;
										}
										else
										{
											strTempBMPPath = dumpWindowResult.m_strOutputFolderPath + "Texture Images/__TEMP_" + pWTDEntry->getEntryName() + ".BMP";
											strImagePath = dumpWindowResult.m_strOutputFolderPath + "Texture Images/" + pWTDEntry->getEntryName() + "." + strImageType;
										}
										strImagePath = Path::getNextFileName(strImagePath, uiMipmapIndex, "-Mipmap");

										pBMPFile->setBMPVersion(3);
										pBMPFile->serialize(strTempBMPPath);

										DHPOBitmap *pBmp = new DHPOBitmap;
										pBmp->loadImage(String::convertStdStringToStdWString(strTempBMPPath).c_str());
										pBmp->saveImage(String::convertStdStringToStdWString(strImagePath).c_str());
										delete pBmp;

										File::removeFile(strTempBMPPath);
									}
									else
									{
										// PNG
										string
											strTempBMPPath,
											strImagePath;
										if (dumpWindowResult.m_bDumpTextureImagesAsFolders)
										{
											strTempBMPPath = dumpWindowResult.m_strOutputFolderPath + "Texture Images/" + Path::removeFileExtension(pIMGEntry->getEntryName()) + "/" + "__TEMP_" + pWTDEntry->getEntryName() + ".BMP";
											strImagePath = dumpWindowResult.m_strOutputFolderPath + "Texture Images/" + Path::removeFileExtension(pIMGEntry->getEntryName()) + "/" + pWTDEntry->getEntryName() + "." + strImageType;
										}
										else
										{
											strTempBMPPath = dumpWindowResult.m_strOutputFolderPath + "Texture Images/__TEMP_" + pWTDEntry->getEntryName() + ".BMP";
											strImagePath = dumpWindowResult.m_strOutputFolderPath + "Texture Images/" + pWTDEntry->getEntryName() + "." + strImageType;
										}
										strImagePath = Path::getNextFileName(strImagePath, uiMipmapIndex, "-Mipmap");
										
										pBMPFile->setBMPVersion(3);
										pBMPFile->serialize(strTempBMPPath);

										GdiplusStartupInput gdiplusStartupInput;
										ULONG_PTR gdiplusToken;
										GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

										// Create an Image object based on a PNG file.
										Image  *image = new Image(String::convertStdStringToStdWString(strTempBMPPath).c_str());

										// Save the image.
										CLSID gifClsid;
										GetEncoderClsid(String::convertStdStringToStdWString(getEncoderClassIdFromImageExtension(strImageType)).c_str(), &gifClsid);
										image->Save(String::convertStdStringToStdWString(strImagePath).c_str(), &gifClsid, NULL);

										delete image;
										GdiplusShutdown(gdiplusToken);

										File::removeFile(strTempBMPPath);
									}

									pBMPFile->unload();
									delete pBMPFile;
									uiMipmapIndex++;
								}
								uiTextureIndex++;
							}
						}
						
						pWTDFile->unload();
						delete pWTDFile;
					}

					uiDumpedTextureCount++;
				}
			}
			else
			{
				if (std::find(dumpWindowResult.m_vecEntryTypes.begin(), dumpWindowResult.m_vecEntryTypes.end(), "Other") != dumpWindowResult.m_vecEntryTypes.end())
				{
					vecDumpedEntryNames.push_back(pIMGEntry->getEntryName());
					pIMGFile->exportSingle(pIMGEntry, dumpWindowResult.m_strOutputFolderPath + "Other/");
				}
			}

			getIMGF()->getTaskManager()->onTaskProgressTick();
		}
	}

	vecCorruptTXDs = StdVector::removeDuplicates(vecCorruptTXDs);
	vecTooLargeTXDs = StdVector::removeDuplicates(vecTooLargeTXDs);
	vecInvalidResolutionTXDs = StdVector::removeDuplicates(vecInvalidResolutionTXDs);
	vecInvalidTextureNames = StdVector::removeDuplicates(vecInvalidTextureNames);
	vecDumpedEntryNames = StdVector::removeDuplicates(vecDumpedEntryNames);
	vecTextureNames = StdVector::removeDuplicates(vecTextureNames);
	vecTXDsContainingTooManyTextures = StdVector::removeDuplicates(vecTXDsContainingTooManyTextures);
	vecMipmapSkippedEntries = StdVector::removeDuplicates(vecMipmapSkippedEntries);

	/*
	todo

	// log
	if (pActiveEditorTab != nullptr)
	{
		uint32 uiDumpedFileCount = vecDumpedEntryNames.size() + uiDumpedTextureCount;
		uint32 uiIMGFileCount = vecIMGFormats.size();
		if (dumpWindowResult.m_uiDumpType == 2)
		{
			pActiveEditorTab->log(LocalizationManager::get()->getTranslatedFormattedText("Log_10", uiDumpedFileCount, uiIMGFileCount));
		}
		else
		{
			pActiveEditorTab->log(LocalizationManager::get()->getTranslatedFormattedText("Log_11", uiDumpedFileCount, uiIMGFileCount));
		}
		pActiveEditorTab->log(LocalizationManager::get()->getTranslatedText("Log_12"), true);
		pActiveEditorTab->log(LocalizationManager::get()->getTranslatedFormattedText("Log_13", vecDumpedEntryNames.size()), true);
		pActiveEditorTab->log(LocalizationManager::get()->getTranslatedFormattedText("Log_14", uiDumpedTextureCount), true);
		pActiveEditorTab->log(LocalizationManager::get()->getTranslatedText("Log_15"), true);
		pActiveEditorTab->log(String::join(vecCorruptTXDs, "\n"), true);
		pActiveEditorTab->log(LocalizationManager::get()->getTranslatedText("Log_16"), true);
		pActiveEditorTab->log(String::join(vecTooLargeTXDs, "\n"), true);
		pActiveEditorTab->log(LocalizationManager::get()->getTranslatedText("Log_17"), true);
		pActiveEditorTab->log(String::join(vecTXDsContainingTooManyTextures, "\n"), true);
		pActiveEditorTab->log(LocalizationManager::get()->getTranslatedText("Log_18"), true);
		pActiveEditorTab->log(String::join(vecInvalidResolutionTXDs, "\n"), true);
		pActiveEditorTab->log(LocalizationManager::get()->getTranslatedText("Log_19"), true);
		pActiveEditorTab->log(String::join(vecInvalidTextureNames, "\n"), true);
		pActiveEditorTab->log(LocalizationManager::get()->getTranslatedText("Log_20"), true);
		pActiveEditorTab->log(String::join(vecDumpedEntryNames, "\n"), true);
		pActiveEditorTab->log(LocalizationManager::get()->getTranslatedText("Log_21"), true);
		pActiveEditorTab->log(String::join(vecTextureNames, "\n"), true);
		pActiveEditorTab->log(LocalizationManager::get()->getTranslatedText("Log_22"), true);
		pActiveEditorTab->log(String::join(vecMipmapSkippedEntries, "\n"), true);
	}
	*/

	/*
	todo
	
	// results popup
	bool bSuccessfulResult =
		vecCorruptTXDs.size() == 0 &&
		vecTooLargeTXDs.size() == 0 &&
		vecInvalidResolutionTXDs.size() == 0 &&
		vecInvalidTextureNames.size() == 0 &&
		vecTXDsContainingTooManyTextures.size() == 0 &&
		vecMipmapSkippedEntries.size() == 0;
	if (bSuccessfulResult)
	{
		getIMGF()->getTaskManager()->onPauseTask();
		Tasks::showMessage(LocalizationManager::get()->getTranslatedText("TextPopup_1"), LocalizationManager::get()->getTranslatedText("TextPopupTitle_1"));
		getIMGF()->getTaskManager()->onResumeTask();
	}
	else
	{
		CDumpResultsDialogData *pDumpResultsDialogData = new CDumpResultsDialogData;
		pDumpResultsDialogData->m_uiCorruptTXDCount = vecCorruptTXDs.size();
		pDumpResultsDialogData->m_uiTooLargeTXDCount = vecTooLargeTXDs.size();
		pDumpResultsDialogData->m_uiInvalidResolutionTXDCount = vecInvalidResolutionTXDs.size();
		pDumpResultsDialogData->m_uiInvalidTextureNameCount = vecInvalidTextureNames.size();
		pDumpResultsDialogData->m_uiTXDCountExceededTextureCountLimit = vecTXDsContainingTooManyTextures.size();
		pDumpResultsDialogData->m_uiMipmapSkippedCount = vecMipmapSkippedEntries.size();
		getIMGF()->getTaskManager()->onPauseTask();
		getIMGF()->getPopupGUIManager()->showDumpResultsDialog(pDumpResultsDialogData);
		getIMGF()->getTaskManager()->onResumeTask();

		if (pDumpResultsDialogData->m_bOpenAdvancedLog)
		{
			string strFilePath = getIMGF()->getSettingsManager()->getSettingString("AutomaticLoggingPath") + String::getDateTextForFolder() + " / " + LocalizationManager::get()->getTranslatedText("LogFilename_Extended");

			if (getIMGF()->getSettingsManager()->getSettingBool("AutomaticLoggingExtended") && File::doesFileExist(strFilePath))
			{
				// automatic logging is enabled, simply open the txt file for the user
				ShellExecute(NULL, NULL, String::convertStdStringToStdWString(strFilePath).c_str(), NULL, NULL, SW_SHOWNORMAL);
			}
			else
			{
				// ask user to save the extended log file, then open the txt file
				getIMGF()->getTaskManager()->onPauseTask();
				string strSaveFilePath = getIMGF()->getTaskManager()->getDispatch()->onRequestSaveLog(true, false);
				getIMGF()->getTaskManager()->onResumeTask();
				if (strSaveFilePath != "")
				{
					ShellExecute(NULL, NULL, String::convertStdStringToStdWString(strSaveFilePath).c_str(), NULL, NULL, SW_SHOWNORMAL);
				}
			}
		}

		delete pDumpResultsDialogData;
	}
	*/

	// clean up
	if (dumpWindowResult.m_uiDumpType == 2 || dumpWindowResult.m_uiDumpType == 3)
	{
		for (auto pIMGFile : vecIMGFormats)
		{
			pIMGFile->unload();
			delete pIMGFile;
		}
	}

	return true;
}

string			DumpManager::getEncoderClassIdFromImageExtension(string strFileExtension)
{
	strFileExtension = String::toUpperCase(strFileExtension);
	if (strFileExtension == "GIF")
	{
		return "image/gif";
	}
	else if (strFileExtension == "JPG")
	{
		return "image/jpeg";
	}
	else if (strFileExtension == "PNG")
	{
		return "image/png";
	}
	else if (strFileExtension == "TIFF")
	{
		return "image/tiff";
	}
	else
	{
		return "";
	}
}