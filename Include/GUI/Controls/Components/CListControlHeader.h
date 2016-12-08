#ifndef CListControlHeader_H
#define CListControlHeader_H

#include "Type/Types.h"
#include "Controls/Components/CGUIControlComponent_Text.h"

class CListControlHeader : public CGUIControlComponent_Text
{
public:
	CListControlHeader(void);
	
	void									unload(void) {}

	void									setColumnWidth(uint32 uiColumnWidth) { m_uiColumnWidth = uiColumnWidth; }
	uint32									getColumnWidth(void) { return m_uiColumnWidth; }
	
private:
	uint32									m_uiColumnWidth;
};

#endif