#pragma once

#include "nsimgf.h"
#include "Format/CFormatManager.h"
#include "Object/CSingleton.h"

class imgf::LSTFormat;

class imgf::LSTManager : public bxcf::CFormatManager<LSTFormat>, public bxcf::CSingleton<LSTManager>
{
public:
	LSTManager(void);
	
	void				init(void);
	void				uninit(void);
};