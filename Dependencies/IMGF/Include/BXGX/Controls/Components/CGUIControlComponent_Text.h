#ifndef CGUIControlComponent_Text_H
#define CGUIControlComponent_Text_H

#include "Type/Types.h"
#include "BXGXManager.h"
#include "GraphicsLibrary/CGraphicsLibrary.h"
#include "String/CGUIString.h"
#include <string>

class CGUIControl;

class CGUIControlComponent_Text
{
public:
	CGUIControlComponent_Text(void);

	bool									checkToRecalculateStringSize(CGUIStyles *pStyles);

	bxcf::Vec2u&							getTextSize(void) { return m_gstrText.getSize(); }
	uint32									getTextWidth(void) { return m_gstrText.getSize().x; }
	uint32									getTextHeight(void) { return m_gstrText.getSize().y; }

	void									setText(std::string& strText);
	std::string&							getText(void) { return m_gstrText.getString(); }

	void									setControl(CGUIControl *pControl) { m_pControl = pControl; }
	CGUIControl*							getControl(void) { return m_pControl; }

	CGUIString&								getGUIString(void) { return m_gstrText; }

	void									setStringSizeNeedsRecalculating(bool bStringSizeNeedsRecalculating) { m_bStringSizeNeedsRecalculating = bStringSizeNeedsRecalculating; }
	bool									doesStringSizeNeedRecalculating(void) { return m_bStringSizeNeedsRecalculating; }

private:
	void									recalculateStringSize(CGUIStyles *pStyles);

private:
	CGUIControl*							m_pControl;
	uint8									m_bStringSizeNeedsRecalculating		: 1;
	CGUIString								m_gstrText;
};

#endif