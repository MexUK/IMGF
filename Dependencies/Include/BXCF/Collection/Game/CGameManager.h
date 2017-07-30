#ifndef CGameManager_H
#define CGameManager_H

#include "bxcf.h"
#include "Object/CManager.h"
#include "Object/CSingleton.h"
#include "Pool/CVectorPool.h"
#include "CGame.h"
#include "Collection/Games/eGame.h"
#include <string>

class bxcf::CGameManager : public bxcf::CManager, public bxcf::CSingleton<bxcf::CGameManager>, public bxcf::CVectorPool<bxcf::CGame*>
{
public:
	void											init(void);
	void											uninit(void);

	std::string										getGameName(bxcf::eGame eGameValue);

private:
	void											initGames(void);
	void											uninitGames(void);
};

#endif