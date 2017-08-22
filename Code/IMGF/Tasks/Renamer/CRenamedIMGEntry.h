#ifndef CRenamedIMGEntry_H
#define CRenamedIMGEntry_H

#include "bxgi.h"

struct CRenamedIMGEntry
{
	bxgi::CIMGEntry*			m_pIMGEntry;
	std::string					m_strPreviousName;
};

#endif