#ifndef CDATLoaderManager_H
#define CDATLoaderManager_H

#include "BXA.h"
#include "Format/CFormatManager.h"
#include "Object/CSingleton.h"
#include "eDATLoaderEntryType.h"
#include "Collection/Games/ePlatformedGame.h"
#include <string>

class bxa::CDATLoaderFormat;

class bxa::CDATLoaderManager : public bxa::CFormatManager<bxa::CDATLoaderFormat>, public bxa::CSingleton<bxa::CDATLoaderManager>
{
public:
	CDATLoaderManager(void);

	void						init(void);
	void						uninit(void);

	static eDATLoaderEntryType	getDATEntryTypeFromString(std::string strType);
	static std::string			getDefaultGameDATSubPath(bxa::ePlatformedGame ePlatformedGameValue);
};

#endif