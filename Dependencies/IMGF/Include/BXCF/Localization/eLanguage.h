#pragma once

// The order of entries in this enum should not change, as language enum ids will be stored into the registry.

#include "nsbxcf.h"
#include "Type/Types.h"

enum bxcf::ELanguage
{
	LANGUAGE_UNKNOWN,
	LANGUAGE_ENGLISH,
	LANGUAGE_CZECH,
	LANGUAGE_DUTCH,
	LANGUAGE_GERMAN
};