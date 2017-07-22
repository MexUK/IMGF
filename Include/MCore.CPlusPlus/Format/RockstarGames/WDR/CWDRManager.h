#ifndef CWDRManager_H
#define CWDRManager_H

#include "bxa.h"
#include "Format/CFormatManager.h"
#include "Object/CSingleton.h"
#include <string>

class bxa::CWDRFormat;
class bxa::CIntermediateModelFormat;

class bxa::CWDRManager : public bxa::CFormatManager<bxa::CWDRFormat>, public bxa::CSingleton<bxa::CWDRManager>
{
public:
	CWDRManager(void);

	void								init(void);
	void								uninit(void);

	static bxa::CWDRFormat*					convertIntermediateModelFileToWDRFile(bxa::CIntermediateModelFormat *pGeneralModelFile);

	static uint32						getPackedOffset(uint32 uiOffset);
	static uint32						getPackedDataOffset(uint32 uiOffset);
};

#endif