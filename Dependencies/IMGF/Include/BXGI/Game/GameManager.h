#pragma once

#include "nsbxgi.h"
#include "nsbxcf.h"
#include "Object/Manager.h"
#include "Object/Singleton.h"
#include "Pool/VectorPool.h"
#include "Game/Game.h"
#include "Game/EGame.h"
#include "Game/PlatformedGame.h"
#include "Game/EPlatformedGame.h"
#include <string>

class bxgi::GameManager : public bxcf::Manager, public bxcf::Singleton<bxgi::GameManager>, public bxcf::VectorPool<bxgi::Game*>
{
public:
	void											init(void);
	void											uninit(void);

	bxcf::VectorPool<bxgi::PlatformedGame*>&		getPlatformedGames(void) { return m_vecPlatformedGames; }

	bxgi::Game*									addGame(bxgi::EGame uiGameId, std::string strGameName);
	bxgi::PlatformedGame*							addPlatformedGame(bxgi::EPlatformedGame uiPlatformedGameId, std::string strGameName);

	std::string										getGameName(bxgi::EGame uiGameId);
	std::string										getPlatformedGameText(bxgi::EPlatformedGame uiPlatformedGameId);

private:
	void											initGames(void);
	void											uninitGames(void);

	void											initPlatformedGames(void);
	void											uninitPlatformedGames(void);

private:
	bxcf::VectorPool<bxgi::PlatformedGame*>		m_vecPlatformedGames;
};