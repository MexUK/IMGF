#pragma once

#include "nsbxgx.h"
#include "Type/Types.h"
#include "Control/Control.h"
#include "Controls/Components/TextComponent.h"

class bxgx::CRadioButton : public bxgx::Control, public bxgx::TextComponent
{
public:
	CRadioButton(void);

	void									bindEvents(void);

	void									unserialize(bool bSkipControlId = false);
	void									serialize(void);

	bool									onLeftMouseUp(bxcf::Vec2i& vecCursorPosition);
	void									onRender(void);

	bxcf::Vec2u							getBoundingRectangleSize(void);

	bxcf::Vec2i							getIconCenterPosition(void);
	
	uint32									getIconRadius(void);

	bxcf::Vec2i							getTextPosition(void);

	int32									getMarkableTextSpacing(void); // todo - duplicated code in check and radio controls

	void									setMarked(bool bMarked) { m_bMarked = bMarked; } // todo - duplicated code in check and radio controls
	bool									isMarked(void) { return m_bMarked; }
	
	void									setGroupId(uint32 uiGroupId) { m_uiGroupId = uiGroupId; }
	uint32									getGroupId(void) { return m_uiGroupId; }
	
private:
	uint32									m_uiGroupId;
	uint8									m_bMarked			: 1;
};