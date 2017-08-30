#include "CMainWindow.h"
#include "Event/EInputEvent.h"
#include "GUI/Editors/CIMGEditor.h"
#include "Controls/CButton.h"
#include "Controls/CGrid.h"
#include "GUI/Window/CWindowManager.h"
#include "Static/CInput.h"
#include "GraphicsLibrary/CGraphicsLibrary.h"
#include "Globals.h"
#include "IMGF.h"
#include "Task/CTaskManager.h"
#include "Task/CTaskDispatchManager.h"
#include "Static/CFile.h"
#include "Static/CPath.h"
#include "Static/CString2.h"
#include "Type/Colour/CColour.h"
#include "GUI/Layers/CMainLayer.h"
#include "GUI/Layer/EMainMenuType.h"
#include "GUI/Layer/ELayer.h"
#include "Controls/CMenu.h"
#include "Controls/Entries/CMenuItem.h"

using namespace std;
using namespace bxcf;
using namespace bxgx;
using namespace bxgx::control::events;
using namespace imgf;
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
}

// item fetching
CProgressBar*		CMainWindow::getProgressBar(void)
{
	return m_pMainLayer->getProgressBar();
}

CTabBar*			CMainWindow::getTabBar(void)
{
	return m_pMainLayer->getTabBar();
}

// window initialization
void					CMainWindow::initWindow(void)
{
	addTitleBar("IMG Factory 2.0 - Development Version");
}

void					CMainWindow::initLayers(void)
{
	initMainLayer();
	initMainMenuLayers();
	initSettingsMenuLayer();
	initEditors();

	bindEventRef(RESIZE_WINDOW, &CMainWindow::repositionAndResizeControls);
	repositionAndResizeControls(Vec2i(0, 0));
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
	CMenu
		*pMenu;
	string
		strStyleGroup;

	// formats menu
	CLayer *pFormatsLayer = addLayer(FORMATS_MENU, true);

	x = 0;
	y = getTitleBarHeight() + uiButtonHeight;
	y2 = y;
	w = 139;
	h = uiButtonHeight;
	h2 = h;
	strStyleGroup = "leftMenu";

	pMenu = pFormatsLayer->addMenu(x, y, w, h, VERTICAL, strStyleGroup);
	vector<CMenuItem*> vecMenuItems = pMenu->addItems(9, "DAT", "IMG", "Item Definition", "Item Placement", "Models", "Collisions", "Textures", "Animations", "Radar");
	vecMenuItems[1]->setActive(true);

	// utility menu
	CLayer *pUtilityLayer = addLayer(UTILITY_MENU, false);

	x = 0;
	y = y2;
	w = 139;
	h = uiButtonHeight;
	h2 = h;
	strStyleGroup = "leftMenu";

	pMenu = pUtilityLayer->addMenu(x, y, w, h, VERTICAL, strStyleGroup);
	pMenu->addItems(2, "Export Game", "Mod Includer");
}

void					CMainWindow::initSettingsMenuLayer(void)
{
	int32
		x, y, w, h, h2;
	uint32
		uiButtonHeight = 37;
	string
		strStyleGroup;

	CLayer *pSettingsMenuLayer = addLayer(SETTINGS_MENU, false);

	y = getTitleBarHeight() + uiButtonHeight;
	w = 139;
	h = uiButtonHeight;
	x = getSize().x - w;
	h2 = h;
	strStyleGroup = "settingsMenu";

	//m_vecSettingsMenuButtons.resize(4);

	m_pSettingsMenu = pSettingsMenuLayer->addMenu(x, y, w, h, VERTICAL, strStyleGroup);
	m_pSettingsMenu->addItems(4, "Settings", "Websites", "Formats", "About");

	/*
	m_vecSettingsMenuButtons[0] = pSettingsMenuLayer->addButton(x, y, w, h, "Settings", strStyleGroup + " firstItemVertically");
	y += h2;
	m_vecSettingsMenuButtons[1] = pSettingsMenuLayer->addButton(x, y, w, h, "Websites", strStyleGroup);
	y += h2;
	m_vecSettingsMenuButtons[2] = pSettingsMenuLayer->addButton(x, y, w, h, "Formats", strStyleGroup);
	y += h2;
	m_vecSettingsMenuButtons[3] = pSettingsMenuLayer->addButton(x, y, w, h, "About", strStyleGroup);
	y += h2;
	*/
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
void					CMainWindow::repositionAndResizeControls(Vec2i& vecSizeDifference)
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

	m_pSettingsMenu->setPosition(Vec2i(x, y));
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