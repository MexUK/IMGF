#pragma once

#include "Format/DAT/Path/Entries/Default/DATEntry_Paths_Default_PathNode.h"
#include "Format/DAT/Path/Entries/CompressedVector_extended.h"
#include "nsbxgi.h"

struct bxgi::DATEntry_Paths_General_PathNode
{
	bool								m_bIsVehiclePathNode;
	DATEntry_Paths_Default_PathNode*	m_pPrev;
	DATEntry_Paths_Default_PathNode**	m_ppNext;
	CompressedVector_extended			m_vecPosition;
	int16								m_wSearchList;
	int16								m_wConnectedNodesStartId;
	int32								m_wLinkId;
	int32								m_wAreaId;
	int32								m_wNodeId;
	uint8								m_ucPathWidth;
	uint8								m_ucNodeType;
	uint32								m_uiFlags;
};