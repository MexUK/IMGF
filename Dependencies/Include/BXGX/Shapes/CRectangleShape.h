#ifndef CRectangleShape_H
#define CRectangleShape_H

#include "Type/Vector/Vec2i.h"
#include "Type/Vector/Vec2u.h"
#include "Shapes/Geometries/CGUIShapeGeometry_1xPoint_1x2DSize.h"

class CRectangleShape : public CGUIShapeGeometry_1xPoint_1x2DSize
{
public:
	CRectangleShape(void);

	void							bindEvents(void);

	void							onRender(void);

	bool							isPointInItem(bxcf::Vec2i& vecPoint);
	bxcf::Vec2i					getBoundingRectanglePosition(void);
	bxcf::Vec2u					getBoundingRectangleSize(void);
};

#endif