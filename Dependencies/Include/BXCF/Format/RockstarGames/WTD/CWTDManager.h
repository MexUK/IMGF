#ifndef CWTDManager_H
#define CWTDManager_H

#include "bxcf.h"
#include "Format/CFormatManager.h"
#include "Object/CSingleton.h"
#include "CWTDFormat.h"
#include "d3d9.h"
#include <string>

class bxcf::CWTDEntry;
class bxcf::CIntermediateTextureFormat;

class bxcf::CWTDManager : public bxcf::CFormatManager<bxcf::CWTDFormat>, public bxcf::CSingleton<bxcf::CWTDManager>
{
public:
	CWTDManager(void);
	
	void						init(void);
	void						uninit(void);

	static uint32				getImageDataSize(CWTDEntry *pWTDEntry, bool bIncludeLevels);

	bxcf::CWTDFormat*					convertIntermediateTextureFileToWTDFile(bxcf::CIntermediateTextureFormat *pIntermediateTextureFormat);
};

#endif