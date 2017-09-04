#pragma once

#include "nsbxgx.h"
#include "Type/Types.h"
#include "BXGX.h"
#include "GraphicsLibrary/Base/GraphicsLibrary.h"
#include "String/SizedString.h"
#include <string>

class bxgx::Control;

class bxgx::TextComponent
{
public:
	TextComponent(void);

	bool									checkToRecalculateStringSize(void);

	bxcf::Vec2u&							getTextSize(void) { return m_gstrText.getSize(); }
	uint32									getTextWidth(void) { return m_gstrText.getSize().x; }
	uint32									getTextHeight(void) { return m_gstrText.getSize().y; }

	void									setText(std::string& strText);
	std::string&							getText(void) { return m_gstrText.getString(); }

	void									setControl(bxgx::Control *pControl) { m_pControl = pControl; }
	bxgx::Control*							getControl(void) { return m_pControl; }

	SizedString&							getSizedString(void) { return m_gstrText; }

	void									setStringSizeNeedsRecalculating(bool bStringSizeNeedsRecalculating) { m_bStringSizeNeedsRecalculating = bStringSizeNeedsRecalculating; }
	bool									doesStringSizeNeedRecalculating(void) { return m_bStringSizeNeedsRecalculating; }

private:
	void									recalculateStringSize(void);

private:
	bxgx::Control*							m_pControl;
	uint8									m_bStringSizeNeedsRecalculating		: 1;
	SizedString							m_gstrText;
};