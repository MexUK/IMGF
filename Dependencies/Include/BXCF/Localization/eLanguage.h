#ifndef eLanguage_H
#define eLanguage_H

// The order of entries in this enum should not change, as language enum ids will be stored into the registry.

#include "bxcf.h"
#include "Type/Types.h"

enum bxcf::eLanguage : uint8
{
	LANGUAGE_UNKNOWN,
	LANGUAGE_ENGLISH,
	LANGUAGE_CZECH,
	LANGUAGE_DUTCH,
	LANGUAGE_GERMAN
};

#endif