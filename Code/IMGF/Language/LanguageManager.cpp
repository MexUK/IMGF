#include "LanguageManager.h"
#include "Language.h"

using namespace bxcf;
using namespace imgf;

void			LanguageManager::init(void)
{
	initLanguages();
}
void			LanguageManager::uninit(void)
{
	uninitLanguages();
}

void			LanguageManager::initLanguages(void)
{
	Language *pLanguage = nullptr;

	/*
	pLanguage = new Language;
	pLanguage->setLanguageId(LANGUAGE_CZECH);
	pLanguage->setLanguageName("Czech");
	pLanguage->setLocalizationKey("Language_Czech");
	addEntry(pLanguage);

	pLanguage = new Language;
	pLanguage->setLanguageId(LANGUAGE_DUTCH);
	pLanguage->setLanguageName("Dutch");
	pLanguage->setLocalizationKey("Language_Dutch");
	addEntry(pLanguage);
	*/

	pLanguage = new Language;
	pLanguage->setLanguageId(LANGUAGE_ENGLISH);
	pLanguage->setLanguageName("English");
	pLanguage->setLocalizationKey("Language_English");
	addEntry(pLanguage);

	/*
	pLanguage = new Language;
	pLanguage->setLanguageId(LANGUAGE_GERMAN);
	pLanguage->setLanguageName("German");
	pLanguage->setLocalizationKey("Language_German");
	addEntry(pLanguage);
	*/
}
void			LanguageManager::uninitLanguages(void)
{
	removeAllEntries();
}

Language*		LanguageManager::getLanguageById(ELanguage ELanguageValue)
{
	for (Language *pLanguage : getEntries())
	{
		if (pLanguage->getLanguageId() == ELanguageValue)
		{
			return pLanguage;
		}
	}
	return nullptr;
}