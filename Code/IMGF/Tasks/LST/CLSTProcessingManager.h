#pragma once

#include "Object/CManager.h"
#include <string>

class CLSTFormat;

class CLSTProcessingManager : public bxcf::CManager
{
public:
	void							init(void);
	void							uninit(void);

	void							process(CLSTFormat *pLSTFile);
};