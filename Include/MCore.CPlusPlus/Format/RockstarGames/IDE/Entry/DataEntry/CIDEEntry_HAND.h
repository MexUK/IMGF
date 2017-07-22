#ifndef CIDEEntry_HAND_H
#define CIDEEntry_HAND_H

#include "bxa.h"
#include "Type/Types.h"
#include "Format/RockstarGames/IDE/Entry/CIDEEntry_Data.h"
#include <string>

class bxa::CIDEEntry_HAND : public bxa::CIDEEntry_Data
{
public:
	CIDEEntry_HAND(bxa::CIDEFormat *pIDEFormat) :
		CIDEEntry_Data(pIDEFormat, IDE_SECTION_HAND),
		m_uiObjectId(0)
	{
	};

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

#endif