#ifndef CPoint2D_H
#define CPoint2D_H

#include "BXA.h"
#include "Type/Vector/CVector2i32.h"
#include "Type/Types.h"

class bxa::CPoint2D
{
public:
	int32	m_x; // todo - rename to .x and .y
	int32	m_y;

	CPoint2D(void)
	{
		m_x = 0;
		m_y = 0;
	}

	CPoint2D(int32 x, int32 y) :
		m_x(x),
		m_y(y)
	{
	}

	CPoint2D(uint32 x, uint32 y) :
		m_x(x),
		m_y(y)
	{
	}

	CPoint2D(float32 x, float32 y) :
		m_x((int32)x),
		m_y((int32)y)
	{
	}

	int32			x(void) { return m_x; }
	int32			y(void) { return m_y; }

	CPoint2D		operator+(const CPoint2D& vecVector2)
	{
		CPoint2D vecVector;
		vecVector.m_x = m_x + vecVector2.m_x;
		vecVector.m_y = m_y + vecVector2.m_y;
		return vecVector;
	}

	CPoint2D		operator-(const CPoint2D& vecVector2)
	{
		CPoint2D vecVector;
		vecVector.m_x = m_x - vecVector2.m_x;
		vecVector.m_y = m_y - vecVector2.m_y;
		return vecVector;
	}

	CPoint2D		operator+(const bxa::CVector2i32& vecVector2)
	{
		CPoint2D vecVector;
		vecVector.m_x = m_x + vecVector2.m_x;
		vecVector.m_y = m_y + vecVector2.m_y;
		return vecVector;
	}

	CPoint2D		operator/(const bxa::CPoint2D& vecVector2)
	{
		CPoint2D vecVector;
		vecVector.m_x = m_x / vecVector2.m_x;
		vecVector.m_y = m_y / vecVector2.m_y;
		return vecVector;
	}

	CPoint2D		operator/(const int32 iValue)
	{
		CPoint2D vecVector;
		vecVector.m_x = m_x / iValue;
		vecVector.m_y = m_y / iValue;
		return vecVector;
	}

	CPoint2D		operator+=(const bxa::CVector2i32& vecVector2)
	{
		CPoint2D vecVector;
		vecVector.m_x = m_x + vecVector2.m_x;
		vecVector.m_y = m_y + vecVector2.m_y;
		return vecVector;
	}
};

#endif