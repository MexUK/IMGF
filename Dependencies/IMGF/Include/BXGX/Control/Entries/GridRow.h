#pragma once

#include "bxgx.h"
#include "Type/Types.h"
#include "Control/Components/TextComponent.h"
#include <string>
#include <vector>

class bxgx::Grid;

class bxgx::GridRow : public bxgx::TextComponent
{
public:
	GridRow(void);
	
	void									unload(void) {}

	void									setGrid(Grid *pGrid);
	Grid*							getGrid(void) { return m_pGrid; }
	
	void									setSelected(bool bSelected);
	bool									isSelected(void) { return m_bSelected; }

	std::vector<std::vector<std::string>>&	getText(void) { return m_vecText; }
	
	uint32									getRowIndex(void);

	bool									isRowDisplayedWithinScrollRange(void);

private:
	Grid*							m_pGrid;
	uint8									m_bSelected;
	std::vector<std::vector<std::string>>	m_vecText;
};