#ifndef CListControlEntry_H
#define CListControlEntry_H

#include "Type/Types.h"
#include "Controls/Components/CGUIControlComponent_Text.h"
#include <string>
#include <vector>

class CListControl;

class CListControlEntry : public CGUIControlComponent_Text
{
public:
	CListControlEntry(void);
	
	void									unload(void) {}

	void									setList(CListControl *pList) { m_pList = pList; }
	CListControl*							getList(void) { return m_pList; }
	
	std::vector<std::vector<std::string>>&	getText(void) { return m_vecText; }
	
private:
	CListControl*							m_pList;
	std::vector<std::vector<std::string>>	m_vecText;
};

#endif