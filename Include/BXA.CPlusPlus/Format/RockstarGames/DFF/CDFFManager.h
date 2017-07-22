#ifndef CDFFManager_H
#define CDFFManager_H

#include "BXA.h"
#include "Format/CFormatManager.h"
#include "Object/CSingleton.h"

class bxa::CDFFFormat;

class bxa::CDFFManager : public bxa::CFormatManager<bxa::CDFFFormat>, public bxa::CSingleton<bxa::CDFFManager>
{
public:
	CDFFManager(void);

	void						init(void);
	void						uninit(void);
};

#endif