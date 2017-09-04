#pragma once

#include "bxgx.h"
#include "Type/Types.h"
#include "Controls/Components/TextComponent.h"
#include <string>
#include <vector>

class bxgx::CGrid;

class bxgx::CGridRow : public bxgx::TextComponent
{
public:
	CGridRow(void);
	
	void									unload(void) {}

	void									setGrid(CGrid *pGrid);
	CGrid*							getGrid(void) { return m_pGrid; }
	
	void									setSelected(bool bSelected);
	bool									isSelected(void) { return m_bSelected; }

	std::vector<std::vector<std::string>>&	getText(void) { return m_vecText; }
	
	uint32									getRowIndex(void);

	bool									isRowDisplayedWithinScrollRange(void);

private:
	CGrid*							m_pGrid;
	uint8									m_bSelected;
	std::vector<std::vector<std::string>>	m_vecText;
};