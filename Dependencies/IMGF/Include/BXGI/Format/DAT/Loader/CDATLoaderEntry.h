#pragma once

#include "nsbxgi.h"
#include "EDATLoaderEntryType.h"
#include <string>
#include <deque>

class bxgi::CDATLoaderEntry
{
public:
	void						unload(void) {}

	void						setEntryType(EDATLoaderEntryType eEntryType) { m_eEntryType = eEntryType; }
	EDATLoaderEntryType			getEntryType(void) { return m_eEntryType; }

	void						setEntryValues(std::deque<std::string>& deqValues) { m_deqValues = deqValues; }
	std::deque<std::string>&	getEntryValues(void) { return m_deqValues; }

private:
	EDATLoaderEntryType			m_eEntryType;
	std::deque<std::string>		m_deqValues;
};