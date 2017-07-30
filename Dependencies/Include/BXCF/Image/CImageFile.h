#ifndef CImageFile_H
#define CImageFile_H

#include "bxcf.h"
#include "Type/Types.h"
#include <string>

class bxcf::CImageFile
{
public:
	uint32					m_uiImageWidth;
	uint32					m_uiImageHeight;
	uint32					m_uiBPP;
	std::string				m_strRasterDataBGRA32;
};

#endif