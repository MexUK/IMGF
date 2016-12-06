#ifndef CSortPriority_H
#define CSortPriority_H

#include "eSortType.h"
#include <string>
#include <vector>

class CSortPriority
{
public:
	/*
	// todo
	CSortPriority(eSortPriorityType eType) :
		m_bEnabled(false),
		m_eType(eType)
	{};
	*/
	CSortPriority(void) :
		m_bEnabled(false)
	{};

	void						unload(void) {}

	void						setEnabled(bool bEnabled) { m_bEnabled = bEnabled; }
	bool						isEnabled(void) { return m_bEnabled; }

	void						setType(CSortType* pType) { m_pType = pType; }
	CSortType*					getType(void) { return m_pType; }

	void						setStrData(std::string strData) { m_strData = strData; }
	std::string					getStrData(void) { return m_strData; }

	void						setData(std::vector<std::string> vecData) { m_vecData = vecData; }
	std::vector<std::string>&	getData(void) { return m_vecData; }

private:
	bool						m_bEnabled;
	CSortType*					m_pType;
	std::string					m_strData;
	std::vector<std::string>	m_vecData;
};

#endif