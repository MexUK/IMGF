#ifndef CDATLoaderManager_H
#define CDATLoaderManager_H

#include "bxcf.h"
#include "Format/CFormatManager.h"
#include "Object/CSingleton.h"
#include "eDATLoaderEntryType.h"
#include "Collection/Games/ePlatformedGame.h"
#include <string>

class bxcf::CDATLoaderFormat;

class bxcf::CDATLoaderManager : public bxcf::CFormatManager<bxcf::CDATLoaderFormat>, public bxcf::CSingleton<bxcf::CDATLoaderManager>
{
public:
	CDATLoaderManager(void);

	void						init(void);
	void						uninit(void);

	static eDATLoaderEntryType	getDATEntryTypeFromString(std::string strType);
	static std::string			getDefaultGameDATSubPath(bxcf::ePlatformedGame ePlatformedGameValue);
};

#endif