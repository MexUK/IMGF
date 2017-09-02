#pragma once

#include "nsimgf.h"
#include "Object/CManager.h"
#include "Localization/ELanguage.h"
#include "Pool/CVectorPool.h"

class imgf::Language;

class imgf::LanguageManager : public bxcf::CManager, public bxcf::CVectorPool<Language*>
{
public:
	void							init(void);
	void							uninit(void);

	Language*						getLanguageById(bxcf::ELanguage ELanguageValue);

private:
	void							initLanguages(void);
	void							uninitLanguages(void);
};