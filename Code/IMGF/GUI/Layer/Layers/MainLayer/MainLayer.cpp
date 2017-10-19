#include "MainLayer.h"
#include "Window/Window.h"
#include "BXGX.h"
#include "Type/Colour/Colour.h"
#include "Control/Controls/TabBar.h"
#include "Control/Controls/DropDown.h"
#include "Control/Controls/Button.h"
#include "Control/Controls/ProgressBar.h"
#include "Control/Controls/TextBox.h"
#include "Shape/Shapes/Line.h"
#include "GUI/Window/Windows/MainWindow/MainWindow.h"
#include "GUI/Editor/Editors/IMGEditor.h"
#include "GUI/Layer/Layers/ELayer.h"
#include "GUI/Input/EInputItem.h"
#include "Control/Controls/Menu.h"
#include "Control/Entries/MenuItem.h"
#include "Static/DataPath.h"

using namespace std;
using namespace bxcf;
using namespace bxgx;
using namespace bxgx::events;
using namespace imgf;
using namespace imgf::layers;
using namespace imgf::mainLayer::input;

MainLayer::MainLayer(void) :
	m_pMainWindow(nullptr),
	m_pSettingsButton(nullptr),
	m_pSettingsButtonLine1(nullptr),
	m_pSettingsButtonLine2(nullptr),
	m_pSettingsButtonLine3(nullptr),
	m_pRecentlyOpenMenu(nullptr),
	m_pFileGroupMenu(nullptr)
{
}

// main interface
void		MainLayer::init(void)
{
	addControls();
	initControls();
}

// tab control
void		MainLayer::onChangeTab(TabBar *pTabBar)
{
	//m_pActiveEditor->onChangeTab(pTabBar);
	if (pTabBar->getEntryCount() == 0)
	{
		m_pMainWindow->getIMGEditor()->setActiveEditorTab(nullptr);
	}
	else
	{
		m_pMainWindow->getIMGEditor()->setActiveEditorTab(m_pMainWindow->getIMGEditor()->getEditorTabs().getEntryByIndex(pTabBar->getActiveIndex()));
	}
}

void		MainLayer::onRemoveTab(Tab *pTab)
{
	m_pMainWindow->getIMGEditor()->removeEditorTab((IMGEditorTab*)m_pMainWindow->getIMGEditor()->getEditorTabs().getEntryByIndex(pTab->getIndex()));
}

