#pragma once

#include "nsimgf.h"
#include "nsbxgi.h"

struct imgf::CRenamedIMGEntry
{
	bxgi::CIMGEntry*			m_pIMGEntry;
	std::string					m_strPreviousName;
};