#ifndef CTXDFormat_H
#define CTXDFormat_H

#include "BXA.h"
#include "Format/RenderWare/Helper/BinaryStream/CRWFormat.h"
#include "Format/RenderWare/Helper/BinaryStream/CRWSection.h"
#include "Collection/Games/ePlatformedGame.h"
#include "Image/eRasterDataFormat.h"
#include "Format/RenderWare/Helper/BinaryStream/eRWVersion.h"
#include <string>
#include <vector>

class bxa::CRWSection_TextureNative;
class bxa::CIntermediateTextureFormat;

class bxa::CTXDFormat : public bxa::CRWFormat
{
public:
	CTXDFormat(void);

	bxa::CRWSection_TextureNative*					addTextureViaFile(std::string& strFilePath, std::string& strTextureDiffuseName, std::string strTextureAlphaName = "");
	std::vector<std::string>					getTextureNames(void);
	std::vector<bxa::CRWSection_TextureNative*>		getTextures(void);

	bool							doesHaveTextureWithInvalidTXDRasterDataFormat(void);

	void							convertToGame(bxa::ePlatformedGame ePlatformedGame, std::vector<std::string>& vecMipmapsRemoved);
	void							convertToRasterDataFormat(bxa::eRasterDataFormat eRasterDataFormatValue, std::vector<std::string>& vecMipmapsRemoved);
	bxa::CIntermediateTextureFormat*		convertToIntermediateFormat(void);

	static bool						isTextureNameValid(std::string& strTextureName, bool bIsAlphaTexture = false);
	static bool						isTextureResolutionValid(uint16 usWidth, uint16 usHeight, std::vector<bxa::ePlatformedGame>& vecGames);
	static bool						isTXDSizeValid(uint32 uiFileSize);
	static bool						isTextureCountValid(uint32 uiTextureCount, std::vector<bxa::ePlatformedGame>& vecGames);
	static uint32					getMaxTextureCountForGame(bxa::ePlatformedGame ePlatformedGame);

	void							setGames(std::vector<bxa::ePlatformedGame>& vecGames) { m_vecGames = vecGames; }
	std::vector<bxa::ePlatformedGame>&	getGames(void) { return m_vecGames; }

	void							setDeviceId(uint16 usDeviceId) { m_usDeviceId = usDeviceId; }
	uint16							getDeviceId(void) { return m_usDeviceId; }

private:
	std::vector<bxa::ePlatformedGame>	m_vecGames;
	uint16							m_usDeviceId;
};

#endif