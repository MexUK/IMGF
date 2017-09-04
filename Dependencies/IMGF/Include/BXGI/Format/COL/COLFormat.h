#pragma once

#include "nsbxgi.h"
#include "Format/Format.h"
#include "Pool/VectorPool.h"
#include "ECOLVersion.h"
#include "COLEntry.h"
#include <string>
#include <vector>

class bxgi::COLVersion;

class bxgi::COLFormat : public bxcf::Format, public bxcf::VectorPool<bxgi::COLEntry*>
{
public:
	COLFormat(void) : Format(true) {}

	void							unload(void);

	void							setCOLVersion(ECOLVersion uiCOLVersion);

	std::vector<std::string>		getModelNames(void);
	bxgi::COLEntry*						getEntryByName(std::string strName);
	std::vector<bxgi::COLEntry*>			getEntriesByModelName(std::string strModelName);

	void							sort(void);
	static bool						sortFunction(bxgi::COLEntry *pCOLEntry1, bxgi::COLEntry *pCOLEntry2);

private:
	void							unserialize(void);
	void							serialize(void);
};