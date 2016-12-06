#ifndef CDBManager_H
#define CDBManager_H

#include "Format/CFormatManager.h"
#include "Object/CSingleton.h"
#include <string>

class CDBFormat;
class mcore::CIMGFormat;

class CDBManager : public mcore::CFormatManager<CDBFormat>, public mcore::CSingleton<CDBManager>
{
public:
	CDBManager(void);
	
	void						init(void);
	void						uninit(void);

	CDBFormat*					createDBFileFromIMGFile(mcore::CIMGFormat *pIMGFile);
	CDBFormat*					createBlankDBFile(void);
	
	bool						compareDBFiles(CDBFormat *pDBFile1, CDBFormat *pDBFile2);
};

#endif