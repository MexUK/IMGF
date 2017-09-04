#pragma once

#include "nsbxcf.h"
#include "Format/Web/URL/URLComponents.h"
#include <string>
#include <vector>

class bxcf::URL
{
public:
	URL(void);
	
	void						loadFromURL(std::string strURL);
	std::vector<std::string>	getHTTPHeaders(void);
	
	void						setProtocol(std::string strProtocol) { m_strProtocol = strProtocol; }
	std::string					getProtocol(void) { return m_strProtocol; }
	
	void						setDomains(std::string strDomains) { m_strDomains = strDomains; }
	std::string					getDomains(void) { return m_strDomains; }
	
	void						setPort(uint16 usPort) { m_usPort = usPort; }
	uint16						getPort(void) { return m_usPort; }
	
	void						setPath(std::string strPath) { m_strPath = strPath; }
	std::string					getPath(void) { return m_strPath; }
	
	void						setQuery(std::string strQuery) { m_strQuery = strQuery; }
	std::string					getQuery(void) { return m_strQuery; }
	
	void						setFragment(std::string strFragment) { m_strFragment = strFragment; }
	std::string					getFragment(void) { return m_strFragment; }
	
	static URLComponents		getURLComponents(std::string strURL);

private:
	std::string					m_strProtocol;
	std::string					m_strDomains;
	uint16						m_usPort;
	std::string					m_strPath;
	std::string					m_strQuery;
	std::string					m_strFragment;
};