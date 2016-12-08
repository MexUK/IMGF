#ifndef CTXDManager_H
#define CTXDManager_H

#include "mcore.h"
#include "Format/CFormatManager.h"
#include "Object/CSingleton.h"
#include "eTXDRasterDataFormat.h"
#include "Image/eRasterDataFormat.h"
#include "Collection/Games/ePlatformedGame.h"
#include "Image/eDXTCompressionType.h"
#include "Platform/Hardware/ePlatform.h"
#include <string>
#include <vector>

class mcore::CTXDFormat;
class mcore::CIntermediateTextureFormat;

class mcore::CTXDManager : public mcore::CFormatManager<mcore::CTXDFormat>, public mcore::CSingleton<CTXDManager>
{
public:
	CTXDManager(void);

	void						init(void);
	void						uninit(void);

	mcore::CTXDFormat*					createFormat(void);

	mcore::CTXDFormat*					convertIntermediateTextureFileToTXDFile(mcore::CIntermediateTextureFormat *pGeneralTextureFile);

	static uint32				getTXDRasterDataFormatFromRasterDataFormat(mcore::eRasterDataFormat eRasterDataFormatValue);
	static std::string			getTXDRasterFormatText(uint32 uiTXDRasterDataFormatValue, mcore::eDXTCompressionType eDXTCompressionTypeValue);
	static mcore::ePlatform			getPlatformFromTXDPlatformId(uint32 uiTXDPlatformId);
};

#endif