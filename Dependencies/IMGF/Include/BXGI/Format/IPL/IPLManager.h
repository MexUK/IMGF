#pragma once

#include "nsbxgi.h"
#include "Format/FormatManager.h"
#include "Object/Singleton.h"

class bxgi::IPLFormat;

class bxgi::IPLManager : public bxcf::FormatManager<bxgi::IPLFormat>, public bxcf::Singleton<bxgi::IPLManager>
{
public:
	IPLManager(void);
	
	void					init(void);
	void					uninit(void);
};