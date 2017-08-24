#ifndef CRWSection_Extension_H
#define CRWSection_Extension_H

#include "bxgi.h"
#include "Format/RW/CRWSection.h"

class bxgi::CRWSection_Extension : public bxgi::CRWSection
{
public:
	CRWSection_Extension(void) { setSectionId(RW_SECTION_EXTENSION); }

	void							unserialize(void);
	void							serialize(void);
};

#endif