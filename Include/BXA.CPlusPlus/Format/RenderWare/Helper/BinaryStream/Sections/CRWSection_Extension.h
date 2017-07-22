#ifndef CRWSection_Extension_H
#define CRWSection_Extension_H

#include "BXA.h"
#include "Format/RenderWare/Helper/BinaryStream/CRWSection.h"
#include <string>

class bxa::CRWSection_Extension : public bxa::CRWSection
{
public:
	CRWSection_Extension(void) { setSectionId(RW_SECTION_EXTENSION); }

	void							unserialize(void);
	void							serialize(void);
};

#endif