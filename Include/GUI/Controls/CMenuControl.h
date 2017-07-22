#ifndef CMenuControl_H
#define CMenuControl_H

#include "Type/Types.h"
#include "Control/CGUIControl.h"
#include "Controls/Entries/CMenuControlEntry.h"
#include "Pool/CVectorPool.h"
#include <string>

class CMenuControl : public CGUIControl, public bxa::CVectorPool<CMenuControlEntry*>
{
public:
	CMenuControl(void);

	void									bindEvents(void);

	void									unserialize(bool bSkipControlId = false);
	void									serialize(void);

	void									render(void);

	bool									isPointInControl(bxa::CPoint2D& vecPoint) { return false; }
};

#endif