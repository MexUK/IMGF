#include "CRecentlyOpenManager.h"
#include "Static/CString2.h"
#include "Static/CPath.h"
#include "Static/CStdVector.h"
#include "Static/CRegistry.h"
#include "Globals.h"
#include "CIMGF.h"
#include "Static/CDebug.h"
#include "Format/IMG/Regular/CIMGEntry.h"
#include "Localization/CLocalizationManager.h"
#include "Window/CWindow.h"
#include "Format/Text/INI/CINIManager.h"
#include "Static/CAppDataPath.h"

using namespace std;
using namespace bxcf;
using namespace imgf;

void					CRecentlyOpenManager::init(void)
{
	loadRecentlyOpenEntries();
}
void					CRecentlyOpenManager::uninit(void)
{
	unloadRecentlyOpenEntries();
}

void					CRecentlyOpenManager::loadRecentlyOpenEntries(void)
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

	uint32 uiRecentlyOpenedCount = CString2::toUint32(CINIManager::getItem(CAppDataPath::getRecentlyOpenedPath(), "RecentlyOpened", "Count"));
	for (int32 i = uiRecentlyOpenedCount; i >= 1; i--)
	{
		string strIMGPath = CINIManager::getItem(CAppDataPath::getRecentlyOpenedPath(), "RecentlyOpened", CString2::toString(i));

		AppendMenu(getIMGF()->m_hSubMenu_File_OpenRecent, MF_STRING, 1800 + i, CString2::convertStdStringToStdWString(CString2::toString((uiRecentlyOpenedCount - i) + 1) + ") " + strIMGPath).c_str());

		getIMGF()->getRecentlyOpenManager()->getRecentlyOpenedFilesContainer()[1800 + i] = strIMGPath;

		CRecentlyOpenEntry *pRecentlyOpenEntry = new CRecentlyOpenEntry;
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
void					CRecentlyOpenManager::unloadRecentlyOpenEntries(void)
{
	removeAllEntries();
}

CRecentlyOpenEntry*		CRecentlyOpenManager::addRecentlyOpenEntry(string strPath)
{
	if (doesRecentlyOpenEntryExist(strPath))
	{
		moveRecentlyOpenEntryToTop(strPath);
		loadRecentlyOpenEntries();
		CRecentlyOpenEntry *pRecentlyOpenEntry = getRecentlyOpenEntryByPath(strPath);
		return pRecentlyOpenEntry;
	}

	strPath = CString2::replace(strPath, "/", "\\");

	CRecentlyOpenEntry *pRecentlyOpenEntry = new CRecentlyOpenEntry;
	pRecentlyOpenEntry->m_strPath = strPath;
	addEntry(pRecentlyOpenEntry);

	uint32 uiRecentlyOpenedMaxCount = 15;
	uint32 uiRecentlyOpenedCount = CString2::toUint32(CINIManager::getItem(CAppDataPath::getRecentlyOpenedPath(), "RecentlyOpened", "Count"));

	if (uiRecentlyOpenedCount == uiRecentlyOpenedMaxCount)
	{
		for (uint32 i = 2; i <= uiRecentlyOpenedMaxCount; i++)
		{
			string strIMGPath2 = CINIManager::getItem(CAppDataPath::getRecentlyOpenedPath(), "RecentlyOpened", CString2::toString(i));
			CINIManager::setItem(CAppDataPath::getRecentlyOpenedPath(), "RecentlyOpened", CString2::toString(i - 1), strIMGPath2);
		}
		CINIManager::setItem(CAppDataPath::getRecentlyOpenedPath(), "RecentlyOpened", CString2::toString(uiRecentlyOpenedMaxCount), strPath);
	}
	else
	{
		CINIManager::setItem(CAppDataPath::getRecentlyOpenedPath(), "RecentlyOpened", "Count", CString2::toString(uiRecentlyOpenedCount + 1));
		CINIManager::setItem(CAppDataPath::getRecentlyOpenedPath(), "RecentlyOpened", CString2::toString(uiRecentlyOpenedCount + 1), strPath);
	}

	return pRecentlyOpenEntry;
}

void					CRecentlyOpenManager::removeRecentlyOpenedEntries(void)
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

	uint32 uiRecentlyOpenedCount = CString2::toUint32(CINIManager::getItem(CAppDataPath::getRecentlyOpenedPath(), "RecentlyOpened", "Count"));
	for (uint32 i = 1; i <= uiRecentlyOpenedCount; i++)
	{
		CINIManager::removeItem(CAppDataPath::getRecentlyOpenedPath(), "RecentlyOpened", CString2::toString(i));
	}
	CINIManager::setItem(CAppDataPath::getRecentlyOpenedPath(), "RecentlyOpened", "Count", 0);

	loadRecentlyOpenEntries();
	*/
}

