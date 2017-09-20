#pragma once

#include "nsimgf.h"
#include "nsbxgx.h"
#include "Object/Manager.h"
#include "GUI/Layer/Layers/IDEInputWindow/IDEInputWindowResult.h"
#include "GUI/Layer/Layers/IPLInputWindow/IPLInputWindowResult.h"
#include "Event/EventBindable.h"

class imgf::MainWindow;

class imgf::WindowManager : public bxcf::Manager, public bxcf::EventBindable
{
public:
	WindowManager(void);

	void					init(void);
	void					uninit(void);

	MainWindow*				openWindow(void);

	void					process(void);

	MainWindow*				getMainWindow(void) { return m_pMainWindow; }

	IDEInputWindowResult	showIDEInputWindow(std::string strWindowTitle, std::string strDisplayedText);
	IPLInputWindowResult	showIPLInputWindow(std::string strWindowTitle, std::string strDisplayedText);
	
	void					onPressButton_IDEInputWindow(bxgx::Button *pButton);

	void					showSettingsWindow(void);
	void					showFormatsWindow(void);
	void					showWebsitesWindow(void);
	void					showAboutWindow(void);

	void					onPressButton_TopRightMenuWindow(bxgx::Button *pButton);

public:
	bool					m_bWindow2Cancelled;
	IDEInputWindowResult	m_ideInputWindowResult;

private:
	MainWindow*				m_pMainWindow;
};