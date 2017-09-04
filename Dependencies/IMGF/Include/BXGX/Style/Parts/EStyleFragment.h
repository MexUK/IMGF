#pragma once

#include "nsbxgx.h"

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