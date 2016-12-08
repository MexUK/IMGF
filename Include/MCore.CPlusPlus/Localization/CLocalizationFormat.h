#ifndef CLocalizationFormat_H
#define CLocalizationFormat_H

#include "mcore.h"
#include "Format/CFormat.h"
#include "eLanguage.h"
#include <string>
#include <unordered_map>

class mcore::CLocalizationFormat : public mcore::CFormat
{
public:
	CLocalizationFormat(void) : CFormat(false) {};

	void											setLanguage(mcore::eLanguage eActiveLanguage) { m_eLanguage = eActiveLanguage; }
	mcore::eLanguage										setLanguage(void) { return m_eLanguage; }

	std::unordered_map<std::string, std::string>	getTranslatedText(void) { return m_umapTranslatedText; }

private:
	void											unserialize(void);
	void											serialize(void); 
	
	void											unserializeLine(void);

private:
	mcore::eLanguage										m_eLanguage;
	std::unordered_map<std::string, std::string>	m_umapTranslatedText;
};

#endif