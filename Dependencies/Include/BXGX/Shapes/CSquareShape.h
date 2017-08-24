#ifndef CSquareShape_H
#define CSquareShape_H

#include "Type/Vector/Vec2i.h"
#include "Type/Vector/Vec2u.h"
#include "Shapes/Geometries/CGUIShapeGeometry_1xPoint_1x1DSize.h"

class CSquareShape : public CGUIShapeGeometry_1xPoint_1x1DSize
{
public:
	CSquareShape(void);

	void							bindEvents(void);

	void							onRender(void);

	bool							isPointInItem(bxcf::Vec2i& vecPoint);
	bxcf::Vec2i					getBoundingRectanglePosition(void);
	bxcf::Vec2u					getBoundingRectangleSize(void);
};

#endif