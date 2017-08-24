#ifndef CTXDManager_H
#define CTXDManager_H

#include "bxgi.h"
#include "Format/CFormatManager.h"
#include "Object/CSingleton.h"
#include "eTXDRasterDataFormat.h"
#include "Image/eRasterDataFormat.h"
#include "Games/ePlatformedGame.h"
#include "Image/eDXTCompressionType.h"
#include "Platform/Hardware/ePlatform.h"
#include <string>

class bxgi::CTXDFormat;
class bxgi::CIntermediateTextureFormat;

class bxgi::CTXDManager : public bxcf::CFormatManager<bxgi::CTXDFormat>, public bxcf::CSingleton<CTXDManager>
{
public:
	CTXDManager(void);

	void						init(void);
	void						uninit(void);

	bxgi::CTXDFormat*			createFormat(void);

	bxgi::CTXDFormat*			convertIntermediateTextureFileToTXDFile(bxgi::CIntermediateTextureFormat *pGeneralTextureFile);

	static uint32				getTXDRasterDataFormatFromRasterDataFormat(bxcf::eRasterDataFormat eRasterDataFormatValue);
	static std::string			getTXDRasterFormatText(uint32 uiTXDRasterDataFormatValue, bxcf::eDXTCompressionType eDXTCompressionTypeValue);
	static bxcf::ePlatform		getPlatformFromTXDPlatformId(uint32 uiTXDPlatformId);
};

#endif