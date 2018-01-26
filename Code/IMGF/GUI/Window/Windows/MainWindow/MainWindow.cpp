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
#include "Static/DataPath.h"
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
#include "DragDrop/DropTarget.h"

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

	m_pActiveEditor(nullptr),

	m_bDragDropOutIsOccurring(false)
{
}

// main interface
void					MainWindow::init(void)
{
	initWindow();
	initLayers();

	RegisterDragDrop(getWindowHandle(), new bxgx::DropTarget(getWindowHandle()));

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
	/*
	initMainLayer();
	initMainLayerNoTabsOpen();
	initMainMenuLayers();
	initSettingsMenuLayer();
	*/

	bindEventRef(RESIZE_WINDOW, &MainWindow::onResizeWindow);
	onResizeWindow(Vec2i(0, 0));

	bindEvent(DROP_ENTRIES, &MainWindow::onDropEntries);

	bindEvent(RELOAD_LAYERS, &MainWindow::reloadLayers);

	/*
	todo

	int32 iLastEditorUsedIndex = String::toUint32(getIMGF()->getSettingsManager()->getSetting("LastEditorUsedIndex"));
	if (iLastEditorUsedIndex < m_vecEditors.getEntryCount())
	{
		setActiveEditor(m_vecEditors.getEntryByIndex(iLastEditorUsedIndex));
	}
	else
	{
		setActiveEditor(m_vecEditors.getFirstEntry());
	}
	*/

	for (string& strLayerFilePath : File::getFilePaths(DataPath::getDataPath() + "Layers/"))
	{
		loadLayerFile(strLayerFilePath);
	}

	initEditors();

	setActiveEditor(m_vecEditors.getFirstEntry());

	Button *pButton = (Button*)getItemById(1004);
	pButton->setActiveItem();
}

void					MainWindow::reloadLayers(void)
{
	Layer *pLayer;
	while(pLayer = getEntryByIndex(0))
		removeLayer(pLayer);

	for (string& strLayerFilePath : File::getFilePaths(DataPath::getDataPath() + "Layers/"))
	{
		loadLayerFile(strLayerFilePath);
	}
}

void					MainWindow::onDropEntries(void *m_pEditorTab, vector<string> vecFileNames, vector<string> vecFileDatas)
{
	// import files
	EditorTab
		*pActiveEditorTab = getActiveEditor()->getActiveEditorTab(),
		*pSourceActiveEditorTab = (EditorTab*)m_pEditorTab;

	if (pActiveEditorTab == pSourceActiveEditorTab)
	{
		// skip if dropped in source editor tab
		return;
	}

	for (uint32 i = 0, j = vecFileNames.size(); i < j; i++)
	{
		pActiveEditorTab->addEntryViaData(vecFileNames[i], vecFileDatas[i]);
	}
}

