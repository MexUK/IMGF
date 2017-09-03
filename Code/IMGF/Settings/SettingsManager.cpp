#pragma warning(disable : 4005)

#include "nsbxcf.h"
#include "SettingsManager.h"
#include "IMGF.h"
#include "Globals.h"
#include "GUI/Popups/PopupGUIManager.h"
#include "Static/Registry.h"
#include "Static/Path.h"
#include "Static/String2.h"
#include "Static/AppDataPath.h"
#include "Format/IMG/Regular/IMGEntry.h"
#include "Format/Text/INI/INIManager.h"

using namespace std;
using namespace bxcf;
using namespace imgf;

// settings for settings
const string						SettingsManager::REGULAR_SETTINGS_STORAGE_SECTION		= "RegularSettings";
const string						SettingsManager::INTERNAL_SETTINGS_STORAGE_SECTION		= "InternalSettings";

// initialization
void			SettingsManager::init(void)
{
	setUsesINIStorage(true);
	setINIFilePath(AppDataPath::getRegularSettingsPath());

	//setUsesINIStorage(false);
	//setRegistryKey("IMGF\\Settings");
}

void			SettingsManager::uninit(void)
{
	//unloadSettings();
}

// load/unload settings
void			SettingsManager::loadSettings(void)
{
	vector<string>
		vecSettingNames_Bool,
		vecSettingNames_Int,
		vecSettingNames_String
	;

	vecSettingNames_Bool = {
		"ColouredButtons",
		"ColouredTabs",
		"RebuildConfirmationOnClose",
		"RebuildOnConvert",
		"AutomaticLoggingBasic",
		"AutomaticLoggingExtended",
		"AskBeforeOverwritingFiles",
		"OverwriteOlderFiles",
		"OverwriteNewerFiles",
		"OverwriteProtectedFiles",
		"AutoSave",
		"RemoveOldVersionOnUpdate",
		"AutoCompressionImportReplace"
	};

	vecSettingNames_Int = {
		"Language"
	};

	vecSettingNames_String = {
		"QuickExportPath",
		"AutomaticLoggingPath"
	};

	for (string& strSettingName : vecSettingNames_Bool)
	{
		setSettingBool(strSettingName, getSettingBool_PermanentStroage(strSettingName), true);
	}

	for (string& strSettingName : vecSettingNames_Int)
	{
		setSettingInt(strSettingName, getSettingInt_PermanentStroage(strSettingName), true);
	}

	for (string& strSettingName : vecSettingNames_String)
	{
		setSettingString(strSettingName, getSettingString_PermanentStroage(strSettingName), true);
	}

	if (getSettingInt("Language") == LANGUAGE_UNKNOWN)
	{
		setSettingInt("Language", LANGUAGE_ENGLISH, true);
	}

	if (getSettingBool("ColouredTabs"))
	{
		// todo
		//((TabCtrl*)getIMGF()->getDialog()->GetDlgItem(1))->ModifyStyle(0, TCS_OWNERDRAWFIXED, 0);
	}
	else
	{
		//((TabCtrl*)getIMGF()->getDialog()->GetDlgItem(1))->ModifyStyle(TCS_OWNERDRAWFIXED, 0, 0);
	}

	// todo
	//getIMGF()->getDialog()->Invalidate();
	//getIMGF()->getDialog()->UpdateWindow();
}

void			SettingsManager::unloadSettings(void)
{
	m_umapSettings_Bool.clear();
	m_umapSettings_Int.clear();
	m_umapSettings_String.clear();
}

