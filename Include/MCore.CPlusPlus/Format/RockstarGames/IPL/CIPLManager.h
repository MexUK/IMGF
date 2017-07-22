#ifndef CIPLManager_H
#define CIPLManager_H

#include "bxa.h"
#include "Format/CFormatManager.h"
#include "Object/CSingleton.h"

class bxa::CIPLFormat;

class bxa::CIPLManager : public bxa::CFormatManager<bxa::CIPLFormat>, public bxa::CSingleton<bxa::CIPLManager>
{
public:
	CIPLManager(void);
	
	void					init(void);
	void					uninit(void);
};

#endif