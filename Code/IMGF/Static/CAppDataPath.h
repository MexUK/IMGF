#pragma once

#include <string>

class CAppDataPath
{
public:
	static std::string					getRegularSettingsPath(void);
	static std::string					getInternalSettingsPath(void);
	static std::string					getSessionsPath(void);
	static std::string					getRecentlyOpenedPath(void);
	static std::string					getTaskDurationsPath(void);
};