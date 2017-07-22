#ifndef CPlatform_H
#define CPlatform_H

#include "BXA.h"
#include "ePlatform.h"
#include <string>

class bxa::CPlatform
{
public:
	void					unload(void) {}

	void					setPlatformId(bxa::ePlatform ePlatformValue) { m_ePlatformId = ePlatformValue; }
	bxa::ePlatform				getPlatformId(void) { return m_ePlatformId; }

	void					setName(std::string strName) { m_strName = strName; }
	std::string				getName(void) { return m_strName; }

private:
	bxa::ePlatform				m_ePlatformId;
	std::string				m_strName;
};

#endif