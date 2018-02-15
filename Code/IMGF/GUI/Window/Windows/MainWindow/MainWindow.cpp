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
#include "GUI/Layer/Layers/MainMenu/EMainMenuType.h"
#include "GUI/Layer/Layers/ELayer.h"
#include "Control/Controls/Menu.h"
#include "Control/Entries/MenuItem.h"
#include "Shape/Shapes/Line.h"
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

	m_bDragDropOutIsOccurring(false),

	m_pRecentlyOpenMenu(nullptr),
	m_pFileGroupMenu(nullptr)
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
	return nullptr; // todo
}

// event binding
void					MainWindow::bindEvents(void)
{
	bindEventRef(RESIZE_WINDOW, &MainWindow::onResizeWindow);
	onResizeWindow(Vec2i(0, 0));

	bindEvent(DROP_ENTRIES, &MainWindow::onDropEntries);
	bindEvent(RELOAD_LAYERS, &MainWindow::reloadLayers);
}

void					MainWindow::unbindEvents(void)
{
	unbindEvent(RESIZE_WINDOW, &MainWindow::onResizeWindow);
	unbindEvent(DROP_ENTRIES, &MainWindow::onDropEntries);
	unbindEvent(RELOAD_LAYERS, &MainWindow::reloadLayers);
}

// window initialization
void					MainWindow::initWindow(void)
{
	addTitleBar("IMG Factory 2.0 - ALPHA Development Version!");
}

void					MainWindow::initLayers(void)
{
	bindEvents();

	for (string& strLayerFilePath : File::getFilePaths(DataPath::getDataPath() + "Layers/"))
	{
		loadLayerFile(strLayerFilePath);
	}

	initEditors();
	initSettingsMenuLayer();
	initMenuRelatedItems();

	int32 iLastEditorUsedIndex = String::toUint32(getIMGF()->getSettingsManager()->getSetting("LastEditorUsedIndex"));
	if (iLastEditorUsedIndex < m_vecEditors.getEntryCount())
	{
		setActiveEditor(m_vecEditors.getEntryByIndex(iLastEditorUsedIndex));
	}
	else
	{
		setActiveEditor(m_vecEditors.getFirstEntry());
	}

	Button *pButton = (Button*)getItemById(1004);
	pButton->setActiveItem();
}

