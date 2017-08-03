#ifndef CRecentlyOpenEntry_H
#define CRecentlyOpenEntry_H

#include <string>

class CRecentlyOpenEntry
{
public:
	void							unload(void) {} 
	
	std::string						serialize(void) { return m_strPath; }
	
	void							setPath(std::string strPath);
	std::string						getPath(void) { return m_strPath; }
	
public:
	std::string						m_strPath;
};

#endif