#pragma once

#include "Type/Types.h"
#include "Object/CSingleton.h"
#include "Type/Colour/CColour.h"
#include "Renderable/CRenderable.h"
#include "Styles/StyleEnums.h"
#include "Control/eGUIControl.h"
#include <string>
#include <vector>
#include <unordered_map>
#include <map>
#include <sparsehash/dense_hash_map___Int.h>
#include <sparsehash/dense_hash_map___Pointer.h>

class CGUIStyles;

class CStyleManager_MapUtility_Uint32
{
public:
	inline size_t operator()(const uint32 &uiValue) const { return uiValue; }
	inline size_t operator()(const bxgx::styles::statuses::EStyleStatus &uiValue) const { return uiValue; }
	inline size_t operator()(const bxgx::controls::components::EControlComponent &uiValue) const { return uiValue; }
	inline size_t operator()(const bxgx::styles::components::EStyleComponent &uiValue) const { return uiValue; }
	inline size_t operator()(const bxgx::styles::fragments::EStyleFragment &uiValue) const { return uiValue; }
	inline size_t operator()(const bxgx::styles::properties::EStyleProperty &uiValue) const { return uiValue; }

	inline constexpr bool operator()(const uint32 &lhs, const uint32 &rhs) const { return lhs == rhs; }
	inline constexpr bool operator()(const bxgx::styles::statuses::EStyleStatus &lhs, const bxgx::styles::statuses::EStyleStatus &rhs) const { return lhs == rhs; }
	inline constexpr bool operator()(const bxgx::controls::components::EControlComponent &lhs, const bxgx::controls::components::EControlComponent &rhs) const { return lhs == rhs; }
	inline constexpr bool operator()(const bxgx::styles::components::EStyleComponent &lhs, const bxgx::styles::components::EStyleComponent &rhs) const { return lhs == rhs; }
	inline constexpr bool operator()(const bxgx::styles::fragments::EStyleFragment &lhs, const bxgx::styles::fragments::EStyleFragment &rhs) const { return lhs == rhs; }
	inline constexpr bool operator()(const bxgx::styles::properties::EStyleProperty &lhs, const bxgx::styles::properties::EStyleProperty &rhs) const { return lhs == rhs; }
};

class CStyleManager_MapUtility_CRenderablePointer
{
public:
	inline size_t operator()(const CRenderable *val) const // https://stackoverflow.com/questions/20953390/what-is-the-fastest-hash-function-for-pointers
	{
        static const size_t shift = (size_t)log2(1 + sizeof(CRenderable));
        return (size_t)(val) >> shift;
    }
	inline constexpr bool operator()(const CRenderable *lhs, const CRenderable *rhs) const
	{
		return ((uint32)lhs) == (uint32)rhs;
	}
};

typedef google::dense_hash_map___Int<uint32,
			google::dense_hash_map___Int<bxgx::styles::statuses::EStyleStatus,
				google::dense_hash_map___Int<bxgx::controls::components::EControlComponent,
					google::dense_hash_map___Int<bxgx::styles::components::EStyleComponent,
						google::dense_hash_map___Int<bxgx::styles::fragments::EStyleFragment,
							google::dense_hash_map___Int<bxgx::styles::properties::EStyleProperty, void*, CStyleManager_MapUtility_Uint32, CStyleManager_MapUtility_Uint32>,
						CStyleManager_MapUtility_Uint32, CStyleManager_MapUtility_Uint32>,
					CStyleManager_MapUtility_Uint32, CStyleManager_MapUtility_Uint32>,
				CStyleManager_MapUtility_Uint32, CStyleManager_MapUtility_Uint32>,
			CStyleManager_MapUtility_Uint32, CStyleManager_MapUtility_Uint32>,
		CStyleManager_MapUtility_Uint32, CStyleManager_MapUtility_Uint32> container6d_1;

