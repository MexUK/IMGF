#pragma once

#include "nsimgf.h"
#include "nsbxgi.h"
#include <string>

struct imgf::TXDBuilderWindowResult
{
	uint32					m_uiDFFFilesType;
	std::string				m_strIDEFilePath;
	std::string				m_strDFFsFolderPath;
	std::string				m_strTexturesBMPsFolderPath;
	std::string				m_strOutputFolderPath;
	uint32					m_uiTextureCountPerTXD;
	bxgi::ERWVersion		m_uiRWVersion;
};