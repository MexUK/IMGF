#pragma once

#include "nsimgf.h"
#include "ESortType.h"
#include <string>
#include <vector>

class imgf::SortPriority
{
public:
	SortPriority(void);

	void						unload(void) {}

	void						setEnabled(bool bEnabled) { m_bEnabled = bEnabled; }
	bool						isEnabled(void) { return m_bEnabled; }

	void						setType(SortType* pType) { m_pType = pType; }
	SortType*					getType(void) { return m_pType; }

	void						setStrData(std::string strData) { m_strData = strData; }
	std::string					getStrData(void) { return m_strData; }

	void						setData(std::vector<std::string> vecData) { m_vecData = vecData; }
	std::vector<std::string>&	getData(void) { return m_vecData; }

private:
	bool						m_bEnabled;
	SortType*					m_pType;
	std::string					m_strData;
	std::vector<std::string>	m_vecData;
};