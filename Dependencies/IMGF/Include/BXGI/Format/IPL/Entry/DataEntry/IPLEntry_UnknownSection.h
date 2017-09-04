#pragma once

#include "nsbxgi.h"
#include "Type/Types.h"
#include "Format/IPL/Entry/IPLEntry_Data.h"
#include <string>

class bxgi::IPLEntry_UnknownSection : public bxgi::IPLEntry_Data
{
public:
	IPLEntry_UnknownSection(bxgi::IPLFormat *pIPLFormat);

	void						unserialize(void);
	void						serialize(void);

	void						setLine(std::string& strLine) { m_strLine = strLine; }
	std::string&				getLine(void) { return m_strLine; }

private:
	std::string					m_strLine;
};