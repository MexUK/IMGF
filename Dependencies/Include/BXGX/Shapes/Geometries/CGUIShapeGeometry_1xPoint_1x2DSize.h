#ifndef CGUIShapeGeometry_1xPoint_1x2DSize_H
#define CGUIShapeGeometry_1xPoint_1x2DSize_H

#include "Type/Types.h"
#include "Type/Vector/CVector2i32.h"
#include "Type/Vector/CPoint2D.h"
#include "Type/Vector/CSize2D.h"
#include "Shape/eGUIShape.h"
#include "Shape/CGUIShape.h"

class CGUIShapeGeometry_1xPoint_1x2DSize : public CGUIShape
{
public:
	CGUIShapeGeometry_1xPoint_1x2DSize(eGUIShape eShapeType);

	void							unserialize(bool bSkipShapeId = false);
	void							serialize(void);

	void							moveItem(bxcf::CVector2i32& vecPositionChange) { m_vecPosition += vecPositionChange; }
	void							resizeItemViaOffsets(bxcf::CVector2i32& vecItemSizeChange) { m_vecSize += bxcf::CSize2D(vecItemSizeChange.m_x, vecItemSizeChange.m_y); }

	void							setPosition(bxcf::CPoint2D& vecPosition) { m_vecPosition = vecPosition; }
	bxcf::CPoint2D&						getPosition(void) { return m_vecPosition; }

	void							setSize(bxcf::CSize2D& vecSize) { m_vecSize = vecSize; }
	bxcf::CSize2D&						getSize(void) { return m_vecSize; }
	
private:
	bxcf::CPoint2D						m_vecPosition;
	bxcf::CSize2D							m_vecSize;
};

#endif