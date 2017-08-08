#pragma once

#include "Type/Types.h"
#include "Object/CSingleton.h"
#include "Type/Vector/CColour.h"
#include "Event/CGUIEventUtilizer.h"
#include <string>
#include <vector>
#include <unordered_map>
#include <map>
#include <sparsehash/dense_hash_map___Int.h>
#include <sparsehash/dense_hash_map___Pointer.h>

class CGUIStyles;

class CStyleManager_Hash1
{
public:
	inline size_t operator()(const uint32 & uiValue) const
	{
		return uiValue;
	}
};

/*
static const size_t InitialFNV = 2166136261U;
static const size_t FNVMultiple = 16777619;
class CStyleManager_Hash2
{
public:
	size_t operator()(const std::string &s) const noexcept
	{
		size_t hash = InitialFNV;
		for (size_t i = 0, j = s.length(); i < j; i++)
		{
			hash ^= (s[i]);       // xor  the low 8 bits
			hash *= FNVMultiple;  // multiply by the magic number
		}
		return hash;
	}
};
*/

/*
typedef std::unordered_map<uint32,
			std::unordered_map<uint32,
				std::unordered_map<uint32,
					std::unordered_map<uint32,
						std::unordered_map<uint32,
							std::unordered_map<uint32, void*>
						>
					>
				>
			>
		> container6d_1;

typedef std::unordered_map<CGUIEventUtilizer*,
			std::unordered_map<uint32,
				std::unordered_map<uint32,
					std::unordered_map<uint32,
						std::unordered_map<uint32,
							std::unordered_map<uint32, void*>
						>
					>
				>
			>
		> container6d_2;
*/

/*
typedef std::tr1::unordered_map<uint32,
			std::tr1::unordered_map<uint32,
				std::tr1::unordered_map<uint32,
					std::tr1::unordered_map<uint32,
						std::tr1::unordered_map<uint32,
							std::tr1::unordered_map<uint32, void*, CStyleManager_Hash1>,
						CStyleManager_Hash1>,
					CStyleManager_Hash1>,
				CStyleManager_Hash1>,
			CStyleManager_Hash1>,
		CStyleManager_Hash1> container6d_1;

typedef std::tr1::unordered_map<CGUIEventUtilizer*,
			std::tr1::unordered_map<uint32,
				std::tr1::unordered_map<uint32,
					std::tr1::unordered_map<uint32,
						std::tr1::unordered_map<uint32,
							std::tr1::unordered_map<uint32, void*, CStyleManager_Hash1>,
						CStyleManager_Hash1>,
					CStyleManager_Hash1>,
				CStyleManager_Hash1>,
			CStyleManager_Hash1>
		> container6d_2;
*/

//static CGUIEventUtilizerBlank * g_pGUIEventUtilizerBlank = new CGUIEventUtilizerBlank;

/*
template <class Value_>
struct umap_google__uint32 : public google::dense_hash_map<uint32, Value_>
{
	umap_google__uint32(void) :
		dense_hash_map()
	{
		set_empty_key(-1);
		set_deleted_key(-2);
	}
};

template <class Value_>
struct umap_google__CGUIEventUtilizerPointer : public google::dense_hash_map<CGUIEventUtilizer*, Value_>
{
	umap_google__CGUIEventUtilizerPointer(void) :
		dense_hash_map()
	{
		set_empty_key(nullptr);
		set_deleted_key(g_pGUIEventUtilizerBlank);
	}
};

typedef umap_google__uint32<
			umap_google__uint32<
				umap_google__uint32<
					umap_google__uint32<
						umap_google__uint32<
							umap_google__uint32<void*>
						>
					>
				>
			>
		> container6d_1;

typedef umap_google__CGUIEventUtilizerPointer<
			umap_google__uint32<
				umap_google__uint32<
					umap_google__uint32<
						umap_google__uint32<
							umap_google__uint32<void*>
						>
					>
				>
			>
		> container6d_2;
*/

typedef google::dense_hash_map___Int<uint32,
			google::dense_hash_map___Int<uint32,
				google::dense_hash_map___Int<uint32,
					google::dense_hash_map___Int<uint32,
						google::dense_hash_map___Int<uint32,
							google::dense_hash_map___Int<uint32, void*>
						>
					>
				>
			>
		> container6d_1;

typedef google::dense_hash_map___Pointer<CGUIEventUtilizer*,
			google::dense_hash_map___Int<uint32,
				google::dense_hash_map___Int<uint32,
					google::dense_hash_map___Int<uint32,
						google::dense_hash_map___Int<uint32,
							google::dense_hash_map___Int<uint32, void*>
						>
					>
				>
			>
		> container6d_2;

