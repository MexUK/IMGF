#pragma once

#include "nsbxgi.h"
#include "Format/IDE/Entry/IDEEntry_Data.h"
#include <string>

class bxgi::IDEEntry_TXDP : public bxgi::IDEEntry_Data
{
public:
	IDEEntry_TXDP(bxgi::IDEFormat *pIDEFormat);

	void						unserialize(void);
	void						serialize(void);

	void						setTXDName(std::string& strTXDName) { m_strTXDName = strTXDName; }
	std::string&				getTXDName(void) { return m_strTXDName; }

	void						setParentTXDName(std::string& strParentTXDName) { m_strParentTXDName = strParentTXDName; }
	std::string&				getParentTXDName(void) { return m_strParentTXDName; }

private:
	// GTA III era & GTA IV (Only GTA SA in GTA III era)
	std::string					m_strTXDName;
	std::string					m_strParentTXDName;
};