typedef google::dense_hash_map___Pointer<CRenderable*,
			google::dense_hash_map___Int<bxgx::styles::statuses::EStyleStatus,
				google::dense_hash_map___Int<bxgx::controls::components::EControlComponent,
					google::dense_hash_map___Int<bxgx::styles::components::EStyleComponent,
						google::dense_hash_map___Int<bxgx::styles::fragments::EStyleFragment,
							google::dense_hash_map___Int<bxgx::styles::properties::EStyleProperty, void*, CStyleManager_MapUtility_Uint32, CStyleManager_MapUtility_Uint32>,
						CStyleManager_MapUtility_Uint32, CStyleManager_MapUtility_Uint32>,
					CStyleManager_MapUtility_Uint32, CStyleManager_MapUtility_Uint32>,
				CStyleManager_MapUtility_Uint32, CStyleManager_MapUtility_Uint32>,
			CStyleManager_MapUtility_Uint32, CStyleManager_MapUtility_Uint32>,
		CStyleManager_MapUtility_CRenderablePointer, CStyleManager_MapUtility_CRenderablePointer> container6d_2;

class CStyleManager : public bxcf::CSingleton<CStyleManager>
{
public:
	CStyleManager(void);

	void											init(void);

	void											initStyles(void);
	void											initReversedKeywords(void);

	bool											doesHaveStyleComponent(bxgx::styles::components::EStyleComponent uiStyleComponent);
	bool											doesHaveStyleFragment(bxgx::styles::components::EStyleComponent uiStyleComponent, bxgx::styles::fragments::EStyleFragment uiStyleFragment);
	bool											doesHaveStyleProperty(bxgx::styles::components::EStyleComponent uiStyleComponent, bxgx::styles::properties::EStyleProperty uiStyleProperty);
	bool											doesStyleExist(bxgx::styles::components::EStyleComponent uiStyleComponent, bxgx::styles::properties::EStyleProperty uiStyleProperty, bxgx::styles::fragments::EStyleFragment uiStyleFragment);

	uint32											getCustomStyleGroupId(std::string& strStyleGroupName);

	uint32											getGroupStylesKey(uint32 uiStyleGroupId, bxgx::styles::statuses::EStyleStatus uiStyleStatus, bxgx::controls::components::EControlComponent uiControlComponent, bxgx::styles::components::EStyleComponent uiStyleComponent, bxgx::styles::fragments::EStyleFragment uiStyleFragment, bxgx::styles::properties::EStyleProperty uiStyleProperty);
	uint32											getStylesKey(bxgx::styles::statuses::EStyleStatus uiStyleStatus, bxgx::controls::components::EControlComponent uiControlComponent, bxgx::styles::components::EStyleComponent uiStyleComponent, bxgx::styles::fragments::EStyleFragment uiStyleFragment, bxgx::styles::properties::EStyleProperty uiStyleProperty);

	bool											getStylePropertyAndValueFromMarkupStyleValues(std::vector<std::string>& vecMarkupStyleValues, uint32 uiTokenIndex, bxgx::styles::components::EStyleComponent uiStyleComponent, bxgx::styles::properties::EStyleProperty& uiStyleProperty, bxgx::styles::fragments::EStyleFragment& uiStyleFragment, void*& pStyleValue, uint32& uiTokenCountRead);

	template <typename T>
	T												getStyle(bxgx::styles::components::EStyleComponent uiStyleComponent, bxgx::styles::properties::EStyleProperty uiStyleProperty);
	template <typename T>
	T												getStyleWithFragment(bxgx::styles::components::EStyleComponent uiStyleComponent, bxgx::styles::properties::EStyleProperty uiStyleProperty, bxgx::styles::fragments::EStyleFragment uiStyleFragment);
	template <typename T>
	T												getStyleFast(std::string& strRenderingStyleGroup, bxgx::styles::components::EStyleComponent uiStyleComponent, bxgx::styles::properties::EStyleProperty uiStyleProperty);

