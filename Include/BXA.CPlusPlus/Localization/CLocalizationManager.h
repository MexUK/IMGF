#ifndef CLocalizationManager_H
#define CLocalizationManager_H

#include "BXA.h"
#include "Object/CManager.h"
#include "eLanguage.h"
#include "Object/CSingleton.h"
#include <string>
#include <unordered_map>

class bxa::CLocalizationManager : public bxa::CManager, public bxa::CSingleton<bxa::CLocalizationManager>
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

	void											setActiveLanguage(bxa::eLanguage eActiveLanguage) { m_eActiveLanguage = eActiveLanguage; }
	bxa::eLanguage										getActiveLanguage(void) { return m_eActiveLanguage; }

	void											setActiveLanguageName(std::string& strActiveLanguageName) { m_strActiveLanguageName = strActiveLanguageName; }
	std::string&									getActiveLanguageName(void) { return m_strActiveLanguageName; }

	void											setInstallationPath(std::string& strInstallationPath) { m_strInstallationPath = strInstallationPath; }
	std::string&									getInstallationPath(void) { return m_strInstallationPath; }

	std::unordered_map<std::string, std::string>&	getTranslatedTextEntries_ActiveLanguage(void) { return m_umapTranslatedText_ActiveLanguage; }
	std::unordered_map<std::string, std::string>&	getTranslatedTextEntries_English(void) { return m_umapTranslatedText_English; }

	std::unordered_map<std::string, std::string>	getTranslatedTextEntries(void);

private:
	bxa::eLanguage										m_eActiveLanguage;
	std::string										m_strActiveLanguageName;
	std::string										m_strInstallationPath;
	std::unordered_map<std::string, std::string>	m_umapTranslatedText_ActiveLanguage;
	std::unordered_map<std::string, std::string>	m_umapTranslatedText_English;
};

#endif