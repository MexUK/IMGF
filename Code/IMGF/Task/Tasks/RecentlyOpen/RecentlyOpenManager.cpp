#include "RecentlyOpenManager.h"
#include "Static/String.h"
#include "Static/Path.h"
#include "Static/StdVector.h"
#include "Static/Registry.h"
#include "Globals.h"
#include "IMGF.h"
#include "Static/Debug.h"
#include "Format/IMG/Regular/IMGEntry.h"
#include "Localization/LocalizationManager.h"
#include "Window/Window.h"
#include "Format/Text/INI/INIManager.h"
#include "Static/AppDataPath.h"
#include "GUI/Window/WindowManager.h"
#include "GUI/Window/Windows/MainWindow/MainWindow.h"
#include "Control/Controls/Menu.h"
#include "Event/EInputEvent.h"
#include "GUI/Input/EInputItem.h"

using namespace std;
using namespace bxcf;
using namespace bxgx;
using namespace bxgx::events;
using namespace imgf;
using namespace imgf::mainLayer::input;

// initialization
void					RecentlyOpenManager::init(void)
{
	bindEvent(BXGX_READY, &RecentlyOpenManager::onToolReady);
}

void					RecentlyOpenManager::uninit(void)
{
	unloadRecentlyOpenEntries(getIMGF()->getWindowManager()->getMainWindow()->getActiveEditor()->getEditorType());
}

// event callbacks
void					RecentlyOpenManager::onToolReady(void)
{
	loadRecentlyOpenEntries(getIMGF()->getWindowManager()->getMainWindow()->getActiveEditor()->getEditorType());
}

// load/unload entries
void					RecentlyOpenManager::loadRecentlyOpenEntries(EEditor uiEditor)
{
	m_umapFilePaths[uiEditor].removeAllEntries();

	Menu *pRecentlyOpenMenu = getIMGF()->getWindowManager()->getMainWindow()->m_pRecentlyOpenMenu;
	
	pRecentlyOpenMenu->removeAllMenuItems();

	string strINISectionName = Editor::getEditorName(uiEditor);
	uint32 uiRecentlyOpenedCount = String::toUint32(INIManager::getItem(AppDataPath::getRecentlyOpenedPath(), strINISectionName, "Count"));
	for (int32 i = uiRecentlyOpenedCount; i >= 1; i--)
	{
		string strIMGPath = INIManager::getItem(AppDataPath::getRecentlyOpenedPath(), strINISectionName, String::toString(i));

		string strMenuItemText = String::toString((uiRecentlyOpenedCount - i) + 1) + ") " + strIMGPath;
		pRecentlyOpenMenu->addMenuItem(strMenuItemText, 1800 + i);

		m_umapRecentlyOpenedFiles[1800 + i] = strIMGPath;

		RecentlyOpenEntry *pRecentlyOpenEntry = new RecentlyOpenEntry;
		pRecentlyOpenEntry->m_strPath = strIMGPath;
		m_umapFilePaths[uiEditor].addEntry(pRecentlyOpenEntry);
	}

	if (uiRecentlyOpenedCount == 0)
	{
		pRecentlyOpenMenu->addMenuItem("There are no recently open files");
	}

	pRecentlyOpenMenu->addMenuItem("Clear Recently Open Files", CLEAR_RECENTLY_OPEN_FILES);
}

void					RecentlyOpenManager::unloadRecentlyOpenEntries(EEditor uiEditor)
{
	m_umapFilePaths[uiEditor].removeAllEntries();
}

