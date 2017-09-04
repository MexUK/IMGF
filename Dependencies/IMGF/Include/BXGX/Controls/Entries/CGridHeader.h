#pragma once

#include "bxgx.h"
#include "Type/Types.h"
#include "Controls/Components/TextComponent.h"

class bxgx::CGrid;

class bxgx::CGridHeader : public bxgx::TextComponent
{
public:
	CGridHeader(void);
	
	void									unload(void) {}

	void									setGrid(CGrid *pGrid) { m_pGrid = pGrid; }
	CGrid*							getGrid(void) { return m_pGrid; }

	void									setColumnWidth(uint32 uiColumnWidth) { m_uiColumnWidth = uiColumnWidth; }
	uint32									getColumnWidth(void) { return m_uiColumnWidth; }
	
private:
	CGrid*							m_pGrid;
	uint32									m_uiColumnWidth;
};