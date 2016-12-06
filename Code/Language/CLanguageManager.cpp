#include "CLanguageManager.h"
#include "CLanguage.h"

using namespace mcore;

void			CLanguageManager::init(void)
{
	initLanguages();
}
void			CLanguageManager::uninit(void)
{
	uninitLanguages();
}

void			CLanguageManager::initLanguages(void)
{
	CLanguage *pLanguage = nullptr;

	/*
	pLanguage = new CLanguage;
	pLanguage->setLanguageId(LANGUAGE_CZECH);
	pLanguage->setLanguageName("Czech");
	pLanguage->setLocalizationKey("Language_Czech");
	addEntry(pLanguage);

	pLanguage = new CLanguage;
	pLanguage->setLanguageId(LANGUAGE_DUTCH);
	pLanguage->setLanguageName("Dutch");
	pLanguage->setLocalizationKey("Language_Dutch");
	addEntry(pLanguage);
	*/

	pLanguage = new CLanguage;
	pLanguage->setLanguageId(LANGUAGE_ENGLISH);
	pLanguage->setLanguageName("English");
	pLanguage->setLocalizationKey("Language_English");
	addEntry(pLanguage);

	/*
	pLanguage = new CLanguage;
	pLanguage->setLanguageId(LANGUAGE_GERMAN);
	pLanguage->setLanguageName("German");
	pLanguage->setLocalizationKey("Language_German");
	addEntry(pLanguage);
	*/
}
void			CLanguageManager::uninitLanguages(void)
{
	removeAllEntries();
}

CLanguage*		CLanguageManager::getLanguageById(eLanguage eLanguageValue)
{
	for (CLanguage *pLanguage : getEntries())
	{
		if (pLanguage->getLanguageId() == eLanguageValue)
		{
			return pLanguage;
		}
	}
	return nullptr;
}