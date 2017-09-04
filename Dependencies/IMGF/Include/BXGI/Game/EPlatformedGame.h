#pragma once

#include "nsbxgi.h"
#include "Type/Types.h"

enum bxgi::EPlatformedGame : uint16
{
	UNKNOWN_PLATFORMED_GAME		= 0, // not for storing in an int as a bit flag
	PC_GTA_III					= 1,
	PC_GTA_VC					= 2,
	PC_GTA_SA					= 4,
	PC_GTA_IV					= 8,
	PC_MANHUNT					= 16,
	PS2_BULLY					= 32,

	PC_SOL						= 64,

	ANDROID_GTA		= 128, // this is just temp here - coz its not really a game its a platform or something ...
	XBOX_GTA		= 256 // this is just temp here too
};