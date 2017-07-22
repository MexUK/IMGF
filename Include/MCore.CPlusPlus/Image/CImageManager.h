#ifndef CImageManager_H
#define CImageManager_H

#include "bxa.h"
#include "Type/Types.h"
#include "Object/CManager.h"
#include "Object/CSingleton.h"
#include "eDXTCompressionType.h"
#include "eRasterDataFormat.h"
#include "d3d9.h"
#include <string>

class bxa::CRasterDataFormatManager;
class bxa::CImageFile;

static std::string						strBlankString = ""; // todo - namespace

class bxa::CImageManager : public bxa::CManager, public bxa::CSingleton<bxa::CImageManager>
{
public:
	CImageManager(void);
	~CImageManager(void);

	void								init(void);
	void								uninit(void);

	CRasterDataFormatManager*			getRasterDataFormatManager(void) { return m_pRasterDataFormatManager; }

	static CImageFile*					loadImageFromFile(std::string& strFilePath);
	
	static std::string					convertBGRA32ToRasterDataFormat(std::string& strRasterData, eRasterDataFormat eRasterDataFormatValue, std::string* strPaletteDataOut = nullptr, uint32 uiWidth = 0, uint32 uiHeight = 0);
	static std::string					convertRasterDataFormatToBGRA32(std::string& strRasterData, eRasterDataFormat eRasterDataFormatValue, std::string& strPaletteDataIn = strBlankString, uint32 uiWidth = 0, uint32 uiHeight = 0);

	static std::string					convertBGRA32ToRGBA32(std::string& strRasterData);
	static std::string					convertRGBA32ToBGRA32(std::string& strRasterData);

	static std::string					convertBGRA32ToBGR24(std::string& strRasterData);
	static std::string					convertBGR24ToBGRA32(std::string& strRasterData);

	static std::string					convertBGR24ToRGB24(std::string& strRasterData);
	static std::string					convertRGB24ToBGR24(std::string& strRasterData);

	static std::string					convertBGRA32ToDXT(std::string& strRasterData, eDXTCompressionType eDXTCompressionTypeValue, uint32 uiWidth, uint32 uiHeight);
	static std::string					convertDXTToBGRA32(std::string& strRasterData, eDXTCompressionType eDXTCompressionTypeValue, uint32 uiWidth, uint32 uiHeight);

	static std::string					convertBGRA32ToPAL4(std::string& strRasterData);
	static std::string					convertPAL4ToBGRA32(std::string& strRasterData, std::string& strPaletteData, uint32 uiWidth, uint32 uiHeight);

	static std::string					convertBGRA32ToPAL8(std::string& strRasterData);
	static std::string					convertPAL8ToBGRA32(std::string& strRasterData, std::string& strPaletteData, uint32 uiWidth, uint32 uiHeight);

	static std::string					swapRows(std::string& strRasterData, uint32 uiWidth, uint32 uiHeight);
	static std::string					swapColumns(std::string& strRasterData, uint32 uiWidth, uint32 uiHeight);
	static std::string					swapRowsAndColumns(std::string& strRasterData, uint32 uiWidth, uint32 uiHeight);

	static D3DFORMAT					getD3DFormatFromRasterDataFormat(eRasterDataFormat eRasterDataFormatValue);
	static eRasterDataFormat			getRasterDataFormatFromD3DFormat(D3DFORMAT d3dFormat);

	static eDXTCompressionType			getDXTCompressionTypeFromRasterDataFormat(eRasterDataFormat eRasterDataFormatValue);

	static uint8						getBPPFromRasterDataFormat(eRasterDataFormat eRasterDataFormatValue);

	static std::string					getD3DFormatToPack(D3DFORMAT d3dFormat);
	static std::string					getD3DFormatText(D3DFORMAT d3dFormat);

	static std::string					getFourCCFromDXTCompressionType(eDXTCompressionType eDXTCompressionTypeValue);
	static eDXTCompressionType			getDXTCompressionTypeFromFourCC(std::string strFourCC);

	static uint8						getTexelByteCountFromDXTCompressionType(eDXTCompressionType eDXTCompressionTypeValue);
	static uint8						getSquishCompressionFlagsForDXTCompressionType(eDXTCompressionType eDXTCompressionTypeValue);

private:
	CRasterDataFormatManager*			m_pRasterDataFormatManager;
};

#endif