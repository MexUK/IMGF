#ifndef CCircleShape_H
#define CCircleShape_H

#include "Type/Vector/CVector2i32.h"
#include "Type/Vector/CSize2D.h"
#include "Shape/eGUIShape.h"
#include "Shapes/Geometries/CGUIShapeGeometry_1xPoint_1x1DSize.h"

class CCircleShape : public CGUIShapeGeometry_1xPoint_1x1DSize
{
public:
	CCircleShape(void);

	void							bindEvents(void);
	void							render(void);
	bool							isPointInItem(mcore::CPoint2D& vecPoint);
	mcore::CPoint2D						getBoundingRectanglePosition(void);
	mcore::CSize2D							getBoundingRectangleSize(void);
};

#endif