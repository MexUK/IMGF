#ifndef ePlatform_H
#define ePlatform_H

#include "BXA.h"

enum bxa::ePlatform : uint8
{
	_PLATFORM_UNKNOWN,
	PLATFORM_PC,
	PLATFORM_XBOX,
	PLATFORM_PS2,
	PLATFORM_ANDROID
};

#endif