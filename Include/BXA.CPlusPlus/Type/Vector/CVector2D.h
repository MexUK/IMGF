#ifndef CVector2D_H
#define CVector2D_H

#include "BXA.h"
#include "Type/Types.h"

class bxa::CVector2D
{
public:
	float32	m_x;	// todo - rename to .x and .y
	float32	m_y;
	
public:
	bxa::CVector2D(void);
	bxa::CVector2D(int32 iX, int32 iY);
	bxa::CVector2D(float32 fX, float32 fY);
};

#endif