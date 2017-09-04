#pragma once

#include "nsbxgi.h"
#include "Format/RW/RWSection.h"

class bxgi::RWSection_Extension : public bxgi::RWSection
{
public:
	RWSection_Extension(void) { setSectionId(RW_SECTION_EXTENSION); }

	void							unserialize(void);
	void							serialize(void);
};