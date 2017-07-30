#ifndef CLocalizationFormat_H
#define CLocalizationFormat_H

#include "bxcf.h"
#include "Format/CFormat.h"
#include "eLanguage.h"
#include <string>
#include <unordered_map>

class bxcf::CLocalizationFormat : public bxcf::CFormat
{
public:
	CLocalizationFormat(void) : CFormat(false) {};

	void											setLanguage(bxcf::eLanguage eActiveLanguage) { m_eLanguage = eActiveLanguage; }
	bxcf::eLanguage										setLanguage(void) { return m_eLanguage; }

	std::unordered_map<std::string, std::string>	getTranslatedText(void) { return m_umapTranslatedText; }

private:
	void											unserialize(void);
	void											serialize(void); 
	
	void											unserializeLine(void);

private:
	bxcf::eLanguage										m_eLanguage;
	std::unordered_map<std::string, std::string>	m_umapTranslatedText;
};

#endif