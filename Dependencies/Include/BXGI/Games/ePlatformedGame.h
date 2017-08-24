#ifndef ePlatformedGame_H
#define ePlatformedGame_H

#include "bxgi.h"
#include "Type/Types.h"

enum bxgi::ePlatformedGame : uint16
{
	PLATFORMED_GAME_UNKNOWN			= 0, // not for storing in an int as a bit flag
	PLATFORMED_GAME_PC_GTA_III		= 1,
	PLATFORMED_GAME_PC_GTA_VC		= 2,
	PLATFORMED_GAME_PC_GTA_SA		= 4,
	PLATFORMED_GAME_PC_GTA_IV		= 8,
	PLATFORMED_GAME_PC_MANHUNT		= 16,
	PLATFORMED_GAME_PS2_BULLY		= 32,

	PLATFORMED_GAME_PC_SOL			= 64,

	PLATFORMED_GAME_ANDROID_GTA		= 128, // this is just temp here - coz its not really a game its a platform or something ...
	PLATFORMED_GAME_XBOX_GTA		= 256 // this is just temp here too
};

#endif