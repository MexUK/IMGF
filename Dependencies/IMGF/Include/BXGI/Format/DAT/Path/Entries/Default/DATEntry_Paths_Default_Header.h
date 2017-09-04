#pragma once

#include "nsbxgi.h"

#pragma pack(push, 1)
struct bxgi::DATEntry_Paths_Default_Header
{
	uint32			m_uiPathNodeCount;
	uint32			m_uiVehicleNodeCount;
	uint32			m_uiPedNodeCount;
	uint32			m_uiNaviNodeCount;
	uint32			m_uiLinkCount;
};
#pragma pack(pop)