#pragma once

#include "nsimgf.h"
#include "Localization/ELanguage.h"
#include <string>

class imgf::Language
{
public:
	void					unload(void) {}

	void					setLanguageId(bxcf::ELanguage ELanguageValue) { ELanguageId = ELanguageValue; }
	bxcf::ELanguage		getLanguageId(void) { return ELanguageId; }
	
	void					setLanguageName(std::string strLanguageName) { m_strLanguageName = strLanguageName; }
	std::string				getLanguageName(void) { return m_strLanguageName; }

	void					setLocalizationKey(std::string strLocalizationKey) { m_strLocalizationKey = strLocalizationKey; }
	std::string				getLocalizationKey(void) { return m_strLocalizationKey; }
	
private:
	bxcf::ELanguage		ELanguageId;
	std::string				m_strLanguageName;
	std::string				m_strLocalizationKey;
};