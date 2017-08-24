#ifndef CWDRManager_H
#define CWDRManager_H

#include "bxgi.h"
#include "Format/CFormatManager.h"
#include "Object/CSingleton.h"

class bxgi::CWDRFormat;
class bxgi::CIntermediateModelFormat;

class bxgi::CWDRManager : public bxcf::CFormatManager<bxgi::CWDRFormat>, public bxcf::CSingleton<bxgi::CWDRManager>
{
public:
	CWDRManager(void);

	void								init(void);
	void								uninit(void);

	static bxgi::CWDRFormat*			convertIntermediateModelFileToWDRFile(bxgi::CIntermediateModelFormat *pGeneralModelFile);

	static uint32						getPackedOffset(uint32 uiOffset);
	static uint32						getPackedDataOffset(uint32 uiOffset);
};

#endif