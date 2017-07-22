#ifndef mcore_CVector2i32_H
#define mcore_CVector2i32_H

#include "bxa.h"
#include "Type/Types.h"

class bxa::CVector2i32
{
public:
	int32	m_x;
	int32	m_y;

public:
	bxa::CVector2i32(void)
	{
	}

	bxa::CVector2i32(int32 iX, int32 iY)
	{
		m_x = iX;
		m_y = iY;
	}
};

#endif