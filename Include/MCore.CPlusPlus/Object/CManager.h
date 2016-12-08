#ifndef CManager_H
#define CManager_H

#include "mcore.h"

class mcore::CManager
{
public:
	virtual void				init(void) = 0;
	virtual void				uninit(void) = 0;
};

#endif