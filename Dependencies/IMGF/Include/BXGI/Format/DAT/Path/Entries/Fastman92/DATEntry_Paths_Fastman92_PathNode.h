#pragma once

#include "nsbxgi.h"
#include "Format/DAT/Path/Entries/CompressedVector.h"

struct bxgi::DATEntry_Paths_Fastman92_PathNode
{
	DATEntry_Paths_Fastman92_PathNode *m_pPrev;
	DATEntry_Paths_Fastman92_PathNode **m_ppNext;
	CompressedVector m_posn;  // deprecated field
	__int16 m_wSearchList;
	__int16 m_wConnectedNodesStartId;
	__int16 m_wAreaId;
	__int16 m_wNodeId;
	char m_nPathWidth;
	char m_nNodeType;
	uint32 m_dwFlags;
};