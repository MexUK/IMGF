#pragma once

#include "nsimgf.h"
#include "Object/Manager.h"
#include "Session.h"
#include "Pool/VectorPool.h"
#include "Event/EventBindable.h"
#include <string>
#include <vector>
#include <unordered_map>

class imgf::SessionManager : public bxcf::Manager, public bxcf::VectorPool<Session*>, public bxcf::EventBindable
{
public:
	void			init(void);
	void			uninit(void);
	
	void			loadSessions(void);
	void			unloadSessions(void);

	Session*		addSession(std::string strSessionName, std::vector<std::string>& vecPaths);
	void			removeSession(Session *pSession);
	Session*		getSessionByName(std::string strSessionName);
	
	std::unordered_map<uint32, std::string>&		getSessionsContainer(void) { return m_umapSessions; }
	
private:
	std::unordered_map<uint32, std::string>			m_umapSessions;
};