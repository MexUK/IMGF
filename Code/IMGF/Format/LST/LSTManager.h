#pragma once

#include "nsimgf.h"
#include "Format/FormatManager.h"
#include "Object/Singleton.h"

class imgf::LSTFormat;

class imgf::LSTManager : public bxcf::FormatManager<LSTFormat>, public bxcf::Singleton<LSTManager>
{
public:
	LSTManager(void);
	
	void				init(void);
	void				uninit(void);
};