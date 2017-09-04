#pragma once

#include "nsbxgi.h"
#include "Image/ERasterDataFormat.h"
#include <string>

class bxgi::WTDEntry;

class bxgi::WTDMipmap
{
public:
	WTDMipmap(bxgi::WTDEntry *pWTDEntry);

	void						unload(void) {}

	void						setWTDEntry(bxgi::WTDEntry *pWTDEntry) { m_pWTDEntry = pWTDEntry; }
	bxgi::WTDEntry*			getWTDEntry(void) { return m_pWTDEntry; }

	void						setRasterData(std::string strRasterData) { m_strRasterData = strRasterData; }
	std::string					getRasterData(void) { return m_strRasterData; }

	void						setImageSize(bool bIsWidth, uint16 usImageSize) { m_usImageSize[bIsWidth ? 0 : 1] = usImageSize; }
	uint16						getImageSize(bool bIsWidth) { return m_usImageSize[bIsWidth ? 0 : 1]; }

	bxcf::ERasterDataFormat		getRasterDataFormat(void);

	std::string					getRasterDataBGRA32(void);

private:
	bxgi::WTDEntry*			m_pWTDEntry;
	std::string					m_strRasterData;
	uint16						m_usImageSize[2];
};