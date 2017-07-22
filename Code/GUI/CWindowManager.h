#ifndef CWindowManager_H
#define CWindowManager_H

#include "Object/CManager.h"

class CWindow;

class CWindowManager : public bxa::CManager
{
public:
	void					init(void);
	void					uninit(void);

	CWindow*				openWindow(void);

	void					processWindows(void);
};

#endif