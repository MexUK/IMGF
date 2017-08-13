#ifndef CGUIStyles_H
#define CGUIStyles_H

#include "bxgx.h"
#include "Type/Types.h"
#include "Type/Vector/Vec2i.h"
#include "Pool/CMultipleTypeValuesUMapContainer.h"
#include "Styles/CCoordinates.h"
#include <string>
#include <vector>
#include <unordered_map>

/*
class CGUIStyles;

namespace bxgx
{
	namespace styles
	{
		// functions
		//template <typename ...T>
		//CGUIStyles*		make(T...); // in CGUIStyles.h
	};
};
*/

class CGUIStyles : public bxcf::CMultipleTypeValuesUMapContainer<std::string>
{
public:
	CGUIStyles(void);

	void					init(void);
	void					uninit(void);

	bool					doesStyleExist(std::string strStyleName);

	void					setStyle(std::string strStyleName, bool bStyleValue);
	void					setStyle(std::string strStyleName, uint32 uiStyleValue);
	void					setStyle(std::string strStyleName, int32 iStyleValue);
	void					setStyle(std::string strStyleName, float32 fStyleValue);
	void					setStyle(std::string strStyleName, std::string strStyleValue);

	template <typename ValueType>
	void					setStyle(std::string strStyleName, ValueType value);
	template <typename ValueType>
	ValueType				getStyle(std::string strStyleName);

	template <typename ValueType>
	ValueType				getStyleDefaultValue(std::string strStyleName);

	bool					doesHaveCompleteBorder(void);
	bool					doesHaveBorderEdge(uint8 uiBorderEdge);
	bool					doesHaveBorder(void);
	bool					doesHaveLeftBorder(void);
	bool					doesHaveRightBorder(void);
	bool					doesHaveTopBorder(void);
	bool					doesHaveBottomBorder(void);
	bool					doesHaveFill(void);

	std::string				getTextAlignX(void);
	std::string				getTextAlignY(void);
	bxcf::Vec2i				getMinInnerSpacing(void);
	bxcf::Vec2i				getMaxInnerSpacing(void);
	uint32					getInnerSpacingTotalX(void);
	uint32					getInnerSpacingTotalY(void);

	void					restoreTemporaryStyleData(void);
	void					restoreStyleOverwrites(void);

	std::string				getResolvedStyleName(std::string strStyleName);

	void					setItemComponent(std::string strItemComponent) { m_strItemComponent = strItemComponent; }
	std::string&			getItemComponent(void) { return m_strItemComponent; }
	void					resetItemComponent(void) { m_strItemComponent = ""; }

	void					setItemStatus(std::string strItemStatus) { m_strItemStatus = strItemStatus; }
	std::string&			getItemStatus(void) { return m_strItemStatus; }
	void					resetItemStatus(void) { m_strItemStatus = ""; }

	void					setHasFillOverwrite(bool bHasFillOverwrite) { m_bHasFillOverwrite = bHasFillOverwrite; }
	bool					doesHaveFillOverwrite(void) { return m_bHasFillOverwrite; }

	static bxcf::CMultipleTypeValuesUMapContainer<std::string>&	getStyleDefaultValues(void) { return m_umapStyleDefaultValues; }

	static bool				doesDefaultStyleValueExist(std::string strStyleName);

	void					loadFromStyles(CGUIStyles *pGUIStyles);

private:
	uint8													m_bHasFillOverwrite		: 1;
	std::string												m_strItemComponent;
	std::string												m_strItemStatus;
	int32													m_zIndex;
	static bxcf::CMultipleTypeValuesUMapContainer<std::string>	m_umapStyleDefaultValues;

public:
	CGUIStyles*												m_pLinkedStyles;

	// Example: m_umapStyles[DEFAULT_STATUS][BUTTON][DEFAULT_CONTROL_COMPONENT][ALL_FRAGMENTS][FILL][COLOUR] = CColour*
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
	>														m_umapCustomStyleGroups, m_umapControlStyleGroups, m_umapDefaultCustomStyleGroups, m_umapDefaultControlStyleGroups;

};




template <typename ValueType>
void				CGUIStyles::setStyle(std::string strStyleName, ValueType value)
{
	setEntry<ValueType>(strStyleName, value);
}