	template <typename T>
	inline T*										getNativeStyle(bxgx::styles::components::EStyleComponent uiStyleComponent, bxgx::styles::properties::EStyleProperty uiStyleProperty);
	template <typename T>
	T*												getNativeStyle(CRenderable *pGUIEventUtilizer, bxgx::styles::components::EStyleComponent uiStyleComponent, bxgx::styles::properties::EStyleProperty uiStyleProperty);
	template <typename T>
	T*												getNativeStyleFast(bxgx::styles::components::EStyleComponent uiStyleComponent, bxgx::styles::properties::EStyleProperty uiStyleProperty);

	void											setItemStyle(CRenderable *pGUIEventUtilizer, bxgx::styles::components::EStyleComponent uiStyleComponent, bxgx::styles::properties::EStyleProperty uiStyleProperty, void *pStyleValue);
	void											setItemStyle(CRenderable *pGUIEventUtilizer, bxgx::styles::components::EStyleComponent uiStyleComponent, bxgx::styles::properties::EStyleProperty uiStyleProperty, bxgx::styles::fragments::EStyleFragment uiStyleFragment, void *pStyleValue);
	void											removeItemStyle(CRenderable *pGUIEventUtilizer, bxgx::styles::components::EStyleComponent uiStyleComponent, bxgx::styles::properties::EStyleProperty uiStyleProperty);
	void											removeItemStyle(CRenderable *pGUIEventUtilizer, bxgx::styles::components::EStyleComponent uiStyleComponent, bxgx::styles::properties::EStyleProperty uiStyleProperty, bxgx::styles::fragments::EStyleFragment uiStyleFragment);

	bool											doesHaveLeftLine(void);
	bool											doesHaveRightLine(void);
	bool											doesHaveTopLine(void);
	bool											doesHaveBottomLine(void);

	bxcf::CColour									getLineColour(void);

	uint32											getSpacingX(void);
	uint32											getSpacingY(void);

public:
	bxgx::item::ERenderable								m_uiRenderingItemType;			// window, layer, shape, or control
	uint32											m_uiRenderingItemSubType;		// type of shape, type of control, etc
	bxgx::controls::components::EControlComponent	m_uiRenderingControlComponent;	// main, headerRow, headerCell, tab, etc
	bxgx::styles::statuses::EStyleStatus			m_uiRenderingStyleStatus;		// default, hover, etc
	bxgx::styles::fragments::EStyleFragment			m_uiRenderingStyleFragment;		// all, left, right, etc
	CRenderable*								m_pRenderingEventUtilizer;
	std::vector<uint32>								m_vecRenderingStyleGroups;

	std::unordered_map<std::string, eGUIControl>										m_umapControls;				// Example: ["grid"] = bxgx::controls::GRID
	std::unordered_map<std::string, bxgx::controls::components::EControlComponent>		m_umapControlComponents;	// Example: ["headers"] = bxgx::controls::components::HEADERS
	std::unordered_map<std::string, bxgx::styles::components::EStyleComponent>			m_umapStyleComponents;		// Example: ["text"] = bxgx::styles::components::TEXT
	std::unordered_map<std::string, bxgx::styles::statuses::EStyleStatus>				m_umapStyleStatuses;		// Example: ["hover"] = bxgx::styles::statuses::HOVER
	std::unordered_map<std::string, bxgx::styles::properties::EStyleProperty>			m_umapStyleProperties;		// Example: ["colour"] = bxgx::styles::components::COLOUR
	std::unordered_map<std::string, bxgx::styles::fragments::EStyleFragment>			m_umapStyleFragments;		// Example: ["left"] = bxgx::styles::fragments::LEFT

	std::unordered_map<std::string, std::pair<bxgx::styles::properties::EStyleProperty, void*>>		m_umapStyleValues;	// Example: ["false"] = pair(bxgx::styles::properties::STATUS, bool* false)

	std::unordered_map<std::string, uint32>			m_umapCustomStyleGroupIds;