/*
typedef std::map<uint32,
			std::map<uint32,
				std::map<uint32,
					std::map<uint32,
						std::map<uint32,
							std::map<uint32, void*>
						>
					>
				>
			>
		> container6d_1;

typedef std::map<CGUIEventUtilizer*,
			std::map<uint32,
				std::map<uint32,
					std::map<uint32,
						std::map<uint32,
							std::map<uint32, void*>
						>
					>
				>
			>
		> container6d_2;
*/

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
	bool											doesStyleExist(uint32 uiStyleComponent, uint32 uiStyleProperty, uint32 uiStyleFragment);

	uint32											getCustomStyleGroupId(std::string& strStyleGroupName);

	uint32											getGroupStylesKey(uint32 uiStyleGroupId, uint32 uiStyleStatus, uint32 uiControlComponent, uint32 uiStyleComponent, uint32 uiStyleFragment, uint32 uiStyleProperty);
	uint32											getStylesKey(uint32 uiStyleStatus, uint32 uiControlComponent, uint32 uiStyleComponent, uint32 uiStyleFragment, uint32 uiStyleProperty);

	bool											getStylePropertyAndValueFromMarkupStyleValues(std::vector<std::string>& vecMarkupStyleValues, uint32 uiTokenIndex, uint32 uiStyleComponent, uint32& uiStyleProperty, uint32& uiStyleFragment, void*& pStyleValue, uint32& uiTokenCountRead);

	template <typename T>
	T												getStyle(uint32 uiStyleComponent, uint32 uiStyleProperty);
	template <typename T>
	T												getStyleWithFragment(uint32 uiStyleComponent, uint32 uiStyleProperty, uint32 uiStyleFragment);
	template <typename T>
	T												getStyleFast(std::string& strRenderingStyleGroup, uint32 uiStyleComponent, uint32 uiStyleProperty);

	template <typename T>
	T*												getNativeStyle(uint32 uiStyleComponent, uint32 uiStyleProperty);
	template <typename T>
	T*												getNativeStyle(CGUIEventUtilizer *pGUIEventUtilizer, uint32 uiStyleComponent, uint32 uiStyleProperty);

	void											setItemStyle(CGUIEventUtilizer *pGUIEventUtilizer, uint32 uiStyleComponent, uint32 uiStyleProperty, void *pStyleValue);
	void											removeItemStyle(CGUIEventUtilizer *pGUIEventUtilizer, uint32 uiStyleComponent, uint32 uiStyleProperty);

	bool											doesHaveLeftLine(void);
	bool											doesHaveRightLine(void);
	bool											doesHaveTopLine(void);
	bool											doesHaveBottomLine(void);

	bxcf::CColour									getLineColour(void);

	uint32											getSpacingX(void);
	uint32											getSpacingY(void);

public:
	uint32											m_uiRenderingItemType; // window, layer, shape, or control
	uint32											m_uiRenderingItemSubType; // type of shape, type of control, etc
	uint32											m_uiRenderingControlComponent; // main, headerRow, headerCell, tab, etc
	uint32											m_uiRenderingStyleStatus; // default, hover, etc
	uint32											m_uiRenderingStyleFragment; // all, left, right, etc
	CGUIEventUtilizer*								m_pRenderingEventUtilizer;
	std::vector<uint32>								m_vecRenderingStyleGroups;

	//CGUIStyles*										m_pDefaultControlStyles;

	std::unordered_map<std::string, uint32>			m_umapControls;				// Example: ["grid"] = bxgx::controls::GRID
	std::unordered_map<std::string, uint32>			m_umapControlComponents;	// Example: ["headers"] = bxgx::controls::components::HEADERS
	std::unordered_map<std::string, uint32>			m_umapStyleComponents;		// Example: ["text"] = bxgx::styles::components::TEXT
	std::unordered_map<std::string, uint32>			m_umapStyleStatuses;		// Example: ["hover"] = bxgx::styles::statuses::HOVER
	std::unordered_map<std::string, uint32>			m_umapStyleProperties;		// Example: ["colour"] = bxgx::styles::components::COLOUR
	std::unordered_map<std::string, uint32>			m_umapStyleFragments;		// Example: ["left"] = bxgx::styles::fragments::LEFT

	std::unordered_map<std::string, std::pair<uint32, void*>>		m_umapStyleValues;			// Example: ["false"] = pair(bxgx::styles::properties::STATUS, bool* false)

	std::unordered_map<std::string, uint32>			m_umapCustomStyleGroupIds;

	container6d_1									m_umapCustomStyleGroups, m_umapControlStyleGroups, m_umapDefaultCustomStyleGroups, m_umapDefaultControlStyleGroups;
	container6d_2									m_umapItemsStyles;

	/*
	std::unordered_map<uint32,
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

	std::unordered_map<CGUIEventUtilizer*,
		std::unordered_map<uint32,
			std::unordered_map<uint32,
				std::unordered_map<uint32,
					std::unordered_map<uint32,
						std::unordered_map<uint32, void*>
					>
				>
			>
		>
	>												m_umapItemsStyles;
	*/
};

template <typename T>
T													CStyleManager::getStyle(uint32 uiStyleComponent, uint32 uiStyleProperty)
{
	T *pStyleValue = getNativeStyle<T>(m_pRenderingEventUtilizer, uiStyleComponent, uiStyleProperty);
	return pStyleValue != nullptr ? *(T*)pStyleValue : T();
}

