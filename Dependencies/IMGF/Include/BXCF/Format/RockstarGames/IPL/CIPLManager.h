#ifndef CIPLManager_H
#define CIPLManager_H

#include "bxcf.h"
#include "Format/CFormatManager.h"
#include "Object/CSingleton.h"

class bxcf::CIPLFormat;

class bxcf::CIPLManager : public bxcf::CFormatManager<bxcf::CIPLFormat>, public bxcf::CSingleton<bxcf::CIPLManager>
{
public:
	CIPLManager(void);
	
	void					init(void);
	void					uninit(void);
};

#endif