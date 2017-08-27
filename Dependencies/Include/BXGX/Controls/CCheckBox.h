#pragma once

#include "nsbxgx.h"
#include "Type/Types.h"
#include "Control/Control.h"
#include "Controls/Components/TextComponent.h"

class bxgx::CCheckBox : public bxgx::Control, public bxgx::TextComponent
{
public:
	CCheckBox(void);

	void									bindEvents(void);

	void									unserialize(bool bSkipControlId = false);
	void									serialize(void);

	bool									onLeftMouseUp(bxcf::Vec2i& vecCursorPosition);
	void									onRender(void);

	bxcf::Vec2u							getBoundingRectangleSize(void);

	bxcf::Vec2i							getTextPosition(void);

	int32									getMarkableTextSpacing(void); // todo - duplicated code in check and radio controls
	
	void									setMarked(bool bMarked) { m_bMarked = bMarked; } // todo - duplicated code in check and radio controls
	bool									isMarked(void) { return m_bMarked; }
	
private:
	uint8									m_bMarked			: 1;
};