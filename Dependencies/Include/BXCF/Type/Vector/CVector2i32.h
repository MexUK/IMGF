#pragma once

#include "bxcf.h"
#include "Type/Types.h"

class bxcf::CVector2i32
{
public:
	int32	m_x;
	int32	m_y;

public:
	bxcf::CVector2i32(void)
	{
	}

	bxcf::CVector2i32(int32 iX, int32 iY)
	{
		m_x = iX;
		m_y = iY;
	}
};