void			SettingsManager::reloadSettings(void)
{
	unloadSettings();
	loadSettings();
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

// internal settings
void			SettingsManager::setInternalSetting(string strInternalSettingName, string strValue, bool bMemoryOnly)
{
	INIManager::setItem(AppDataPath::getInternalSettingsPath(), INTERNAL_SETTINGS_STORAGE_SECTION, strInternalSettingName, strValue);
}

string			SettingsManager::getInternalSetting(string strSettingName)
{
	return INIManager::getItem(AppDataPath::getInternalSettingsPath(), INTERNAL_SETTINGS_STORAGE_SECTION, strSettingName);
}

// settings - data types - old
void			SettingsManager::setSettingBool(string strSettingName, bool bValue, bool bMemoryOnly)
{
	m_umapSettings_Bool[strSettingName] = bValue;
	if (!bMemoryOnly)
	{
		setSettingBool_PermanentStroage(strSettingName, bValue);
	}
}
void			SettingsManager::setSettingInt(string strSettingName, int iValue, bool bMemoryOnly)
{
	m_umapSettings_Int[strSettingName] = iValue;
	if (!bMemoryOnly)
	{
		setSettingInt_PermanentStroage(strSettingName, iValue);
	}
}
void			SettingsManager::setSettingString(string strSettingName, string strValue, bool bMemoryOnly)
{
	m_umapSettings_String[strSettingName] = strValue;
	if (!bMemoryOnly)
	{
		setSettingString_PermanentStroage(strSettingName, strValue); // todo - misspelt
	}
}

bool			SettingsManager::getSettingBool(string strSettingName)
{
	if (m_umapSettings_Bool.find(strSettingName) == m_umapSettings_Bool.end())
	{
		return false;
	}
	else
	{
		return m_umapSettings_Bool[strSettingName];
	}
}
int				SettingsManager::getSettingInt(string strSettingName)
{
	if (m_umapSettings_Int.find(strSettingName) == m_umapSettings_Int.end())
	{
		return 0;
	}
	else
	{
		return m_umapSettings_Int[strSettingName];
	}
}
string			SettingsManager::getSettingString(string strSettingName)
{
	if (m_umapSettings_String.find(strSettingName) == m_umapSettings_String.end())
	{
		return "";
	}
	else
	{
		return m_umapSettings_String[strSettingName];
	}
}

// settings permanent storage
void			SettingsManager::setSettingBool_PermanentStroage(string strSettingName, bool bValue)
{
	if (doesUseINIStorage())
	{
		INIManager::setItem(getINIFilePath(), "Settings", strSettingName, bValue ? "1" : "0");
	}
	else
	{
		Registry::setSoftwareValueInt(getRegistryKey(), strSettingName, bValue ? 1 : 0);
	}
}
void			SettingsManager::setSettingInt_PermanentStroage(string strSettingName, int iValue)
{
	if (doesUseINIStorage())
	{
		INIManager::setItem(getINIFilePath(), "Settings", strSettingName, String2::toString(iValue));
	}
	else
	{
		Registry::setSoftwareValueInt(getRegistryKey(), strSettingName, iValue);
	}
}
void			SettingsManager::setSettingString_PermanentStroage(string strSettingName, string strValue)
{
	if (doesUseINIStorage())
	{
		INIManager::setItem(getINIFilePath(), "Settings", strSettingName, strValue);
	}
	else
	{
		Registry::setSoftwareValueString(getRegistryKey(), strSettingName, strValue);
	}
}

bool			SettingsManager::getSettingBool_PermanentStroage(string strSettingName)
{
	if (doesUseINIStorage())
	{
		return INIManager::getItem(getINIFilePath(), "Settings", strSettingName) == "1";
	}
	else
	{
		return Registry::getSoftwareValueInt(getRegistryKey(), strSettingName) == 1;
	}
}
int				SettingsManager::getSettingInt_PermanentStroage(string strSettingName)
{
	if (doesUseINIStorage())
	{
		return String2::toNumber(INIManager::getItem(getINIFilePath(), "Settings", strSettingName));
	}
	else
	{
		return Registry::getSoftwareValueInt(getRegistryKey(), strSettingName);
	}
}
string			SettingsManager::getSettingString_PermanentStroage(string strSettingName)
{
	if (doesUseINIStorage())
	{
		return INIManager::getItem(getINIFilePath(), "Settings", strSettingName);
	}
	else
	{
		return Registry::getSoftwareValueString(getRegistryKey(), strSettingName);
	}
}