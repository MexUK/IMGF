#pragma once

#include "nsbxcf.h"

struct bxcf::URLComponents
{
	std::string				m_strProtocol;
	std::string				m_strDomains;
	uint16					m_usPort;
	std::string				m_strPath;
	std::string				m_strQuery;
	std::string				m_strHash;
};