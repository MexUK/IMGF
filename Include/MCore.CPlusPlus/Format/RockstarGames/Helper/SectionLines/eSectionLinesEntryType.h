#ifndef eSectionLinesEntryType_H
#define eSectionLinesEntryType_H

#include "mcore.h"
#include "Type/Types.h"

enum mcore::eSectionLinesEntryType : uint8
{
	SECTION_LINES_ENTRY_UNKNOWN,
	SECTION_LINES_ENTRY_SECTION,
	SECTION_LINES_ENTRY_DATA,
	SECTION_LINES_ENTRY_OTHER
};

#endif