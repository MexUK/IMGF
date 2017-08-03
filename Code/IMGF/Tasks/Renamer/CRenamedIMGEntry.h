#ifndef CRenamedIMGEntry_H
#define CRenamedIMGEntry_H

#include "bxcf.h"

struct CRenamedIMGEntry
{
	bxcf::CIMGEntry*			m_pIMGEntry;
	std::string					m_strPreviousName;
};

#endif