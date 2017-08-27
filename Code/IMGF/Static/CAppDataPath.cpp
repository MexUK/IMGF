#include "CAppDataPath.h"
#include "Static/CDataPath.h"

using namespace std;
using namespace bxcf;
using namespace imgf;

string					CAppDataPath::getRegularSettingsPath(void)
{
	return CDataPath::getDataPath() + "Settings" + CDataPath::FOLDER_SEPARATOR + "RegularSettings.ini";
}

string					CAppDataPath::getInternalSettingsPath(void)
{
	return CDataPath::getDataPath() + "Settings" + CDataPath::FOLDER_SEPARATOR + "InternalSettings.ini";
}

string					CAppDataPath::getSessionsPath(void)
{
	return CDataPath::getDataPath() + "Features" + CDataPath::FOLDER_SEPARATOR + "Sessions.ini";
}

string					CAppDataPath::getRecentlyOpenedPath(void)
{
	return CDataPath::getDataPath() + "Features" + CDataPath::FOLDER_SEPARATOR + "RecentlyOpened.ini";
}

string					CAppDataPath::getTaskDurationsPath(void)
{
	return CDataPath::getDataPath() + "Task" + CDataPath::FOLDER_SEPARATOR + "TaskDurations.ini";
}