#pragma once

#include "TYpe/Types.h"
#include "Object/CSingleton.h"
#include <string>
#include <unordered_map>

class CGUIStyles;

class CStyleManager : public bxcf::CSingleton<CStyleManager>
{
public:
	CStyleManager(void);

	void											init(void);

	void											initDefaultStyles(void);
	void											initStyles(void);
	void											initReversedKeywords(void);

	bool											doesHaveStyleComponent(uint32 uiStyleComponent, uint32 uiStyleFlags, std::string& strStyleGroup);
	//bool											doesHaveStyleFragment(uint32 uiStyleComponent, uint32 uiStyleFragment, uint32 uiStyleFlags, std::string& strStyleGroup);
	bool											doesHaveStyleProperty(uint32 uiStyleComponent, uint32 uiStyleProperty, uint32 uiStyleFlags, std::string& strStyleGroup);

	void*											getStyleValueFromMarkupStyleValue(std::string& strMarkupValue);	// Example: "false" -> bool false
	//void											getStylePropertyAndValueFromMarkupStyleValue(std::string& strMarkupStyleValue, uint32& uiStyleProperty, void* pStyleValue, bool& bIsPartialValueToken);
	void											getStylePropertyAndValueFromMarkupStyleValues(std::vector<std::string>& vecMarkupStyleValues, uint32 uiStyleComponent, uint32& uiStyleProperty, void* pStyleValue, uint32& uiTokenCountRead);

	template <typename T>
	T												getStyleIfExists(uint32 uiStyleComponent, uint32 uiStyleProperty, uint32 uiStyleFlags, std::string& strStyleGroup);
	template <typename T>
	T												getStyle(uint32 uiStyleComponent, uint32 uiStyleProperty, uint32 uiStyleFlags, std::string& strStyleGroup);

	inline uint32									getControlFromFlags(uint32 uiStyleFlags);
	inline uint32									getControlComponentFromFlags(uint32 uiStyleFlags);
	inline uint32									getStyleStatusFromFlags(uint32 uiStyleFlags);
	inline uint32									getStyleFragmentFromFlags(uint32 uiStyleFlags);

public:
	CGUIStyles*										m_pDefaultControlStyles;

	std::unordered_map<std::string, uint32>			m_umapControls;				// Example: ["grid"] = bxgx::controls::GRID
	std::unordered_map<std::string, uint32>			m_umapControlComponents;	// Example: ["headers"] = bxgx::controls::components::HEADERS
	std::unordered_map<std::string, uint32>			m_umapStyleComponents;		// Example: ["text"] = bxgx::styles::components::TEXT
	std::unordered_map<std::string, uint32>			m_umapStyleStatuses;		// Example: ["hover"] = bxgx::styles::statuses::HOVER
	std::unordered_map<std::string, uint32>			m_umapStyleProperties;		// Example: ["colour"] = bxgx::styles::components::COLOUR
	std::unordered_map<std::string, uint32>			m_umapStyleFragments;		// Example: ["left"] = bxgx::styles::fragments::LEFT

	std::unordered_map<std::string, std::pair<uint32, void*>>		m_umapStyleValues;			// Example: ["false"] = pair(bxgx::styles::properties::STATUS, bool* false)

	std::unordered_map<std::string,
		std::unordered_map<uint32,
			std::unordered_map<uint32,
				std::unordered_map<uint32,
					std::unordered_map<uint32,
						std::unordered_map<uint32, void*>
					>
				>
			>
		>
	>												m_umapCustomStyleGroups,
													m_umapControlStyleGroups,
													m_umapDefaultCustomStyleGroups,
													m_umapDefaultControlStyleGroups;
};

template <typename T>
T													CStyleManager::getStyleIfExists(uint32 uiStyleComponent, uint32 uiStyleProperty, uint32 uiStyleFlags, std::string& strStyleGroup)
{
	uint32
		uiControlComponent = getControlComponentFromFlags(uiStyleFlags),
		uiControl = getControlFromFlags(uiStyleFlags),
		uiStyleStatus = getStyleStatusFromFlags(uiStyleFlags),
		uiStyleFragment = getStyleFragmentFromFlags(uiStyleFlags);

	if (strStyleGroup.size() != 0)
	{
		if (m_umapCustomStyleGroups.find(strStyleGroup) != m_umapCustomStyleGroups.end())
		{
			if (m_umapCustomStyleGroups[strStyleGroup].find(uiStyleStatus) != m_umapCustomStyleGroups[strStyleGroup].end())
			{
				if (m_umapCustomStyleGroups[strStyleGroup][uiStyleStatus].find(uiControlComponent) != m_umapCustomStyleGroups[strStyleGroup][uiStyleStatus].end())
				{
					if (m_umapCustomStyleGroups[strStyleGroup][uiStyleStatus][uiControlComponent].find(uiStyleComponent) != m_umapCustomStyleGroups[strStyleGroup][uiStyleStatus][uiControlComponent].end())
					{
						if (m_umapCustomStyleGroups[strStyleGroup][uiStyleStatus][uiControlComponent][uiStyleComponent].find(uiStyleFragment) != m_umapCustomStyleGroups[strStyleGroup][uiStyleStatus][uiControlComponent][uiStyleComponent].end())
						{
							if (m_umapCustomStyleGroups[strStyleGroup][uiStyleStatus][uiControlComponent][uiStyleComponent][uiStyleFragment].find(uiStyleProperty) != m_umapCustomStyleGroups[strStyleGroup][uiStyleStatus][uiControlComponent][uiStyleComponent][uiStyleFragment].end())
							{
								return *(T*)m_umapCustomStyleGroups[strStyleGroup][uiStyleStatus][uiControlComponent][uiStyleComponent][uiStyleFragment][uiStyleProperty];
							}
						}
					}
				}
			}
		}
	}

	return *(T*)0;
}

template <typename T>
T													CStyleManager::getStyle(uint32 uiStyleComponent, uint32 uiStyleProperty, uint32 uiStyleFlags, std::string& strStyleGroup)
{
	return *(T*)m_umapCustomStyleGroups[strStyleGroup][getStyleStatusFromFlags(uiStyleFlags)][getControlComponentFromFlags(uiStyleFlags)][uiStyleComponent][getStyleFragmentFromFlags(uiStyleFlags)][uiStyleProperty];
}