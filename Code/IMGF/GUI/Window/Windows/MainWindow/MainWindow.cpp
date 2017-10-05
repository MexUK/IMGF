#include "MainWindow.h"
#include "Event/EInputEvent.h"
#include "GUI/Editor/Editors/IMGEditor.h"
#include "GUI/Editor/Editors/TextureEditor.h"
#include "Control/Controls/Button.h"
#include "Control/Controls/Grid.h"
#include "GUI/Window/WindowManager.h"
#include "Static/Input.h"
#include "GraphicsLibrary/Base/GraphicsLibrary.h"
#include "Globals.h"
#include "IMGF.h"
#include "Task/TaskManager.h"
#include "Task/Tasks/Tasks.h"
#include "Static/File.h"
#include "Static/Path.h"
#include "Static/String.h"
#include "Type/Colour/Colour.h"
#include "GUI/Layer/Layers/MainLayer/MainLayer.h"
#include "GUI/Layer/Layers/MainLayer/MainLayerNoTabsOpen.h"
#include "GUI/Layer/Layers/MainMenu/EMainMenuType.h"
#include "GUI/Layer/Layers/ELayer.h"
#include "Control/Controls/Menu.h"
#include "Control/Entries/MenuItem.h"
#include "Program/BuildVersion.h"
#include "GUI/Input/EInputItem.h"
#include "Settings/SettingsManager.h"

using namespace std;
using namespace bxcf;
using namespace bxgx;
using namespace bxgx::events;
using namespace imgf;
using namespace imgf::mainLayer::mainMenuType;
using namespace imgf::layers;
using namespace imgf::mainLayer::input;

MainWindow::MainWindow(void) :
	m_uiMainMenuType(EMainMenuType::FORMATS),
	m_pMainLayer(nullptr),
	m_pMainLayerNoTabsOpen(nullptr),
	m_pIMGEditor(nullptr),
	m_pTextureEditor(nullptr)
{
}

// main interface
void					MainWindow::init(void)
{
	initWindow();
	initLayers();

	/* Settings */
	SettingsManager *pSettingsManager = getIMGF()->getSettingsManager();

	// Window Always on Top
	if (pSettingsManager->getSetting("WindowAlwaysOnTop") == "1")
	{
		setTopZIndex(true);
	}
}

// item fetching
ProgressBar*		MainWindow::getProgressBar(void)
{
	return m_pMainLayerNoTabsOpen->getProgressBar();
}

TabBar*			MainWindow::getTabBar(void)
{
	return m_pMainLayer->getTabBar();
}

// window initialization
void					MainWindow::initWindow(void)
{
	addTitleBar("IMG Factory 2.0 - ALPHA Development Version!");
}

void					MainWindow::initLayers(void)
{
	initMainLayer();
	initMainLayerNoTabsOpen();
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

void					MainWindow::initMainLayerNoTabsOpen(void)
{
	m_pMainLayerNoTabsOpen = addLayer<MainLayerNoTabsOpen>(-1, true);
	m_pMainLayerNoTabsOpen->setIMGFWindow(this);
	m_pMainLayerNoTabsOpen->init();
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
		uiButtonHeight = 37,
		uiTitleBarHeight = getTitleBarHeight();
	string
		strStyleGroup;

	Layer *pSettingsMenuLayer = addLayer(ELayer::SETTINGS_MENU, false);

	/*
	x = 139 + 139 + 139;
	y = uiTitleBarHeight;
	w = uiButtonHeight + 1;
	h = uiButtonHeight;
	m_pMainLayer->addMenu(x, y, w, h, VERTICAL, "settingsMenuButton", SETTINGS, 5);
	*/

	y = getTitleBarHeight() + uiButtonHeight;
	w = 139;
	h = uiButtonHeight;
	x = getSize().x - w;
	h2 = h;
	strStyleGroup = "settingsMenu";

	m_pSettingsMenu = pSettingsMenuLayer->addMenu(x, y, w, h, VERTICAL, strStyleGroup, EInputItem::SETTINGS_MENU, -100);
	m_pSettingsMenu->addMenuItem("Settings", SETTINGS);
	m_pSettingsMenu->addMenuItem("Formats", FORMATS2);
	m_pSettingsMenu->addMenuItem("Websites", WEBSITES);
	m_pSettingsMenu->addMenuItem("About", ABOUT);
	m_pSettingsMenu->addMenuItem("Update", UPDATE);
}

void					MainWindow::initEditors(void)
{
	m_pIMGEditor = addLayer<IMGEditor>(-1, true);
	m_pTextureEditor = addLayer<TextureEditor>(-1, false);

	m_pIMGEditor->setMainWindow(this);
	m_pTextureEditor->setMainWindow(this);

	m_pIMGEditor->init();
	m_pTextureEditor->init();
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