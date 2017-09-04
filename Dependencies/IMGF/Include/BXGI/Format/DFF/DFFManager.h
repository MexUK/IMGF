#pragma once

#include "nsbxgi.h"
#include "Format/FormatManager.h"
#include "Object/Singleton.h"

class bxgi::DFFFormat;

class bxgi::DFFManager : public bxcf::FormatManager<bxgi::DFFFormat>, public bxcf::Singleton<bxgi::DFFManager>
{
public:
	DFFManager(void);

	void						init(void);
	void						uninit(void);
};