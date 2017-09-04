#pragma once

#include "nsbxgx.h"
#include "Type/Vector/Vec2i.h"
#include "Type/Vector/Vec2u.h"
#include "Geometry/Geometries/_1Point2LengthGeometry.h"

class bxgx::Rectangle : public _1Point2LengthGeometry
{
public:
	Rectangle(void);

	void							bindEvents(void);

	void							onRender(void);

	bool							isPointInItem(bxcf::Vec2i& vecPoint);
	bxcf::Vec2i						getBoundingRectanglePosition(void);
	bxcf::Vec2u						getBoundingRectangleSize(void);
};