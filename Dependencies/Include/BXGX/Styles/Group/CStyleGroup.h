#pragma once

#include "Type/Types.h"
#include <string>
#include <unordered_map>
#include <vector>

class CStyleGroup
{
public:
	CStyleGroup(void);

public:
	bool				m_bIsCustomStyleGroup;
	std::string			m_strName;
	uint32				m_uiControlComponent;
	CStyleGroup*		m_pLinkedStyleGroup;

	std::unordered_map<uint32,
		std::unordered_map<uint32,
			std::unordered_map<uint32,
				std::vector<void*>
			>
		>
	>					m_umapStyles;
};