#pragma once

#include "nsbxgi.h"
#include "Format/RW/CRWSection.h"
#include "Pool/CVectorPool.h"
#include "Image/EDXTCompressionType.h"
#include "Game/EPlatformedGame.h"
#include "Image/ERasterDataFormat.h"
#include "Format/RW/Entries/CRWEntry_TextureNative_MipMap.h"
#include "Type/Vector/Vec2u.h"
#include "Platform/Hardware/EPlatform.h"
#include <string>
#include <vector>

class bxgi::CRWSection_TextureNative : public bxgi::CRWSection
{
public:
	CRWSection_TextureNative(void);
	
	void						unserialize(void);
	void						serialize(void);
	
	void						convertToGame(bxgi::EPlatformedGame EPlatformedGame, std::vector<std::string>& vecMipmapsRemoved);
	void						convertToRasterDataFormat(bxcf::ERasterDataFormat ERasterDataFormatValue, std::vector<std::string>& vecMipmapsRemoved);

	bool						doesHaveValidTXDRasterDataFormat(void);
	bxcf::ERasterDataFormat		detectRasterDataFormat(void);

	uint32						getBodyLength(void);
	void						unswizzlePS2Format(void);
	
	bxcf::CVectorPool<bxgi::CRWEntry_TextureNative_MipMap*>&	getMipMaps(void) { return m_vecMipMaps; }

	static bool					doesTXDRasterDataFormatExist(uint32 uiTXDRasterDataFormat);
	
	void						setHasDiffuse(bool bHasDiffuse) { m_bHasDiffuse = bHasDiffuse; }
	bool						doesHaveDiffuse(void) { return m_bHasDiffuse; }

	void						setHasAlpha(bool bHasAlpha) { m_bHasAlpha = bHasAlpha; }
	bool						doesHaveAlpha(void) { return m_bHasAlpha; }

	void						setPaletteUsed(bool bPaletteIsUsed) { m_bPaletteIsUsed = bPaletteIsUsed; }
	bool						isPaletteUsed(void) { return m_bPaletteIsUsed; }

	void						setPlatformId(uint32 uiPlatformId) { m_uiPlatformId = uiPlatformId; }
	uint32						getPlatformId(void) { return m_uiPlatformId; }

	void						setFilterFlags(uint8 ucFilterFlags) { m_ucFilterFlags = ucFilterFlags; }
	uint8						getFilterFlags(void) { return m_ucFilterFlags; }

	void						setTextureWrapUV(uint8 ucTextureWrapUV) { m_ucTextureWrapUV = ucTextureWrapUV; }
	uint8						getTextureWrapUV(void) { return m_ucTextureWrapUV; }

	void						setDiffuseName(std::string& strDiffuseName) { m_strDiffuseName = strDiffuseName; }
	std::string&				getDiffuseName(void) { return m_strDiffuseName; }

	void						setAlphaName(std::string& strAlphaName) { m_strAlphaName = strAlphaName; }
	std::string&				getAlphaName(void) { return m_strAlphaName; }

	void						setTXDRasterDataFormat(uint32 uiTXDRasterDataFormat) { m_uiTXDRasterDataFormat = uiTXDRasterDataFormat; }
	uint32						getTXDRasterDataFormat(void) { return m_uiTXDRasterDataFormat; }

	void						setRasterDataFormat(bxcf::ERasterDataFormat ERasterDataFormatValue, bool bUpdatETXDRasterDataFormat = true);
	bxcf::ERasterDataFormat		getRasterDataFormat(void) { return m_ERasterDataFormat; }

	void						setAlpha(uint32 uiAlpha) { m_uiAlpha = uiAlpha; }
	uint32						getAlpha(void) { return m_uiAlpha; }

	void						setImageSize(bxcf::Vec2u& vecImageSize) { m_vecImageSize = vecImageSize; }
	bxcf::Vec2u&					getImageSize(void) { return m_vecImageSize; }

