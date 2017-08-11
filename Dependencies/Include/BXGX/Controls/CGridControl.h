#ifndef CGridControl_H
#define CGridControl_H

#include "Type/Types.h"
#include "Control/CGUIControl.h"
#include "Styles/CGUIStyles.h"
#include "Controls/Entries/CGridControlEntry.h"
#include "Controls/Components/CGridControlHeader.h"
#include "Pool/CVectorPool.h"
#include "Type/Vector/Vec2i.h"
#include <string>
#include <vector>

class CGridControl : public CGUIControl, public bxcf::CVectorPool<CGridControlEntry*>
{
public:
	CGridControl(void);

	void										bindEvents(void);

	void										unserialize(bool bSkipControlId = false);
	void										serialize(void);

	bool										onLeftMouseDown(bxcf::Vec2i& vecCursorPosition);
	void										onRender(void);

	CGridControlHeader*							addHeader(std::string strHeaderText, uint32 uiColumnWidth);

	bxcf::Vec2i								getRowPosition(uint32 uiRowIndex);	// in pixels
	bxcf::Vec2u								getRowSize(void);					// in pixels

	bxcf::Vec2i								getCellTextPosition(uint32 uiRowIndex, uint32 uiTextRowIndex, uint32 uiColumnIndex);	// in pixels
	bxcf::Vec2u								getCellTextSize(uint32 uiRowIndex, uint32 uiTextRowIndex, uint32 uiColumnIndex);		// in pixels

	void										setRowHeight(uint32 uiRowHeight) { m_uiRowHeight = uiRowHeight; }	// in pixels
	uint32										getRowHeight(void) { return m_uiRowHeight; }						// in pixels

	uint32										getRowFillColour1(void) { return getStyles()->getStyle<uint32>("row-fill-colour-1"); }	// RGBA
	uint32										getRowFillColour2(void) { return getStyles()->getStyle<uint32>("row-fill-colour-2"); }	// RGBA
	
	void										setColumnWidth(uint32 uiColumnWidth) { m_uiColumnWidth = uiColumnWidth; }	// in pixels
	uint32										getColumnWidth(void) { return m_uiColumnWidth; }							// in pixels

	void										setRowTextHeight(uint32 uiRowTextHeight) { m_uiRowTextHeight = uiRowTextHeight; }	// in pixels
	uint32										getRowTextHeight(void) { return m_uiRowTextHeight; }								// in pixels

	void										setHasVerticalScrollBar(bool bHasVerticalScrollBar) { m_bHasVerticalScrollBar = bHasVerticalScrollBar; }
	bool										doesHaveVerticalScrollBar(void) { return m_bHasVerticalScrollBar; }
	
	bxcf::CVectorPool<CGridControlHeader*>&		getHeaders(void) { return m_vecHeaders; }

private:
	uint32										m_uiRowHeight;				// in pixels
	uint32										m_uiColumnWidth;			// in pixels
	uint32										m_uiRowTextHeight;			// in pixels
	uint8										m_bHasVerticalScrollBar		: 1;
	bxcf::CVectorPool<CGridControlHeader*>		m_vecHeaders;
};

#endif