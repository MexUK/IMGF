#ifndef CWDRManager_H
#define CWDRManager_H

#include "mcore.h"
#include "Format/CFormatManager.h"
#include "Object/CSingleton.h"
#include <string>

class mcore::CWDRFormat;
class mcore::CIntermediateModelFormat;

class mcore::CWDRManager : public mcore::CFormatManager<mcore::CWDRFormat>, public mcore::CSingleton<mcore::CWDRManager>
{
public:
	CWDRManager(void);

	void								init(void);
	void								uninit(void);

	static mcore::CWDRFormat*					convertIntermediateModelFileToWDRFile(mcore::CIntermediateModelFormat *pGeneralModelFile);

	static uint32						getPackedOffset(uint32 uiOffset);
	static uint32						getPackedDataOffset(uint32 uiOffset);
};

#endif