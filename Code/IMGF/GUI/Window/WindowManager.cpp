#include "WindowManager.h"
#include "nsbxgx.h"
#include "BXGX.h"
#include "GUI/Window/Windows/MainWindow/MainWindow.h"
#include "GUI/Editor/Editors/IMGEditor.h"
#include "../../Compiler/Projects/IMGF/resource.h"
#include "GUI/Layer/Layers/IDEInputWindow/IDEInputLayer.h"
#include "GUI/Layer/Layers/IPLInputWindow/IPLInputLayer.h"
#include "GUI/Layer/Layers/FormatsWindow/FormatsWindowLayer.h"
#include "GUI/Layer/Layers/AboutWindow/AboutWindowLayer.h"
#include "GUI/Layer/Layers/WebsitesWindow/WebsitesWindowLayer.h"
#include "GUI/Layer/Layers/SettingsWindow/SettingsWindowLayer.h"
#include "GUI/Layer/Layers/DumpWindow/DumpWindowLayer.h"
#include "GUI/Layer/Layers/SessionManagerWindow/SessionManagerWindowLayer.h"
#include "GUI/Layer/Layers/RenamerWindow/RenamerWindowLayer.h"
#include "GUI/Layer/Layers/TXDBuilderWindow/TXDBuilderWindowLayer.h"
#include "GUI/Layer/Layers/TXDOrganizerWindow/TXDOrganizerWindowLayer.h"
#include "GUI/Layer/Layers/DATPathsMoverWindow/DATPathsMoverWindowLayer.h"
#include "GUI/Layer/Layers/MapMoverAndIDShifterWindow/MapMoverAndIDShifterWindowLayer.h"
#include "Control/Controls/Button.h"
#include "Control/Controls/CheckBox.h"
#include "Control/Controls/Text.h"
#include "Static/Input.h"
#include "Task/Tasks/Tasks.h"
#include "IMGF.h"
#include <string>

using namespace std;
using namespace bxcf;
using namespace bxgx;
using namespace bxgx::events;
using namespace imgf;

WindowManager::WindowManager(void) :
	m_pMainWindow(nullptr),
	m_bWindow2Cancelled(true)
{
	m_ideInputWindowResult = IDEInputWindowResult();
}

// main interface
void					WindowManager::init(void)
{
}

void					WindowManager::uninit(void)
{
}

// window open/close
MainWindow*				WindowManager::openWindow(void)
{
	LPWSTR pIcon = MAKEINTRESOURCE(IDI_ICON1);
	uint32 uiIcon = (uint32) pIcon;

	m_pMainWindow = bxgx::get()->addWindow<MainWindow>(-1, -1, 1300, 800, uiIcon);
	if (!m_pMainWindow)
	{
		return nullptr;
	}

	return m_pMainWindow;
}

// window processing
void					WindowManager::process(void)
{
	bxgx::get()->process();
}

// window input
void					WindowManager::onPressButton_IDEInputWindow(Button *pButton)
{
	Window
		*pWindow1 = BXGX::get()->getEntryByIndex(0),
		*pWindow2 = BXGX::get()->getEntryByIndex(1);

	if (pButton->getId() == 100)
	{
		// Select all
		for (uint32 uiCheckBoxId = 300; uiCheckBoxId <= 500; uiCheckBoxId++)
		{
			RenderItem *pRenderItem = pWindow2->getItemById(uiCheckBoxId);
			if (pRenderItem)
			{
				CheckBox *pCheckBox = (CheckBox*)pRenderItem;
				pCheckBox->setMarked(true);
			}
		}
		return;
	}
	else if (pButton->getId() == 110)
	{
		// Unselect all
		for (uint32 uiCheckBoxId = 300; uiCheckBoxId <= 500; uiCheckBoxId++)
		{
			RenderItem *pRenderItem = pWindow2->getItemById(uiCheckBoxId);
			if (pRenderItem)
			{
				CheckBox *pCheckBox = (CheckBox*)pRenderItem;
				pCheckBox->setMarked(false);
			}
		}
		return;
	}
	else if (pButton->getId() == 200)
	{
		// OK
		bool bAtLeastOneCheckBoxIsMarked = false;
		for (uint32 uiCheckBoxId = 300; uiCheckBoxId <= 500; uiCheckBoxId++)
		{
			RenderItem *pRenderItem = pWindow2->getItemById(uiCheckBoxId);
			if (pRenderItem)
			{
				CheckBox *pCheckBox = (CheckBox*)pRenderItem;
				if (pCheckBox->isMarked())
				{
					bAtLeastOneCheckBoxIsMarked = true;
					break;
				}
			}
		}
		if (!bAtLeastOneCheckBoxIsMarked)
		{
			Tasks::showMessage("At least one check box must be marked.", "Input Error", MB_OK);
			return;
		}
		else
		{
			m_bWindow2Cancelled = false;

			for (uint32 uiCheckBoxId = 300; uiCheckBoxId <= 500; uiCheckBoxId++)
			{
				RenderItem *pRenderItem = pWindow2->getItemById(uiCheckBoxId);
				if(pRenderItem)
				{
					CheckBox *pCheckBox = (CheckBox*)pRenderItem;
					m_ideInputWindowResult.m_umapCheckBoxStatuses[uiCheckBoxId] = pCheckBox->isMarked();
				}
			}
		}
	}

	BXGX::get()->m_vecWindowsToDestroy.push_back(pWindow2);
}

