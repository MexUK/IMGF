#pragma once

#include "nsbxgi.h"

#pragma pack(push, 1)
struct bxgi::DATEntry_Paths_Default_NaviNode
{
	int16			m_iPosition[2];
	uint16			m_usAreaId;
	uint16			m_usNodeId;
	uint8			m_ucDirection[2];
	uint32			m_uiFlags;
};
#pragma pack(pop)