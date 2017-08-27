#pragma once

#include "nsbxcf.h"
#include "Format/CFormatManager.h"
#include "Object/CSingleton.h"

class bxcf::CDDSFormat;

class bxcf::CDDSManager : public bxcf::CFormatManager<bxcf::CDDSFormat>, public bxcf::CSingleton<bxcf::CDDSManager>
{
public:
	CDDSManager(void);

	void						init(void);
	void						uninit(void);
};