// windows
IDEInputWindowResult	WindowManager::showIDEInputWindow(string strWindowTitle, string strDisplayedText)
{
	m_bWindow2Cancelled = true;

	Window *pWindow = BXGX::get()->addWindow(500, 460);
	IDEInputLayer *pLayer = pWindow->addLayer<IDEInputLayer>();
	pLayer->init();

	pWindow->addTitleBar(strWindowTitle);
	pLayer->m_pText->setText(strDisplayedText);

	pWindow->render();

	getIMGF()->getTaskManager()->onPauseTask();
	bindEvent(PRESS_BUTTON, &WindowManager::onPressButton_IDEInputWindow);
	while (BXGX::get()->m_vecWindowsToInitialize.size() > 0 || BXGX::get()->getEntryCount() > 1)
	{
		BXGX::get()->process2ndThreadOnce();
	}
	unbindEvent(PRESS_BUTTON, &WindowManager::onPressButton_IDEInputWindow);
	getIMGF()->getTaskManager()->onResumeTask();

	return m_ideInputWindowResult;
}

IPLInputWindowResult	WindowManager::showIPLInputWindow(string strWindowTitle, string strDisplayedText)
{
	// todo - function needed?
	m_bWindow2Cancelled = true;

	Window *pWindow = BXGX::get()->addWindow(500, 460);
	IPLInputLayer *pLayer = pWindow->addLayer<IPLInputLayer>();
	pLayer->init();

	pWindow->addTitleBar(strWindowTitle);
	pLayer->m_pText->setText(strDisplayedText);

	pWindow->render();

	getIMGF()->getTaskManager()->onPauseTask();
	bindEvent(PRESS_BUTTON, &WindowManager::onPressButton_IDEInputWindow);
	while (BXGX::get()->m_vecWindowsToInitialize.size() > 0 || BXGX::get()->getEntryCount() > 1)
	{
		BXGX::get()->process2ndThreadOnce();
	}
	unbindEvent(PRESS_BUTTON, &WindowManager::onPressButton_IDEInputWindow);
	getIMGF()->getTaskManager()->onResumeTask();

	return IPLInputWindowResult();
}

// top right menu windows
void					WindowManager::showSettingsWindow(void)
{
	m_bWindow2Cancelled = true;

	if (m_pMainWindow->getActiveEditor()->getActiveEditorTab())
	{
		m_pMainWindow->getActiveEditor()->getActiveEditorTab()->unbindEvents();
	}

	Window *pWindow = BXGX::get()->addWindow(750, 510);
	SettingsWindowLayer *pLayer = pWindow->addLayer<SettingsWindowLayer>();

	pWindow->addTitleBar("Settings");
	pLayer->init();

	while (((Text*)pLayer->getItemById(520))->getTextWidth() == 0) // todo - waitForBlah()
	{
		Sleep(100);
	}

	pWindow->render();

	getIMGF()->getTaskManager()->onPauseTask();
	bindEvent(PRESS_BUTTON, &WindowManager::onPressButton_TopRightMenuWindow);
	while (BXGX::get()->m_vecWindowsToInitialize.size() > 0 || BXGX::get()->getEntryCount() > 1)
	{
		BXGX::get()->process2ndThreadOnce();
	}
	unbindEvent(PRESS_BUTTON, &WindowManager::onPressButton_TopRightMenuWindow);
	getIMGF()->getTaskManager()->onResumeTask();

	if (m_pMainWindow->getActiveEditor()->getActiveEditorTab())
	{
		m_pMainWindow->getActiveEditor()->getActiveEditorTab()->bindEvents();
	}
}

