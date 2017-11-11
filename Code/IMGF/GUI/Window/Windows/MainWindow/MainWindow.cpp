#include "MainWindow.h"
#include "Event/EInputEvent.h"
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
#include "Static/StdVector.h"
#include "Task/Tasks/RecentlyOpen/RecentlyOpenManager.h"
#include "Task/Tasks/FileGroups/FileGroupManager.h"

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

	m_pFormatsMenu(nullptr),
	m_pSettingsMenu(nullptr),

	m_pDATEditor(nullptr),
	m_pIMGEditor(nullptr),
	m_pItemDefinitionEditor(nullptr),
	m_pItemPlacementEditor(nullptr),
	m_pModelEditor(nullptr),
	m_pCollisionEditor(nullptr),
	m_pAnimationEditor(nullptr),
	m_pRadarEditor(nullptr),

	m_pActiveEditor(nullptr)
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

	// load file from command line
	getIMGF()->initCommandLine();
}

// item fetching
ProgressBar*			MainWindow::getProgressBar(void)
{
	return m_pMainLayerNoTabsOpen->getProgressBar();
}

// window initialization
void					MainWindow::initWindow(void)
{
	addTitleBar("IMG Factory 2.0 - ALPHA Development Version!");
}

void					MainWindow::initLayers(void)
{
	initEditors();
	initMainLayer();
	initMainLayerNoTabsOpen();
	initMainMenuLayers();
	initSettingsMenuLayer();

	bindEventRef(RESIZE_WINDOW, &MainWindow::repositionAndResizeControls);
	repositionAndResizeControls(Vec2i(0, 0));

	int32 iLastEditorUsedIndex = String::toUint32(getIMGF()->getSettingsManager()->getSetting("LastEditorUsedIndex"));
	if (iLastEditorUsedIndex < m_vecEditors.getEntryCount())
	{
		setActiveEditor(m_vecEditors.getEntryByIndex(iLastEditorUsedIndex));
	}
	else
	{
		setActiveEditor(m_vecEditors.getFirstEntry());
	}
}

// layer initialization
void					MainWindow::initEditors(void)
{
	m_pDATEditor = addEditor<DATEditor>();
	m_pIMGEditor = addEditor<IMGEditor>();
	m_pItemDefinitionEditor = addEditor<ItemDefinitionEditor>();
	m_pItemPlacementEditor = addEditor<ItemPlacementEditor>();
	m_pModelEditor = addEditor<ModelEditor>();
	m_pCollisionEditor = addEditor<CollisionEditor>();
	m_pTextureEditor = addEditor<TextureEditor>();
	m_pAnimationEditor = addEditor<AnimationEditor>();
	m_pRadarEditor = addEditor<RadarEditor>();
}

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

	m_pFormatsMenu = pFormatsLayer->addMenu(x, y, w, h, VERTICAL, strStyleGroup, -1, -200);
	vector<MenuItem*> vecMenuItems = m_pFormatsMenu->addMenuItems(9, "DAT", "IMG", "Item Definition", "Item Placement", "Model", "Collision", "Texture", "Animation", "Radar");
	m_pFormatsMenu->setItemIds(500);
	m_pFormatsMenu->setActiveMenuItem(vecMenuItems[6]);

	// utility menu
	Layer *pUtilityLayer = addLayer(UTILITY_MENU, false);

	x = 0;
	y = y2;
	w = 139;
	h = uiButtonHeight;
	h2 = h;
	strStyleGroup = "leftMenu";

	pMenu = pUtilityLayer->addMenu(x, y, w, h, VERTICAL, strStyleGroup, -1, -200);
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

	m_pSettingsMenu = pSettingsMenuLayer->addMenu(x, y, w, h, VERTICAL, strStyleGroup, EInputItem::SETTINGS_MENU, -200);
	m_pSettingsMenu->addMenuItem("Settings", SETTINGS);
	m_pSettingsMenu->addMenuItem("Formats", FORMATS2);
	m_pSettingsMenu->addMenuItem("Websites", WEBSITES);
	m_pSettingsMenu->addMenuItem("About", ABOUT);
	m_pSettingsMenu->addMenuItem("Update", UPDATE);
}

