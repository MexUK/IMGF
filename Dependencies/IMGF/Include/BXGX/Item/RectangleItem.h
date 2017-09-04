#pragma once

#include "nsbxgx.h"
#include "nsbxcf.h"
#include "Item/Render/ERenderItem.h"
#include "Static/Math.h"
#include "Item/Render/RenderItem.h"

class bxgx::RectangleItem : public RenderItem
{
public:
	RectangleItem(void);
	RectangleItem(bxcf::Vec2i& vecPosition, bxcf::Vec2u& vecSize);

	inline bxgx::item::ERenderItem	getItemType(void) { return bxgx::item::RECTANGLE; }
	uint32							getItemSubType(void) { return 0; }
	inline bool						isPointInItem(bxcf::Vec2i& vecPoint) { return bxcf::Math::isPointInRectangle(vecPoint, m_vecPosition, m_vecSize); }
	inline bool						doesItemHaveFocus(void) { return false; }

	void							setPosition(bxcf::Vec2i& vecPosition) { m_vecPosition = vecPosition; }
	bxcf::Vec2i&					getPosition(void) { return m_vecPosition; }

	void							setSize(bxcf::Vec2u& vecSize) { m_vecSize = vecSize; }
	bxcf::Vec2u&					getSize(void) { return m_vecSize; }

private:
	bxcf::Vec2i						m_vecPosition;
	bxcf::Vec2u						m_vecSize;
};