#include "CSessionManager.h"
#include "Static/CString2.h"
#include "Static/CPath.h"
#include "Static/CStdVector.h"
#include "Globals.h"
#include "CIMGF.h"
#include "Format/IMG/Regular/CIMGEntry.h"
#include "Localization/CLocalizationManager.h"
#include "Format/Text/INI/CINIManager.h"
#include "Static/CAppDataPath.h"

using namespace std;
using namespace bxcf;

void		CSessionManager::init(void)
{
	loadSessions();
}
void		CSessionManager::uninit(void)
{
	unloadSessions();
}

void		CSessionManager::loadSessions(void)
{
	// todo 
	return;

	removeAllEntries();

	for (auto it : getIMGF()->getSessionManager()->getSessionsContainer())
	{
		// todo DeleteMenu(getIMGF()->m_hSubMenu_File_Sessions, it.first, 0);
	}
	getIMGF()->getSessionManager()->getSessionsContainer().clear();
	// todo DeleteMenu(getIMGF()->m_hSubMenu_File_Sessions, 1981, 0);

	uint32 uiSessionCount = CString2::toUint32(CINIManager::getItem(CAppDataPath::getSessionsPath(), "Sessions", "Count"));
	for (int32 i = uiSessionCount; i >= 1; i--)
	{
		string strIMGPaths = CINIManager::getItem(CAppDataPath::getSessionsPath(), "Sessions", i);
		
		deque<string> deqIMGPaths = CStdVector::convertVectorToDeque(CString2::split(strIMGPaths, "; "));
		string strSessionName = deqIMGPaths[0];
		deqIMGPaths.pop_front();
		uint32 j2 = deqIMGPaths.size();
		vector<string> vecIMGPaths;
		for (uint32 i2 = 0; i2 < j2; i2++)
		{
			vecIMGPaths.push_back(deqIMGPaths[i2]);
			deqIMGPaths[i2] = CPath::getFileName(deqIMGPaths[i2]);
		}
		// todo AppendMenu(getIMGF()->m_hSubMenu_File_Sessions, MF_STRING, 1900 + i, CString2::convertStdStringToStdWString(CString2::toString((uiSessionCount - i) + 1) + ") " + CString2::escapeMenuText(strSessionName) + " (" + CString2::toString(j2) + " tab" + (j2 == 1 ? "" : "s") + ")").c_str());

		getIMGF()->getSessionManager()->getSessionsContainer()[1900 + i] = strIMGPaths;

		CSession *pSession = new CSession;
		pSession->m_strName = strSessionName;
		pSession->m_vecPaths = vecIMGPaths;
		addEntry(pSession);
	}

	if (uiSessionCount == 0)
	{
		// todo AppendMenu(getIMGF()->m_hSubMenu_File_Sessions, MF_STRING | MF_DISABLED, 1981, CLocalizationManager::get()->getTranslatedTextW("Menu_Sessions_NoSessions").c_str());
	}
}
void		CSessionManager::unloadSessions(void)
{
	removeAllEntries();
}

CSession*	CSessionManager::addSession(string strSessionName, vector<string>& vecPaths)
{
	uint32 uiSessionIndex = getEntryCount() + 1;

	CSession *pSession = new CSession;
	pSession->m_strName = strSessionName;
	pSession->m_vecPaths = vecPaths;
	addEntry(pSession);

	CINIManager::setItem(CAppDataPath::getSessionsPath(), "Sessions", "Count", CString2::toString(uiSessionIndex));
	CINIManager::setItem(CAppDataPath::getSessionsPath(), "Sessions", uiSessionIndex, pSession->serialize());
	
	return pSession;
}

void		CSessionManager::removeSession(CSession *pSession)
{
	// fetch session index
	uint32 uiSessionIndex = getIndexByEntry(pSession);
	
	// remove session from memory and file
	removeEntry(pSession);
	CINIManager::removeItem(CAppDataPath::getSessionsPath(), "Sessions", uiSessionIndex);
	
	// shift other sessions with a higher ID down by 1 ID in file
	uint32 uiSessionCount = CString2::toUint32(CINIManager::getItem(CAppDataPath::getSessionsPath(), "Sessions", "Count"));
	for (uint32 i = uiSessionIndex; i < uiSessionCount; i++)
	{
		string strIMGPaths2 = CINIManager::getItem(CAppDataPath::getSessionsPath(), "Sessions", i + 1);
		CINIManager::setItem(CAppDataPath::getSessionsPath(), "Sessions", i, strIMGPaths2);
	}
	
	// remove session with highest ID in file?
	CINIManager::removeItem(CAppDataPath::getSessionsPath(), "Sessions", uiSessionCount);
	
	// update session count to file
	CINIManager::setItem(CAppDataPath::getSessionsPath(), "Sessions", "Count", CString2::toString(uiSessionCount - 1));
}

CSession*		CSessionManager::getSessionByName(string strSessionName)
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