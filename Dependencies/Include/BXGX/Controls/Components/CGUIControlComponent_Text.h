#ifndef CGUIControlComponent_Text_H
#define CGUIControlComponent_Text_H

#include "Type/Types.h"
#include "CGUIManager.h"
#include "GraphicsLibrary/CGraphicsLibrary.h"
#include "String/CGUIString.h"
#include <string>
#include <Windows.h>
#include <Gdiplus.h>

class CGUIControlComponent_Text
{
public:
	CGUIControlComponent_Text(void);

	bool									checkToRecalculateStringSize(CGUIStyles *pStyles);

	bxcf::CSize2D&								getTextSize(void) { return m_gstrText.getSize(); }
	uint32									getTextWidth(void) { return m_gstrText.getSize().m_x; }
	uint32									getTextHeight(void) { return m_gstrText.getSize().m_y; }

	void									setText(std::string& strText) { m_gstrText.setString(strText); }
	std::string&							getText(void) { return m_gstrText.getString(); }

	CGUIString&								getGUIString(void) { return m_gstrText; }

	void									setStringSizeNeedsRecalculating(bool bStringSizeNeedsRecalculating) { m_bStringSizeNeedsRecalculating = bStringSizeNeedsRecalculating; }
	bool									doesStringSizeNeedRecalculating(void) { return m_bStringSizeNeedsRecalculating; }

private:
	void									recalculateStringSize(CGUIStyles *pStyles);

private:
	uint8									m_bStringSizeNeedsRecalculating		: 1;
	CGUIString								m_gstrText;
};

#endif