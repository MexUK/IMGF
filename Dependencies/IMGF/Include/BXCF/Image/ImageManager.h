#pragma once

#include "nsbxcf.h"
#include "Type/Types.h"
#include "Object/Manager.h"
#include "Object/Singleton.h"
#include "EDXTCompressionType.h"
#include "ERasterDataFormat.h"
#include "d3d9.h"
#include <string>

class bxcf::RasterDataFormatManager;
class bxcf::ImageFile;

class bxcf::ImageManager : public bxcf::Manager, public bxcf::Singleton<bxcf::ImageManager>
{
public:
	ImageManager(void);
	~ImageManager(void);

	void								init(void);
	void								uninit(void);

	RasterDataFormatManager*			getRasterDataFormatManager(void) { return m_pRasterDataFormatManager; }

	static ImageFile*					loadImageFromFile(std::string& strFilePath);
	
	static std::string					convertBGRA32ToRasterDataFormat(std::string& strRasterData, ERasterDataFormat ERasterDataFormatValue, std::string* strPaletteDataOut = nullptr, uint32 uiWidth = 0, uint32 uiHeight = 0);
	static std::string					convertRasterDataFormatToBGRA32(std::string& strRasterData, ERasterDataFormat ERasterDataFormatValue, std::string& strPaletteDataIn = bxcf::g_strBlankString, uint32 uiWidth = 0, uint32 uiHeight = 0);

	static std::string					convertBGRA32ToRGBA32(std::string& strRasterData);
	static std::string					convertRGBA32ToBGRA32(std::string& strRasterData);

	static std::string					convertBGRA32ToBGR24(std::string& strRasterData);
	static std::string					convertBGR24ToBGRA32(std::string& strRasterData);

	static std::string					convertBGR24ToRGB24(std::string& strRasterData);
	static std::string					convertRGB24ToBGR24(std::string& strRasterData);

	static std::string					convertBGRA32ToDXT(std::string& strRasterData, EDXTCompressionType EDXTCompressionTypeValue, uint32 uiWidth, uint32 uiHeight);
	static std::string					convertDXTToBGRA32(std::string& strRasterData, EDXTCompressionType EDXTCompressionTypeValue, uint32 uiWidth, uint32 uiHeight);

	static std::string					convertBGRA32ToPAL4(std::string& strRasterData);
	static std::string					convertPAL4ToBGRA32(std::string& strRasterData, std::string& strPaletteData, uint32 uiWidth, uint32 uiHeight);

	static std::string					convertBGRA32ToPAL8(std::string& strRasterData);
	static std::string					convertPAL8ToBGRA32(std::string& strRasterData, std::string& strPaletteData, uint32 uiWidth, uint32 uiHeight);

	static std::string					swapRows(std::string& strRasterData, uint32 uiWidth, uint32 uiHeight);
	static std::string					swapColumns(std::string& strRasterData, uint32 uiWidth, uint32 uiHeight);
	static std::string					swapRowsAndColumns(std::string& strRasterData, uint32 uiWidth, uint32 uiHeight);

	static D3DFORMAT					getD3DFormatFromRasterDataFormat(ERasterDataFormat ERasterDataFormatValue);
	static ERasterDataFormat			getRasterDataFormatFromD3DFormat(D3DFORMAT d3dFormat);

	static EDXTCompressionType			getDXTCompressionTypeFromRasterDataFormat(ERasterDataFormat ERasterDataFormatValue);

	static uint8						getBPPFromRasterDataFormat(ERasterDataFormat ERasterDataFormatValue);

	static std::string					getD3DFormatToPack(D3DFORMAT d3dFormat);
	static std::string					getD3DFormatText(D3DFORMAT d3dFormat);

	static std::string					getFourCCFromDXTCompressionType(EDXTCompressionType EDXTCompressionTypeValue);
	static EDXTCompressionType			getDXTCompressionTypeFromFourCC(std::string strFourCC);

	static uint8						getTexelByteCountFromDXTCompressionType(EDXTCompressionType EDXTCompressionTypeValue);
	static uint8						getSquishCompressionFlagsForDXTCompressionType(EDXTCompressionType EDXTCompressionTypeValue);

private:
	RasterDataFormatManager*			m_pRasterDataFormatManager;
};