	void						setBPP(uint8 ucBPP) { m_ucBPP = ucBPP; }
	uint8						getBPP(void) { return m_ucBPP; }

	void						setOriginalBPP(uint8 ucBPP) { m_ucOriginalBPP = ucBPP; }
	uint8						getOriginalBPP(void) { return m_ucOriginalBPP; }

	void						setRasterType(uint8 ucRasterType) { m_ucRasterType = ucRasterType; }
	uint8						getRasterType(void) { return m_ucRasterType; }

	void						setDXTCompressionType(bxcf::EDXTCompressionType ECompressionAlgorithm) { m_EDXTCompressionType = ECompressionAlgorithm; }
	bxcf::EDXTCompressionType	getDXTCompressionType(void) { return m_EDXTCompressionType; }

	void						setCubeTexture(bool bCubeTexture) { m_bCubeTexture = bCubeTexture; }
	bool						getCubeTexture(void) { return m_bCubeTexture; }

	void						setAutoMipMaps(bool bCubeTexture) { m_bAutoMipMaps = bCubeTexture; }
	bool						getAutoMipMaps(void) { return m_bAutoMipMaps; }

	void						setIsNotRWCompatible(bool bIsNotRWCompatible) { m_bIsNotRWCompatible = bIsNotRWCompatible; }
	bool						getIsNotRWCompatible(void) { return m_bIsNotRWCompatible; }

	void						setPaletteData(std::string& strPaletteData) { m_strPaletteData = strPaletteData; }
	std::string&				getPaletteData(void) { return m_strPaletteData; }

	void						setMipMapCount(uint32 uiMipMapCount) { m_uiMipMapCount = uiMipMapCount; }
	uint32						getMipMapCount(void) { return m_uiMipMapCount; }

private:
	void						unserializeHeader(void);
	void						unserializeBody(void);

	void						serializeHeader(void);
	void						serializeBody(void);

	void						unserializeHeader_Direct3D(void);
	void						unserializeHeader_PS2(void);
	void						unserializeHeader_Android(void);
	void						unserializeBody_Direct3D(void);
	void						unserializeBody_PS2(void);
	void						unserializeBody_Android(void);
	
	void						serializeHeader_Direct3D(void);
	void						serializeHeader_PS2(void);
	void						serializeHeader_Android(void);
	void						serializeBody_Direct3D(void);
	void						serializeBody_PS2(void);
	void						serializeBody_Android(void);

	std::string					unserializeString(void);
	void						processPs2Swizzle(void);
	void						unswizzle8(uint8 *pTexels, uint8 *pRawIndices, uint32 uiWidth, uint32 uiHeight);
	void						unclut(uint32 uiWidth, uint32 uiHeight);
	
private:
	bxcf::EPlatform				m_EPlatform;

	uint8						m_bHasDiffuse : 1;
	uint8						m_bHasAlpha : 1;
	uint8						m_bPaletteIsUsed : 1;
	
	uint32						m_uiPlatformId;
	uint8						m_ucFilterFlags;
	uint8						m_ucTextureWrapUV;
	std::string					m_strDiffuseName;
	std::string					m_strAlphaName;
	uint32						m_uiTXDRasterDataFormat;
	bxcf::ERasterDataFormat		m_ERasterDataFormat;
	uint32						m_uiAlpha;
	bxcf::Vec2u					m_vecImageSize;
	uint8						m_ucBPP;
	uint8						m_ucRasterType;
	bxcf::EDXTCompressionType	m_EDXTCompressionType;
	uint8						m_bCubeTexture : 1;
	uint8						m_bAutoMipMaps : 1;
	uint8						m_bIsNotRWCompatible : 1;
	std::string					m_strPaletteData;
	uint8						m_ucOriginalBPP;
	uint32						m_uiMipMapCount;

	bxcf::CVectorPool<bxgi::CRWEntry_TextureNative_MipMap*>	m_vecMipMaps;
};