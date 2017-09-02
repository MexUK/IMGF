#include "RecentlyOpenManager.h"
#include "Static/CString2.h"
#include "Static/CPath.h"
#include "Static/CStdVector.h"
#include "Static/CRegistry.h"
#include "Globals.h"
#include "IMGF.h"
#include "Static/CDebug.h"
#include "Format/IMG/Regular/CIMGEntry.h"
#include "Localization/CLocalizationManager.h"
#include "Window/Window.h"
#include "Format/Text/INI/CINIManager.h"
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

	uint32 uiRecentlyOpenedCount = CString2::toUint32(CINIManager::getItem(AppDataPath::getRecentlyOpenedPath(), "RecentlyOpened", "Count"));
	for (int32 i = uiRecentlyOpenedCount; i >= 1; i--)
	{
		string strIMGPath = CINIManager::getItem(AppDataPath::getRecentlyOpenedPath(), "RecentlyOpened", CString2::toString(i));

		AppendMenu(getIMGF()->m_hSubMenu_File_OpenRecent, MF_STRING, 1800 + i, CString2::convertStdStringToStdWString(CString2::toString((uiRecentlyOpenedCount - i) + 1) + ") " + strIMGPath).c_str());

		getIMGF()->getRecentlyOpenManager()->getRecentlyOpenedFilesContainer()[1800 + i] = strIMGPath;

		RecentlyOpenEntry *pRecentlyOpenEntry = new RecentlyOpenEntry;
		pRecentlyOpenEntry->m_strPath = strIMGPath;
		addEntry(pRecentlyOpenEntry);
	}

	if (uiRecentlyOpenedCount == 0)
	{
		AppendMenu(getIMGF()->m_hSubMenu_File_OpenRecent, MF_STRING | MF_DISABLED, 1881, CLocalizationManager::get()->getTranslatedTextW("Menu_RecentlyOpenFiles_NoFiles").c_str());
	}

	AppendMenu(getIMGF()->m_hSubMenu_File_OpenRecent, MF_STRING, 1880, CLocalizationManager::get()->getTranslatedTextW("Menu_RecentlyOpenFiles_Clear").c_str());
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

	strPath = CString2::replace(strPath, "/", "\\");

	RecentlyOpenEntry *pRecentlyOpenEntry = new RecentlyOpenEntry;
	pRecentlyOpenEntry->m_strPath = strPath;
	addEntry(pRecentlyOpenEntry);

	uint32 uiRecentlyOpenedMaxCount = 15;
	uint32 uiRecentlyOpenedCount = CString2::toUint32(CINIManager::getItem(AppDataPath::getRecentlyOpenedPath(), "RecentlyOpened", "Count"));

	if (uiRecentlyOpenedCount == uiRecentlyOpenedMaxCount)
	{
		for (uint32 i = 2; i <= uiRecentlyOpenedMaxCount; i++)
		{
			string strIMGPath2 = CINIManager::getItem(AppDataPath::getRecentlyOpenedPath(), "RecentlyOpened", CString2::toString(i));
			CINIManager::setItem(AppDataPath::getRecentlyOpenedPath(), "RecentlyOpened", CString2::toString(i - 1), strIMGPath2);
		}
		CINIManager::setItem(AppDataPath::getRecentlyOpenedPath(), "RecentlyOpened", CString2::toString(uiRecentlyOpenedMaxCount), strPath);
	}
	else
	{
		CINIManager::setItem(AppDataPath::getRecentlyOpenedPath(), "RecentlyOpened", "Count", CString2::toString(uiRecentlyOpenedCount + 1));
		CINIManager::setItem(AppDataPath::getRecentlyOpenedPath(), "RecentlyOpened", CString2::toString(uiRecentlyOpenedCount + 1), strPath);
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

	uint32 uiRecentlyOpenedCount = CString2::toUint32(CINIManager::getItem(AppDataPath::getRecentlyOpenedPath(), "RecentlyOpened", "Count"));
	for (uint32 i = 1; i <= uiRecentlyOpenedCount; i++)
	{
		CINIManager::removeItem(AppDataPath::getRecentlyOpenedPath(), "RecentlyOpened", CString2::toString(i));
	}
	CINIManager::setItem(AppDataPath::getRecentlyOpenedPath(), "RecentlyOpened", "Count", 0);

	loadRecentlyOpenEntries();
	*/
}

void					RecentlyOpenManager::removeRecentlyOpenEntry(RecentlyOpenEntry *pRecentlyOpenEntry)
{
	uint32 uiRecentlyOpenedIndex = getRecentlyOpenedFileIndex(pRecentlyOpenEntry->getPath());
	CINIManager::removeItem(AppDataPath::getRecentlyOpenedPath(), "RecentlyOpened", CString2::toString(uiRecentlyOpenedIndex));

	uint32 uiRecentlyOpenedCount = CString2::toUint32(CINIManager::getItem(AppDataPath::getRecentlyOpenedPath(), "RecentlyOpened", "Count"));
	for (uint32 i = uiRecentlyOpenedIndex; i <= uiRecentlyOpenedCount; i++)
	{
		string strIMGPath2 = CINIManager::getItem(AppDataPath::getRecentlyOpenedPath(), "RecentlyOpened", CString2::toString(i + 1));
		CINIManager::setItem(AppDataPath::getRecentlyOpenedPath(), "RecentlyOpened", CString2::toString(i), strIMGPath2);
	}
	CINIManager::setItem(AppDataPath::getRecentlyOpenedPath(), "RecentlyOpened", "Count", CString2::toString(uiRecentlyOpenedCount - 1));

	removeEntry(pRecentlyOpenEntry);
}

uint32			RecentlyOpenManager::getRecentlyOpenedFileIndex(string strIMGPath)
{
	uint32 uiRecentlyOpenedCount = CString2::toUint32(CINIManager::getItem(AppDataPath::getRecentlyOpenedPath(), "RecentlyOpened", "Count"));
	for (uint32 i = 1; i <= uiRecentlyOpenedCount; i++)
	{
		string strIMGPath2 = CINIManager::getItem(AppDataPath::getRecentlyOpenedPath(), "RecentlyOpened", CString2::toString(i));
		if (strIMGPath2 == strIMGPath)
		{
			return i;
		}
	}
	return -1;
}

RecentlyOpenEntry*		RecentlyOpenManager::getRecentlyOpenEntryByPath(string strPath)
{
	strPath = CString2::toUpperCase(strPath);
	strPath = CString2::replace(strPath, "\\", "/");
	for (auto pRecentlyOpenEntry : getEntries())
	{
		if (CString2::replace(CString2::toUpperCase(pRecentlyOpenEntry->m_strPath), "\\", "/") == strPath)
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
	uint32 uiRecentlyOpenedCount = CString2::toUint32(CINIManager::getItem(AppDataPath::getRecentlyOpenedPath(), "RecentlyOpened", "Count"));
	if (uiRecentlyOpenedCount == 0)
	{
		return "";
	}

	string strIMGPath = CINIManager::getItem(AppDataPath::getRecentlyOpenedPath(), "RecentlyOpened", CString2::toString(uiRecentlyOpenedCount));
	return strIMGPath;
}

void					RecentlyOpenManager::moveRecentlyOpenEntryToTop(string strIMGPath)
{
	removeRecentlyOpenEntry(getRecentlyOpenEntryByPath(strIMGPath));
	addRecentlyOpenEntry(strIMGPath);
}