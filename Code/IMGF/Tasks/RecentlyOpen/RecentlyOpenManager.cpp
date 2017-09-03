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

using namespace std;
using namespace bxcf;
using namespace imgf;

void					RecentlyOpenManager::init(void)
{
	loadRecentlyOpenEntries();
}
void					RecentlyOpenManager::uninit(void)
{
	unloadRecentlyOpenEntries();
}

void					RecentlyOpenManager::loadRecentlyOpenEntries(void)
{
	/*
	todo

	removeAllEntries();

	for (auto it : getIMGF()->getRecentlyOpenManager()->getRecentlyOpenedFilesContainer())
	{
		DeleteMenu(getIMGF()->m_hSubMenu_File_OpenRecent, it.first, 0);
	}
	getIMGF()->getRecentlyOpenManager()->getRecentlyOpenedFilesContainer().clear();
	DeleteMenu(getIMGF()->m_hSubMenu_File_OpenRecent, 1880, 0);
	DeleteMenu(getIMGF()->m_hSubMenu_File_OpenRecent, 1881, 0);

	uint32 uiRecentlyOpenedCount = String::toUint32(INIManager::getItem(AppDataPath::getRecentlyOpenedPath(), "RecentlyOpened", "Count"));
	for (int32 i = uiRecentlyOpenedCount; i >= 1; i--)
	{
		string strIMGPath = INIManager::getItem(AppDataPath::getRecentlyOpenedPath(), "RecentlyOpened", String::toString(i));

		AppendMenu(getIMGF()->m_hSubMenu_File_OpenRecent, MF_STRING, 1800 + i, String::convertStdStringToStdWString(String::toString((uiRecentlyOpenedCount - i) + 1) + ") " + strIMGPath).c_str());

		getIMGF()->getRecentlyOpenManager()->getRecentlyOpenedFilesContainer()[1800 + i] = strIMGPath;

		RecentlyOpenEntry *pRecentlyOpenEntry = new RecentlyOpenEntry;
		pRecentlyOpenEntry->m_strPath = strIMGPath;
		addEntry(pRecentlyOpenEntry);
	}

	if (uiRecentlyOpenedCount == 0)
	{
		AppendMenu(getIMGF()->m_hSubMenu_File_OpenRecent, MF_STRING | MF_DISABLED, 1881, LocalizationManager::get()->getTranslatedTextW("Menu_RecentlyOpenFiles_NoFiles").c_str());
	}

	AppendMenu(getIMGF()->m_hSubMenu_File_OpenRecent, MF_STRING, 1880, LocalizationManager::get()->getTranslatedTextW("Menu_RecentlyOpenFiles_Clear").c_str());
	*/
}
void					RecentlyOpenManager::unloadRecentlyOpenEntries(void)
{
	removeAllEntries();
}

RecentlyOpenEntry*		RecentlyOpenManager::addRecentlyOpenEntry(string strPath)
{
	if (doesRecentlyOpenEntryExist(strPath))
	{
		moveRecentlyOpenEntryToTop(strPath);
		loadRecentlyOpenEntries();
		RecentlyOpenEntry *pRecentlyOpenEntry = getRecentlyOpenEntryByPath(strPath);
		return pRecentlyOpenEntry;
	}

	strPath = String::replace(strPath, "/", "\\");

	RecentlyOpenEntry *pRecentlyOpenEntry = new RecentlyOpenEntry;
	pRecentlyOpenEntry->m_strPath = strPath;
	addEntry(pRecentlyOpenEntry);

	uint32 uiRecentlyOpenedMaxCount = 15;
	uint32 uiRecentlyOpenedCount = String::toUint32(INIManager::getItem(AppDataPath::getRecentlyOpenedPath(), "RecentlyOpened", "Count"));

	if (uiRecentlyOpenedCount == uiRecentlyOpenedMaxCount)
	{
		for (uint32 i = 2; i <= uiRecentlyOpenedMaxCount; i++)
		{
			string strIMGPath2 = INIManager::getItem(AppDataPath::getRecentlyOpenedPath(), "RecentlyOpened", String::toString(i));
			INIManager::setItem(AppDataPath::getRecentlyOpenedPath(), "RecentlyOpened", String::toString(i - 1), strIMGPath2);
		}
		INIManager::setItem(AppDataPath::getRecentlyOpenedPath(), "RecentlyOpened", String::toString(uiRecentlyOpenedMaxCount), strPath);
	}
	else
	{
		INIManager::setItem(AppDataPath::getRecentlyOpenedPath(), "RecentlyOpened", "Count", String::toString(uiRecentlyOpenedCount + 1));
		INIManager::setItem(AppDataPath::getRecentlyOpenedPath(), "RecentlyOpened", String::toString(uiRecentlyOpenedCount + 1), strPath);
	}

	return pRecentlyOpenEntry;
}

void					RecentlyOpenManager::removeRecentlyOpenedEntries(void)
{
	/*
	todo
	for (auto it : getIMGF()->getRecentlyOpenManager()->getRecentlyOpenedFilesContainer())
	{
		DeleteMenu(getIMGF()->m_hSubMenu_File_OpenRecent, it.first, 0);
	}
	getIMGF()->getRecentlyOpenManager()->getRecentlyOpenedFilesContainer().clear();

	removeAllEntries();
	getIMGF()->getActiveWindow()->clearOpenLastFilename();

	uint32 uiRecentlyOpenedCount = String::toUint32(INIManager::getItem(AppDataPath::getRecentlyOpenedPath(), "RecentlyOpened", "Count"));
	for (uint32 i = 1; i <= uiRecentlyOpenedCount; i++)
	{
		INIManager::removeItem(AppDataPath::getRecentlyOpenedPath(), "RecentlyOpened", String::toString(i));
	}
	INIManager::setItem(AppDataPath::getRecentlyOpenedPath(), "RecentlyOpened", "Count", 0);

	loadRecentlyOpenEntries();
	*/
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