void					WindowManager::showFormatsWindow(void)
{
	m_bWindow2Cancelled = true;

	if (m_pMainWindow->getActiveEditor()->getActiveEditorTab())
	{
		m_pMainWindow->getActiveEditor()->getActiveEditorTab()->unbindEvents();
	}

	Window *pWindow = BXGX::get()->addWindow(650, 510);
	FormatsWindowLayer *pLayer = pWindow->addLayer<FormatsWindowLayer>();
	
	pWindow->addTitleBar("Formats");
	pLayer->init();

	pWindow->render();

	getIMGF()->getTaskManager()->onPauseTask();
	bindEvent(PRESS_BUTTON, &WindowManager::onPressButton_TopRightMenuWindow);
	while (BXGX::get()->m_vecWindowsToInitialize.size() > 0 || BXGX::get()->getEntryCount() > 1)
	{
		BXGX::get()->process2ndThreadOnce();
	}
	unbindEvent(PRESS_BUTTON, &WindowManager::onPressButton_TopRightMenuWindow);
	getIMGF()->getTaskManager()->onResumeTask();

	if (m_pMainWindow->getActiveEditor()->getActiveEditorTab())
	{
		m_pMainWindow->getActiveEditor()->getActiveEditorTab()->bindEvents();
	}
}

void					WindowManager::showWebsitesWindow(void)
{
	m_bWindow2Cancelled = true;

	if (m_pMainWindow->getActiveEditor()->getActiveEditorTab())
	{
		m_pMainWindow->getActiveEditor()->getActiveEditorTab()->unbindEvents();
	}

	Window *pWindow = BXGX::get()->addWindow(700, 300);
	WebsitesWindowLayer *pLayer = pWindow->addLayer<WebsitesWindowLayer>();

	pWindow->addTitleBar("Websites");
	pLayer->init();

	pWindow->render();

	getIMGF()->getTaskManager()->onPauseTask();
	bindEvent(PRESS_BUTTON, &WindowManager::onPressButton_TopRightMenuWindow);
	while (BXGX::get()->m_vecWindowsToInitialize.size() > 0 || BXGX::get()->getEntryCount() > 1)
	{
		BXGX::get()->process2ndThreadOnce();
	}
	unbindEvent(PRESS_BUTTON, &WindowManager::onPressButton_TopRightMenuWindow);
	getIMGF()->getTaskManager()->onResumeTask();

	if (m_pMainWindow->getActiveEditor()->getActiveEditorTab())
	{
		m_pMainWindow->getActiveEditor()->getActiveEditorTab()->bindEvents();
	}
}

void					WindowManager::showAboutWindow(void)
{
	m_bWindow2Cancelled = true;

	if (m_pMainWindow->getActiveEditor()->getActiveEditorTab())
	{
		m_pMainWindow->getActiveEditor()->getActiveEditorTab()->unbindEvents();
	}

	Window *pWindow = BXGX::get()->addWindow(650, 620);
	AboutWindowLayer *pLayer = pWindow->addLayer<AboutWindowLayer>();

	pWindow->addTitleBar("About");
	pLayer->init();

	pWindow->render();

	getIMGF()->getTaskManager()->onPauseTask();
	bindEvent(PRESS_BUTTON, &WindowManager::onPressButton_TopRightMenuWindow);
	while (BXGX::get()->m_vecWindowsToInitialize.size() > 0 || BXGX::get()->getEntryCount() > 1)
	{
		BXGX::get()->process2ndThreadOnce();
	}
	unbindEvent(PRESS_BUTTON, &WindowManager::onPressButton_TopRightMenuWindow);
	getIMGF()->getTaskManager()->onResumeTask();

	if (m_pMainWindow->getActiveEditor()->getActiveEditorTab())
	{
		m_pMainWindow->getActiveEditor()->getActiveEditorTab()->bindEvents();
	}
}

// top right menu window input
void					WindowManager::onPressButton_TopRightMenuWindow(Button *pButton)
{
	Window
		*pWindow1 = BXGX::get()->getEntryByIndex(0),
		*pWindow2 = BXGX::get()->getEntryByIndex(1);

	if (pButton->getId() == 200)
	{
		BXGX::get()->m_vecWindowsToDestroy.push_back(pWindow2);
	}
}

// other task windows
DumpWindowResult		WindowManager::showDumpWindow(void)
{
	m_bWindow2Cancelled = true;

	Window *pWindow = BXGX::get()->addWindow(750, 600);
	DumpWindowLayer *pLayer = pWindow->addLayer<DumpWindowLayer>();

	pWindow->addTitleBar("Dump");
	pLayer->init();

	pWindow->render();

	getIMGF()->getTaskManager()->onPauseTask();
	while (BXGX::get()->m_vecWindowsToInitialize.size() > 0 || BXGX::get()->getEntryCount() > 1)
	{
		BXGX::get()->process2ndThreadOnce();
	}
	getIMGF()->getTaskManager()->onResumeTask();

	return getMainWindow()->m_dumpWindowResult;
}

