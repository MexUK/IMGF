#pragma once

#include "nsimgf.h"
#include "nsbxgi.h"

struct imgf::RenamedIMGEntry
{
	bxgi::IMGEntry*			m_pIMGEntry;
	std::string					m_strPreviousName;
};