// controls
void		MainLayer::addControls(void)
{
	int32
		x, y, y2, w, h, w2, h2, h3;
	uint32
		uiTitleBarHeight, uiButtonHeight, uiLogWidth;
	Menu
		*pMenu1, *pMenu2, *pMenu3, *pMenu4;
	MenuItem
		*pMenuItem1, *pMenuItem2, *pMenuItem3;
	string
		strStyleGroup;

	uiTitleBarHeight = getWindow()->getTitleBarHeight();
	uiButtonHeight = 37;
	uiLogWidth = 335;

	// top left menu
	x = 0;
	y = uiTitleBarHeight;
	w = 70;
	h = uiButtonHeight;
	strStyleGroup = "topLeftMenu";

	pMenu1 = addMenu(x, y, h, w, HORIZONTAL, strStyleGroup, -1, -200);
	pMenu1->addMenuItem("Formats", FORMATS);
	pMenu1->addMenuItem("Utility", UTILITY);

	// top menu - buttons
	x = 139 + 139;
	y = uiTitleBarHeight;
	w = 139;
	h = uiButtonHeight;
	w2 = w;
	strStyleGroup = "topMenu";

	pMenu1 = addMenu(x, y, h, w, HORIZONTAL, strStyleGroup, TOP_MENU, -200);

	pMenuItem1 = pMenu1->addMenuItem("New");
	pMenu2 = pMenuItem1->addMenu(VERTICAL);
	pMenu2->addMenuItem("New File", NEW_FILE);
	pMenu2->addMenuItem("New Window", NEW_WINDOW);

	pMenuItem1 = pMenu1->addMenuItem("Open");
	pMenu2 = pMenuItem1->addMenu(VERTICAL);
	pMenu2->addMenuItem("Open File(s)", OPEN_FILES);
	pMenu2->addMenuItem("Open Folder", OPEN_FOLDER);
	pMenu2->addMenuItem("Open Folder Recursively", OPEN_FOLDER_RECURSIVELY);
	pMenu2->addMenuItem("Reopen", REOPEN_FILE);
	pMenu2->addMenuItem("Open Last Closed File", OPEN_LAST_CLOSED_FILE);

	pMenuItem2 = pMenu2->addMenuItem("Recently Open");
	m_pRecentlyOpenMenu = pMenuItem2->addMenu(VERTICAL);

	pMenuItem2 = pMenu2->addMenuItem("Open File Group");
	m_pFileGroupMenu = pMenuItem2->addMenu(VERTICAL);

	pMenu2->addMenuItem("Open File Folder in Explorer", OPEN_FILE_FOLDER_IN_EXPLORER);

	pMenuItem2 = pMenu2->addMenuItem("Logs");
	pMenu3 = pMenuItem2->addMenu(VERTICAL);
	pMenu3->addMenuItem("Open Today's Logs File", OPEN_TODAYS_LOGS_FILE);
	pMenu3->addMenuItem("Open Logs Folder", OPEN_LOGS_FOLDER);

	pMenuItem1 = pMenu1->addMenuItem("Save", SAVE_MENU);
	pMenu2 = pMenuItem1->addMenu(VERTICAL);
	pMenu2->addMenuItem("Save File", SAVE_FILE);
	pMenu2->addMenuItem("Save As", SAVE_FILE_AS);
	pMenu2->addMenuItem("Save All", SAVE_ALL_FILES);
	pMenu2->addMenuItem("Clone File", CLONE_FILE);
	pMenu2->addMenuItem("Save File Group", SAVE_FILE_GROUP);

	pMenuItem2 = pMenu2->addMenuItem("Logs", SAVE_LOGS_MENU);
	pMenu3 = pMenuItem2->addMenu(VERTICAL);
	pMenu3->addMenuItem("Save Logs", SAVE_LOGS);
	pMenu3->addMenuItem("Save Logs for All Tabs", SAVE_LOGS_ALL_TABS);
	pMenu3->addMenuItem("Clear Logs", CLEAR_LOGS);
	pMenu3->addMenuItem("Clear Logs for All Tabs", CLEAR_LOGS_ALL_TABS);

	pMenuItem1 = pMenu1->addMenuItem("Close");
	pMenu2 = pMenuItem1->addMenu(VERTICAL);
	pMenu2->addMenuItem("Close File", CLOSE_FILE);
	pMenu2->addMenuItem("Close All", CLOSE_ALL_FILES);
	pMenu2->addMenuItem("Exit Tool", EXIT_TOOL);

	// settings icon
	x += w;
	w = uiButtonHeight + 1;
	h = uiButtonHeight;

	m_pSettingsButton = addButton(x, y, w, h, "", "settingsMenuButton", SETTINGS, 5);
	m_pSettingsButtonLine1 = addLine(x + 10, y + 10, x + 27, y + 10, "settingsMenuLine", -1, 10);
	m_pSettingsButtonLine2 = addLine(x + 10, y + 19, x + 27, y + 19, "settingsMenuLine", -1, 10);
	m_pSettingsButtonLine3 = addLine(x + 10, y + 28, x + 27, y + 28, "settingsMenuLine", -1, 10);

	m_pSettingsButton->addLinkedItem(m_pSettingsButtonLine1);
	m_pSettingsButton->addLinkedItem(m_pSettingsButtonLine2);
	m_pSettingsButton->addLinkedItem(m_pSettingsButtonLine3);

	// 2nd left menu - actions
	x = 139;
	y = uiTitleBarHeight + uiButtonHeight;
	w = 139;
	h = uiButtonHeight;
	h2 = h;
	h3 = h2 + 0;
	strStyleGroup = "secondLeftMenu";




	pMenu1 = addMenu(x, y, w, h, VERTICAL, strStyleGroup, SECOND_LEFT_MENU, -200);

	// import
	pMenuItem1 = pMenu1->addMenuItem("Import", IMPORT_MENU);

	pMenu2 = pMenuItem1->addMenu();
	pMenu2->addMenuItem("Import by File(s)", IMPORT_BY_FILES);

	pMenuItem2 = pMenu2->addMenuItem("Import by Folder(s)", IMPORT_BY_FOLDERS_MENU);
	pMenu3 = pMenuItem2->addMenu();
	pMenu3->addMenuItem("Import by Single Folder", IMPORT_BY_SINGLE_FOLDER);
	pMenu3->addMenuItem("Import by Folder Recursively", IMPORT_BY_FOLDER_RECURSIVELY);

	pMenu2->addMenuItem("Import by IDE", IMPORT_BY_IDE);
	pMenu2->addMenuItem("Import by Entry Names", IMPORT_BY_ENTRY_NAMES);

	// export
	pMenuItem1 = pMenu1->addMenuItem("Export", EXPORT_MENU);

	pMenu2 = pMenuItem1->addMenu();
	pMenu2->addMenuItem("Export Selection", EXPORT_SELECTED);
	pMenu2->addMenuItem("Export All Entries", EXPORT_ALL);

	pMenuItem2 = pMenu2->addMenuItem("Export by Column..", EXPORT_BY_COLUMN_MENU);
	pMenu3 = pMenuItem2->addMenu();
	pMenu3->addMenuItem("Export by Index", EXPORT_BY_INDEX);
	pMenu3->addMenuItem("Export by Name", EXPORT_BY_NAME);
	pMenu3->addMenuItem("Export by Offset", EXPORT_BY_OFFSET);
	pMenu3->addMenuItem("Export by Size", EXPORT_BY_SIZE);
	pMenu3->addMenuItem("Export by Type", EXPORT_BY_TYPE);
	pMenu3->addMenuItem("Export by Version", EXPORT_BY_VERSION);

	pMenuItem2 = pMenu2->addMenuItem("Export All Entries into..", EXPORT_ALL_ENTRIES_INTO_MENU);
	pMenu3 = pMenuItem2->addMenu();
	pMenu3->addMenuItem("Export all entries into Grouped Folders by Type", EXPORT_ALL_INTO_GROUPED_FOLDERS_BY_TYPE);

	pMenuItem2 = pMenu2->addMenuItem("Export All Tabs..", EXPORT_ALL_TABS_MENU);
	pMenu3 = pMenuItem2->addMenu();
	pMenu3->addMenuItem("Export all entries from all tabs", EXPORT_ALL_FROM_ALL_TABS);
	pMenu3->addMenuItem("Export all entries from all tabs into grouped folders by type", EXPORT_ALL_FROM_ALL_TABS_INTO_GROUPED_FOLDERS_BY_TYPE);
	pMenu3->addMenuItem("Export selection from all tabs", EXPORT_SELECTION_FROM_ALL_TABS);
	pMenu3->addMenuItem("Export by IDE from All Tabs", EXPORT_BY_IDE_FROM_ALL_TABS);
	pMenu3->addMenuItem("Export by Entry Names from All Tabs", EXPORT_BY_ENTRY_NAMES_FROM_ALL_TABS);

	pMenu2->addMenuItem("Export by IDE", EXPORT_BY_IDE);
	pMenu2->addMenuItem("Export by IPL", EXPORT_BY_IPL);
	pMenu2->addMenuItem("Export by DAT", EXPORT_BY_DAT);
	pMenu2->addMenuItem("Export by Entry Names", EXPORT_BY_ENTRY_NAMES);

	// quick export
	pMenu1->addMenuItem("Quick Export", QUICK_EXPORT);

	// rename
	pMenuItem1 = pMenu1->addMenuItem("Rename", RENAME);
	pMenuItem1->setStyleGroups(string("thirdItemVertically"));

	// replace
	pMenuItem1 = pMenu1->addMenuItem("Replace", REPLACE_MENU);

	pMenu2 = pMenuItem1->addMenu();
	pMenuItem2 = pMenu2->addMenuItem("Replace by File(s)", REPLACE_BY_FILES);
	pMenuItem2 = pMenu2->addMenuItem("Replace by Folder..", REPLACE_BY_FOLDER_MENU);

	pMenu3 = pMenuItem2->addMenu();
	pMenuItem3 = pMenu3->addMenuItem("Replace by Single Folder", REPLACE_BY_SINGLE_FOLDER);
	pMenuItem3 = pMenu3->addMenuItem("Replace by Folder Recursively", REPLACE_BY_FOLDER_RECURSIVELY);

	pMenuItem2 = pMenu2->addMenuItem("Replace by IDE", REPLACE_BY_IDE);

	// remove
	pMenuItem1 = pMenu1->addMenuItem("Remove", REMOVE_MENU);

	pMenu2 = pMenuItem1->addMenu();
	pMenu2->addMenuItem("Remove Selection", REMOVE_SELECTED);
	pMenu2->addMenuItem("Remove All Entries", REMOVE_ALL);
	pMenuItem2 = pMenu2->addMenuItem("Remove by Column..", REMOVE_BY_COLUMN_MENU);

	pMenu3 = pMenuItem2->addMenu();
	pMenu3->addMenuItem("Remove by Index", REMOVE_BY_INDEX);
	pMenu3->addMenuItem("Remove by Name", REMOVE_BY_NAME);
	pMenu3->addMenuItem("Remove by Offset", REMOVE_BY_OFFSET);
	pMenu3->addMenuItem("Remove by Size", REMOVE_BY_SIZE);
	pMenu3->addMenuItem("Remove by Type", REMOVE_BY_TYPE);
	pMenu3->addMenuItem("Remove by Version", REMOVE_BY_VERSION);

	pMenu2->addMenuItem("Remove by IDE", REMOVE_BY_IDE);
	pMenu2->addMenuItem("Remove by Entry Names", REMOVE_BY_ENTRY_NAMES);

	// merge
	pMenuItem1 = pMenu1->addMenuItem("Merge", MERGE);
	pMenuItem1->setStyleGroups(string("thirdItemVertically"));

	// split
	pMenuItem1 = pMenu1->addMenuItem("Split", SPLIT_MENU);

	pMenu2 = pMenuItem1->addMenu();
	pMenuItem2 = pMenu2->addMenuItem("Split Selection", SPLIT_SELECTED);
	pMenuItem2 = pMenu2->addMenuItem("Split by IDE", SPLIT_BY_IDE);
	pMenuItem2 = pMenu2->addMenuItem("Split by Entry Names", SPLIT_BY_ENTRY_NAMES);

	// convert
	pMenuItem1 = pMenu1->addMenuItem("Convert", CONVERT_MENU);
	pMenu2 = pMenuItem1->addMenu();

	pMenuItem2 = pMenu2->addMenuItem("IMG", CONVERT_IMG_MENU);
	pMenu3 = pMenuItem2->addMenu();
	pMenuItem3 = pMenu3->addMenuItem("Convert IMG Version", CONVERT_IMG_VERSION);

	pMenuItem2 = pMenu2->addMenuItem("COL", CONVERT_COL_MENU);
	pMenu3 = pMenuItem2->addMenu();
	pMenuItem3 = pMenu3->addMenuItem("Convert COL Version for Selection", CONVERT_SELECTED_COL_VERSION);

	pMenuItem2 = pMenu2->addMenuItem("DFF", CONVERT_DFF_MENU);
	pMenu3 = pMenuItem2->addMenu();
	pMenuItem3 = pMenu3->addMenuItem("Convert DFF RW Version for Selection", CONVERT_SELECTED_DFF_RW_VERSION);
	pMenuItem3 = pMenu3->addMenuItem("Convert DFF to WDR for Selection", CONVERT_SELECTED_DFF_TO_WDR);

	pMenuItem2 = pMenu2->addMenuItem("TXD", CONVERT_TXD_MENU);
	pMenu3 = pMenuItem2->addMenu();
	pMenuItem3 = pMenu3->addMenuItem("Convert TXD RW Version for Selection", CONVERT_SELECTED_TXD_RW_VERSION);
	pMenuItem3 = pMenu3->addMenuItem("Convert TXD to Game for Selection", CONVERT_SELECTED_TXD_TO_GAME);
	pMenuItem3 = pMenu3->addMenuItem("Convert TXD to Texture Format for Selection", CONVERT_SELECTED_TXD_TO_TEXTURE_FORMAT);

	pMenuItem2 = pMenu2->addMenuItem("WTD", CONVERT_WTD_MENU);
	pMenu3 = pMenuItem2->addMenu();
	pMenuItem3 = pMenu3->addMenuItem("Convert WTD to TXD for Selection", CONVERT_SELECTED_WTD_TO_TXD);

	// select
	pMenuItem1 = pMenu1->addMenuItem("Select", SELECT_MENU);
	pMenuItem1->setStyleGroups(string("thirdItemVertically"));

	pMenu2 = pMenuItem1->addMenu();
	pMenu2->addMenuItem("Select All Entries", SELECT_ALL);
	pMenu2->addMenuItem("Unselect All Entries", UNSELECT_ALL);
	pMenu2->addMenuItem("Select Inverse", SELECT_INVERSE);
	pMenuItem2 = pMenu2->addMenuItem("Select by Column..", SELECT_BY_COLUMN_MENU);

	pMenu3 = pMenuItem2->addMenu();
	pMenu3->addMenuItem("Select by Index", SELECT_BY_INDEX);
	pMenu3->addMenuItem("Select by Name", SELECT_BY_NAME);
	pMenu3->addMenuItem("Select by Offset", SELECT_BY_OFFSET);
	pMenu3->addMenuItem("Select by Size", SELECT_BY_SIZE);
	pMenu3->addMenuItem("Select by Type", SELECT_BY_TYPE);
	pMenu3->addMenuItem("Select by Version", SELECT_BY_VERSION);

	pMenu2->addMenuItem("Select by IDE", SELECT_BY_IDE);

	pMenuItem2 = pMenu2->addMenuItem("Unselect by Column..", UNSELECT_BY_COLUMN_MENU);

	pMenu3 = pMenuItem2->addMenu();
	pMenu3->addMenuItem("Unselect by Index", UNSELECT_BY_INDEX);
	pMenu3->addMenuItem("Unselect by Name", UNSELECT_BY_NAME);
	pMenu3->addMenuItem("Unselect by Offset", UNSELECT_BY_OFFSET);
	pMenu3->addMenuItem("Unselect by Size", UNSELECT_BY_SIZE);
	pMenu3->addMenuItem("Unselect by Type", UNSELECT_BY_TYPE);
	pMenu3->addMenuItem("Unselect by Version", UNSELECT_BY_VERSION);

	pMenu2->addMenuItem("Unselect by IDE", UNSELECT_BY_IDE);

	// sort
	pMenuItem1 = pMenu1->addMenuItem("Sort", SORT_MENU);

	pMenu2 = pMenuItem1->addMenu();
	pMenuItem2 = pMenu2->addMenuItem("Sort by Index..", SORT_BY_INDEX_MENU);

	pMenu3 = pMenuItem2->addMenu();
	pMenu3->addMenuItem("Sort by Index (Reverse)", SORT_BY_INDEX_REVERSE);

	pMenuItem2 = pMenu2->addMenuItem("Sort by Name..", SORT_BY_NAME_MENU);

	pMenu3 = pMenuItem2->addMenu();
	pMenu3->addMenuItem("Sort by Name Ascending (0-9, A-Z)", SORT_BY_NAME_ASCENDING_09AZ);
	//pMenu3->addMenuItem("Sort by Name Ascending (A-Z, 0-9)", SORT_BY_NAME_ASCENDING_AZ09);
	pMenu3->addMenuItem("Sort by Name Descending (Z-A, 9-0)", SORT_BY_NAME_DESCENDING_ZA90);
	//pMenu3->addMenuItem("Sort by Name Descending (9-0, Z-A)", SORT_BY_NAME_DESCENDING_90ZA);

	pMenuItem2 = pMenu2->addMenuItem("Sort by Offset..", SORT_BY_OFFSET_MENU);

	pMenu3 = pMenuItem2->addMenu();
	pMenu3->addMenuItem("Sort by Offset (Low-High)", SORT_BY_OFFSET_LOW_HIGH);
	pMenu3->addMenuItem("Sort by Offset (High-Low)", SORT_BY_OFFSET_HIGH_LOW);

	pMenuItem2 = pMenu2->addMenuItem("Sort by Size..", SORT_BY_SIZE_MENU);

	pMenu3 = pMenuItem2->addMenu();
	pMenu3->addMenuItem("Sort by Size (Small-Big)", SORT_BY_SIZE_SMALL_BIG);
	pMenu3->addMenuItem("Sort by Size (Big-Small)", SORT_BY_SIZE_BIG_SMALL);

	pMenuItem2 = pMenu2->addMenuItem("Sort by Type..", SORT_BY_TYPE_MENU);

	pMenu3 = pMenuItem2->addMenu();
	pMenu3->addMenuItem("Sort by Type (A-Z)", SORT_BY_TYPE_AZ);
	pMenu3->addMenuItem("Sort by Type (Z-A)", SORT_BY_TYPE_ZA);

	pMenuItem2 = pMenu2->addMenuItem("Sort by Version..", SORT_BY_VERSION_MENU);

	pMenu3 = pMenuItem2->addMenu();
	pMenu3->addMenuItem("Sort by Version (Old-New)", SORT_BY_VERSION_OLD_NEW);
	pMenu3->addMenuItem("Sort by Version (New-Old)", SORT_BY_VERSION_NEW_OLD);

	// LST
	pMenu1->addMenuItem("LST", LST);

	// entry
	pMenuItem1 = pMenu1->addMenuItem("Entry", ENTRY_MENU);
	pMenuItem1->setStyleGroups(string("thirdItemVertically"));

	pMenu2 = pMenuItem1->addMenu();

	pMenuItem2 = pMenu2->addMenuItem("Entry Name Case", ENTRY_NAME_CASE_MENU);
	pMenu3 = pMenuItem2->addMenu();
	pMenu3->addMenuItem("lower case", NAME_CASE_LOWER);
	pMenu3->addMenuItem("UPPER CASE", NAME_CASE_UPPER);
	pMenu3->addMenuItem("Title Case", NAME_CASE_TITLE);

	pMenuItem2 = pMenu2->addMenuItem("Copy Entry Data", ENTRY_COPY_DATA_MENU);
	pMenu3 = pMenuItem2->addMenu();
	pMenu3->addMenuItem("Copy Entries Index", COPY_ENTRY_INDEX);
	pMenu3->addMenuItem("Copy Entries Type", COPY_ENTRY_TYPE);
	pMenu3->addMenuItem("Copy Entries Name", COPY_ENTRY_NAME);
	pMenu3->addMenuItem("Copy Entries Offset", COPY_ENTRY_OFFSET);
	pMenu3->addMenuItem("Copy Entries Size", COPY_ENTRY_SIZE);
	pMenu3->addMenuItem("Copy Entries Version", COPY_ENTRY_VERSION);
	pMenu3->addMenuItem("Copy Entries Row Data", COPY_ENTRY_ROW_DATA);

	pMenuItem2 = pMenu2->addMenuItem("Shift Entry", ENTRY_SHIFT_MENU);
	pMenu3 = pMenuItem2->addMenu();
	pMenu3->addMenuItem("Shift Entries Up 1 Row", SHIFT_ENTRY_UP_1_ROW);
	pMenu3->addMenuItem("Shift Entries Up 5 Rows", SHIFT_ENTRY_UP_5_ROWS);
	pMenu3->addMenuItem("Shift Entries Up 10 Rows", SHIFT_ENTRY_UP_10_ROWS);
	pMenu3->addMenuItem("Shift Entries Up 100 Rows", SHIFT_ENTRY_UP_100_ROWS);
	pMenu3->addMenuItem("Shift Entries Up 1000 Rows", SHIFT_ENTRY_UP_1000_ROWS);
	pMenu3->addMenuItem("Shift Entries Down 1 Row", SHIFT_ENTRY_DOWN_1_ROW);
	pMenu3->addMenuItem("Shift Entries Down 5 Rows", SHIFT_ENTRY_DOWN_5_ROWS);
	pMenu3->addMenuItem("Shift Entries Down 10 Rows", SHIFT_ENTRY_DOWN_10_ROWS);
	pMenu3->addMenuItem("Shift Entries Down 100 Rows", SHIFT_ENTRY_DOWN_100_ROWS);
	pMenu3->addMenuItem("Shift Entries Down 1000 Rows", SHIFT_ENTRY_DOWN_1000_ROWS);

	// orphan entries
	pMenuItem1 = pMenu1->addMenuItem("Orphan Entries", ORPHAN_ENTRIES_MENU);
	pMenu2 = pMenuItem1->addMenu();
	pMenu2->addMenuItem("Remove Orphan Textures from DFF Entries", REMOVE_ORPHAN_TEXTURES_FROM_DFF_ENTRIES);
	pMenu2->addMenuItem("Find Orphan IMG Entries not in IDE", FIND_ORPHAN_IMG_ENTRIES_NOT_IN_IDE);
	pMenu2->addMenuItem("Find Orphan IDE Entries not in IMG", FIND_ORPHAN_IDE_ENTRIES_NOT_IN_IMG);
	pMenu2->addMenuItem("Find Orphan TXD Textures for DFFs in IMG by IDE", FIND_ORPHAN_TXD_TEXTURES_FOR_DFFS_IN_IMG_BY_IDE);

	// tools
	pMenuItem1 = pMenu1->addMenuItem("Tools");
	pMenuItem1->setStyleGroups(string("thirdItemVertically"));

	pMenu2 = pMenuItem1->addMenu();
	pMenu2->addMenuItem("Dump", DUMP);
	pMenu2->addMenuItem("Session Manager", SESSION_MANAGER);
	pMenu2->addMenuItem("Renamer", RENAMER);
	pMenu2->addMenuItem("TXD Builder", TXD_BUILDER);
	pMenu2->addMenuItem("TXD Organizer", TXD_ORGANIZER);
	pMenu2->addMenuItem("DAT Paths Mover", DAT_PATHS_MOVER);
	pMenu2->addMenuItem("Map Mover and ID Shifter", MAP_MOVER_AND_ID_SHIFTER);

	// other
	pMenuItem1 = pMenu1->addMenuItem("Other");

	pMenu2 = pMenuItem1->addMenu();
	pMenu2->addMenuItem("Texture List", TEXTURE_LIST);
	pMenu2->addMenuItem("Stats", STATS);

	pMenuItem2 = pMenu2->addMenuItem("Find Duplicate Entries");
	pMenu3 = pMenuItem2->addMenu();
	pMenu3->addMenuItem("Find Duplicate Entries in Selection", FIND_DUPLICATE_ENTRIES_IN_SELECTION);
	pMenu3->addMenuItem("Find Duplicate Entries in Tab", FIND_DUPLICATE_ENTRIES_IN_TAB);
	pMenu3->addMenuItem("Find Duplicate Entries in All Tabs", FIND_DUPLICATE_ENTRIES_IN_ALL_TABS);
	pMenu3->addMenuItem("Find Duplicate Entries by DAT", FIND_DUPLICATE_ENTRIES_BY_DAT);

	pMenu2->addMenuItem("Compare IMGs", COMPARE_IMGS);
	pMenu2->addMenuItem("Model List for IDE/IPL by DAT", MODEL_LIST_FOR_IDE_AND_IPL_BY_DAT);
	pMenu2->addMenuItem("Save IMG Signature", SAVE_IMG_SIGNATURE);
	pMenu2->addMenuItem("Verify IMG Signature", VERIFY_IMG_SIGNATURE);
	pMenu2->addMenuItem("Validate DFF in Tab", VALIDATE_DFF_IN_TAB);
	pMenu2->addMenuItem("Validate TXD in Tab", VALIDATE_TXD_IN_TAB);
	pMenu2->addMenuItem("Center COL Meshes in Selection", CENTER_COL_MESHES_IN_SELECTION);
	pMenu2->addMenuItem("Align COL Meshes to DFF Meshes", ALIGN_COL_MESHES_TO_DFF_MESHES);
	pMenu2->addMenuItem("Extract DVC and NVC into DFFs", EXTRACT_DVC_AND_NVC_INTO_DFFS);
	pMenu2->addMenuItem("Extract 2DFX into DFFs", EXTRACT_2DFX_INTO_DFFS);
	pMenu2->addMenuItem("IMG Compression", IMG_COMPRESSION);
	pMenu2->addMenuItem("Generate COL from DFF", GENERATE_COL_FROM_DFF);
	
	// set certain items enabled
	setCertainMenuItemsEnabled(false);




	// logo
	x = 139 + 14;
	y = uiTitleBarHeight;
	w = 0;
	h = 0;

	addImage(x, y, DataPath::getDataPath() + "Images/Logo.png", w, h);
}

