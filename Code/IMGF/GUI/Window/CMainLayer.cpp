#include "CMainLayer.h"
#include "Window/CWindow.h"
#include "CGUIManager.h"
#include "Type/Vector/CColour.h"
#include "Controls/CTabControl.h"
#include "Controls/CDropControl.h"
#include "Controls/CButtonControl.h"
#include "Controls/CProgressControl.h"
#include "Controls/CEditControl.h"
#include "GUI/Window/CIMGFWindow.h"
#include "GUI/Editors/CIMGEditor.h"

using namespace std;
using namespace bxcf;
using namespace bxgx;

// main interface
void		CMainLayer::init(void)
{
	addControls();
	initControls();
}

// controls
void		CMainLayer::addControls(void)
{
	int32 i, i2, x, y, w, h, w2, w3, h2, h3;
	uint32 uiTitleBarHeight = getWindow()->getTitleBarHeight();
	CColour
		borderColour(135, 135, 135),
		borderColour2(0, 0, 0);

	// all buttons
	CButtonControl *pButton, *pOpenButton;
	CGUIStyles *pButtonStyles = bxgx::CGUIManager::createStyles();
	pButtonStyles->setStyle("fill-colour", CColour(255, 255, 255));
	pButtonStyles->setStyle("border-colour", borderColour);
	pButtonStyles->setStyle("text-align-x", string("left"));
	pButtonStyles->setStyle("text-align-y", string("center"));
	pButtonStyles->setStyle("inner-spacing-left", (int32)8);

	// top left menu
	x = 0;
	y = uiTitleBarHeight;
	w = 70;
	h = 30;

	CGUIStyles *pButtonStyles_TopLeftMenu = bxgx::CGUIManager::createStyles();
	pButtonStyles_TopLeftMenu->setStyle("fill-colour", CColour(219, 239, 255));
	pButtonStyles_TopLeftMenu->setStyle("border-colour", borderColour);
	pButtonStyles_TopLeftMenu->setStyle("border-state-left", true);
	pButtonStyles_TopLeftMenu->setStyle("text-align-x", string("left"));
	pButtonStyles_TopLeftMenu->setStyle("text-align-y", string("center"));
	pButtonStyles_TopLeftMenu->setStyle("inner-spacing-left", (int32)8);

	CGUIStyles *pButtonStyles_TopLeftMenu_FirstItem = bxgx::CGUIManager::createStyles();
	pButtonStyles_TopLeftMenu_FirstItem->setStyle("fill-colour", CColour(219, 239, 255));
	pButtonStyles_TopLeftMenu_FirstItem->setStyle("text-align-x", string("left"));
	pButtonStyles_TopLeftMenu_FirstItem->setStyle("text-align-y", string("center"));
	pButtonStyles_TopLeftMenu_FirstItem->setStyle("inner-spacing-left", (int32)8);

	pButton = addButton(x, y, w, h, "Formats", pButtonStyles_TopLeftMenu_FirstItem);
	x += w - 1;
	pButton = addButton(x, y, w, h, "Utility", pButtonStyles_TopLeftMenu);

	// formats menu
	x = 0;
	y += h;
	w = 139;
	h = 40;
	h2 = h;

	CGUIStyles *pButtonStyles_FormatsMenu = bxgx::CGUIManager::createStyles();
	CColour leftMenuColour(122, 195, 255);
	pButtonStyles_FormatsMenu->setStyle("fill-colour", leftMenuColour); // 149, 207, 255
	pButtonStyles_FormatsMenu->setStyle("border-colour", borderColour);
	pButtonStyles_FormatsMenu->setStyle("border-state-top", true);
	pButtonStyles_FormatsMenu->setStyle("text-align-x", string("left"));
	pButtonStyles_FormatsMenu->setStyle("text-align-y", string("center"));
	pButtonStyles_FormatsMenu->setStyle("inner-spacing-left", (int32)8);

	CGUIStyles *pButtonStyles_FormatsMenu_FirstItem = bxgx::CGUIManager::createStyles();
	pButtonStyles_FormatsMenu_FirstItem->setStyle("fill-colour", leftMenuColour);
	pButtonStyles_FormatsMenu_FirstItem->setStyle("text-align-x", string("left"));
	pButtonStyles_FormatsMenu_FirstItem->setStyle("text-align-y", string("center"));
	pButtonStyles_FormatsMenu_FirstItem->setStyle("inner-spacing-left", (int32)8);

	pButton = addButton(x, y, w, h, "DAT", pButtonStyles_FormatsMenu_FirstItem);
	y += h2;
	pButton = addButton(x, y, w, h, "IMG", pButtonStyles_FormatsMenu);
	y += h2;
	pButton = addButton(x, y, w, h, "Item Definition", pButtonStyles_FormatsMenu);
	y += h2;
	pButton = addButton(x, y, w, h, "Item Placement", pButtonStyles_FormatsMenu);
	y += h2;
	pButton = addButton(x, y, w, h, "Models", pButtonStyles_FormatsMenu);
	y += h2;
	pButton = addButton(x, y, w, h, "Collisions", pButtonStyles_FormatsMenu);
	y += h2;
	pButton = addButton(x, y, w, h, "Textures", pButtonStyles_FormatsMenu);
	y += h2;
	pButton = addButton(x, y, w, h, "Animations", pButtonStyles_FormatsMenu);
	y += h2;
	pButton = addButton(x, y, w, h, "Radar", pButtonStyles_FormatsMenu);

	// game information headers
	x = 149;
	y = (uiTitleBarHeight - 1) + 10;
	w = 150;
	h = 20;
	h2 = 15;

	CGUIStyles *pTextStyles_GameInfo = bxgx::CGUIManager::createStyles();
	pTextStyles_GameInfo->setStyle("text-colour", CColour(255, 255, 255));

	addText(x, y, w, h, "Game", pTextStyles_GameInfo);
	y += h2;
	addText(x, y, w, h, "Game Validity", pTextStyles_GameInfo);
	y += h2;
	addText(x, y, w, h, "Game Location", pTextStyles_GameInfo);
	y += h2;
	addText(x, y, w, h, "File Game", pTextStyles_GameInfo);
	y += h2;
	addText(x, y, w, h, "File Validity", pTextStyles_GameInfo);
	y += h2;
	addText(x, y, w, h, "File Location", pTextStyles_GameInfo);

	// game information values
	x += 149;
	y = (uiTitleBarHeight - 1) + 10;
	w = 350;
	h = 20;

	addText(x, y, w, h, "GTA Vice City (PC, 1.0)", pTextStyles_GameInfo);
	y += h2;
	addText(x, y, w, h, "Launchable", pTextStyles_GameInfo);
	y += h2;
	addText(x, y, w, h, "C:/Program Files (x86)/Rockstar Games/Grand Theft Auto Vice City", pTextStyles_GameInfo);
	y += h2;
	addText(x, y, w, h, "GTA Vice City (PC, RW 11.22.33.44)", pTextStyles_GameInfo);
	y += h2;
	addText(x, y, w, h, "Valid", pTextStyles_GameInfo);
	y += h2;
	addText(x, y, w, h, "C:/Program Files (x86)/Rockstar Games/Grand Theft Auto Vice City/DATA/maps/a.txd", pTextStyles_GameInfo);

	// top menu - buttons
	x = 139;
	y = 133;
	w = 100;
	h = 30;
	w2 = w;

	CGUIStyles *pButtonStyles_TopMenu = bxgx::CGUIManager::createStyles();
	CColour topMenuFillColour(255, 209, 209);
	pButtonStyles_TopMenu->setStyle("fill-colour", topMenuFillColour);
	pButtonStyles_TopMenu->setStyle("border-colour", borderColour);
	pButtonStyles_TopMenu->setStyle("border-state-left", true);
	pButtonStyles_TopMenu->setStyle("text-align-x", string("left"));
	pButtonStyles_TopMenu->setStyle("text-align-y", string("center"));
	pButtonStyles_TopMenu->setStyle("inner-spacing-left", (int32)8);

	CGUIStyles *pButtonStyles_TopMenu_FirstItem = bxgx::CGUIManager::createStyles();
	pButtonStyles_TopMenu_FirstItem->setStyle("fill-colour", topMenuFillColour);
	pButtonStyles_TopMenu_FirstItem->setStyle("text-align-x", string("left"));
	pButtonStyles_TopMenu_FirstItem->setStyle("text-align-y", string("center"));
	pButtonStyles_TopMenu_FirstItem->setStyle("inner-spacing-left", (int32)8);

	addButton(x, y, w, h, "Open", pButtonStyles_TopMenu_FirstItem);
	x += w2;
	addButton(x, y, w, h, "Close", pButtonStyles_TopMenu);
	x += w2;
	addButton(x, y, w, h, "Save", pButtonStyles_TopMenu);
	x += w2;

	// filter bar - search box
	w2 = 0;
	x += w2;
	w = 273;
	h = 30;

	CGUIStyles *pSearchBoxStyles = bxgx::CGUIManager::createStyles();
	CColour filtersFillColour(255, 149, 149);
	pSearchBoxStyles->setStyle("fill-colour", filtersFillColour);
	pSearchBoxStyles->setStyle("border-colour", borderColour);
	pSearchBoxStyles->setStyle("text-colour", CColour(0, 0, 0));
	pSearchBoxStyles->setStyle("text-align-x", string("left"));
	pSearchBoxStyles->setStyle("text-align-y", string("center"));
	pSearchBoxStyles->setStyle("inner-spacing-x", (int32)8);

	m_pSearchBox = addEdit(CPoint2D(x, y), CSize2D(w, h), "Search", false, pSearchBoxStyles);

	// filter bar - entry type
	x += w + w2;
	w = 140;
	h = 30;

	CGUIStyles *pEntryTypeFilterStyles = bxgx::CGUIManager::createStyles();
	pEntryTypeFilterStyles->setStyle("fill-colour", filtersFillColour);
	pEntryTypeFilterStyles->setStyle("border-colour", borderColour);
	pEntryTypeFilterStyles->setStyle("border-state-left", true);
	pEntryTypeFilterStyles->setStyle("text-colour", CColour(0, 0, 0));
	pEntryTypeFilterStyles->setStyle("text-align-x", string("left"));
	pEntryTypeFilterStyles->setStyle("text-align-y", string("center"));
	pEntryTypeFilterStyles->setStyle("inner-spacing-x", (int32)8);
	
	m_pEntryTypeFilter = addDrop(CPoint2D(x, y), CSize2D(w, h), pEntryTypeFilterStyles);
	m_pEntryTypeFilter->addItem("Entry Type", true);

	// filter bar - entry version
	x += w + w2;
	w = 240;
	h = 30;

	CGUIStyles *pEntryVersionFilterStyles = bxgx::CGUIManager::createStyles();
	pEntryVersionFilterStyles->setStyle("fill-colour", filtersFillColour);
	pEntryVersionFilterStyles->setStyle("border-colour", borderColour);
	pEntryVersionFilterStyles->setStyle("border-state-left", true);
	pEntryVersionFilterStyles->setStyle("text-colour", CColour(0, 0, 0));
	pEntryVersionFilterStyles->setStyle("text-align-x", string("left"));
	pEntryVersionFilterStyles->setStyle("text-align-y", string("center"));
	pEntryVersionFilterStyles->setStyle("inner-spacing-x", (int32)8);

	m_pEntryVersionFilter = addDrop(CPoint2D(x, y), CSize2D(w, h), pEntryVersionFilterStyles);
	m_pEntryVersionFilter->addItem("Entry Version", true);

	// files tab bar
	x = 139;
	y = 162;
	w = 500;
	h = 30;

	CGUIStyles *pIMGInstanceTabBarStyles = bxgx::CGUIManager::createStyles();
	pIMGInstanceTabBarStyles->setStyle("fill-colour", CColour(220, 220, 220));
	pIMGInstanceTabBarStyles->setStyle("border-colour", borderColour);
	pIMGInstanceTabBarStyles->setStyle("border-state-left", true);
	pIMGInstanceTabBarStyles->setStyle("text-align-x", string("left"));
	pIMGInstanceTabBarStyles->setStyle("text-align-y", string("center"));
	pIMGInstanceTabBarStyles->setStyle("inner-spacing-x", (int32)8);

	CTabControl *pIMGInstanceTabBar = addTabBar(CPoint2D(x, y), CSize2D(w, h), pIMGInstanceTabBarStyles);
	
	CGUIStyles *pIMGInstanceTabBarStyles_FirstTab = bxgx::CGUIManager::createStyles();
	pIMGInstanceTabBarStyles_FirstTab->setStyle("border-state-left", false);

	CGUIStyles *pIMGInstanceTabBarStyles_NotFirstTab = bxgx::CGUIManager::createStyles();
	pIMGInstanceTabBarStyles_NotFirstTab->setStyle("border-state-left", true);

	CTabControlEntry * pTab;

	pTab = pIMGInstanceTabBar->addTab("gta3.img (#1000)", true);
	pTab->setStyles(pIMGInstanceTabBarStyles_FirstTab);

	pTab = pIMGInstanceTabBar->addTab("gta3 - backup.img (#1200)");
	pTab->setStyles(pIMGInstanceTabBarStyles_NotFirstTab);

	pTab = pIMGInstanceTabBar->addTab("gta3.img (#1000)");
	pTab->setStyles(pIMGInstanceTabBarStyles_NotFirstTab);

	// 2nd left menu - actions
	x = 139;
	y += h;
	w = 110;
	h = 30;
	h2 = h;
	h3 = h2 + 0;

	CColour secondLeftMenuFillColour(255, 209, 209);//(175, 255, 149);
	CGUIStyles *pButtonStyles_ActionMenu = bxgx::CGUIManager::createStyles();
	pButtonStyles_ActionMenu->setStyle("fill-colour", secondLeftMenuFillColour);
	pButtonStyles_ActionMenu->setStyle("border-colour", borderColour);
	pButtonStyles_ActionMenu->setStyle("border-state-top", true);
	pButtonStyles_ActionMenu->setStyle("text-align-x", string("left"));
	pButtonStyles_ActionMenu->setStyle("text-align-y", string("center"));
	pButtonStyles_ActionMenu->setStyle("inner-spacing-left", (int32)8);

	CGUIStyles *pButtonStyles_ActionMenu_FirstItem = bxgx::CGUIManager::createStyles();
	pButtonStyles_ActionMenu_FirstItem->setStyle("fill-colour", secondLeftMenuFillColour);
	pButtonStyles_ActionMenu_FirstItem->setStyle("border-colour", borderColour2);
	pButtonStyles_ActionMenu_FirstItem->setStyle("border-state-top", true);
	pButtonStyles_ActionMenu_FirstItem->setStyle("text-align-x", string("left"));
	pButtonStyles_ActionMenu_FirstItem->setStyle("text-align-y", string("center"));
	pButtonStyles_ActionMenu_FirstItem->setStyle("inner-spacing-left", (int32)8);

	CGUIStyles *pButtonStyles_ActionMenu_FirstItem2 = bxgx::CGUIManager::createStyles();
	pButtonStyles_ActionMenu_FirstItem2->setStyle("fill-colour", secondLeftMenuFillColour);
	pButtonStyles_ActionMenu_FirstItem2->setStyle("text-align-x", string("left"));
	pButtonStyles_ActionMenu_FirstItem2->setStyle("text-align-y", string("center"));
	pButtonStyles_ActionMenu_FirstItem2->setStyle("inner-spacing-left", (int32)8);

	addButton(x, y, w, h, "Import", pButtonStyles_ActionMenu_FirstItem2);
	y += h2;
	addButton(x, y, w, h, "Export", pButtonStyles_ActionMenu);
	y += h2;
	addButton(x, y, w, h, "Quick Export", pButtonStyles_ActionMenu);
	y += h3;

	addButton(x, y, w, h, "Rename", pButtonStyles_ActionMenu_FirstItem);
	y += h2;
	addButton(x, y, w, h, "Replace", pButtonStyles_ActionMenu);
	y += h2;
	addButton(x, y, w, h, "Remove", pButtonStyles_ActionMenu);
	y += h3;

	addButton(x, y, w, h, "Merge", pButtonStyles_ActionMenu_FirstItem);
	y += h2;
	addButton(x, y, w, h, "Split", pButtonStyles_ActionMenu);
	y += h2;
	addButton(x, y, w, h, "Convert", pButtonStyles_ActionMenu);
	y += h3;

	addButton(x, y, w, h, "Select", pButtonStyles_ActionMenu_FirstItem);
	y += h2;
	addButton(x, y, w, h, "Sort", pButtonStyles_ActionMenu);
	y += h2;
	addButton(x, y, w, h, "LST", pButtonStyles_ActionMenu);
	y += h3;

	// progress bar
	w = 150;
	w2 = 10;
	h2 = 10;
	x = (m_pWindow->getSize().m_x - w2) - w;
	y = uiTitleBarHeight + h2;
	h = 12;

	CGUIStyles *pProgressBarStyles = bxgx::CGUIManager::createStyles();
	pProgressBarStyles->setStyle("fill-colour", CColour(255, 255, 255));
	//pProgressBarStyles->setStyle("border-colour", borderColour);

	m_pProgressBar = addProgress(x, y, w, h, pProgressBarStyles);
}

