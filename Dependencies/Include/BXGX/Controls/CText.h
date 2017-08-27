#pragma once

#include "nsbxgx.h"
#include "Type/Types.h"
#include "Control/Control.h"
#include "Controls/Components/TextComponent.h"

class bxgx::CText : public bxgx::Control, public bxgx::TextComponent
{
public:
	CText(void);

	void									bindEvents(void);

	void									unserialize(bool bSkipControlId = false);
	void									serialize(void);

	void									onRender(void);
};