void						MainLayer::setCertainMenuItemsEnabled(bool bEnabled)
{
	// disable certain menu items
	vector<EInputItem> vecMenuItemIds = {
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
		IMPORT_BY_IDE,
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
		EXPORT_BY_IDE,
		EXPORT_BY_IDE_FROM_ALL_TABS,
		EXPORT_BY_IPL,
		EXPORT_BY_DAT,
		EXPORT_BY_ENTRY_NAMES,
		EXPORT_BY_ENTRY_NAMES_FROM_ALL_TABS,

		QUICK_EXPORT,

		RENAME,

		REPLACE_BY_FILES,
		REPLACE_BY_SINGLE_FOLDER,
		REPLACE_BY_FOLDER_RECURSIVELY,
		REPLACE_BY_IDE,

		REMOVE_SELECTED,
		REMOVE_ALL,
		REMOVE_BY_INDEX,
		REMOVE_BY_NAME,
		REMOVE_BY_OFFSET,
		REMOVE_BY_SIZE,
		REMOVE_BY_TYPE,
		REMOVE_BY_VERSION,
		REMOVE_BY_IDE,
		REMOVE_BY_ENTRY_NAMES,

		MERGE,

		SPLIT_SELECTED,
		SPLIT_BY_IDE,
		SPLIT_BY_ENTRY_NAMES,

		CONVERT_IMG_VERSION,
		CONVERT_SELECTED_COL_VERSION,
		CONVERT_SELECTED_DFF_RW_VERSION,
		CONVERT_SELECTED_DFF_TO_WDR,
		CONVERT_SELECTED_TXD_RW_VERSION,
		CONVERT_SELECTED_TXD_TO_GAME,
		CONVERT_SELECTED_TXD_TO_TEXTURE_FORMAT,
		CONVERT_SELECTED_WTD_TO_TXD,

		SELECT_ALL,
		UNSELECT_ALL,
		SELECT_INVERSE,
		SELECT_BY_INDEX,
		SELECT_BY_NAME,
		SELECT_BY_OFFSET,
		SELECT_BY_SIZE,
		SELECT_BY_TYPE,
		SELECT_BY_VERSION,
		SELECT_BY_IDE,
		UNSELECT_BY_INDEX,
		UNSELECT_BY_NAME,
		UNSELECT_BY_OFFSET,
		UNSELECT_BY_SIZE,
		UNSELECT_BY_TYPE,
		UNSELECT_BY_VERSION,
		UNSELECT_BY_IDE,

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
		SHIFT_ENTRY_DOWN_1000_ROWS,

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
		IMG_COMPRESSION
	};
	
	for (EInputItem uiMenuItemId : vecMenuItemIds)
	{
		MenuItem *pMenuItem = (MenuItem*) m_pWindow->getItemById(uiMenuItemId);
		if (pMenuItem)
		{
			pMenuItem->setEnabled(bEnabled);
		}
	}

	Menu *pMenu;

	pMenu = (Menu*)m_pWindow->getItemById(TOP_MENU);
	pMenu->render();

	pMenu = (Menu*)m_pWindow->getItemById(SECOND_LEFT_MENU);
	pMenu->render();
}

