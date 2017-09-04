#pragma once

#include "nsbxgi.h"
#include "Helper/SectionLines/SectionLinesFormat.h"
#include "EIPLSection.h"
#include "EIPLPathType.h"
#include "Entry/IPLEntry_Other.h"
#include "Entry/IPLEntry_Section.h"
#include "Entry/IPLEntry_Data.h"
#include <string>

class bxgi::IPLFormat;
class bxgi::IPLEntry;

class bxgi::IPLFormat : public bxgi::SectionLinesFormat<bxgi::IPLFormat, bxgi::IPLEntry, EIPLSection, bxgi::IPLEntry_Other, bxgi::IPLEntry_Section, bxgi::IPLEntry_Data>
{
public:
	IPLFormat(void);

	void												setIsBinary(bool bState) { m_bIsBinary = bState; }
	bool												isBinary(void) { return m_bIsBinary; }

	bxgi::IPLEntry_Data*								createDataEntry(EIPLSection EIDESectionValue, uint32 uiSectionSpecificType = 0);

	EIPLSection											getSectionFromText(std::string strIPLSectionText);
	std::string											getSectionText(EIPLSection EIPLSectionValue);

	uint32												detectSectionSpecificType(EIPLSection EIPLSectionValue);

private:
	void												unserialize(void);
	void												serialize(void);

	void												unserializeBinary(void);
	void												serializeBinary(void);

	bxgi::IPLEntry_Data*								unserializeDataEntry(EIPLSection EIPLSectionValue);

	EIPLPathType										detectPATHType(void);

private:
	uint8												m_bIsBinary : 1;
};