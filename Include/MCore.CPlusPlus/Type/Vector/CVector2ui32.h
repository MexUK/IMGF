#ifndef CVector2ui32_H
#define CVector2ui32_H

#include "mcore.h"
#include "Type/Vector/CVector2i32.h"
#include "Type/Types.h"

class mcore::CVector2ui32
{
public:
	uint32	m_x;
	uint32	m_y;

public:
	CVector2ui32(void)
	{
	}
	CVector2ui32(uint32 x, uint32 y)
	{
		m_x = x;
		m_y = y;
	}

	CVector2ui32&	operator+(const mcore::CVector2i32& vecVector2)
	{
		CVector2ui32 vecVector;
		vecVector.m_x = m_x + vecVector2.m_x;
		vecVector.m_y = m_y + vecVector2.m_y;
		return vecVector;
	}
};

#endif