#ifndef CIPLFormat_H
#define CIPLFormat_H

#include "bxgi.h"
#include "Helper/SectionLines/CSectionLinesFormat.h"
#include "eIPLSection.h"
#include "eIPLPathType.h"
#include "Entry/CIPLEntry_Other.h"
#include "Entry/CIPLEntry_Section.h"
#include "Entry/CIPLEntry_Data.h"
#include <string>

class bxgi::CIPLFormat;
class bxgi::CIPLEntry;

class bxgi::CIPLFormat : public bxgi::CSectionLinesFormat<bxgi::CIPLFormat, bxgi::CIPLEntry, eIPLSection, bxgi::CIPLEntry_Other, bxgi::CIPLEntry_Section, bxgi::CIPLEntry_Data>
{
public:
	CIPLFormat(void);

	void												setIsBinary(bool bState) { m_bIsBinary = bState; }
	bool												isBinary(void) { return m_bIsBinary; }

	bxgi::CIPLEntry_Data*								createDataEntry(eIPLSection eIDESectionValue, uint32 uiSectionSpecificType = 0);

	eIPLSection											getSectionFromText(std::string strIPLSectionText);
	std::string											getSectionText(eIPLSection eIPLSectionValue);

	uint32												detectSectionSpecificType(eIPLSection eIPLSectionValue);

private:
	void												unserialize(void);
	void												serialize(void);

	void												unserializeBinary(void);
	void												serializeBinary(void);

	bxgi::CIPLEntry_Data*								unserializeDataEntry(eIPLSection eIPLSectionValue);

	eIPLPathType										detectPATHType(void);

private:
	uint8												m_bIsBinary : 1;
};

#endif