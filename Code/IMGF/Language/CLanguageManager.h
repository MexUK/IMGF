#ifndef CLanguageManager_H
#define CLanguageManager_H

#include "Object/CManager.h"
#include "Localization/eLanguage.h"
#include "Pool/CVectorPool.h"

class CLanguage;

class CLanguageManager : public bxcf::CManager, public bxcf::CVectorPool<CLanguage*>
{
public:
	void							init(void);
	void							uninit(void);

	CLanguage*						getLanguageById(bxcf::eLanguage eLanguageValue);

private:
	void							initLanguages(void);
	void							uninitLanguages(void);
};

#endif