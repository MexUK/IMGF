#pragma once

#include "nsimgf.h"
#include "nsbxgx.h"
#include "Object/Manager.h"
#include "GUI/Layer/Layers/IDEInputWindow/IDEInputWindowResult.h"
#include "GUI/Layer/Layers/IPLInputWindow/IPLInputWindowResult.h"
#include "GUI/Layer/Layers/DATPathsMoverWindow/DATPathsMoverWindowResult.h"
#include "GUI/Layer/Layers/MapMoverAndIDShifterWindow/MapMoverAndIDShifterWindowResult.h"
#include "GUI/Layer/Layers/TXDOrganizerWindow/TXDOrganizerWindowResult.h"
#include "GUI/Layer/Layers/TXDBuilderWindow/TXDBuilderWindowResult.h"
#include "GUI/Layer/Layers/RenamerWindow/RenamerWindowResult.h"
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

	template <class Layer1>
	void					createContainedWindow(uint32 uiWindowWidth, uint32 uiWindowHeight, std::string strWindowTitle);

	MainWindow*				getMainWindow(void) { return m_pMainWindow; }

	IDEInputWindowResult	showIDEInputWindow(std::string strWindowTitle, std::string strDisplayedText);
	IPLInputWindowResult	showIPLInputWindow(std::string strWindowTitle, std::string strDisplayedText);
	
	void					onPressButton_IDEInputWindow(bxgx::Button *pButton);

	void					showSettingsWindow(void);
	void					showFormatsWindow(void);
	void					showWebsitesWindow(void);
	void					showAboutWindow(void);

	void					onPressButton_TopRightMenuWindow(bxgx::Button *pButton);

	DumpWindowResult					showDumpWindow(void);
	void								showSessionManagerWindow(void);
	RenamerWindowResult					showRenamerWindow(void);
	TXDBuilderWindowResult				showTXDBuilderWindow(void);
	TXDOrganizerWindowResult			showTXDOrganizerWindow(void);
	DATPathsMoverWindowResult			showDATPathsMoverWindow(void);
	MapMoverAndIDShifterWindowResult	showMapMoverAndIdShifterWindow(void);

public:
	bool								m_bWindow2Cancelled;
	IDEInputWindowResult				m_ideInputWindowResult;
	DATPathsMoverWindowResult			m_datPathsMoverWindowResult;
	MapMoverAndIDShifterWindowResult	m_mapMoverAndIDShifterWindowResult;
	TXDOrganizerWindowResult			m_txdOrganizerWindowResult;
	TXDBuilderWindowResult				m_txdBuilderWindowResult;
	RenamerWindowResult					m_renamerWindowResult;

private:
	MainWindow*							m_pMainWindow;
};

// window creation
template <class Layer1>
void					imgf::WindowManager::createContainedWindow(uint32 uiWindowWidth, uint32 uiWindowHeight, std::string strWindowTitle)
{
	m_bWindow2Cancelled = true;
	getIMGF()->getTaskManager()->onPauseTask();
	BXGX::get()->createContainedWindow<Layer1>(uiWindowWidth, uiWindowHeight, strWindowTitle);
	getIMGF()->getTaskManager()->onResumeTask();
}