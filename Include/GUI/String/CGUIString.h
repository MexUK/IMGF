#ifndef CGUIString_H
#define CGUIString_H

#include "Type/Types.h"
#include "Type/Vector/CSize2D.h"
#include <string>

class CGUIString
{
public:
	void							setSize(mcore::CSize2D& vecSize) { m_vecSize = vecSize; }
	mcore::CSize2D&						getSize(void) { return m_vecSize; }

	void							setString(std::string& strString) { m_strString = strString; }
	std::string&					getString(void) { return m_strString; }

private:
	mcore::CSize2D							m_vecSize;
	std::string						m_strString;
};

#endif