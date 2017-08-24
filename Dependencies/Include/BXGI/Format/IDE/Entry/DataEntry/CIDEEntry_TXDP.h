#ifndef CIDEEntry_TXDP_H
#define CIDEEntry_TXDP_H

#include "bxgi.h"
#include "Format/IDE/Entry/CIDEEntry_Data.h"
#include <string>

class bxgi::CIDEEntry_TXDP : public bxgi::CIDEEntry_Data
{
public:
	CIDEEntry_TXDP(bxgi::CIDEFormat *pIDEFormat) :
		CIDEEntry_Data(pIDEFormat, IDE_SECTION_TXDP)
	{
	};

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

#endif