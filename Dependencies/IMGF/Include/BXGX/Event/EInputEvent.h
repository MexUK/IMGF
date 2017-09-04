#pragma once

#include "nsbxgx.h"

enum bxgx::control::events::EInputEvent
{
	// bxgx
	BXGX_READY = 20000,

	// window
	RESIZE_WINDOW, // todo - move to bxgx::window::events

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

	PROGRESS_PROGRESS_BAR,

	SELECT_GRID_ROW,
	UNSELECT_GRID_ROW
};