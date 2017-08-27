#pragma once

#include "nsbxgi.h"
#include "Format/CFormatManager.h"
#include "Object/CSingleton.h"

class bxgi::CIPLFormat;

class bxgi::CIPLManager : public bxcf::CFormatManager<bxgi::CIPLFormat>, public bxcf::CSingleton<bxgi::CIPLManager>
{
public:
	CIPLManager(void);
	
	void					init(void);
	void					uninit(void);
};