void					MainWindow::addEditor(Editor *pEditor)
{
	m_vecEditors.addEntry(pEditor);
}

void					MainWindow::setActiveEditor(Editor *pActiveEditor)
{
	bool bDiff = m_pActiveEditor != pActiveEditor;

	if (m_pActiveEditor && bDiff && m_pActiveEditor->isEnabled())
	{
		//m_pActiveEditor->unbindEvents();
		m_pActiveEditor->setEnabled(false);
	}

	m_pActiveEditor = pActiveEditor;

	if (pActiveEditor && bDiff && !pActiveEditor->isEnabled())
	{
		getIMGF()->getSettingsManager()->setSetting("LastEditorUsedIndex", String::toString(getEditorIndex(pActiveEditor)));
		pActiveEditor->setEnabled(true);
		//pActiveEditor->bindEvents();
	}

	m_pMainLayer->removeMenus();
	m_pMainLayer->addMenus();
	m_pMainLayer->setCertainMenuItemsEnabled(pActiveEditor && (pActiveEditor->getEditorTabs().getEntryCount() > 0));

	if (m_pActiveEditor)
	{
		getIMGF()->getRecentlyOpenManager()->unloadRecentlyOpenEntries(m_pActiveEditor->getEditorType());
		getIMGF()->getRecentlyOpenManager()->loadRecentlyOpenEntries(m_pActiveEditor->getEditorType());

		getIMGF()->getFileGroupManager()->unloadFileGroups(m_pActiveEditor->getEditorType());
		getIMGF()->getFileGroupManager()->loadFileGroups(m_pActiveEditor->getEditorType());
	}

	bool bEnableLayerWithNoTabsOpen = pActiveEditor && pActiveEditor->getEditorTabs().getEntryCount() == 0;
	Layer *pLayerWithNoTabsOpen = getIMGF()->getWindowManager()->getMainWindow()->getMainLayerNoTabsOpen();
	if (pLayerWithNoTabsOpen->isEnabled() != bEnableLayerWithNoTabsOpen)
	{
		pLayerWithNoTabsOpen->setEnabled(bEnableLayerWithNoTabsOpen);
	}

	uint32 uiEditorIndex = m_vecEditors.getIndexByEntry(pActiveEditor);
	MenuItem *pActiveMenuItem = m_pFormatsMenu->getEntryByIndex(uiEditorIndex);
	m_pFormatsMenu->setActiveMenuItem(pActiveMenuItem);

	string strEditorTitleNoSpaces = String::replace(pActiveMenuItem->getText(), " ", "");
	string strWindowStyleGroup = "window windowEditorTab_" + strEditorTitleNoSpaces;
	resetStyleGroups();
	setStyleGroups(strWindowStyleGroup);
	render();
}

Editor*					MainWindow::getEditorFromFileExtension(string& strFileExtension)
{
	string strFileExtensionUpper = String::toUpperCase(strFileExtension);
	if (StdVector::isIn(StdVector::toUpperCase(m_pActiveEditor->getEditorFileFormats()), strFileExtensionUpper))
	{
		return m_pActiveEditor;
	}
	for (Editor *pEditor : getEditors().getEntries())
	{
		if (StdVector::isIn(StdVector::toUpperCase(pEditor->getEditorFileFormats()), strFileExtensionUpper))
		{
			return pEditor;
		}
	}
	return nullptr;
}

int32					MainWindow::getEditorIndex(Editor *pEditor)
{
	if (pEditor == m_pDATEditor) return 0;
	if (pEditor == m_pIMGEditor) return 1;
	if (pEditor == m_pItemDefinitionEditor) return 2;
	if (pEditor == m_pItemPlacementEditor) return 3;
	if (pEditor == m_pModelEditor) return 4;
	if (pEditor == m_pCollisionEditor) return 5;
	if (pEditor == m_pTextureEditor) return 6;
	if (pEditor == m_pAnimationEditor) return 7;
	if (pEditor == m_pRadarEditor) return 8;
	return -1;
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