#ifndef CRenamedIMGEntry_H
#define CRenamedIMGEntry_H

#include "bxa.h"

struct CRenamedIMGEntry
{
	bxa::CIMGEntry*			m_pIMGEntry;
	std::string					m_strPreviousName;
};

#endif