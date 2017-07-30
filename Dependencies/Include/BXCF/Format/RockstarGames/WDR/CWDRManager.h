#ifndef CWDRManager_H
#define CWDRManager_H

#include "bxcf.h"
#include "Format/CFormatManager.h"
#include "Object/CSingleton.h"
#include <string>

class bxcf::CWDRFormat;
class bxcf::CIntermediateModelFormat;

class bxcf::CWDRManager : public bxcf::CFormatManager<bxcf::CWDRFormat>, public bxcf::CSingleton<bxcf::CWDRManager>
{
public:
	CWDRManager(void);

	void								init(void);
	void								uninit(void);

	static bxcf::CWDRFormat*					convertIntermediateModelFileToWDRFile(bxcf::CIntermediateModelFormat *pGeneralModelFile);

	static uint32						getPackedOffset(uint32 uiOffset);
	static uint32						getPackedDataOffset(uint32 uiOffset);
};

#endif