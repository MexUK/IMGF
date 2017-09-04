#pragma once

#include "nsbxgi.h"
#include "Format/DAT/Path/Entries/Fastman92/NodeAddress.h"

struct bxgi::DATEntry_Paths_Fastman92_NaviNode
{
	__int16 posX;  // deprecated field
	__int16 posY;  // deprecated field
	NodeAddress info;
	char dirX;
	char dirY;
	uint32 m_dwFlags;
};