#pragma once

#include "nsbxgi.h"

struct bxgi::DATEntry_Paths_Default_Link_Wrapper
{
	uint16			m_usAreaId;
	uint16			m_usNodeId;
	uint16			m_usNaviNodeData; // lower 10 bit are the Navi Node ID, upper 6 bit the corresponding Area ID
	uint8			m_ucLinkLength;
};