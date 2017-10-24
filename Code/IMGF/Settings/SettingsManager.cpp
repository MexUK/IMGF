#pragma warning(disable : 4005)

#include "nsbxcf.h"
#include "SettingsManager.h"
#include "IMGF.h"
#include "Globals.h"
#include "Static/Registry.h"
#include "Static/Path.h"
#include "Static/String.h"
#include "Static/AppDataPath.h"
#include "Format/IMG/Regular/IMGEntry.h"
#include "Format/Text/INI/INIManager.h"
#include "Localization/ELanguage.h"
#include "Style/StyleManager.h"

using namespace std;
using namespace bxcf;
using namespace bxgx;
using namespace imgf;

// settings for settings
const string						SettingsManager::REGULAR_SETTINGS_STORAGE_SECTION		= "RegularSettings";
const string						SettingsManager::INTERNAL_SETTINGS_STORAGE_SECTION		= "InternalSettings";

// initialization
void			SettingsManager::init(void)
{
	// storage - ini file
	setUsesINIStorage(true);
	setINIFilePath(AppDataPath::getRegularSettingsPath());
	
	// storage - registry
	//setUsesINIStorage(false);
	//setRegistryKey("IMGF\\Settings");

	// theme
	string strThemeName = getSetting("ThemeName");
	if (strThemeName == "")
	{
		strThemeName = "Main";
	}
	StyleManager::get()->setThemeName(strThemeName);
	StyleManager::get()->loadTheme();
}

void			SettingsManager::uninit(void)
{
}

// regular settings
void			SettingsManager::setSetting(string strSettingName, string strValue, bool bMemoryOnly)
{
	INIManager::setItem(AppDataPath::getRegularSettingsPath(), REGULAR_SETTINGS_STORAGE_SECTION, strSettingName, strValue);
}

string			SettingsManager::getSetting(string strSettingName)
{
	return INIManager::getItem(AppDataPath::getRegularSettingsPath(), REGULAR_SETTINGS_STORAGE_SECTION, strSettingName);
}

uint32			SettingsManager::getSettingInt(string strSettingName)
{
	return String::toUint32(getSetting(strSettingName));
}

bool			SettingsManager::getSettingBool(string strSettingName)
{
	return String::toUint32(getSetting(strSettingName)) == 1;
}

// internal settings
void			SettingsManager::setInternalSetting(string strInternalSettingName, string strValue, bool bMemoryOnly)
{
	INIManager::setItem(AppDataPath::getInternalSettingsPath(), INTERNAL_SETTINGS_STORAGE_SECTION, strInternalSettingName, strValue);
}

string			SettingsManager::getInternalSetting(string strSettingName)
{
	return INIManager::getItem(AppDataPath::getInternalSettingsPath(), INTERNAL_SETTINGS_STORAGE_SECTION, strSettingName);
}