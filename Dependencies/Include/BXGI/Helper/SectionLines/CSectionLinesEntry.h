#ifndef CSectionLinesEntry_H
#define CSectionLinesEntry_H

#include "bxgi.h"
#include "Type/Types.h"
#include "eSectionLinesEntryType.h"
#include <string>

template<class FormatClass, typename SectionEnum>
class bxgi::CSectionLinesEntry
{
public:
	CSectionLinesEntry(FormatClass *pFormat) :
		m_pFormat(pFormat),
		m_eEntryType(SECTION_LINES_ENTRY_UNKNOWN),
		m_eSectionType((SectionEnum)0),
		m_ucFormatType(0)
	{
	};

	virtual void				unload(void) {}

	virtual void				unserialize(void) = 0;
	virtual void				serialize(void) = 0;

	void						setFormat(FormatClass* pFormat) { m_pFormat = pFormat; }
	FormatClass*				getFormat(void) { return m_pFormat; }

	void						setEntryType(bxgi::eSectionLinesEntryType eEntryType) { m_eEntryType = eEntryType; }
	bxgi::eSectionLinesEntryType		getEntryType(void) { return m_eEntryType; }

	void						setSectionType(SectionEnum eSectionValue) { m_eSectionType = eSectionValue; }
	SectionEnum					getSectionType(void) { return m_eSectionType; }

	void						setComment(std::string& strComment) { m_strComment = strComment; }
	std::string&				getComment(void) { return m_strComment; }

	void						setFormatType(uint8 ucFormatType) { m_ucFormatType = ucFormatType; }
	uint8						getFormatType(void) { return m_ucFormatType; }

private:
	FormatClass*				m_pFormat;
	bxgi::eSectionLinesEntryType		m_eEntryType;
	SectionEnum					m_eSectionType;
	std::string					m_strComment;
	uint8						m_ucFormatType;
};

#endif