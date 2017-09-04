#pragma once

#include "nsbxcf.h"

class bxcf::CManager
{
public:
	virtual void				init(void) = 0;
	virtual void				uninit(void) = 0;
};