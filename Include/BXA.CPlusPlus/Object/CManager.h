#ifndef CManager_H
#define CManager_H

#include "BXA.h"

class bxa::CManager
{
public:
	virtual void				init(void) = 0;
	virtual void				uninit(void) = 0;
};

#endif