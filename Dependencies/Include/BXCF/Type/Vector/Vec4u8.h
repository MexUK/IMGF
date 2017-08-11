#pragma once

#include "bxcf.h"
#include "Type/Types.h"

class bxcf::Vec4u8
{
public:
	uint8	x;
	uint8	y;
	uint8	z;
	uint8	w;

public:
	uint32					convertToUint32(void)
	{
		return x +
			(y * 256) +
			(z * 65536) +
			(w * 16777216);
		// todo - make like: uint32 CMath::getUint32(ui8_1, ui8_2, ui8_3, ui8_4, bool bBigEndian = false)
		// todo - and make this function take a bool for endian type
	};
};