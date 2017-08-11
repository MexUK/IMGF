#ifndef CWindowManager_H
#define CWindowManager_H

#include "Object/CManager.h"

class CIMGFWindow;

class CWindowManager : public bxcf::CManager
{
public:
	CWindowManager(void);

	void					init(void);
	void					uninit(void);

	CIMGFWindow*			openWindow(void);

	void					processWindows(void);

	CIMGFWindow*			getMainWindow(void) { return m_pMainWindow; }

private:
	CIMGFWindow*			m_pMainWindow;
};

#endif