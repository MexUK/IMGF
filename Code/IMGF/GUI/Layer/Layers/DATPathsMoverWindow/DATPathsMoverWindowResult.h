#pragma once

#include "nsimgf.h"
#include "nsbxcf.h"
#include "Type/Vector/Vec2f.h"
#include "Type/Vector/Vec3f.h"
#include <string>

struct imgf::DATPathsMoverWindowResult
{
	bxcf::Vec2f		m_vecMinOutputMapRange;
	bxcf::Vec2f		m_vecMaxOutputMapRange;
	bxcf::Vec2f		m_vecOutputTileSize;
	bxcf::Vec3f		m_vecPositionOffset;
	std::string		m_strDATInputFolderPath;
	std::string		m_strDATOutputFolderPath;
};