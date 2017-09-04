#pragma once

#include "nsbxgi.h"
#include "Type/Types.h"
#include "Format/IPL/Entry/DataEntry/CIPLEntry_PATH.h"
#include "Type/Vector/Vec3f.h"

class bxgi::CIPLEntry_PATH_Node : public bxgi::CIPLEntry_PATH
{
public:
	CIPLEntry_PATH_Node(CIPLFormat *pIPLFormat);

	void							unserialize(void);
	void							serialize(void);

	void							setNodeType(uint32 uiNodeType) { m_uiNodeType = uiNodeType; }
	uint32							getNodeType(void) { return m_uiNodeType; }

	void							setNextNode(uint32 uiNextNode) { m_uiNextNode = uiNextNode; }
	uint32							getNextNode(void) { return m_uiNextNode; }

	void							setIsCrossRoad(uint32 uiIsCrossRoad) { m_uiIsCrossRoad = uiIsCrossRoad; }
	uint32							getIsCrossRoad(void) { return m_uiIsCrossRoad; }

	void							setPosition(bxcf::Vec3f& vecPosition) { m_vecPosition = vecPosition; }
	bxcf::Vec3f&						getPosition(void) { return m_vecPosition; }

	void							setMedian(float32 fMedian) { m_fMedian = fMedian; }
	float32							getMedian(void) { return m_fMedian; }

	void							setLeftLaneCount(uint32 uiLeftLaneCount) { m_uiLeftLaneCount = uiLeftLaneCount; }
	uint32							getLeftLaneCount(void) { return m_uiLeftLaneCount; }

	void							setRightLaneCount(uint32 uiRightLaneCount) { m_uiRightLaneCount = uiRightLaneCount; }
	uint32							getRightLaneCount(void) { return m_uiRightLaneCount; }

	void							setSpeedLimit(uint32 uiSpeedLimit) { m_uiSpeedLimit = uiSpeedLimit; }
	uint32							getSpeedLimit(void) { return m_uiSpeedLimit; }

	void							setFlags(uint32 uiFlags) { m_uiFlags = uiFlags; }
	uint32							getFlags(void) { return m_uiFlags; }

	void							setSpawnRate(float32 fSpawnRate) { m_fSpawnRate = fSpawnRate; }
	float32							getSpawnRate(void) { return m_fSpawnRate; }

private:
	// GTA VC only
	uint32							m_uiNodeType;
	uint32							m_uiNextNode;
	uint32							m_uiIsCrossRoad;
	bxcf::Vec3f						m_vecPosition;
	float32							m_fMedian;
	uint32							m_uiLeftLaneCount;
	uint32							m_uiRightLaneCount;
	uint32							m_uiSpeedLimit;
	uint32							m_uiFlags;
	float32							m_fSpawnRate;
};