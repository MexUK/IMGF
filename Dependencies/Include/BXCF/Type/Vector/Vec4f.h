#pragma once

#define _USE_MATH_DEFINES

#include "bxcf.h"
#include "Type/Types.h"
#include <math.h>

class bxcf::Vec4f
{
public:
	float32	x;
	float32	y;
	float32	z;
	float32	w;
	
public:
	Vec4f(void);
	Vec4f(float32 fX, float32 fY, float32 fZ, float32 fW);
};