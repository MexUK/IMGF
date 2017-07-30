#ifndef CVector4ui8_H
#define CVector4ui8_H

#include "bxcf.h"
#include "Type/Types.h"

class bxcf::CVector4ui8
{
public:
	uint8	m_x;	// todo - rename to .x and .y and .z and .w
	uint8	m_y;
	uint8	m_z;
	uint8	m_w;

public:
	uint32					convertToUint32(void)
	{
		return m_x +
			(m_y * 256) +
			(m_z * 65536) +
			(m_w * 16777216);
		// todo - make like: uint32 CMath::getUint32(ui8_1, ui8_2, ui8_3, ui8_4, bool bBigEndian = false)
		// todo - and make this function take a bool for endian type
	};
};

#endif