// add/remove entries
RecentlyOpenEntry*		RecentlyOpenManager::addRecentlyOpenEntry(EEditor uiEditor, string strFilePath)
{
	if (doesRecentlyOpenEntryExist(uiEditor, strFilePath))
	{
		moveRecentlyOpenEntryToTop(uiEditor, strFilePath);
		loadRecentlyOpenEntries(uiEditor);
		RecentlyOpenEntry *pRecentlyOpenEntry = getRecentlyOpenEntryByPath(uiEditor, strFilePath);
		return pRecentlyOpenEntry;
	}

	string strINISectionName = Editor::getEditorName(uiEditor);

	strFilePath = String::replace(strFilePath, "/", "\\");

	RecentlyOpenEntry *pRecentlyOpenEntry = new RecentlyOpenEntry;
	pRecentlyOpenEntry->m_strPath = strFilePath;
	m_umapFilePaths[uiEditor].addEntry(pRecentlyOpenEntry);

	uint32 uiRecentlyOpenedMaxCount = 15;
	uint32 uiRecentlyOpenedCount = String::toUint32(INIManager::getItem(AppDataPath::getRecentlyOpenedPath(), strINISectionName, "Count"));

	Menu *pRecentlyOpenMenu = getIMGF()->getWindowManager()->getMainWindow()->m_pRecentlyOpenMenu;

	if (uiRecentlyOpenedCount == 0)
	{
		pRecentlyOpenMenu->removeMenuItem(pRecentlyOpenMenu->getFirstEntry());
	}

	pRecentlyOpenMenu->removeMenuItem(pRecentlyOpenMenu->getLastEntry());

	string strMenuItemText = String::toString(uiRecentlyOpenedCount + 1) + ") " + strFilePath;
	pRecentlyOpenMenu->addMenuItem(strMenuItemText, 1800 + uiRecentlyOpenedCount + 1);
	m_umapRecentlyOpenedFiles[1800 + uiRecentlyOpenedCount + 1] = strFilePath;

	pRecentlyOpenMenu->addMenuItem("Clear Recently Open Files", CLEAR_RECENTLY_OPEN_FILES);

	if (uiRecentlyOpenedCount == uiRecentlyOpenedMaxCount)
	{
		for (uint32 i = 2; i <= uiRecentlyOpenedMaxCount; i++)
		{
			string strIMGPath2 = INIManager::getItem(AppDataPath::getRecentlyOpenedPath(), strINISectionName, String::toString(i));
			INIManager::setItem(AppDataPath::getRecentlyOpenedPath(), strINISectionName, String::toString(i - 1), strIMGPath2);
		}
		INIManager::setItem(AppDataPath::getRecentlyOpenedPath(), strINISectionName, String::toString(uiRecentlyOpenedMaxCount), strFilePath);
	}
	else
	{
		INIManager::setItem(AppDataPath::getRecentlyOpenedPath(), strINISectionName, "Count", String::toString(uiRecentlyOpenedCount + 1));
		INIManager::setItem(AppDataPath::getRecentlyOpenedPath(), strINISectionName, String::toString(uiRecentlyOpenedCount + 1), strFilePath);
	}

	return pRecentlyOpenEntry;
}

void					RecentlyOpenManager::removeRecentlyOpenedEntries(EEditor uiEditor)
{
	string strINISectionName = Editor::getEditorName(uiEditor);
	Menu *pRecentlyOpenMenu = getIMGF()->getWindowManager()->getMainWindow()->m_pRecentlyOpenMenu;

	pRecentlyOpenMenu->removeAllMenuItems();
	m_umapRecentlyOpenedFiles.clear();

	getIMGF()->getRecentlyOpenManager()->getRecentlyOpenedFilesContainer().clear();

	m_umapFilePaths[uiEditor].removeAllEntries();
	getIMGF()->getWindowManager()->getMainWindow()->clearOpenLastFilename();

	uint32 uiRecentlyOpenedCount = String::toUint32(INIManager::getItem(AppDataPath::getRecentlyOpenedPath(), strINISectionName, "Count"));
	for (uint32 i = 1; i <= uiRecentlyOpenedCount; i++)
	{
		INIManager::removeItem(AppDataPath::getRecentlyOpenedPath(), strINISectionName, String::toString(i));
	}
	INIManager::setItem(AppDataPath::getRecentlyOpenedPath(), strINISectionName, "Count", "0");

	loadRecentlyOpenEntries(uiEditor);
}

