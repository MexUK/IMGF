#ifndef CEllipseShape_H
#define CEllipseShape_H

#include "Type/Vector/Vec2i.h"
#include "Type/Vector/Vec2u.h"
#include "Shapes/Geometries/CGUIShapeGeometry_1xPoint_1x2DSize.h"

class CEllipseShape : public CGUIShapeGeometry_1xPoint_1x2DSize
{
public:
	CEllipseShape(void);

	void							bindEvents(void);

	void							onRender(void);

	bool							isPointInItem(bxcf::Vec2i& vecPoint);
	bxcf::Vec2i					getBoundingRectanglePosition(void);
	bxcf::Vec2u					getBoundingRectangleSize(void);
};

#endif