#ifndef CPlatformManager_H
#define CPlatformManager_H

#include "bxcf.h"
#include "Object/CManager.h"
#include "Object/CSingleton.h"
#include "Pool/CVectorPool.h"
#include "CPlatform.h"
#include "ePlatform.h"
#include <string>

class bxcf::CPlatformManager : public bxcf::CManager, public bxcf::CSingleton<bxcf::CPlatformManager>, public bxcf::CVectorPool<bxcf::CPlatform*>
{
public:
	void											init(void);
	void											uninit(void);

	std::string										getPlatformName(bxcf::ePlatform ePlatformValue);

private:
	void											initPlatforms(void);
	void											uninitPlatforms(void);
};

#endif