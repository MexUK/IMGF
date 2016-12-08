#ifndef CCOLFormat_H
#define CCOLFormat_H

#include "mcore.h"
#include "Format/CFormat.h"
#include "Pool/CVectorPool.h"
#include "eCOLVersion.h"
#include "CCOLEntry.h"
#include <string>
#include <vector>

class mcore::CCOLVersion;

class mcore::CCOLFormat : public mcore::CFormat, public mcore::CVectorPool<mcore::CCOLEntry*>
{
public:
	CCOLFormat(void) : CFormat(true) {};

	void							unload(void);

	void							setCOLVersion(CCOLVersion *pCOLVersion);

	std::vector<std::string>		getModelNames(void);
	mcore::CCOLEntry*						getEntryByName(std::string strName);
	std::vector<mcore::CCOLEntry*>			getEntriesByModelName(std::string strModelName);

	void							sort(void);
	static bool						sortFunction(mcore::CCOLEntry *pCOLEntry1, mcore::CCOLEntry *pCOLEntry2);

private:
	void							unserialize(void);
	void							serialize(void);
};

#endif