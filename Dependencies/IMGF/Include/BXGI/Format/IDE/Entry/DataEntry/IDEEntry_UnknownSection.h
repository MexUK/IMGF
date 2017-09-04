#pragma once

#include "nsbxgi.h"
#include "Type/Types.h"
#include "Format/IDE/Entry/IDEEntry_Data.h"
#include <string>

class bxgi::IDEEntry_UnknownSection : public bxgi::IDEEntry_Data
{
public:
	IDEEntry_UnknownSection(bxgi::IDEFormat *pIDEFormat);

	void						unserialize(void);
	void						serialize(void);

	void						setLine(std::string& strLine) { m_strLine = strLine; }
	std::string&				getLine(void) { return m_strLine; }

private:
	std::string					m_strLine;
};