#pragma once

#include "nsimgf.h"
#include "Object/Manager.h"
#include <string>
#include <unordered_map>

class imgf::SettingsManager : public bxcf::Manager
{
public:
	static const std::string						REGULAR_SETTINGS_STORAGE_SECTION;
	static const std::string						INTERNAL_SETTINGS_STORAGE_SECTION;

public:
	void											init(void);
	void											uninit(void);

	void											setUsesINIStorage(bool bUsesINIStorage) { m_bUsesINIStorage = bUsesINIStorage; }
	bool											doesUseINIStorage(void) { return m_bUsesINIStorage; }

	void											setINIFilePath(std::string strINIFilePath) { m_strINIFilePath = strINIFilePath; }
	std::string										getINIFilePath(void) { return m_strINIFilePath; }

	void											setRegistryKey(std::string strRegistryKey) { m_strRegistryKey = strRegistryKey; }
	std::string										getRegistryKey(void) { return m_strRegistryKey; }

	static void										setSetting(std::string strSettingName, std::string strValue, bool bMemoryOnly = false);
	static std::string								getSetting(std::string strSettingName);
	static uint32									getSettingInt(std::string strSettingName);
	static bool										getSettingBool(std::string strSettingName);

	static void										setInternalSetting(std::string strInternalSettingName, std::string strValue, bool bMemoryOnly = false);
	static std::string								getInternalSetting(std::string strInternalSettingName);

private:
	bool											m_bUsesINIStorage;
	std::string										m_strRegistryKey;
	std::string										m_strINIFilePath;
	std::unordered_map<std::string, bool>			m_umapSettings_Bool;
	std::unordered_map<std::string, int>			m_umapSettings_Int;
	std::unordered_map<std::string, std::string>	m_umapSettings_String;
};