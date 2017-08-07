#pragma once

#include "Type/Types.h"
#include <string>
#include <vector>
#include <unordered_map>

class CStyleGroup
{
public:
	CStyleGroup(void);

	std::vector<CStyleGroup*>		getAllLinkedStyleGroups(void);
	std::vector<CStyleGroup*>		getAllLinkedStyleGroups2(CStyleGroup *pStyleGroup);

public:
	bool							m_bIsCustomStyleGroup;
	std::string						m_strName;
	uint32							m_uiControlComponent;
	uint32							m_uiStyleStatus;
	std::vector<CStyleGroup*>		m_vecLinkedStyleGroups;

	std::unordered_map<uint32,
		std::unordered_map<uint32,
			std::unordered_map<uint32, void*>
		>
	>								m_umapStyles;
};