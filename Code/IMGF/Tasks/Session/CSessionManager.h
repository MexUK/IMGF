#pragma once

#include "nsimgf.h"
#include "Object/CManager.h"
#include "CSession.h"
#include "Pool/CVectorPool.h"
#include <string>
#include <vector>
#include <unordered_map>

class imgf::CSessionManager : public bxcf::CManager, public bxcf::CVectorPool<CSession*>
{
public:
	void			init(void);
	void			uninit(void);
	
	void			loadSessions(void);
	void			unloadSessions(void);

	CSession*		addSession(std::string strSessionName, std::vector<std::string>& vecPaths);
	void			removeSession(CSession *pSession);
	CSession*		getSessionByName(std::string strSessionName);
	
	std::unordered_map<uint32, std::string>&		getSessionsContainer(void) { return m_umapSessions; }
	
private:
	std::unordered_map<uint32, std::string>			m_umapSessions;
};