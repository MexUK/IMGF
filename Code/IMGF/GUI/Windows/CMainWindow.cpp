#include "CMainWindow.h"
#include "GUI/Editors/CIMGEditor.h"
#include "Controls/CButtonControl.h"
#include "Controls/CGridControl.h"
#include "Styles/CGUIStyles.h"
#include "GUI/Window/CWindowManager.h"
#include "Static/CInput.h"
#include "GraphicsLibrary/CGraphicsLibrary.h"
#include "Event/CEventManager.h"
#include "Event/eEvent.h"
#include "Globals.h"
#include "CIMGF.h"
#include "Task/CTaskManager.h"
#include "Task/CTaskDispatchManager.h"
#include "Static/CFile.h"
#include "Static/CPath.h"
#include "Static/CString2.h"
#include "Type/Colour/CColour.h"
#include "GUI/Layers/CMainLayer.h"
#include "GUI/Layer/EMainMenuType.h"
#include "GUI/Layer/ELayers.h"

using namespace std;
using namespace bxcf;
using namespace imgf::mainLayer::mainMenuType;
using namespace imgf::layers;

CMainWindow::CMainWindow(void) :
	m_uiMainMenuType(FORMATS),
	m_pMainLayer(nullptr),
	m_pIMGEditor(nullptr)
{
}

// main interface
void					CMainWindow::init(void)
{
	initWindow();
	initLayers();
	CWindow::bindEvents();
}

// item fetching
CProgressControl*		CMainWindow::getProgressBar(void)
{
	return m_pMainLayer->getProgressBar();
}

CTabBarControl*			CMainWindow::getTabBar(void)
{
	return m_pMainLayer->getTabBar();
}

// window initialization
void					CMainWindow::initWindow(void)
{
	CWindow::init();

	addTitleBar("IMG Factory 2.0 - Development Version");
}

void					CMainWindow::initLayers(void)
{
	initMainLayer();
	initMainMenuLayers();
	initSettingsMenuLayer();
	initEditors();

	CEventManager::get()->bindEvent(EVENT_onResizeWindow, [](void* pArg1, void* pArg2) {
		((CMainWindow*)pArg1)->repositionAndResizeControls();
	}, this);
	repositionAndResizeControls();
}

// layer initialization
void					CMainWindow::initMainLayer(void)
{
	m_pMainLayer = addLayer<CMainLayer>(-1, true);
	m_pMainLayer->setIMGFWindow(this);
	m_pMainLayer->init();
}

void					CMainWindow::initMainMenuLayers(void)
{
	int32
		x, y, y2, w, h, h2;
	uint32
		uiButtonHeight = 37;
	CButtonControl
		*pButton;
	string
		strStyleGroup;

	// formats menu
	CGUILayer *pFormatsLayer = addLayer(FORMATS_MENU, true);

	x = 0;
	y = getTitleBarHeight() + uiButtonHeight;
	y2 = y;
	w = 139;
	h = uiButtonHeight;
	h2 = h;
	strStyleGroup = "leftMenuButton";

	pButton = pFormatsLayer->addButton(x, y, w, h, "DAT", strStyleGroup);
	y += h2;
	pButton = pFormatsLayer->addButton(x, y, w, h, "IMG", "activeLeftMenuButton " + strStyleGroup);
	y += h2;
	pButton = pFormatsLayer->addButton(x, y, w, h, "Item Definition", strStyleGroup);
	y += h2;
	pButton = pFormatsLayer->addButton(x, y, w, h, "Item Placement", strStyleGroup);
	y += h2;
	pButton = pFormatsLayer->addButton(x, y, w, h, "Models", strStyleGroup);
	y += h2;
	pButton = pFormatsLayer->addButton(x, y, w, h, "Collisions", strStyleGroup);
	y += h2;
	pButton = pFormatsLayer->addButton(x, y, w, h, "Textures", strStyleGroup);
	y += h2;
	pButton = pFormatsLayer->addButton(x, y, w, h, "Animations", strStyleGroup);
	y += h2;
	pButton = pFormatsLayer->addButton(x, y, w, h, "Radar", strStyleGroup);

	// utility menu
	CGUILayer *pUtilityLayer = addLayer(UTILITY_MENU, false);

	x = 0;
	y = y2;
	w = 139;
	h = uiButtonHeight;
	h2 = h;
	strStyleGroup = "leftMenuButton";

	pButton = pUtilityLayer->addButton(x, y, w, h, "Export Game", strStyleGroup);
	y += h2;
	pButton = pUtilityLayer->addButton(x, y, w, h, "Mod Includer", strStyleGroup);
	y += h2;
}

void					CMainWindow::initSettingsMenuLayer(void)
{
	int32
		x, y, w, h, h2;
	uint32
		uiButtonHeight = 37;
	string
		strStyleGroup;

	CGUILayer *pSettingsMenuLayer = addLayer(SETTINGS_MENU, false);

	y = getTitleBarHeight() + uiButtonHeight;
	w = 139;
	h = uiButtonHeight;
	x = getSize().x - w;
	h2 = h;
	strStyleGroup = "settingsMenuButton";

	m_vecSettingsMenuButtons.resize(4);

	m_vecSettingsMenuButtons[0] = pSettingsMenuLayer->addButton(x, y, w, h, "Settings", strStyleGroup + " firstItemVertically");
	y += h2;
	m_vecSettingsMenuButtons[1] = pSettingsMenuLayer->addButton(x, y, w, h, "Websites", strStyleGroup);
	y += h2;
	m_vecSettingsMenuButtons[2] = pSettingsMenuLayer->addButton(x, y, w, h, "Formats", strStyleGroup);
	y += h2;
	m_vecSettingsMenuButtons[3] = pSettingsMenuLayer->addButton(x, y, w, h, "About", strStyleGroup);
	y += h2;
}

void					CMainWindow::initEditors(void)
{
	//m_pDATEditor = addLayer<CDATEditor>(-1, false);
	m_pIMGEditor = addLayer<CIMGEditor>(-1, true);

	//m_pDATEditor->setMainWindow(this);
	m_pIMGEditor->setMainWindow(this);

	//m_pDATEditor->init();
	m_pIMGEditor->init();
}

// layer repositioning and resizing
void					CMainWindow::repositionAndResizeControls(void)
{
	int32
		x, y, w, h;
	uint32
		uiButtonHeight = 37;

	// settings menu buttons
	y = getTitleBarHeight() + uiButtonHeight;
	w = 139;
	h = uiButtonHeight;
	x = getSize().x - w;

	for (CButtonControl *pButton : m_vecSettingsMenuButtons)
	{
		pButton->setPosition(Vec2i(x, y));
		y += h;
	}
}

// main menu type
void					CMainWindow::setMainMenuType(EMainMenuType uiMainMenuType)
{
	if (uiMainMenuType == m_uiMainMenuType)
	{
		return;
	}
	m_uiMainMenuType = uiMainMenuType;
	swapLayersEnabled(FORMATS_MENU, UTILITY_MENU);
}