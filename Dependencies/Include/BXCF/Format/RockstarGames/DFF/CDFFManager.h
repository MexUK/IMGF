#ifndef CDFFManager_H
#define CDFFManager_H

#include "bxcf.h"
#include "Format/CFormatManager.h"
#include "Object/CSingleton.h"

class bxcf::CDFFFormat;

class bxcf::CDFFManager : public bxcf::CFormatManager<bxcf::CDFFFormat>, public bxcf::CSingleton<bxcf::CDFFManager>
{
public:
	CDFFManager(void);

	void						init(void);
	void						uninit(void);
};

#endif