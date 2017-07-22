#ifndef CGameManager_H
#define CGameManager_H

#include "bxa.h"
#include "Object/CManager.h"
#include "Object/CSingleton.h"
#include "Pool/CVectorPool.h"
#include "CGame.h"
#include "Collection/Games/eGame.h"
#include <string>

class bxa::CGameManager : public bxa::CManager, public bxa::CSingleton<bxa::CGameManager>, public bxa::CVectorPool<bxa::CGame*>
{
public:
	void											init(void);
	void											uninit(void);

	std::string										getGameName(bxa::eGame eGameValue);

private:
	void											initGames(void);
	void											uninitGames(void);
};

#endif