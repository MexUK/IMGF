#ifndef CGUIShapeGeometry_2xPoints_H
#define CGUIShapeGeometry_2xPoints_H

#include "Type/Types.h"
#include "Type/Vector/CVector2i32.h"
#include "Type/Vector/CPoint2D.h"
#include "Shape/eGUIShape.h"
#include "Shape/CGUIShape.h"

class CGUIShapeGeometry_2xPoints : public CGUIShape
{
public:
	CGUIShapeGeometry_2xPoints(eGUIShape eShapeType);

	void							unserialize(bool bSkipShapeId = false);
	void							serialize(void);

	void							moveItem(bxa::CVector2i32& vecPositionChange);
	void							resizeItemViaOffsets(bxa::CVector2i32& vecItemSizeChange) {}

	void							setPoint1(bxa::CPoint2D& vecPoint1) { m_vecPoint1 = vecPoint1; }
	bxa::CPoint2D&						getPoint1(void) { return m_vecPoint1; }

	void							setPoint2(bxa::CPoint2D& vecPoint2) { m_vecPoint2 = vecPoint2; }
	bxa::CPoint2D&						getPoint2(void) { return m_vecPoint2; }
	
private:
	bxa::CPoint2D						m_vecPoint1;
	bxa::CPoint2D						m_vecPoint2;
};

#endif