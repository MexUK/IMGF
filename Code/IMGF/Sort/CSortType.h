#ifndef CSortType_H
#define CSortType_H

#include "eSortType.h"
#include <string>

class CSortType
{
public:
	void						unload(void) {}

	void						setType(eSortType eType) { m_eType = eType; }
	eSortType					getType(void) { return m_eType; }
	
	void						setText(std::string strText) { m_strText = strText; }
	std::string					getText(void);
	std::string					getTextForMenu(void);

private:
	eSortType					m_eType;
	std::string					m_strText;
};

#endif