#ifndef CWTDEntry_H
#define CWTDEntry_H

#include "mcore.h"
#include "CWTDMipmap.h"
#include "Pool/CVectorPool.h"
#include "Image/eRasterDataFormat.h"
#include "d3d9.h"
#include <string>

class mcore::CWTDMipmap;

class mcore::CWTDEntry : public mcore::CVectorPool<mcore::CWTDMipmap*>
{
public:
	CWTDEntry(void);

	void						unload(void) {}

	void						setEntryName(std::string strEntryName) { m_strEntryName = strEntryName; }
	std::string					getEntryName(void) { return m_strEntryName; }

	void						setD3DFormat(D3DFORMAT eD3DFormat) { m_eD3DFormat = eD3DFormat; }
	D3DFORMAT					getD3DFormat(void) { return m_eD3DFormat; }

	void						setRasterDataFormat(mcore::eRasterDataFormat eRasterDataFormatValue, bool bUpdateD3DFormat = true);
	mcore::eRasterDataFormat			getRasterDataFormat(void) { return m_eRasterDataFormat; }

	void						setImageSize(bool bIsWidth, uint16 usImageSize) { m_usImageSize[bIsWidth ? 0 : 1] = usImageSize; }
	uint16						getImageSize(bool bIsWidth) { return m_usImageSize[bIsWidth ? 0 : 1]; }

	void						setRawDataOffset(uint32 uiRawDataOffset) { m_uiRawDataOffset = uiRawDataOffset; }
	uint32						getRawDataOffset(void) { return m_uiRawDataOffset; }

	void						setTextureHash(uint32 uiTextureHash) { m_uiTextureHash = uiTextureHash; }
	uint32						getTextureHash(void) { return m_uiTextureHash; }

	void						setLevels(uint8 ucLevels) { m_ucLevels = ucLevels; }
	uint8						getLevels(void) { return m_ucLevels; }

	void						stripNameHeaderAndFooter(void);

private:
	std::string					m_strEntryName;
	D3DFORMAT					m_eD3DFormat;
	mcore::eRasterDataFormat			m_eRasterDataFormat;
	uint32						m_uiRawDataOffset;
	uint16						m_usImageSize[2];
	uint8						m_ucLevels;
	uint32						m_uiTextureHash;
};

#endif