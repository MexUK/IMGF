#pragma once

#include "Type/Types.h"
#include "Styles/StyleEnums.h"
#include <string>
#include <vector>
#include <unordered_map>

class CStyleGroup
{
public:
	CStyleGroup(void);

	std::vector<CStyleGroup*>							getAllLinkedStyleGroups(void);
	std::vector<CStyleGroup*>							getAllLinkedStyleGroups2(CStyleGroup *pStyleGroup);

public:
	bool												m_bIsCustomStyleGroup;
	std::string											m_strName;
	bxgx::controls::components::EControlComponent		m_uiControlComponent;
	bxgx::styles::statuses::EStyleStatus				m_uiStyleStatus;
	std::vector<CStyleGroup*>							m_vecLinkedStyleGroups;

	std::unordered_map<bxgx::styles::components::EStyleComponent,
		std::unordered_map<bxgx::styles::fragments::EStyleFragment,
			std::unordered_map<bxgx::styles::properties::EStyleProperty, void*>
		>
	>													m_umapStyles;
};