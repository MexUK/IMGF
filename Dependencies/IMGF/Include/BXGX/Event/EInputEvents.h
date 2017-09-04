#pragma once

#include "bxgx.h"

enum bxgx::control::events::EInputEvents
{
	// window
	RESIZE_WINDOW = 20000, // todo - move to bxgx::window::events

	// items
	MOUSE_ENTER_ITEM, // todo - move to bxgx::item::events
	MOUSE_EXIT_ITEM, // todo - move to bxgx::item::events

	// item
	PRESS_BUTTON,

	MARK_CHECKBOX,
	UNMARK_CHECKBOX,

	CHECK_RADIO_BUTTON,
	UNCHECK_RADIO_BUTTON,

	CHANGE_TAB,
	REMOVE_TAB,

	OPEN_DROP_LIST,
	CLOSE_DROP_LIST,
	SELECT_DROP_ENTRY,

	MOVE_SCROLL_SEEK_BAR,
	START_MOVING_SCROLL_SEEK_BAR,
	STOP_MOVING_SCROLL_SEEK_BAR,

	PROGRESS_BAR_PROGRESS,

	SELECT_GRID_ROW,
	UNSELECT_GRID_ROW
};