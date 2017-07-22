#ifndef CRadioControl_H
#define CRadioControl_H

#include "Type/Types.h"
#include "Control/CGUIControl.h"
#include "Controls/Components/CGUIControlComponent_Text.h"

class CRadioControl : public CGUIControl, public CGUIControlComponent_Text
{
public:
	CRadioControl(void);

	void									bindEvents(void);

	void									unserialize(bool bSkipControlId = false);
	void									serialize(void);

	void									onMouseUp(bxa::CPoint2D& vecCursorPosition);

	void									render(void);

	bool									isPointInControl(bxa::CPoint2D& vecPoint);

	bxa::CPoint2D								getIconCenterPosition(void);

	bxa::CSize2D									getTotalSize(void); // todo - duplicated code in check and radio controls
	uint32									getIconRadius(void);

	bxa::CPoint2D								getTextPosition(void);

	int32									getMarkableTextSpacing(void); // todo - duplicated code in check and radio controls

	void									setMarked(bool bMarked) { m_bMarked = bMarked; } // todo - duplicated code in check and radio controls
	bool									isMarked(void) { return m_bMarked; }
	
	void									setGroupId(uint32 uiGroupId) { m_uiGroupId = uiGroupId; }
	uint32									getGroupId(void) { return m_uiGroupId; }
	
private:
	uint32									m_uiGroupId;
	uint8									m_bMarked			: 1;
};

#endif