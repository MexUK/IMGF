#pragma warning(disable : 4005)

#include "DumpManager.h"
#include "IMGF.h"
#include "Globals.h"
#include "GUI/Editors/IMGEditor.h"
#include "GUI/Editors/Tab/IMGEditorTab.h"
#include "GUI/Popups/PopupGUIManager.h"
#include "Format/IMG/Regular/IMGFormat.h"
#include "Static/Input.h"
#include "Static/Path.h"
#include "Static/String2.h"
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
#include "Task/TaskDispatchManager.h"
#include "Format/IMG/Regular/IMGEntry.h"
#include "Format/WTD/WTDManager.h"
#include "Format/WTD/WTDFormat.h"
#include "Format/WTD/WTDEntry.h"
#include "Image/ImageManager.h"
#include "Format/Image/DDS/DDSFormat.h"
#include "Localization/LocalizationManager.h"
#include "Settings/SettingsManager.h"
#include <gdiplus.h>

using namespace std;
using namespace bxcf;
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

void		DumpManager::process(void)
{
	getIMGF()->getTaskManager()->onPauseTask();
	CDumpDialogData *pDumpDialogData = getIMGF()->getPopupGUIManager()->showDumpDialog(getIMGF()->getLastUsedDirectory("DUMP__DAT"), getIMGF()->getLastUsedDirectory("DUMP__Destination"));
	getIMGF()->getTaskManager()->onResumeTask();
	if (!pDumpDialogData->m_bResult)
	{
		getIMGF()->getTaskManager()->onTaskEnd("onRequestDump", true);
		delete pDumpDialogData;
		return;
	}
	if (pDumpDialogData->m_uiDumpType == 2)
	{
		getIMGF()->setLastUsedDirectory("DUMP__DAT", pDumpDialogData->m_strDATPath);
	}
	getIMGF()->setLastUsedDirectory("DUMP__Destination", pDumpDialogData->m_strDumpDestinationFolderPath);

	// choose img files
	vector<IMGFormat*> vecIMGFormats;
	if (pDumpDialogData->m_uiDumpType == 0) // All entries in active tab
	{
		if (getIMGF()->getEntryListTab() == nullptr)
		{
			delete pDumpDialogData;
			getIMGF()->getTaskManager()->onTaskEnd("onRequestDump", true);
			return;
		}

		vecIMGFormats.push_back(getIMGF()->getEntryListTab()->getIMGFile());
	}
	else if (pDumpDialogData->m_uiDumpType == 4) // Selected entries in active tab
	{
		if (getIMGF()->getEntryListTab() == nullptr)
		{
			delete pDumpDialogData;
			getIMGF()->getTaskManager()->onTaskEnd("onRequestDump", true);
			return;
		}

		vecIMGFormats.push_back(getIMGF()->getEntryListTab()->getIMGFile());
	}
	else if (pDumpDialogData->m_uiDumpType == 1) // All entries in all tabs
	{
		vecIMGFormats = getIMGF()->getIMGEditor()->getAllMainWindowTabsIMGFiles();
	}
	else if (pDumpDialogData->m_uiDumpType == 2) // DAT file
	{
		EPlatformedGame EPlatformedGameValue = UNKNOWN_PLATFORMED_GAME;
		switch (pDumpDialogData->m_uiDATOptionIndex)
		{
		case 0: // GTA III
			EPlatformedGameValue = PC_GTA_III;
			break;
		case 1: // GTA VC
			EPlatformedGameValue = PC_GTA_VC;
			break;
		case 2: // GTA SA
			EPlatformedGameValue = PC_GTA_SA;
			break;
		case 3: // SOL
			EPlatformedGameValue = PC_SOL;
			break;
		case 4: // Other
			break;
		}
		string strDATPath = pDumpDialogData->m_strGameDirectoryPath + DATLoaderManager::getDefaultGameDATSubPath(EPlatformedGameValue);

		DATLoaderFormat *pDATFile = DATLoaderManager::get()->parseViaFile(strDATPath);
		if (!pDATFile->doesHaveError())
		{
			vecIMGFormats = pDATFile->parseIMGFiles(pDumpDialogData->m_strGameDirectoryPath);
		}
		pDATFile->unload();
		delete pDATFile;

		vector<string> vecGameIMGPaths = IMGManager::getDefaultGameIMGSubPaths(EPlatformedGameValue);

		for (auto strIMGRelativePath : vecGameIMGPaths)
		{
			string strIMGPath = pDumpDialogData->m_strGameDirectoryPath + strIMGRelativePath;
			if (File::doesFileExist(strIMGPath))
			{
				IMGFormat *pIMGFile = IMGManager::get()->parseViaFile(strIMGPath);
				if(!pIMGFile->doesHaveError())
				{
					vecIMGFormats.push_back(pIMGFile);
				}
			}
		}
	}
	else if (pDumpDialogData->m_uiDumpType == 3) // Game IMGs
	{
		EPlatformedGame EPlatformedGameValue2 = UNKNOWN_PLATFORMED_GAME;
		switch (pDumpDialogData->m_uiDATOptionIndex)
		{
		case 0: // GTA III
			EPlatformedGameValue2 = PC_GTA_III;
			break;
		case 1: // GTA VC
			EPlatformedGameValue2 = PC_GTA_VC;
			break;
		case 2: // GTA SA
			EPlatformedGameValue2 = PC_GTA_SA;
			break;
		case 3: // SOL
			EPlatformedGameValue2 = PC_SOL;
			break;
		case 4: // Other
			break;
		}

		vector<string> vecGameIMGPaths = IMGManager::getDefaultGameIMGSubPaths(EPlatformedGameValue2);

		for (auto strIMGRelativePath : vecGameIMGPaths)
		{
			string strIMGPath = pDumpDialogData->m_strGameDirectoryPath + strIMGRelativePath;
			if (File::doesFileExist(strIMGPath))
			{
				IMGFormat *pIMGFile = IMGManager::get()->parseViaFile(strIMGPath);
				if(!pIMGFile->doesHaveError())
				{
					vecIMGFormats.push_back(pIMGFile);
				}
			}
		}
	}

	// dump folder path
	pDumpDialogData->m_strDumpDestinationFolderPath = Path::addSlashToEnd(pDumpDialogData->m_strDumpDestinationFolderPath);

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

	for (auto pIMGFile : vecIMGFormats)
	{
		// choose IMG entries to dump
		vector<IMGEntry*> vecIMGEntries;
		if (pDumpDialogData->m_uiDumpType == 4) // selected entries
		{
			vecIMGEntries = getIMGF()->getEntryListTab()->getSelectedEntries();
		}
		else
		{
			vecIMGEntries = pIMGFile->getEntries();
		}

		// dump IMG entries
		for (auto pIMGEntry : vecIMGEntries)
		{
			string strExtension = String2::toUpperCase(Path::getFileExtension(pIMGEntry->getEntryName()));
			if (strExtension == "COL" || strExtension == "WBN" || strExtension == "WBD")
			{
				if (std::find(pDumpDialogData->m_vecDumpExtensions.begin(), pDumpDialogData->m_vecDumpExtensions.end(), "COL") != pDumpDialogData->m_vecDumpExtensions.end())
				{
					vecDumpedEntryNames.push_back(pIMGEntry->getEntryName());
					pIMGFile->exportSingle(pIMGEntry, pDumpDialogData->m_strDumpDestinationFolderPath + strExtension + "/");
				}
			}
			else if (strExtension == "DFF" || strExtension == "BSP" || strExtension == "MDL" || strExtension == "WDR" || strExtension == "WDD")
			{
				if (std::find(pDumpDialogData->m_vecDumpExtensions.begin(), pDumpDialogData->m_vecDumpExtensions.end(), "DFF") != pDumpDialogData->m_vecDumpExtensions.end())
				{
					vecDumpedEntryNames.push_back(pIMGEntry->getEntryName());
					pIMGFile->exportSingle(pIMGEntry, pDumpDialogData->m_strDumpDestinationFolderPath + strExtension + "/");
				}
			}
			else if (strExtension == "IPL" || strExtension == "WPL")
			{
				if (std::find(pDumpDialogData->m_vecDumpExtensions.begin(), pDumpDialogData->m_vecDumpExtensions.end(), "IPL") != pDumpDialogData->m_vecDumpExtensions.end())
				{
					vecDumpedEntryNames.push_back(pIMGEntry->getEntryName());
					pIMGFile->exportSingle(pIMGEntry, pDumpDialogData->m_strDumpDestinationFolderPath + strExtension + "/");
				}
			}
			else if (strExtension == "TXD" || strExtension == "WTD")
			{
				if (std::find(pDumpDialogData->m_vecDumpExtensions.begin(), pDumpDialogData->m_vecDumpExtensions.end(), "TXD") != pDumpDialogData->m_vecDumpExtensions.end())
				{
					vecDumpedEntryNames.push_back(pIMGEntry->getEntryName());
					pIMGFile->exportSingle(pIMGEntry, pDumpDialogData->m_strDumpDestinationFolderPath + strExtension + "/");

					string strTXDData = pIMGEntry->getEntryData();
					if (!TXDFormat::isTXDSizeValid(strTXDData.size()))
					{
						vecTooLargeTXDs.push_back(LocalizationManager::get()->getTranslatedFormattedText("Log_TXD_MaxSize", pIMGEntry->getEntryName().c_str()));
					}

					TXDFormat *pTXDFile = TXDManager::get()->parseViaMemory(strTXDData);
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
							vecInvalidResolutionTXDs.push_back("[" + pIMGEntry->getEntryName() + "] " + pTexture->getDiffuseName() + " (" + String2::toString(pTexture->getImageSize().x) + " x " + String2::toString(pTexture->getImageSize().y) + ")");
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

				if (std::find(pDumpDialogData->m_vecDumpExtensions.begin(), pDumpDialogData->m_vecDumpExtensions.end(), "Texture Images") != pDumpDialogData->m_vecDumpExtensions.end())
				{
					//vector<IMGEntry*> vecIMGEntries;
					//vecIMGEntries.push_back(pIMGEntry);
					//IMGManager::get()->exportEntries(pIMGFile, vecIMGEntries, pDumpDialogData->m_strDumpDestinationFolderPath + strExtension + "/");

					string strEntryExtensionUpper = String2::toUpperCase(Path::getFileExtension(pIMGEntry->getEntryName()));
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
						TXDFormat *pTXDFile = TXDManager::get()->parseViaMemory(strTXDData);
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

						for (auto strImageType : pDumpDialogData->m_vecDumpImageTypes)
						{
							uint32 uiTextureIndex = 0;
							for (auto pTexture : pTXDFile->getTextures())
							{
								if (pTexture->getDiffuseName().length() == 0)
								{
									continue;
								}

								/*
								Debugger::log("pTexture->m_strDiffuseName: [" + pIMGEntry->getEntryName() + "] " + pTexture->getDiffuseName());
								Debugger::log("pTexture->m_usWidth: " + String2::toString(pTexture->getImageSize(true)));
								Debugger::log("pTexture->m_usHeight: " + String2::toString(pTexture->getImageSize(false)));
								Debugger::log("pTexture->m_uiRasterFormat: " + String2::toString(pTexture->getRasterFormat()));
								Debugger::log("pTexture->m_ucBPP: " + String2::toString(pTexture->getBPP()));
								*/

								if (!TXDFormat::isTextureResolutionValid((uint16)pTexture->getImageSize().x, (uint16)pTexture->getImageSize().y, pTXDFile->getPlatformedGames()))
								{
									vecInvalidResolutionTXDs.push_back("[" + pIMGEntry->getEntryName() + "] " + pTexture->getDiffuseName() + " (" + String2::toString(pTexture->getImageSize().x) + " x " + String2::toString(pTexture->getImageSize().y) + ")");
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
								if (pDumpDialogData->m_bDumpAllTextureMipmaps)
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
										if (pDumpDialogData->m_bDumpTextureImagesAsFolders)
										{
											strBMPFilePath = pDumpDialogData->m_strDumpDestinationFolderPath + "Texture Images/" + Path::removeFileExtension(pIMGEntry->getEntryName()) + "/" + pTexture->getDiffuseName() + ".BMP";
										}
										else
										{
											strBMPFilePath = pDumpDialogData->m_strDumpDestinationFolderPath + "Texture Images/" + pTexture->getDiffuseName() + ".BMP";
										}
										strBMPFilePath = Path::getNextFileName(strBMPFilePath, uiMipmapIndex, "-Mipmap");

										pBMPFile->setBMPVersion(3);
										pBMPFile->serializeViaFile(strBMPFilePath);
									}
									else if (strImageType == "ICO")
									{
										string strICOFilePath;
										if (pDumpDialogData->m_bDumpTextureImagesAsFolders)
										{
											strICOFilePath = pDumpDialogData->m_strDumpDestinationFolderPath + "Texture Images/" + Path::removeFileExtension(pIMGEntry->getEntryName()) + "/" + pTexture->getDiffuseName() + ".ICO";
										}
										else
										{
											strICOFilePath = pDumpDialogData->m_strDumpDestinationFolderPath + "Texture Images/" + pTexture->getDiffuseName() + ".ICO";
										}
										strICOFilePath = Path::getNextFileName(strICOFilePath, uiMipmapIndex, "-Mipmap");

										ICOFormat *pICOFormat = ICOManager::get()->createFormatFromBMP(pBMPFile);
										pICOFormat->serializeViaFile(strICOFilePath);
										pICOFormat->unload();
										delete pICOFormat;
									}
									else if (strImageType == "CUR")
									{
										string strCURFilePath;
										if (pDumpDialogData->m_bDumpTextureImagesAsFolders)
										{
											strCURFilePath = pDumpDialogData->m_strDumpDestinationFolderPath + "Texture Images/" + Path::removeFileExtension(pIMGEntry->getEntryName()) + "/" + pTexture->getDiffuseName() + ".CUR";
										}
										else
										{
											strCURFilePath = pDumpDialogData->m_strDumpDestinationFolderPath + "Texture Images/" + pTexture->getDiffuseName() + ".CUR";
										}
										strCURFilePath = Path::getNextFileName(strCURFilePath, uiMipmapIndex, "-Mipmap");
										
										CURFormat *pCURFormat = CURManager::get()->createFormatFromBMP(pBMPFile);
										pCURFormat->serializeViaFile(strCURFilePath);
										pCURFormat->unload();
										delete pCURFormat;
									}
									else if (strImageType == "DDS")
									{
										string strDDSFilePath;
										if (pDumpDialogData->m_bDumpTextureImagesAsFolders)
										{
											strDDSFilePath = pDumpDialogData->m_strDumpDestinationFolderPath + "Texture Images/" + Path::removeFileExtension(pIMGEntry->getEntryName()) + "/" + pTexture->getDiffuseName() + ".DDS";
										}
										else
										{
											strDDSFilePath = pDumpDialogData->m_strDumpDestinationFolderPath + "Texture Images/" + pTexture->getDiffuseName() + ".DDS";
										}
										strDDSFilePath = Path::getNextFileName(strDDSFilePath, uiMipmapIndex, "-Mipmap");

										DDSFormat ddsFile;
										ddsFile.m_uiWidth = pMipmap->getImageSize().x;
										ddsFile.m_uiHeight = pMipmap->getImageSize().y;
										//ddsFile.m_strRasterData = ImageManager::swapRowsAndColumns(ImageManager::convertBGRA32ToRGBA32(strImageDataBGRA), ddsFile.m_uiWidth, ddsFile.m_uiHeight);
										ddsFile.m_strRasterData = ImageManager::convertBGRA32ToDXT(ImageManager::swapRowsAndColumns(strImageDataBGRA, ddsFile.m_uiWidth, ddsFile.m_uiHeight), DXT_1, ddsFile.m_uiWidth, ddsFile.m_uiHeight);
										ddsFile.serializeViaFile(strDDSFilePath);
									}
									else if (strImageType == "TGA")
									{
										string
											strTempBMPPath,
											strImagePath;
										if (pDumpDialogData->m_bDumpTextureImagesAsFolders)
										{
											strTempBMPPath = pDumpDialogData->m_strDumpDestinationFolderPath + "Texture Images/" + Path::removeFileExtension(pIMGEntry->getEntryName()) + "/" + "__TEMP_" + pTexture->getDiffuseName() + ".BMP";
											strImagePath = pDumpDialogData->m_strDumpDestinationFolderPath + "Texture Images/" + Path::removeFileExtension(pIMGEntry->getEntryName()) + "/" + pTexture->getDiffuseName() + "." + strImageType;
										}
										else
										{
											strTempBMPPath = pDumpDialogData->m_strDumpDestinationFolderPath + "Texture Images/__TEMP_" + pTexture->getDiffuseName() + ".BMP";
											strImagePath = pDumpDialogData->m_strDumpDestinationFolderPath + "Texture Images/" + pTexture->getDiffuseName() + "." + strImageType;
										}
										strImagePath = Path::getNextFileName(strImagePath, uiMipmapIndex, "-Mipmap");

										pBMPFile->setBMPVersion(3);
										pBMPFile->serializeViaFile(strTempBMPPath);

										DHPOBitmap *pBmp = new DHPOBitmap;
										pBmp->loadImage(String2::convertStdStringToStdWString(strTempBMPPath).c_str());
										pBmp->saveImage(String2::convertStdStringToStdWString(strImagePath).c_str());
										delete pBmp;

										File::removeFile(strTempBMPPath);
									}
									else
									{
										// PNG
										string
											strTempBMPPath,
											strImagePath;
										if (pDumpDialogData->m_bDumpTextureImagesAsFolders)
										{
											strTempBMPPath = pDumpDialogData->m_strDumpDestinationFolderPath + "Texture Images/" + Path::removeFileExtension(pIMGEntry->getEntryName()) + "/" + "__TEMP_" + pTexture->getDiffuseName() + ".BMP";
											strImagePath = pDumpDialogData->m_strDumpDestinationFolderPath + "Texture Images/" + Path::removeFileExtension(pIMGEntry->getEntryName()) + "/" + pTexture->getDiffuseName() + "." + strImageType;
										}
										else
										{
											strTempBMPPath = pDumpDialogData->m_strDumpDestinationFolderPath + "Texture Images/__TEMP_" + pTexture->getDiffuseName() + ".BMP";
											strImagePath = pDumpDialogData->m_strDumpDestinationFolderPath + "Texture Images/" + pTexture->getDiffuseName() + "." + strImageType;
										}
										strImagePath = Path::getNextFileName(strImagePath, uiMipmapIndex, "-Mipmap");

										pBMPFile->setBMPVersion(3);
										pBMPFile->serializeViaFile(strTempBMPPath);

										GdiplusStartupInput gdiplusStartupInput;
										ULONG_PTR gdiplusToken;
										GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

										// Create an Image object based on a PNG file.
										Image  *image = new Image(String2::convertStdStringToStdWString(strTempBMPPath).c_str());

										// Save the image.
										CLSID gifClsid;
										GetEncoderClsid(String2::convertStdStringToStdWString(getEncoderClassIdFromImageExtension(strImageType)).c_str(), &gifClsid);
										image->Save(String2::convertStdStringToStdWString(strImagePath).c_str(), &gifClsid, NULL);

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
						WTDFormat *pWTDFile = WTDManager::get()->parseViaMemory(pIMGEntry->getEntryData());
						
						if (pWTDFile->doesHaveError())
						{
							vecCorruptTXDs.push_back(pIMGEntry->getEntryName());
							getIMGF()->getTaskManager()->onTaskProgressTick();
							continue;
						}

						for (auto strImageType : pDumpDialogData->m_vecDumpImageTypes)
						{
							uint32 uiTextureIndex = 0;
							for (auto pWTDEntry : pWTDFile->getEntries())
							{
								if (pWTDEntry->getEntryName().length() == 0)
								{
									continue;
								}

								string strTextureNamesLogLine = pWTDEntry->getEntryName();
								vecTextureNames.push_back(strTextureNamesLogLine);

								// choose whether to dump all mipmaps in the texture, or just the first mipmap in the texture
								vector<WTDMipmap*> vecTextureMipmapsToDump;
								if (pDumpDialogData->m_bDumpAllTextureMipmaps)
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
								for (auto pMipmap : vecTextureMipmapsToDump)
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
										if (pDumpDialogData->m_bDumpTextureImagesAsFolders)
										{
											strBMPFilePath = pDumpDialogData->m_strDumpDestinationFolderPath + "Texture Images/" + Path::removeFileExtension(pIMGEntry->getEntryName()) + "/" + pWTDEntry->getEntryName() + ".BMP";
										}
										else
										{
											strBMPFilePath = pDumpDialogData->m_strDumpDestinationFolderPath + "Texture Images/" + pWTDEntry->getEntryName() + ".BMP";
										}
										strBMPFilePath = Path::getNextFileName(strBMPFilePath, uiMipmapIndex, "-Mipmap");
										
										pBMPFile->setBMPVersion(3);
										pBMPFile->serializeViaFile(strBMPFilePath);
									}
									else if (strImageType == "ICO")
									{
										string strICOFilePath;
										if (pDumpDialogData->m_bDumpTextureImagesAsFolders)
										{
											strICOFilePath = pDumpDialogData->m_strDumpDestinationFolderPath + "Texture Images/" + Path::removeFileExtension(pIMGEntry->getEntryName()) + "/" + pWTDEntry->getEntryName() + ".ICO";
										}
										else
										{
											strICOFilePath = pDumpDialogData->m_strDumpDestinationFolderPath + "Texture Images/" + pWTDEntry->getEntryName() + ".ICO";
										}
										strICOFilePath = Path::getNextFileName(strICOFilePath, uiMipmapIndex, "-Mipmap");

										string strICOHeaderData = "";
										strICOHeaderData += String2::packUint16(0, false);
										strICOHeaderData += String2::packUint16(1, false); // 1 for icon, 2 for cursor
										strICOHeaderData += String2::packUint16(1, false); // image count
										strICOHeaderData += String2::packUint8((uint8)pBMPFile->getWidth());
										strICOHeaderData += String2::packUint8((uint8)pBMPFile->getHeight());
										strICOHeaderData += String2::packUint8(0); // palette colour count
										strICOHeaderData += String2::packUint8(0); // reserved
										strICOHeaderData += String2::packUint16(0, false); // colour planes
										strICOHeaderData += String2::packUint16(32, false); // BPP
										strICOHeaderData += String2::packUint32((pBMPFile->getWidth() * pBMPFile->getHeight()) * (32 / 8), false); // BPP
										strICOHeaderData += String2::packUint32(22, false); // offset to BMP data from beginning of file
										
										pBMPFile->setSkipBMPFileHeaderForSerialize(true);
										pBMPFile->setBMPVersion(3);
										File::storeFile(strICOFilePath, strICOHeaderData + pBMPFile->serializeViaMemory(), false, true);
									}
									else if (strImageType == "CUR")
									{
										string strCURFilePath;
										if (pDumpDialogData->m_bDumpTextureImagesAsFolders)
										{
											strCURFilePath = pDumpDialogData->m_strDumpDestinationFolderPath + "Texture Images/" + Path::removeFileExtension(pIMGEntry->getEntryName()) + "/" + pWTDEntry->getEntryName() + ".CUR";
										}
										else
										{
											strCURFilePath = pDumpDialogData->m_strDumpDestinationFolderPath + "Texture Images/" + pWTDEntry->getEntryName() + ".CUR";
										}
										strCURFilePath = Path::getNextFileName(strCURFilePath, uiMipmapIndex, "-Mipmap");

										string strCURHeaderData = "";
										strCURHeaderData += String2::packUint16(0, false);
										strCURHeaderData += String2::packUint16(2, false); // 1 for icon, 2 for cursor
										strCURHeaderData += String2::packUint16(1, false); // image count
										strCURHeaderData += String2::packUint8((uint8)pBMPFile->getWidth());
										strCURHeaderData += String2::packUint8((uint8)pBMPFile->getHeight());
										strCURHeaderData += String2::packUint8(0); // palette colour count
										strCURHeaderData += String2::packUint8(0); // reserved
										strCURHeaderData += String2::packUint16((uint8)pBMPFile->getWidth() / 2, false); // x hotspot
										strCURHeaderData += String2::packUint16((uint8)pBMPFile->getHeight() / 2, false); // y hotspot
										strCURHeaderData += String2::packUint32((pBMPFile->getWidth() * pBMPFile->getHeight()) * (32 / 8), false); // BPP
										strCURHeaderData += String2::packUint32(22, false); // offset to BMP data from beginning of file
										
										pBMPFile->setSkipBMPFileHeaderForSerialize(true);
										pBMPFile->setBMPVersion(3);
										File::storeFile(strCURFilePath, strCURHeaderData + pBMPFile->serializeViaMemory(), false, true);
									}
									else if (strImageType == "DDS")
									{
										string strDDSFilePath;
										if (pDumpDialogData->m_bDumpTextureImagesAsFolders)
										{
											strDDSFilePath = pDumpDialogData->m_strDumpDestinationFolderPath + "Texture Images/" + Path::removeFileExtension(pIMGEntry->getEntryName()) + "/" + pWTDEntry->getEntryName() + ".DDS";
										}
										else
										{
											strDDSFilePath = pDumpDialogData->m_strDumpDestinationFolderPath + "Texture Images/" + pWTDEntry->getEntryName() + ".DDS";
										}

										strDDSFilePath = Path::getNextFileName(strDDSFilePath, uiMipmapIndex, "-Mipmap");

										DDSFormat ddsFile;
										ddsFile.m_uiWidth = pMipmap->getImageSize(true);
										ddsFile.m_uiHeight = pMipmap->getImageSize(false);
										//ddsFile.m_strRasterData = ImageManager::swapRowsAndColumns(ImageManager::convertBGRA32ToRGBA32(strImageDataBGRA), ddsFile.m_uiWidth, ddsFile.m_uiHeight);
										ddsFile.m_strRasterData = ImageManager::convertBGRA32ToDXT(ImageManager::swapRowsAndColumns(strImageDataBGRA, ddsFile.m_uiWidth, ddsFile.m_uiHeight), DXT_1, ddsFile.m_uiWidth, ddsFile.m_uiHeight);
										ddsFile.serializeViaFile(strDDSFilePath);
									}
									else if (strImageType == "TGA")
									{
										string
											strTempBMPPath,
											strImagePath;
										if (pDumpDialogData->m_bDumpTextureImagesAsFolders)
										{
											strTempBMPPath = pDumpDialogData->m_strDumpDestinationFolderPath + "Texture Images/" + Path::removeFileExtension(pIMGEntry->getEntryName()) + "/" + "__TEMP_" + pWTDEntry->getEntryName() + ".BMP";
											strImagePath = pDumpDialogData->m_strDumpDestinationFolderPath + "Texture Images/" + Path::removeFileExtension(pIMGEntry->getEntryName()) + "/" + pWTDEntry->getEntryName() + "." + strImageType;
										}
										else
										{
											strTempBMPPath = pDumpDialogData->m_strDumpDestinationFolderPath + "Texture Images/__TEMP_" + pWTDEntry->getEntryName() + ".BMP";
											strImagePath = pDumpDialogData->m_strDumpDestinationFolderPath + "Texture Images/" + pWTDEntry->getEntryName() + "." + strImageType;
										}
										strImagePath = Path::getNextFileName(strImagePath, uiMipmapIndex, "-Mipmap");

										pBMPFile->setBMPVersion(3);
										pBMPFile->serializeViaFile(strTempBMPPath);

										DHPOBitmap *pBmp = new DHPOBitmap;
										pBmp->loadImage(String2::convertStdStringToStdWString(strTempBMPPath).c_str());
										pBmp->saveImage(String2::convertStdStringToStdWString(strImagePath).c_str());
										delete pBmp;

										File::removeFile(strTempBMPPath);
									}
									else
									{
										// PNG
										string
											strTempBMPPath,
											strImagePath;
										if (pDumpDialogData->m_bDumpTextureImagesAsFolders)
										{
											strTempBMPPath = pDumpDialogData->m_strDumpDestinationFolderPath + "Texture Images/" + Path::removeFileExtension(pIMGEntry->getEntryName()) + "/" + "__TEMP_" + pWTDEntry->getEntryName() + ".BMP";
											strImagePath = pDumpDialogData->m_strDumpDestinationFolderPath + "Texture Images/" + Path::removeFileExtension(pIMGEntry->getEntryName()) + "/" + pWTDEntry->getEntryName() + "." + strImageType;
										}
										else
										{
											strTempBMPPath = pDumpDialogData->m_strDumpDestinationFolderPath + "Texture Images/__TEMP_" + pWTDEntry->getEntryName() + ".BMP";
											strImagePath = pDumpDialogData->m_strDumpDestinationFolderPath + "Texture Images/" + pWTDEntry->getEntryName() + "." + strImageType;
										}
										strImagePath = Path::getNextFileName(strImagePath, uiMipmapIndex, "-Mipmap");
										
										pBMPFile->setBMPVersion(3);
										pBMPFile->serializeViaFile(strTempBMPPath);

										GdiplusStartupInput gdiplusStartupInput;
										ULONG_PTR gdiplusToken;
										GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

										// Create an Image object based on a PNG file.
										Image  *image = new Image(String2::convertStdStringToStdWString(strTempBMPPath).c_str());

										// Save the image.
										CLSID gifClsid;
										GetEncoderClsid(String2::convertStdStringToStdWString(getEncoderClassIdFromImageExtension(strImageType)).c_str(), &gifClsid);
										image->Save(String2::convertStdStringToStdWString(strImagePath).c_str(), &gifClsid, NULL);

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
				if (std::find(pDumpDialogData->m_vecDumpExtensions.begin(), pDumpDialogData->m_vecDumpExtensions.end(), "Other") != pDumpDialogData->m_vecDumpExtensions.end())
				{
					vecDumpedEntryNames.push_back(pIMGEntry->getEntryName());
					pIMGFile->exportSingle(pIMGEntry, pDumpDialogData->m_strDumpDestinationFolderPath + "Other/");
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

	// log
	if (getIMGF()->getEntryListTab() != nullptr)
	{
		uint32 uiDumpedFileCount = vecDumpedEntryNames.size() + uiDumpedTextureCount;
		uint32 uiIMGFileCount = vecIMGFormats.size();
		if (pDumpDialogData->m_uiDumpType == 2)
		{
			getIMGF()->getEntryListTab()->log(LocalizationManager::get()->getTranslatedFormattedText("Log_10", uiDumpedFileCount, uiIMGFileCount));
		}
		else
		{
			getIMGF()->getEntryListTab()->log(LocalizationManager::get()->getTranslatedFormattedText("Log_11", uiDumpedFileCount, uiIMGFileCount));
		}
		getIMGF()->getEntryListTab()->log(LocalizationManager::get()->getTranslatedText("Log_12"), true);
		getIMGF()->getEntryListTab()->log(LocalizationManager::get()->getTranslatedFormattedText("Log_13", vecDumpedEntryNames.size()), true);
		getIMGF()->getEntryListTab()->log(LocalizationManager::get()->getTranslatedFormattedText("Log_14", uiDumpedTextureCount), true);
		getIMGF()->getEntryListTab()->log(LocalizationManager::get()->getTranslatedText("Log_15"), true);
		getIMGF()->getEntryListTab()->log(String2::join(vecCorruptTXDs, "\n"), true);
		getIMGF()->getEntryListTab()->log(LocalizationManager::get()->getTranslatedText("Log_16"), true);
		getIMGF()->getEntryListTab()->log(String2::join(vecTooLargeTXDs, "\n"), true);
		getIMGF()->getEntryListTab()->log(LocalizationManager::get()->getTranslatedText("Log_17"), true);
		getIMGF()->getEntryListTab()->log(String2::join(vecTXDsContainingTooManyTextures, "\n"), true);
		getIMGF()->getEntryListTab()->log(LocalizationManager::get()->getTranslatedText("Log_18"), true);
		getIMGF()->getEntryListTab()->log(String2::join(vecInvalidResolutionTXDs, "\n"), true);
		getIMGF()->getEntryListTab()->log(LocalizationManager::get()->getTranslatedText("Log_19"), true);
		getIMGF()->getEntryListTab()->log(String2::join(vecInvalidTextureNames, "\n"), true);
		getIMGF()->getEntryListTab()->log(LocalizationManager::get()->getTranslatedText("Log_20"), true);
		getIMGF()->getEntryListTab()->log(String2::join(vecDumpedEntryNames, "\n"), true);
		getIMGF()->getEntryListTab()->log(LocalizationManager::get()->getTranslatedText("Log_21"), true);
		getIMGF()->getEntryListTab()->log(String2::join(vecTextureNames, "\n"), true);
		getIMGF()->getEntryListTab()->log(LocalizationManager::get()->getTranslatedText("Log_22"), true);
		getIMGF()->getEntryListTab()->log(String2::join(vecMipmapSkippedEntries, "\n"), true);
	}
	else
	{
		uint32 uiDumpedFileCount = vecDumpedEntryNames.size() + uiDumpedTextureCount;
		uint32 uiIMGFileCount = vecIMGFormats.size();
		if (pDumpDialogData->m_uiDumpType == 2)
		{
			getIMGF()->getIMGEditor()->logWithNoTabsOpen(LocalizationManager::get()->getTranslatedFormattedText("Log_10", uiDumpedFileCount, uiIMGFileCount));
		}
		else
		{
			getIMGF()->getIMGEditor()->logWithNoTabsOpen(LocalizationManager::get()->getTranslatedFormattedText("Log_11", uiDumpedFileCount, uiIMGFileCount));
		}
		getIMGF()->getIMGEditor()->logWithNoTabsOpen(LocalizationManager::get()->getTranslatedText("Log_12"), true);
		getIMGF()->getIMGEditor()->logWithNoTabsOpen(LocalizationManager::get()->getTranslatedFormattedText("Log_13", vecDumpedEntryNames.size()), true);
		getIMGF()->getIMGEditor()->logWithNoTabsOpen(LocalizationManager::get()->getTranslatedFormattedText("Log_14", uiDumpedTextureCount), true);
		getIMGF()->getIMGEditor()->logWithNoTabsOpen(LocalizationManager::get()->getTranslatedText("Log_15"), true);
		getIMGF()->getIMGEditor()->logWithNoTabsOpen(String2::join(vecCorruptTXDs, "\n"), true);
		getIMGF()->getIMGEditor()->logWithNoTabsOpen(LocalizationManager::get()->getTranslatedText("Log_16"), true);
		getIMGF()->getIMGEditor()->logWithNoTabsOpen(String2::join(vecTooLargeTXDs, "\n"), true);
		getIMGF()->getIMGEditor()->logWithNoTabsOpen(LocalizationManager::get()->getTranslatedText("Log_17"), true);
		getIMGF()->getIMGEditor()->logWithNoTabsOpen(String2::join(vecTXDsContainingTooManyTextures, "\n"), true);
		getIMGF()->getIMGEditor()->logWithNoTabsOpen(LocalizationManager::get()->getTranslatedText("Log_18"), true);
		getIMGF()->getIMGEditor()->logWithNoTabsOpen(String2::join(vecInvalidResolutionTXDs, "\n"), true);
		getIMGF()->getIMGEditor()->logWithNoTabsOpen(LocalizationManager::get()->getTranslatedText("Log_19"), true);
		getIMGF()->getIMGEditor()->logWithNoTabsOpen(String2::join(vecInvalidTextureNames, "\n"), true);
		getIMGF()->getIMGEditor()->logWithNoTabsOpen(LocalizationManager::get()->getTranslatedText("Log_20"), true);
		getIMGF()->getIMGEditor()->logWithNoTabsOpen(String2::join(vecDumpedEntryNames, "\n"), true);
		getIMGF()->getIMGEditor()->logWithNoTabsOpen(LocalizationManager::get()->getTranslatedText("Log_21"), true);
		getIMGF()->getIMGEditor()->logWithNoTabsOpen(String2::join(vecTextureNames, "\n"), true);
		getIMGF()->getIMGEditor()->logWithNoTabsOpen(LocalizationManager::get()->getTranslatedText("Log_22"), true);
		getIMGF()->getIMGEditor()->logWithNoTabsOpen(String2::join(vecMipmapSkippedEntries, "\n"), true);
	}

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
		Input::showMessage(LocalizationManager::get()->getTranslatedText("TextPopup_1"), LocalizationManager::get()->getTranslatedText("TextPopupTitle_1"));
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
			string strFilePath = getIMGF()->getSettingsManager()->getSettingString("AutomaticLoggingPath") + String2::getDateTextForFolder() + " / " + LocalizationManager::get()->getTranslatedText("LogFilename_Extended");

			if (getIMGF()->getSettingsManager()->getSettingBool("AutomaticLoggingExtended") && File::doesFileExist(strFilePath))
			{
				// automatic logging is enabled, simply open the txt file for the user
				ShellExecute(NULL, NULL, String2::convertStdStringToStdWString(strFilePath).c_str(), NULL, NULL, SW_SHOWNORMAL);
			}
			else
			{
				// ask user to save the extended log file, then open the txt file
				getIMGF()->getTaskManager()->onPauseTask();
				string strSaveFilePath = getIMGF()->getTaskManager()->getDispatch()->onRequestSaveLog(true, false);
				getIMGF()->getTaskManager()->onResumeTask();
				if (strSaveFilePath != "")
				{
					ShellExecute(NULL, NULL, String2::convertStdStringToStdWString(strSaveFilePath).c_str(), NULL, NULL, SW_SHOWNORMAL);
				}
			}
		}

		delete pDumpResultsDialogData;
	}

	// clean up
	if (pDumpDialogData->m_uiDumpType == 2 || pDumpDialogData->m_uiDumpType == 3)
	{
		for (auto pIMGFile : vecIMGFormats)
		{
			pIMGFile->unload();
			delete pIMGFile;
		}
	}

	delete pDumpDialogData;
}

string			DumpManager::getEncoderClassIdFromImageExtension(string strFileExtension)
{
	strFileExtension = String2::toUpperCase(strFileExtension);
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