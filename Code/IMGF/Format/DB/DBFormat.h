#pragma once

#include "nsimgf.h"
#include "nsbxgi.h"
#include "Type/Types.h"
#include "Format/Format.h"
#include "Pool/VectorPool.h"
#include "DBEntry.h"
#include <string>
#include <vector>

class bxgi::CIMGFormat;
class bxgi::CIMGEntry;

class imgf::DBFormat : public bxcf::Format, public bxcf::VectorPool<imgf::DBEntry*>
{
public:
	DBFormat(void) : bxcf::Format(true, bxcf::LITTLE_ENDIAN) {}
	
	void								unload(void);

	bool								isIMGEntryFound(bxgi::CIMGFormat *pIMGFile, bxgi::CIMGEntry *pIMGEntry);
	imgf::DBEntry*						getEntryByNameExactCase(std::string strEntryName);

	void								setDBVersion(uint32 uiDBVersion) { m_uiDBVersion = uiDBVersion; }
	uint32								getDBVersion(void) { return m_uiDBVersion; }

private:
	void								unserialize(void);
	void								serialize(void);

private:
	uint32								m_uiDBVersion;
};