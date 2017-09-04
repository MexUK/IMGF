#ifndef CDATPathManager_H
#define CDATPathManager_H

#include "bxcf.h"
#include "Format/CFormatManager.h"
#include "Object/CSingleton.h"
#include "Type/Vector/Vec2f.h"
#include "Collection/Games/ePlatformedGame.h"
#include <string>
#include <vector>

class bxcf::CDATPathFormat;
struct bxcf::CDATEntry_Paths_General_PathNode;
struct bxcf::CDATEntry_Paths_General_NaviNode;

class bxcf::CDATPathManager : public bxcf::CFormatManager<bxcf::CDATPathFormat>, public bxcf::CSingleton<CDATPathManager>
{
public:
	CDATPathManager(void);

	void						init(void);
	void						uninit(void);

	static uint32		getAreaIdFromPosition(bxcf::Vec2f& vecPosition, bxcf::Vec2f& vecMapRangeMin, bxcf::Vec2f& vecMapRangeMax, bxcf::Vec2f& vecAreaSize);
	static uint32		getTileCount(bxcf::Vec2f& vecMapRangeMin, bxcf::Vec2f& vecMapRangeMax, bxcf::Vec2f& vecAreaSize);

	static bool					findPathNode(std::vector<bxcf::CDATPathFormat*>& veCDATFormatPaths, bxcf::CDATEntry_Paths_General_PathNode& pathNodeToFind, uint32& uiAreaId_Out, uint32& uiNodeId_Out);
	static bool					findNaviNode(std::vector<bxcf::CDATPathFormat*>& veCDATFormatPaths, bxcf::CDATEntry_Paths_General_NaviNode& naviNodeToFind, uint32& uiAreaId_Out, uint32& uiNodeId_Out);
	static bxcf::CDATEntry_Paths_General_PathNode					getLowestPathNode(std::vector<bxcf::CDATEntry_Paths_General_PathNode>& vecPathNodes);
	static std::vector<bxcf::CDATEntry_Paths_General_PathNode>	getTargetPathNodesForNaviNode(std::vector<bxcf::CDATPathFormat*> veCDATFormats, bxcf::CDATEntry_Paths_General_NaviNode& naviNode, uint32 uiNaviNodeAreaId, uint32 uiNaviNodeNodeId, uint32& uiLinkId_Out);
};

#endif