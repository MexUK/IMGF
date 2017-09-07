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

	pMenu1 = addMenu(x, y, h, w, HORIZONTAL, strStyleGroup, -1, -100);
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

	addText(x, y, w, h, "Game", strStyleGroup);
	y += h2;
	addText(x, y, w, h, "Game Validity", strStyleGroup);
	y += h2;
	addText(x, y, w, h, "Game Location", strStyleGroup);
	y += h2;
	addText(x, y, w, h, "File Game", strStyleGroup);
	y += h2;
	addText(x, y, w, h, "File Validity", strStyleGroup);
	y += h2;
	addText(x, y, w, h, "File Location", strStyleGroup);

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
	m_pText_Game = addText(x, y, w2, h, "No file is open", strStyleGroup);
	y += h2;
	m_pText_GameValidity = addText(x, y, w2, h, "-", strStyleGroup);
	y += h2;
	m_pText_GameLocation = addText(x, y, w, h, "-", strStyleGroup);
	y += h2;
	m_pText_FilEGame = addText(x, y, w2, h, "-", strStyleGroup);
	y += h2;
	m_pText_FileValidity = addText(x, y, w2, h, "-", strStyleGroup);
	y += h2;
	m_pText_FileLocation = addText(x, y, w, h, "-", strStyleGroup);

	// top menu - buttons
	x = 139 + 139;
	y = uiTitleBarHeight;
	w = 139;
	h = uiButtonHeight;
	w2 = w;
	strStyleGroup = "topMenu";

	pMenu1 = addMenu(x, y, h, w, HORIZONTAL, strStyleGroup, -1, -100);
	pMenu1->addMenuItem("New", NEW);
	pMenu1->addMenuItem("Open", OPEN);
	pMenu1->addMenuItem("Close", CLOSE);
	pMenu1->addMenuItem("Save", SAVE);

	// search box
	w2 = 0;
	x += pMenu1->getEntryCount() * w;
	w = (m_pWindow->getSize().x - x) - (uiButtonHeight + 1);
	h = uiButtonHeight;
	strStyleGroup = "filter";

	m_pSearchBox = addTextBox(x, y, w, h, "Search", false, strStyleGroup);

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




	pMenu1 = addMenu(x, y, w, h, VERTICAL, strStyleGroup, -1, -100);

	// import
	pMenuItem1 = pMenu1->addMenuItem("Import");

	pMenu2 = pMenuItem1->addMenu();
	pMenu2->addMenuItem("Import by File(s)");
	pMenu2->addMenuItem("Import by Folder");

	// export
	pMenuItem1 = pMenu1->addMenuItem("Export");

	pMenu2 = pMenuItem1->addMenu();
	pMenu2->addMenuItem("Export Selection");
	pMenu2->addMenuItem("Export All");
	pMenuItem2 = pMenu2->addMenuItem("Export by..");

	pMenu3 = pMenuItem2->addMenu();
	pMenu3->addMenuItem("Export by Index");
	pMenu3->addMenuItem("Export by Name (Wildcard match)");
	pMenu3->addMenuItem("Export by Offset");
	pMenu3->addMenuItem("Export by Size");
	pMenuItem3 = pMenu3->addMenuItem("Export by Type..");

	pMenu4 = pMenuItem3->addMenu();
	pMenu4->addMenuItem("Export by Type into Single Folder");
	pMenu4->addMenuItem("Export by Type into Grouped Folder(s)");

	pMenu3->addMenuItem("Export by Version");

	// quick export
	pMenu1->addMenuItem("Quick Export");

	// rename
	pMenuItem1 = pMenu1->addMenuItem("Rename");
	pMenuItem1->setStyleGroups(string("thirdItemVertically"));

	// replace
	pMenu1->addMenuItem("Replace");

	// remove
	pMenuItem1 = pMenu1->addMenuItem("Remove");

	pMenu2 = pMenuItem1->addMenu();
	pMenu2->addMenuItem("Remove Selection");
	pMenu2->addMenuItem("Remove All");
	pMenuItem2 = pMenu2->addMenuItem("Remove by..");

	pMenu3 = pMenuItem2->addMenu();
	pMenu3->addMenuItem("Remove by Index");
	pMenu3->addMenuItem("Remove by Name (Wildcard match)");
	pMenu3->addMenuItem("Remove by Offset");
	pMenu3->addMenuItem("Remove by Size");
	pMenu3->addMenuItem("Remove by Type");
	pMenu3->addMenuItem("Remove by Version");
	
	// merge
	pMenuItem1 = pMenu1->addMenuItem("Merge");
	pMenuItem1->setStyleGroups(string("thirdItemVertically"));

	// split
	pMenu1->addMenuItem("Split");

	// convert
	pMenu1->addMenuItem("Convert");

	// select
	pMenuItem1 = pMenu1->addMenuItem("Select");
	pMenuItem1->setStyleGroups(string("thirdItemVertically"));

	pMenu2 = pMenuItem1->addMenu();
	pMenu2->addMenuItem("Select All", SELECT_ALL);
	pMenu2->addMenuItem("Unselect All", UNSELECT_ALL);
	pMenu2->addMenuItem("Select Inverse", SELECT_INVERSE);
	pMenuItem2 = pMenu2->addMenuItem("Select by..");

	pMenu3 = pMenuItem2->addMenu();
	pMenu3->addMenuItem("Select by Index");
	pMenu3->addMenuItem("Select by Name (Wildcard match)");
	pMenu3->addMenuItem("Select by Offset");
	pMenu3->addMenuItem("Select by Size");
	pMenu3->addMenuItem("Select by Type");
	pMenu3->addMenuItem("Select by Version");

	pMenuItem2 = pMenu2->addMenuItem("Unselect by..");

	pMenu3 = pMenuItem2->addMenu();
	pMenu3->addMenuItem("Unselect by Index");
	pMenu3->addMenuItem("Unselect by Name (Wildcard match)");
	pMenu3->addMenuItem("Unselect by Offset");
	pMenu3->addMenuItem("Unselect by Size");
	pMenu3->addMenuItem("Unselect by Type");
	pMenu3->addMenuItem("Unselect by Version");
	
	// sort
	pMenuItem1 = pMenu1->addMenuItem("Sort");

	pMenu2 = pMenuItem1->addMenu();
	pMenuItem2 = pMenu2->addMenuItem("Sort by Index..");

	pMenu3 = pMenuItem2->addMenu();
	pMenu3->addMenuItem("Sort by Index (Reverse)");

	pMenuItem2 = pMenu2->addMenuItem("Sort by Name..");

	pMenu3 = pMenuItem2->addMenu();
	pMenu3->addMenuItem("Sort by Name Ascending (0-9, A-Z)");
	pMenu3->addMenuItem("Sort by Name Ascending (A-Z, 0-9)");
	pMenu3->addMenuItem("Sort by Name Descending (Z-A, 9-0)");
	pMenu3->addMenuItem("Sort by Name Descending (9-0, Z-A)");

	pMenuItem2 = pMenu2->addMenuItem("Sort by Offset..");

	pMenu3 = pMenuItem2->addMenu();
	pMenu3->addMenuItem("Sort by Offset (Low-High)");
	pMenu3->addMenuItem("Sort by Offset (High-Low)");

	pMenuItem2 = pMenu2->addMenuItem("Sort by Size..");

	pMenu3 = pMenuItem2->addMenu();
	pMenu3->addMenuItem("Sort by Size (Small-Big)");
	pMenu3->addMenuItem("Sort by Size (Big-Small)");

	pMenuItem2 = pMenu2->addMenuItem("Sort by Type..");

	pMenu3 = pMenuItem2->addMenu();
	pMenu3->addMenuItem("Sort by Type (A-Z)");
	pMenu3->addMenuItem("Sort by Type (Z-A)");

	pMenuItem2 = pMenu2->addMenuItem("Sort by Version..");

	pMenu3 = pMenuItem2->addMenu();
	pMenu3->addMenuItem("Sort by Version (Old-New)");
	pMenu3->addMenuItem("Sort by Version (New-Old)");

	// LST
	pMenu1->addMenuItem("LST");




	// progress bar
	w = 150;
	w2 = 10;
	h2 = uiButtonHeight + 10;
	x = (m_pWindow->getSize().x - w2) - w;
	y = uiTitleBarHeight + h2;
	h = 5;
	strStyleGroup = "progressBar";

	m_pProgressBar = addProgressBar(x, y, w, h, strStyleGroup);

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

	// progress bar
	point = m_pProgressBar->getPosition();
	iNewX = (pWindow->getSize().x - m_pProgressBar->getSize().x) - 10;
	m_pProgressBar->setPosition(Vec2i(iNewX, point.y));

	// search box
	size = m_pSearchBox->getSize();
	iNewWidth = (pWindow->getSize().x - m_pSearchBox->getPosition().x) - (uiButtonHeight + 1);
	m_pSearchBox->setSize(Vec2u(iNewWidth, size.y));

	// tab bar
	size = m_pTabBar->getSize();
	iNewWidth = pWindow->getSize().x - m_pTabBar->getPosition().x;
	m_pTabBar->setSize(Vec2u(iNewWidth, size.y));

	// settings icon
	point = m_pSettingsButton->getPosition();
	iNewX = pWindow->getSize().x - (uiButtonHeight + 1);
	m_pSettingsButton->setPosition(Vec2i(iNewX, point.y));

	x = m_pSearchBox->getPosition().x + m_pSearchBox->getSize().x;
	y = m_pSearchBox->getPosition().y;
	m_pSettingsButtonLine1->setPoint1(Vec2i(x + 10, y + 10));
	m_pSettingsButtonLine1->setPoint2(Vec2i(x + 27, y + 10));
	m_pSettingsButtonLine2->setPoint1(Vec2i(x + 10, y + 19));
	m_pSettingsButtonLine2->setPoint2(Vec2i(x + 27, y + 19));
	m_pSettingsButtonLine3->setPoint1(Vec2i(x + 10, y + 28));
	m_pSettingsButtonLine3->setPoint2(Vec2i(x + 27, y + 28));
}