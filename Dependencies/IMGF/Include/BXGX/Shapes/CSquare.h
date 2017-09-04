#pragma once

#include "nsbxgx.h"
#include "Type/Vector/Vec2i.h"
#include "Type/Vector/Vec2u.h"
#include "Shapes/Geometries/C1Point1LengthGeometry.h"

class bxgx::CSquare : public C1Point1LengthGeometry
{
public:
	CSquare(void);

	void							bindEvents(void);

	void							onRender(void);

	bool							isPointInItem(bxcf::Vec2i& vecPoint);
	bxcf::Vec2i					getBoundingRectanglePosition(void);
	bxcf::Vec2u					getBoundingRectangleSize(void);
};