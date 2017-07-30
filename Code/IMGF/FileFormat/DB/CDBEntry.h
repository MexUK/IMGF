#ifndef CDBEntry_H
#define CDBEntry_H

#include "Type/Types.h"
#include <string>

class CDBEntry
{
public:
	void				unload(void) {}

	void				unserialize(void);
	void				serialize(void);

	void				setEntryName(std::string strEntryName) { m_strEntryName = strEntryName; }
	std::string			getEntryName(void) { return m_strEntryName; }

	void				setEntrySize(uint32 uiEntrySize) { m_uiEntrySize = uiEntrySize; }
	uint32				getEntrySize(void) { return m_uiEntrySize; }

	void				setEntryDataCRC(uint32 uiEntryDataCRC) { m_uiEntryDataCRC = uiEntryDataCRC; }
	uint32				getEntryDataCRC(void) { return m_uiEntryDataCRC; }

	void				setEntryCreationDate(uint32 uiEntryCreationDate) { m_uiEntryCreationDate = uiEntryCreationDate; }
	uint32				getEntryCreationDate(void) { return m_uiEntryCreationDate; }

	void				setHasIssue(bool bHasIssue) { m_bHasIssue = bHasIssue; }
	bool				doesHaveIssue(void) { return m_bHasIssue; }

private:
	std::string			m_strEntryName;
	uint32				m_uiEntrySize;
	uint32				m_uiEntryDataCRC;
	uint32				m_uiEntryCreationDate;
	bool				m_bHasIssue		: 1;
};

#endif