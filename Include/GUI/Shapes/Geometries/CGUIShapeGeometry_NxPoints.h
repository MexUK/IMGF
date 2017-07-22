#ifndef CGUIShapeGeometry_NxPoints_H
#define CGUIShapeGeometry_NxPoints_H

#include "Type/Types.h"
#include "Type/Vector/CVector2i32.h"
#include "Type/Vector/CPoint2D.h"
#include "Shape/eGUIShape.h"
#include "Shape/CGUIShape.h"
#include <vector>

class CGUIShapeGeometry_NxPoints : public CGUIShape
{
public:
	CGUIShapeGeometry_NxPoints(eGUIShape eShapeType);

	void							unserialize(bool bSkipShapeId = false);
	void							serialize(void);

	void							moveItem(bxa::CVector2i32& vecPositionChange);
	void							resizeItemViaOffsets(bxa::CVector2i32& vecItemSizeChange) {}

	void							setPoints(std::vector<bxa::CPoint2D>& vecPoints) { m_vecPoints = vecPoints; }
	std::vector<bxa::CPoint2D>&			getPoints(void) { return m_vecPoints; }
	
private:
	std::vector<bxa::CPoint2D>			m_vecPoints;
};

#endif