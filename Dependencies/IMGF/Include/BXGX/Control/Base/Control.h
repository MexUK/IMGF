#pragma once

#include "nsbxgx.h"
#include "Type/Types.h"
#include "Type/Vector/Vec2i.h"
#include "Type/Vector/Vec2u.h"
#include "EControl.h"
#include "Item/Layer/LayerItem.h"
#include "Type/Axis/E2DAxis.h"
#include "Item/Render/ERenderItem.h"

class bxgx::Window;
class bxgx::ScrollBarPool;
class bxgx::Layer;
class bxgx::ScrollBar;

class bxgx::Control : public LayerItem
{
public:
	Control(EControl eControlType);
	virtual ~Control(void);

	void									unload(void) {}

	virtual void							unserialize(bool bSkipControlId = false);
	virtual void							serialize(void);

	bxgx::item::ERenderItem					getItemType(void) { return bxgx::item::CONTROL; }
	uint32									getItemSubType(void) { return m_uiControlType; }

	virtual bool							isPointInItem(bxcf::Vec2i& vecPoint);
	virtual bool							doesControlUsePosition(bxcf::Vec2i& vecPoint) { return false; }

	virtual bxcf::Vec2i						getBoundingRectanglePosition(void) { return m_vecPosition; }
	virtual bxcf::Vec2u						getBoundingRectangleSize(void) { return m_vecSize; }
	void									moveItem(bxcf::Vec2i& vecPositionChange) { m_vecPosition += vecPositionChange; }
	void									resizeItemViaOffsets(bxcf::Vec2i& vecItemSizeChange) { m_vecSize += bxcf::Vec2u(vecItemSizeChange.x, vecItemSizeChange.y); }

	ScrollBar*								addScroll(bxcf::E2DAxis uiOrientation);

	virtual uint32							getHeaderHeight(void);

	bool									doesHaveHoverIcon(void);

	void									setControlType(bxgx::EControl eControlType) { m_uiControlType = eControlType; }
	bxgx::EControl							getControlType(void) { return m_uiControlType; }
	
	void									setPosition(bxcf::Vec2i& vecPosition) { m_vecPosition = vecPosition; }
	bxcf::Vec2i&							getPosition(void) { return m_vecPosition; }
	
	void									setSize(bxcf::Vec2u& vecSize) { m_vecSize = vecSize; }
	bxcf::Vec2u&							getSize(void) { return m_vecSize; }
	
	void									setPointMarkedAsInControl(bool bPointMarkedAsInControl) { m_bPointMarkedAsInControl = bPointMarkedAsInControl; }
	bool									isPointMarkedAsInControl(void) { return m_bPointMarkedAsInControl; }

	void									setProgressFor1Item(float32 fProgressFor1Item) { m_fProgressFor1Item = fProgressFor1Item; }
	float32									getProgressFor1Item(void) { return m_fProgressFor1Item; }

	virtual uint32							getMaxDisplayedItemCount(void) { return 1; }
	virtual uint32							getItemCount(void) { return 0; }

	ScrollBarPool*							getScrolls(void) { return m_pScrolls; }

protected:
	bxcf::Vec2i								m_vecPosition;
	bxcf::Vec2u								m_vecSize;
	float32									m_fProgressFor1Item;

private:
	bxgx::EControl							m_uiControlType;
	uint8									m_bPointMarkedAsInControl		: 1;
	ScrollBarPool*							m_pScrolls;
};