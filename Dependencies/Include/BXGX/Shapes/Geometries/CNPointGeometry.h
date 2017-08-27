#pragma once

#include "nsbxgx.h"
#include "Type/Types.h"
#include "Type/Vector/Vec2i.h"
#include "Type/Vector/Vec2i.h"
#include "Shape/EShape.h"
#include "Shape/CShape.h"
#include <vector>

class bxgx::CNPointGeometry : public CShape
{
public:
	CNPointGeometry(EShape eShapeType);

	void							unserialize(bool bSkipShapeId = false);
	void							serialize(void);

	void							moveItem(bxcf::Vec2i& vecPositionChange);
	void							resizeItemViaOffsets(bxcf::Vec2i& vecItemSizeChange) {}

	void							setPoints(std::vector<bxcf::Vec2i>& vecPoints) { m_vecPoints = vecPoints; }
	std::vector<bxcf::Vec2i>&		getPoints(void) { return m_vecPoints; }
	
private:
	std::vector<bxcf::Vec2i>		m_vecPoints;
};