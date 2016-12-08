#ifndef CSectionLinesEntry_Other_H
#define CSectionLinesEntry_Other_H

#include "mcore.h"
#include <string>

class mcore::CSectionLinesEntry_Other
{
public:
	void						setLine(std::string& strLine) { m_strLine = strLine; }
	std::string&				getLine(void) { return m_strLine; }

private:
	std::string					m_strLine;
};

#endif