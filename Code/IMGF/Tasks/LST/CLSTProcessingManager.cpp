#pragma warning(disable : 4005)

#include "CLSTProcessingManager.h"
#include "CIMGF.h"
#include "Globals.h"
#include "LST/CLSTFormat.h"
#include "LST/CLSTSection.h"
#include "LST/CLSTEntry.h"
#include "Static/CString2.h"
#include "Static/CFile.h"
#include "Static/CPath.h"
#include "Task/CTaskManager.h"
#include "Task/CTaskDispatchManager.h"
#include "GUI/Editors/CIMGEditor.h"
#include "GUI/Editors/Tab/CIMGEditorTab.h"
#include "Format/COL/CCOLManager.h"
#include "Format/COL/CCOLFormat.h"
#include "Format/COL/CCOLEntry.h"
#include "Static/CInput.h"
#include "Tasks/Sort/CSortManager.h"
#include "Format/IMG/Regular/CIMGEntry.h"
#include "Localization/CLocalizationManager.h"

using namespace std;
using namespace bxcf;
using namespace bxgi;
using namespace imgf;

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
		strGTARootFolderPath = CInput::chooseFolderDialog(CLocalizationManager::get()->getTranslatedText("ChooseFolderPopup_3"), getIMGF()->getLastUsedDirectory("LST_GAME"));
		if (strGTARootFolderPath == "")
		{
			CInput::showMessage(CLocalizationManager::get()->getTranslatedText("TextPopup_60"), CLocalizationManager::get()->getTranslatedText("TextPopupTitle_60"), MB_OK);
			return;
		}
		strGTARootFolderPath = CPath::addSlashToEnd(strGTARootFolderPath);
		getIMGF()->setLastUsedDirectory("LST_GAME", strGTARootFolderPath);
	}
	strGTARootFolderPath = CPath::addSlashToEnd(strGTARootFolderPath);

	//string strWorkingPath = strGTARootFolderPath;
	//string strWorkingPath = CPath::addSlashToEnd(pLSTFile->getSectionByName("Start")->getEntryByName("updatearchive")->getValue(0));

	if (pLSTFile->doesEntryExistByName("cdimages"))
	{
		if (!pLSTFile->getEntryByName("cdimages")->doesEntryExistByName("gamepath"))
		{
			CInput::showMessage(CLocalizationManager::get()->getTranslatedFormattedText("LSTEntryMissing", "gamepath", "cdimages"), CLocalizationManager::get()->getTranslatedText("TextPopupTitle_LSTFileError"), MB_OK);
			return;
		}

		string strIMGPath = strGTARootFolderPath + pLSTFile->getEntryByName("cdimages")->getEntryByName("gamepath")->getValuesLine();
		if (!CFile::doesFileExist(strIMGPath))
		{
			CInput::showMessage(CLocalizationManager::get()->getTranslatedFormattedText("TextPopup_27", strIMGPath.c_str()), CLocalizationManager::get()->getTranslatedText("TextPopupTitle_LSTFileError"), MB_OK);
			return;
		}
		getIMGF()->getTaskManager()->getDispatch()->_openFile(strIMGPath);

		string strSourceFolderPath = "";
		if (!pLSTFile->getEntryByName("cdimages")->doesEntryExistByName("source"))
		{
			strSourceFolderPath = CPath::removeSlashFromFront(CPath::addSlashToEnd(pLSTFile->getEntryByName("cdimages")->getEntryByName("source")->getValuesLine()));
		}

		for (auto pLSTFileEntry : pLSTFile->getEntryByName("cdimages")->getEntries())
		{
			string strCommandUpper = CString2::toUpperCase(pLSTFileEntry->getName());
			if (strCommandUpper == "ADD")
			{
				if (strSourceFolderPath == "")
				{
					CInput::showMessage(CLocalizationManager::get()->getTranslatedFormattedText("LSTEntryMissing", "source", "cdimages"), CLocalizationManager::get()->getTranslatedText("TextPopupTitle_LSTFileError"), MB_OK);
					return;
				}

				string strEntryFileName = CPath::getFileName(pLSTFileEntry->getValuesLine());
				string strEntryPath = strGTARootFolderPath + strSourceFolderPath + strEntryFileName;
				if (CFile::doesFileExist(strEntryPath))
				{
					getIMGF()->getEntryListTab()->addOrReplaceEntryViaFileAndSettings(strEntryPath);
					getIMGF()->getEntryListTab()->log(CLocalizationManager::get()->getTranslatedFormattedText("Log_30", strEntryFileName.c_str()));
				}
				else
				{
					getIMGF()->getEntryListTab()->log(CLocalizationManager::get()->getTranslatedFormattedText("Log_31", strEntryFileName.c_str()));
					getIMGF()->getEntryListTab()->log(CLocalizationManager::get()->getTranslatedFormattedText("Log_32", strEntryPath.c_str()), true);
				}
			}
			else if (strCommandUpper == "DEL")
			{
				string strEntryFileName = CPath::getFileName(pLSTFileEntry->getValuesLine());
				CIMGEntry *pIMGEntry = getIMGF()->getEntryListTab()->getEntryByName(strEntryFileName);
				if (pIMGEntry == nullptr)
				{
					getIMGF()->getEntryListTab()->log(CLocalizationManager::get()->getTranslatedFormattedText("Log_33", strEntryFileName.c_str()));
				}
				else
				{
					getIMGF()->getEntryListTab()->removeEntry(pIMGEntry);
					getIMGF()->getEntryListTab()->log(CLocalizationManager::get()->getTranslatedFormattedText("Log_34", strEntryFileName.c_str()));
				}
			}
			else if (strCommandUpper == "RESORT")
			{
				getIMGF()->getSortManager()->sort(getIMGF()->getEntryListTab()->getIMGFile());
				getIMGF()->getEntryListTab()->log(CLocalizationManager::get()->getTranslatedText("Log_35"));
			}
			else if (strCommandUpper == "REBUILD")
			{
				getIMGF()->getEntryListTab()->rebuild();
				getIMGF()->getIMGEditor()->refreshActiveTab();
				getIMGF()->getEntryListTab()->log(CLocalizationManager::get()->getTranslatedText("Log_36"));
			}
		}

	}

	if (pLSTFile->doesEntryExistByName("collisions"))
	{
		if (!pLSTFile->getEntryByName("collisions")->doesEntryExistByName("gamepath"))
		{
			CInput::showMessage(CLocalizationManager::get()->getTranslatedFormattedText("LSTEntryMissing", "gamepath", "collisions"), CLocalizationManager::get()->getTranslatedText("TextPopupTitle_LSTFileError"), MB_OK);
			return;
		}

		string strCOLPath = strGTARootFolderPath + pLSTFile->getEntryByName("collisions")->getEntryByName("gamepath")->getValuesLine();
		if (!CFile::doesFileExist(strCOLPath))
		{
			CInput::showMessage(CLocalizationManager::get()->getTranslatedFormattedText("TextPopup_29", strCOLPath.c_str()), CLocalizationManager::get()->getTranslatedText("TextPopupTitle_LSTFileError"), MB_OK);
			return;
		}
		CCOLFormat *pCOLFile = CCOLManager::get()->parseViaFile(strCOLPath);
		if(!pCOLFile->doesHaveError())
		{
			string strSourceFolderPath = "";
			if (!pLSTFile->getEntryByName("collisions")->doesEntryExistByName("source"))
			{
				strSourceFolderPath = CPath::removeSlashFromFront(CPath::addSlashToEnd(pLSTFile->getEntryByName("collisions")->getEntryByName("source")->getValuesLine()));
			}

			for (auto pLSTFileEntry : pLSTFile->getEntryByName("collisions")->getEntries())
			{
				string strCommandUpper = CString2::toUpperCase(pLSTFileEntry->getName());
				if (strCommandUpper == "RENAME")
				{
					string strCOLOldFileName = CPath::removeFileExtension(CPath::getFileName(pLSTFileEntry->getValue(0)));
					string strCOLNewFileName = CPath::removeFileExtension(CPath::getFileName(pLSTFileEntry->getValue(1)));
					CCOLEntry *pCOLEntry = pCOLFile->getEntryByName(strCOLOldFileName);
					if (pCOLEntry == nullptr)
					{
						getIMGF()->getEntryListTab()->log(CLocalizationManager::get()->getTranslatedFormattedText("Log_37", strCOLOldFileName.c_str()));
					}
					else
					{
						pCOLEntry->setModelName(strCOLNewFileName);
						getIMGF()->getEntryListTab()->log(CLocalizationManager::get()->getTranslatedFormattedText("Log_38", strCOLOldFileName.c_str(), strCOLNewFileName.c_str()));
					}
				}
				else if (strCommandUpper == "ADD")
				{
					if (strSourceFolderPath == "")
					{
						CInput::showMessage(CLocalizationManager::get()->getTranslatedFormattedText("LSTEntryMissing", "source", "collisions"), CLocalizationManager::get()->getTranslatedText("TextPopupTitle_LSTFileError"), MB_OK);
						return;
					}

					string strEntryFileName = CPath::getFileName(pLSTFileEntry->getValuesLine());
					string strEntryPath = strGTARootFolderPath + strSourceFolderPath + strEntryFileName;

					if (CFile::doesFileExist(strEntryPath))
					{
						getIMGF()->getEntryListTab()->addOrReplaceEntryViaFileAndSettings(strEntryPath);
						getIMGF()->getEntryListTab()->log(CLocalizationManager::get()->getTranslatedFormattedText("Log_39", strEntryFileName.c_str()));
					}
					else
					{
						getIMGF()->getEntryListTab()->log(CLocalizationManager::get()->getTranslatedFormattedText("Log_40", strEntryFileName.c_str()));
						getIMGF()->getEntryListTab()->log(CLocalizationManager::get()->getTranslatedFormattedText("Log_41", strEntryPath.c_str()), true);
					}
				}
				else if (strCommandUpper == "DEL")
				{
					string strEntryFileName = CPath::getFileName(pLSTFileEntry->getValuesLine());
					CCOLEntry *pCOLEntry = pCOLFile->getEntryByName(strEntryFileName);
					if (pCOLEntry == nullptr)
					{
						getIMGF()->getEntryListTab()->log(CLocalizationManager::get()->getTranslatedFormattedText("Log_42", strEntryFileName.c_str()));
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
					getIMGF()->getEntryListTab()->log(CLocalizationManager::get()->getTranslatedText("Log_43"));
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
				strSourceFolderPath = CPath::removeSlashFromFront(CPath::addSlashToEnd(pLSTFileEntry->getValuesLine()));
			}
			else if (strCommandUpper == "GAMEPATH")
			{
				strGamePathFolderPath = CPath::removeSlashFromFront(CPath::addSlashToEnd(pLSTFileEntry->getValuesLine()));
			}
			else if (strCommandUpper == "COPY")
			{
				if (strSourceFolderPath == "")
				{
					CInput::showMessage(CLocalizationManager::get()->getTranslatedFormattedText("LSTEntryMissing", "source", "other"), CLocalizationManager::get()->getTranslatedText("TextPopupTitle_LSTFileError"), MB_OK);
					return;
				}

				if (strGamePathFolderPath == "")
				{
					CInput::showMessage(CLocalizationManager::get()->getTranslatedFormattedText("LSTEntryMissing", "gamepath", "other"), CLocalizationManager::get()->getTranslatedText("TextPopupTitle_LSTFileError"), MB_OK);
					return;
				}

				string strFileName = CPath::getFileName(CPath::removeSlashFromEnd(pLSTFileEntry->getValuesLine()));
				if (strFileName == "*")
				{
					string strCopySourceFolder = strGTARootFolderPath + strSourceFolderPath + CPath::removeSlashFromFront(CPath::getDirectory(pLSTFileEntry->getValuesLine()));
					for (auto strFileName : CFile::getFileNames(strCopySourceFolder))
					{
						string strCopySourcePath = strGTARootFolderPath + strSourceFolderPath + strFileName;
						string strCopyDestinationPath = strGTARootFolderPath + strGamePathFolderPath + strFileName;
						CFile::copyFile(strCopySourcePath, strCopyDestinationPath);
					}
					getIMGF()->getEntryListTab()->log(CLocalizationManager::get()->getTranslatedText("Log_LSTCopy1"));
					getIMGF()->getEntryListTab()->log(CLocalizationManager::get()->getTranslatedFormattedText("Log_LSTCopy2", strCopySourceFolder.c_str(), (strGTARootFolderPath + strGamePathFolderPath).c_str()), true);
				}
				else
				{
					string strFileName = CPath::removeSlashFromFront(pLSTFileEntry->getValuesLine());
					string strCopySourcePath = strGTARootFolderPath + strSourceFolderPath + strFileName;
					string strCopyDestinationPath = strGTARootFolderPath + strGamePathFolderPath + strFileName;
					CFile::copyFile(strCopySourcePath, strCopyDestinationPath);
					getIMGF()->getEntryListTab()->log(CLocalizationManager::get()->getTranslatedFormattedText("Log_LSTCopy3", strFileName.c_str()));
					getIMGF()->getEntryListTab()->log(CLocalizationManager::get()->getTranslatedFormattedText("Log_LSTCopy4", strFileName.c_str(), strCopySourcePath.c_str(), strCopyDestinationPath.c_str()), true);
				}
			}
			else if (strCommandUpper == "DEL" || strCommandUpper == "DELETE")
			{
				if (strSourceFolderPath == "")
				{
					CInput::showMessage(CLocalizationManager::get()->getTranslatedFormattedText("LSTEntryMissing", "source", "other"), CLocalizationManager::get()->getTranslatedText("TextPopupTitle_LSTFileError"), MB_OK);
					return;
				}

				if (strGamePathFolderPath == "")
				{
					CInput::showMessage(CLocalizationManager::get()->getTranslatedFormattedText("LSTEntryMissing", "gamepath", "other"), CLocalizationManager::get()->getTranslatedText("TextPopupTitle_LSTFileError"), MB_OK);
					return;
				}

				string strFileName = CPath::getFileName(CPath::removeSlashFromEnd(pLSTFileEntry->getValuesLine()));
				if (strFileName == "*")
				{
					string strFolderPath = strGTARootFolderPath + strGamePathFolderPath + CPath::removeSlashFromFront(CPath::getDirectory(pLSTFileEntry->getValuesLine()));
					for (auto strFileName : CFile::getFileNames(strFolderPath))
					{
						string strFilePath = strFolderPath + strFileName;
						CFile::removeFile(strFilePath);
					}
					getIMGF()->getEntryListTab()->log(CLocalizationManager::get()->getTranslatedText("Log_LSTDelete1"));
					getIMGF()->getEntryListTab()->log(CLocalizationManager::get()->getTranslatedFormattedText("Log_LSTDelete2", strFolderPath.c_str()), true);
				}
				else
				{
					string strFileName = CPath::removeSlashFromFront(pLSTFileEntry->getValuesLine());
					string strFilePath = strGTARootFolderPath + strGamePathFolderPath + strFileName;
					CFile::removeFile(strFilePath);

					getIMGF()->getEntryListTab()->log(CLocalizationManager::get()->getTranslatedFormattedText("Log_LSTDelete3", strFileName.c_str()));
					getIMGF()->getEntryListTab()->log(CLocalizationManager::get()->getTranslatedFormattedText("Log_LSTDelete4", strFilePath.c_str()), true);
				}
			}
		}
	}
	
	pLSTFile->unload();
	delete pLSTFile;
}