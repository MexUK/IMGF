#ifndef CVector2D_H
#define CVector2D_H

#include "mcore.h"
#include "Type/Types.h"

class mcore::CVector2D
{
public:
	float32	m_x;	// todo - rename to .x and .y
	float32	m_y;
	
public:
	mcore::CVector2D(void);
	mcore::CVector2D(int32 iX, int32 iY);
	mcore::CVector2D(float32 fX, float32 fY);
};

#endif