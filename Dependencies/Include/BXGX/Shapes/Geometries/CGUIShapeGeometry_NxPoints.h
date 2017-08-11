#ifndef CGUIShapeGeometry_NxPoints_H
#define CGUIShapeGeometry_NxPoints_H

#include "Type/Types.h"
#include "Type/Vector/Vec2i.h"
#include "Type/Vector/Vec2i.h"
#include "Shape/eGUIShape.h"
#include "Shape/CGUIShape.h"
#include <vector>

class CGUIShapeGeometry_NxPoints : public CGUIShape
{
public:
	CGUIShapeGeometry_NxPoints(eGUIShape eShapeType);

	void							unserialize(bool bSkipShapeId = false);
	void							serialize(void);

	void							moveItem(bxcf::Vec2i& vecPositionChange);
	void							resizeItemViaOffsets(bxcf::Vec2i& vecItemSizeChange) {}

	void							setPoints(std::vector<bxcf::Vec2i>& vecPoints) { m_vecPoints = vecPoints; }
	std::vector<bxcf::Vec2i>&		getPoints(void) { return m_vecPoints; }
	
private:
	std::vector<bxcf::Vec2i>		m_vecPoints;
};

#endif