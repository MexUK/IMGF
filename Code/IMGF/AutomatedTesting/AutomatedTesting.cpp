#include "AutomatedTesting.h"
#include "Format/Image/BMP/BMPManager.h"
#include "Format/Image/BMP/BMPFormat.h"

using namespace std;
using namespace bxcf;
using namespace imgf;

template<class Manager, class Format>
void						testFormatSerialization(string strFormatFilePath)
{
	// test parsing
	Format *pFormat = Manager::get()->parseViaFile(strFormatFilePath);
	bool bHasError = pFormat->doesHaveError();
	if(bHasError)
	{
		pFormat->unload();
		delete pFormat;
		throw TESTING_PARSE;
	}
	
	// test storing
	string strOutputFormatFilePath = "Output/" + Path::getFileName(strFormatFilePath);
	pFormat->storeViaFile(strOutputFormatFilePath);
	if(bHasError)
	{
		pFormat->unload();
		delete pFormat;
		throw TESTING_STORE;
	}
	
	// test store with file that is: stored, then parsed, then stored
	if(!File::compareFiles(strFormatFilePath, strOutputFormatFilePath))
	{
		pFormat->unload();
		delete pFormat;
		throw TESTING_COMPARE;
	}
	
	// unload
	pFormat->unload();
	delete pFormat;
}

void						AutomatedTesting::testFormatsSerialization(void)
{
	/*
	testFormatSerialization<BMPManager,		BMPFormat>			("a.bmp");
	testFormatSerialization<COLManager,		COLFormat>			("a.col");
	testFormatSerialization<DATLoaderManager,	DATLoaderFormat>	("a.dat");
	testFormatSerialization<DATPathManager,	DATPathFormat>		("a.dat");
	testFormatSerialization<DBManager,			DBFormat>			("a.db");
	testFormatSerialization<DDSManager,		DDSFormat>			("a.dds");
	testFormatSerialization<DFFManager,		DFFFormat>			("a.dff");
	testFormatSerialization<IDEManager,		IDEFormat>			("a.ide");
	testFormatSerialization<IMGManager,		IMGFormat>			("a.img");
	testFormatSerialization<IPLManager,		IPLFormat>			("a.ipl");
	testFormatSerialization<LSTManager,		LSTFormat>			("a.lst");
	testFormatSerialization<TXDManager,		TXDFormat>			("a.txd");
	testFormatSerialization<WDRManager,		WDRFormat>			("a.wdr");
	testFormatSerialization<WTDManager,		WTDFormat>			("a.wtd");
	*/
}