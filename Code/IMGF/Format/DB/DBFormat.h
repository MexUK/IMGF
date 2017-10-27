#pragma once

#include "nsimgf.h"
#include "nsbxgi.h"
#include "Type/Types.h"
#include "Format/Format.h"
#include "Pool/VectorPool.h"
#include "Format/DB/DBEntry.h"
#include <string>
#include <vector>

class bxgi::IMGFormat;
class bxgi::IMGEntry;

class imgf::DBFormat : public bxcf::Format, public bxcf::VectorPool<imgf::DBEntry*>
{
public:
	using bxcf::VectorPool<imgf::DBEntry*>::getEntryCount;

	DBFormat(void) : bxcf::Format(true, bxcf::LITTLE_ENDIAN) {}
	DBFormat(std::string& strFilePathOrData, bool bStringIsFilePath = true) : bxcf::Format(strFilePathOrData, bStringIsFilePath, true, bxcf::LITTLE_ENDIAN) {}

	void								unload(void);

	bool								isIMGEntryFound(bxgi::IMGFormat *pIMGFile, bxgi::IMGEntry *pIMGEntry);
	imgf::DBEntry*						getEntryByNameExactCase(std::string strEntryName);

	void								setDBVersion(uint32 uiDBVersion) { m_uiDBVersion = uiDBVersion; }
	uint32								getDBVersion(void) { return m_uiDBVersion; }

private:
	void								_unserialize(void);
	void								_serialize(void);

private:
	uint32								m_uiDBVersion;
};