#pragma once

#include "nsimgf.h"
#include "Object/CManager.h"
#include <string>

class imgf::LSTFormat;

class imgf::LSTProcessingManager : public bxcf::CManager
{
public:
	void							init(void);
	void							uninit(void);

	void							process(LSTFormat *pLSTFile);
};