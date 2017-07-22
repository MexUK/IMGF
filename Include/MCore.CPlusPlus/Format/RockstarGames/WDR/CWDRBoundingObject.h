#ifndef CWDRBoundingObject_H
#define CWDRBoundingObject_H

#include "bxa.h"

class bxa::CWDRBoundingObject
{
public:
	float32					m_fMin[4]; // x y z w
	float32					m_fMax[4]; // x y z w
};

#endif