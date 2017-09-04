#include "DBFormat.h"
#include "Static/String.h"
#include "Format/IMG/Regular/IMGFormat.h"
#include "Format/IMG/Regular/IMGEntry.h"
#include "Stream/DataReader.h"
#include "Stream/DataWriter.h"

using namespace std;
using namespace bxcf;
using namespace bxgi;
using namespace imgf;

void								DBFormat::unload(void)
{
	removeAllEntries();
}

void								DBFormat::unserialize(void)
{
	unload();
	DataReader *pDataReader = DataReader::get();

	// DB file header
	m_uiDBVersion = pDataReader->readUint32();
	uint32 uiEntryCount = pDataReader->readUint32();

	// copy RG structs into wrapper structs - so that we can use std::string for strings in our structs rather than char arrays
	vector<DBEntry*>& rvecDBEntries = getEntries();
	rvecDBEntries.resize(uiEntryCount);
	DBEntry *pDBEntries = new DBEntry[uiEntryCount];

	// DB file entries
	for (uint32 i = 0; i < uiEntryCount; i++)
	{
		DBEntry *pDBEntry = pDBEntries++;
		rvecDBEntries[i] = pDBEntry;
		pDBEntry->unserialize();
	}
}

void								DBFormat::serialize(void)
{
	DataWriter *pDataWriter = DataWriter::get();

	// DB file header
	pDataWriter->writeUint32(getDBVersion());
	pDataWriter->writeUint32(getEntryCount());

	// DB file entries
	for (auto pDBEntry : getEntries())
	{
		pDBEntry->serialize();
	}
}

bool								DBFormat::isIMGEntryFound(IMGFormat *pIMGFile, IMGEntry *pIMGEntry)
{
	DBEntry *pDBEntry = getEntryByNameExactCase(pIMGEntry->getEntryName());
	if (pDBEntry == nullptr)
	{
		return false;
	}

	if (pDBEntry->getEntryDataCRC() != String::getCRC(pIMGEntry->getEntryData()))
	{
		return false;
	}

	return true;
}

DBEntry*							DBFormat::getEntryByNameExactCase(string strEntryName)
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