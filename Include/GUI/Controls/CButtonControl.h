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
	
	void									bindEvents(void);

	void									unserialize(bool bSkipControlId = false);
	void									serialize(void);

	void									onMouseDown(mcore::CPoint2D& vecCursorPosition);
	void									onMouseUp(mcore::CPoint2D& vecCursorPosition);

	void									render(void);
};

#endif