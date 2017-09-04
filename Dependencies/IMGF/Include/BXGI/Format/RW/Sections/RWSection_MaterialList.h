#pragma once

#include "nsbxgi.h"
#include "Format/RW/RWSection.h"
#include <string>

class bxgi::RWSection_MaterialList : public bxgi::RWSection
{
public:
	RWSection_MaterialList(void);

	void							unserialize(void);
	void							serialize(void);

	void							setMaterialCount(uint32 uiMaterialCount) { m_uiMaterialCount = uiMaterialCount; }
	uint32							getMaterialCount(void) { return m_uiMaterialCount; }

	void							setReservedValues(std::string& strReservedValues) { m_strReservedValues = strReservedValues; }
	std::string&					getReservedValues(void) { return m_strReservedValues; }

private:
	uint32							m_uiMaterialCount;
	std::string						m_strReservedValues;
};