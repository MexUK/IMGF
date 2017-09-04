#ifndef CLineShape_H
#define CLineShape_H

#include "Type/Vector/Vec2i.h"
#include "Type/Vector/Vec2u.h"
#include "Shapes/Geometries/CGUIShapeGeometry_2xPoints.h"

class CLineShape : public CGUIShapeGeometry_2xPoints
{
public:
	CLineShape(void);

	void							bindEvents(void);

	void							onRenderAfter(void);

	bool							isPointInItem(bxcf::Vec2i& vecPoint);
	bxcf::Vec2i						getBoundingRectanglePosition(void);
	bxcf::Vec2u						getBoundingRectangleSize(void);
};

#endif