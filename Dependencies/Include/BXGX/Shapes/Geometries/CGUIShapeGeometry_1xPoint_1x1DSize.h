#ifndef CGUIShapeGeometry_1xPoint_1x1DSize_H
#define CGUIShapeGeometry_1xPoint_1x1DSize_H

#include "Type/Types.h"
#include "Type/Vector/CVector2i32.h"
#include "Type/Vector/CPoint2D.h"
#include "Shape/eGUIShape.h"
#include "Shape/CGUIShape.h"

class CGUIShapeGeometry_1xPoint_1x1DSize : public CGUIShape
{
public:
	CGUIShapeGeometry_1xPoint_1x1DSize(eGUIShape eShapeType);

	void							unserialize(bool bSkipShapeId = false);
	void							serialize(void);

	bxcf::CPoint2D						getCenterPosition(void);

	void							moveItem(bxcf::CVector2i32& vecPositionChange) { m_vecPosition += vecPositionChange; }
	void							resizeItemViaOffsets(bxcf::CVector2i32& vecItemSizeChange) { m_fSize += (((vecItemSizeChange.m_x + vecItemSizeChange.m_y) < 0) ? -1 : 1) * sqrt(vecItemSizeChange.m_x + vecItemSizeChange.m_y); } // todo - methodify

	void							setPosition(bxcf::CPoint2D& vecPosition) { m_vecPosition = vecPosition; }
	bxcf::CPoint2D&						getPosition(void) { return m_vecPosition; }

	void							setSize(float32 fSize) { m_fSize = fSize; }
	float32							getSize(void) { return m_fSize; }
	
private:
	bxcf::CPoint2D						m_vecPosition;
	float32							m_fSize;
};

#endif