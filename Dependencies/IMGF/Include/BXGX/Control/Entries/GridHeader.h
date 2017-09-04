#pragma once

#include "bxgx.h"
#include "Type/Types.h"
#include "Control/Components/TextComponent.h"

class bxgx::Grid;

class bxgx::GridHeader : public bxgx::TextComponent
{
public:
	GridHeader(void);
	
	void									unload(void) {}

	void									setGrid(Grid *pGrid) { m_pGrid = pGrid; }
	Grid*							getGrid(void) { return m_pGrid; }

	void									setColumnWidth(uint32 uiColumnWidth) { m_uiColumnWidth = uiColumnWidth; }
	uint32									getColumnWidth(void) { return m_uiColumnWidth; }
	
private:
	Grid*							m_pGrid;
	uint32									m_uiColumnWidth;
};