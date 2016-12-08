#ifndef CDFFManager_H
#define CDFFManager_H

#include "mcore.h"
#include "Format/CFormatManager.h"
#include "Object/CSingleton.h"

class mcore::CDFFFormat;

class mcore::CDFFManager : public mcore::CFormatManager<mcore::CDFFFormat>, public mcore::CSingleton<mcore::CDFFManager>
{
public:
	CDFFManager(void);

	void						init(void);
	void						uninit(void);
};

#endif