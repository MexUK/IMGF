#pragma once

#include "nsbxcf.h"
#include "EPlatform.h"
#include <string>

class bxcf::Platform
{
public:
	void					unload(void) {}

	void					setPlatformId(bxcf::EPlatform EPlatformValue) { m_EPlatformId = EPlatformValue; }
	bxcf::EPlatform			getPlatformId(void) { return m_EPlatformId; }

	void					setName(std::string& strName) { m_strName = strName; }
	std::string&			getName(void) { return m_strName; }

private:
	bxcf::EPlatform			m_EPlatformId;
	std::string				m_strName;
};