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
#include "GUI/Layer/Layers/MainLayer/MainLayer.h"
#include "Control/Controls/Menu.h"
#include "Event/EInputEvent.h"
#include "GUI/Input/EInputItem.h"

using namespace std;
using namespace bxcf;
using namespace bxgx;
using namespace bxgx::events;
using namespace imgf;
using namespace imgf::mainLayer::input;

void					RecentlyOpenManager::init(void)
{
	bindEvent(BXGX_READY, &RecentlyOpenManager::loadRecentlyOpenEntries);
}

void					RecentlyOpenManager::uninit(void)
{
	unloadRecentlyOpenEntries();
}

void					RecentlyOpenManager::loadRecentlyOpenEntries(void)
{
	removeAllEntries();

	Menu *pRecentlyOpenMenu = getIMGF()->getWindowManager()->getMainWindow()->getMainLayer()->m_pRecentlyOpenMenu;
	
	pRecentlyOpenMenu->removeAllMenuItems();
	m_umapRecentlyOpenedFiles.clear();

	uint32 uiRecentlyOpenedCount = String::toUint32(INIManager::getItem(AppDataPath::getRecentlyOpenedPath(), "RecentlyOpened", "Count"));
	for (int32 i = uiRecentlyOpenedCount; i >= 1; i--)
	{
		string strIMGPath = INIManager::getItem(AppDataPath::getRecentlyOpenedPath(), "RecentlyOpened", String::toString(i));

		string strMenuItemText = String::toString((uiRecentlyOpenedCount - i) + 1) + ") " + strIMGPath;
		pRecentlyOpenMenu->addMenuItem(strMenuItemText, 1800 + i);

		m_umapRecentlyOpenedFiles[1800 + i] = strIMGPath;

		RecentlyOpenEntry *pRecentlyOpenEntry = new RecentlyOpenEntry;
		pRecentlyOpenEntry->m_strPath = strIMGPath;
		addEntry(pRecentlyOpenEntry);
	}

	if (uiRecentlyOpenedCount == 0)
	{
		pRecentlyOpenMenu->addMenuItem("There are no recently open files");
	}

	pRecentlyOpenMenu->addMenuItem("Clear Recently Open Files", CLEAR_RECENTLY_OPEN_FILES);
}
void					RecentlyOpenManager::unloadRecentlyOpenEntries(void)
{
	removeAllEntries();
}

RecentlyOpenEntry*		RecentlyOpenManager::addRecentlyOpenEntry(string strFilePath)
{
	if (doesRecentlyOpenEntryExist(strFilePath))
	{
		moveRecentlyOpenEntryToTop(strFilePath);
		loadRecentlyOpenEntries();
		RecentlyOpenEntry *pRecentlyOpenEntry = getRecentlyOpenEntryByPath(strFilePath);
		return pRecentlyOpenEntry;
	}

	strFilePath = String::replace(strFilePath, "/", "\\");

	RecentlyOpenEntry *pRecentlyOpenEntry = new RecentlyOpenEntry;
	pRecentlyOpenEntry->m_strPath = strFilePath;
	addEntry(pRecentlyOpenEntry);

	uint32 uiRecentlyOpenedMaxCount = 15;
	uint32 uiRecentlyOpenedCount = String::toUint32(INIManager::getItem(AppDataPath::getRecentlyOpenedPath(), "RecentlyOpened", "Count"));

	Menu *pRecentlyOpenMenu = getIMGF()->getWindowManager()->getMainWindow()->getMainLayer()->m_pRecentlyOpenMenu;

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
			string strIMGPath2 = INIManager::getItem(AppDataPath::getRecentlyOpenedPath(), "RecentlyOpened", String::toString(i));
			INIManager::setItem(AppDataPath::getRecentlyOpenedPath(), "RecentlyOpened", String::toString(i - 1), strIMGPath2);
		}
		INIManager::setItem(AppDataPath::getRecentlyOpenedPath(), "RecentlyOpened", String::toString(uiRecentlyOpenedMaxCount), strFilePath);
	}
	else
	{
		INIManager::setItem(AppDataPath::getRecentlyOpenedPath(), "RecentlyOpened", "Count", String::toString(uiRecentlyOpenedCount + 1));
		INIManager::setItem(AppDataPath::getRecentlyOpenedPath(), "RecentlyOpened", String::toString(uiRecentlyOpenedCount + 1), strFilePath);
	}

	return pRecentlyOpenEntry;
}