template <typename T>
T*													CStyleManager::getNativeStyle(uint32 uiStyleComponent, uint32 uiStyleProperty)
{
	return getNativeStyle<T>(m_pRenderingEventUtilizer, uiStyleComponent, uiStyleProperty);
}

template <typename T>
T*													CStyleManager::getNativeStyle(CGUIEventUtilizer *pGUIEventUtilizer, uint32 uiStyleComponent, uint32 uiStyleProperty)
{
	/*
	if (m_umapItemsStyles[m_pRenderingEventUtilizer][m_uiRenderingStyleStatus][m_uiRenderingControlComponent][uiStyleComponent][m_uiRenderingStyleFragment].find(uiStyleProperty) != m_umapItemsStyles[m_pRenderingEventUtilizer][m_uiRenderingStyleStatus][m_uiRenderingControlComponent][uiStyleComponent][m_uiRenderingStyleFragment].end())
	{
		return (T*)m_umapItemsStyles[m_pRenderingEventUtilizer][m_uiRenderingStyleStatus][m_uiRenderingControlComponent][uiStyleComponent][m_uiRenderingStyleFragment][uiStyleProperty];
	}
	for (uint32 uiRenderingStyleGroup : m_vecRenderingStyleGroups)
	{
		if (m_umapCustomStyleGroups[uiRenderingStyleGroup][m_uiRenderingStyleStatus][m_uiRenderingControlComponent][uiStyleComponent][m_uiRenderingStyleFragment].find(uiStyleProperty) != m_umapCustomStyleGroups[uiRenderingStyleGroup][m_uiRenderingStyleStatus][m_uiRenderingControlComponent][uiStyleComponent][m_uiRenderingStyleFragment].end())
		{
			return (T*)m_umapCustomStyleGroups[uiRenderingStyleGroup][m_uiRenderingStyleStatus][m_uiRenderingControlComponent][uiStyleComponent][m_uiRenderingStyleFragment][uiStyleProperty];
		}
	}
	return nullptr;
	*/

	///*
	if (m_umapItemsStyles.find(pGUIEventUtilizer) != m_umapItemsStyles.end())
	{
		auto &umap1 = m_umapItemsStyles[pGUIEventUtilizer];
		if (umap1.find(m_uiRenderingStyleStatus) != umap1.end())
		{
			auto &umap2 = umap1[m_uiRenderingStyleStatus];
			if (umap2.find(m_uiRenderingControlComponent) != umap2.end())
			{
				auto &umap3 = umap2[m_uiRenderingControlComponent];
				if (umap3.find(uiStyleComponent) != umap3.end())
				{
					auto &umap4 = umap3[uiStyleComponent];
					if (umap4.find(m_uiRenderingStyleFragment) != umap4.end())
					{
						auto &umap5 = umap4[m_uiRenderingStyleFragment];
						if (umap5.find(uiStyleProperty) != umap5.end())
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
						if (umap4.find(m_uiRenderingStyleFragment) != umap4.end())
						{
							auto &umap5 = umap4[m_uiRenderingStyleFragment];
							if (umap5.find(uiStyleProperty) != umap5.end())
							{
								return (T*)umap5[uiStyleProperty];
							}
						}
					}
				}
			}
		}
	}
	//*/

	/*
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
	for (std::string& strRenderingStyleGroup : m_vecRenderingStyleGroups)
	{
		if (m_umapCustomStyleGroups.count(strRenderingStyleGroup))
		{
			auto &umap1 = m_umapCustomStyleGroups[strRenderingStyleGroup];
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
	*/

	return nullptr;
}

template <typename T>
T													CStyleManager::getStyleWithFragment(uint32 uiStyleComponent, uint32 uiStyleProperty, uint32 uiStyleFragment)
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
T													CStyleManager::getStyleFast(std::string& strRenderingStyleGroup, uint32 uiStyleComponent, uint32 uiStyleProperty)
{
	if (m_umapItemsStyles[m_pRenderingEventUtilizer][m_uiRenderingStyleStatus][m_uiRenderingControlComponent][uiStyleComponent][m_uiRenderingStyleFragment].find(uiStyleProperty) != m_umapItemsStyles[m_pRenderingEventUtilizer][m_uiRenderingStyleStatus][m_uiRenderingControlComponent][uiStyleComponent][m_uiRenderingStyleFragment].end())
	{
		return *(T*)m_umapItemsStyles[m_pRenderingEventUtilizer][m_uiRenderingStyleStatus][m_uiRenderingControlComponent][uiStyleComponent][m_uiRenderingStyleFragment][uiStyleProperty];
	}
	return *(T*)m_umapCustomStyleGroups[strRenderingStyleGroup][m_uiRenderingStyleStatus][m_uiRenderingControlComponent][uiStyleComponent][m_uiRenderingStyleFragment][uiStyleProperty];
}