#pragma once

#include "nsbxgi.h"
#include "Type/Types.h"
#include "EDATPathFormat.h"
#include <string>

// default format file structures
#pragma pack(push, 1)
struct bxgi::CDATEntry_Paths_Default_Header
{
	uint32			m_uiPathNodeCount;
	uint32			m_uiVehicleNodeCount;
	uint32			m_uiPedNodeCount;
	uint32			m_uiNaviNodeCount;
	uint32			m_uiLinkCount;
};
#pragma pack(pop)

#pragma pack(push, 1)
struct bxgi::CDATEntry_Paths_Default_PathNode
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

#pragma pack(push, 1)
struct bxgi::CDATEntry_Paths_Default_NaviNode
{
	int16			m_iPosition[2];
	uint16			m_usAreaId;
	uint16			m_usNodeId;
	uint8			m_ucDirection[2];
	uint32			m_uiFlags;
};
#pragma pack(pop)

#pragma pack(push, 1)
struct bxgi::CDATEntry_Paths_Default_Link
{
	uint16			m_usAreaId;
	uint16			m_usNodeId;
};
#pragma pack(pop)

#pragma pack(push, 1)
struct bxgi::CDATEntry_Paths_Default_NaviLink
{
	uint16			m_usData; // lower 10 bit are the Navi Node ID, upper 6 bit the corresponding Area ID
};
#pragma pack(pop)

#pragma pack(push, 1)
struct bxgi::CDATEntry_Paths_Default_LinkLength
{
	uint8			m_ucLength;
};
#pragma pack(pop)

// default format wrapper structures
struct bxgi::CDATEntry_Paths_Default_Link_Wrapper
{
	uint16			m_usAreaId;
	uint16			m_usNodeId;
	uint16			m_usNaviNodeData; // lower 10 bit are the Navi Node ID, upper 6 bit the corresponding Area ID
	uint8			m_ucLinkLength;
};

// fastman92 format file structures
class bxgi::CompressedVector
{
public:
	signed __int16 x;
	signed __int16 y;
	signed __int16 z;
};

class bxgi::CompressedVector_extended
{
public:
	signed __int32 x;
	signed __int32 y;
	signed __int32 z;
};

struct bxgi::CNodeAddress
{
	unsigned __int16 areaId;
	unsigned __int16 nodeId;
};

struct bxgi::CDATEntry_Paths_Fastman92_Header
{
	uint32			m_uiFourCC; // 0xFFFFFFFF
	std::string		m_strFormat; // FM92
	uint8			m_ucNicknameLength;
	std::string		m_strNickname; // char					m_szNickname[m_ucNicknameLength];
	std::string		m_strFormatVersion;
	uint32			m_uiPathNodeCount;
	uint32			m_uiVehicleNodeCount;
	uint32			m_uiPedNodeCount;
	uint32			m_uiNaviNodeCount;
	uint32			m_uiLinkCount;
};

struct bxgi::CDATEntry_Paths_Fastman92_PathNode
{
	CDATEntry_Paths_Fastman92_PathNode *m_pPrev;
	CDATEntry_Paths_Fastman92_PathNode **m_ppNext;
	CompressedVector m_posn;  // deprecated field
	__int16 m_wSearchList;
	__int16 m_wConnectedNodesStartId;
	__int16 m_wAreaId;
	__int16 m_wNodeId;
	char m_nPathWidth;
	char m_nNodeType;
	uint32 m_dwFlags;
};

struct bxgi::CDATEntry_Paths_Fastman92_PathNode_extended : public CDATEntry_Paths_Fastman92_PathNode
{
	CompressedVector_extended m_extended_posn;
};

struct bxgi::CDATEntry_Paths_Fastman92_NaviNode
{
	__int16 posX;  // deprecated field
	__int16 posY;  // deprecated field
	CNodeAddress info;
	char dirX;
	char dirY;
	uint32 m_dwFlags;
};

struct bxgi::CDATEntry_Paths_Fastman92_NaviNode_extended : public CDATEntry_Paths_Fastman92_NaviNode
{
	signed __int32 extended_posX;
	signed __int32 extended_posY;
};

struct bxgi::CDATEntry_Paths_Fastman92_Link
{
	uint16			m_usAreaId;
	uint16			m_usNodeId;
};

struct bxgi::CDATEntry_Paths_Fastman92_NaviLink
{
	uint32			m_uiData; // lower 16 bit are the Navi Node ID, upper 16 bit the corresponding Area ID
};

struct bxgi::CDATEntry_Paths_Fastman92_LinkLength
{
	uint8			m_ucLength;
};

struct bxgi::CDATEntry_Paths_Fastman92_PathIntersectionFlags
{
	//uint8			m_bRoadCross : 1;
	//uint8			m_bPedTrafficLight : 1;
	uint8			m_ucData;
};

// general format file structures
struct bxgi::CDATEntry_Paths_General_Header
{
	EDATPathFormat		m_ePathsFormat;
	uint32				m_uiPathNodeCount;
	uint32				m_uiVehicleNodeCount;
	uint32				m_uiPedNodeCount;
	uint32				m_uiNaviNodeCount;
	uint32				m_uiLinkCount;
};

struct bxgi::CDATEntry_Paths_General_PathNode
{
	bool								m_bIsVehiclePathNode;
	CDATEntry_Paths_Default_PathNode*	m_pPrev;
	CDATEntry_Paths_Default_PathNode**	m_ppNext;
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

struct bxgi::CDATEntry_Paths_General_NaviNode
{
	int32						m_iPosition[2];
	char						m_ucDirection[2];
	char						m_ucPathNodeWidth;
	uint32						m_uiFlags;
	uint16						m_usTargetNode_AreaId;
	uint16						m_usTargetNode_NodeId;

	//uint32					m_uiTargetNode_NewAreaId;
	//uint32					m_uiTargetNode_NewNodeId;

	uint32						m_uiTargetNode_OldAreaId;
	uint32						m_uiTargetNode_OldNodeId;
};

struct bxgi::CDATEntry_Paths_General_Link
{
	uint16						m_usAreaId;
	uint16						m_usNodeId;
	uint16						m_usNaviNodeId;
	uint16						m_usNaviAreaId;
	uint8						m_ucLength;
	uint8						m_ucPathIntersectionFlags;
};