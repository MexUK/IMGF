#ifndef CGUIItem_H
#define CGUIItem_H

#include "Type/Vector/Vec2i.h"
#include "Type/Vector/Vec2i.h"
#include "Type/Vector/Vec2u.h"
#include "Styles/CGUIStyleableEntity.h"
#include "Event/CGUIEventUtilizer.h"
#include <unordered_map>

class CGUILayer;
class CWindow;

class CGUIItem : public CGUIStyleableEntity, public CGUIEventUtilizer
{
public:
	CGUIItem(void);
	virtual ~CGUIItem(void) {}

	void									unload(void) {}

	virtual void							unserialize(bool bSkipItemId = false)	= 0;
	virtual void							serialize(void)							= 0;

	void									setLayer(CGUILayer* pLayer) { m_pLayer = pLayer; }
	CGUILayer*								getLayer(void) { return m_pLayer; }

	void									setId(uint32 uiId) { m_uiId = uiId; }
	uint32									getId(void) { return m_uiId; }

	virtual bxcf::Vec2i						getBoundingRectanglePosition(void)						= 0;
	virtual bxcf::Vec2u						getBoundingRectangleSize(void)							= 0;
	virtual void							moveItem(bxcf::Vec2i& vecItemPositionChange)			= 0;
	virtual void							resizeItemViaOffsets(bxcf::Vec2i& vecItemSizeChange)	= 0;

	void									onMoveItem(bxcf::Vec2i& vecItemPositionChange);
	void									onResizeItem(bxcf::Vec2i& vecItemPositionChange, bxcf::Vec2i& vecItemSizeChange);

	void									renderItemNow(void);

	void									setActiveItem(void);

	CWindow*								getWindow(void);
	void									markToRedraw(void);

	void									applyHoverEffects(uint32 uiFragment = bxgx::styles::fragments::ALL_STYLE_FRAGMENTS);
	void									unapplyHoverEffects(void);

	virtual bool							applyCursorHoverIcon(void);

	bool									doesItemHaveFocus(void);

	bool									isPointInBoundingRectangle(bxcf::Vec2i& vecPoint, uint32 uiOuterSpacing);

protected:
	CGUILayer*								m_pLayer;

private:
	uint32									m_uiId;
};

#endif