#pragma once

#include "nsbxgi.h"
#include "Format/RW/CRWFormat.h"
#include "Format/RW/CRWSection.h"
#include "Game/EPlatformedGame.h"
#include "Image/ERasterDataFormat.h"
#include "Engine/RW/ERWVersion.h"
#include <string>
#include <vector>

class bxgi::CRWSection_TextureNative;
class bxgi::CIntermediateTextureFormat;

class bxgi::CTXDFormat : public bxgi::CRWFormat
{
public:
	CTXDFormat(void);

	bxgi::CRWSection_TextureNative*					addTextureViaFile(std::string& strFilePath, std::string& strTextureDiffuseName, std::string strTextureAlphaName = "");
	std::vector<std::string>					getTextureNames(void);
	std::vector<bxgi::CRWSection_TextureNative*>		getTextures(void);

	bool							doesHaveTextureWithInvalidTXDRasterDataFormat(void);

	void							convertToGame(bxgi::EPlatformedGame EPlatformedGame, std::vector<std::string>& vecMipmapsRemoved);
	void							convertToRasterDataFormat(bxcf::ERasterDataFormat ERasterDataFormatValue, std::vector<std::string>& vecMipmapsRemoved);
	bxgi::CIntermediateTextureFormat*		convertToIntermediateFormat(void);

	static bool						isTextureNameValid(std::string& strTextureName, bool bIsAlphaTexture = false);
	static bool						isTextureResolutionValid(uint16 usWidth, uint16 usHeight, std::vector<bxgi::EPlatformedGame>& vecGames);
	static bool						isTXDSizeValid(uint32 uiFileSize);
	static bool						isTextureCountValid(uint32 uiTextureCount, std::vector<bxgi::EPlatformedGame>& vecGames);
	static uint32					getMaxTextureCountForGame(bxgi::EPlatformedGame EPlatformedGame);

	void									setPlatformedGames(std::vector<bxgi::EPlatformedGame>& vecGames) { m_vecGames = vecGames; }
	std::vector<bxgi::EPlatformedGame>&		getPlatformedGames(void) { return m_vecGames; }

	void							setDeviceId(uint16 usDeviceId) { m_usDeviceId = usDeviceId; }
	uint16							getDeviceId(void) { return m_usDeviceId; }

private:
	std::vector<bxgi::EPlatformedGame>	m_vecGames;
	uint16							m_usDeviceId;
};