void					MainWindow::reloadLayers(void)
{
	setActiveEditor(nullptr);

	Layer *pLayer;
	while(pLayer = getEntryByIndex(0))
		removeLayer(pLayer);

	for (Editor *pEditor : m_vecEditors.getEntries())
	{
		delete pEditor;
	}
	m_vecEditors.getEntries().clear();

	unbindEvents();

	initLayers();
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

void					MainWindow::initSettingsMenuLayer(void)
{
	// settings button

	CoordinateSet x, y, w, h;

	x.m_bIsX = true;
	x.m_fRelative = 1.0f;
	x.m_iOffsetPx = -50;

	y.m_bIsX = false;
	y.m_fRelative = 0.0f;
	y.m_iOffsetPx = 40;

	w.m_bIsX = true;
	w.m_fRelative = 0.0f;
	w.m_iOffsetPx = 38;

	h.m_bIsX = false;
	h.m_fRelative = 0.0f;
	h.m_iOffsetPx = 38;

	x.px();
	y.px();
	w.px();
	h.px();

	m_pSettingsButton = getLayerById(45)->addButton(x, y, w, h, "", "settingsMenuButton", SETTINGS, 5);
	m_pSettingsButtonLine1 = getLayerById(45)->addLine(x.m_px + 10, y.m_px + 10, x.m_px + 27, y.m_px + 10, "settingsMenuLine", -1, 10);
	m_pSettingsButtonLine2 = getLayerById(45)->addLine(x.m_px + 10, y.m_px + 19, x.m_px + 27, y.m_px + 19, "settingsMenuLine", -1, 10);
	m_pSettingsButtonLine3 = getLayerById(45)->addLine(x.m_px + 10, y.m_px + 28, x.m_px + 27, y.m_px + 28, "settingsMenuLine", -1, 10);

	m_pSettingsButton->addLinkedItem(m_pSettingsButtonLine1);
	m_pSettingsButton->addLinkedItem(m_pSettingsButtonLine2);
	m_pSettingsButton->addLinkedItem(m_pSettingsButtonLine3);



	// settings menu

	int32
		x2, y2, w2, h2, h3;
	uint32
		uiButtonHeight = 37,
		uiTitleBarHeight = getTitleBarHeight();
	string
		strStyleGroup;

	Layer *pSettingsMenuLayer = addLayer(ELayer::SETTINGS_MENU, false);

	y2 = getTitleBarHeight() + uiButtonHeight;
	w2 = 139;
	h2 = uiButtonHeight;
	x2 = getSize().x - w2;
	h3 = h2;
	strStyleGroup = "settingsMenu";

	m_pSettingsMenu = pSettingsMenuLayer->addMenu(x2, y2, w2, h2, VERTICAL, 2, strStyleGroup, EInputItem::SETTINGS_MENU, -200);
	m_pSettingsMenu->addMenuItem("Settings", SETTINGS);
	m_pSettingsMenu->addMenuItem("Formats", FORMATS2);
	m_pSettingsMenu->addMenuItem("Websites", WEBSITES);
	m_pSettingsMenu->addMenuItem("About", ABOUT);
	m_pSettingsMenu->addMenuItem("Update", UPDATE);
}

void					MainWindow::initMenuRelatedItems(void)
{
	MenuItem *pMenuItem1 = (MenuItem*)getItemById(4700);
	m_pRecentlyOpenMenu = pMenuItem1->addMenu(VERTICAL, 1);

	MenuItem *pMenuItem2 = (MenuItem*)getItemById(1059);
	m_pFileGroupMenu = pMenuItem2->addMenu(VERTICAL, 1);
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
		m_pActiveEditor->getLayer()->setEnabled(false);
		m_pActiveEditor->getEditorButton()->resetStyleGroups();
		m_pActiveEditor->unbindEvents();

		if (m_pActiveEditor->getEditorTabs().getEntryCount() != 0)
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
		// todo
		getIMGF()->getSettingsManager()->setSetting("LastEditorUsedIndex", String::toString(getEditorIndex(pActiveEditor)));
		
		pActiveEditor->getEditorButton()->setStyleGroups(string("activeEditorButton"));
		pActiveEditor->getLayer()->setEnabled(true);
		pActiveEditor->bindEvents();

		if (pActiveEditor->getEditorTabs().getEntryCount() != 0)
		{
			pActiveEditor->getActiveEditorTab()->bindEvents();
			pActiveEditor->getActiveEditorTab()->getBaseLayer()->setEnabled(true);
			pActiveEditor->getActiveEditorTab()->getLayer()->setEnabled(true);
		}
	}

	// todo
	//m_pMainLayer->removeMenus();
	//m_pMainLayer->addMenus();
	setCertainMenuItemsEnabled(pActiveEditor && (pActiveEditor->getEditorTabs().getEntryCount() > 0));

	if (m_pActiveEditor)
	{
		getIMGF()->getRecentlyOpenManager()->unloadRecentlyOpenEntries(m_pActiveEditor->getEditorType());
		getIMGF()->getFileGroupManager()->unloadFileGroups(m_pActiveEditor->getEditorType());
	}

	if (pActiveEditor)
	{
		getIMGF()->getRecentlyOpenManager()->loadRecentlyOpenEntries(pActiveEditor->getEditorType());
		setOpenLastFilename(getIMGF()->getRecentlyOpenManager()->getLastOpenEntry(pActiveEditor->getEditorType()));
		getIMGF()->getFileGroupManager()->loadFileGroups(pActiveEditor->getEditorType());
	}

	uint32 uiEditorIndex = m_vecEditors.getIndexByEntry(pActiveEditor);

	// todo
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
	return getEditors().getIndexByEntry(pEditor);
}

