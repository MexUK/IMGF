#include "SessionManager.h"
#include "Static/String2.h"
#include "Static/Path.h"
#include "Static/StdVector.h"
#include "Globals.h"
#include "IMGF.h"
#include "Format/IMG/Regular/IMGEntry.h"
#include "Localization/LocalizationManager.h"
#include "Format/Text/INI/INIManager.h"
#include "Static/AppDataPath.h"

using namespace std;
using namespace bxcf;
using namespace imgf;

void		SessionManager::init(void)
{
	loadSessions();
}
void		SessionManager::uninit(void)
{
	unloadSessions();
}

void		SessionManager::loadSessions(void)
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

	uint32 uiSessionCount = String2::toUint32(INIManager::getItem(AppDataPath::getSessionsPath(), "Sessions", "Count"));
	for (int32 i = uiSessionCount; i >= 1; i--)
	{
		string strIMGPaths = INIManager::getItem(AppDataPath::getSessionsPath(), "Sessions", i);
		
		deque<string> deqIMGPaths = StdVector::convertVectorToDeque(String2::split(strIMGPaths, "; "));
		string strSessionName = deqIMGPaths[0];
		deqIMGPaths.pop_front();
		uint32 j2 = deqIMGPaths.size();
		vector<string> vecIMGPaths;
		for (uint32 i2 = 0; i2 < j2; i2++)
		{
			vecIMGPaths.push_back(deqIMGPaths[i2]);
			deqIMGPaths[i2] = Path::getFileName(deqIMGPaths[i2]);
		}
		// todo AppendMenu(getIMGF()->m_hSubMenu_File_Sessions, MF_STRING, 1900 + i, String2::convertStdStringToStdWString(String2::toString((uiSessionCount - i) + 1) + ") " + String2::escapeMenuText(strSessionName) + " (" + String2::toString(j2) + " tab" + (j2 == 1 ? "" : "s") + ")").c_str());

		getIMGF()->getSessionManager()->getSessionsContainer()[1900 + i] = strIMGPaths;

		Session *pSession = new Session;
		pSession->m_strName = strSessionName;
		pSession->m_vecPaths = vecIMGPaths;
		addEntry(pSession);
	}

	if (uiSessionCount == 0)
	{
		// todo AppendMenu(getIMGF()->m_hSubMenu_File_Sessions, MF_STRING | MF_DISABLED, 1981, LocalizationManager::get()->getTranslatedTextW("Menu_Sessions_NoSessions").c_str());
	}
}
void		SessionManager::unloadSessions(void)
{
	removeAllEntries();
}

Session*	SessionManager::addSession(string strSessionName, vector<string>& vecPaths)
{
	uint32 uiSessionIndex = getEntryCount() + 1;

	Session *pSession = new Session;
	pSession->m_strName = strSessionName;
	pSession->m_vecPaths = vecPaths;
	addEntry(pSession);

	INIManager::setItem(AppDataPath::getSessionsPath(), "Sessions", "Count", String2::toString(uiSessionIndex));
	INIManager::setItem(AppDataPath::getSessionsPath(), "Sessions", uiSessionIndex, pSession->serialize());
	
	return pSession;
}

void		SessionManager::removeSession(Session *pSession)
{
	// fetch session index
	uint32 uiSessionIndex = getIndexByEntry(pSession);
	
	// remove session from memory and file
	removeEntry(pSession);
	INIManager::removeItem(AppDataPath::getSessionsPath(), "Sessions", uiSessionIndex);
	
	// shift other sessions with a higher ID down by 1 ID in file
	uint32 uiSessionCount = String2::toUint32(INIManager::getItem(AppDataPath::getSessionsPath(), "Sessions", "Count"));
	for (uint32 i = uiSessionIndex; i < uiSessionCount; i++)
	{
		string strIMGPaths2 = INIManager::getItem(AppDataPath::getSessionsPath(), "Sessions", i + 1);
		INIManager::setItem(AppDataPath::getSessionsPath(), "Sessions", i, strIMGPaths2);
	}
	
	// remove session with highest ID in file?
	INIManager::removeItem(AppDataPath::getSessionsPath(), "Sessions", uiSessionCount);
	
	// update session count to file
	INIManager::setItem(AppDataPath::getSessionsPath(), "Sessions", "Count", String2::toString(uiSessionCount - 1));
}

Session*		SessionManager::getSessionByName(string strSessionName)
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