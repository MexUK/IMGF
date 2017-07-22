#ifndef eRasterDataFormat_H
#define eRasterDataFormat_H

#include "BXA.h"
#include "Type/Types.h"

enum bxa::eRasterDataFormat : uint8
{
	RASTERDATAFORMAT_UNKNOWN,
	RASTERDATAFORMAT_DXT1,
	RASTERDATAFORMAT_DXT2,
	RASTERDATAFORMAT_DXT3,
	RASTERDATAFORMAT_DXT4,
	RASTERDATAFORMAT_DXT5,
	RASTERDATAFORMAT_BGRA32,
	RASTERDATAFORMAT_RGBA32,
	RASTERDATAFORMAT_BGR32,
	RASTERDATAFORMAT_RGB32,
	RASTERDATAFORMAT_BGR24,
	RASTERDATAFORMAT_RGB24,
	RASTERDATAFORMAT_PAL4,
	RASTERDATAFORMAT_PAL8
};

#endif