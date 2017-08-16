#ifndef CGridControlEntry_H
#define CGridControlEntry_H

#include "Type/Types.h"
#include "Controls/Components/CGUIControlComponent_Text.h"
#include <string>
#include <vector>

class CGridControl;

class CGridControlEntry : public CGUIControlComponent_Text
{
public:
	CGridControlEntry(void);
	
	void									unload(void) {}

	void									setGrid(CGridControl *pGrid);
	CGridControl*							getGrid(void) { return m_pGrid; }
	
	void									setSelected(bool bSelected);
	bool									isSelected(void) { return m_bSelected; }

	std::vector<std::vector<std::string>>&	getText(void) { return m_vecText; }
	
private:
	CGridControl*							m_pGrid;
	uint8									m_bSelected;
	std::vector<std::vector<std::string>>	m_vecText;
};

#endif