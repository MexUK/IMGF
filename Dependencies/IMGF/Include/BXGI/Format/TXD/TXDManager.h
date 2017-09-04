#pragma once

#include "nsbxgi.h"
#include "Format/FormatManager.h"
#include "Object/Singleton.h"
#include "ETXDRasterDataFormat.h"
#include "Image/ERasterDataFormat.h"
#include "Game/EPlatformedGame.h"
#include "Image/EDXTCompressionType.h"
#include "Platform/Hardware/EPlatform.h"
#include <string>

class bxgi::TXDFormat;
class bxgi::IntermediateTextureFormat;

class bxgi::TXDManager : public bxcf::FormatManager<bxgi::TXDFormat>, public bxcf::Singleton<TXDManager>
{
public:
	TXDManager(void);

	void						init(void);
	void						uninit(void);

	bxgi::TXDFormat*			createFormat(void);

	bxgi::TXDFormat*			convertIntermediateTextureFileToTXDFile(bxgi::IntermediateTextureFormat *pGeneralTextureFile);

	static uint32				getTXDRasterDataFormatFromRasterDataFormat(bxcf::ERasterDataFormat ERasterDataFormatValue);
	static std::string			getTXDRasterFormatText(uint32 uiTXDRasterDataFormatValue, bxcf::EDXTCompressionType EDXTCompressionTypeValue);
	static bxcf::EPlatform		getPlatformFromTXDPlatformId(uint32 uiTXDPlatformId);
};