void					RecentlyOpenManager::removeRecentlyOpenEntry(EEditor uiEditor, RecentlyOpenEntry *pRecentlyOpenEntry)
{
	string strINISectionName = Editor::getEditorName(uiEditor);

	uint32 uiRecentlyOpenedIndex = getRecentlyOpenedFileIndex(uiEditor, pRecentlyOpenEntry->getPath());
	INIManager::removeItem(AppDataPath::getRecentlyOpenedPath(), strINISectionName, String::toString(uiRecentlyOpenedIndex));

	uint32 uiRecentlyOpenedCount = String::toUint32(INIManager::getItem(AppDataPath::getRecentlyOpenedPath(), strINISectionName, "Count"));
	for (uint32 i = uiRecentlyOpenedIndex; i <= uiRecentlyOpenedCount; i++)
	{
		string strIMGPath2 = INIManager::getItem(AppDataPath::getRecentlyOpenedPath(), strINISectionName, String::toString(i + 1));
		INIManager::setItem(AppDataPath::getRecentlyOpenedPath(), strINISectionName, String::toString(i), strIMGPath2);
	}
	INIManager::setItem(AppDataPath::getRecentlyOpenedPath(), strINISectionName, "Count", String::toString(uiRecentlyOpenedCount - 1));

	m_umapFilePaths[uiEditor].removeEntry(pRecentlyOpenEntry);
}

// entry fetching
uint32			RecentlyOpenManager::getRecentlyOpenedFileIndex(EEditor uiEditor, string strIMGPath)
{
	string strINISectionName = Editor::getEditorName(uiEditor);
	uint32 uiRecentlyOpenedCount = String::toUint32(INIManager::getItem(AppDataPath::getRecentlyOpenedPath(), strINISectionName, "Count"));
	for (uint32 i = 1; i <= uiRecentlyOpenedCount; i++)
	{
		string strIMGPath2 = INIManager::getItem(AppDataPath::getRecentlyOpenedPath(), strINISectionName, String::toString(i));
		if (strIMGPath2 == strIMGPath)
		{
			return i;
		}
	}
	return -1;
}

RecentlyOpenEntry*		RecentlyOpenManager::getRecentlyOpenEntryByPath(EEditor uiEditor, string strPath)
{
	strPath = String::toUpperCase(strPath);
	strPath = String::replace(strPath, "\\", "/");
	for (auto pRecentlyOpenEntry : m_umapFilePaths[uiEditor].getEntries())
	{
		if (String::replace(String::toUpperCase(pRecentlyOpenEntry->m_strPath), "\\", "/") == strPath)
		{
			return pRecentlyOpenEntry;
		}
	}
	return nullptr;
}

string					RecentlyOpenManager::getLastOpenEntry(EEditor uiEditor)
{
	string strINISectionName = Editor::getEditorName(uiEditor);
	uint32 uiRecentlyOpenedCount = String::toUint32(INIManager::getItem(AppDataPath::getRecentlyOpenedPath(), strINISectionName, "Count"));
	if (uiRecentlyOpenedCount == 0)
	{
		return "";
	}

	string strIMGPath = INIManager::getItem(AppDataPath::getRecentlyOpenedPath(), strINISectionName, String::toString(uiRecentlyOpenedCount));
	return strIMGPath;
}

// entry testing
bool					RecentlyOpenManager::doesRecentlyOpenEntryExist(EEditor uiEditor, string strPath)
{
	return getRecentlyOpenEntryByPath(uiEditor, strPath) != nullptr;
}

// entry moving
void					RecentlyOpenManager::moveRecentlyOpenEntryToTop(EEditor uiEditor, string strIMGPath)
{
	removeRecentlyOpenEntry(uiEditor, getRecentlyOpenEntryByPath(uiEditor, strIMGPath));
	addRecentlyOpenEntry(uiEditor, strIMGPath);
}