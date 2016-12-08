#ifndef CRectangleShape_H
#define CRectangleShape_H

#include "Type/Vector/CPoint2D.h"
#include "Type/Vector/CSize2D.h"
#include "Shape/eGUIShape.h"
#include "Shapes/Geometries/CGUIShapeGeometry_1xPoint_1x2DSize.h"

class CRectangleShape : public CGUIShapeGeometry_1xPoint_1x2DSize
{
public:
	CRectangleShape(void);

	void							bindEvents(void);
	void							render(void);
	bool							isPointInItem(mcore::CPoint2D& vecPoint);
	mcore::CPoint2D						getBoundingRectanglePosition(void);
	mcore::CSize2D							getBoundingRectangleSize(void);
};

#endif