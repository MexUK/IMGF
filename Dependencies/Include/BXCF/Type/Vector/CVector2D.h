#ifndef CVector2D_H
#define CVector2D_H

#include "bxcf.h"
#include "Type/Types.h"

class bxcf::CVector2D
{
public:
	float32	m_x;	// todo - rename to .x and .y
	float32	m_y;
	
public:
	bxcf::CVector2D(void);
	bxcf::CVector2D(int32 iX, int32 iY);
	bxcf::CVector2D(float32 fX, float32 fY);
};

#endif