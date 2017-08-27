#include "CDBFormat.h"
#include "CDBEntry.h"
#include "Static/CString2.h"
#include "Format/IMG/Regular/CIMGFormat.h"
#include "Format/IMG/Regular/CIMGEntry.h"
#include "Stream/CDataReader.h"
#include "Stream/CDataWriter.h"

using namespace std;
using namespace bxcf;
using namespace bxgi;
using namespace imgf;

void								CDBFormat::unload(void)
{
	removeAllEntries();
}

void								CDBFormat::unserialize(void)
{
	unload();
	CDataReader *pDataReader = CDataReader::get();

	// DB file header
	m_uiDBVersion = pDataReader->readUint32();
	uint32 uiEntryCount = pDataReader->readUint32();

	// copy RG structs into wrapper structs - so that we can use std::string for strings in our structs rather than char arrays
	vector<CDBEntry*>& rvecDBEntries = getEntries();
	rvecDBEntries.resize(uiEntryCount);
	CDBEntry *pDBEntries = new CDBEntry[uiEntryCount];

	// DB file entries
	for (uint32 i = 0; i < uiEntryCount; i++)
	{
		CDBEntry *pDBEntry = pDBEntries++;
		rvecDBEntries[i] = pDBEntry;
		pDBEntry->unserialize();
	}
}

void								CDBFormat::serialize(void)
{
	CDataWriter *pDataWriter = CDataWriter::get();

	// DB file header
	pDataWriter->writeUint32(getDBVersion());
	pDataWriter->writeUint32(getEntryCount());

	// DB file entries
	for (auto pDBEntry : getEntries())
	{
		pDBEntry->serialize();
	}
}

bool								CDBFormat::isIMGEntryFound(CIMGFormat *pIMGFile, CIMGEntry *pIMGEntry)
{
	CDBEntry *pDBEntry = getEntryByNameExactCase(pIMGEntry->getEntryName());
	if (pDBEntry == nullptr)
	{
		return false;
	}

	if (pDBEntry->getEntryDataCRC() != CString2::getCRC(pIMGEntry->getEntryData()))
	{
		return false;
	}

	return true;
}

CDBEntry*							CDBFormat::getEntryByNameExactCase(string strEntryName)
{
	for (auto pDBEntry : getEntries())
	{
		if (pDBEntry->getEntryName() == strEntryName)
		{
			return pDBEntry;
		}
	}
	return nullptr;
}