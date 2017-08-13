#ifndef CDropControl_H
#define CDropControl_H

#include "Type/Types.h"
#include "Control/CGUIControl.h"
#include "Pool/CVectorPool.h"
#include "Controls/Entries/CDropControlEntry.h"
#include "Controls/Components/CGUIControlComponent_Text.h"
#include "Type/Vector/Vec2i.h"
#include "Type/Vector/Vec2u.h"
#include <string>

class CDropControl : public CGUIControl, public bxcf::CVectorPool<CDropControlEntry*>, public CGUIControlComponent_Text
{
public:
	CDropControl(void);

	void									bindEvents(void);

	void									unserialize(bool bSkipControlId = false);
	void									serialize(void);

	bool									onLeftMouseDown(bxcf::Vec2i& vecCursorPosition);
	bool									onLeftMouseUp(bxcf::Vec2i& vecCursorPosition);
	bool									onMouseMove(bxcf::Vec2i& vecCursorPosition);
	bool									onMouseEnter(bxcf::Vec2i& vecCursorPosition);
	bool									onMouseExit(bxcf::Vec2i& vecCursorPosition);
	void									onRender(void);

	bool									applyCursorHoverIcon(void);

	CDropControlEntry*						addItem(std::string strItemText, bool bIsActiveItem = false, bool bIsSelectable = true);
	void									removeItem(CDropControlEntry *pDropEntry);
	
	bxcf::Vec2u								getBoundingRectangleSize(void);
	bool									isPointInSelectionList(bxcf::Vec2i& vecPoint);

	bxcf::Vec2i								getSelectionListPosition(void);
	bxcf::Vec2u								getSelectionListSize(void);
	bxcf::Vec2i								getSelectionListEntryPosition(uint32 uiEntryIndex);
	bxcf::Vec2u								getSelectionListEntrySize(void);
	uint32									getSelectionListEntryFromPoint(bxcf::Vec2i& vecCursorPosition);

	void									setSize(bxcf::Vec2u& vecSize);

	uint32									getActiveIndex(void);

	void									setActiveItem(CDropControlEntry *pDropEntry) { m_pActiveItem = pDropEntry; }
	CDropControlEntry*						getActiveItem(void) { return m_pActiveItem; }
	
	void									setListWidth(uint32 uiListWidth) { m_uiListWidth = uiListWidth; }	// in pixels
	uint32									getListWidth(void) { return m_uiListWidth; }						// in pixels

	void									setListRowHeight(uint32 uiListRowHeight) { m_uiListRowHeight = uiListRowHeight; }	// in pixels
	uint32									getListRowHeight(void) { return m_uiListRowHeight; }								// in pixels

	void									setSelectionListOpen(bool bSelectionListOpen) { m_bSelectionListOpen = bSelectionListOpen; }
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
	CDropControlEntry*						m_pActiveItem;
};

#endif