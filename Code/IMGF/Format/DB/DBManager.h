#pragma once

#include "nsimgf.h"
#include "nsbxgi.h"
#include "Format/FormatManager.h"
#include "Object/Singleton.h"

class imgf::DBFormat;
class bxgi::CIMGFormat;

class imgf::DBManager : public bxcf::FormatManager<DBFormat>, public bxcf::Singleton<DBManager>
{
public:
	DBManager(void);
	
	void						init(void);
	void						uninit(void);

	DBFormat*					createDBFileFromIMGFile(bxgi::CIMGFormat *pIMGFile);
	DBFormat*					createBlankDBFile(void);
	
	bool						compareDBFiles(DBFormat *pDBFile1, DBFormat *pDBFile2);
};