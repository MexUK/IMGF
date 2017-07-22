#ifndef CDBFormat_H
#define CDBFormat_H

#include "Type/Types.h"
#include "Format/CFormat.h"
#include "Pool/CVectorPool.h"
#include "CDBEntry.h"
#include <string>
#include <vector>

class bxa::CIMGFormat;
class bxa::CIMGEntry;

class CDBFormat : public bxa::CFormat, public bxa::CVectorPool<CDBEntry*>
{
public:
	CDBFormat(void) : CFormat(true, bxa::LITTLE_ENDIAN) {};
	
	void								unload(void);

	bool								isIMGEntryFound(bxa::CIMGFormat *pIMGFile, bxa::CIMGEntry *pIMGEntry);
	CDBEntry*							getEntryByNameExactCase(std::string strEntryName);

	void								setDBVersion(uint32 uiDBVersion) { m_uiDBVersion = uiDBVersion; }
	uint32								getDBVersion(void) { return m_uiDBVersion; }

private:
	void								unserialize(void);
	void								serialize(void);

private:
	uint32								m_uiDBVersion;
};

#endif