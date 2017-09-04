#ifndef CRWSection_UnknownSection_H
#define CRWSection_UnknownSection_H

#include "bxcf.h"
#include "Format/RenderWare/Helper/BinaryStream/CRWSection.h"
#include <string>

class bxcf::CRWSection_UnknownSection : public bxcf::CRWSection
{
public:
	CRWSection_UnknownSection(void);

	void							unserialize(void);
	void							serialize(void);

	void							setActualSectionId(uint32 uiActualSectionId) { m_uiActualSectionId = uiActualSectionId; }
	uint32							getActualSectionId(void) { return m_uiActualSectionId; }

	void							setData(std::string& strData) { m_strData = strData; }
	std::string&					getData(void) { return m_strData; }

private:
	uint32							m_uiActualSectionId;
	std::string						m_strData;
};

#endif