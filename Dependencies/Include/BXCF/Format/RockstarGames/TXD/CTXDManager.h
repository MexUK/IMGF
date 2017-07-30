#ifndef CTXDManager_H
#define CTXDManager_H

#include "bxcf.h"
#include "Format/CFormatManager.h"
#include "Object/CSingleton.h"
#include "eTXDRasterDataFormat.h"
#include "Image/eRasterDataFormat.h"
#include "Collection/Games/ePlatformedGame.h"
#include "Image/eDXTCompressionType.h"
#include "Platform/Hardware/ePlatform.h"
#include <string>
#include <vector>

class bxcf::CTXDFormat;
class bxcf::CIntermediateTextureFormat;

class bxcf::CTXDManager : public bxcf::CFormatManager<bxcf::CTXDFormat>, public bxcf::CSingleton<CTXDManager>
{
public:
	CTXDManager(void);

	void						init(void);
	void						uninit(void);

	bxcf::CTXDFormat*					createFormat(void);

	bxcf::CTXDFormat*					convertIntermediateTextureFileToTXDFile(bxcf::CIntermediateTextureFormat *pGeneralTextureFile);

	static uint32				getTXDRasterDataFormatFromRasterDataFormat(bxcf::eRasterDataFormat eRasterDataFormatValue);
	static std::string			getTXDRasterFormatText(uint32 uiTXDRasterDataFormatValue, bxcf::eDXTCompressionType eDXTCompressionTypeValue);
	static bxcf::ePlatform			getPlatformFromTXDPlatformId(uint32 uiTXDPlatformId);
};

#endif