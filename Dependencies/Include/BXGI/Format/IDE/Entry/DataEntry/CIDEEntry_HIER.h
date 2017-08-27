#pragma once

#include "nsbxgi.h"
#include "Type/Types.h"
#include "Format/IDE/Entry/CIDEEntry_Data.h"
#include <string>

class bxgi::CIDEEntry_HIER : public bxgi::CIDEEntry_Data
{
public:
	CIDEEntry_HIER(bxgi::CIDEFormat *pIDEFormat);

	void						unserialize(void);
	void						serialize(void);

	void						setObjectId(uint32 uiObjectId) { m_uiObjectId = uiObjectId; }
	uint32						getObjectId(void) { return m_uiObjectId; }

	void						setModelName(std::string& strModelName) { m_strModelName = strModelName; }
	std::string&				getModelName(void) { return m_strModelName; }

	void						setTXDName(std::string& strTXDName) { m_strTXDName = strTXDName; }
	std::string&				getTXDName(void) { return m_strTXDName; }

private:
	// GTA III era & GTA IV
	uint32						m_uiObjectId;
	std::string					m_strModelName;
	std::string					m_strTXDName;
};