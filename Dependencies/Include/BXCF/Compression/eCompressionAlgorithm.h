#pragma once

#include "nsbxcf.h"
#include "Type/Types.h"

enum bxcf::ECompressionAlgorithm : uint8
{
	COMPRESSION_NONE		= 0,
	COMPRESSION_UNKNOWN		= 255,

	COMPRESSION_ZLIB		= 1,
	COMPRESSION_LZ4			= 2
};