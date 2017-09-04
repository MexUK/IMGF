#pragma once

#include "nsbxgi.h"
#include "Type/Types.h"

enum bxgi::EGameFlag : uint8
{
	GAME_FLAG_UNKNOWN	= 0,
	GAME_FLAG_GTA_III	= 1,
	GAME_FLAG_GTA_VC	= 2,
	GAME_FLAG_GTA_SA	= 4,
	GAME_FLAG_GTA_IV	= 8
};