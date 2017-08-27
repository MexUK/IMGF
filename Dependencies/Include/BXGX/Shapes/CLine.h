#pragma once

#include "nsbxgx.h"
#include "Type/Vector/Vec2i.h"
#include "Type/Vector/Vec2u.h"
#include "Shapes/Geometries/C2PointGeometry.h"

class bxgx::CLine : public C2PointGeometry
{
public:
	CLine(void);

	void							bindEvents(void);

	void							onRenderAfter(void);

	bool							isPointInItem(bxcf::Vec2i& vecPoint);
	bxcf::Vec2i						getBoundingRectanglePosition(void);
	bxcf::Vec2u						getBoundingRectangleSize(void);
};