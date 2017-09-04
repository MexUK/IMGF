#pragma once

#include "nsbxcf.h"

class bxcf::Number
{
public:
	static bool								isInRange(double dNumber, double dMin, double dMax);
	static bool								isInteger(double dNumber);
	static unsigned long					reverseUlong(unsigned long uiNumber);
	static unsigned long					getRandomColour(void);
};