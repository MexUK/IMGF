#pragma once

#include "nsbxcf.h"
#include "Type/Types.h"
#include <string>

class bxcf::ImageFile
{
public:
	uint32					m_uiImageWidth;
	uint32					m_uiImageHeight;
	uint32					m_uiBPP;
	std::string				m_strRasterDataBGRA32;
};