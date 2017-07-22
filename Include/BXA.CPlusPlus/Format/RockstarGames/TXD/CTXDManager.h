#ifndef CTXDManager_H
#define CTXDManager_H

#include "BXA.h"
#include "Format/CFormatManager.h"
#include "Object/CSingleton.h"
#include "eTXDRasterDataFormat.h"
#include "Image/eRasterDataFormat.h"
#include "Collection/Games/ePlatformedGame.h"
#include "Image/eDXTCompressionType.h"
#include "Platform/Hardware/ePlatform.h"
#include <string>
#include <vector>

class bxa::CTXDFormat;
class bxa::CIntermediateTextureFormat;

class bxa::CTXDManager : public bxa::CFormatManager<bxa::CTXDFormat>, public bxa::CSingleton<CTXDManager>
{
public:
	CTXDManager(void);

	void						init(void);
	void						uninit(void);

	bxa::CTXDFormat*					createFormat(void);

	bxa::CTXDFormat*					convertIntermediateTextureFileToTXDFile(bxa::CIntermediateTextureFormat *pGeneralTextureFile);

	static uint32				getTXDRasterDataFormatFromRasterDataFormat(bxa::eRasterDataFormat eRasterDataFormatValue);
	static std::string			getTXDRasterFormatText(uint32 uiTXDRasterDataFormatValue, bxa::eDXTCompressionType eDXTCompressionTypeValue);
	static bxa::ePlatform			getPlatformFromTXDPlatformId(uint32 uiTXDPlatformId);
};

#endif