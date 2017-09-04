#pragma once

#include "nsbxgi.h"
#include "Format/FormatManager.h"
#include "Object/Singleton.h"

class bxgi::WDRFormat;
class bxgi::IntermediateModelFormat;

class bxgi::WDRManager : public bxcf::FormatManager<bxgi::WDRFormat>, public bxcf::Singleton<bxgi::WDRManager>
{
public:
	WDRManager(void);

	void								init(void);
	void								uninit(void);

	static bxgi::WDRFormat*			convertIntermediateModelFileToWDRFile(bxgi::IntermediateModelFormat *pGeneralModelFile);

	static uint32						getPackedOffset(uint32 uiOffset);
	static uint32						getPackedDataOffset(uint32 uiOffset);
};