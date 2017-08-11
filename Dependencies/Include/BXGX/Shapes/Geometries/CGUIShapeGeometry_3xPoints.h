#ifndef CGUIShapeGeometry_3xPoints_H
#define CGUIShapeGeometry_3xPoints_H

#include "Type/Types.h"
#include "Type/Vector/Vec2i.h"
#include "Type/Vector/Vec2i.h"
#include "Shape/eGUIShape.h"
#include "Shape/CGUIShape.h"

class CGUIShapeGeometry_3xPoints : public CGUIShape
{
public:
	CGUIShapeGeometry_3xPoints(eGUIShape eShapeType);

	void							unserialize(bool bSkipShapeId = false);
	void							serialize(void);

	void							moveItem(bxcf::Vec2i& vecPositionChange);
	void							resizeItemViaOffsets(bxcf::Vec2i& vecItemSizeChange) {}

	void							setPoint1(bxcf::Vec2i& vecPoint1) { m_vecPoint1 = vecPoint1; }
	bxcf::Vec2i&						getPoint1(void) { return m_vecPoint1; }

	void							setPoint2(bxcf::Vec2i& vecPoint2) { m_vecPoint2 = vecPoint2; }
	bxcf::Vec2i&						getPoint2(void) { return m_vecPoint2; }
	
	void							setPoint3(bxcf::Vec2i& vecPoint3) { m_vecPoint3 = vecPoint3; }
	bxcf::Vec2i&						getPoint3(void) { return m_vecPoint3; }
	
private:
	bxcf::Vec2i						m_vecPoint1;
	bxcf::Vec2i						m_vecPoint2;
	bxcf::Vec2i						m_vecPoint3;
};

#endif