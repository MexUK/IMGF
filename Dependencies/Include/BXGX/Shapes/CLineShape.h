#ifndef CLineShape_H
#define CLineShape_H

#include "Type/Vector/CPoint2D.h"
#include "Type/Vector/CSize2D.h"
#include "Shape/eGUIShape.h"
#include "Shapes/Geometries/CGUIShapeGeometry_2xPoints.h"

class CLineShape : public CGUIShapeGeometry_2xPoints
{
public:
	CLineShape(void);

	void							bindEvents(void);

	void							onRender(void);

	bool							isPointInItem(bxcf::CPoint2D& vecPoint);
	bxcf::CPoint2D					getBoundingRectanglePosition(void);
	bxcf::CSize2D					getBoundingRectangleSize(void);
};

#endif