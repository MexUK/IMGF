#pragma once

#include "nsbxgi.h"
#include "Format/CFormat.h"
#include "Pool/CVectorPool.h"
#include "ECOLVersion.h"
#include "CCOLEntry.h"
#include <string>
#include <vector>

class bxgi::CCOLVersion;

class bxgi::CCOLFormat : public bxcf::CFormat, public bxcf::CVectorPool<bxgi::CCOLEntry*>
{
public:
	CCOLFormat(void) : CFormat(true) {}

	void							unload(void);

	void							setCOLVersion(ECOLVersion uiCOLVersion);

	std::vector<std::string>		getModelNames(void);
	bxgi::CCOLEntry*						getEntryByName(std::string strName);
	std::vector<bxgi::CCOLEntry*>			getEntriesByModelName(std::string strModelName);

	void							sort(void);
	static bool						sortFunction(bxgi::CCOLEntry *pCOLEntry1, bxgi::CCOLEntry *pCOLEntry2);

private:
	void							unserialize(void);
	void							serialize(void);
};