// layer initialization
void					MainWindow::initEditors(void)
{
	m_pDATEditor = addEditor<DATEditor>();
	m_pIMGEditor = addEditor<IMGEditor>();
	m_pTextureEditor = addEditor<TextureEditor>();
	m_pCollisionEditor = addEditor<CollisionEditor>();
	m_pModelEditor = addEditor<ModelEditor>();
	m_pRadarEditor = addEditor<RadarEditor>();
	m_pWaterEditor = addEditor<RadarEditor>(); // todo - Water
	m_pPathsEditor = addEditor<RadarEditor>(); // todo - Paths
	m_pPaintEditor = addEditor<RadarEditor>(); // todo - Paint
	m_pZonsEditor = addEditor<RadarEditor>(); // todo - Zons
	m_pAnimationEditor = addEditor<AnimationEditor>();
	m_pItemDefinitionEditor = addEditor<ItemDefinitionEditor>();
	m_pItemPlacementEditor = addEditor<ItemPlacementEditor>();
	m_pMapEditor = addEditor<MapEditor>();
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
		x, y, y2, w, h, w2, h2;
	uint32
		uiButtonHeight = 37;
	Menu
		*pMenu;
	string
		strStyleGroup;

	// formats menu
	Layer *pFormatsLayer = addLayer(FORMATS_MENU, true);

	x = 5;
	y = getTitleBarHeight() + 40;
	y2 = y;
	w = 139;
	h = 29;
	w2 = 10;
	h2 = 10;
	strStyleGroup = "leftMenu";

	//m_pFormatsMenu = pFormatsLayer->addMenu(x, y, w, h, VERTICAL, strStyleGroup, -1, -200);
	//vector<MenuItem*> vecMenuItems = m_pFormatsMenu->addMenuItems(23, "Root Dat", "IMG", "Tex", "COL", "Model", "Radar", "Water", "Path", "Paint", "Zone", "Animation", "IDE", "IPL", "2DFX / IFX", "Text Editor", "Map Editor", "Weapon", "Cut Scene", "Vehicle", "Pedestrian", "Carcol", "Timecyc", "More ->");
	//m_pFormatsMenu->setItemIds(500);
	//m_pFormatsMenu->setActiveMenuItem(vecMenuItems[6]);

	Button *pButton = getMainLayer()->addButton(x, y, w, h, "Root Dat");
	
	y += h + h2;
	w = 65;
	getMainLayer()->addButton(x, y, w, h, "IMG");
	x += w + w2;
	getMainLayer()->addButton(x, y, w, h, "Tex");
	y += h + h2;
	x -= w + w2;
	getMainLayer()->addButton(x, y, w, h, "COL");
	x += w + w2;
	getMainLayer()->addButton(x, y, w, h, "Model");
	y += h + h2;
	x -= w + w2;
	w = 139;
	getMainLayer()->addButton(x, y, w, h, "Radar");
	y += h + h2;
	getMainLayer()->addButton(x, y, w, h, "Water");
	y += h + h2;
	getMainLayer()->addButton(x, y, w, h, "Paths");
	y += h + h2;
	getMainLayer()->addButton(x, y, w, h, "Paint");
	y += h + h2;
	getMainLayer()->addButton(x, y, w, h, "Zones");
	y += h + h2;
	getMainLayer()->addButton(x, y, w, h, "Anims");
	y += h + (h2 * 4);
	w = 65;
	getMainLayer()->addButton(x, y, w, h, "IDE");
	x += w + w2;
	getMainLayer()->addButton(x, y, w, h, "IPL");
	y += h + h2;
	x -= w + w2;
	w = 139;
	getMainLayer()->addButton(x, y, w, h, "2DFX / IFX");
	y += h + h2;
	getMainLayer()->addButton(x, y, w, h, "Text Editor");
	y += h + h2;
	getMainLayer()->addButton(x, y, w, h, "Map Editor");
	y += h + h2;
	w = 65;
	getMainLayer()->addButton(x, y, w, h, "Weap");
	x += w + w2;
	getMainLayer()->addButton(x, y, w, h, "Cuts");
	y += h + h2;
	x -= w + w2;
	getMainLayer()->addButton(x, y, w, h, "Vehicle");
	x += w + w2;
	getMainLayer()->addButton(x, y, w, h, "Ped");
	x -= w + w2;
	y += h + h2;
	w = 139;
	getMainLayer()->addButton(x, y, w, h, "Car Cols");
	y += h + h2;
	getMainLayer()->addButton(x, y, w, h, "Timecyc");
	y += h + h2;
	getMainLayer()->addButton(x, y, w, h, "More ->");
	y += h + h2;

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
	//Layer *pBlankLayer = getLayerById(99);

	// disable previous editor
	if (m_pActiveEditor && bDiff)
	{
		//m_pActiveEditor->unbindEvents();
		
		m_pActiveEditor->getLayer()->setEnabled(false);
		m_pActiveEditor->getEditorButton()->resetStyleGroups();
		m_pActiveEditor->unbindEvents();

		if (m_pActiveEditor->getEditorTabs().getEntryCount() == 0)
		{
			//pBlankLayer->setEnabled(false);
		}
		else
		{
			m_pActiveEditor->getActiveEditorTab()->unbindEvents();
			m_pActiveEditor->getActiveEditorTab()->getBaseLayer()->setEnabled(false);
			m_pActiveEditor->getActiveEditorTab()->getLayer()->setEnabled(false);
		}
	}

	// set next editor
	m_pActiveEditor = pActiveEditor;

	// enable next editor
	if (pActiveEditor && bDiff)
	{
		//getIMGF()->getSettingsManager()->setSetting("LastEditorUsedIndex", String::toString(getEditorIndex(pActiveEditor)));
		
		pActiveEditor->getEditorButton()->setStyleGroups(string("activeEditorButton"));
		pActiveEditor->getLayer()->setEnabled(true);
		pActiveEditor->bindEvents();

		if (pActiveEditor->getEditorTabs().getEntryCount() == 0)
		{
			//pBlankLayer->setEnabled(true);
		}
		else
		{
			pActiveEditor->getActiveEditorTab()->bindEvents();
			pActiveEditor->getActiveEditorTab()->getBaseLayer()->setEnabled(true);
			pActiveEditor->getActiveEditorTab()->getLayer()->setEnabled(true);
		}
		//pActiveEditor->bindEvents();
	}

	// todo
	//m_pMainLayer->removeMenus();
	//m_pMainLayer->addMenus();
	//m_pMainLayer->setCertainMenuItemsEnabled(pActiveEditor && (pActiveEditor->getEditorTabs().getEntryCount() > 0));

	/*
	todo
	if (m_pActiveEditor)
	{
		getIMGF()->getRecentlyOpenManager()->unloadRecentlyOpenEntries(m_pActiveEditor->getEditorType());
		getIMGF()->getRecentlyOpenManager()->loadRecentlyOpenEntries(m_pActiveEditor->getEditorType());

		getIMGF()->getFileGroupManager()->unloadFileGroups(m_pActiveEditor->getEditorType());
		getIMGF()->getFileGroupManager()->loadFileGroups(m_pActiveEditor->getEditorType());
	}
	*/

	// todo
	//bool bEnableLayerWithNoTabsOpen = pActiveEditor && pActiveEditor->getEditorTabs().getEntryCount() == 0;
	//if (pBlankLayer->isEnabled() != bEnableLayerWithNoTabsOpen)
	//{
	//	pBlankLayer->setEnabled(bEnableLayerWithNoTabsOpen);
	//}

	uint32 uiEditorIndex = m_vecEditors.getIndexByEntry(pActiveEditor);
	//MenuItem *pActiveMenuItem = m_pFormatsMenu->getEntryByIndex(uiEditorIndex);
	//m_pFormatsMenu->setActiveMenuItem(pActiveMenuItem);

	//string strEditorTitleNoSpaces = String::replace(pActiveMenuItem->getText(), " ", "");
	//string strWindowStyleGroup = "window windowEditorTab_" + strEditorTitleNoSpaces;
	//resetStyleGroups();
	//setStyleGroups(strWindowStyleGroup);
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
void					MainWindow::onResizeWindow(Vec2i& vecSizeDifference)
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

	// todo m_pSettingsMenu->setPosition(Vec2i(x, y));
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