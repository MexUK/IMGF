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
	uint32
		uiTitleBarHeight = getWindow()->getTitleBarHeight();
	CColour
		borderColour(135, 135, 135),
		borderColour2(0, 0, 0);
	string
		strStyleGroup;

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
	strStyleGroup = "topLeftMenuButton";

	pButton = addButton(x, y, w, h, "Formats", strStyleGroup);
	x += w - 1;
	pButton = addButton(x, y, w, h, "Utility", strStyleGroup);

	// formats menu
	x = 0;
	y += h;
	w = 139;
	h = 40;
	h2 = h;
	strStyleGroup = "leftMenuButton";

	pButton = addButton(x, y, w, h, "DAT", strStyleGroup);
	y += h2;
	pButton = addButton(x, y, w, h, "IMG", strStyleGroup);
	y += h2;
	pButton = addButton(x, y, w, h, "Item Definition", strStyleGroup);
	y += h2;
	pButton = addButton(x, y, w, h, "Item Placement", strStyleGroup);
	y += h2;
	pButton = addButton(x, y, w, h, "Models", strStyleGroup);
	y += h2;
	pButton = addButton(x, y, w, h, "Collisions", strStyleGroup);
	y += h2;
	pButton = addButton(x, y, w, h, "Textures", strStyleGroup);
	y += h2;
	pButton = addButton(x, y, w, h, "Animations", strStyleGroup);
	y += h2;
	pButton = addButton(x, y, w, h, "Radar", strStyleGroup);

	// game information headers
	x = 149;
	y = (uiTitleBarHeight - 1) + 10;
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
	y = (uiTitleBarHeight - 1) + 10;
	w = 350;
	h = 20;

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

	// top menu - buttons
	x = 139;
	y = 133;
	w = 100;
	h = 30;
	w2 = w;
	strStyleGroup = "topMenuButton";

	addButton(x, y, w, h, "Open", strStyleGroup);
	x += w2;
	addButton(x, y, w, h, "Close", strStyleGroup);
	x += w2;
	addButton(x, y, w, h, "Save", strStyleGroup);
	x += w2;

	// filter bar - search box
	w2 = 0;
	x += w2;
	w = 273;
	h = 30;
	strStyleGroup = "filter";

	m_pSearchBox = addEdit(CPoint2D(x, y), CSize2D(w, h), "Search", false, strStyleGroup);

	// filter bar - entry type
	x += w + w2;
	w = 140;
	h = 30;

	m_pEntryTypeFilter = addDrop(CPoint2D(x, y), CSize2D(w, h), strStyleGroup);
	m_pEntryTypeFilter->addItem("Entry Type", true);

	// filter bar - entry version
	x += w + w2;
	w = 240;
	h = 30;

	m_pEntryVersionFilter = addDrop(CPoint2D(x, y), CSize2D(w, h), strStyleGroup);
	m_pEntryVersionFilter->addItem("Entry Version", true);

	// files tab bar
	x = 139;
	y = 162;
	w = 500;
	h = 30;
	strStyleGroup = "fileTabBar";

	CTabControl *pIMGInstanceTabBar = addTabBar(CPoint2D(x, y), CSize2D(w, h), strStyleGroup);

	CTabControlEntry * pTab;
	pTab = pIMGInstanceTabBar->addTab("gta3.img (#1000)", true);
	pTab = pIMGInstanceTabBar->addTab("gta3 - backup.img (#1200)");
	pTab = pIMGInstanceTabBar->addTab("gta3.img (#1000)");

	// 2nd left menu - actions
	x = 139;
	y += h;
	w = 110;
	h = 30;
	h2 = h;
	h3 = h2 + 0;
	strStyleGroup = "secondLeftMenu";

	addButton(x, y, w, h, "Import", strStyleGroup);
	y += h2;
	addButton(x, y, w, h, "Export", strStyleGroup);
	y += h2;
	addButton(x, y, w, h, "Quick Export", strStyleGroup);
	y += h3;

	addButton(x, y, w, h, "Rename", strStyleGroup);
	y += h2;
	addButton(x, y, w, h, "Replace", strStyleGroup);
	y += h2;
	addButton(x, y, w, h, "Remove", strStyleGroup);
	y += h3;

	addButton(x, y, w, h, "Merge", strStyleGroup);
	y += h2;
	addButton(x, y, w, h, "Split", strStyleGroup);
	y += h2;
	addButton(x, y, w, h, "Convert", strStyleGroup);
	y += h3;

	addButton(x, y, w, h, "Select", strStyleGroup);
	y += h2;
	addButton(x, y, w, h, "Sort", strStyleGroup);
	y += h2;
	addButton(x, y, w, h, "LST", strStyleGroup);
	y += h3;

	// progress bar
	w = 150;
	w2 = 10;
	h2 = 10;
	x = (m_pWindow->getSize().m_x - w2) - w;
	y = uiTitleBarHeight + h2;
	h = 12;
	strStyleGroup = "progressBar";

	m_pProgressBar = addProgress(x, y, w, h, strStyleGroup);
}

void		CMainLayer::initControls(void)
{
	CEventManager::getInstance()->bindEvent(EVENT_onResizeWindow, [](void* pArg1, void* pArg2) {
		((CMainLayer*)pArg1)->repositionAndResizeControls();
	}, this);
	repositionAndResizeControls();
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