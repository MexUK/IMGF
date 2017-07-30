#ifndef CSocketUtility_H
#define CSocketUtility_H

#include "Type/Types.h"
#include <string>

struct CURLComponents
{
	std::string				m_strProtocol;
	std::string				m_strDomains;
	uint16					m_usPort;
	std::string				m_strPath;
	std::string				m_strQuery;
	std::string				m_strHash;
};

class CSocketUtility
{
public:
	static CURLComponents	getURLComponents(std::string strURL);
};

#endif