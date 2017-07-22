#ifndef CSectionLinesEntry_Other_H
#define CSectionLinesEntry_Other_H

#include "BXA.h"
#include <string>

class bxa::CSectionLinesEntry_Other
{
public:
	void						setLine(std::string& strLine) { m_strLine = strLine; }
	std::string&				getLine(void) { return m_strLine; }

private:
	std::string					m_strLine;
};

#endif