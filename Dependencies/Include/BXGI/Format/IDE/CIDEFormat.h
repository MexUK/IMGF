#ifndef CIDEFormat_H
#define CIDEFormat_H

#include "bxgi.h"
#include "Type/Types.h"
#include "Helper/SectionLines/CSectionLinesFormat.h"
//#include "eDataType.h" // todo - no idea why this include is needed - it makes eIDESection underlined when not here
#include "eIDESection.h"
#include "Format/e2DFXType.h"
#include "eIDEPathType.h"
#include "Entry/CIDEEntry_Other.h"
#include "Entry/CIDEEntry_Section.h"
#include "Entry/CIDEEntry_Data.h"
#include <string>
#include <vector>

class bxgi::CIDEFormat;
class bxgi::CIDEEntry;

class bxgi::CIDEFormat : public bxgi::CSectionLinesFormat<bxgi::CIDEFormat, bxgi::CIDEEntry, bxgi::eIDESection, bxgi::CIDEEntry_Other, bxgi::CIDEEntry_Section, bxgi::CIDEEntry_Data>
{
public:
	CIDEFormat(void);

	bxgi::CIDEEntry_Data*								createDataEntry(eIDESection eIDESectionValue, uint32 uiSectionSpecificType = 0);
	
	template<class EntryClass2>
	std::vector<EntryClass2*>					getEntriesBySection(eIDESection eIDESectionValue, bxgi::e2DFXType e2DFXTypeValue = bxgi::_2DFX_UNKNOWN);

	eIDESection									getSectionFromText(std::string strIDESectionText);
	std::string									getSectionText(eIDESection eIDESectionValue);

	uint32										detectSectionSpecificType(eIDESection eIDESectionValue);

private:
	void										unserialize(void);
	void										serialize(void);

	bxgi::CIDEEntry_Data*								unserializeDataEntry(eIDESection eIDESectionValue);

	std::pair<bxgi::e2DFXType, uint32>				detect2DFXTypeAndGame(void);
	eIDEPathType								detectPATHType(void);
};

template<class EntryClass2>
std::vector<EntryClass2*>						bxgi::CIDEFormat::getEntriesBySection(eIDESection eIDESectionValue, bxgi::e2DFXType e2DFXTypeValue)
{
	if (eIDESectionValue != IDE_SECTION_2DFX || e2DFXTypeValue == bxgi::_2DFX_UNKNOWN)
	{
		return CSectionLinesFormat::getEntriesBySection<EntryClass2>(eIDESectionValue);
	}
	else
	{
		std::vector<EntryClass2*> vecDerivedEntries;
		for (EntryClass2* pIDEEntry : CSectionLinesFormat::getEntriesBySection<EntryClass2>(eIDESectionValue))
		{
			if (((CIDEEntry_2DFX*)pIDEEntry)->get2DFXType() == e2DFXTypeValue)
			{
				vecDerivedEntries.push_back(pIDEEntry);
			}
		}
		return vecDerivedEntries;
	}
}

#endif