#include "DragDrop/DragDrop.h"

using namespace imgf;

// drop files from explorer to imgf
/*
void					DragDrop::onDropFiles(vector<string>& vecPaths)
{
	vector<string>
		vecOpenPaths,
		vecEntryPaths;
	for (uint32 i = 0; i < vecPaths.size(); i++)
	{
		string strPath = vecPaths[i];

		// folder
		if (File::doesFolderExist(strPath))
		{
			strPath = Path::addSlashToEnd(strPath);
			vector<string> vecFileNames = File::getFileNames(strPath);
			for (auto strFileName : vecFileNames)
			{
				vecPaths.push_back(strPath + strFileName);
			}
			continue;
		}

		string strExtension = String2::toUpperCase(Path::getFileExtension(strPath));
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
		//getIMGF()->getEntryListTab()->log(LocalizationManager::get()->getTranslatedFormattedText("Log_23", vecImportPaths.size()));

		getIMGF()->getEntryListTab()->setIMGModifiedSinceRebuild(true);
	}

	for (auto strPath : vecOpenPaths)
	{
		getIMGF()->getTaskManager()->getDispatch()->onRequestOpen2(strPath);
	}
}
*/