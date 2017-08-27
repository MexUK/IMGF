#pragma once

#include "nsbxgi.h"
#include "Type/Types.h"

enum bxgi::ESectionLinesEntryType : uint8
{
	SECTION_LINES_ENTRY_UNKNOWN,
	SECTION_LINES_ENTRY_SECTION,
	SECTION_LINES_ENTRY_DATA,
	SECTION_LINES_ENTRY_OTHER
};