#pragma once

#include "nsbxgx.h"
#include "Type/Types.h"
#include "Control/Control.h"
#include "Controls/Entries/CMenuEntry.h"
#include "Pool/CVectorPool.h"

class bxgx::CMenu : public bxgx::Control, public bxcf::CVectorPool<CMenuEntry*>
{
public:
	CMenu(void);

	void									bindEvents(void);

	void									unserialize(bool bSkipControlId = false);
	void									serialize(void);

	void									onRender(void);
};