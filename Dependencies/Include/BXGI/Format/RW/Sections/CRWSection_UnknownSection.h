#ifndef CRWSection_UnknownSection_H
#define CRWSection_UnknownSection_H

#include "bxgi.h"
#include "Format/RW/CRWSection.h"
#include <string>

class bxgi::CRWSection_UnknownSection : public bxgi::CRWSection
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