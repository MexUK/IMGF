#ifndef CCOLFormat_H
#define CCOLFormat_H

#include "bxgi.h"
#include "Format/CFormat.h"
#include "Pool/CVectorPool.h"
#include "eCOLVersion.h"
#include "CCOLEntry.h"
#include <string>
#include <vector>

class bxgi::CCOLVersion;

class bxgi::CCOLFormat : public bxcf::CFormat, public bxcf::CVectorPool<bxgi::CCOLEntry*>
{
public:
	CCOLFormat(void) : CFormat(true) {};

	void							unload(void);

	void							setCOLVersion(CCOLVersion *pCOLVersion);

	std::vector<std::string>		getModelNames(void);
	bxgi::CCOLEntry*						getEntryByName(std::string strName);
	std::vector<bxgi::CCOLEntry*>			getEntriesByModelName(std::string strModelName);

	void							sort(void);
	static bool						sortFunction(bxgi::CCOLEntry *pCOLEntry1, bxgi::CCOLEntry *pCOLEntry2);

private:
	void							unserialize(void);
	void							serialize(void);
};

#endif