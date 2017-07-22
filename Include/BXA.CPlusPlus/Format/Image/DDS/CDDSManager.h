#ifndef CDDSManager_H
#define CDDSManager_H

#include "BXA.h"
#include "Format/CFormatManager.h"
#include "Object/CSingleton.h"

class bxa::CDDSFormat;

class bxa::CDDSManager : public bxa::CFormatManager<bxa::CDDSFormat>, public bxa::CSingleton<bxa::CDDSManager>
{
public:
	CDDSManager(void);

	void						init(void);
	void						uninit(void);
};

#endif