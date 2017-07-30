#ifndef ePlatform_H
#define ePlatform_H

#include "bxcf.h"

enum bxcf::ePlatform : uint8
{
	_PLATFORM_UNKNOWN,
	PLATFORM_PC,
	PLATFORM_XBOX,
	PLATFORM_PS2,
	PLATFORM_ANDROID
};

#endif