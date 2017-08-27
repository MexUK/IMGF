#pragma once

#include "nsbxgi.h"
#include "Type/Types.h"
#include "Helper/SectionLines/CSectionLinesFormat.h"
//#include "eDataType.h" // todo - no idea why this include is needed - it makes EIDESection underlined when not here
#include "EIDESection.h"
#include "Format/E2DFXType.h"
#include "EIDEPathType.h"
#include "Entry/CIDEEntry_Other.h"
#include "Entry/CIDEEntry_Section.h"
#include "Entry/CIDEEntry_Data.h"
#include <string>
#include <vector>

class bxgi::CIDEFormat;
class bxgi::CIDEEntry;

class bxgi::CIDEFormat : public bxgi::CSectionLinesFormat<bxgi::CIDEFormat, bxgi::CIDEEntry, bxgi::EIDESection, bxgi::CIDEEntry_Other, bxgi::CIDEEntry_Section, bxgi::CIDEEntry_Data>
{
public:
	CIDEFormat(void);

	bxgi::CIDEEntry_Data*								createDataEntry(EIDESection EIDESectionValue, uint32 uiSectionSpecificType = 0);
	
	template<class EntryClass2>
	std::vector<EntryClass2*>					getEntriesBySection(EIDESection EIDESectionValue, bxgi::E2DFXType E2DFXTypeValue = bxgi::_2DFX_UNKNOWN);

	EIDESection									getSectionFromText(std::string strIDESectionText);
	std::string									getSectionText(EIDESection EIDESectionValue);

	uint32										detectSectionSpecificType(EIDESection EIDESectionValue);

private:
	void										unserialize(void);
	void										serialize(void);

	bxgi::CIDEEntry_Data*								unserializeDataEntry(EIDESection EIDESectionValue);

	std::pair<bxgi::E2DFXType, uint32>				detect2DFXTypeAndGame(void);
	EIDEPathType								detectPATHType(void);
};

template<class EntryClass2>
std::vector<EntryClass2*>						bxgi::CIDEFormat::getEntriesBySection(EIDESection EIDESectionValue, bxgi::E2DFXType E2DFXTypeValue)
{
	if (EIDESectionValue != IDE_SECTION_2DFX || E2DFXTypeValue == bxgi::_2DFX_UNKNOWN)
	{
		return CSectionLinesFormat::getEntriesBySection<EntryClass2>(EIDESectionValue);
	}
	else
	{
		std::vector<EntryClass2*> vecDerivedEntries;
		for (EntryClass2* pIDEEntry : CSectionLinesFormat::getEntriesBySection<EntryClass2>(EIDESectionValue))
		{
			if (((CIDEEntry_2DFX*)pIDEEntry)->get2DFXType() == E2DFXTypeValue)
			{
				vecDerivedEntries.push_back(pIDEEntry);
			}
		}
		return vecDerivedEntries;
	}
}