void					RecentlyOpenManager::removeRecentlyOpenedEntries(void)
{
	Menu *pRecentlyOpenMenu = getIMGF()->getWindowManager()->getMainWindow()->getMainLayer()->m_pRecentlyOpenMenu;

	pRecentlyOpenMenu->removeAllMenuItems();
	m_umapRecentlyOpenedFiles.clear();

	getIMGF()->getRecentlyOpenManager()->getRecentlyOpenedFilesContainer().clear();

	removeAllEntries();
	getIMGF()->getWindowManager()->getMainWindow()->clearOpenLastFilename();

	uint32 uiRecentlyOpenedCount = String::toUint32(INIManager::getItem(AppDataPath::getRecentlyOpenedPath(), "RecentlyOpened", "Count"));
	for (uint32 i = 1; i <= uiRecentlyOpenedCount; i++)
	{
		INIManager::removeItem(AppDataPath::getRecentlyOpenedPath(), "RecentlyOpened", String::toString(i));
	}
	INIManager::setItem(AppDataPath::getRecentlyOpenedPath(), "RecentlyOpened", "Count", "0");

	loadRecentlyOpenEntries();
}

void					RecentlyOpenManager::removeRecentlyOpenEntry(RecentlyOpenEntry *pRecentlyOpenEntry)
{
	uint32 uiRecentlyOpenedIndex = getRecentlyOpenedFileIndex(pRecentlyOpenEntry->getPath());
	INIManager::removeItem(AppDataPath::getRecentlyOpenedPath(), "RecentlyOpened", String::toString(uiRecentlyOpenedIndex));

	uint32 uiRecentlyOpenedCount = String::toUint32(INIManager::getItem(AppDataPath::getRecentlyOpenedPath(), "RecentlyOpened", "Count"));
	for (uint32 i = uiRecentlyOpenedIndex; i <= uiRecentlyOpenedCount; i++)
	{
		string strIMGPath2 = INIManager::getItem(AppDataPath::getRecentlyOpenedPath(), "RecentlyOpened", String::toString(i + 1));
		INIManager::setItem(AppDataPath::getRecentlyOpenedPath(), "RecentlyOpened", String::toString(i), strIMGPath2);
	}
	INIManager::setItem(AppDataPath::getRecentlyOpenedPath(), "RecentlyOpened", "Count", String::toString(uiRecentlyOpenedCount - 1));

	removeEntry(pRecentlyOpenEntry);
}

uint32			RecentlyOpenManager::getRecentlyOpenedFileIndex(string strIMGPath)
{
	uint32 uiRecentlyOpenedCount = String::toUint32(INIManager::getItem(AppDataPath::getRecentlyOpenedPath(), "RecentlyOpened", "Count"));
	for (uint32 i = 1; i <= uiRecentlyOpenedCount; i++)
	{
		string strIMGPath2 = INIManager::getItem(AppDataPath::getRecentlyOpenedPath(), "RecentlyOpened", String::toString(i));
		if (strIMGPath2 == strIMGPath)
		{
			return i;
		}
	}
	return -1;
}

RecentlyOpenEntry*		RecentlyOpenManager::getRecentlyOpenEntryByPath(string strPath)
{
	strPath = String::toUpperCase(strPath);
	strPath = String::replace(strPath, "\\", "/");
	for (auto pRecentlyOpenEntry : getEntries())
	{
		if (String::replace(String::toUpperCase(pRecentlyOpenEntry->m_strPath), "\\", "/") == strPath)
		{
			return pRecentlyOpenEntry;
		}
	}
	return nullptr;
}

bool					RecentlyOpenManager::doesRecentlyOpenEntryExist(string strPath)
{
	return getRecentlyOpenEntryByPath(strPath) != nullptr;
}

string					RecentlyOpenManager::getLastOpenEntry(void)
{
	uint32 uiRecentlyOpenedCount = String::toUint32(INIManager::getItem(AppDataPath::getRecentlyOpenedPath(), "RecentlyOpened", "Count"));
	if (uiRecentlyOpenedCount == 0)
	{
		return "";
	}

	string strIMGPath = INIManager::getItem(AppDataPath::getRecentlyOpenedPath(), "RecentlyOpened", String::toString(uiRecentlyOpenedCount));
	return strIMGPath;
}

void					RecentlyOpenManager::moveRecentlyOpenEntryToTop(string strIMGPath)
{
	removeRecentlyOpenEntry(getRecentlyOpenEntryByPath(strIMGPath));
	addRecentlyOpenEntry(strIMGPath);
}