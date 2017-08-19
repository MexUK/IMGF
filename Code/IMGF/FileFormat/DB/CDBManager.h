#ifndef CDBManager_H
#define CDBManager_H

#include "bxgi.h"
#include "Format/CFormatManager.h"
#include "Object/CSingleton.h"
#include <string>

class CDBFormat;
class bxgi::CIMGFormat;

class CDBManager : public bxcf::CFormatManager<CDBFormat>, public bxcf::CSingleton<CDBManager>
{
public:
	CDBManager(void);
	
	void						init(void);
	void						uninit(void);

	CDBFormat*					createDBFileFromIMGFile(bxgi::CIMGFormat *pIMGFile);
	CDBFormat*					createBlankDBFile(void);
	
	bool						compareDBFiles(CDBFormat *pDBFile1, CDBFormat *pDBFile2);
};

#endif