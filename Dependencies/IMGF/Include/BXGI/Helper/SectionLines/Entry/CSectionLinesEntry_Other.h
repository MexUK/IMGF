#pragma once

#include "nsbxgi.h"
#include <string>

class bxgi::CSectionLinesEntry_Other
{
public:
	void						setLine(std::string& strLine) { m_strLine = strLine; }
	std::string&				getLine(void) { return m_strLine; }

private:
	std::string					m_strLine;
};