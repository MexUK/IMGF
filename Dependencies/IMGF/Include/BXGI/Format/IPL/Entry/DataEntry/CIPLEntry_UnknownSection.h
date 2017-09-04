#pragma once

#include "nsbxgi.h"
#include "Type/Types.h"
#include "Format/IPL/Entry/CIPLEntry_Data.h"
#include <string>

class bxgi::CIPLEntry_UnknownSection : public bxgi::CIPLEntry_Data
{
public:
	CIPLEntry_UnknownSection(bxgi::CIPLFormat *pIPLFormat);

	void						unserialize(void);
	void						serialize(void);

	void						setLine(std::string& strLine) { m_strLine = strLine; }
	std::string&				getLine(void) { return m_strLine; }

private:
	std::string					m_strLine;
};