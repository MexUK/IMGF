#ifndef CCOLFormat_H
#define CCOLFormat_H

#include "bxa.h"
#include "Format/CFormat.h"
#include "Pool/CVectorPool.h"
#include "eCOLVersion.h"
#include "CCOLEntry.h"
#include <string>
#include <vector>

class bxa::CCOLVersion;

class bxa::CCOLFormat : public bxa::CFormat, public bxa::CVectorPool<bxa::CCOLEntry*>
{
public:
	CCOLFormat(void) : CFormat(true) {};

	void							unload(void);

	void							setCOLVersion(CCOLVersion *pCOLVersion);

	std::vector<std::string>		getModelNames(void);
	bxa::CCOLEntry*						getEntryByName(std::string strName);
	std::vector<bxa::CCOLEntry*>			getEntriesByModelName(std::string strModelName);

	void							sort(void);
	static bool						sortFunction(bxa::CCOLEntry *pCOLEntry1, bxa::CCOLEntry *pCOLEntry2);

private:
	void							unserialize(void);
	void							serialize(void);
};

#endif