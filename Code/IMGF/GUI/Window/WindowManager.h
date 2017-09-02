#pragma once

#include "nsimgf.h"
#include "Object/CManager.h"

class imgf::MainWindow;

class imgf::WindowManager : public bxcf::CManager
{
public:
	WindowManager(void);

	void					init(void);
	void					uninit(void);

	MainWindow*			openWindow(void);

	void					process(void);

	MainWindow*			getMainWindow(void) { return m_pMainWindow; }

private:
	MainWindow*			m_pMainWindow;
};