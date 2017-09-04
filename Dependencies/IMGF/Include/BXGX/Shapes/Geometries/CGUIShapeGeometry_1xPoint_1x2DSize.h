#ifndef CGUIShapeGeometry_1xPoint_1x2DSize_H
#define CGUIShapeGeometry_1xPoint_1x2DSize_H

#include "Type/Types.h"
#include "Type/Vector/Vec2i.h"
#include "Type/Vector/Vec2i.h"
#include "Type/Vector/Vec2u.h"
#include "Shape/eGUIShape.h"
#include "Shape/CGUIShape.h"

class CGUIShapeGeometry_1xPoint_1x2DSize : public CGUIShape
{
public:
	CGUIShapeGeometry_1xPoint_1x2DSize(eGUIShape eShapeType);

	void							unserialize(bool bSkipShapeId = false);
	void							serialize(void);

	void							moveItem(bxcf::Vec2i& vecPositionChange) { m_vecPosition += vecPositionChange; }
	void							resizeItemViaOffsets(bxcf::Vec2i& vecItemSizeChange) { m_vecSize += bxcf::Vec2u(vecItemSizeChange.x, vecItemSizeChange.y); }

	void							setPosition(bxcf::Vec2i& vecPosition) { m_vecPosition = vecPosition; }
	bxcf::Vec2i&						getPosition(void) { return m_vecPosition; }

	void							setSize(bxcf::Vec2u& vecSize) { m_vecSize = vecSize; }
	bxcf::Vec2u&						getSize(void) { return m_vecSize; }
	
private:
	bxcf::Vec2i						m_vecPosition;
	bxcf::Vec2u							m_vecSize;
};

#endif