	container6d_1									m_umapCustomStyleGroups, m_umapControlStyleGroups, m_umapDefaultCustomStyleGroups, m_umapDefaultControlStyleGroups;
	container6d_2									m_umapItemsStyles;
};

template <typename T>
T													CStyleManager::getStyle(bxgx::styles::components::EStyleComponent uiStyleComponent, bxgx::styles::properties::EStyleProperty uiStyleProperty)
{
	T *pStyleValue = getNativeStyle<T>(m_pRenderingEventUtilizer, uiStyleComponent, uiStyleProperty);
	return pStyleValue != nullptr ? *(T*)pStyleValue : T();
}

template <typename T>
T*													CStyleManager::getNativeStyle(bxgx::styles::components::EStyleComponent uiStyleComponent, bxgx::styles::properties::EStyleProperty uiStyleProperty)
{
	return getNativeStyle<T>(m_pRenderingEventUtilizer, uiStyleComponent, uiStyleProperty);
}

template <typename T>
T*													CStyleManager::getNativeStyle(CRenderable *pGUIEventUtilizer, bxgx::styles::components::EStyleComponent uiStyleComponent, bxgx::styles::properties::EStyleProperty uiStyleProperty)
{
	if (m_umapItemsStyles.count(pGUIEventUtilizer))
	{
		auto &umap1 = m_umapItemsStyles[pGUIEventUtilizer];
		if (umap1.count(m_uiRenderingStyleStatus))
		{
			auto &umap2 = umap1[m_uiRenderingStyleStatus];
			if (umap2.count(m_uiRenderingControlComponent))
			{
				auto &umap3 = umap2[m_uiRenderingControlComponent];
				if (umap3.count(uiStyleComponent))
				{
					auto &umap4 = umap3[uiStyleComponent];
					if (umap4.count(m_uiRenderingStyleFragment))
					{
						auto &umap5 = umap4[m_uiRenderingStyleFragment];
						if (umap5.count(uiStyleProperty))
						{
							return (T*)umap5[uiStyleProperty];
						}
					}
				}
			}
		}
	}
	for (uint32 uiRenderingStyleGroup : m_vecRenderingStyleGroups)
	{
		if (m_umapCustomStyleGroups.count(uiRenderingStyleGroup))
		{
			auto &umap1 = m_umapCustomStyleGroups[uiRenderingStyleGroup];
			if (umap1.count(m_uiRenderingStyleStatus))
			{
				auto &umap2 = umap1[m_uiRenderingStyleStatus];
				if (umap2.count(m_uiRenderingControlComponent))
				{
					auto &umap3 = umap2[m_uiRenderingControlComponent];
					if (umap3.count(uiStyleComponent))
					{
						auto &umap4 = umap3[uiStyleComponent];
						if (umap4.count(m_uiRenderingStyleFragment))
						{
							auto &umap5 = umap4[m_uiRenderingStyleFragment];
							if (umap5.count(uiStyleProperty))
							{
								return (T*)umap5[uiStyleProperty];
							}
						}
					}
				}
			}
		}
	}
	return nullptr;
}

