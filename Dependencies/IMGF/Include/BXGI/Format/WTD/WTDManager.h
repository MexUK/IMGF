#pragma once

#include "nsbxgi.h"
#include "Format/FormatManager.h"
#include "Object/Singleton.h"
#include "WTDFormat.h"
#include "d3d9.h"

class bxgi::WTDEntry;
class bxgi::IntermediateTextureFormat;

class bxgi::WTDManager : public bxcf::FormatManager<bxgi::WTDFormat>, public bxcf::Singleton<bxgi::WTDManager>
{
public:
	WTDManager(void);
	
	void						init(void);
	void						uninit(void);

	static uint32				getImageDataSize(WTDEntry *pWTDEntry, bool bIncludeLevels);

	bxgi::WTDFormat*			convertIntermediateTextureFileToWTDFile(bxgi::IntermediateTextureFormat *pIntermediateTextureFormat);
};