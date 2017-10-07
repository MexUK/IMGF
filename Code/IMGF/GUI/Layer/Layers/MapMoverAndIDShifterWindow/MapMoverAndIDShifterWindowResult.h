#pragma once

#include "nsimgf.h"
#include "nsbxcf.h"
#include "Type/Vector/Vec3f.h"
#include <string>
#include <vector>

struct imgf::MapMoverAndIDShifterWindowResult
{
	std::string		m_strDATFile;
	std::string		m_strGameFolder;
	bool			m_bUseIDEFolder;
	std::string		m_strIDEFolder;
	bool			m_bUseIPLFolder;
	std::string		m_strIPLFolder;
	std::string		m_strOutputFolder;
	bool			m_bUseIDStart;
	uint32			m_uiIDStart;
	bool			m_bUsePositionOffset;
	bxcf::Vec3f		m_vecPositionOffset;
	bool			m_bIgnoreDefaultObjects;
	std::vector<std::string>		m_vecIgnoreFilesForIDShifter;
	std::vector<std::string>		m_vecIgnoreFilesForMapMover;
};