#ifndef CWTDManager_H
#define CWTDManager_H

#include "bxgi.h"
#include "Format/CFormatManager.h"
#include "Object/CSingleton.h"
#include "CWTDFormat.h"
#include "d3d9.h"

class bxgi::CWTDEntry;
class bxgi::CIntermediateTextureFormat;

class bxgi::CWTDManager : public bxcf::CFormatManager<bxgi::CWTDFormat>, public bxcf::CSingleton<bxgi::CWTDManager>
{
public:
	CWTDManager(void);
	
	void						init(void);
	void						uninit(void);

	static uint32				getImageDataSize(CWTDEntry *pWTDEntry, bool bIncludeLevels);

	bxgi::CWTDFormat*			convertIntermediateTextureFileToWTDFile(bxgi::CIntermediateTextureFormat *pIntermediateTextureFormat);
};

#endif