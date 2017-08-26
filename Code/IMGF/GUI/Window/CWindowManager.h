#pragma once

#include "Object/CManager.h"

class CMainWindow;

class CWindowManager : public bxcf::CManager
{
public:
	CWindowManager(void);

	void					init(void);
	void					uninit(void);

	CMainWindow*			openWindow(void);

	void					process(void);

	CMainWindow*			getMainWindow(void) { return m_pMainWindow; }

private:
	CMainWindow*			m_pMainWindow;
};