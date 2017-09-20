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

using namespace std;
using namespace bxcf;
using namespace bxgx;
using namespace bxgx::events;
using namespace imgf;
using namespace imgf::layers;
using namespace imgf::mainLayer::input;

MainLayer::MainLayer(void) :
	m_pMainWindow(nullptr),
	m_pTabBar(nullptr),
	m_pSettingsButton(nullptr),
	m_pSettingsButtonLine1(nullptr),
	m_pSettingsButtonLine2(nullptr),
	m_pSettingsButtonLine3(nullptr),
	m_pText_FilePath(nullptr),
	m_pText_FileVersion(nullptr),
	m_pText_FileGame(nullptr),
	m_pText_FileEntryCount(nullptr),
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
		m_pMainWindow->getIMGEditor()->setActiveFile(nullptr);
	}
	else
	{
		m_pMainWindow->getIMGEditor()->setActiveFile(m_pMainWindow->getIMGEditor()->getTabs().getEntryByIndex(pTabBar->getActiveIndex()));
	}
}

void		MainLayer::onRemoveTab(Tab *pTab)
{
	m_pMainWindow->getIMGEditor()->removeFile((IMGEditorTab*)m_pMainWindow->getIMGEditor()->getTabs().getEntryByIndex(pTab->getIndex()));
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

	// game information headers
	x = 149 + 139;
	y = (uiTitleBarHeight - 1) + uiButtonHeight + 10;
	y2 = y;
	w = 80;
	h = 20;
	h2 = 20;
	strStyleGroup = "gameInfoText";

	addText(x, y, w, h, "Path", strStyleGroup, -1, -150);
	y += h2;
	addText(x, y, w, h, "Version", strStyleGroup, -1, -150);
	y += h2;
	addText(x, y, w, h, "Game", strStyleGroup, -1, -150);
	y += h2;
	addText(x, y, w, h, "Entries", strStyleGroup, -1, -150);

	// game information values
	x += 90;
	y = y2;
	w = 415;
	w2 = 200;

	m_pText_FilePath = addText(x, y, w, h, "No file is open", strStyleGroup, -1, -150);
	y += h2;
	m_pText_FileVersion = addText(x, y, w2, h, "-", strStyleGroup, -1, -150);
	y += h2;
	m_pText_FileGame = addText(x, y, w2, h, "-", strStyleGroup, -1, -150);
	y += h2;
	m_pText_FileEntryCount = addText(x, y, w2, h, "-", strStyleGroup, -1, -150);

	// top menu - buttons
	x = 139 + 139;
	y = uiTitleBarHeight;
	w = 139;
	h = uiButtonHeight;
	w2 = w;
	strStyleGroup = "topMenu";

	pMenu1 = addMenu(x, y, h, w, HORIZONTAL, strStyleGroup, -1, -200);
	
	pMenuItem1 = pMenu1->addMenuItem("New", NEW_FILE);
	pMenu2 = pMenuItem1->addMenu(VERTICAL);
	pMenu2->addMenuItem("New File", NEW_FILE);
	pMenu2->addMenuItem("New Window", NEW_WINDOW);

	pMenuItem1 = pMenu1->addMenuItem("Open", OPEN_FILES);
	pMenu2 = pMenuItem1->addMenu(VERTICAL);
	pMenu2->addMenuItem("Open File(s)", OPEN_FILES);
	pMenu2->addMenuItem("Open Folder", OPEN_FOLDER);
	pMenu2->addMenuItem("Open Folder Recursively", OPEN_FOLDER_RECURSIVELY);
	pMenu2->addMenuItem("Reopen", REOPEN_FILE);
	pMenu2->addMenuItem("Open Last Closed File", OPEN_LAST_CLOSED_FILE);
	
	pMenuItem1 = pMenu2->addMenuItem("Recently Open");
	m_pRecentlyOpenMenu = pMenuItem1->addMenu(VERTICAL);

	pMenuItem1 = pMenu2->addMenuItem("Open File Group");
	m_pFileGroupMenu = pMenuItem1->addMenu(VERTICAL);

	pMenu2->addMenuItem("Open File Folder in Explorer", OPEN_FILE_FOLDER_IN_EXPLORER);
	pMenu2->addMenuItem("Open Today's Logs File", OPEN_TODAYS_LOGS_FILE);
	pMenu2->addMenuItem("Open Logs Folder", OPEN_LOGS_FOLDER);

	pMenuItem1 = pMenu1->addMenuItem("Save", SAVE_FILE);
	pMenu2 = pMenuItem1->addMenu(VERTICAL);
	pMenu2->addMenuItem("Save File", SAVE_FILE);
	pMenu2->addMenuItem("Save As", SAVE_FILE_AS);
	pMenu2->addMenuItem("Save All", SAVE_ALL_FILES);
	pMenu2->addMenuItem("Clone File", CLONE_FILE);
	pMenu2->addMenuItem("Save File Group", SAVE_FILE_GROUP);
	pMenu2->addMenuItem("Save Logs", SAVE_LOGS);
	pMenu2->addMenuItem("Save Logs for All Tabs", SAVE_LOGS_ALL_TABS);
	pMenu2->addMenuItem("Clear Logs", CLEAR_LOGS);
	pMenu2->addMenuItem("Clear Logs for All Tabs", CLEAR_LOGS_ALL_TABS);

	pMenuItem1 = pMenu1->addMenuItem("Close", CLOSE_FILE);
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

	// files tab bar
	x = 139 + 139;
	y = 162;
	w = m_pWindow->getSize().x - x - uiLogWidth;
	h = 30;
	strStyleGroup = "fileTabBar";

	m_pTabBar = addTabBar(x, y, w, h, strStyleGroup);
	m_pTabBar->setDefaultText("No tabs to display");

	/*
	Tab * pTab;
	pTab = m_pTabBar->addTab("gta3.img (1000)", true, "firstItemHorizontally");
	pTab = m_pTabBar->addTab("gta3 - backup.img (1200)");
	pTab = m_pTabBar->addTab("gta3.img (1000)");
	*/

	// 2nd left menu - actions
	x = 139;
	y = uiTitleBarHeight + uiButtonHeight;
	w = 139;
	h = uiButtonHeight;
	h2 = h;
	h3 = h2 + 0;
	strStyleGroup = "secondLeftMenu";




	pMenu1 = addMenu(x, y, w, h, VERTICAL, strStyleGroup, -1, -200);

	// import
	pMenuItem1 = pMenu1->addMenuItem("Import");

	pMenu2 = pMenuItem1->addMenu();
	pMenu2->addMenuItem("Import by File(s)", IMPORT_BY_FILES);

	pMenuItem2 = pMenu2->addMenuItem("Import by Folder(s)");
	pMenu3 = pMenuItem2->addMenu();
	pMenu3->addMenuItem("Import by Single Folder", IMPORT_BY_SINGLE_FOLDER);
	pMenu3->addMenuItem("Import by Folder Recursively", IMPORT_BY_FOLDER_RECURSIVELY);

	pMenu2->addMenuItem("Import by IDE", IMPORT_BY_IDE);
	pMenu2->addMenuItem("Import by Entry Names", IMPORT_BY_ENTRY_NAMES);

	// export
	pMenuItem1 = pMenu1->addMenuItem("Export");

	pMenu2 = pMenuItem1->addMenu();
	pMenu2->addMenuItem("Export Selection", EXPORT_SELECTED);
	pMenu2->addMenuItem("Export All Entries", EXPORT_ALL);

	pMenuItem2 = pMenu2->addMenuItem("Export by Column..");
	pMenu3 = pMenuItem2->addMenu();
	pMenu3->addMenuItem("Export by Index", EXPORT_BY_INDEX);
	pMenu3->addMenuItem("Export by Name", EXPORT_BY_NAME);
	pMenu3->addMenuItem("Export by Offset", EXPORT_BY_OFFSET);
	pMenu3->addMenuItem("Export by Size", EXPORT_BY_SIZE);
	pMenu3->addMenuItem("Export by Type", EXPORT_BY_TYPE);
	pMenu3->addMenuItem("Export by Version", EXPORT_BY_VERSION);

	pMenuItem2 = pMenu2->addMenuItem("Export All Entries into..");
	pMenu3 = pMenuItem2->addMenu();
	pMenu3->addMenuItem("Export all entries into Grouped Folders by Type", EXPORT_ALL_INTO_GROUPED_FOLDERS_BY_TYPE);

	pMenuItem2 = pMenu2->addMenuItem("Export All Tabs..");
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
	pMenuItem1 = pMenu1->addMenuItem("Replace");

	pMenu2 = pMenuItem1->addMenu();
	pMenuItem2 = pMenu2->addMenuItem("Replace by File(s)", REPLACE_BY_FILES);
	pMenuItem2 = pMenu2->addMenuItem("Replace by Folder..");

	pMenu3 = pMenuItem2->addMenu();
	pMenuItem3 = pMenu3->addMenuItem("Replace by Single Folder", REPLACE_BY_SINGLE_FOLDER);
	pMenuItem3 = pMenu3->addMenuItem("Replace by Folder Recursively", REPLACE_BY_FOLDER_RECURSIVELY);

	pMenuItem2 = pMenu2->addMenuItem("Replace by IDE", REPLACE_BY_IDE);

	// remove
	pMenuItem1 = pMenu1->addMenuItem("Remove");

	pMenu2 = pMenuItem1->addMenu();
	pMenu2->addMenuItem("Remove Selection", REMOVE_SELECTED);
	pMenu2->addMenuItem("Remove All Entries", REMOVE_ALL);
	pMenuItem2 = pMenu2->addMenuItem("Remove by Column..");

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
	pMenuItem1 = pMenu1->addMenuItem("Split");

	pMenu2 = pMenuItem1->addMenu();
	pMenuItem2 = pMenu2->addMenuItem("Split Selection", SPLIT_SELECTED);
	pMenuItem2 = pMenu2->addMenuItem("Split by IDE", SPLIT_BY_IDE);
	pMenuItem2 = pMenu2->addMenuItem("Split by Entry Names", SPLIT_BY_ENTRY_NAMES);

	// convert
	pMenuItem1 = pMenu1->addMenuItem("Convert");
	pMenu2 = pMenuItem1->addMenu();

	pMenuItem2 = pMenu2->addMenuItem("IMG");
	pMenu3 = pMenuItem2->addMenu();
	pMenuItem3 = pMenu3->addMenuItem("Convert IMG Version", CONVERT_IMG_VERSION);

	pMenuItem2 = pMenu2->addMenuItem("COL");
	pMenu3 = pMenuItem2->addMenu();
	pMenuItem3 = pMenu3->addMenuItem("Convert COL Version for Selection", CONVERT_SELECTED_COL_VERSION);

	pMenuItem2 = pMenu2->addMenuItem("DFF");
	pMenu3 = pMenuItem2->addMenu();
	pMenuItem3 = pMenu3->addMenuItem("Convert DFF RW Version for Selection", CONVERT_SELECTED_DFF_RW_VERSION);
	pMenuItem3 = pMenu3->addMenuItem("Convert DFF to WDR for Selection", CONVERT_SELECTED_DFF_TO_WDR);
	
	pMenuItem2 = pMenu2->addMenuItem("TXD");
	pMenu3 = pMenuItem2->addMenu();
	pMenuItem3 = pMenu3->addMenuItem("Convert TXD RW Version for Selection", CONVERT_SELECTED_TXD_RW_VERSION);
	pMenuItem3 = pMenu3->addMenuItem("Convert TXD to Game for Selection", CONVERT_SELECTED_TXD_TO_GAME);
	pMenuItem3 = pMenu3->addMenuItem("Convert TXD to Texture Format for Selection", CONVERT_SELECTED_TXD_TO_TEXTURE_FORMAT);

	pMenuItem2 = pMenu2->addMenuItem("WTD");
	pMenu3 = pMenuItem2->addMenu();
	pMenuItem3 = pMenu3->addMenuItem("Convert WTD to TXD for Selection", CONVERT_SELECTED_WTD_TO_TXD);

	// select
	pMenuItem1 = pMenu1->addMenuItem("Select");
	pMenuItem1->setStyleGroups(string("thirdItemVertically"));

	pMenu2 = pMenuItem1->addMenu();
	pMenu2->addMenuItem("Select All Entries", SELECT_ALL);
	pMenu2->addMenuItem("Unselect All Entries", UNSELECT_ALL);
	pMenu2->addMenuItem("Select Inverse", SELECT_INVERSE);
	pMenuItem2 = pMenu2->addMenuItem("Select by Column..");

	pMenu3 = pMenuItem2->addMenu();
	pMenu3->addMenuItem("Select by Index", SELECT_BY_INDEX);
	pMenu3->addMenuItem("Select by Name", SELECT_BY_NAME);
	pMenu3->addMenuItem("Select by Offset", SELECT_BY_OFFSET);
	pMenu3->addMenuItem("Select by Size", SELECT_BY_SIZE);
	pMenu3->addMenuItem("Select by Type", SELECT_BY_TYPE);
	pMenu3->addMenuItem("Select by Version", SELECT_BY_VERSION);

	pMenu2->addMenuItem("Select by IDE", SELECT_BY_IDE);

	pMenuItem2 = pMenu2->addMenuItem("Unselect by Column..");

	pMenu3 = pMenuItem2->addMenu();
	pMenu3->addMenuItem("Unselect by Index", UNSELECT_BY_INDEX);
	pMenu3->addMenuItem("Unselect by Name", UNSELECT_BY_NAME);
	pMenu3->addMenuItem("Unselect by Offset", UNSELECT_BY_OFFSET);
	pMenu3->addMenuItem("Unselect by Size", UNSELECT_BY_SIZE);
	pMenu3->addMenuItem("Unselect by Type", UNSELECT_BY_TYPE);
	pMenu3->addMenuItem("Unselect by Version", UNSELECT_BY_VERSION);
	
	pMenu2->addMenuItem("Unselect by IDE", UNSELECT_BY_IDE);

	// sort
	pMenuItem1 = pMenu1->addMenuItem("Sort");

	pMenu2 = pMenuItem1->addMenu();
	pMenuItem2 = pMenu2->addMenuItem("Sort by Index..");

	pMenu3 = pMenuItem2->addMenu();
	pMenu3->addMenuItem("Sort by Index (Reverse)", SORT_BY_INDEX_REVERSE);

	pMenuItem2 = pMenu2->addMenuItem("Sort by Name..");

	pMenu3 = pMenuItem2->addMenu();
	pMenu3->addMenuItem("Sort by Name Ascending (0-9, A-Z)", SORT_BY_NAME_ASCENDING_09AZ);
	//pMenu3->addMenuItem("Sort by Name Ascending (A-Z, 0-9)", SORT_BY_NAME_ASCENDING_AZ09);
	pMenu3->addMenuItem("Sort by Name Descending (Z-A, 9-0)", SORT_BY_NAME_DESCENDING_ZA90);
	//pMenu3->addMenuItem("Sort by Name Descending (9-0, Z-A)", SORT_BY_NAME_DESCENDING_90ZA);

	pMenuItem2 = pMenu2->addMenuItem("Sort by Offset..");

	pMenu3 = pMenuItem2->addMenu();
	pMenu3->addMenuItem("Sort by Offset (Low-High)", SORT_BY_OFFSET_LOW_HIGH);
	pMenu3->addMenuItem("Sort by Offset (High-Low)", SORT_BY_OFFSET_HIGH_LOW);

	pMenuItem2 = pMenu2->addMenuItem("Sort by Size..");

	pMenu3 = pMenuItem2->addMenu();
	pMenu3->addMenuItem("Sort by Size (Small-Big)", SORT_BY_SIZE_SMALL_BIG);
	pMenu3->addMenuItem("Sort by Size (Big-Small)", SORT_BY_SIZE_BIG_SMALL);

	pMenuItem2 = pMenu2->addMenuItem("Sort by Type..");

	pMenu3 = pMenuItem2->addMenu();
	pMenu3->addMenuItem("Sort by Type (A-Z)", SORT_BY_TYPE_AZ);
	pMenu3->addMenuItem("Sort by Type (Z-A)", SORT_BY_TYPE_ZA);

	pMenuItem2 = pMenu2->addMenuItem("Sort by Version..");

	pMenu3 = pMenuItem2->addMenu();
	pMenu3->addMenuItem("Sort by Version (Old-New)", SORT_BY_VERSION_OLD_NEW);
	pMenu3->addMenuItem("Sort by Version (New-Old)", SORT_BY_VERSION_NEW_OLD);

	// LST
	pMenu1->addMenuItem("LST", LST);

	// entry
	pMenuItem1 = pMenu1->addMenuItem("Entry");
	pMenu2 = pMenuItem1->addMenu();
	
	pMenuItem2 = pMenu2->addMenuItem("Entry Name Case");
	pMenu3 = pMenuItem2->addMenu();
	pMenu3->addMenuItem("lower case", NAME_CASE_LOWER);
	pMenu3->addMenuItem("UPPER CASE", NAME_CASE_UPPER);
	pMenu3->addMenuItem("Title Case", NAME_CASE_TITLE);

	pMenuItem2 = pMenu2->addMenuItem("Copy Entry Data");
	pMenu3 = pMenuItem2->addMenu();
	pMenu3->addMenuItem("Copy Entries Index", COPY_ENTRY_INDEX);
	pMenu3->addMenuItem("Copy Entries Type", COPY_ENTRY_TYPE);
	pMenu3->addMenuItem("Copy Entries Name", COPY_ENTRY_NAME);
	pMenu3->addMenuItem("Copy Entries Offset", COPY_ENTRY_OFFSET);
	pMenu3->addMenuItem("Copy Entries Size", COPY_ENTRY_SIZE);
	pMenu3->addMenuItem("Copy Entries Version", COPY_ENTRY_VERSION);
	pMenu3->addMenuItem("Copy Entries Row Data", COPY_ENTRY_ROW_DATA);

	pMenuItem2 = pMenu2->addMenuItem("Shift Entry");
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

	// missing entries
	pMenu1->addMenuItem("Missing Entries");

	// orphan entries
	pMenuItem1 = pMenu1->addMenuItem("Orphan Entries");
	pMenu2 = pMenuItem1->addMenu();
	pMenu2->addMenuItem("Remove Orphan Textures from DFF Entries", REMOVE_ORPHAN_TEXTURES_FROM_DFF_ENTRIES);
	pMenu2->addMenuItem("Find Orphan IMG Entries not in IDE", FIND_ORPHAN_IMG_ENTRIES_NOT_IN_IDE);

	// tools
	pMenu1->addMenuItem("Tools");

	// other
	pMenu1->addMenuItem("Other");







	// logo
	x = 139 + 14;
	y = uiTitleBarHeight;
	w = 0;
	h = 0;

	addImage(x, y, "Internal/Images/Logo.png", w, h);
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

	// tab bar
	size = m_pTabBar->getSize();
	iNewWidth = pWindow->getSize().x - m_pTabBar->getPosition().x - uiLogWidth;
	m_pTabBar->setSize(Vec2u(iNewWidth, size.y));

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