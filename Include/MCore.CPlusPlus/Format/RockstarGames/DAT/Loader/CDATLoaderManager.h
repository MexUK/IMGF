#ifndef CDATLoaderManager_H
#define CDATLoaderManager_H

#include "mcore.h"
#include "Format/CFormatManager.h"
#include "Object/CSingleton.h"
#include "eDATLoaderEntryType.h"
#include "Collection/Games/ePlatformedGame.h"
#include <string>

class mcore::CDATLoaderFormat;

class mcore::CDATLoaderManager : public mcore::CFormatManager<mcore::CDATLoaderFormat>, public mcore::CSingleton<mcore::CDATLoaderManager>
{
public:
	CDATLoaderManager(void);

	void						init(void);
	void						uninit(void);

	static eDATLoaderEntryType	getDATEntryTypeFromString(std::string strType);
	static std::string			getDefaultGameDATSubPath(mcore::ePlatformedGame ePlatformedGameValue);
};

#endif