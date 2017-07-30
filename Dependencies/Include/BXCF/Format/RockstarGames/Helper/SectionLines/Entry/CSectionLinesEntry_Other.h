#ifndef CSectionLinesEntry_Other_H
#define CSectionLinesEntry_Other_H

#include "bxcf.h"
#include <string>

class bxcf::CSectionLinesEntry_Other
{
public:
	void						setLine(std::string& strLine) { m_strLine = strLine; }
	std::string&				getLine(void) { return m_strLine; }

private:
	std::string					m_strLine;
};

#endif