#ifndef CLSTManager_H
#define CLSTManager_H

#include "Format/CFormatManager.h"
#include "Object/CSingleton.h"
#include <string>

class CLSTFormat;

class CLSTManager : public bxcf::CFormatManager<CLSTFormat>, public bxcf::CSingleton<CLSTManager>
{
public:
	CLSTManager(void);
	
	void				init(void);
	void				uninit(void);
};

#endif