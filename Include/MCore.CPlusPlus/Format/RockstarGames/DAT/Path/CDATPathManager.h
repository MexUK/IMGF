#ifndef CDATPathManager_H
#define CDATPathManager_H

#include "mcore.h"
#include "Format/CFormatManager.h"
#include "Object/CSingleton.h"
#include "Type/Vector/CVector2D.h"
#include "Collection/Games/ePlatformedGame.h"
#include <string>
#include <vector>

class mcore::CDATPathFormat;
struct mcore::CDATEntry_Paths_General_PathNode;
struct mcore::CDATEntry_Paths_General_NaviNode;

class mcore::CDATPathManager : public mcore::CFormatManager<mcore::CDATPathFormat>, public mcore::CSingleton<CDATPathManager>
{
public:
	CDATPathManager(void);

	void						init(void);
	void						uninit(void);

	static uint32		getAreaIdFromPosition(mcore::CVector2D& vecPosition, mcore::CVector2D& vecMapRangeMin, mcore::CVector2D& vecMapRangeMax, mcore::CVector2D& vecAreaSize);
	static uint32		getTileCount(mcore::CVector2D& vecMapRangeMin, mcore::CVector2D& vecMapRangeMax, mcore::CVector2D& vecAreaSize);

	static bool					findPathNode(std::vector<mcore::CDATPathFormat*>& veCDATFormatPaths, mcore::CDATEntry_Paths_General_PathNode& pathNodeToFind, uint32& uiAreaId_Out, uint32& uiNodeId_Out);
	static bool					findNaviNode(std::vector<mcore::CDATPathFormat*>& veCDATFormatPaths, mcore::CDATEntry_Paths_General_NaviNode& naviNodeToFind, uint32& uiAreaId_Out, uint32& uiNodeId_Out);
	static mcore::CDATEntry_Paths_General_PathNode					getLowestPathNode(std::vector<mcore::CDATEntry_Paths_General_PathNode>& vecPathNodes);
	static std::vector<mcore::CDATEntry_Paths_General_PathNode>	getTargetPathNodesForNaviNode(std::vector<mcore::CDATPathFormat*> veCDATFormats, mcore::CDATEntry_Paths_General_NaviNode& naviNode, uint32 uiNaviNodeAreaId, uint32 uiNaviNodeNodeId, uint32& uiLinkId_Out);
};

#endif