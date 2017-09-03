#pragma once

#include "nsimgf.h"
#include "Object/Manager.h"
#include "Localization/ELanguage.h"
#include "Pool/VectorPool.h"

class imgf::Language;

class imgf::LanguageManager : public bxcf::Manager, public bxcf::VectorPool<Language*>
{
public:
	void							init(void);
	void							uninit(void);

	Language*						getLanguageById(bxcf::ELanguage ELanguageValue);

private:
	void							initLanguages(void);
	void							uninitLanguages(void);
};