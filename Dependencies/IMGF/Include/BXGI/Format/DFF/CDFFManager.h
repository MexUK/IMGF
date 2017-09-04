#pragma once

#include "nsbxgi.h"
#include "Format/CFormatManager.h"
#include "Object/CSingleton.h"

class bxgi::CDFFFormat;

class bxgi::CDFFManager : public bxcf::CFormatManager<bxgi::CDFFFormat>, public bxcf::CSingleton<bxgi::CDFFManager>
{
public:
	CDFFManager(void);

	void						init(void);
	void						uninit(void);
};