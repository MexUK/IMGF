#ifndef CRenamedIMGEntry_H
#define CRenamedIMGEntry_H

#include "mcore.h"

struct CRenamedIMGEntry
{
	mcore::CIMGEntry*			m_pIMGEntry;
	std::string					m_strPreviousName;
};

#endif