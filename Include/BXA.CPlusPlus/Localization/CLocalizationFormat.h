#ifndef CLocalizationFormat_H
#define CLocalizationFormat_H

#include "BXA.h"
#include "Format/CFormat.h"
#include "eLanguage.h"
#include <string>
#include <unordered_map>

class bxa::CLocalizationFormat : public bxa::CFormat
{
public:
	CLocalizationFormat(void) : CFormat(false) {};

	void											setLanguage(bxa::eLanguage eActiveLanguage) { m_eLanguage = eActiveLanguage; }
	bxa::eLanguage										setLanguage(void) { return m_eLanguage; }

	std::unordered_map<std::string, std::string>	getTranslatedText(void) { return m_umapTranslatedText; }

private:
	void											unserialize(void);
	void											serialize(void); 
	
	void											unserializeLine(void);

private:
	bxa::eLanguage										m_eLanguage;
	std::unordered_map<std::string, std::string>	m_umapTranslatedText;
};

#endif