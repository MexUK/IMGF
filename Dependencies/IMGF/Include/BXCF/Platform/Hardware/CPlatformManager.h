#pragma once

#include "nsbxcf.h"
#include "Object/CManager.h"
#include "Object/CSingleton.h"
#include "Pool/CVectorPool.h"
#include "CPlatform.h"
#include "EPlatform.h"
#include <string>

class bxcf::CPlatformManager : public bxcf::CManager, public bxcf::CSingleton<bxcf::CPlatformManager>, public bxcf::CVectorPool<bxcf::CPlatform*>
{
public:
	void											init(void);
	void											uninit(void);

	std::string										getPlatformName(bxcf::EPlatform EPlatformValue);

private:
	void											initPlatforms(void);
	void											uninitPlatforms(void);
};