#include "CMainLayer.h"
#include "Window/CWindow.h"
#include "CGUIManager.h"
#include "Type/Colour/CColour.h"
#include "Controls/CTabBarControl.h"
#include "Controls/CDropControl.h"
#include "Controls/CButtonControl.h"
#include "Controls/CProgressControl.h"
#include "Controls/CTextBoxControl.h"
#include "GUI/Windows/CMainWindow.h"
#include "GUI/Editors/CIMGEditor.h"
#include "GUI/Layer/ELayers.h"
#include "GUI/Input/Buttons/EButtons.h"

using namespace std;
using namespace bxcf;
using namespace bxgx;
using namespace imgf::layers;
using namespace imgf::mainLayer::buttons;

// main interface
void		CMainLayer::init(void)
{
	addControls();
	initControls();
}

// controls
void		CMainLayer::addControls(void)
{
	int32
		i, i2, x, y, y2, w, h, w2, w3, h2, h3;
	uint32
		uiTitleBarHeight = getWindow()->getTitleBarHeight();
	CButtonControl
		*pButton;
	string
		strStyleGroup;

	// top left menu
	x = 0;
	y = uiTitleBarHeight;
	w = 70;
	h = 30;
	strStyleGroup = "topLeftMenuButton";

	pButton = addButton(x, y, w, h, "Formats", "firstItemHorizontally " + strStyleGroup, FORMATS);
	x += w - 1;
	pButton = addButton(x, y, w, h, "Utility", strStyleGroup, UTILITY);

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
	addText(x, y, w, h, "No file is open", strStyleGroup);
	y += h2;
	addText(x, y, w, h, "-", strStyleGroup);
	y += h2;
	addText(x, y, w, h, "-", strStyleGroup);
	y += h2;
	addText(x, y, w, h, "-", strStyleGroup);
	y += h2;
	addText(x, y, w, h, "-", strStyleGroup);
	y += h2;
	addText(x, y, w, h, "-", strStyleGroup);

	// top menu - buttons
	x = 139;
	y = 133;
	w = 100;
	h = 30;
	w2 = w;
	strStyleGroup = "topMenuButton";

	addButton(x, y, w, h, "Open", strStyleGroup + " firstItemHorizontally", OPEN);
	x += w2;
	addButton(x, y, w, h, "Close", strStyleGroup, CLOSE);
	x += w2;
	addButton(x, y, w, h, "Save", strStyleGroup, SAVE);
	x += w2;

	// filter bar - search box
	w2 = 0;
	x += w2;
	w = 273;
	h = 30;
	strStyleGroup = "filter";

	m_pSearchBox = addTextBox(Vec2i(x, y), Vec2u(w, h), "Search", false, strStyleGroup);

	// filter bar - entry type
	x += w + w2;
	w = 140;
	h = 30;

	m_pEntryTypeFilter = addDrop(Vec2i(x, y), Vec2u(w, h), "Entry Type", strStyleGroup);
	m_pEntryTypeFilter->addItem("No file is open", false, false);

	// filter bar - entry version
	x += w + w2;
	w = 240;
	h = 30;

	m_pEntryVersionFilter = addDrop(Vec2i(x, y), Vec2u(w, h), "Entry Version", strStyleGroup);
	m_pEntryVersionFilter->addItem("No file is open", false, false);

	// files tab bar
	x = 139;
	y = 162;
	w = 500;
	h = 30;
	strStyleGroup = "fileTabBar";

	m_pTabBar = addTabBar(Vec2i(x, y), Vec2u((getWindow()->getSize().x - 10) - 249, h), strStyleGroup);
	m_pTabBar->setDefaultText("No tabs to display");

	/*
	CTabBarControlEntry * pTab;
	pTab = m_pTabBar->addTab("gta3.img (1000)", true, "firstItemHorizontally");
	pTab = m_pTabBar->addTab("gta3 - backup.img (1200)");
	pTab = m_pTabBar->addTab("gta3.img (1000)");
	*/

	// 2nd left menu - actions
	x = 139;
	y += h;
	w = 110;
	h = 30;
	h2 = h;
	h3 = h2 + 0;
	strStyleGroup = "secondLeftMenu";

	addButton(x, y, w, h, "Import", strStyleGroup + " firstItemVertically");
	y += h2;
	addButton(x, y, w, h, "Export", strStyleGroup);
	y += h2;
	addButton(x, y, w, h, "Quick Export", strStyleGroup);
	y += h3;

	addButton(x, y, w, h, "Rename", "thirdItemVertically " + strStyleGroup);
	y += h2;
	addButton(x, y, w, h, "Replace", strStyleGroup);
	y += h2;
	addButton(x, y, w, h, "Remove", strStyleGroup);
	y += h3;

	addButton(x, y, w, h, "Merge", "thirdItemVertically " + strStyleGroup);
	y += h2;
	addButton(x, y, w, h, "Split", strStyleGroup);
	y += h2;
	addButton(x, y, w, h, "Convert", strStyleGroup);
	y += h3;

	addButton(x, y, w, h, "Select", "thirdItemVertically " + strStyleGroup);
	y += h2;
	addButton(x, y, w, h, "Sort", strStyleGroup);
	y += h2;
	addButton(x, y, w, h, "LST", strStyleGroup);
	y += h3;

	// progress bar
	w = 150;
	w2 = 10;
	h2 = 10;
	x = (m_pWindow->getSize().x - w2) - w;
	y = uiTitleBarHeight + h2;
	h = 5;
	strStyleGroup = "progressBar";

	m_pProgressBar = addProgress(x, y, w, h, strStyleGroup);
}

void		CMainLayer::initControls(void)
{
	CEventManager::get()->bindEvent(EVENT_onResizeWindow, [](void* pArg1, void* pArg2) {
		((CMainLayer*)pArg1)->repositionAndResizeControls();
	}, this);
	repositionAndResizeControls();
}

void		CMainLayer::repositionAndResizeControls(void)
{
	CWindow *pWindow = getWindow();

	Vec2i point;
	Vec2u size;
	int32 iNewX, iNewY, iNewWidth, iNewHeight;

	// progress bar
	point = m_pProgressBar->getPosition();
	iNewX = (pWindow->getSize().x - m_pProgressBar->getSize().x) - 10;
	m_pProgressBar->setPosition(Vec2i(iNewX, point.y));

	// filter bar - search box
	size = m_pSearchBox->getSize();
	iNewWidth = pWindow->getSize().x - 438 - 380 - 9;
	m_pSearchBox->setSize(Vec2u(iNewWidth, size.y));

	// filter bar - entry type
	point = m_pEntryTypeFilter->getPosition();
	iNewX = (m_pSearchBox->getPosition().x + iNewWidth) - 1;
	m_pEntryTypeFilter->setPosition(Vec2i(iNewX, point.y));

	// filter bar - entry version
	point = m_pEntryVersionFilter->getPosition();
	iNewX = (m_pEntryTypeFilter->getPosition().x + m_pEntryTypeFilter->getSize().x) - 1;
	m_pEntryVersionFilter->setPosition(Vec2i(iNewX, point.y));
}