void					CRecentlyOpenManager::removeRecentlyOpenEntry(CRecentlyOpenEntry *pRecentlyOpenEntry)
{
	uint32 uiRecentlyOpenedIndex = getRecentlyOpenedFileIndex(pRecentlyOpenEntry->getPath());
	CINIManager::removeItem(CAppDataPath::getRecentlyOpenedPath(), "RecentlyOpened", CString2::toString(uiRecentlyOpenedIndex));

	uint32 uiRecentlyOpenedCount = CString2::toUint32(CINIManager::getItem(CAppDataPath::getRecentlyOpenedPath(), "RecentlyOpened", "Count"));
	for (uint32 i = uiRecentlyOpenedIndex; i <= uiRecentlyOpenedCount; i++)
	{
		string strIMGPath2 = CINIManager::getItem(CAppDataPath::getRecentlyOpenedPath(), "RecentlyOpened", CString2::toString(i + 1));
		CINIManager::setItem(CAppDataPath::getRecentlyOpenedPath(), "RecentlyOpened", CString2::toString(i), strIMGPath2);
	}
	CINIManager::setItem(CAppDataPath::getRecentlyOpenedPath(), "RecentlyOpened", "Count", CString2::toString(uiRecentlyOpenedCount - 1));

	removeEntry(pRecentlyOpenEntry);
}

uint32			CRecentlyOpenManager::getRecentlyOpenedFileIndex(string strIMGPath)
{
	uint32 uiRecentlyOpenedCount = CString2::toUint32(CINIManager::getItem(CAppDataPath::getRecentlyOpenedPath(), "RecentlyOpened", "Count"));
	for (uint32 i = 1; i <= uiRecentlyOpenedCount; i++)
	{
		string strIMGPath2 = CINIManager::getItem(CAppDataPath::getRecentlyOpenedPath(), "RecentlyOpened", CString2::toString(i));
		if (strIMGPath2 == strIMGPath)
		{
			return i;
		}
	}
	return -1;
}

CRecentlyOpenEntry*		CRecentlyOpenManager::getRecentlyOpenEntryByPath(string strPath)
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

bool					CRecentlyOpenManager::doesRecentlyOpenEntryExist(string strPath)
{
	return getRecentlyOpenEntryByPath(strPath) != nullptr;
}

string					CRecentlyOpenManager::getLastOpenEntry(void)
{
	uint32 uiRecentlyOpenedCount = CString2::toUint32(CINIManager::getItem(CAppDataPath::getRecentlyOpenedPath(), "RecentlyOpened", "Count"));
	if (uiRecentlyOpenedCount == 0)
	{
		return "";
	}

	string strIMGPath = CINIManager::getItem(CAppDataPath::getRecentlyOpenedPath(), "RecentlyOpened", CString2::toString(uiRecentlyOpenedCount));
	return strIMGPath;
}

void					CRecentlyOpenManager::moveRecentlyOpenEntryToTop(string strIMGPath)
{
	removeRecentlyOpenEntry(getRecentlyOpenEntryByPath(strIMGPath));
	addRecentlyOpenEntry(strIMGPath);
}