void					WindowManager::showSessionManagerWindow(void)
{
	m_bWindow2Cancelled = true;

	Window *pWindow = BXGX::get()->addWindow(750, 650);
	SessionManagerWindowLayer *pLayer = pWindow->addLayer<SessionManagerWindowLayer>();

	pWindow->addTitleBar("Session Manager");
	pLayer->init();

	pWindow->render();

	getIMGF()->getTaskManager()->onPauseTask();
	while (BXGX::get()->m_vecWindowsToInitialize.size() > 0 || BXGX::get()->getEntryCount() > 1)
	{
		BXGX::get()->process2ndThreadOnce();
	}
	getIMGF()->getTaskManager()->onResumeTask();
}

RenamerWindowResult				WindowManager::showRenamerWindow(void)
{
	m_bWindow2Cancelled = true;

	Window *pWindow = BXGX::get()->addWindow(800, 750);
	RenamerWindowLayer *pLayer = pWindow->addLayer<RenamerWindowLayer>();

	pWindow->addTitleBar("Renamer");
	pLayer->init();

	pWindow->render();

	getIMGF()->getTaskManager()->onPauseTask();
	while (BXGX::get()->m_vecWindowsToInitialize.size() > 0 || BXGX::get()->getEntryCount() > 1)
	{
		BXGX::get()->process2ndThreadOnce();
	}
	getIMGF()->getTaskManager()->onResumeTask();

	return m_renamerWindowResult;
}

TXDBuilderWindowResult			WindowManager::showTXDBuilderWindow(void)
{
	m_bWindow2Cancelled = true;

	Window *pWindow = BXGX::get()->addWindow(750, 750);
	TXDBuilderWindowLayer *pLayer = pWindow->addLayer<TXDBuilderWindowLayer>();

	pWindow->addTitleBar("TXD Builder");
	pLayer->init();

	pWindow->render();

	getIMGF()->getTaskManager()->onPauseTask();
	while (BXGX::get()->m_vecWindowsToInitialize.size() > 0 || BXGX::get()->getEntryCount() > 1)
	{
		BXGX::get()->process2ndThreadOnce();
	}
	getIMGF()->getTaskManager()->onResumeTask();

	return m_txdBuilderWindowResult;
}

TXDOrganizerWindowResult		WindowManager::showTXDOrganizerWindow(void)
{
	m_bWindow2Cancelled = true;

	Window *pWindow = BXGX::get()->addWindow(850, 400);
	TXDOrganizerWindowLayer *pLayer = pWindow->addLayer<TXDOrganizerWindowLayer>();

	pWindow->addTitleBar("TXD Organizer");
	pLayer->init();

	pWindow->render();

	getIMGF()->getTaskManager()->onPauseTask();
	while (BXGX::get()->m_vecWindowsToInitialize.size() > 0 || BXGX::get()->getEntryCount() > 1)
	{
		BXGX::get()->process2ndThreadOnce();
	}
	getIMGF()->getTaskManager()->onResumeTask();

	return m_txdOrganizerWindowResult;
}

DATPathsMoverWindowResult			WindowManager::showDATPathsMoverWindow(void)
{
	m_bWindow2Cancelled = true;

	Window *pWindow = BXGX::get()->addWindow(750, 600);
	DATPathsMoverWindowLayer *pLayer = pWindow->addLayer<DATPathsMoverWindowLayer>();

	pWindow->addTitleBar("DAT Paths Mover - Currently only works with fastman92's path format");
	pLayer->init();

	pWindow->render();

	getIMGF()->getTaskManager()->onPauseTask();
	while (BXGX::get()->m_vecWindowsToInitialize.size() > 0 || BXGX::get()->getEntryCount() > 1)
	{
		BXGX::get()->process2ndThreadOnce();
	}
	getIMGF()->getTaskManager()->onResumeTask();

	return m_datPathsMoverWindowResult;
}

MapMoverAndIDShifterWindowResult					WindowManager::showMapMoverAndIdShifterWindow(void)
{
	m_bWindow2Cancelled = true;

	Window *pWindow = BXGX::get()->addWindow(750, 650);
	MapMoverAndIDShifterWindowLayer *pLayer = pWindow->addLayer<MapMoverAndIDShifterWindowLayer>();

	pWindow->addTitleBar("Map Mover and ID Shifter");
	pLayer->init();

	pWindow->render();

	getIMGF()->getTaskManager()->onPauseTask();
	while (BXGX::get()->m_vecWindowsToInitialize.size() > 0 || BXGX::get()->getEntryCount() > 1)
	{
		BXGX::get()->process2ndThreadOnce();
	}
	getIMGF()->getTaskManager()->onResumeTask();

	return m_mapMoverAndIDShifterWindowResult;
}