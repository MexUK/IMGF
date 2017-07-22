#ifndef CPolygonShape_H
#define CPolygonShape_H

#include "Type/Vector/CPoint2D.h"
#include "Type/Vector/CSize2D.h"
#include "Shape/eGUIShape.h"
#include "Shapes/Geometries/CGUIShapeGeometry_NxPoints.h"

class CPolygonShape : public CGUIShapeGeometry_NxPoints
{
public:
	CPolygonShape(void);

	void							bindEvents(void);
	void							render(void);
	bool							isPointInItem(bxa::CPoint2D& vecPoint);
	bxa::CPoint2D						getBoundingRectanglePosition(void);
	bxa::CSize2D							getBoundingRectangleSize(void);
};

#endif