#ifndef CSettingsManager_H
#define CSettingsManager_H

#include "Object/CManager.h"
#include <string>
#include <unordered_map>

class CSettingsData;

class CSettingsManager : public mcore::CManager
{
public:
	void											init(void);
	void											uninit(void);

	void											loadSettings(void);
	void											unloadSettings(void);
	void											reloadSettings(void);

	void											setSettingBool(std::string strSettingName, bool bValue, bool bMemoryOnly = false);
	void											setSettingInt(std::string strSettingName, int iValue, bool bMemoryOnly = false);
	void											setSettingString(std::string strSettingName, std::string strValue, bool bMemoryOnly = false);

	bool											getSettingBool(std::string strSettingName);
	int												getSettingInt(std::string strSettingName);
	std::string										getSettingString(std::string strSettingName);

	void											setUsesINIStorage(bool bUsesINIStorage) { m_bUsesINIStorage = bUsesINIStorage; }
	bool											doesUseINIStorage(void) { return m_bUsesINIStorage; }

	void											setINIFilePath(std::string strINIFilePath) { m_strINIFilePath = strINIFilePath; }
	std::string										getINIFilePath(void) { return m_strINIFilePath; }

	void											setRegistryKey(std::string strRegistryKey) { m_strRegistryKey = strRegistryKey; }
	std::string										getRegistryKey(void) { return m_strRegistryKey; }

private:
	void											setSettingBool_PermanentStroage(std::string strSettingName, bool bValue);
	void											setSettingInt_PermanentStroage(std::string strSettingName, int iValue);
	void											setSettingString_PermanentStroage(std::string strSettingName, std::string strValue);

	bool											getSettingBool_PermanentStroage(std::string strSettingName);
	int												getSettingInt_PermanentStroage(std::string strSettingName);
	std::string										getSettingString_PermanentStroage(std::string strSettingName);

private:
	bool											m_bUsesINIStorage;
	std::string										m_strRegistryKey;
	std::string										m_strINIFilePath;
	std::unordered_map<std::string, bool>			m_umapSettings_Bool;
	std::unordered_map<std::string, int>			m_umapSettings_Int;
	std::unordered_map<std::string, std::string>	m_umapSettings_String;
};

#endif