#ifndef CGUIShapeGeometry_1xPoint_1x1DSize_H
#define CGUIShapeGeometry_1xPoint_1x1DSize_H

#include "Type/Types.h"
#include "Type/Vector/Vec2i.h"
#include "Type/Vector/Vec2i.h"
#include "Shape/eGUIShape.h"
#include "Shape/CGUIShape.h"

class CGUIShapeGeometry_1xPoint_1x1DSize : public CGUIShape
{
public:
	CGUIShapeGeometry_1xPoint_1x1DSize(eGUIShape eShapeType);

	void							unserialize(bool bSkipShapeId = false);
	void							serialize(void);

	bxcf::Vec2i						getCenterPosition(void);

	void							moveItem(bxcf::Vec2i& vecPositionChange) { m_vecPosition += vecPositionChange; }
	void							resizeItemViaOffsets(bxcf::Vec2i& vecItemSizeChange) { m_fSize += (float32)((((vecItemSizeChange.x + vecItemSizeChange.y) < 0) ? -1 : 1)) * (float32)sqrt(vecItemSizeChange.x + vecItemSizeChange.y); } // todo - methodify

	void							setPosition(bxcf::Vec2i& vecPosition) { m_vecPosition = vecPosition; }
	bxcf::Vec2i&					getPosition(void) { return m_vecPosition; }

	void							setSize(float32 fSize) { m_fSize = fSize; }
	float32							getSize(void) { return m_fSize; }
	
private:
	bxcf::Vec2i						m_vecPosition;
	float32							m_fSize;
};

#endif