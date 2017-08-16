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

class CGridControl : public CGUIControl, public bxcf::CVectorPool<CGridControlEntry*>//, public bxcf::Clonable<CGridControl>
{
public:
	CGridControl(void);

	void										addScrollBars(void);

	void										bindEvents(void);

	void										unserialize(bool bSkipControlId = false);
	void										serialize(void);

	CGridControl*								clone(void);

	bool										onLeftMouseDown(bxcf::Vec2i& vecCursorPosition);
	bool										onKeyDown(uint16 uiKeyCode);
	bool										onMouseWheelMove(int16 iRotationDistance);
	void										onRender(void);

	CGridControlHeader*							addHeader(std::string strHeaderText, uint32 uiColumnWidth);

	uint32										getHeaderHeight(void);

	int32										getColumnStartPositionX(uint32 uiColumnIndex);

	bxcf::Vec2i									getRowPosition(uint32 uiRowIndex);	// in pixels
	bxcf::Vec2u									getRowSize(void);					// in pixels

	bxcf::Vec2i									getCellTextPosition(uint32 uiRowIndex, uint32 uiTextRowIndex, uint32 uiColumnIndex);	// in pixels
	bxcf::Vec2u									getCellTextSize(uint32 uiRowIndex, uint32 uiTextRowIndex, uint32 uiColumnIndex);		// in pixels

	void										selectAllRows(void);
	void										unselectAllRows(void);
	bool										isAnyRowSelected(void);
	bool										areAllRowsSelected(void);

	void										checkToScroll(void);
	void										scrollByRows(int32 iRowCount);
	void										scrollTo(float32 fProgress);
	float32										getScrollProgressIncreaseForControlLength(int32 iLength);

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
	uint32										m_uiPreviousSelectedRowIndex;
	uint32										m_uiFirstSelectedRowIndex;
	uint8										m_bHasVerticalScrollBar		: 1;
	bxcf::CVectorPool<CGridControlHeader*>		m_vecHeaders;
};

#endif