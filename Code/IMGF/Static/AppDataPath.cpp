#include "AppDataPath.h"
#include "Static/CDataPath.h"

using namespace std;
using namespace bxcf;
using namespace imgf;

string					AppDataPath::getRegularSettingsPath(void)
{
	return CDataPath::getDataPath() + "Settings" + CDataPath::FOLDER_SEPARATOR + "RegularSettings.ini";
}

string					AppDataPath::getInternalSettingsPath(void)
{
	return CDataPath::getDataPath() + "Settings" + CDataPath::FOLDER_SEPARATOR + "InternalSettings.ini";
}

string					AppDataPath::getSessionsPath(void)
{
	return CDataPath::getDataPath() + "Features" + CDataPath::FOLDER_SEPARATOR + "Sessions.ini";
}

string					AppDataPath::getRecentlyOpenedPath(void)
{
	return CDataPath::getDataPath() + "Features" + CDataPath::FOLDER_SEPARATOR + "RecentlyOpened.ini";
}

string					AppDataPath::getTaskDurationsPath(void)
{
	return CDataPath::getDataPath() + "Task" + CDataPath::FOLDER_SEPARATOR + "TaskDurations.ini";
}