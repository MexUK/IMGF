#pragma once

#include "nsbxgi.h"
#include "Type/Types.h"
#include "Format/IDE/Entry/IDEEntry_Data.h"
#include <string>

class bxgi::IDEEntry_WEAP : public bxgi::IDEEntry_Data
{
public:
	IDEEntry_WEAP(bxgi::IDEFormat *pIDEFormat);

	void						unserialize(void);
	void						serialize(void);

	void						setObjectId(uint32 uiObjectId) { m_uiObjectId = uiObjectId; }
	uint32						getObjectId(void) { return m_uiObjectId; }

	void						setModelName(std::string& strModelName) { m_strModelName = strModelName; }
	std::string&				getModelName(void) { return m_strModelName; }

	void						setTXDName(std::string& strTXDName) { m_strTXDName = strTXDName; }
	std::string&				getTXDName(void) { return m_strTXDName; }

	void						setAnimationName(std::string& strAnimationName) { m_strAnimationName = strAnimationName; }
	std::string&				getAnimationName(void) { return m_strAnimationName; }

	void						setClumpCount(uint32 uiClumpCount) { m_uiClumpCount = uiClumpCount; }
	uint32						getClumpCount(void) { return m_uiClumpCount; }

	void						setDrawDistance(float32 fDrawDistance) { m_fDrawDistance = fDrawDistance; }
	float32						getDrawDistance(void) { return m_fDrawDistance; }

	void						setFlags(uint32 uiFlags) { m_uiFlags = uiFlags; }
	uint32						getFlags(void) { return m_uiFlags; }

private:
	// GTA III era & GA IV only
	std::string					m_strModelName;
	std::string					m_strTXDName;
	std::string					m_strAnimationName;
	uint32						m_uiClumpCount;
	float32						m_fDrawDistance;
	uint32						m_uiFlags;

	// GTA III era only
	uint32						m_uiObjectId;
};