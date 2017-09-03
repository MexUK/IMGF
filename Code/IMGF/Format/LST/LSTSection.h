#pragma once

#include "nsimgf.h"
#include "Type/Types.h"
#include "Pool/VectorPool.h"
#include "LSTEntry.h"
#include <string>

class imgf::LSTSection : public bxcf::VectorPool<LSTEntry*>
{
public:
	void								unload(void);

	LSTEntry*							getEntryByName(std::string strName);
	bool								doesEntryExistByName(std::string strName);

	void								setName(std::string& strName) { m_strName = strName; }
	std::string&						getName(void) { return m_strName; }

private:
	std::string							m_strName;
};