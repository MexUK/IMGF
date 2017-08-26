#pragma once

#include "Type/Types.h"
#include "Pool/CVectorPool.h"
#include "CLSTEntry.h"
#include <string>

class CLSTSection : public bxcf::CVectorPool<CLSTEntry*>
{
public:
	void								unload(void);

	CLSTEntry*							getEntryByName(std::string strName);
	bool								doesEntryExistByName(std::string strName);

	void								setName(std::string& strName) { m_strName = strName; }
	std::string&						getName(void) { return m_strName; }

private:
	std::string							m_strName;
};