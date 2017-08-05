#ifndef CSquareShape_H
#define CSquareShape_H

#include "Type/Vector/CPoint2D.h"
#include "Type/Vector/CSize2D.h"
#include "Shape/eGUIShape.h"
#include "Shapes/Geometries/CGUIShapeGeometry_1xPoint_1x1DSize.h"

class CSquareShape : public CGUIShapeGeometry_1xPoint_1x1DSize
{
public:
	CSquareShape(void);

	void							bindEvents(void);

	bool							onRender(void);

	bool							isPointInItem(bxcf::CPoint2D& vecPoint);
	bxcf::CPoint2D					getBoundingRectanglePosition(void);
	bxcf::CSize2D					getBoundingRectangleSize(void);
};

#endif