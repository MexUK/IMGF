#ifndef CIntermediateTexture_H
#define CIntermediateTexture_H

#include "bxcf.h"
#include "Type/Types.h"
#include "Pool/CVectorPool.h"
#include "Image/eRasterDataFormat.h"
#include "Data/CIntermediateTextureMipmap.h"
#include "Type/Vector/CVector2ui16.h"
#include <string>

class bxcf::CIntermediateTexture : public bxcf::CVectorPool<bxcf::CIntermediateTextureMipmap*>
{
public:
	CIntermediateTexture(void) :
		m_eRasterDataFormat(bxcf::RASTERDATAFORMAT_UNKNOWN)
	{
		m_vecSize.m_x = 0;
		m_vecSize.m_y = 0;
	};

	void						unload(void) {}

	void						setName(std::string& strName) { m_strName = strName; }
	std::string&				getName(void) { return m_strName; }

	void						setRasterDataFormat(bxcf::eRasterDataFormat eRasterDataFormatValue) { m_eRasterDataFormat = eRasterDataFormatValue; }
	bxcf::eRasterDataFormat			getRasterDataFormat(void) { return m_eRasterDataFormat; }

	void						setSize(bxcf::CVector2ui16& vecSize) { m_vecSize = vecSize; }
	bxcf::CVector2ui16&				getSize(void) { return m_vecSize; }

	void						setPaletteData(std::string& strPaletteData) { m_strPaletteData = strPaletteData; }
	std::string&				getPaletteData(void) { return m_strPaletteData; }

private:
	std::string					m_strName;
	bxcf::eRasterDataFormat			m_eRasterDataFormat;
	bxcf::CVector2ui16				m_vecSize;
	std::string					m_strPaletteData;
};

#endif