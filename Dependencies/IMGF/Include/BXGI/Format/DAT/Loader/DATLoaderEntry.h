#pragma once

#include "nsbxgi.h"
#include "EDATLoaderEntryType.h"
#include <string>
#include <deque>

class bxgi::DATLoaderEntry
{
public:
	void						unload(void) {}

	void						setEntryType(EDATLoaderEntryType eEntryType) { m_uiEntryType = eEntryType; }
	EDATLoaderEntryType			getEntryType(void) { return m_uiEntryType; }

	void						setEntryValues(std::deque<std::string>& deqValues) { m_deqValues = deqValues; }
	std::deque<std::string>&	getEntryValues(void) { return m_deqValues; }

private:
	EDATLoaderEntryType			m_uiEntryType;
	std::deque<std::string>		m_deqValues;
};