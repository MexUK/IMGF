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

	void											initStyles(void);
	void											initReversedKeywords(void);

	bool											doesHaveStyleComponent(uint32 uiStyleComponent);
	bool											doesHaveStyleFragment(uint32 uiStyleComponent, uint32 uiStyleFragment);
	bool											doesHaveStyleProperty(uint32 uiStyleComponent, uint32 uiStyleProperty);

	bool											getStylePropertyAndValueFromMarkupStyleValues(std::vector<std::string>& vecMarkupStyleValues, uint32 uiTokenIndex, uint32 uiStyleComponent, uint32& uiStyleProperty, uint32& uiStyleFragment, void*& pStyleValue, uint32& uiTokenCountRead);

	template <typename T>
	T												getStyle(uint32 uiStyleComponent, uint32 uiStyleProperty);
	template <typename T>
	T												getStyleWithFragment(uint32 uiStyleComponent, uint32 uiStyleProperty, uint32 uiStyleFragment);
	template <typename T>
	T												getStyleFast(uint32 uiStyleComponent, uint32 uiStyleProperty);

	/*
	inline uint32									getControlFromFlags(uint32 uiStyleFlags);
	inline uint32									getControlComponentFromFlags(uint32 uiStyleFlags);
	inline uint32									getStyleStatusFromFlags(uint32 uiStyleFlags);
	inline uint32									getStyleFragmentFromFlags(uint32 uiStyleFlags);
	*/

	bool											doesHaveLeftLine(void);
	bool											doesHaveRightLine(void);
	bool											doesHaveTopLine(void);
	bool											doesHaveBottomLine(void);

public:
	uint32											m_uiRenderingItemType; // window, layer, shape, or control
	uint32											m_uiRenderingItemSubType; // type of shape, type of control, etc
	uint32											m_uiRenderingControlComponent; // main, headerRow, headerCell, tab, etc
	uint32											m_uiRenderingStyleStatus; // default, hover, etc
	uint32											m_uiRenderingStyleFragment; // all, left, right, etc
	std::string										m_strRenderingStyleGroup; // blank string, or string

	//CGUIStyles*										m_pDefaultControlStyles;

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
T													CStyleManager::getStyle(uint32 uiStyleComponent, uint32 uiStyleProperty)
{
	if (m_umapCustomStyleGroups.find(m_strRenderingStyleGroup) != m_umapCustomStyleGroups.end())
	{
		if (m_umapCustomStyleGroups[m_strRenderingStyleGroup].find(m_uiRenderingStyleStatus) != m_umapCustomStyleGroups[m_strRenderingStyleGroup].end())
		{
			if (m_umapCustomStyleGroups[m_strRenderingStyleGroup][m_uiRenderingStyleStatus].find(m_uiRenderingControlComponent) != m_umapCustomStyleGroups[m_strRenderingStyleGroup][m_uiRenderingStyleStatus].end())
			{
				if (m_umapCustomStyleGroups[m_strRenderingStyleGroup][m_uiRenderingStyleStatus][m_uiRenderingControlComponent].find(uiStyleComponent) != m_umapCustomStyleGroups[m_strRenderingStyleGroup][m_uiRenderingStyleStatus][m_uiRenderingControlComponent].end())
				{
					if (m_umapCustomStyleGroups[m_strRenderingStyleGroup][m_uiRenderingStyleStatus][m_uiRenderingControlComponent][uiStyleComponent].find(m_uiRenderingStyleFragment) != m_umapCustomStyleGroups[m_strRenderingStyleGroup][m_uiRenderingStyleStatus][m_uiRenderingControlComponent][uiStyleComponent].end())
					{
						if (m_umapCustomStyleGroups[m_strRenderingStyleGroup][m_uiRenderingStyleStatus][m_uiRenderingControlComponent][uiStyleComponent][m_uiRenderingStyleFragment].find(uiStyleProperty) != m_umapCustomStyleGroups[m_strRenderingStyleGroup][m_uiRenderingStyleStatus][m_uiRenderingControlComponent][uiStyleComponent][m_uiRenderingStyleFragment].end())
						{
							return *(T*)m_umapCustomStyleGroups[m_strRenderingStyleGroup][m_uiRenderingStyleStatus][m_uiRenderingControlComponent][uiStyleComponent][m_uiRenderingStyleFragment][uiStyleProperty];
						}
					}
				}
			}
		}
	}

	return T();
}

template <typename T>
T													CStyleManager::getStyleWithFragment(uint32 uiStyleComponent, uint32 uiStyleProperty, uint32 uiStyleFragment)
{
	if (m_umapCustomStyleGroups.find(m_strRenderingStyleGroup) != m_umapCustomStyleGroups.end())
	{
		if (m_umapCustomStyleGroups[m_strRenderingStyleGroup].find(m_uiRenderingStyleStatus) != m_umapCustomStyleGroups[m_strRenderingStyleGroup].end())
		{
			if (m_umapCustomStyleGroups[m_strRenderingStyleGroup][m_uiRenderingStyleStatus].find(m_uiRenderingControlComponent) != m_umapCustomStyleGroups[m_strRenderingStyleGroup][m_uiRenderingStyleStatus].end())
			{
				if (m_umapCustomStyleGroups[m_strRenderingStyleGroup][m_uiRenderingStyleStatus][m_uiRenderingControlComponent].find(uiStyleComponent) != m_umapCustomStyleGroups[m_strRenderingStyleGroup][m_uiRenderingStyleStatus][m_uiRenderingControlComponent].end())
				{
					if (m_umapCustomStyleGroups[m_strRenderingStyleGroup][m_uiRenderingStyleStatus][m_uiRenderingControlComponent][uiStyleComponent].find(uiStyleFragment) != m_umapCustomStyleGroups[m_strRenderingStyleGroup][m_uiRenderingStyleStatus][m_uiRenderingControlComponent][uiStyleComponent].end())
					{
						if (m_umapCustomStyleGroups[m_strRenderingStyleGroup][m_uiRenderingStyleStatus][m_uiRenderingControlComponent][uiStyleComponent][uiStyleFragment].find(uiStyleProperty) != m_umapCustomStyleGroups[m_strRenderingStyleGroup][m_uiRenderingStyleStatus][m_uiRenderingControlComponent][uiStyleComponent][uiStyleFragment].end())
						{
							return *(T*)m_umapCustomStyleGroups[m_strRenderingStyleGroup][m_uiRenderingStyleStatus][m_uiRenderingControlComponent][uiStyleComponent][uiStyleFragment][uiStyleProperty];
						}
					}
				}
			}
		}
	}

	return T();
}

template <typename T>
T													CStyleManager::getStyleFast(uint32 uiStyleComponent, uint32 uiStyleProperty)
{
	return *(T*)m_umapCustomStyleGroups[m_strRenderingStyleGroup][m_uiRenderingStyleStatus][m_uiRenderingControlComponent][uiStyleComponent][m_uiRenderingStyleFragment][uiStyleProperty];
}