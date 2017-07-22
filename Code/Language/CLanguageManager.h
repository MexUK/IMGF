#ifndef CLanguageManager_H
#define CLanguageManager_H

#include "Object/CManager.h"
#include "Localization/eLanguage.h"
#include "Pool/CVectorPool.h"

class CLanguage;

class CLanguageManager : public bxa::CManager, public bxa::CVectorPool<CLanguage*>
{
public:
	void							init(void);
	void							uninit(void);

	CLanguage*						getLanguageById(bxa::eLanguage eLanguageValue);

private:
	void							initLanguages(void);
	void							uninitLanguages(void);
};

#endif