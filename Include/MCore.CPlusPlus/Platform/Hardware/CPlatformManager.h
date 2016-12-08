#ifndef CPlatformManager_H
#define CPlatformManager_H

#include "mcore.h"
#include "Object/CManager.h"
#include "Object/CSingleton.h"
#include "Pool/CVectorPool.h"
#include "CPlatform.h"
#include "ePlatform.h"
#include <string>

class mcore::CPlatformManager : public mcore::CManager, public mcore::CSingleton<mcore::CPlatformManager>, public mcore::CVectorPool<mcore::CPlatform*>
{
public:
	void											init(void);
	void											uninit(void);

	std::string										getPlatformName(mcore::ePlatform ePlatformValue);

private:
	void											initPlatforms(void);
	void											uninitPlatforms(void);
};

#endif