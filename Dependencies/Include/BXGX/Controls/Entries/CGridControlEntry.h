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

	void									setList(CGridControl *pList) { m_pList = pList; }
	CGridControl*							getList(void) { return m_pList; }
	
	std::vector<std::vector<std::string>>&	getText(void) { return m_vecText; }
	
private:
	CGridControl*							m_pList;
	std::vector<std::vector<std::string>>	m_vecText;
};

#endif