template <typename ValueType>
ValueType				CGUIStyles::getStyle(std::string strStyleName)
{
	/*
	Order of style processing
	-------------------------
	applied style: default.fill-colour:marked
	applied style: fill-colour:marked
	default style: fill-colour:marked	- eventually can be fully resolved to encounter for default values for multiple components - todo
	applied style: default.fill-colour
	applied style: fill-colour
	default style: fill-colour		- eventually can be fully resolved to encounter for default values for multiple components - todo
	*/

	std::string
		&strItemComponent = getItemComponent(),
		&strItemStatus = getItemStatus();
	bool
		bHasComponent = strItemComponent != "",
		bHasStatus = strItemStatus != "";
	std::string
		strStyleNamePartial1 = (!bHasStatus ? "" : (":" + strItemStatus)),
		strStyleNameWithComponent = (!bHasComponent ? "default." : (strItemComponent + ".")) + strStyleName,
		strStyleNameFullyResolved = strStyleNameWithComponent + strStyleNamePartial1, // with component and status
		strStyleNameWithStatus = strStyleName + strStyleNamePartial1;

	if (bHasComponent && bHasStatus)
	{
		if (doesStyleExist(strStyleNameFullyResolved))
		{
			// e.g. drop-triangle.fill-colour:list-open
			return *getEntryPointer<ValueType>(strStyleNameFullyResolved);
		}
		else if (doesDefaultStyleValueExist(strStyleNameFullyResolved))
		{
			// e.g. drop-triangle.fill-colour:list-open
			return getStyleDefaultValue<ValueType>(strStyleNameFullyResolved);
		}
	}
	else if (bHasStatus)
	{
		if (doesStyleExist(strStyleNameWithStatus))
		{
			// e.g. fill-colour:list-open
			return *getEntryPointer<ValueType>(strStyleNameWithStatus);
		}
		else if (doesDefaultStyleValueExist(strStyleNameWithStatus))
		{
			// e.g. fill-colour:list-open
			return getStyleDefaultValue<ValueType>(strStyleNameWithStatus);
		}
	}
	else if (bHasComponent)
	{
		if (doesStyleExist(strStyleNameWithComponent))
		{
			// e.g. drop-triangle.fill-colour
			return *getEntryPointer<ValueType>(strStyleNameWithComponent);
		}
		else if (doesDefaultStyleValueExist(strStyleNameWithComponent))
		{
			// e.g. drop-triangle.fill-colour
			return getStyleDefaultValue<ValueType>(strStyleNameWithComponent);
		}
	}

	if (doesStyleExist(strStyleName))
	{
		// e.g. fill-colour
		return *getEntryPointer<ValueType>(strStyleName);
	}
	else
	{
		// e.g. fill-colour
		return getStyleDefaultValue<ValueType>(strStyleName);
	}
}

template <typename ValueType>
ValueType				CGUIStyles::getStyleDefaultValue(std::string strStyleName)
{
	if (getStyleDefaultValues().doesEntryExist(strStyleName))
	{
		return *(getStyleDefaultValues().getEntryPointer<ValueType>(strStyleName));
	}
	else
	{
		return ValueType();
	}
}

/*
template <typename ...T>
CGUIStyles*		bxgx::styles::make(T... ppStyles)
{
	std::vector<const char *> vecStyles = { ppStyles ... };
	CGUIStyles * pStyles = new CGUIStyles;
	for (const char * szStyle : vecStyles)
	{
		std::string strStyle = std::string(szStyle);
		auto parts = bxcf::CString2::split(strStyle, ":");
		std::string prop = bxcf::CString2::trim(parts[0]);
		std::string value = bxcf::CString2::trim(parts[1]);

		if (prop == "border-colour")
		{
			auto parts2 = bxcf::CString2::split(value, " ");
			uint8 r = bxcf::CString2::toNumber(parts2[0]);
			uint8 g = bxcf::CString2::toNumber(parts2[1]);
			uint8 b = bxcf::CString2::toNumber(parts2[2]);
			uint8 a = bxcf::CString2::toNumber(parts2[3]);
			pStyles->setStyle(prop, bxcf::CColour(r, g, b, a));
		}
		else if (prop == "line-thickness")
		{
		}
		else if (prop == "x" || prop == "y")
		{
			pStyles->setStyle(prop, CCoordinateExpression(value));
		}
		else if (prop.c_str()[0] == 'x' || prop.c_str()[0] == 'y')
		{
			pStyles->setStyle(prop, CString2::toFloat32(value));
		}
		else if (prop == "text-size")
		{
			pStyles->setStyle(prop, CString2::toNumber(value));
		}
		else
		{
			pStyles->setStyle(prop, value);
		}
	}
	return pStyles;
}
*/

#endif