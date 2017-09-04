#pragma once

#include "nsbxgi.h"
#include "Format/DAT/Path/EDATPathFormat.h"

struct bxgi::DATEntry_Paths_General_Header
{
	EDATPathFormat		m_uiPathsFormat;
	uint32				m_uiPathNodeCount;
	uint32				m_uiVehicleNodeCount;
	uint32				m_uiPedNodeCount;
	uint32				m_uiNaviNodeCount;
	uint32				m_uiLinkCount;
};