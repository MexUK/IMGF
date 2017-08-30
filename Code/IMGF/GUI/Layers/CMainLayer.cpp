#include "CMainLayer.h"
#include "Window/CWindow.h"
#include "BXGX.h"
#include "Type/Colour/CColour.h"
#include "Controls/CTabBar.h"
#include "Controls/CDropDown.h"
#include "Controls/CButton.h"
#include "Controls/CProgressBar.h"
#include "Controls/CTextBox.h"
#include "Shapes/CLine.h"
#include "GUI/Windows/CMainWindow.h"
#include "GUI/Editors/CIMGEditor.h"
#include "GUI/Layer/ELayer.h"
#include "GUI/Input/Buttons/EButton.h"
#include "Controls/CMenu.h"
#include "Controls/Entries/CMenuItem.h"

using namespace std;
using namespace bxcf;
using namespace bxgx;
using namespace bxgx::control::events;
using namespace imgf;
using namespace imgf::layers;
using namespace imgf::mainLayer::buttons;

// main interface
void		CMainLayer::init(void)
{
	addControls();
	initControls();
}

// tab control
void		CMainLayer::onChangeTab(CTabBar *pTabBar)
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

void		CMainLayer::onRemoveTab(CTab *pTab)
{
	m_pMainWindow->getIMGEditor()->removeFile((CIMGEditorTab*)m_pMainWindow->getIMGEditor()->getTabs().getEntryByIndex(pTab->getIndex()));
}

