#ifndef CPlatformManager_H
#define CPlatformManager_H

#include "bxa.h"
#include "Object/CManager.h"
#include "Object/CSingleton.h"
#include "Pool/CVectorPool.h"
#include "CPlatform.h"
#include "ePlatform.h"
#include <string>

class bxa::CPlatformManager : public bxa::CManager, public bxa::CSingleton<bxa::CPlatformManager>, public bxa::CVectorPool<bxa::CPlatform*>
{
public:
	void											init(void);
	void											uninit(void);

	std::string										getPlatformName(bxa::ePlatform ePlatformValue);

private:
	void											initPlatforms(void);
	void											uninitPlatforms(void);
};

#endif