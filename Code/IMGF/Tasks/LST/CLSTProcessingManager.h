#pragma once

#include "nsimgf.h"
#include "Object/CManager.h"
#include <string>

class imgf::CLSTFormat;

class imgf::CLSTProcessingManager : public bxcf::CManager
{
public:
	void							init(void);
	void							uninit(void);

	void							process(CLSTFormat *pLSTFile);
};