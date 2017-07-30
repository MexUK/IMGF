#ifndef eGameFlag_H
#define eGameFlag_H

#include "bxcf.h"

enum bxcf::eGameFlag : uint8
{
	GAME_FLAG_UNKNOWN	= 0,
	GAME_FLAG_GTA_III	= 1,
	GAME_FLAG_GTA_VC	= 2,
	GAME_FLAG_GTA_SA	= 4,
	GAME_FLAG_GTA_IV	= 8
};

#endif