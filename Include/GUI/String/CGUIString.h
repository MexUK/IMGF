#ifndef CGUIString_H
#define CGUIString_H

#include "Type/Types.h"
#include "Type/Vector/CSize2D.h"
#include <string>

class CGUIString
{
public:
	void							setSize(bxa::CSize2D& vecSize) { m_vecSize = vecSize; }
	bxa::CSize2D&						getSize(void) { return m_vecSize; }

	void							setString(std::string& strString) { m_strString = strString; }
	std::string&					getString(void) { return m_strString; }

private:
	bxa::CSize2D							m_vecSize;
	std::string						m_strString;
};

#endif