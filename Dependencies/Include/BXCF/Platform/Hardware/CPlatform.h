#ifndef CPlatform_H
#define CPlatform_H

#include "bxcf.h"
#include "ePlatform.h"
#include <string>

class bxcf::CPlatform
{
public:
	void					unload(void) {}

	void					setPlatformId(bxcf::ePlatform ePlatformValue) { m_ePlatformId = ePlatformValue; }
	bxcf::ePlatform				getPlatformId(void) { return m_ePlatformId; }

	void					setName(std::string strName) { m_strName = strName; }
	std::string				getName(void) { return m_strName; }

private:
	bxcf::ePlatform				m_ePlatformId;
	std::string				m_strName;
};

#endif