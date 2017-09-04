#pragma once

#include "nsbxgx.h"
#include "Type/Vector/Vec2i.h"
#include "Type/Vector/Vec2u.h"
#include "Shapes/Geometries/C3PointGeometry.h"

class bxgx::CTriangle : public C3PointGeometry
{
public:
	CTriangle(void);

	void							bindEvents(void);

	void							onRender(void);

	bool							isPointInItem(bxcf::Vec2i& vecPoint);
	bxcf::Vec2i					getBoundingRectanglePosition(void);
	bxcf::Vec2u					getBoundingRectangleSize(void);
};