template <typename T>
T													CStyleManager::getStyleWithFragment(bxgx::styles::components::EStyleComponent uiStyleComponent, bxgx::styles::properties::EStyleProperty uiStyleProperty, bxgx::styles::fragments::EStyleFragment uiStyleFragment)
{
	if (m_umapItemsStyles.find(m_pRenderingEventUtilizer) != m_umapItemsStyles.end())
	{
		auto &umap1 = m_umapItemsStyles[m_pRenderingEventUtilizer];
		if (umap1.find(m_uiRenderingStyleStatus) != umap1.end())
		{
			auto &umap2 = umap1[m_uiRenderingStyleStatus];
			if (umap2.find(m_uiRenderingControlComponent) != umap2.end())
			{
				auto &umap3 = umap2[m_uiRenderingControlComponent];
				if (umap3.find(uiStyleComponent) != umap3.end())
				{
					auto &umap4 = umap3[uiStyleComponent];
					if (umap4.find(uiStyleFragment) != umap4.end())
					{
						auto &umap5 = umap4[uiStyleFragment];
						if (umap5.find(uiStyleProperty) != umap5.end())
						{
							return *(T*)umap5[uiStyleProperty];
						}
					}
				}
			}
		}
	}
	for (uint32 uiRenderingStyleGroup : m_vecRenderingStyleGroups)
	{
		if (m_umapCustomStyleGroups.find(uiRenderingStyleGroup) != m_umapCustomStyleGroups.end())
		{
			auto &umap1 = m_umapCustomStyleGroups[uiRenderingStyleGroup];
			if (umap1.find(m_uiRenderingStyleStatus) != umap1.end())
			{
				auto &umap2 = umap1[m_uiRenderingStyleStatus];
				if (umap2.find(m_uiRenderingControlComponent) != umap2.end())
				{
					auto &umap3 = umap2[m_uiRenderingControlComponent];
					if (umap3.find(uiStyleComponent) != umap3.end())
					{
						auto &umap4 = umap3[uiStyleComponent];
						if (umap4.find(uiStyleFragment) != umap4.end())
						{
							auto &umap5 = umap4[uiStyleFragment];
							if (umap5.find(uiStyleProperty) != umap5.end())
							{
								return *(T*)umap5[uiStyleProperty];
							}
						}
					}
				}
			}
		}
	}
	return T();
}

template <typename T>
T*													CStyleManager::getNativeStyleFast(bxgx::styles::components::EStyleComponent uiStyleComponent, bxgx::styles::properties::EStyleProperty uiStyleProperty)
{
	if (m_umapItemsStyles[m_pRenderingEventUtilizer][m_uiRenderingStyleStatus][m_uiRenderingControlComponent][uiStyleComponent][m_uiRenderingStyleFragment].count(uiStyleProperty))
	{
		return (T*)m_umapItemsStyles[m_pRenderingEventUtilizer][m_uiRenderingStyleStatus][m_uiRenderingControlComponent][uiStyleComponent][m_uiRenderingStyleFragment][uiStyleProperty];
	}
	for (uint32 uiRenderingStyleGroup : m_vecRenderingStyleGroups)
	{
		if (m_umapCustomStyleGroups[uiRenderingStyleGroup][m_uiRenderingStyleStatus][m_uiRenderingControlComponent][uiStyleComponent][m_uiRenderingStyleFragment].count(uiStyleProperty))
		{
			return (T*)m_umapCustomStyleGroups[uiRenderingStyleGroup][m_uiRenderingStyleStatus][m_uiRenderingControlComponent][uiStyleComponent][m_uiRenderingStyleFragment][uiStyleProperty];
		}
	}
	return nullptr;
}

template <typename T>
T													CStyleManager::getStyleFast(std::string& strRenderingStyleGroup, bxgx::styles::components::EStyleComponent uiStyleComponent, bxgx::styles::properties::EStyleProperty uiStyleProperty)
{
	if (m_umapItemsStyles[m_pRenderingEventUtilizer][m_uiRenderingStyleStatus][m_uiRenderingControlComponent][uiStyleComponent][m_uiRenderingStyleFragment].find(uiStyleProperty) != m_umapItemsStyles[m_pRenderingEventUtilizer][m_uiRenderingStyleStatus][m_uiRenderingControlComponent][uiStyleComponent][m_uiRenderingStyleFragment].end())
	{
		return *(T*)m_umapItemsStyles[m_pRenderingEventUtilizer][m_uiRenderingStyleStatus][m_uiRenderingControlComponent][uiStyleComponent][m_uiRenderingStyleFragment][uiStyleProperty];
	}
	return *(T*)m_umapCustomStyleGroups[strRenderingStyleGroup][m_uiRenderingStyleStatus][m_uiRenderingControlComponent][uiStyleComponent][m_uiRenderingStyleFragment][uiStyleProperty];
}