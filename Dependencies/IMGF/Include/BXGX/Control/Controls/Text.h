#pragma once

#include "nsbxgx.h"
#include "Type/Types.h"
#include "Control/Base/Control.h"
#include "Control/Components/TextComponent.h"

class bxgx::Text : public bxgx::Control, public bxgx::TextComponent
{
public:
	Text(void);

	void									bindEvents(void);

	void									unserialize(bool bSkipControlId = false);
	void									serialize(void);

	void									onRender(void);
};