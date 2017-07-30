#ifndef CVector4D_H
#define CVector4D_H

#define _USE_MATH_DEFINES

#include "bxcf.h"
#include "Type/Types.h"
#include <math.h>

class bxcf::CVector4D
{
public:
	float32	m_x;	// todo - rename to .x and .y and .z and .w
	float32	m_y;
	float32	m_z;
	float32	m_w;
	
public:
	bxcf::CVector4D(void);
	bxcf::CVector4D(float32 fX, float32 fY, float32 fZ, float32 fW);
};

#endif