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
		uiTitleBarHeight = getWindow()->getTitleBarHeight(),
		uiButtonHeight = 37;
	Menu
		*pMenu1, *pMenu2, *pMenu3, *pMenu4;
	MenuItem
		*pMenuItem1, *pMenuItem2, *pMenuItem3;
	string
		strStyleGroup;

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
	y = (uiTitleBarHeight - 1) + uiButtonHeight + 6;
	y2 = y;
	w = 150;
	h = 20;
	h2 = 15;
	strStyleGroup = "gameInfoText";

	addText(x, y, w, h, "Game", strStyleGroup, -1, -150);
	y += h2;
	addText(x, y, w, h, "Game Validity", strStyleGroup, -1, -150);
	y += h2;
	addText(x, y, w, h, "Game Location", strStyleGroup, -1, -150);
	y += h2;
	addText(x, y, w, h, "File Game", strStyleGroup, -1, -150);
	y += h2;
	addText(x, y, w, h, "File Validity", strStyleGroup, -1, -150);
	y += h2;
	addText(x, y, w, h, "File Location", strStyleGroup, -1, -150);

	// game information values
	x += 149;
	y = y2;
	w = 657;
	w2 = 350;

	/*
	addText(x, y, w, h, "GTA Vice City (PC, 1.0)", strStyleGroup);
	y += h2;
	addText(x, y, w, h, "Launchable", strStyleGroup);
	y += h2;
	addText(x, y, w, h, "C:/Program Files (x86)/Rockstar Games/Grand Theft Auto Vice City", strStyleGroup);
	y += h2;
	addText(x, y, w, h, "GTA Vice City (PC, RW 11.22.33.44)", strStyleGroup);
	y += h2;
	addText(x, y, w, h, "Valid", strStyleGroup);
	y += h2;
	addText(x, y, w, h, "C:/Program Files (x86)/Rockstar Games/Grand Theft Auto Vice City/DATA/maps/a.txd", strStyleGroup);
	*/
	m_pText_Game = addText(x, y, w2, h, "No file is open", strStyleGroup, -1, -150);
	y += h2;
	m_pText_GameValidity = addText(x, y, w2, h, "-", strStyleGroup, -1, -150);
	y += h2;
	m_pText_GameLocation = addText(x, y, w, h, "-", strStyleGroup, -1, -150);
	y += h2;
	m_pText_FilEGame = addText(x, y, w2, h, "-", strStyleGroup, -1, -150);
	y += h2;
	m_pText_FileValidity = addText(x, y, w2, h, "-", strStyleGroup, -1, -150);
	y += h2;
	m_pText_FileLocation = addText(x, y, w, h, "-", strStyleGroup, -1, -150);

	// top menu - buttons
	x = 139 + 139;
	y = uiTitleBarHeight;
	w = 139;
	h = uiButtonHeight;
	w2 = w;
	strStyleGroup = "topMenu";

	pMenu1 = addMenu(x, y, h, w, HORIZONTAL, strStyleGroup, -1, -200);
	pMenu1->addMenuItem("New", NEW);

	pMenuItem1 = pMenu1->addMenuItem("Open", OPEN_FILES);
	pMenu2 = pMenuItem1->addMenu(VERTICAL);
	pMenu2->addMenuItem("Open File(s)", OPEN_FILES);
	pMenu2->addMenuItem("Open Folder", OPEN_FOLDER);

	pMenuItem1 = pMenu1->addMenuItem("Save", SAVE_FILE);
	pMenu2 = pMenuItem1->addMenu(VERTICAL);
	pMenu2->addMenuItem("Save File", SAVE_FILE);
	pMenu2->addMenuItem("Save As", SAVE_FILE_AS);
	pMenu2->addMenuItem("Save All", SAVE_ALL_FILES);

	pMenuItem1 = pMenu1->addMenuItem("Close", CLOSE_FILE);
	pMenu2 = pMenuItem1->addMenu(VERTICAL);
	pMenu2->addMenuItem("Close File", CLOSE_FILE);
	pMenu2->addMenuItem("Close All", CLOSE_ALL_FILES);

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
	w = m_pWindow->getSize().x - x;
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

	pMenu2->addMenuItem("Export by IDE", EXPORT_BY_IDE);

	// quick export
	pMenu1->addMenuItem("Quick Export");

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

	// merge
	pMenuItem1 = pMenu1->addMenuItem("Merge", MERGE);
	pMenuItem1->setStyleGroups(string("thirdItemVertically"));

	// split
	pMenu1->addMenuItem("Split", SPLIT);

	// convert
	pMenuItem1 = pMenu1->addMenuItem("Convert");

	pMenu2 = pMenuItem1->addMenu();
	pMenuItem2 = pMenu2->addMenuItem("IMG");

	pMenu3 = pMenuItem2->addMenu();
	pMenuItem3 = pMenu3->addMenuItem("Convert IMG Version", CONVERT_IMG_VERSION);

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
	pMenu1->addMenuItem("LST");




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
	uint32 uiButtonHeight = 37;

	// tab bar
	size = m_pTabBar->getSize();
	iNewWidth = pWindow->getSize().x - m_pTabBar->getPosition().x;
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