#pragma once

#include "nsbxgi.h"
#include "nsbxcf.h"
#include "Object/CManager.h"
#include "Object/CSingleton.h"
#include "Pool/CVectorPool.h"
#include "Game/CGame.h"
#include "Game/EGame.h"
#include "Game/CPlatformedGame.h"
#include "Game/EPlatformedGame.h"
#include <string>

class bxgi::CGameManager : public bxcf::CManager, public bxcf::CSingleton<bxgi::CGameManager>, public bxcf::CVectorPool<bxgi::CGame*>
{
public:
	void											init(void);
	void											uninit(void);

	bxcf::CVectorPool<bxgi::CPlatformedGame*>&		getPlatformedGames(void) { return m_vecPlatformedGames; }

	bxgi::CGame*									addGame(bxgi::EGame uiGameId, std::string strGameName);
	bxgi::CPlatformedGame*							addPlatformedGame(bxgi::EPlatformedGame uiPlatformedGameId, std::string strGameName);

	std::string										getGameName(bxgi::EGame uiGameId);
	std::string										getPlatformedGameText(bxgi::EPlatformedGame uiPlatformedGameId);

private:
	void											initGames(void);
	void											uninitGames(void);

	void											initPlatformedGames(void);
	void											uninitPlatformedGames(void);

private:
	bxcf::CVectorPool<bxgi::CPlatformedGame*>		m_vecPlatformedGames;
};