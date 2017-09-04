#pragma once

#include "nsbxgi.h"

struct bxgi::DATEntry_Paths_General_NaviNode
{
	int32						m_iPosition[2];
	char						m_ucDirection[2];
	char						m_ucPathNodeWidth;
	uint32						m_uiFlags;
	uint16						m_usTargetNode_AreaId;
	uint16						m_usTargetNode_NodeId;

	uint32						m_uiTargetNode_OldAreaId;
	uint32						m_uiTargetNode_OldNodeId;
};