#pragma once

#include "nsbxgx.h"
#include "Type/Vector/Vec2i.h"
#include "Type/Vector/Vec2u.h"
#include "Geometry/Geometries/_2PointGeometry.h"

class bxgx::Line : public _2PointGeometry
{
public:
	Line(void);

	void							bindEvents(void);

	void							onRenderAfter(void);

	bool							isPointInItem(bxcf::Vec2i& vecPoint);
	bxcf::Vec2i						getBoundingRectanglePosition(void);
	bxcf::Vec2u						getBoundingRectangleSize(void);
};