#ifndef CSize2D_H
#define CSize2D_H

#include "mcore.h"
#include "Type/Types.h"

class mcore::CSize2D
{
public:
	uint32	m_x; // todo - rename to .width and .height
	uint32	m_y;

public:
	CSize2D(void)
	{
		m_x = 0;
		m_y = 0;
	}

	CSize2D(uint32 x, uint32 y) :
		m_x(x),
		m_y(y)
	{
	}

	uint32			width(void) { return m_x; }
	uint32			height(void) { return m_y; }

	CSize2D&		operator+(const CSize2D& vecVector2)
	{
		CSize2D vecVector;
		vecVector.m_x = m_x + vecVector2.m_x;
		vecVector.m_y = m_y + vecVector2.m_y;
		return vecVector;
	}

	CSize2D&		operator+=(const CSize2D& vecVector2)
	{
		CSize2D vecVector;
		vecVector.m_x = m_x + vecVector2.m_x;
		vecVector.m_y = m_y + vecVector2.m_y;
		return vecVector;
	}
};

#endif