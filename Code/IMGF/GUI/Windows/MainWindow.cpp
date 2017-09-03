#include "MainWindow.h"
#include "Event/EInputEvent.h"
#include "GUI/Editors/IMGEditor.h"
#include "Control/Controls/Button.h"
#include "Control/Controls/Grid.h"
#include "GUI/Window/WindowManager.h"
#include "Static/Input.h"
#include "GraphicsLibrary/Base/GraphicsLibrary.h"
#include "Globals.h"
#include "IMGF.h"
#include "Task/TaskManager.h"
#include "Task/TaskDispatchManager.h"
#include "Static/File.h"
#include "Static/Path.h"
#include "Static/String.h"
#include "Type/Colour/Colour.h"
#include "GUI/Layers/MainLayer.h"
#include "GUI/Layer/EMainMenuType.h"
#include "GUI/Layer/ELayer.h"
#include "Control/Controls/Menu.h"
#include "Control/Entries/MenuItem.h"

using namespace std;
using namespace bxcf;
using namespace bxgx;
using namespace bxgx::control::events;
using namespace imgf;
using namespace imgf::mainLayer::mainMenuType;
using namespace imgf::layers;

MainWindow::MainWindow(void) :
	m_uiMainMenuType(FORMATS),
	m_pMainLayer(nullptr),
	m_pIMGEditor(nullptr)
{
}

// main interface
void					MainWindow::init(void)
{
	initWindow();
	initLayers();
}

// item fetching
ProgressBar*		MainWindow::getProgressBar(void)
{
	return m_pMainLayer->getProgressBar();
}

TabBar*			MainWindow::getTabBar(void)
{
	return m_pMainLayer->getTabBar();
}

// window initialization
void					MainWindow::initWindow(void)
{
	addTitleBar("IMG Factory 2.0 - Development Version");
}

void					MainWindow::initLayers(void)
{
	initMainLayer();
	initMainMenuLayers();
	initSettingsMenuLayer();
	initEditors();

	bindEventRef(RESIZE_WINDOW, &MainWindow::repositionAndResizeControls);
	repositionAndResizeControls(Vec2i(0, 0));
}

// layer initialization
void					MainWindow::initMainLayer(void)
{
	m_pMainLayer = addLayer<MainLayer>(-1, true);
	m_pMainLayer->setIMGFWindow(this);
	m_pMainLayer->init();
}

void					MainWindow::initMainMenuLayers(void)
{
	int32
		x, y, y2, w, h, h2;
	uint32
		uiButtonHeight = 37;
	Menu
		*pMenu;
	string
		strStyleGroup;

	// formats menu
	Layer *pFormatsLayer = addLayer(FORMATS_MENU, true);

	x = 0;
	y = getTitleBarHeight() + uiButtonHeight;
	y2 = y;
	w = 139;
	h = uiButtonHeight;
	h2 = h;
	strStyleGroup = "leftMenu";

	pMenu = pFormatsLayer->addMenu(x, y, w, h, VERTICAL, strStyleGroup, -1, -100);
	vector<MenuItem*> vecMenuItems = pMenu->addMenuItems(9, "DAT", "IMG", "Item Definition", "Item Placement", "Models", "Collisions", "Textures", "Animations", "Radar");
	pMenu->setActiveMenuItem(vecMenuItems[1]);

	// utility menu
	Layer *pUtilityLayer = addLayer(UTILITY_MENU, false);

	x = 0;
	y = y2;
	w = 139;
	h = uiButtonHeight;
	h2 = h;
	strStyleGroup = "leftMenu";

	pMenu = pUtilityLayer->addMenu(x, y, w, h, VERTICAL, strStyleGroup, -1, -100);
	pMenu->addMenuItems(2, "Export Game", "Mod Includer");
}

void					MainWindow::initSettingsMenuLayer(void)
{
	int32
		x, y, w, h, h2;
	uint32
		uiButtonHeight = 37;
	string
		strStyleGroup;

	Layer *pSettingsMenuLayer = addLayer(SETTINGS_MENU, false);

	y = getTitleBarHeight() + uiButtonHeight;
	w = 139;
	h = uiButtonHeight;
	x = getSize().x - w;
	h2 = h;
	strStyleGroup = "settingsMenu";

	//m_vecSettingsMenuButtons.resize(4);

	m_pSettingsMenu = pSettingsMenuLayer->addMenu(x, y, w, h, VERTICAL, strStyleGroup, -1, -100);
	m_pSettingsMenu->addMenuItems(4, "Settings", "Websites", "Formats", "About");

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

void					MainWindow::initEditors(void)
{
	//m_pDATEditor = addLayer<DATEditor>(-1, false);
	m_pIMGEditor = addLayer<IMGEditor>(-1, true);

	//m_pDATEditor->setMainWindow(this);
	m_pIMGEditor->setMainWindow(this);

	//m_pDATEditor->init();
	m_pIMGEditor->init();
}

// layer repositioning and resizing
void					MainWindow::repositionAndResizeControls(Vec2i& vecSizeDifference)
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
void					MainWindow::setMainMenuType(EMainMenuType uiMainMenuType)
{
	if (uiMainMenuType == m_uiMainMenuType)
	{
		return;
	}

	m_uiMainMenuType = uiMainMenuType;
	swapLayersEnabled(FORMATS_MENU, UTILITY_MENU);
}