#ifndef CLanguage_H
#define CLanguage_H

#include "Localization/eLanguage.h"
#include <string>

class CLanguage
{
public:
	void					unload(void) {}

	void					setLanguageId(mcore::eLanguage eLanguageValue) { eLanguageId = eLanguageValue; }
	mcore::eLanguage		getLanguageId(void) { return eLanguageId; }
	
	void					setLanguageName(std::string strLanguageName) { m_strLanguageName = strLanguageName; }
	std::string				getLanguageName(void) { return m_strLanguageName; }

	void					setLocalizationKey(std::string strLocalizationKey) { m_strLocalizationKey = strLocalizationKey; }
	std::string				getLocalizationKey(void) { return m_strLocalizationKey; }
	
private:
	mcore::eLanguage		eLanguageId;
	std::string				m_strLanguageName;
	std::string				m_strLocalizationKey;
};

#endif