#ifndef CRWSection_MaterialList_H
#define CRWSection_MaterialList_H

#include "mcore.h"
#include "Format/RenderWare/Helper/BinaryStream/CRWSection.h"
#include <string>

class mcore::CRWSection_MaterialList : public mcore::CRWSection
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