#include "DBManager.h"
#include "DBFormat.h"
#include "DBEntry.h"
#include "Format/IMG/Regular/IMGFormat.h"
#include "Format/IMG/Regular/IMGEntry.h"
#include "Static/String2.h"
#include "Stream/DataReader.h"
#include "Static/Debug.h"

using namespace std;
using namespace bxcf;
using namespace bxgi;
using namespace imgf;

DBManager::DBManager(void)
{
}

void			DBManager::init(void)
{
}
void			DBManager::uninit(void)
{
}

DBFormat*		DBManager::createDBFileFromIMGFile(IMGFormat *pIMGFile)
{
	DBFormat *pDBFile = new DBFormat;
	pDBFile->setDBVersion(0x01);
	for (auto pIMGEntry : pIMGFile->getEntries())
	{
		DBEntry *pDBEntry = new DBEntry;
		pDBEntry->setEntryName(pIMGEntry->getEntryName());
		pDBEntry->setEntrySize(pIMGEntry->getEntrySize());
		pDBEntry->setEntryDataCRC(String2::getCRC(pIMGEntry->getEntryData()));
		pDBEntry->setEntryCreationDate(pIMGEntry->getFileCreationDate());
		pDBEntry->setHasIssue(false);
		pDBFile->addEntry(pDBEntry);
	}
	return pDBFile;
}

DBFormat*		DBManager::createBlankDBFile(void)
{
	DBFormat *pDBFile = new DBFormat;
	pDBFile->setDBVersion(0x01);
	return pDBFile;
}

bool			DBManager::compareDBFiles(DBFormat *pDBFile1, DBFormat *pDBFile2)
{
	if (pDBFile1->getDBVersion() != pDBFile2->getDBVersion())
	{
		return false;
	}
	if (pDBFile1->getEntryCount() != pDBFile2->getEntryCount())
	{
		return false;
	}
	for (uint32 i = 0, j = pDBFile1->getEntryCount(); i < j; i++)
	{
		if (pDBFile1->getEntryByIndex(i)->doesHaveIssue() != pDBFile2->getEntryByIndex(i)->doesHaveIssue() ||
			pDBFile1->getEntryByIndex(i)->getEntryName() != pDBFile2->getEntryByIndex(i)->getEntryName() ||
			pDBFile1->getEntryByIndex(i)->getEntryDataCRC() != pDBFile2->getEntryByIndex(i)->getEntryDataCRC() ||
			pDBFile1->getEntryByIndex(i)->getEntryCreationDate() != pDBFile2->getEntryByIndex(i)->getEntryCreationDate() ||
			pDBFile1->getEntryByIndex(i)->getEntrySize() != pDBFile2->getEntryByIndex(i)->getEntrySize())
		{
			return false;
		}
	}
	return true;
}