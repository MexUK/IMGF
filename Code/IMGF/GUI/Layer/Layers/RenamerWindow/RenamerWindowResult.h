#pragma once

#include "nsimgf.h"
#include <string>

struct imgf::RenamerWindowResult
{
	uint32				m_uiEntriesType;
	bool				m_bMatchingEntriesInIDE;
	bool				m_bMatchingEntriesInIPL;
	bool				m_bMatchingEntriesInCOL;
	std::string			m_strMatchingEntriesInIDEFolderPath;
	std::string			m_strMatchingEntriesInIPLFolderPath;
	std::string			m_strMatchingEntriesInCOLFolderPath;
	std::string			m_strCharAddingFront;
	std::string			m_strCharAddingEnd;
	std::string			m_strCharAddingAtPosition;
	uint32				m_uiCharAddingAtPositionIndex;
	uint32				m_uiCharRemovingFront;
	uint32				m_uiCharRemovingEnd;
	uint32				m_uiCharRemovingAtPosition;
	uint32				m_uiCharRemovingAtPosition2;
	uint32				m_uiCharCase;
	uint32				m_uiCharReplaceType;
	uint32				m_uiOnlyReplaceIfLengthExceeds;
	bool				m_bUpdateLODNames;
};