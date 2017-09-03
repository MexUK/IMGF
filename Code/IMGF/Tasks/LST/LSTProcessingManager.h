#pragma once

#include "nsimgf.h"
#include "Object/Manager.h"
#include <string>

class imgf::LSTFormat;

class imgf::LSTProcessingManager : public bxcf::Manager
{
public:
	void							init(void);
	void							uninit(void);

	void							process(LSTFormat *pLSTFile);
};