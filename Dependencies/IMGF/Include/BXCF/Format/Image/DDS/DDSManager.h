#pragma once

#include "nsbxcf.h"
#include "Format/FormatManager.h"
#include "Object/Singleton.h"

class bxcf::DDSFormat;

class bxcf::DDSManager : public bxcf::FormatManager<bxcf::DDSFormat>, public bxcf::Singleton<bxcf::DDSManager>
{
public:
	DDSManager(void);

	void						init(void);
	void						uninit(void);
};