void		MainLayer::initControls(void)
{
	bindEventConst<void>(CHANGE_TAB, &MainLayer::onChangeTab);
	bindEvent(REMOVE_TAB, &MainLayer::onRemoveTab);

	bindEvent(RESIZE_WINDOW, &MainLayer::repositionAndResizeControls);
	repositionAndResizeControls(Vec2i(0, 0));
}

void		MainLayer::repositionAndResizeControls(Vec2i& vecSizeDifference)
{
	Window *pWindow = getWindow();

	Vec2i point;
	Vec2u size;
	int32 x, y, iNewX, iNewWidth;
	uint32 uiButtonHeight, uiLogWidth;

	uiButtonHeight = 37;
	uiLogWidth = 335;

	// settings icon
	point = m_pSettingsButton->getPosition();
	iNewX = pWindow->getSize().x - (uiButtonHeight + 1);
	m_pSettingsButton->setPosition(Vec2i(iNewX, point.y));

	x = m_pWindow->getSize().x - (uiButtonHeight + 1);
	y = m_pWindow->getTitleBarHeight();
	m_pSettingsButtonLine1->setPoint1(Vec2i(x + 10, y + 10));
	m_pSettingsButtonLine1->setPoint2(Vec2i(x + 27, y + 10));
	m_pSettingsButtonLine2->setPoint1(Vec2i(x + 10, y + 19));
	m_pSettingsButtonLine2->setPoint2(Vec2i(x + 27, y + 19));
	m_pSettingsButtonLine3->setPoint1(Vec2i(x + 10, y + 28));
	m_pSettingsButtonLine3->setPoint2(Vec2i(x + 27, y + 28));
}