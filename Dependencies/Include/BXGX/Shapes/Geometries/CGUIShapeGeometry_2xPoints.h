#ifndef CGUIShapeGeometry_2xPoints_H
#define CGUIShapeGeometry_2xPoints_H

#include "Type/Types.h"
#include "Type/Vector/Vec2i.h"
#include "Type/Vector/Vec2i.h"
#include "Shape/eGUIShape.h"
#include "Shape/CGUIShape.h"

class CGUIShapeGeometry_2xPoints : public CGUIShape
{
public:
	CGUIShapeGeometry_2xPoints(eGUIShape eShapeType);

	void							unserialize(bool bSkipShapeId = false);
	void							serialize(void);

	void							moveItem(bxcf::Vec2i& vecPositionChange);
	void							resizeItemViaOffsets(bxcf::Vec2i& vecItemSizeChange) {}

	void							setPoint1(bxcf::Vec2i& vecPoint1) { m_vecPoint1 = vecPoint1; }
	bxcf::Vec2i&						getPoint1(void) { return m_vecPoint1; }

	void							setPoint2(bxcf::Vec2i& vecPoint2) { m_vecPoint2 = vecPoint2; }
	bxcf::Vec2i&						getPoint2(void) { return m_vecPoint2; }
	
private:
	bxcf::Vec2i						m_vecPoint1;
	bxcf::Vec2i						m_vecPoint2;
};

#endif