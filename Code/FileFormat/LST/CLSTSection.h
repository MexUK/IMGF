#ifndef CLSTSection_H
#define CLSTSection_H

#include "Type/Types.h"
#include "Pool/CVectorPool.h"
#include "CLSTEntry.h"
#include <string>
#include <vector>

class CLSTSection : public mcore::CVectorPool<CLSTEntry*>
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

#endif