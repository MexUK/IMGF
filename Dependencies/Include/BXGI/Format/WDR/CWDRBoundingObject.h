#ifndef CWDRBoundingObject_H
#define CWDRBoundingObject_H

#include "bxgi.h"

class bxgi::CWDRBoundingObject
{
public:
	float32					m_fMin[4]; // x y z w
	float32					m_fMax[4]; // x y z w
};

#endif