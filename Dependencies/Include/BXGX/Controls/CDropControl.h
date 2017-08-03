#ifndef CDropControl_H
#define CDropControl_H

#include "Type/Types.h"
#include "Control/CGUIControl.h"
#include "Pool/CVectorPool.h"
#include "Controls/Entries/CDropControlEntry.h"
#include "Type/Vector/CPoint2D.h"
#include "Type/Vector/CSize2D.h"
#include <string>

class CDropControl : public CGUIControl, public bxcf::CVectorPool<CDropControlEntry*>
{
public:
	CDropControl(void);

	void									bindEvents(void);

	void									unserialize(bool bSkipControlId = false);
	void									serialize(void);

	bool									onLeftMouseUp(bxcf::CPoint2D& vecCursorPosition);
	bool									onRender(void);

	CDropControlEntry*						addItem(std::string strItemText, bool bIsActiveItem = false);
	void									removeItem(CDropControlEntry *pDropEntry);

	bool									isPointInControl(bxcf::CPoint2D& vecPoint);
	bool									isPointInSelectionList(bxcf::CPoint2D& vecPoint);

	bxcf::CPoint2D								getSelectionListPosition(void);
	bxcf::CSize2D									getSelectionListSize(void);
	bxcf::CPoint2D								getSelectionListEntryPosition(uint32 uiEntryIndex);
	bxcf::CSize2D									getSelectionListEntrySize(void);
	uint32									getSelectionListEntryFromPoint(bxcf::CPoint2D& vecCursorPosition);

	void									setSize(bxcf::CSize2D& vecSize);

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
	bxcf::CPoint2D								getDropTrianglePosition(void);
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