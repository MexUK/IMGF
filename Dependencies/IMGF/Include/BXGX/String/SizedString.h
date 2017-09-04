#pragma once

#include "nsbxgx.h"
#include "Type/Types.h"
#include "Type/Vector/Vec2u.h"
#include <string>

class bxgx::SizedString
{
public:
	SizedString(void);

	void							setSize(bxcf::Vec2u& vecSize) { m_vecSize = vecSize; }
	bxcf::Vec2u&					getSize(void) { return m_vecSize; }

	void							setString(std::string& strString) { m_strString = strString; }
	std::string&					getString(void) { return m_strString; }

private:
	bxcf::Vec2u						m_vecSize;
	std::string						m_strString;
};