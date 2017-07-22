#ifndef CEllipseShape_H
#define CEllipseShape_H

#include "Type/Vector/CPoint2D.h"
#include "Type/Vector/CSize2D.h"
#include "Shape/eGUIShape.h"
#include "Shapes/Geometries/CGUIShapeGeometry_1xPoint_1x2DSize.h"

class CEllipseShape : public CGUIShapeGeometry_1xPoint_1x2DSize
{
public:
	CEllipseShape(void);

	void							bindEvents(void);
	void							render(void);
	bool							isPointInItem(bxa::CPoint2D& vecPoint);
	bxa::CPoint2D						getBoundingRectanglePosition(void);
	bxa::CSize2D							getBoundingRectangleSize(void);
};

#endif