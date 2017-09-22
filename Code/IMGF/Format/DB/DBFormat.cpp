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

// serialization
void								DBFormat::_unserialize(void)
{
	unload();

	// DB file header
	m_uiDBVersion = m_reader.readUint32();
	uint32 uiEntryCount = m_reader.readUint32();

	// copy RG structs into wrapper structs - so that we can use std::string for strings in our structs rather than char arrays
	vector<DBEntry*>& rvecDBEntries = getEntries();
	rvecDBEntries.resize(uiEntryCount);
	DBEntry *pDBEntries = new DBEntry[uiEntryCount];

	// DB file entries
	for (uint32 i = 0; i < uiEntryCount; i++)
	{
		DBEntry *pDBEntry = pDBEntries++;
		rvecDBEntries[i] = pDBEntry;
		pDBEntry->m_pFormat = this;
		pDBEntry->unserialize();
	}
}

void								DBFormat::_serialize(void)
{
	// DB file header
	m_writer.writeUint32(getDBVersion());
	m_writer.writeUint32(getEntryCount());

	// DB file entries
	for (DBEntry *pDBEntry : getEntries())
	{
		pDBEntry->serialize();
	}
}

// fetch entry
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

// check entry existence
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