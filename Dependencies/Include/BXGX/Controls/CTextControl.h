#ifndef CTextControl_H
#define CTextControl_H

#include "Type/Types.h"
#include "Control/CGUIControl.h"
#include "Controls/Components/CGUIControlComponent_Text.h"
#include <string>

class CTextControl : public CGUIControl, public CGUIControlComponent_Text
{
public:
	CTextControl(void);

	void									bindEvents(void);

	void									unserialize(bool bSkipControlId = false);
	void									serialize(void);

	void									render(void);
};

#endif