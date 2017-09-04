#pragma once

#include "nsbxgi.h"
#include "Format/IDE/Entry/DataEntry/IDEEntry_PATH.h"
#include "Pool/VectorPool.h"
#include <string>

class bxgi::IDEEntry;

class bxgi::IDEEntry_PATH_Group : public bxgi::IDEEntry_PATH, public bxcf::VectorPool<bxgi::IDEEntry*>
{
public:
	IDEEntry_PATH_Group(bxgi::IDEFormat *pIDEFormat);

	void							unload(void);

	void							unserialize(void);
	void							serialize(void);

	void							setGroupType(std::string& strGroupType) { m_strGroupType = strGroupType; }
	std::string&					getGroupType(void) { return m_strGroupType; }

	void							setObjectId(uint32 uiObjectId) { m_uiObjectId = uiObjectId; }
	uint32							getObjectId(void) { return m_uiObjectId; }

	void							setModelName(std::string& strModelName) { m_strModelName = strModelName; }
	std::string&					getModelName(void) { return m_strModelName; }

private:
	// GTA III era only
	std::string						m_strGroupType;
	uint32							m_uiObjectId;
	std::string						m_strModelName;
};