#pragma warning(disable : 4005)

#include "LSTProcessingManager.h"
#include "IMGF.h"
#include "Globals.h"
#include "LST/LSTFormat.h"
#include "LST/LSTSection.h"
#include "LST/LSTEntry.h"
#include "Static/String.h"
#include "Static/File.h"
#include "Static/Path.h"
#include "Task/TaskManager.h"
#include "Task/Tasks/Tasks.h"
#include "GUI/Editor/Editors/IMGEditor.h"
#include "GUI/Editor/Tabs/IMGEditorTab.h"
#include "Format/COL/COLManager.h"
#include "Format/COL/COLFormat.h"
#include "Format/COL/COLEntry.h"
#include "Static/Input.h"
#include "Task/Tasks/Sort/SortManager.h"
#include "Format/IMG/Regular/IMGEntry.h"
#include "Localization/LocalizationManager.h"

using namespace std;
using namespace bxcf;
using namespace bxgi;
using namespace imgf;

void		LSTProcessingManager::init(void)
{
}
void		LSTProcessingManager::uninit(void)
{
}

void		LSTProcessingManager::process(LSTFormat *pLSTFile)
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
		strGTARootFolderPath = Input::openFolder(LocalizationManager::get()->getTranslatedText("ChooseFolderPopup_3"), getIMGF()->getLastUsedDirectory("LST_GAME"));
		if (strGTARootFolderPath == "")
		{
			Tasks::showMessage(LocalizationManager::get()->getTranslatedText("TextPopup_60"), LocalizationManager::get()->getTranslatedText("TextPopupTitle_60"), MB_OK);
			return;
		}
		strGTARootFolderPath = Path::addSlashToEnd(strGTARootFolderPath);
		getIMGF()->setLastUsedDirectory("LST_GAME", strGTARootFolderPath);
	}
	strGTARootFolderPath = Path::addSlashToEnd(strGTARootFolderPath);

	//string strWorkingPath = strGTARootFolderPath;
	//string strWorkingPath = Path::addSlashToEnd(pLSTFile->getSectionByName("Start")->getEntryByName("updatearchive")->getValue(0));

	if (pLSTFile->doesEntryExistByName("cdimages"))
	{
		if (!pLSTFile->getEntryByName("cdimages")->doesEntryExistByName("gamepath"))
		{
			Tasks::showMessage(LocalizationManager::get()->getTranslatedFormattedText("LSTEntryMissing", "gamepath", "cdimages"), LocalizationManager::get()->getTranslatedText("TextPopupTitle_LSTFileError"), MB_OK);
			return;
		}

		string strIMGPath = strGTARootFolderPath + pLSTFile->getEntryByName("cdimages")->getEntryByName("gamepath")->getValuesLine();
		if (!File::doesFileExist(strIMGPath))
		{
			Tasks::showMessage(LocalizationManager::get()->getTranslatedFormattedText("TextPopup_27", strIMGPath.c_str()), LocalizationManager::get()->getTranslatedText("TextPopupTitle_LSTFileError"), MB_OK);
			return;
		}
		getIMGF()->getTaskManager()->getDispatch()->_openFile(strIMGPath);

		string strSourceFolderPath = "";
		if (!pLSTFile->getEntryByName("cdimages")->doesEntryExistByName("source"))
		{
			strSourceFolderPath = Path::removeSlashFromFront(Path::addSlashToEnd(pLSTFile->getEntryByName("cdimages")->getEntryByName("source")->getValuesLine()));
		}

		for (auto pLSTFileEntry : pLSTFile->getEntryByName("cdimages")->getEntries())
		{
			string strCommandUpper = String::toUpperCase(pLSTFileEntry->getName());
			if (strCommandUpper == "ADD")
			{
				if (strSourceFolderPath == "")
				{
					Tasks::showMessage(LocalizationManager::get()->getTranslatedFormattedText("LSTEntryMissing", "source", "cdimages"), LocalizationManager::get()->getTranslatedText("TextPopupTitle_LSTFileError"), MB_OK);
					return;
				}

				string strEntryFileName = Path::getFileName(pLSTFileEntry->getValuesLine());
				string strEntryPath = strGTARootFolderPath + strSourceFolderPath + strEntryFileName;
				if (File::doesFileExist(strEntryPath))
				{
					getIMGF()->getEntryListTab()->addOrReplaceEntryViaFileAndSettings(strEntryPath);
					// todo - getIMGF()->getEntryListTab()->log(LocalizationManager::get()->getTranslatedFormattedText("Log_30", strEntryFileName.c_str()));
				}
				else
				{
					// todo - getIMGF()->getEntryListTab()->log(LocalizationManager::get()->getTranslatedFormattedText("Log_31", strEntryFileName.c_str()));
					// todo - getIMGF()->getEntryListTab()->log(LocalizationManager::get()->getTranslatedFormattedText("Log_32", strEntryPath.c_str()), true);
				}
			}
			else if (strCommandUpper == "DEL")
			{
				string strEntryFileName = Path::getFileName(pLSTFileEntry->getValuesLine());
				IMGEntry *pIMGEntry = getIMGF()->getEntryListTab()->getEntryByName(strEntryFileName);
				if (pIMGEntry == nullptr)
				{
					// todo - getIMGF()->getEntryListTab()->log(LocalizationManager::get()->getTranslatedFormattedText("Log_33", strEntryFileName.c_str()));
				}
				else
				{
					getIMGF()->getEntryListTab()->removeEntry(pIMGEntry);
					// todo - getIMGF()->getEntryListTab()->log(LocalizationManager::get()->getTranslatedFormattedText("Log_34", strEntryFileName.c_str()));
				}
			}
			else if (strCommandUpper == "RESORT")
			{
				getIMGF()->getSortManager()->sort(getIMGF()->getEntryListTab()->getIMGFile());
				// todo - getIMGF()->getEntryListTab()->log(LocalizationManager::get()->getTranslatedText("Log_35"));
			}
			else if (strCommandUpper == "REBUILD")
			{
				getIMGF()->getEntryListTab()->rebuild();
				getIMGF()->getIMGEditor()->refreshActiveTab();
				// todo - getIMGF()->getEntryListTab()->log(LocalizationManager::get()->getTranslatedText("Log_36"));
			}
		}

	}

	if (pLSTFile->doesEntryExistByName("collisions"))
	{
		if (!pLSTFile->getEntryByName("collisions")->doesEntryExistByName("gamepath"))
		{
			Tasks::showMessage(LocalizationManager::get()->getTranslatedFormattedText("LSTEntryMissing", "gamepath", "collisions"), LocalizationManager::get()->getTranslatedText("TextPopupTitle_LSTFileError"), MB_OK);
			return;
		}

		string strCOLPath = strGTARootFolderPath + pLSTFile->getEntryByName("collisions")->getEntryByName("gamepath")->getValuesLine();
		if (!File::doesFileExist(strCOLPath))
		{
			Tasks::showMessage(LocalizationManager::get()->getTranslatedFormattedText("TextPopup_29", strCOLPath.c_str()), LocalizationManager::get()->getTranslatedText("TextPopupTitle_LSTFileError"), MB_OK);
			return;
		}
		COLFormat *pCOLFile = COLManager::get()->unserializeFile(strCOLPath);
		if(!pCOLFile->doesHaveError())
		{
			string strSourceFolderPath = "";
			if (!pLSTFile->getEntryByName("collisions")->doesEntryExistByName("source"))
			{
				strSourceFolderPath = Path::removeSlashFromFront(Path::addSlashToEnd(pLSTFile->getEntryByName("collisions")->getEntryByName("source")->getValuesLine()));
			}

			for (auto pLSTFileEntry : pLSTFile->getEntryByName("collisions")->getEntries())
			{
				string strCommandUpper = String::toUpperCase(pLSTFileEntry->getName());
				if (strCommandUpper == "RENAME")
				{
					string strCOLOldFileName = Path::removeFileExtension(Path::getFileName(pLSTFileEntry->getValue(0)));
					string strCOLNewFileName = Path::removeFileExtension(Path::getFileName(pLSTFileEntry->getValue(1)));
					COLEntry *pCOLEntry = pCOLFile->getEntryByName(strCOLOldFileName);
					if (pCOLEntry == nullptr)
					{
						// todo - getIMGF()->getEntryListTab()->log(LocalizationManager::get()->getTranslatedFormattedText("Log_37", strCOLOldFileName.c_str()));
					}
					else
					{
						pCOLEntry->setModelName(strCOLNewFileName);
						// todo - getIMGF()->getEntryListTab()->log(LocalizationManager::get()->getTranslatedFormattedText("Log_38", strCOLOldFileName.c_str(), strCOLNewFileName.c_str()));
					}
				}
				else if (strCommandUpper == "ADD")
				{
					if (strSourceFolderPath == "")
					{
						Tasks::showMessage(LocalizationManager::get()->getTranslatedFormattedText("LSTEntryMissing", "source", "collisions"), LocalizationManager::get()->getTranslatedText("TextPopupTitle_LSTFileError"), MB_OK);
						return;
					}

					string strEntryFileName = Path::getFileName(pLSTFileEntry->getValuesLine());
					string strEntryPath = strGTARootFolderPath + strSourceFolderPath + strEntryFileName;

					if (File::doesFileExist(strEntryPath))
					{
						getIMGF()->getEntryListTab()->addOrReplaceEntryViaFileAndSettings(strEntryPath);
						// todo - getIMGF()->getEntryListTab()->log(LocalizationManager::get()->getTranslatedFormattedText("Log_39", strEntryFileName.c_str()));
					}
					else
					{
						// todo - getIMGF()->getEntryListTab()->log(LocalizationManager::get()->getTranslatedFormattedText("Log_40", strEntryFileName.c_str()));
						// todo - getIMGF()->getEntryListTab()->log(LocalizationManager::get()->getTranslatedFormattedText("Log_41", strEntryPath.c_str()), true);
					}
				}
				else if (strCommandUpper == "DEL")
				{
					string strEntryFileName = Path::getFileName(pLSTFileEntry->getValuesLine());
					COLEntry *pCOLEntry = pCOLFile->getEntryByName(strEntryFileName);
					if (pCOLEntry == nullptr)
					{
						// todo - getIMGF()->getEntryListTab()->log(LocalizationManager::get()->getTranslatedFormattedText("Log_42", strEntryFileName.c_str()));
					}
					else
					{
						string strEntryActualFileName = pCOLEntry->getModelName();
						pCOLFile->removeEntry(pCOLEntry);
						// todo - getIMGF()->getEntryListTab()->log("Removed COL entry: " + strEntryActualFileName);
					}
				}
				else if (strCommandUpper == "RESORT")
				{
					pCOLFile->sort();
					// todo - getIMGF()->getEntryListTab()->log(LocalizationManager::get()->getTranslatedText("Log_43"));
				}
			}
			pCOLFile->serialize();
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
			string strCommandUpper = String::toUpperCase(pLSTFileEntry->getName());
			if (strCommandUpper == "SOURCE")
			{
				strSourceFolderPath = Path::removeSlashFromFront(Path::addSlashToEnd(pLSTFileEntry->getValuesLine()));
			}
			else if (strCommandUpper == "GAMEPATH")
			{
				strGamePathFolderPath = Path::removeSlashFromFront(Path::addSlashToEnd(pLSTFileEntry->getValuesLine()));
			}
			else if (strCommandUpper == "COPY")
			{
				if (strSourceFolderPath == "")
				{
					Tasks::showMessage(LocalizationManager::get()->getTranslatedFormattedText("LSTEntryMissing", "source", "other"), LocalizationManager::get()->getTranslatedText("TextPopupTitle_LSTFileError"), MB_OK);
					return;
				}

				if (strGamePathFolderPath == "")
				{
					Tasks::showMessage(LocalizationManager::get()->getTranslatedFormattedText("LSTEntryMissing", "gamepath", "other"), LocalizationManager::get()->getTranslatedText("TextPopupTitle_LSTFileError"), MB_OK);
					return;
				}

				string strFileName = Path::getFileName(Path::removeSlashFromEnd(pLSTFileEntry->getValuesLine()));
				if (strFileName == "*")
				{
					string strCopySourceFolder = strGTARootFolderPath + strSourceFolderPath + Path::removeSlashFromFront(Path::getDirectory(pLSTFileEntry->getValuesLine()));
					for (auto strFileName : File::getFileNames(strCopySourceFolder))
					{
						string strCopySourcePath = strGTARootFolderPath + strSourceFolderPath + strFileName;
						string strCopyDestinationPath = strGTARootFolderPath + strGamePathFolderPath + strFileName;
						File::copyFile(strCopySourcePath, strCopyDestinationPath);
					}
					// todo - getIMGF()->getEntryListTab()->log(LocalizationManager::get()->getTranslatedText("Log_LSTCopy1"));
					// todo - getIMGF()->getEntryListTab()->log(LocalizationManager::get()->getTranslatedFormattedText("Log_LSTCopy2", strCopySourceFolder.c_str(), (strGTARootFolderPath + strGamePathFolderPath).c_str()), true);
				}
				else
				{
					string strFileName = Path::removeSlashFromFront(pLSTFileEntry->getValuesLine());
					string strCopySourcePath = strGTARootFolderPath + strSourceFolderPath + strFileName;
					string strCopyDestinationPath = strGTARootFolderPath + strGamePathFolderPath + strFileName;
					File::copyFile(strCopySourcePath, strCopyDestinationPath);
					// todo - getIMGF()->getEntryListTab()->log(LocalizationManager::get()->getTranslatedFormattedText("Log_LSTCopy3", strFileName.c_str()));
					// todo - getIMGF()->getEntryListTab()->log(LocalizationManager::get()->getTranslatedFormattedText("Log_LSTCopy4", strFileName.c_str(), strCopySourcePath.c_str(), strCopyDestinationPath.c_str()), true);
				}
			}
			else if (strCommandUpper == "DEL" || strCommandUpper == "DELETE")
			{
				if (strSourceFolderPath == "")
				{
					Tasks::showMessage(LocalizationManager::get()->getTranslatedFormattedText("LSTEntryMissing", "source", "other"), LocalizationManager::get()->getTranslatedText("TextPopupTitle_LSTFileError"), MB_OK);
					return;
				}

				if (strGamePathFolderPath == "")
				{
					Tasks::showMessage(LocalizationManager::get()->getTranslatedFormattedText("LSTEntryMissing", "gamepath", "other"), LocalizationManager::get()->getTranslatedText("TextPopupTitle_LSTFileError"), MB_OK);
					return;
				}

				string strFileName = Path::getFileName(Path::removeSlashFromEnd(pLSTFileEntry->getValuesLine()));
				if (strFileName == "*")
				{
					string strFolderPath = strGTARootFolderPath + strGamePathFolderPath + Path::removeSlashFromFront(Path::getDirectory(pLSTFileEntry->getValuesLine()));
					for (auto strFileName : File::getFileNames(strFolderPath))
					{
						string strFilePath = strFolderPath + strFileName;
						File::removeFile(strFilePath);
					}
					// todo - getIMGF()->getEntryListTab()->log(LocalizationManager::get()->getTranslatedText("Log_LSTDelete1"));
					// todo - getIMGF()->getEntryListTab()->log(LocalizationManager::get()->getTranslatedFormattedText("Log_LSTDelete2", strFolderPath.c_str()), true);
				}
				else
				{
					string strFileName = Path::removeSlashFromFront(pLSTFileEntry->getValuesLine());
					string strFilePath = strGTARootFolderPath + strGamePathFolderPath + strFileName;
					File::removeFile(strFilePath);

					// todo - getIMGF()->getEntryListTab()->log(LocalizationManager::get()->getTranslatedFormattedText("Log_LSTDelete3", strFileName.c_str()));
					// todo - getIMGF()->getEntryListTab()->log(LocalizationManager::get()->getTranslatedFormattedText("Log_LSTDelete4", strFilePath.c_str()), true);
				}
			}
		}
	}
	
	pLSTFile->unload();
	delete pLSTFile;
}