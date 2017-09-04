#pragma once

#include "nsbxgi.h"

#pragma pack(push, 1)
struct bxgi::DATEntry_Paths_Default_PathNode
{
	uint32			m_uiMemoryAddress; // unused
	uint32			m_uiZero; // unused
	int16			m_iPosition[3];
	int16			m_iUnknown1;
	uint16			m_usLinkId;
	uint16			m_usAreaId;
	uint16			m_usNodeId;
	uint8			m_ucPathWidth;
	uint8			m_ucNodeType;
	uint32			m_uiFlags;
};
#pragma pack(pop)