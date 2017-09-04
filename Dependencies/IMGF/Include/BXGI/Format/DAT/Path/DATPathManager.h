#pragma once

#include "nsbxgi.h"
#include "Format/FormatManager.h"
#include "Object/Singleton.h"
#include "Type/Vector/Vec2f.h"
#include "Game/EPlatformedGame.h"
#include <vector>

class bxgi::DATPathFormat;
struct bxgi::DATEntry_Paths_General_PathNode;
struct bxgi::DATEntry_Paths_General_NaviNode;

class bxgi::DATPathManager : public bxcf::FormatManager<bxgi::DATPathFormat>, public bxcf::Singleton<DATPathManager>
{
public:
	DATPathManager(void);

	void						init(void);
	void						uninit(void);

	static uint32		getAreaIdFromPosition(bxcf::Vec2f& vecPosition, bxcf::Vec2f& vecMapRangeMin, bxcf::Vec2f& vecMapRangeMax, bxcf::Vec2f& vecAreaSize);
	static uint32		getTileCount(bxcf::Vec2f& vecMapRangeMin, bxcf::Vec2f& vecMapRangeMax, bxcf::Vec2f& vecAreaSize);

	static bool					findPathNode(std::vector<bxgi::DATPathFormat*>& veDATFormatPaths, bxgi::DATEntry_Paths_General_PathNode& pathNodeToFind, uint32& uiAreaId_Out, uint32& uiNodeId_Out);
	static bool					findNaviNode(std::vector<bxgi::DATPathFormat*>& veDATFormatPaths, bxgi::DATEntry_Paths_General_NaviNode& naviNodeToFind, uint32& uiAreaId_Out, uint32& uiNodeId_Out);
	static bxgi::DATEntry_Paths_General_PathNode					getLowestPathNode(std::vector<bxgi::DATEntry_Paths_General_PathNode>& vecPathNodes);
	static std::vector<bxgi::DATEntry_Paths_General_PathNode>	getTargetPathNodesForNaviNode(std::vector<bxgi::DATPathFormat*> veDATFormats, bxgi::DATEntry_Paths_General_NaviNode& naviNode, uint32 uiNaviNodeAreaId, uint32 uiNaviNodeNodeId, uint32& uiLinkId_Out);
};