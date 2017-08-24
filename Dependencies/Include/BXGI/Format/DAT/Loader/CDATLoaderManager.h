#ifndef CDATLoaderManager_H
#define CDATLoaderManager_H

#include "bxgi.h"
#include "Format/CFormatManager.h"
#include "Object/CSingleton.h"
#include "eDATLoaderEntryType.h"
#include "Games/ePlatformedGame.h"
#include <string>

class bxgi::CDATLoaderFormat;

class bxgi::CDATLoaderManager : public bxcf::CFormatManager<bxgi::CDATLoaderFormat>, public bxcf::CSingleton<bxgi::CDATLoaderManager>
{
public:
	CDATLoaderManager(void);

	void						init(void);
	void						uninit(void);

	static eDATLoaderEntryType	getDATEntryTypeFromString(std::string strType);
	static std::string			getDefaultGameDATSubPath(bxgi::ePlatformedGame ePlatformedGameValue);
};

#endif