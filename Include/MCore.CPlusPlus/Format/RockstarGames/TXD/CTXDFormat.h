#ifndef CTXDFormat_H
#define CTXDFormat_H

#include "mcore.h"
#include "Format/RenderWare/Helper/BinaryStream/CRWFormat.h"
#include "Format/RenderWare/Helper/BinaryStream/CRWSection.h"
#include "Collection/Games/ePlatformedGame.h"
#include "Image/eRasterDataFormat.h"
#include "Format/RenderWare/Helper/BinaryStream/eRWVersion.h"
#include <string>
#include <vector>

class mcore::CRWSection_TextureNative;
class mcore::CIntermediateTextureFormat;

class mcore::CTXDFormat : public mcore::CRWFormat
{
public:
	CTXDFormat(void);

	mcore::CRWSection_TextureNative*					addTextureViaFile(std::string& strFilePath, std::string& strTextureDiffuseName, std::string strTextureAlphaName = "");
	std::vector<std::string>					getTextureNames(void);
	std::vector<mcore::CRWSection_TextureNative*>		getTextures(void);

	bool							doesHaveTextureWithInvalidTXDRasterDataFormat(void);

	void							convertToGame(mcore::ePlatformedGame ePlatformedGame, std::vector<std::string>& vecMipmapsRemoved);
	void							convertToRasterDataFormat(mcore::eRasterDataFormat eRasterDataFormatValue, std::vector<std::string>& vecMipmapsRemoved);
	mcore::CIntermediateTextureFormat*		convertToIntermediateFormat(void);

	static bool						isTextureNameValid(std::string& strTextureName, bool bIsAlphaTexture = false);
	static bool						isTextureResolutionValid(uint16 usWidth, uint16 usHeight, std::vector<mcore::ePlatformedGame>& vecGames);
	static bool						isTXDSizeValid(uint32 uiFileSize);
	static bool						isTextureCountValid(uint32 uiTextureCount, std::vector<mcore::ePlatformedGame>& vecGames);
	static uint32					getMaxTextureCountForGame(mcore::ePlatformedGame ePlatformedGame);

	void							setGames(std::vector<mcore::ePlatformedGame>& vecGames) { m_vecGames = vecGames; }
	std::vector<mcore::ePlatformedGame>&	getGames(void) { return m_vecGames; }

	void							setDeviceId(uint16 usDeviceId) { m_usDeviceId = usDeviceId; }
	uint16							getDeviceId(void) { return m_usDeviceId; }

private:
	std::vector<mcore::ePlatformedGame>	m_vecGames;
	uint16							m_usDeviceId;
};

#endif