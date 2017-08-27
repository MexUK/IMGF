#pragma once

#include "nsbxgx.h"

enum bxgx::controls::components::EControlComponent
{
	DEFAULT_CONTROL_COMPONENT	= 0,
	HEADER_ROW					= 1,
	HEADER_CELL					= 2,
	TAB							= 3,
	ICON						= 4,
	LIST						= 5,
	LIST_ROW					= 6,
	ARROW						= 7,
	CARET						= 8,
	SELECTION					= 9,
	ROW							= 10,
	CELL						= 11,
	INNER_BAR					= 12,
	SEEK_BAR					= 13,
	DEFAULT_TEXT				= 14
};

enum bxgx::styles::statuses::EStyleStatus
{
	DEFAULT_STATUS				= 0,
	HOVER						= 1,
	HOVER2						= 2,
	CHECKED						= 3,
	UNCHECKED					= 4,
	N1							= 5,
	N2							= 6,
	SELECTED					= 7,
	MAIN_SELECTED				= 8,
	ACTIVE						= 9
};

enum bxgx::styles::components::EStyleComponent
{
	FILL						= 0,
	LINE						= 1,
	TEXT						= 2,
	SPACING						= 3
};

enum bxgx::styles::properties::EStyleProperty
{
	COLOUR						= 0,
	RADIUS						= 1,
	LENGTH						= 2,
	FONT						= 3,
	WEIGHT						= 4,
	STYLE						= 5,
	ALIGN						= 6,
	STATUS						= 7
};

enum bxgx::styles::fragments::EStyleFragment
{
	ALL_STYLE_FRAGMENTS			= 0,
	LEFT						= 1,
	RIGHT						= 2,
	TOP							= 3,
	BOTTOM						= 4,
	TOP_LEFT					= 5,
	TOP_RIGHT					= 6,
	BOTTOM_LEFT					= 7,
	BOTTOM_RIGHT				= 8,
	START						= 9,  // e.g. start colour for gradient
	STOP						= 10, // e.g. stop colour for gradient
	X							= 11, // e.g. x align for text
	Y							= 12, // e.g. y align for text
	MIN							= 13, // e.g. min spacing for text
	MAX							= 14  // e.g. max spacing for text
};

enum bxgx::styles::values::EStyleValue
{
	BOLD						= 0,
	ITALIC						= 1,
	UNDERLINE					= 2,
	STRIKETHROUGH				= 3,
	LEFT						= 4,
	RIGHT						= 5,
	CENTER						= 6,
	TOP							= 7,
	BOTTOM						= 8
};