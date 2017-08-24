#ifndef CIntermediateTexture_H
#define CIntermediateTexture_H

#include "bxgi.h"
#include "Type/Types.h"
#include "Pool/CVectorPool.h"
#include "Image/eRasterDataFormat.h"
#include "Data/CIntermediateTextureMipmap.h"
#include "Type/Vector/Vec2u16.h"
#include <string>

class bxgi::CIntermediateTexture : public bxcf::CVectorPool<bxgi::CIntermediateTextureMipmap*>
{
public:
	CIntermediateTexture(void) :
		m_eRasterDataFormat(bxcf::RASTERDATAFORMAT_UNKNOWN)
	{
		m_vecSize.x = 0;
		m_vecSize.y = 0;
	};

	void						unload(void) {}

	void						setName(std::string& strName) { m_strName = strName; }
	std::string&				getName(void) { return m_strName; }

	void						setRasterDataFormat(bxcf::eRasterDataFormat eRasterDataFormatValue) { m_eRasterDataFormat = eRasterDataFormatValue; }
	bxcf::eRasterDataFormat		getRasterDataFormat(void) { return m_eRasterDataFormat; }

	void						setSize(bxcf::Vec2u16& vecSize) { m_vecSize = vecSize; }
	bxcf::Vec2u16&				getSize(void) { return m_vecSize; }

	void						setPaletteData(std::string& strPaletteData) { m_strPaletteData = strPaletteData; }
	std::string&				getPaletteData(void) { return m_strPaletteData; }

private:
	std::string					m_strName;
	bxcf::eRasterDataFormat		m_eRasterDataFormat;
	bxcf::Vec2u16				m_vecSize;
	std::string					m_strPaletteData;
};

#endif