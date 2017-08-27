#pragma once

#include "nsbxgi.h"
#include "Helper/SectionLines/CSectionLinesFormat.h"
#include "EIPLSection.h"
#include "EIPLPathType.h"
#include "Entry/CIPLEntry_Other.h"
#include "Entry/CIPLEntry_Section.h"
#include "Entry/CIPLEntry_Data.h"
#include <string>

class bxgi::CIPLFormat;
class bxgi::CIPLEntry;

class bxgi::CIPLFormat : public bxgi::CSectionLinesFormat<bxgi::CIPLFormat, bxgi::CIPLEntry, EIPLSection, bxgi::CIPLEntry_Other, bxgi::CIPLEntry_Section, bxgi::CIPLEntry_Data>
{
public:
	CIPLFormat(void);

	void												setIsBinary(bool bState) { m_bIsBinary = bState; }
	bool												isBinary(void) { return m_bIsBinary; }

	bxgi::CIPLEntry_Data*								createDataEntry(EIPLSection EIDESectionValue, uint32 uiSectionSpecificType = 0);

	EIPLSection											getSectionFromText(std::string strIPLSectionText);
	std::string											getSectionText(EIPLSection EIPLSectionValue);

	uint32												detectSectionSpecificType(EIPLSection EIPLSectionValue);

private:
	void												unserialize(void);
	void												serialize(void);

	void												unserializeBinary(void);
	void												serializeBinary(void);

	bxgi::CIPLEntry_Data*								unserializeDataEntry(EIPLSection EIPLSectionValue);

	EIPLPathType										detectPATHType(void);

private:
	uint8												m_bIsBinary : 1;
};