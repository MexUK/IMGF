#include "DragDrop/CDragDrop.h"

// drop files from explorer to imgf
/*
void					CDragDrop::onDropFiles(vector<string>& vecPaths)
{
	vector<string>
		vecOpenPaths,
		vecEntryPaths;
	for (uint32 i = 0; i < vecPaths.size(); i++)
	{
		string strPath = vecPaths[i];

		// folder
		if (CFileManager::doesFolderExist(strPath))
		{
			strPath = CPathManager::addSlashToEnd(strPath);
			vector<string> vecFileNames = CFileManager::getFileNames(strPath);
			for (auto strFileName : vecFileNames)
			{
				vecPaths.push_back(strPath + strFileName);
			}
			continue;
		}

		string strExtension = CString2::toUpperCase(CPathManager::getFileExtension(strPath));
		if (strExtension == "IMG" || strExtension == "DIR")
		{
			// open IMG
			vecOpenPaths.push_back(strPath);
		}
		else
		{
			if (getIMGF()->getActiveTab() == nullptr)
			{
				return;
			}

			vecEntryPaths.push_back(strPath);
		}
	}

	if (vecEntryPaths.size() > 0)
	{
		for (auto strPath : vecEntryPaths)
		{
			getIMGF()->getEntryListTab()->addOrReplaceEntryViaFileAndSettings(strPath);
		}
		//getIMGF()->getEntryListTab()->log(CLocalizationManager::get()->getTranslatedFormattedText("Log_23", vecImportPaths.size()));

		getIMGF()->getEntryListTab()->setIMGModifiedSinceRebuild(true);
	}

	for (auto strPath : vecOpenPaths)
	{
		getIMGF()->getTaskManager()->getDispatch()->onRequestOpen2(strPath);
	}
}
*/