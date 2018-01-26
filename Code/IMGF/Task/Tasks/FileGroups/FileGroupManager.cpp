#include "FileGroupManager.h"
#include "Static/String.h"
#include "Static/Path.h"
#include "Static/StdVector.h"
#include "Globals.h"
#include "IMGF.h"
#include "Format/IMG/Regular/IMGEntry.h"
#include "Localization/LocalizationManager.h"
#include "Format/Text/INI/INIManager.h"
#include "Static/AppDataPath.h"
#include "GUI/Window/WindowManager.h"
#include "GUI/Window/Windows/MainWindow/MainWindow.h"
#include "Control/Controls/Menu.h"
#include "Event/EInputEvent.h"

using namespace std;
using namespace bxcf;
using namespace bxgx;
using namespace bxgx::events;
using namespace imgf;

// initialization
void		FileGroupManager::init(void)
{
	// todo bindEvent(BXGX_READY, &FileGroupManager::loadFileGroups);
}

void		FileGroupManager::uninit(void)
{
	// todo unloadFileGroups(uiEditor);
}

// load/unload file group
void		FileGroupManager::loadFileGroups(EEditor uiEditor)
{
	removeAllEntries();

	// todo
	//Menu *pMenu = getIMGF()->getWindowManager()->getMainWindow()->getMainLayer()->m_pFileGroupMenu;

	//pMenu->removeAllMenuItems();
	getIMGF()->getFileGroupManager()->getFileGroupsContainer().clear();

	string strINISectionName = Editor::getEditorName(uiEditor);
	uint32 uiSessionCount = String::toUint32(INIManager::getItem(AppDataPath::getFileGroupsPath(), strINISectionName, "Count"));
	for (int32 i = uiSessionCount; i >= 1; i--)
	{
		string strIMGPaths = INIManager::getItem(AppDataPath::getFileGroupsPath(), strINISectionName, i);
		
		deque<string> deqIMGPaths = StdVector::convertVectorToDeque(String::split(strIMGPaths, "; "));
		string strSessionName = deqIMGPaths[0];
		deqIMGPaths.pop_front();
		uint32 j2 = deqIMGPaths.size();
		vector<string> vecIMGPaths;
		for (uint32 i2 = 0; i2 < j2; i2++)
		{
			vecIMGPaths.push_back(deqIMGPaths[i2]);
			deqIMGPaths[i2] = Path::getFileName(deqIMGPaths[i2]);
		}

		string strMenuItemText = String::toString((uiSessionCount - i) + 1) + ") " + strSessionName + " (" + String::toString(j2) + " tab" + (j2 == 1 ? "" : "s") + ")";
		//pMenu->addMenuItem(strMenuItemText, 1900 + i);

		getIMGF()->getFileGroupManager()->getFileGroupsContainer()[1900 + i] = strIMGPaths;

		FileGroup *pFileGroup = new FileGroup;
		pFileGroup->m_strName = strSessionName;
		pFileGroup->m_vecPaths = vecIMGPaths;
		addEntry(pFileGroup);
	}

	if (uiSessionCount == 0)
	{
		//pMenu->addMenuItem("There are currently no file groups.", 1981);
	}
}

void		FileGroupManager::unloadFileGroups(EEditor uiEditor)
{
	removeAllEntries();
}

// add/remove file group
FileGroup*	FileGroupManager::addFileGroup(EEditor uiEditor, string strSessionName, vector<string>& vecPaths)
{
	string strINISectionName = Editor::getEditorName(uiEditor);
	uint32 uiSessionIndex = getEntryCount() + 1;

	FileGroup *pFileGroup = new FileGroup;
	pFileGroup->m_strName = strSessionName;
	pFileGroup->m_vecPaths = vecPaths;
	addEntry(pFileGroup);

	INIManager::setItem(AppDataPath::getFileGroupsPath(), strINISectionName, "Count", String::toString(uiSessionIndex));
	INIManager::setItem(AppDataPath::getFileGroupsPath(), strINISectionName, String::toString(uiSessionIndex), pFileGroup->serialize());
	
	return pFileGroup;
}

void		FileGroupManager::removeFileGroup(EEditor uiEditor, FileGroup *pFileGroup)
{
	string strINISectionName = Editor::getEditorName(uiEditor);

	// fetch session index
	uint32 uiSessionIndex = getIndexByEntry(pFileGroup);
	
	// remove session from memory and file
	removeEntry(pFileGroup);
	INIManager::removeItem(AppDataPath::getFileGroupsPath(), strINISectionName, uiSessionIndex);
	
	// shift other sessions with a higher ID down by 1 ID in file
	uint32 uiSessionCount = String::toUint32(INIManager::getItem(AppDataPath::getFileGroupsPath(), strINISectionName, "Count"));
	for (uint32 i = uiSessionIndex; i < uiSessionCount; i++)
	{
		string strIMGPaths2 = INIManager::getItem(AppDataPath::getFileGroupsPath(), strINISectionName, i + 1);
		INIManager::setItem(AppDataPath::getFileGroupsPath(), strINISectionName, i, strIMGPaths2);
	}
	
	// remove session with highest ID in file?
	INIManager::removeItem(AppDataPath::getFileGroupsPath(), strINISectionName, uiSessionCount);
	
	// update session count to file
	INIManager::setItem(AppDataPath::getFileGroupsPath(), strINISectionName, "Count", String::toString(uiSessionCount - 1));
}

// fetch file group
FileGroup*		FileGroupManager::getFileGroupByName(EEditor uiEditor, string strSessionName)
{
	for(auto pSession : getEntries())
	{
		if(pSession->m_strName == strSessionName)
		{
			return pSession;
		}
	}
	return nullptr;
}