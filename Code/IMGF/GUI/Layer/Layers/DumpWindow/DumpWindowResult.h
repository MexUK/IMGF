#pragma once

#include <string>
#include <vector>
#include "nsimgf.h"
#include "nsbxgi.h"
// todo #include "Control/Controls/CheckBox.h"

struct imgf::DumpWindowResult
{
	bool										m_bCancelled;
	uint32										m_uiDumpType;
	std::string									m_strGameFolderPath;
	std::vector<std::string>					m_vecDATFilePaths;
	std::string									m_strOutputFolderPath;
	std::vector<std::string>					m_vecEntryTypes;
	std::vector<std::string>					m_vecTextureImageOutputFormats;
	bool										m_bDumpAllTextureMipmaps;
	bool										m_bDumpTextureImagesAsFolders;
};