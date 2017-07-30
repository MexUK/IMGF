#ifndef CManager_H
#define CManager_H

#include "bxcf.h"

class bxcf::CManager
{
public:
	virtual void				init(void) = 0;
	virtual void				uninit(void) = 0;
};

#endif