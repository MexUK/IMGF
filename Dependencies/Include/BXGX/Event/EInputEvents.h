#pragma once

#include "bxgx.h"

enum bxgx::control::events::EInputEvents
{
	MOUSE_ENTER_ITEM,
	MOUSE_EXIT_ITEM,

	PRESS_BUTTON,

	MARK_CHECKBOX,
	UNMARK_CHECKBOX,

	CHECK_RADIO_BUTTON,
	UNCHECK_RADIO_BUTTON,

	CHANGE_TAB
};