#pragma once

#include "nsbxgx.h"
#include "Type/Types.h"
#include "Control/Control.h"
#include "Pool/CVectorPool.h"
#include "Controls/Entries/CDropDownItem.h"
#include "Controls/Components/TextComponent.h"
#include "Type/Vector/Vec2i.h"
#include "Type/Vector/Vec2u.h"
#include <string>

class bxgx::CDropDown : public bxgx::Control, public bxcf::CVectorPool<CDropDownItem*>, public bxgx::TextComponent
{
public:
	CDropDown(void);

	void									bindEvents(void);

	void									unserialize(bool bSkipControlId = false);
	void									serialize(void);

	bool									onLeftMouseDown(bxcf::Vec2i& vecCursorPosition);
	bool									onLeftMouseUp(bxcf::Vec2i& vecCursorPosition);
	bool									onMouseMove(bxcf::Vec2i& vecCursorPosition);
	bool									onMouseEnter(bxcf::Vec2i& vecCursorPosition);
	bool									onMouseExit(bxcf::Vec2i& vecCursorPosition);
	void									onRender(void);
	void									onRenderAfter(void);

	bool									doesControlUsePosition(bxcf::Vec2i& vecPoint) { return true; }

	CDropDownItem*						addItem(std::string strItemText, bool bIsActiveItem = false, bool bIsSelectable = true);
	void									addItems(std::vector<std::string>& vecItems);
	void									removeItem(CDropDownItem *pDropEntry);
	void									reset(void);
	int32									getSelectedItemIndex(void);

	bxcf::Vec2i								getBoundingRectanglePosition(void);
	bxcf::Vec2u								getBoundingRectangleSize(void);
	bool									isPointInSelectionList(bxcf::Vec2i& vecPoint);

	bxcf::Vec2i								getSelectionListPosition(void);
	bxcf::Vec2u								getSelectionListSize(void);
	bxcf::Vec2u								getSelectionListSizeWithButton(void);
	bxcf::Vec2i								getSelectionListEntryPosition(uint32 uiEntryIndex);
	bxcf::Vec2u								getSelectionListEntrySize(void);
	uint32									getSelectionListEntryFromPoint(bxcf::Vec2i& vecCursorPosition);

	void									setSize(bxcf::Vec2u& vecSize);

	void									setActiveItem(CDropDownItem *pDropEntry) { m_pActiveItem = pDropEntry; }
	CDropDownItem*						getActiveItem(void) { return m_pActiveItem; }
	
	void									setListWidth(uint32 uiListWidth) { m_uiListWidth = uiListWidth; }	// in pixels
	uint32									getListWidth(void) { return m_uiListWidth; }						// in pixels

	void									setListRowHeight(uint32 uiListRowHeight) { m_uiListRowHeight = uiListRowHeight; }	// in pixels
	uint32									getListRowHeight(void) { return m_uiListRowHeight; }								// in pixels

	void									setSelectionListOpen(bool bSelectionListOpen);
	bool									isSelectionListOpen(void) { return m_bSelectionListOpen; }

private:
	bxcf::Vec2i								getDropTrianglePosition(void);
	float32									getDropTriangleSideLength(void);
	float32									getDropTriangleSideHeight(void);

	void									recalculateListWidth(void);

private:
	uint32									m_uiListWidth;		// in pixels
	uint32									m_uiListRowHeight;	// in pixels
	uint8									m_bSelectionListOpen				: 1;
	CDropDownItem*						m_pActiveItem;
};