#pragma once

#include "nsimgf.h"
#include "nsbxcf.h"
#include <string>
#include <vector>

struct imgf::TXDOrganizerWindowResult
{
	uint32							m_uiEveryNDFFFiles;
	std::string						m_strTXDNamePrefix;
	std::string						m_strTextureImportFolder;
	std::string						m_strIDEUpdateFolder;
	std::string						m_strOutputFolder;
	bxcf::RasterDataFormat*			m_vecTXDTextureFormat;
};