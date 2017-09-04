#pragma once

#include "nsbxcf.h"
#include "Type/Types.h"
#include <string>
#include <vector>

class bxcf::INIManager
{
public:
	static bool						setItem(std::string strPath, std::string strSection, std::string strKey, std::string strValue);
	static bool						setItem(std::string strPath, std::string strSection, uint32 uiKey, std::string strValue);
	static bool						setItem(std::string strPath, uint32 uiSection, std::string strKey, std::string strValue);
	static bool						setItem(std::string strPath, uint32 uiSection, uint32 uiKey, std::string strValue);
	static std::string				getItem(std::string strPath, std::string strSection, std::string strKey);
	static std::string				getItem(std::string strPath, std::string strSection, uint32 uiKey);
	static std::string				getItem(std::string strPath, uint32 uiSection, std::string strKey);
	static std::string				getItem(std::string strPath, uint32 uiSection, uint32 uiKey);
	static bool						removeItem(std::string strPath, std::string strSection, std::string strKey);
	static bool						removeItem(std::string strPath, std::string strSection, uint32 uiKey);
	static bool						removeItem(std::string strPath, uint32 uiSection, std::string strKey);
	static bool						removeItem(std::string strPath, uint32 uiSection, uint32 uiKey);
	static bool						doesItemExist(std::string strPath, std::string strSection, std::string strKey);
	static bool						doesItemExist(std::string strPath, std::string strSection, uint32 uiKey);
	static bool						doesItemExist(std::string strPath, uint32 uiSection, std::string strKey);
	static bool						doesItemExist(std::string strPath, uint32 uiSection, uint32 uiKey);
	static std::vector<std::string>	getItems(std::string strPath, std::string strSection);
	static std::vector<std::string>	getItems(std::string strPath, uint32 uiSection);
	static void						addSection(std::string strPath, std::string strSection);
	static bool						removeSection(std::string strPath, std::string strSection);
	static bool						removeSection(std::string strPath, uint32 uiSection);
	static bool						doesSectionExist(std::string strPath, std::string strSection);
	static bool						doesSectionExist(std::string strPath, uint32 uiSection);
	static std::string				getSection(std::string strPath, uint32 uiSection);
	static std::vector<std::string>	getSections(std::string strPath);
	static void						clearFile(std::string strPath);
};