#ifndef CTriangleShape_H
#define CTriangleShape_H

#include "Type/Vector/CPoint2D.h"
#include "Type/Vector/CSize2D.h"
#include "Shape/eGUIShape.h"
#include "Shapes/Geometries/CGUIShapeGeometry_3xPoints.h"

class CTriangleShape : public CGUIShapeGeometry_3xPoints
{
public:
	CTriangleShape(void);

	void							bindEvents(void);
	void							render(void);
	bool							isPointInItem(bxa::CPoint2D& vecPoint);
	bxa::CPoint2D						getBoundingRectanglePosition(void);
	bxa::CSize2D							getBoundingRectangleSize(void);
};

#endif