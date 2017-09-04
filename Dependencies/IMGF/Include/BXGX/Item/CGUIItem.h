#ifndef CGUIItem_H
#define CGUIItem_H

#include "Type/Vector/Vec2i.h"
#include "Type/Vector/Vec2i.h"
#include "Type/Vector/Vec2u.h"
#include "Styles/CGUIStyleableEntity.h"
#include "Renderable/CRenderable.h"
#include "Styles/StyleEnums.h"
#include <unordered_map>
#include <Windows.h> // for HCURSOR

class CGUILayer;
class CWindow;

class CGUIItem : public CGUIStyleableEntity, public CRenderable
{
public:
	CGUIItem(void);
	virtual ~CGUIItem(void) {}

	void									unload(void) {}

	virtual void							unserialize(bool bSkipItemId = false)	= 0;
	virtual void							serialize(void)							= 0;

	virtual void							bindEvents(void) {}
	virtual void							unbindEvents(void) {}

	void									setLayer(CGUILayer* pLayer) { m_pLayer = pLayer; }
	CGUILayer*								getLayer(void) { return m_pLayer; }

	void									setId(uint32 uiId) { m_uiId = uiId; }
	uint32									getId(void) { return m_uiId; }

	void									setHoverCursor(char *pHoverIcon);
	void									setHoverCursor(HCURSOR hHoverCursor) { m_hHoverCursor = hHoverCursor; }
	HCURSOR									getHoverCursor(void) { return m_hHoverCursor; }
	void									applyHoverCursor(void);

	void									applyDefaultCursor(void);
	
	void									applyCursor(void);
	void									applyCursor(char *pCursorIcon);

	virtual bxcf::Vec2i						getBoundingRectanglePosition(void)						= 0;
	virtual bxcf::Vec2u						getBoundingRectangleSize(void)							= 0;
	virtual void							moveItem(bxcf::Vec2i& vecItemPositionChange)			= 0;
	virtual void							resizeItemViaOffsets(bxcf::Vec2i& vecItemSizeChange)	= 0;

	void									onMoveItem(bxcf::Vec2i& vecItemPositionChange);
	void									onResizeItem(bxcf::Vec2i& vecItemPositionChange, bxcf::Vec2i& vecItemSizeChange);

	void									setActiveItem(void);

	CWindow*								getWindow(void);
	
	void									render(void);
	void									renderNow(void);

	void									applyHoverEffects(bxgx::styles::fragments::EStyleFragment uiFragment = bxgx::styles::fragments::ALL_STYLE_FRAGMENTS);
	void									unapplyHoverEffects(void);

	bool									doesItemHaveFocus(void);

	bool									isPointInBoundingRectangle(bxcf::Vec2i& vecPoint, uint32 uiOuterSpacing);

protected:
	CGUILayer*								m_pLayer;

private:
	uint32									m_uiId;
	HCURSOR									m_hHoverCursor;
};

#endif