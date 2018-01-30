#pragma once

#include "nsimgf.h"
#include "Format/FormatManager.h"
#include "Object/Singleton.h"
#include "LSTFormat.h"

class imgf::LSTManager : public bxcf::FormatManager<LSTFormat>, public bxcf::Singleton<LSTManager>
{
public:
	LSTManager(void);
	
	void				init(void);
	void				uninit(void);
};