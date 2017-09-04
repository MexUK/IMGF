#ifndef CTXDFormat_H
#define CTXDFormat_H

#include "bxcf.h"
#include "Format/RenderWare/Helper/BinaryStream/CRWFormat.h"
#include "Format/RenderWare/Helper/BinaryStream/CRWSection.h"
#include "Collection/Games/ePlatformedGame.h"
#include "Image/eRasterDataFormat.h"
#include "Format/RenderWare/Helper/BinaryStream/eRWVersion.h"
#include <string>
#include <vector>

class bxcf::CRWSection_TextureNative;
class bxcf::CIntermediateTextureFormat;

class bxcf::CTXDFormat : public bxcf::CRWFormat
{
public:
	CTXDFormat(void);

	bxcf::CRWSection_TextureNative*					addTextureViaFile(std::string& strFilePath, std::string& strTextureDiffuseName, std::string strTextureAlphaName = "");
	std::vector<std::string>					getTextureNames(void);
	std::vector<bxcf::CRWSection_TextureNative*>		getTextures(void);

	bool							doesHaveTextureWithInvalidTXDRasterDataFormat(void);

	void							convertToGame(bxcf::ePlatformedGame ePlatformedGame, std::vector<std::string>& vecMipmapsRemoved);
	void							convertToRasterDataFormat(bxcf::eRasterDataFormat eRasterDataFormatValue, std::vector<std::string>& vecMipmapsRemoved);
	bxcf::CIntermediateTextureFormat*		convertToIntermediateFormat(void);

	static bool						isTextureNameValid(std::string& strTextureName, bool bIsAlphaTexture = false);
	static bool						isTextureResolutionValid(uint16 usWidth, uint16 usHeight, std::vector<bxcf::ePlatformedGame>& vecGames);
	static bool						isTXDSizeValid(uint32 uiFileSize);
	static bool						isTextureCountValid(uint32 uiTextureCount, std::vector<bxcf::ePlatformedGame>& vecGames);
	static uint32					getMaxTextureCountForGame(bxcf::ePlatformedGame ePlatformedGame);

	void							setGames(std::vector<bxcf::ePlatformedGame>& vecGames) { m_vecGames = vecGames; }
	std::vector<bxcf::ePlatformedGame>&	getGames(void) { return m_vecGames; }

	void							setDeviceId(uint16 usDeviceId) { m_usDeviceId = usDeviceId; }
	uint16							getDeviceId(void) { return m_usDeviceId; }

private:
	std::vector<bxcf::ePlatformedGame>	m_vecGames;
	uint16							m_usDeviceId;
};

#endif