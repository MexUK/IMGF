#ifndef CPlatform_H
#define CPlatform_H

#include "mcore.h"
#include "ePlatform.h"
#include <string>

class mcore::CPlatform
{
public:
	void					unload(void) {}

	void					setPlatformId(mcore::ePlatform ePlatformValue) { m_ePlatformId = ePlatformValue; }
	mcore::ePlatform				getPlatformId(void) { return m_ePlatformId; }

	void					setName(std::string strName) { m_strName = strName; }
	std::string				getName(void) { return m_strName; }

private:
	mcore::ePlatform				m_ePlatformId;
	std::string				m_strName;
};

#endif