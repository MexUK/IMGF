#pragma once

#include "nsimgf.h"
#include "Format/CFormatManager.h"
#include "Object/CSingleton.h"

class imgf::CLSTFormat;

class imgf::CLSTManager : public bxcf::CFormatManager<CLSTFormat>, public bxcf::CSingleton<CLSTManager>
{
public:
	CLSTManager(void);
	
	void				init(void);
	void				uninit(void);
};