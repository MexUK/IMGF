#pragma warning(disable : 4005)

#include "CLSTProcessingManager.h"
#include "CIMGF.h"
#include "Globals.h"
#include "LST/CLSTFormat.h"
#include "LST/CLSTSection.h"
#include "LST/CLSTEntry.h"
#include "Type/String/CString2.h"
#include "File/CFileManager.h"
#include "Path/CPathManager.h"
#include "Task/CTaskManager.h"
#include "Task/CTaskDispatchManager.h"
#include "GUI/Editors/CIMGEditor.h"
#include "GUI/Editors/Tab/CIMGEditorTab.h"
#include "Format/RockstarGames/COL/CCOLManager.h"
#include "Format/RockstarGames/COL/CCOLFormat.h"
#include "Format/RockstarGames/COL/CCOLEntry.h"
#include "GUI/CGUIManager.h"
#include "Sort/CSortManager.h"
#include "Format/RockstarGames/IMG/CIMGEntry.h"
#include "Localization/CLocalizationManager.h"

using namespace std;
using namespace mcore;

void		CLSTProcessingManager::init(void)
{
}
void		CLSTProcessingManager::uninit(void)
{
}

void		CLSTProcessingManager::process(CLSTFormat *pLSTFile)
{
	string strGTARootFolderPath;
	if (pLSTFile->doesEntryExistByName("gtaroot"))
	{
		if (pLSTFile->getEntryByName("gtaroot")->getEntryCount() > 0)
		{
			strGTARootFolderPath = pLSTFile->getEntryByName("gtaroot")->getEntryByIndex(0)->getLine();
		}
	}
	if (strGTARootFolderPath == "")
	{
		strGTARootFolderPath = mcore::CGUIManager::chooseFolderDialog(CLocalizationManager::getInstance()->getTranslatedText("ChooseFolderPopup_3"), getIMGF()->getLastUsedDirectory("LST_GAME"));
		if (strGTARootFolderPath == "")
		{
			mcore::CGUIManager::showMessage(CLocalizationManager::getInstance()->getTranslatedText("TextPopup_60"), CLocalizationManager::getInstance()->getTranslatedText("TextPopupTitle_60"), MB_OK);
			return;
		}
		strGTARootFolderPath = CPathManager::addSlashToEnd(strGTARootFolderPath);
		getIMGF()->setLastUsedDirectory("LST_GAME", strGTARootFolderPath);
	}
	strGTARootFolderPath = CPathManager::addSlashToEnd(strGTARootFolderPath);

	//string strWorkingPath = strGTARootFolderPath;
	//string strWorkingPath = CPathManager::addSlashToEnd(pLSTFile->getSectionByName("Start")->getEntryByName("updatearchive")->getValue(0));

	if (pLSTFile->doesEntryExistByName("cdimages"))
	{
		if (!pLSTFile->getEntryByName("cdimages")->doesEntryExistByName("gamepath"))
		{
			mcore::CGUIManager::showMessage(CLocalizationManager::getInstance()->getTranslatedFormattedText("LSTEntryMissing", "gamepath", "cdimages"), CLocalizationManager::getInstance()->getTranslatedText("TextPopupTitle_LSTFileError"), MB_OK);
			return;
		}

		string strIMGPath = strGTARootFolderPath + pLSTFile->getEntryByName("cdimages")->getEntryByName("gamepath")->getValuesLine();
		if (!CFileManager::doesFileExist(strIMGPath))
		{
			mcore::CGUIManager::showMessage(CLocalizationManager::getInstance()->getTranslatedFormattedText("TextPopup_27", strIMGPath.c_str()), CLocalizationManager::getInstance()->getTranslatedText("TextPopupTitle_LSTFileError"), MB_OK);
			return;
		}
		getIMGF()->getTaskManager()->getDispatch()->onRequestOpen2(strIMGPath);

		string strSourceFolderPath = "";
		if (!pLSTFile->getEntryByName("cdimages")->doesEntryExistByName("source"))
		{
			strSourceFolderPath = CPathManager::removeSlashFromFront(CPathManager::addSlashToEnd(pLSTFile->getEntryByName("cdimages")->getEntryByName("source")->getValuesLine()));
		}

		for (auto pLSTFileEntry : pLSTFile->getEntryByName("cdimages")->getEntries())
		{
			string strCommandUpper = CString2::toUpperCase(pLSTFileEntry->getName());
			if (strCommandUpper == "ADD")
			{
				if (strSourceFolderPath == "")
				{
					mcore::CGUIManager::showMessage(CLocalizationManager::getInstance()->getTranslatedFormattedText("LSTEntryMissing", "source", "cdimages"), CLocalizationManager::getInstance()->getTranslatedText("TextPopupTitle_LSTFileError"), MB_OK);
					return;
				}

				string strEntryFileName = CPathManager::getFileName(pLSTFileEntry->getValuesLine());
				string strEntryPath = strGTARootFolderPath + strSourceFolderPath + strEntryFileName;
				if (CFileManager::doesFileExist(strEntryPath))
				{
					getIMGF()->getEntryListTab()->addOrReplaceEntryViaFileAndSettings(strEntryPath);
					getIMGF()->getEntryListTab()->log(CLocalizationManager::getInstance()->getTranslatedFormattedText("Log_30", strEntryFileName.c_str()));
				}
				else
				{
					getIMGF()->getEntryListTab()->log(CLocalizationManager::getInstance()->getTranslatedFormattedText("Log_31", strEntryFileName.c_str()));
					getIMGF()->getEntryListTab()->log(CLocalizationManager::getInstance()->getTranslatedFormattedText("Log_32", strEntryPath.c_str()), true);
				}
			}
			else if (strCommandUpper == "DEL")
			{
				string strEntryFileName = CPathManager::getFileName(pLSTFileEntry->getValuesLine());
				CIMGEntry *pIMGEntry = getIMGF()->getEntryListTab()->getEntryByName(strEntryFileName);
				if (pIMGEntry == nullptr)
				{
					getIMGF()->getEntryListTab()->log(CLocalizationManager::getInstance()->getTranslatedFormattedText("Log_33", strEntryFileName.c_str()));
				}
				else
				{
					getIMGF()->getEntryListTab()->removeEntry(pIMGEntry);
					getIMGF()->getEntryListTab()->log(CLocalizationManager::getInstance()->getTranslatedFormattedText("Log_34", strEntryFileName.c_str()));
				}
			}
			else if (strCommandUpper == "RESORT")
			{
				getIMGF()->getSortManager()->sort(getIMGF()->getEntryListTab()->getIMGFile());
				getIMGF()->getEntryListTab()->log(CLocalizationManager::getInstance()->getTranslatedText("Log_35"));
			}
			else if (strCommandUpper == "REBUILD")
			{
				getIMGF()->getEntryListTab()->rebuild();
				getIMGF()->getIMGEditor()->refreshActiveTab();
				getIMGF()->getEntryListTab()->log(CLocalizationManager::getInstance()->getTranslatedText("Log_36"));
			}
		}

	}

	if (pLSTFile->doesEntryExistByName("collisions"))
	{
		if (!pLSTFile->getEntryByName("collisions")->doesEntryExistByName("gamepath"))
		{
			mcore::CGUIManager::showMessage(CLocalizationManager::getInstance()->getTranslatedFormattedText("LSTEntryMissing", "gamepath", "collisions"), CLocalizationManager::getInstance()->getTranslatedText("TextPopupTitle_LSTFileError"), MB_OK);
			return;
		}

		string strCOLPath = strGTARootFolderPath + pLSTFile->getEntryByName("collisions")->getEntryByName("gamepath")->getValuesLine();
		if (!CFileManager::doesFileExist(strCOLPath))
		{
			mcore::CGUIManager::showMessage(CLocalizationManager::getInstance()->getTranslatedFormattedText("TextPopup_29", strCOLPath.c_str()), CLocalizationManager::getInstance()->getTranslatedText("TextPopupTitle_LSTFileError"), MB_OK);
			return;
		}
		CCOLFormat *pCOLFile = CCOLManager::getInstance()->parseViaFile(strCOLPath);
		if(!pCOLFile->doesHaveError())
		{
			string strSourceFolderPath = "";
			if (!pLSTFile->getEntryByName("collisions")->doesEntryExistByName("source"))
			{
				strSourceFolderPath = CPathManager::removeSlashFromFront(CPathManager::addSlashToEnd(pLSTFile->getEntryByName("collisions")->getEntryByName("source")->getValuesLine()));
			}

			for (auto pLSTFileEntry : pLSTFile->getEntryByName("collisions")->getEntries())
			{
				string strCommandUpper = CString2::toUpperCase(pLSTFileEntry->getName());
				if (strCommandUpper == "RENAME")
				{
					string strCOLOldFileName = CPathManager::removeFileExtension(CPathManager::getFileName(pLSTFileEntry->getValue(0)));
					string strCOLNewFileName = CPathManager::removeFileExtension(CPathManager::getFileName(pLSTFileEntry->getValue(1)));
					CCOLEntry *pCOLEntry = pCOLFile->getEntryByName(strCOLOldFileName);
					if (pCOLEntry == nullptr)
					{
						getIMGF()->getEntryListTab()->log(CLocalizationManager::getInstance()->getTranslatedFormattedText("Log_37", strCOLOldFileName.c_str()));
					}
					else
					{
						pCOLEntry->setModelName(strCOLNewFileName);
						getIMGF()->getEntryListTab()->log(CLocalizationManager::getInstance()->getTranslatedFormattedText("Log_38", strCOLOldFileName.c_str(), strCOLNewFileName.c_str()));
					}
				}
				else if (strCommandUpper == "ADD")
				{
					if (strSourceFolderPath == "")
					{
						mcore::CGUIManager::showMessage(CLocalizationManager::getInstance()->getTranslatedFormattedText("LSTEntryMissing", "source", "collisions"), CLocalizationManager::getInstance()->getTranslatedText("TextPopupTitle_LSTFileError"), MB_OK);
						return;
					}

					string strEntryFileName = CPathManager::getFileName(pLSTFileEntry->getValuesLine());
					string strEntryPath = strGTARootFolderPath + strSourceFolderPath + strEntryFileName;

					if (CFileManager::doesFileExist(strEntryPath))
					{
						getIMGF()->getEntryListTab()->addOrReplaceEntryViaFileAndSettings(strEntryPath);
						getIMGF()->getEntryListTab()->log(CLocalizationManager::getInstance()->getTranslatedFormattedText("Log_39", strEntryFileName.c_str()));
					}
					else
					{
						getIMGF()->getEntryListTab()->log(CLocalizationManager::getInstance()->getTranslatedFormattedText("Log_40", strEntryFileName.c_str()));
						getIMGF()->getEntryListTab()->log(CLocalizationManager::getInstance()->getTranslatedFormattedText("Log_41", strEntryPath.c_str()), true);
					}
				}
				else if (strCommandUpper == "DEL")
				{
					string strEntryFileName = CPathManager::getFileName(pLSTFileEntry->getValuesLine());
					CCOLEntry *pCOLEntry = pCOLFile->getEntryByName(strEntryFileName);
					if (pCOLEntry == nullptr)
					{
						getIMGF()->getEntryListTab()->log(CLocalizationManager::getInstance()->getTranslatedFormattedText("Log_42", strEntryFileName.c_str()));
					}
					else
					{
						string strEntryActualFileName = pCOLEntry->getModelName();
						pCOLFile->removeEntry(pCOLEntry);
						getIMGF()->getEntryListTab()->log("Removed COL entry: " + strEntryActualFileName);
					}
				}
				else if (strCommandUpper == "RESORT")
				{
					pCOLFile->sort();
					getIMGF()->getEntryListTab()->log(CLocalizationManager::getInstance()->getTranslatedText("Log_43"));
				}
			}
			pCOLFile->serializeViaFile();
			pCOLFile->unload();
		}
		pCOLFile->unload();
		delete pCOLFile;
	}

	string
		strSourceFolderPath = "",
		strGamePathFolderPath = "";
	if (pLSTFile->doesEntryExistByName("other"))
	{
		for (auto pLSTFileEntry : pLSTFile->getEntryByName("other")->getEntries())
		{
			string strCommandUpper = CString2::toUpperCase(pLSTFileEntry->getName());
			if (strCommandUpper == "SOURCE")
			{
				strSourceFolderPath = CPathManager::removeSlashFromFront(CPathManager::addSlashToEnd(pLSTFileEntry->getValuesLine()));
			}
			else if (strCommandUpper == "GAMEPATH")
			{
				strGamePathFolderPath = CPathManager::removeSlashFromFront(CPathManager::addSlashToEnd(pLSTFileEntry->getValuesLine()));
			}
			else if (strCommandUpper == "COPY")
			{
				if (strSourceFolderPath == "")
				{
					mcore::CGUIManager::showMessage(CLocalizationManager::getInstance()->getTranslatedFormattedText("LSTEntryMissing", "source", "other"), CLocalizationManager::getInstance()->getTranslatedText("TextPopupTitle_LSTFileError"), MB_OK);
					return;
				}

				if (strGamePathFolderPath == "")
				{
					mcore::CGUIManager::showMessage(CLocalizationManager::getInstance()->getTranslatedFormattedText("LSTEntryMissing", "gamepath", "other"), CLocalizationManager::getInstance()->getTranslatedText("TextPopupTitle_LSTFileError"), MB_OK);
					return;
				}

				string strFileName = CPathManager::getFileName(CPathManager::removeSlashFromEnd(pLSTFileEntry->getValuesLine()));
				if (strFileName == "*")
				{
					string strCopySourceFolder = strGTARootFolderPath + strSourceFolderPath + CPathManager::removeSlashFromFront(CPathManager::getDirectory(pLSTFileEntry->getValuesLine()));
					for (auto strFileName : CFileManager::getFileNames(strCopySourceFolder))
					{
						string strCopySourcePath = strGTARootFolderPath + strSourceFolderPath + strFileName;
						string strCopyDestinationPath = strGTARootFolderPath + strGamePathFolderPath + strFileName;
						CFileManager::copyFile(strCopySourcePath, strCopyDestinationPath);
					}
					getIMGF()->getEntryListTab()->log(CLocalizationManager::getInstance()->getTranslatedText("Log_LSTCopy1"));
					getIMGF()->getEntryListTab()->log(CLocalizationManager::getInstance()->getTranslatedFormattedText("Log_LSTCopy2", strCopySourceFolder.c_str(), (strGTARootFolderPath + strGamePathFolderPath).c_str()), true);
				}
				else
				{
					string strFileName = CPathManager::removeSlashFromFront(pLSTFileEntry->getValuesLine());
					string strCopySourcePath = strGTARootFolderPath + strSourceFolderPath + strFileName;
					string strCopyDestinationPath = strGTARootFolderPath + strGamePathFolderPath + strFileName;
					CFileManager::copyFile(strCopySourcePath, strCopyDestinationPath);
					getIMGF()->getEntryListTab()->log(CLocalizationManager::getInstance()->getTranslatedFormattedText("Log_LSTCopy3", strFileName.c_str()));
					getIMGF()->getEntryListTab()->log(CLocalizationManager::getInstance()->getTranslatedFormattedText("Log_LSTCopy4", strFileName.c_str(), strCopySourcePath.c_str(), strCopyDestinationPath.c_str()), true);
				}
			}
			else if (strCommandUpper == "DEL" || strCommandUpper == "DELETE")
			{
				if (strSourceFolderPath == "")
				{
					mcore::CGUIManager::showMessage(CLocalizationManager::getInstance()->getTranslatedFormattedText("LSTEntryMissing", "source", "other"), CLocalizationManager::getInstance()->getTranslatedText("TextPopupTitle_LSTFileError"), MB_OK);
					return;
				}

				if (strGamePathFolderPath == "")
				{
					mcore::CGUIManager::showMessage(CLocalizationManager::getInstance()->getTranslatedFormattedText("LSTEntryMissing", "gamepath", "other"), CLocalizationManager::getInstance()->getTranslatedText("TextPopupTitle_LSTFileError"), MB_OK);
					return;
				}

				string strFileName = CPathManager::getFileName(CPathManager::removeSlashFromEnd(pLSTFileEntry->getValuesLine()));
				if (strFileName == "*")
				{
					string strFolderPath = strGTARootFolderPath + strGamePathFolderPath + CPathManager::removeSlashFromFront(CPathManager::getDirectory(pLSTFileEntry->getValuesLine()));
					for (auto strFileName : CFileManager::getFileNames(strFolderPath))
					{
						string strFilePath = strFolderPath + strFileName;
						CFileManager::removeFile(strFilePath);
					}
					getIMGF()->getEntryListTab()->log(CLocalizationManager::getInstance()->getTranslatedText("Log_LSTDelete1"));
					getIMGF()->getEntryListTab()->log(CLocalizationManager::getInstance()->getTranslatedFormattedText("Log_LSTDelete2", strFolderPath.c_str()), true);
				}
				else
				{
					string strFileName = CPathManager::removeSlashFromFront(pLSTFileEntry->getValuesLine());
					string strFilePath = strGTARootFolderPath + strGamePathFolderPath + strFileName;
					CFileManager::removeFile(strFilePath);

					getIMGF()->getEntryListTab()->log(CLocalizationManager::getInstance()->getTranslatedFormattedText("Log_LSTDelete3", strFileName.c_str()));
					getIMGF()->getEntryListTab()->log(CLocalizationManager::getInstance()->getTranslatedFormattedText("Log_LSTDelete4", strFilePath.c_str()), true);
				}
			}
		}
	}
	
	pLSTFile->unload();
	delete pLSTFile;
}