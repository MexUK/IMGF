#pragma once

#include "nsbxgi.h"

#pragma pack(push, 1)
struct bxgi::DATEntry_Paths_Default_NaviLink
{
	uint16			m_usData; // lower 10 bit are the Navi Node ID, upper 6 bit the corresponding Area ID
};
#pragma pack(pop)