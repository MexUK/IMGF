#pragma once

#include "nsbxcf.h"
#include "Object/Manager.h"
#include "Object/Singleton.h"
#include "Pool/VectorPool.h"
#include "Platform.h"
#include "EPlatform.h"
#include <string>

class bxcf::PlatformManager : public bxcf::Manager, public bxcf::Singleton<bxcf::PlatformManager>, public bxcf::VectorPool<bxcf::Platform*>
{
public:
	void											init(void);
	void											uninit(void);

	std::string										getPlatformName(bxcf::EPlatform EPlatformValue);

private:
	void											initPlatforms(void);
	void											uninitPlatforms(void);
};