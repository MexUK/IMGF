#pragma once

#include "nsimgf.h"
#include <string>

class imgf::AppDataPath
{
public:
	static std::string					getRegularSettingsPath(void);
	static std::string					getInternalSettingsPath(void);
	static std::string					getFileGroupsPath(void);
	static std::string					getRecentlyOpenedPath(void);
	static std::string					getTaskDurationsPath(void);
};