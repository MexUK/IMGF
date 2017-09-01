#pragma once

#include "nsimgf.h"
#include "ESortType.h"
#include <string>

class imgf::CSortType
{
public:
	void						unload(void) {}

	void						setType(ESortType eType) { m_uiType = eType; }
	ESortType					getType(void) { return m_uiType; }
	
	void						setText(std::string strText) { m_strText = strText; }
	std::string					getText(void);
	std::string					getTextForMenu(void);

private:
	ESortType					m_uiType;
	std::string					m_strText;
};