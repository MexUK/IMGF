#ifndef CCOLFormat_H
#define CCOLFormat_H

#include "bxcf.h"
#include "Format/CFormat.h"
#include "Pool/CVectorPool.h"
#include "eCOLVersion.h"
#include "CCOLEntry.h"
#include <string>
#include <vector>

class bxcf::CCOLVersion;

class bxcf::CCOLFormat : public bxcf::CFormat, public bxcf::CVectorPool<bxcf::CCOLEntry*>
{
public:
	CCOLFormat(void) : CFormat(true) {};

	void							unload(void);

	void							setCOLVersion(CCOLVersion *pCOLVersion);

	std::vector<std::string>		getModelNames(void);
	bxcf::CCOLEntry*						getEntryByName(std::string strName);
	std::vector<bxcf::CCOLEntry*>			getEntriesByModelName(std::string strModelName);

	void							sort(void);
	static bool						sortFunction(bxcf::CCOLEntry *pCOLEntry1, bxcf::CCOLEntry *pCOLEntry2);

private:
	void							unserialize(void);
	void							serialize(void);
};

#endif