// controls
void		CMainLayer::addControls(void)
{
	int32
		x, y, y2, w, h, w2, h2, h3;
	uint32
		uiTitleBarHeight = getWindow()->getTitleBarHeight(),
		uiButtonHeight = 37;
	CMenu
		*pMenu;
	CMenuItem
		*pMenuItem, *pMenuItem2, *pMenuItem3;
	string
		strStyleGroup;

	// top left menu
	x = 0;
	y = uiTitleBarHeight;
	w = 70;
	h = uiButtonHeight;
	strStyleGroup = "topLeftMenu";

	pMenu = addMenu(x, y, h, w, HORIZONTAL, strStyleGroup);
	pMenu->addItem("Formats", FORMATS);
	pMenu->addItem("Utility", UTILITY);

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

	pMenu = addMenu(x, y, h, w, HORIZONTAL, strStyleGroup);
	pMenu->addItem("New", NEW);
	pMenu->addItem("Open", OPEN);
	pMenu->addItem("Close", CLOSE);
	pMenu->addItem("Save", SAVE);

	// search box
	w2 = 0;
	x += pMenu->getEntryCount() * w;
	w = (m_pWindow->getSize().x - x) - (uiButtonHeight + 1);
	h = uiButtonHeight;
	strStyleGroup = "filter";

	m_pSearchBox = addTextBox(x, y, w, h, "Search", false, strStyleGroup);

	// settings icon
	x += w;
	w = uiButtonHeight + 1;
	h = uiButtonHeight;
	strStyleGroup = "settingsMenu";

	m_pSettingsButton = addButton(x, y, w, h, "", strStyleGroup, SETTINGS, 0);
	m_pSettingsButtonLine1 = addLine(x + 10, y + 10, x + 27, y + 10, "settingsMenuLine", -1, 10);
	m_pSettingsButtonLine2 = addLine(x + 10, y + 19, x + 27, y + 19, "settingsMenuLine", -1, 10);
	m_pSettingsButtonLine3 = addLine(x + 10, y + 28, x + 27, y + 28, "settingsMenuLine", -1, 10);

	//m_pSettingsButtonLine1->setContainerItem(m_pSettingsButton);
	//m_pSettingsButtonLine2->setContainerItem(m_pSettingsButton);
	//m_pSettingsButtonLine3->setContainerItem(m_pSettingsButton);

	// files tab bar
	x = 139 + 139;
	y = 162;
	w = m_pWindow->getSize().x - x;
	h = 30;
	strStyleGroup = "fileTabBar";

	m_pTabBar = addTabBar(x, y, w, h, strStyleGroup);
	m_pTabBar->setDefaultText("No tabs to display");

	/*
	CTab * pTab;
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

	pMenu = addMenu(x, y, w, h, VERTICAL, strStyleGroup);
	
	pMenuItem = pMenu->addItem("Import");
	pMenuItem->addItem("Import by File(s)");
	pMenuItem->addItem("Import by Folder");

	pMenuItem = pMenu->addItem("Export");
	pMenuItem->addItem("Export Selection");
	pMenuItem->addItem("Export All");
	pMenuItem2 = pMenuItem->addItem("Export by..");
	pMenuItem2->addItem("Export by Index");
	pMenuItem2->addItem("Export by Name (Wildcard match)");
	pMenuItem2->addItem("Export by Offset");
	pMenuItem2->addItem("Export by Size");
	pMenuItem3 = pMenuItem2->addItem("Export by Type..");
	pMenuItem3->addItem("Export by Type into Single Folder");
	pMenuItem3->addItem("Export by Type into Grouped Folder(s)");
	pMenuItem2->addItem("Export by Version");

	pMenu->addItem("Quick Export");
	pMenu->addItem("Rename");
	pMenu->addItem("Replace");

	pMenuItem = pMenu->addItem("Remove");
	pMenuItem->addItem("Remove Selection");
	pMenuItem->addItem("Remove All");
	pMenuItem2 = pMenuItem->addItem("Remove by..");
	pMenuItem2->addItem("Remove by Index");
	pMenuItem2->addItem("Remove by Name (Wildcard match)");
	pMenuItem2->addItem("Remove by Offset");
	pMenuItem2->addItem("Remove by Size");
	pMenuItem2->addItem("Remove by Type");
	pMenuItem2->addItem("Remove by Version");
	
	pMenu->addItem("Merge");
	pMenu->addItem("Split");
	pMenu->addItem("Convert");

	pMenuItem = pMenu->addItem("Select");
	pMenuItem->addItem("Select All");
	pMenuItem->addItem("Unselect All");
	pMenuItem2 = pMenuItem->addItem("Select by..");
	pMenuItem2->addItem("Select by Index");
	pMenuItem2->addItem("Select by Name (Wildcard match)");
	pMenuItem2->addItem("Select by Offset");
	pMenuItem2->addItem("Select by Size");
	pMenuItem2->addItem("Select by Type");
	pMenuItem2->addItem("Select by Version");
	pMenuItem2 = pMenuItem->addItem("Unselect by..");
	pMenuItem2->addItem("Unselect by Index");
	pMenuItem2->addItem("Unselect by Name (Wildcard match)");
	pMenuItem2->addItem("Unselect by Offset");
	pMenuItem2->addItem("Unselect by Size");
	pMenuItem2->addItem("Unselect by Type");
	pMenuItem2->addItem("Unselect by Version");
	
	pMenuItem = pMenu->addItem("Sort");
	pMenuItem2 = pMenuItem->addItem("Sort by Index..");
	pMenuItem2->addItem("Sort by Index (Reverse)");
	pMenuItem2 = pMenuItem->addItem("Sort by Name..");
	pMenuItem2->addItem("Sort by Name Ascending (0-9, A-Z)");
	pMenuItem2->addItem("Sort by Name Ascending (A-Z, 0-9)");
	pMenuItem2->addItem("Sort by Name Descending (Z-A, 9-0)");
	pMenuItem2->addItem("Sort by Name Descending (9-0, Z-A)");
	pMenuItem2 = pMenuItem->addItem("Sort by Offset..");
	pMenuItem2->addItem("Sort by Offset (Low-High)");
	pMenuItem2->addItem("Sort by Offset (High-Low)");
	pMenuItem2 = pMenuItem->addItem("Sort by Size..");
	pMenuItem2->addItem("Sort by Size (Small-Big)");
	pMenuItem2->addItem("Sort by Size (Big-Small)");
	pMenuItem2 = pMenuItem->addItem("Sort by Type..");
	pMenuItem2->addItem("Sort by Type (A-Z)");
	pMenuItem2->addItem("Sort by Type (Z-A)");
	pMenuItem2 = pMenuItem->addItem("Sort by Version..");
	pMenuItem2->addItem("Sort by Version (Old-New)");
	pMenuItem2->addItem("Sort by Version (New-Old)");

	pMenu->addItem("LST");

	// progress bar
	w = 150;
	w2 = 10;
	h2 = uiButtonHeight + 10;
	x = (m_pWindow->getSize().x - w2) - w;
	y = uiTitleBarHeight + h2;
	h = 5;
	strStyleGroup = "progressBar";

	m_pProgressBar = addProgress(x, y, w, h, strStyleGroup);

	// logo
	x = 139 + 14;
	y = uiTitleBarHeight;
	w = 0;
	h = 0;

	addImage(x, y, "Internal/Images/Logo.png", w, h);
}

void		CMainLayer::initControls(void)
{
	bindEventConst<void>(CHANGE_TAB, &CMainLayer::onChangeTab);
	bindEvent(REMOVE_TAB, &CMainLayer::onRemoveTab);

	bindEvent(RESIZE_WINDOW, &CMainLayer::repositionAndResizeControls);
	repositionAndResizeControls(Vec2i(0, 0));
}

void		CMainLayer::repositionAndResizeControls(Vec2i& vecSizeDifference)
{
	CWindow *pWindow = getWindow();

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