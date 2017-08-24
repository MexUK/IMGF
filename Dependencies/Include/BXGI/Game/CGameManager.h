#ifndef CGameManager_H
#define CGameManager_H

#include "bxgi.h"
#include "bxcf.h"
#include "Object/CManager.h"
#include "Object/CSingleton.h"
#include "Pool/CVectorPool.h"
#include "Game/CGame.h"
#include "Games/eGame.h"
#include <string>

class bxgi::CGameManager : public bxcf::CManager, public bxcf::CSingleton<bxgi::CGameManager>, public bxcf::CVectorPool<bxgi::CGame*>
{
public:
	void											init(void);
	void											uninit(void);

	std::string										getGameName(bxgi::eGame eGameValue);

private:
	void											initGames(void);
	void											uninitGames(void);
};

#endif