#ifndef CDDSManager_H
#define CDDSManager_H

#include "mcore.h"
#include "Format/CFormatManager.h"
#include "Object/CSingleton.h"

class mcore::CDDSFormat;

class mcore::CDDSManager : public mcore::CFormatManager<mcore::CDDSFormat>, public mcore::CSingleton<mcore::CDDSManager>
{
public:
	CDDSManager(void);

	void						init(void);
	void						uninit(void);
};

#endif