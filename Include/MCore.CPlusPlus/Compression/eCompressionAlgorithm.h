#ifndef eCompressionAlgorithm_H
#define eCompressionAlgorithm_H

#include "bxa.h"
#include "Type/Types.h"

enum bxa::eCompressionAlgorithm : uint8
{
	COMPRESSION_NONE		= 0,
	COMPRESSION_UNKNOWN		= 255,

	COMPRESSION_ZLIB		= 1,
	COMPRESSION_LZ4			= 2
};

#endif