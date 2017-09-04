#pragma once

#include "nsbxgx.h"
#include "Type/Vector/Vec2i.h"
#include "Type/Vector/Vec2u.h"
#include "Geometry/Geometries/NPointGeometry.h"

class bxgx::Polygon : public NPointGeometry
{
public:
	Polygon(void);

	void							bindEvents(void);

	void							onRender(void);

	bool							isPointInItem(bxcf::Vec2i& vecPoint);
	bxcf::Vec2i					getBoundingRectanglePosition(void);
	bxcf::Vec2u					getBoundingRectangleSize(void);
};