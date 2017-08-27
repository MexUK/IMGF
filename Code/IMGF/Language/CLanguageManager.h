#pragma once

#include "nsimgf.h"
#include "Object/CManager.h"
#include "Localization/ELanguage.h"
#include "Pool/CVectorPool.h"

class imgf::CLanguage;

class imgf::CLanguageManager : public bxcf::CManager, public bxcf::CVectorPool<CLanguage*>
{
public:
	void							init(void);
	void							uninit(void);

	CLanguage*						getLanguageById(bxcf::ELanguage ELanguageValue);

private:
	void							initLanguages(void);
	void							uninitLanguages(void);
};