// layer repositioning and resizing
void					MainWindow::onResizeWindow(Vec2i& vecSizeDifference)
{
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

// open last closed file
void					MainWindow::setOpenLastFilename(string strFileName)
{
	EEditor uiActiveEditorType = getActiveEditor()->getEditorType();
	string strMenuItemText = "Open Last Closed File" + (getIMGF()->getRecentlyOpenManager()->getLastOpenEntry(uiActiveEditorType) == "" ? "" : " (" + Path::getFileName(getIMGF()->getRecentlyOpenManager()->getLastOpenEntry(uiActiveEditorType)) + ")");
	MenuItem *pMenuItem = (MenuItem*)getItemById(1056);
	pMenuItem->setText(strMenuItemText);
}

void					MainWindow::clearOpenLastFilename(void)
{
	EEditor uiActiveEditorType = getActiveEditor()->getEditorType();
	string strMenuItemText = "Open Last Closed File";
	MenuItem *pMenuItem = (MenuItem*)getItemById(1056);
	pMenuItem->setText(strMenuItemText);
}

// menu items enabled/disabled
void					MainWindow::setCertainMenuItemsEnabled(bool bEnabled)
{
	bool
		bIsIMGEditor = getActiveEditor() == getIMGEditor(),
		bIsModelEditor = getActiveEditor() == getModelEditor(),
		bIsTextureEditor = getActiveEditor() == getTextureEditor(),
		// todo bIsTextEditor = getActiveEditor() == getTextEditor(),
		bIsCollisionEditor = getActiveEditor() == getCollisionEditor();

	// disable certain menu items
	vector<EInputItem> vecMenuItemIds {
		// second left and top menus
		SAVE_MENU,
		SAVE_LOGS_MENU,
		IMPORT_MENU,
		IMPORT_BY_FOLDERS_MENU,
		EXPORT_MENU,
		EXPORT_BY_COLUMN_MENU,
		EXPORT_ALL_ENTRIES_INTO_MENU,
		EXPORT_ALL_TABS_MENU,
		REPLACE_MENU,
		REPLACE_BY_FOLDER_MENU,
		REMOVE_MENU,
		REMOVE_BY_COLUMN_MENU,
		SPLIT_MENU,
		CONVERT_MENU,
		CONVERT_IMG_MENU,
		CONVERT_COL_MENU,
		CONVERT_DFF_MENU,
		CONVERT_TXD_MENU,
		CONVERT_WTD_MENU,
		SELECT_MENU,
		SELECT_BY_COLUMN_MENU,
		UNSELECT_BY_COLUMN_MENU,
		SORT_MENU,
		SORT_BY_INDEX_MENU,
		SORT_BY_NAME_MENU,
		SORT_BY_OFFSET_MENU,
		SORT_BY_SIZE_MENU,
		SORT_BY_TYPE_MENU,
		SORT_BY_VERSION_MENU,
		ENTRY_MENU,
		ENTRY_NAME_CASE_MENU,
		ENTRY_COPY_DATA_MENU,
		ENTRY_SHIFT_MENU,
		ORPHAN_ENTRIES_MENU,

		// top menu items
		REOPEN_FILE,
		OPEN_FILE_FOLDER_IN_EXPLORER,

		SAVE_FILE,
		SAVE_FILE_AS,
		SAVE_ALL_FILES,
		CLONE_FILE,
		SAVE_FILE_GROUP,
		SAVE_LOGS,
		SAVE_LOGS_ALL_TABS,
		CLEAR_LOGS,
		CLEAR_LOGS_ALL_TABS,

		CLOSE_FILE,
		CLOSE_ALL_FILES,

		// second left menu items
		IMPORT_BY_FILES,
		IMPORT_BY_SINGLE_FOLDER,
		IMPORT_BY_FOLDER_RECURSIVELY,
		IMPORT_BY_ENTRY_NAMES,

		EXPORT_SELECTED,
		EXPORT_ALL,
		EXPORT_BY_INDEX,
		EXPORT_BY_NAME,
		EXPORT_BY_OFFSET,
		EXPORT_BY_SIZE,
		EXPORT_BY_TYPE,
		EXPORT_BY_VERSION,
		EXPORT_ALL_INTO_GROUPED_FOLDERS_BY_TYPE,
		EXPORT_ALL_FROM_ALL_TABS,
		EXPORT_ALL_FROM_ALL_TABS_INTO_GROUPED_FOLDERS_BY_TYPE,
		EXPORT_SELECTION_FROM_ALL_TABS,
		EXPORT_BY_ENTRY_NAMES,
		EXPORT_BY_ENTRY_NAMES_FROM_ALL_TABS,

		QUICK_EXPORT,

		RENAME,

		REPLACE_BY_FILES,
		REPLACE_BY_SINGLE_FOLDER,
		REPLACE_BY_FOLDER_RECURSIVELY,

		REMOVE_SELECTED,
		REMOVE_ALL,
		REMOVE_BY_INDEX,
		REMOVE_BY_NAME,
		REMOVE_BY_OFFSET,
		REMOVE_BY_SIZE,
		REMOVE_BY_TYPE,
		REMOVE_BY_VERSION,
		REMOVE_BY_ENTRY_NAMES,

		MERGE,

		SPLIT_SELECTED,
		SPLIT_BY_ENTRY_NAMES,

		SELECT_ALL,
		UNSELECT_ALL,
		SELECT_INVERSE,
		SELECT_BY_INDEX,
		SELECT_BY_NAME,
		SELECT_BY_OFFSET,
		SELECT_BY_SIZE,
		SELECT_BY_TYPE,
		SELECT_BY_VERSION,
		UNSELECT_BY_INDEX,
		UNSELECT_BY_NAME,
		UNSELECT_BY_OFFSET,
		UNSELECT_BY_SIZE,
		UNSELECT_BY_TYPE,
		UNSELECT_BY_VERSION,

		SORT_BY_INDEX_REVERSE,
		SORT_BY_NAME_ASCENDING_09AZ,
		SORT_BY_NAME_ASCENDING_AZ09,
		SORT_BY_NAME_DESCENDING_ZA90,
		SORT_BY_NAME_DESCENDING_90ZA,
		SORT_BY_OFFSET_LOW_HIGH,
		SORT_BY_OFFSET_HIGH_LOW,
		SORT_BY_SIZE_SMALL_BIG,
		SORT_BY_SIZE_BIG_SMALL,
		SORT_BY_TYPE_AZ,
		SORT_BY_TYPE_ZA,
		SORT_BY_VERSION_OLD_NEW,
		SORT_BY_VERSION_NEW_OLD,

		NAME_CASE_LOWER,
		NAME_CASE_UPPER,
		NAME_CASE_TITLE,

		COPY_ENTRY_INDEX,
		COPY_ENTRY_TYPE,
		COPY_ENTRY_NAME,
		COPY_ENTRY_OFFSET,
		COPY_ENTRY_SIZE,
		COPY_ENTRY_VERSION,
		COPY_ENTRY_ROW_DATA,

		SHIFT_ENTRY_UP_1_ROW,
		SHIFT_ENTRY_UP_5_ROWS,
		SHIFT_ENTRY_UP_10_ROWS,
		SHIFT_ENTRY_UP_100_ROWS,
		SHIFT_ENTRY_UP_1000_ROWS,
		SHIFT_ENTRY_DOWN_1_ROW,
		SHIFT_ENTRY_DOWN_5_ROWS,
		SHIFT_ENTRY_DOWN_10_ROWS,
		SHIFT_ENTRY_DOWN_100_ROWS,
		SHIFT_ENTRY_DOWN_1000_ROWS
	};
	if (bIsIMGEditor)
	{
		StdVector::addToVector(vecMenuItemIds, vector<EInputItem>({
			IMPORT_BY_IDE,
//			IMPORT_BY_IPL,
			EXPORT_BY_IDE,
			EXPORT_BY_IDE_FROM_ALL_TABS,
			EXPORT_BY_IPL,
			EXPORT_BY_DAT,
			EXPORT_TEXTURE_NAME_LIST,
			REPLACE_BY_IDE,
			REMOVE_BY_IDE,
			SPLIT_BY_IDE,
			SELECT_BY_IDE,
			UNSELECT_BY_IDE,
			SORT_BY_IDE,
			SORT_BY_COL,

			REMOVE_ORPHAN_TEXTURES_FROM_DFF_ENTRIES,
			FIND_ORPHAN_IMG_ENTRIES_NOT_IN_IDE,
			FIND_ORPHAN_IDE_ENTRIES_NOT_IN_IMG,
			FIND_ORPHAN_TXD_TEXTURES_FOR_DFFS_IN_IMG_BY_IDE,

			TEXTURE_LIST,
			STATS,
			FIND_DUPLICATE_ENTRIES_IN_SELECTION,
			FIND_DUPLICATE_ENTRIES_IN_TAB,
			FIND_DUPLICATE_ENTRIES_IN_ALL_TABS,
			COMPARE_IMGS,
			SAVE_IMG_SIGNATURE,
			VERIFY_IMG_SIGNATURE,
			VALIDATE_DFF_IN_TAB,
			VALIDATE_TXD_IN_TAB,
			CENTER_COL_MESHES_IN_SELECTION,
			IMG_COMPRESSION,

			CONVERT_IMG_VERSION
		}));
		if (bIsIMGEditor || bIsCollisionEditor)
		{
			StdVector::addToVector(vecMenuItemIds, vector<EInputItem>({
				CONVERT_SELECTED_COL_VERSION
			}));
		}
		if (bIsIMGEditor || bIsModelEditor)
		{
			StdVector::addToVector(vecMenuItemIds, vector<EInputItem>({
				CONVERT_SELECTED_DFF_RW_VERSION,
				CONVERT_SELECTED_DFF_TO_WDR
			}));
		}
		if (bIsIMGEditor || bIsTextureEditor)
		{
			StdVector::addToVector(vecMenuItemIds, vector<EInputItem>({
				CONVERT_SELECTED_TXD_RW_VERSION,
				CONVERT_SELECTED_TXD_TO_GAME,
				CONVERT_SELECTED_TXD_TO_TEXTURE_FORMAT,
				CONVERT_SELECTED_WTD_TO_TXD
			}));
		}
	}

	for (EInputItem uiMenuItemId : vecMenuItemIds)
	{
		MenuItem *pMenuItem = (MenuItem*) getItemById(uiMenuItemId);
		if (pMenuItem)
		{
			pMenuItem->setEnabled(bEnabled);
		}
	}

	Menu *pMenu;

	pMenu = (Menu*)getItemById(4800);
	pMenu->render();

	pMenu = (Menu*)getItemById(4801);
	pMenu->render();

	pMenu = (Menu*)getItemById(4802);
	pMenu->render();
}