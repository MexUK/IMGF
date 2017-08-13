#ifndef CButtonControl_H
#define CButtonControl_H

#include "Type/Types.h"
#include "Control/CGUIControl.h"
#include "Controls/Components/CGUIControlComponent_Text.h"
#include <string>
#include <vector>

class CButtonControl : public CGUIControl, public CGUIControlComponent_Text
{
public:
	CButtonControl(void);
	virtual ~CButtonControl(void) {}

	void									bindEvents(void);

	void									unserialize(bool bSkipControlId = false);
	void									serialize(void);

	bool									onLeftMouseDown(bxcf::Vec2i& vecCursorPosition);
	bool									onLeftMouseUp(bxcf::Vec2i& vecCursorPosition);
	bool									onMouseMove(bxcf::Vec2i& vecCursorPosition);
	bool									onMouseEnter(bxcf::Vec2i& vecCursorPosition);
	bool									onMouseExit(bxcf::Vec2i& vecCursorPosition);
	void									onRender(void);

	bool									applyCursorHoverIcon(void);

	void									setCursorHoverActive(bool bCursorHoverIsActive) { m_bCursorHoverIsActive = bCursorHoverIsActive; }
	bool									isCursorHoverActive(void) { return m_bCursorHoverIsActive; }

private:
	bool									m_bCursorHoverIsActive;
};

#endif