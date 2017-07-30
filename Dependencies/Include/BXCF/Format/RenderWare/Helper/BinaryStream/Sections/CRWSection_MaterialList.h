#ifndef CRWSection_MaterialList_H
#define CRWSection_MaterialList_H

#include "bxcf.h"
#include "Format/RenderWare/Helper/BinaryStream/CRWSection.h"
#include <string>

class bxcf::CRWSection_MaterialList : public bxcf::CRWSection
{
public:
	CRWSection_MaterialList(void);

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

#endif