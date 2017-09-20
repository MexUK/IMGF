#include "SessionManager.h"
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
#include "GUI/Layer/Layers/MainLayer/MainLayer.h"
#include "Control/Controls/Menu.h"
#include "Event/EInputEvent.h"

using namespace std;
using namespace bxcf;
using namespace bxgx;
using namespace bxgx::events;
using namespace imgf;

// initialization
void		SessionManager::init(void)
{
	bindEvent(BXGX_READY, &SessionManager::loadSessions);
}
void		SessionManager::uninit(void)
{
	unloadSessions();
}

// load/unload file group
void		SessionManager::loadSessions(void)
{
	removeAllEntries();

	Menu *pMenu = getIMGF()->getWindowManager()->getMainWindow()->getMainLayer()->m_pFileGroupMenu;

	pMenu->removeAllMenuItems();
	getIMGF()->getSessionManager()->getSessionsContainer().clear();

	uint32 uiSessionCount = String::toUint32(INIManager::getItem(AppDataPath::getSessionsPath(), "Sessions", "Count"));
	for (int32 i = uiSessionCount; i >= 1; i--)
	{
		string strIMGPaths = INIManager::getItem(AppDataPath::getSessionsPath(), "Sessions", i);
		
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
		pMenu->addMenuItem(strMenuItemText, 1900 + i);

		getIMGF()->getSessionManager()->getSessionsContainer()[1900 + i] = strIMGPaths;

		Session *pSession = new Session;
		pSession->m_strName = strSessionName;
		pSession->m_vecPaths = vecIMGPaths;
		addEntry(pSession);
	}

	if (uiSessionCount == 0)
	{
		pMenu->addMenuItem("There are currently no file groups.", 1981);
	}
}

void		SessionManager::unloadSessions(void)
{
	removeAllEntries();
}

// add/remove file group
Session*	SessionManager::addSession(string strSessionName, vector<string>& vecPaths)
{
	uint32 uiSessionIndex = getEntryCount() + 1;

	Session *pSession = new Session;
	pSession->m_strName = strSessionName;
	pSession->m_vecPaths = vecPaths;
	addEntry(pSession);

	INIManager::setItem(AppDataPath::getSessionsPath(), "Sessions", "Count", String::toString(uiSessionIndex));
	INIManager::setItem(AppDataPath::getSessionsPath(), "Sessions", String::toString(uiSessionIndex), pSession->serialize());
	
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
	uint32 uiSessionCount = String::toUint32(INIManager::getItem(AppDataPath::getSessionsPath(), "Sessions", "Count"));
	for (uint32 i = uiSessionIndex; i < uiSessionCount; i++)
	{
		string strIMGPaths2 = INIManager::getItem(AppDataPath::getSessionsPath(), "Sessions", i + 1);
		INIManager::setItem(AppDataPath::getSessionsPath(), "Sessions", i, strIMGPaths2);
	}
	
	// remove session with highest ID in file?
	INIManager::removeItem(AppDataPath::getSessionsPath(), "Sessions", uiSessionCount);
	
	// update session count to file
	INIManager::setItem(AppDataPath::getSessionsPath(), "Sessions", "Count", String::toString(uiSessionCount - 1));
}

// fetch file group
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