#ifndef CGridControlHeader_H
#define CGridControlHeader_H

#include "Type/Types.h"
#include "Controls/Components/CGUIControlComponent_Text.h"

class CGridControl;

class CGridControlHeader : public CGUIControlComponent_Text, public CGUIStyleableEntity
{
public:
	CGridControlHeader(void);
	
	void									unload(void) {}

	void									setGrid(CGridControl *pGrid) { m_pGrid = pGrid; }
	CGridControl*							getGrid(void) { return m_pGrid; }

	void									setColumnWidth(uint32 uiColumnWidth) { m_uiColumnWidth = uiColumnWidth; }
	uint32									getColumnWidth(void) { return m_uiColumnWidth; }
	
private:
	CGridControl*							m_pGrid;
	uint32									m_uiColumnWidth;
};

#endif