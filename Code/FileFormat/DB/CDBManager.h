#ifndef CDBManager_H
#define CDBManager_H

#include "Format/CFormatManager.h"
#include "Object/CSingleton.h"
#include <string>

class CDBFormat;
class bxa::CIMGFormat;

class CDBManager : public bxa::CFormatManager<CDBFormat>, public bxa::CSingleton<CDBManager>
{
public:
	CDBManager(void);
	
	void						init(void);
	void						uninit(void);

	CDBFormat*					createDBFileFromIMGFile(bxa::CIMGFormat *pIMGFile);
	CDBFormat*					createBlankDBFile(void);
	
	bool						compareDBFiles(CDBFormat *pDBFile1, CDBFormat *pDBFile2);
};

#endif