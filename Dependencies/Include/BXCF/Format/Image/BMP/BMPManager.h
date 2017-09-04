#pragma once

#include "nsbxcf.h"
#include "Format/FormatManager.h"
#include "Object/Singleton.h"

class bxcf::BMPFormat;

class bxcf::BMPManager : public bxcf::FormatManager<bxcf::BMPFormat>, public bxcf::Singleton<bxcf::BMPManager>
{
public:
	BMPManager(void);

	void						init(void);
	void						uninit(void);
};