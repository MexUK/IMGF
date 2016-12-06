#include "CAutomatedTesting.h"

using namespace std;

template<class Manager, class Format>
void						testFormatSerialization(string strFormatFilePath)
{
	// test parsing
	Format *pFormat = Manager::getInstance()->parseViaFile(strFormatFilePath);
	bool bHasError = pFormat->doesHaveError();
	if(bHasError)
	{
		pFormat->unload();
		delete pFormat;
		throw TESTING_PARSE;
	}
	
	// test storing
	string strOutputFormatFilePath = "Output/" + CPathManager::getFileName(strFormatFilePath);
	pFormat->storeViaFile(strOutputFormatFilePath);
	if(bHasError)
	{
		pFormat->unload();
		delete pFormat;
		throw TESTING_STORE;
	}
	
	// test store with file that is: stored, then parsed, then stored
	if(!CFileManager::compareFiles(strFormatFilePath, strOutputFormatFilePath))
	{
		pFormat->unload();
		delete pFormat;
		throw TESTING_COMPARE;
	}
	
	// unload
	pFormat->unload();
	delete pFormat;
}

void						CAutomatedTesting::testFormatsSerialization(void)
{
	testFormatSerialization<CBMPManager,		CBMPFormat>			("a.bmp");
	testFormatSerialization<CCOLManager,		CCOLFormat>			("a.col");
	testFormatSerialization<CDATLoaderManager,	CDATLoaderFormat>	("a.dat");
	testFormatSerialization<CDATPathManager,	CDATPathFormat>		("a.dat");
	testFormatSerialization<CDBManager,			CDBFormat>			("a.db");
	testFormatSerialization<CDDSManager,		CDDSFormat>			("a.dds");
	testFormatSerialization<CDFFManager,		CDFFFormat>			("a.dff");
	testFormatSerialization<CIDEManager,		CIDEFormat>			("a.ide");
	testFormatSerialization<CIMGManager,		CIMGFormat>			("a.img");
	testFormatSerialization<CIPLManager,		CIPLFormat>			("a.ipl");
	testFormatSerialization<CLSTManager,		CLSTFormat>			("a.lst");
	testFormatSerialization<CTXDManager,		CTXDFormat>			("a.txd");
	testFormatSerialization<CWDRManager,		CWDRFormat>			("a.wdr");
	testFormatSerialization<CWTDManager,		CWTDFormat>			("a.wtd");
}