void		CMainLayer::initControls(void)
{
	CEventManager::getInstance()->bindEvent(EVENT_onResizeWindow, [](void* pArg1, void* pArg2) {
		((CMainLayer*)pArg1)->repositionAndResizeControls();
	}, this);
	repositionAndResizeControls();

	bindEvents();
}

void		CMainLayer::repositionAndResizeControls(void)
{
	CWindow *pWindow = getWindow();

	CPoint2D point;
	CSize2D size;
	int32 iNewX, iNewY, iNewWidth, iNewHeight;

	// progress bar
	point = m_pProgressBar->getPosition();
	iNewX = (pWindow->getSize().m_x - m_pProgressBar->getSize().m_x) - 10;
	m_pProgressBar->setPosition(CPoint2D(iNewX, point.m_y));

	// filter bar - search box
	size = m_pSearchBox->getSize();
	iNewWidth = pWindow->getSize().m_x - 438 - 380 - 9;
	m_pSearchBox->setSize(CSize2D(iNewWidth, size.m_y));

	// filter bar - entry type
	point = m_pEntryTypeFilter->getPosition();
	iNewX = (m_pSearchBox->getPosition().m_x + iNewWidth) - 1;
	m_pEntryTypeFilter->setPosition(CPoint2D(iNewX, point.m_y));

	// filter bar - entry version
	point = m_pEntryVersionFilter->getPosition();
	iNewX = (m_pEntryTypeFilter->getPosition().m_x + m_pEntryTypeFilter->getSize().m_x) - 1;
	m_pEntryVersionFilter->setPosition(CPoint2D(iNewX, point.m_y));
}