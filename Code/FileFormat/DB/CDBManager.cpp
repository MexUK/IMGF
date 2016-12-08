#include "CDBManager.h"
#include "CDBFormat.h"
#include "CDBEntry.h"
#include "Format/RockstarGames/IMG/CIMGFormat.h"
#include "Format/RockstarGames/IMG/CIMGEntry.h"
#include "Type/String/CString2.h"
#include "Stream/CDataReader.h"
#include "Debug/CDebug.h"

using namespace std;
using namespace mcore;

CDBManager::CDBManager(void)
{
}

void			CDBManager::init(void)
{
}
void			CDBManager::uninit(void)
{
}

CDBFormat*		CDBManager::createDBFileFromIMGFile(CIMGFormat *pIMGFile)
{
	CDBFormat *pDBFile = new CDBFormat;
	pDBFile->setDBVersion(0x01);
	for (auto pIMGEntry : pIMGFile->getEntries())
	{
		CDBEntry *pDBEntry = new CDBEntry;
		pDBEntry->setEntryName(pIMGEntry->getEntryName());
		pDBEntry->setEntrySize(pIMGEntry->getEntrySize());
		pDBEntry->setEntryDataCRC(CString2::getCRC(pIMGEntry->getEntryData()));
		pDBEntry->setEntryCreationDate(pIMGEntry->getFileCreationDate());
		pDBEntry->setHasIssue(false);
		pDBFile->addEntry(pDBEntry);
	}
	return pDBFile;
}

CDBFormat*		CDBManager::createBlankDBFile(void)
{
	CDBFormat *pDBFile = new CDBFormat;
	pDBFile->setDBVersion(0x01);
	return pDBFile;
}

bool			CDBManager::compareDBFiles(CDBFormat *pDBFile1, CDBFormat *pDBFile2)
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