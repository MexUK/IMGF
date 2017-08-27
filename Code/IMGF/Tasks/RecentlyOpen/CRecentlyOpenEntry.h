#pragma once

#include "nsimgf.h"
#include <string>

class imgf::CRecentlyOpenEntry
{
public:
	void							unload(void) {} 
	
	std::string						serialize(void) { return m_strPath; }
	
	void							setPath(std::string strPath) { m_strPath = strPath; }
	std::string						getPath(void) { return m_strPath; }
	
public:
	std::string						m_strPath;
};