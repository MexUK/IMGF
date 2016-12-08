#ifndef CIPLManager_H
#define CIPLManager_H

#include "mcore.h"
#include "Format/CFormatManager.h"
#include "Object/CSingleton.h"

class mcore::CIPLFormat;

class mcore::CIPLManager : public mcore::CFormatManager<mcore::CIPLFormat>, public mcore::CSingleton<mcore::CIPLManager>
{
public:
	CIPLManager(void);
	
	void					init(void);
	void					uninit(void);
};

#endif