#pragma once

#include "nsbxgx.h"
#include "Type/Types.h"
#include "Type/Vector/Vec2i.h"
#include "Shape/Base/EShape.h"
#include "Shape/Base/Shape.h"
#include <vector>

class bxgx::NPointGeometry : public Shape
{
public:
	NPointGeometry(EShape eShapeType);

	void							unserialize(bool bSkipShapeId = false);
	void							serialize(void);

	void							moveItem(bxcf::Vec2i& vecPositionChange);
	void							resizeItemViaOffsets(bxcf::Vec2i& vecItemSizeChange) {}

	void							setPoints(std::vector<bxcf::Vec2i>& vecPoints) { m_vecPoints = vecPoints; }
	std::vector<bxcf::Vec2i>&		getPoints(void) { return m_vecPoints; }
	
private:
	std::vector<bxcf::Vec2i>		m_vecPoints;
};