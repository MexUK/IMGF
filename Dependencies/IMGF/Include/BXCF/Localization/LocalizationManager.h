#pragma once

#include "nsbxcf.h"
#include "Object/Manager.h"
#include "ELanguage.h"
#include "Object/Singleton.h"
#include <string>
#include <unordered_map>

class bxcf::LocalizationManager : public bxcf::Manager, public bxcf::Singleton<bxcf::LocalizationManager>
{
public:
	void											init(void);
	void											uninit(void);

	void											loadTranslatedText(void);

	std::string										getTranslatedText(std::string strInternalName);
	std::wstring									getTranslatedTextW(std::string strInternalName);

	std::string										getTranslatedFormattedText(std::string strInternalName, ...);
	std::string										getTranslatedFormattedTextVA(std::string strInternalName, va_list vlArguments);
	std::wstring									getTranslatedFormattedTextW(std::string strInternalName, ...);

	void											setActivELanguage(bxcf::ELanguage eActivELanguage) { m_uiActiveLanguage = eActivELanguage; }
	bxcf::ELanguage									getActivELanguage(void) { return m_uiActiveLanguage; }

	void											setActivELanguageName(std::string& strActivELanguageName) { m_strActivELanguageName = strActivELanguageName; }
	std::string&									getActivELanguageName(void) { return m_strActivELanguageName; }

	void											setInstallationPath(std::string& strInstallationPath) { m_strInstallationPath = strInstallationPath; }
	std::string&									getInstallationPath(void) { return m_strInstallationPath; }

	std::unordered_map<std::string, std::string>&	getTranslatedTextEntries_ActivELanguage(void) { return m_umapTranslatedText_ActivELanguage; }
	std::unordered_map<std::string, std::string>&	getTranslatedTextEntries_English(void) { return m_umapTranslatedText_English; }

	std::unordered_map<std::string, std::string>	getTranslatedTextEntries(void);

private:
	bxcf::ELanguage									m_uiActiveLanguage;
	std::string										m_strActivELanguageName;
	std::string										m_strInstallationPath;
	std::unordered_map<std::string, std::string>	m_umapTranslatedText_ActivELanguage;
	std::unordered_map<std::string, std::string>	m_umapTranslatedText_English;
};