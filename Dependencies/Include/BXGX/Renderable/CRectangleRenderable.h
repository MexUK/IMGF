#pragma once

#include "bxgx.h"
#include "bxcf.h"
#include "Renderable/ERenderable.h"
#include "Static/CMath.h"
#include "Renderable/CRenderable.h"

class CRectangleRenderable : public CRenderable
{
public:
	CRectangleRenderable(void) :
		m_vecPosition(bxcf::Vec2i(0, 0)),
		m_vecSize(bxcf::Vec2u(0, 0))
	{
	}
	CRectangleRenderable(bxcf::Vec2i& vecPosition, bxcf::Vec2u& vecSize) :
		m_vecPosition(vecPosition),
		m_vecSize(vecSize)
	{
	}

	inline bxgx::item::ERenderable		getItemType(void) { return bxgx::item::RECTANGLE; }
	uint32							getItemSubType(void) { return 0; }
	inline bool						isPointInItem(bxcf::Vec2i& vecPoint) { return bxcf::CMath::isPointInRectangle(vecPoint, m_vecPosition, m_vecSize); }
	inline bool						doesItemHaveFocus(void) { return false; }

	void							setPosition(bxcf::Vec2i& vecPosition) { m_vecPosition = vecPosition; }
	bxcf::Vec2i&					getPosition(void) { return m_vecPosition; }

	void							setSize(bxcf::Vec2u& vecSize) { m_vecSize = vecSize; }
	bxcf::Vec2u&					getSize(void) { return m_vecSize; }

private:
	bxcf::Vec2i						m_vecPosition;
	bxcf::Vec2u						m_vecSize;
};