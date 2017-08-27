#pragma once

#include "nsbxgi.h"
#include "Type/Types.h"
#include "Format/CFormat.h"
#include "Pool/CVectorPool.h"
#include "CDBEntry.h"
#include <string>
#include <vector>

class bxgi::CIMGFormat;
class bxgi::CIMGEntry;

class CDBFormat : public bxcf::CFormat, public bxcf::CVectorPool<CDBEntry*>
{
public:
	CDBFormat(void) : CFormat(true, bxcf::LITTLE_ENDIAN) {};
	
	void								unload(void);

	bool								isIMGEntryFound(bxgi::CIMGFormat *pIMGFile, bxgi::CIMGEntry *pIMGEntry);
	CDBEntry*							getEntryByNameExactCase(std::string strEntryName);

	void								setDBVersion(uint32 uiDBVersion) { m_uiDBVersion = uiDBVersion; }
	uint32								getDBVersion(void) { return m_uiDBVersion; }

private:
	void								unserialize(void);
	void								serialize(void);

private:
	uint32								m_uiDBVersion;
};