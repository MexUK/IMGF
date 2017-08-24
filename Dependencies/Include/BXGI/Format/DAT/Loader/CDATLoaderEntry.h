#ifndef CDATLoaderEntry_H
#define CDATLoaderEntry_H

#include "bxgi.h"
#include "eDATLoaderEntryType.h"
#include <string>
#include <deque>

class bxgi::CDATLoaderEntry
{
public:
	void						unload(void) {}

	void						setEntryType(eDATLoaderEntryType eEntryType) { m_eEntryType = eEntryType; }
	eDATLoaderEntryType			getEntryType(void) { return m_eEntryType; }

	void						setEntryValues(std::deque<std::string>& deqValues) { m_deqValues = deqValues; }
	std::deque<std::string>&	getEntryValues(void) { return m_deqValues; }

private:
	eDATLoaderEntryType			m_eEntryType;
	std::deque<std::string>		m_deqValues;
};

#endif