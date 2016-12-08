#ifndef CGameManager_H
#define CGameManager_H

#include "mcore.h"
#include "Object/CManager.h"
#include "Object/CSingleton.h"
#include "Pool/CVectorPool.h"
#include "CGame.h"
#include "Collection/Games/eGame.h"
#include <string>

class mcore::CGameManager : public mcore::CManager, public mcore::CSingleton<mcore::CGameManager>, public mcore::CVectorPool<mcore::CGame*>
{
public:
	void											init(void);
	void											uninit(void);

	std::string										getGameName(mcore::eGame eGameValue);

private:
	void											initGames(void);
	void											uninitGames(void);
};

#endif