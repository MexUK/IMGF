#include "AppDataPath.h"
#include "Static/DataPath.h"

using namespace std;
using namespace bxcf;
using namespace imgf;

string					AppDataPath::getRegularSettingsPath(void)
{
	return DataPath::getDataPath() + "Settings" + DataPath::FOLDER_SEPARATOR + "RegularSettings.ini";
}

string					AppDataPath::getInternalSettingsPath(void)
{
	return DataPath::getDataPath() + "Settings" + DataPath::FOLDER_SEPARATOR + "InternalSettings.ini";
}

string					AppDataPath::getSessionsPath(void)
{
	return DataPath::getDataPath() + "Features" + DataPath::FOLDER_SEPARATOR + "Sessions.ini";
}

string					AppDataPath::getRecentlyOpenedPath(void)
{
	return DataPath::getDataPath() + "Features" + DataPath::FOLDER_SEPARATOR + "RecentlyOpened.ini";
}

string					AppDataPath::getTaskDurationsPath(void)
{
	return DataPath::getDataPath() + "Task" + DataPath::FOLDER_SEPARATOR + "TaskDurations.ini";
}