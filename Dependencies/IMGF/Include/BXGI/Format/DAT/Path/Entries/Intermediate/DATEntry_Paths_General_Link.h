#pragma once

#include "nsbxgi.h"

struct bxgi::DATEntry_Paths_General_Link
{
	uint16						m_usAreaId;
	uint16						m_usNodeId;
	uint16						m_usNaviNodeId;
	uint16						m_usNaviAreaId;
	uint8						m_ucLength;
	uint8						m_ucPathIntersectionFlags;
};