#pragma once

#include "nsbxgi.h"
#include "Format/CFormatManager.h"
#include "Object/CSingleton.h"
#include "ETXDRasterDataFormat.h"
#include "Image/ERasterDataFormat.h"
#include "Game/EPlatformedGame.h"
#include "Image/EDXTCompressionType.h"
#include "Platform/Hardware/EPlatform.h"
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

	static uint32				getTXDRasterDataFormatFromRasterDataFormat(bxcf::ERasterDataFormat ERasterDataFormatValue);
	static std::string			getTXDRasterFormatText(uint32 uiTXDRasterDataFormatValue, bxcf::EDXTCompressionType EDXTCompressionTypeValue);
	static bxcf::EPlatform		getPlatformFromTXDPlatformId(uint32 uiTXDPlatformId);
};