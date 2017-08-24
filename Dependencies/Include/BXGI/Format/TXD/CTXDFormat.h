#ifndef CTXDFormat_H
#define CTXDFormat_H

#include "bxgi.h"
#include "Format/RW/CRWFormat.h"
#include "Format/RW/CRWSection.h"
#include "Games/ePlatformedGame.h"
#include "Image/eRasterDataFormat.h"
#include "Engine/RW/eRWVersion.h"
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

	void							convertToGame(bxgi::ePlatformedGame ePlatformedGame, std::vector<std::string>& vecMipmapsRemoved);
	void							convertToRasterDataFormat(bxcf::eRasterDataFormat eRasterDataFormatValue, std::vector<std::string>& vecMipmapsRemoved);
	bxgi::CIntermediateTextureFormat*		convertToIntermediateFormat(void);

	static bool						isTextureNameValid(std::string& strTextureName, bool bIsAlphaTexture = false);
	static bool						isTextureResolutionValid(uint16 usWidth, uint16 usHeight, std::vector<bxgi::ePlatformedGame>& vecGames);
	static bool						isTXDSizeValid(uint32 uiFileSize);
	static bool						isTextureCountValid(uint32 uiTextureCount, std::vector<bxgi::ePlatformedGame>& vecGames);
	static uint32					getMaxTextureCountForGame(bxgi::ePlatformedGame ePlatformedGame);

	void							setGames(std::vector<bxgi::ePlatformedGame>& vecGames) { m_vecGames = vecGames; }
	std::vector<bxgi::ePlatformedGame>&	getGames(void) { return m_vecGames; }

	void							setDeviceId(uint16 usDeviceId) { m_usDeviceId = usDeviceId; }
	uint16							getDeviceId(void) { return m_usDeviceId; }

private:
	std::vector<bxgi::ePlatformedGame>	m_vecGames;
	uint16							m_usDeviceId;
};

#endif