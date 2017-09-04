#pragma once

#include "nsbxgi.h"
#include "Type/Types.h"
#include "Format/IDE/Entry/IDEEntry_Data.h"
#include <string>

class bxgi::IDEEntry_HAND : public bxgi::IDEEntry_Data
{
public:
	IDEEntry_HAND(bxgi::IDEFormat *pIDEFormat);

	void						unserialize(void);
	void						serialize(void);

	void						setObjectId(uint32 uiObjectId) { m_uiObjectId = uiObjectId; }
	uint32						getObjectId(void) { return m_uiObjectId; }

	void						setModelName(std::string& strModelName) { m_strModelName = strModelName; }
	std::string&				getModelName(void) { return m_strModelName; }

	void						setTXDName(std::string& strTXDName) { m_strTXDName = strTXDName; }
	std::string&				getTXDName(void) { return m_strTXDName; }

	void						setUnknown1(std::string& strUnknown1) { m_strUnknown1 = strUnknown1; }
	std::string&				getUnknown1(void) { return m_strUnknown1; }

private:
	// GTA III era only
	uint32						m_uiObjectId;
	std::string					m_strModelName;
	std::string					m_strTXDName;
	std::string					m_strUnknown1;
};