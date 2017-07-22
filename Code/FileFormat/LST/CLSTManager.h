#ifndef CLSTManager_H
#define CLSTManager_H

#include "Format/CFormatManager.h"
#include "Object/CSingleton.h"
#include <string>

struct CLSTFormat;

class CLSTManager : public bxa::CFormatManager<CLSTFormat>, public bxa::CSingleton<CLSTManager>
{
public:
	CLSTManager(void);
	
	void				init(void);
	void				uninit(void);
};

#endif