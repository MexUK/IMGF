#pragma once

#include "nsbxgi.h"
#include "Format/CFormatManager.h"
#include "Object/CSingleton.h"
#include "Type/Vector/Vec2f.h"
#include "Game/EPlatformedGame.h"
#include <vector>

class bxgi::CDATPathFormat;
struct bxgi::CDATEntry_Paths_General_PathNode;
struct bxgi::CDATEntry_Paths_General_NaviNode;

class bxgi::CDATPathManager : public bxcf::CFormatManager<bxgi::CDATPathFormat>, public bxcf::CSingleton<CDATPathManager>
{
public:
	CDATPathManager(void);

	void						init(void);
	void						uninit(void);

	static uint32		getAreaIdFromPosition(bxcf::Vec2f& vecPosition, bxcf::Vec2f& vecMapRangeMin, bxcf::Vec2f& vecMapRangeMax, bxcf::Vec2f& vecAreaSize);
	static uint32		getTileCount(bxcf::Vec2f& vecMapRangeMin, bxcf::Vec2f& vecMapRangeMax, bxcf::Vec2f& vecAreaSize);

	static bool					findPathNode(std::vector<bxgi::CDATPathFormat*>& veCDATFormatPaths, bxgi::CDATEntry_Paths_General_PathNode& pathNodeToFind, uint32& uiAreaId_Out, uint32& uiNodeId_Out);
	static bool					findNaviNode(std::vector<bxgi::CDATPathFormat*>& veCDATFormatPaths, bxgi::CDATEntry_Paths_General_NaviNode& naviNodeToFind, uint32& uiAreaId_Out, uint32& uiNodeId_Out);
	static bxgi::CDATEntry_Paths_General_PathNode					getLowestPathNode(std::vector<bxgi::CDATEntry_Paths_General_PathNode>& vecPathNodes);
	static std::vector<bxgi::CDATEntry_Paths_General_PathNode>	getTargetPathNodesForNaviNode(std::vector<bxgi::CDATPathFormat*> veCDATFormats, bxgi::CDATEntry_Paths_General_NaviNode& naviNode, uint32 uiNaviNodeAreaId, uint32 uiNaviNodeNodeId, uint32& uiLinkId_Out);
};