#ifndef CWTDManager_H
#define CWTDManager_H

#include "bxa.h"
#include "Format/CFormatManager.h"
#include "Object/CSingleton.h"
#include "CWTDFormat.h"
#include "d3d9.h"
#include <string>

class bxa::CWTDEntry;
class bxa::CIntermediateTextureFormat;

class bxa::CWTDManager : public bxa::CFormatManager<bxa::CWTDFormat>, public bxa::CSingleton<bxa::CWTDManager>
{
public:
	CWTDManager(void);
	
	void						init(void);
	void						uninit(void);

	static uint32				getImageDataSize(CWTDEntry *pWTDEntry, bool bIncludeLevels);

	bxa::CWTDFormat*					convertIntermediateTextureFileToWTDFile(bxa::CIntermediateTextureFormat *pIntermediateTextureFormat);
};

#endif