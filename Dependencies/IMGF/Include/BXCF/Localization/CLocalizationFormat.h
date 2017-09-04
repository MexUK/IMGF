#pragma once

#include "nsbxcf.h"
#include "Format/CFormat.h"
#include "ELanguage.h"
#include <string>
#include <unordered_map>

class bxcf::CLocalizationFormat : public bxcf::CFormat
{
public:
	CLocalizationFormat(void) : CFormat(false) {}

	void											setLanguage(bxcf::ELanguage eActivELanguage) { m_ELanguage = eActivELanguage; }
	bxcf::ELanguage										setLanguage(void) { return m_ELanguage; }

	std::unordered_map<std::string, std::string>	getTranslatedText(void) { return m_umapTranslatedText; }

private:
	void											unserialize(void);
	void											serialize(void); 
	
	void											unserializeLine(void);

private:
	bxcf::ELanguage										m_ELanguage;
	std::unordered_map<std::string, std::string>	m_umapTranslatedText;
};