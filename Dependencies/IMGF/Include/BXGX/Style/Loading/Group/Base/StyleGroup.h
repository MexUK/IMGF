#pragma once

#include "nsbxgx.h"
#include "Type/Types.h"
#include "Style/Parts/EControlComponent.h"
#include "Style/Parts/EStyleStatus.h"
#include "Style/Parts/EStyleComponent.h"
#include "Style/Parts/EStyleFragment.h"
#include "Style/Parts/EStyleProperty.h"
#include <string>
#include <vector>
#include <unordered_map>

class bxgx::StyleGroup
{
public:
	StyleGroup(void);

	std::vector<StyleGroup*>							getAllLinkedStyleGroups(void);
	std::vector<StyleGroup*>							getAllLinkedStyleGroups2(StyleGroup *pStyleGroup);

public:
	bool												m_bIsCustomStyleGroup;
	std::string											m_strName;
	bxgx::controls::components::EControlComponent		m_uiControlComponent;
	bxgx::styles::statuses::EStyleStatus				m_uiStyleStatus;
	std::vector<StyleGroup*>							m_vecLinkedStyleGroups;

	std::unordered_map<bxgx::styles::components::EStyleComponent,
		std::unordered_map<bxgx::styles::fragments::EStyleFragment,
			std::unordered_map<bxgx::styles::properties::EStyleProperty, void*>
		>
	>													m_umapStyles;
};