#ifndef CWTDManager_H
#define CWTDManager_H

#include "mcore.h"
#include "Format/CFormatManager.h"
#include "Object/CSingleton.h"
#include "CWTDFormat.h"
#include "d3d9.h"
#include <string>

class mcore::CWTDEntry;
class mcore::CIntermediateTextureFormat;

class mcore::CWTDManager : public mcore::CFormatManager<mcore::CWTDFormat>, public mcore::CSingleton<mcore::CWTDManager>
{
public:
	CWTDManager(void);
	
	void						init(void);
	void						uninit(void);

	static uint32				getImageDataSize(CWTDEntry *pWTDEntry, bool bIncludeLevels);

	mcore::CWTDFormat*					convertIntermediateTextureFileToWTDFile(mcore::CIntermediateTextureFormat *pIntermediateTextureFormat);
};

#endif