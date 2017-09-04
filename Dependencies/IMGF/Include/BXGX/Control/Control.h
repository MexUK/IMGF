#pragma once

#include "nsbxgx.h"
#include "Type/Types.h"
#include "Type/Vector/Vec2i.h"
#include "Type/Vector/Vec2u.h"
#include "EControl.h"
#include "Item/CLayerItem.h"
#include "Control/E2DAxis.h"
#include "Renderable/ERenderable.h"

class bxgx::CWindow;
class bxgx::CScrollBarPool;
class bxgx::CLayer;
class bxgx::CScrollBar;

class bxgx::Control : public CLayerItem
{
public:
	Control(EControl eControlType);
	virtual ~Control(void);

	void									unload(void) {}

	virtual void							unserialize(bool bSkipControlId = false);
	virtual void							serialize(void);

	bxgx::item::ERenderable					getItemType(void) { return bxgx::item::CONTROL; }
	uint32									getItemSubType(void) { return m_eControlType; }

	virtual bool							isPointInItem(bxcf::Vec2i& vecPoint);
	virtual bool							doesControlUsePosition(bxcf::Vec2i& vecPoint) { return false; }

	virtual bxcf::Vec2i						getBoundingRectanglePosition(void) { return m_vecPosition; }
	virtual bxcf::Vec2u						getBoundingRectangleSize(void) { return m_vecSize; }
	void									moveItem(bxcf::Vec2i& vecPositionChange) { m_vecPosition += vecPositionChange; }
	void									resizeItemViaOffsets(bxcf::Vec2i& vecItemSizeChange) { m_vecSize += bxcf::Vec2u(vecItemSizeChange.x, vecItemSizeChange.y); }

	CScrollBar*							addScroll(E2DAxis uiOrientation);

	virtual uint32							getHeaderHeight(void);

	bool									doesHaveHoverIcon(void);

	void									setControlType(bxgx::EControl eControlType) { m_eControlType = eControlType; }
	bxgx::EControl								getControlType(void) { return m_eControlType; }
	
	void									setControlId(uint32 uiControlId) { m_uiControlId = uiControlId; }
	uint32									getControlId(void) { return m_uiControlId; }
	
	void									setPosition(bxcf::Vec2i& vecPosition) { m_vecPosition = vecPosition; }
	bxcf::Vec2i&							getPosition(void) { return m_vecPosition; }
	
	void									setSize(bxcf::Vec2u& vecSize) { m_vecSize = vecSize; }
	bxcf::Vec2u&							getSize(void) { return m_vecSize; }
	
	void									setPointMarkedAsInControl(bool bPointMarkedAsInControl) { m_bPointMarkedAsInControl = bPointMarkedAsInControl; }
	bool									isPointMarkedAsInControl(void) { return m_bPointMarkedAsInControl; }

	CScrollBarPool*							getScrolls(void) { return m_pScrolls; }

private:
	bxgx::EControl								m_eControlType;
	bxcf::Vec2i								m_vecPosition;
	bxcf::Vec2u								m_vecSize;
	uint32									m_uiControlId;
	uint8									m_bPointMarkedAsInControl		: 1;
	CScrollBarPool*							m_pScrolls;
};