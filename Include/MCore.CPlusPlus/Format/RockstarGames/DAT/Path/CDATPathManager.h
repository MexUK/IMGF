#ifndef CDATPathManager_H
#define CDATPathManager_H

#include "bxa.h"
#include "Format/CFormatManager.h"
#include "Object/CSingleton.h"
#include "Type/Vector/CVector2D.h"
#include "Collection/Games/ePlatformedGame.h"
#include <string>
#include <vector>

class bxa::CDATPathFormat;
struct bxa::CDATEntry_Paths_General_PathNode;
struct bxa::CDATEntry_Paths_General_NaviNode;

class bxa::CDATPathManager : public bxa::CFormatManager<bxa::CDATPathFormat>, public bxa::CSingleton<CDATPathManager>
{
public:
	CDATPathManager(void);

	void						init(void);
	void						uninit(void);

	static uint32		getAreaIdFromPosition(bxa::CVector2D& vecPosition, bxa::CVector2D& vecMapRangeMin, bxa::CVector2D& vecMapRangeMax, bxa::CVector2D& vecAreaSize);
	static uint32		getTileCount(bxa::CVector2D& vecMapRangeMin, bxa::CVector2D& vecMapRangeMax, bxa::CVector2D& vecAreaSize);

	static bool					findPathNode(std::vector<bxa::CDATPathFormat*>& veCDATFormatPaths, bxa::CDATEntry_Paths_General_PathNode& pathNodeToFind, uint32& uiAreaId_Out, uint32& uiNodeId_Out);
	static bool					findNaviNode(std::vector<bxa::CDATPathFormat*>& veCDATFormatPaths, bxa::CDATEntry_Paths_General_NaviNode& naviNodeToFind, uint32& uiAreaId_Out, uint32& uiNodeId_Out);
	static bxa::CDATEntry_Paths_General_PathNode					getLowestPathNode(std::vector<bxa::CDATEntry_Paths_General_PathNode>& vecPathNodes);
	static std::vector<bxa::CDATEntry_Paths_General_PathNode>	getTargetPathNodesForNaviNode(std::vector<bxa::CDATPathFormat*> veCDATFormats, bxa::CDATEntry_Paths_General_NaviNode& naviNode, uint32 uiNaviNodeAreaId, uint32 uiNaviNodeNodeId, uint32& uiLinkId_Out);
};

#endif