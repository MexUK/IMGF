#include "CMainLayer.h"
#include "Window/CWindow.h"
#include "CGUIManager.h"
#include "Type/Colour/CColour.h"
#include "Controls/CTabBarControl.h"
#include "Controls/CDropControl.h"
#include "Controls/CButtonControl.h"
#include "Controls/CProgressControl.h"
#include "Controls/CTextBoxControl.h"
#include "Shapes/CLineShape.h"
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
		uiTitleBarHeight = getWindow()->getTitleBarHeight(),
		uiButtonHeight = 37;
	CButtonControl
		*pButton;
	string
		strStyleGroup;

	// top left menu
	x = 0;
	y = uiTitleBarHeight;
	w = 70;
	h = uiButtonHeight;
	strStyleGroup = "topLeftMenuButton";

	pButton = addButton(x, y, w, h, "Formats", "firstItemHorizontally " + strStyleGroup, FORMATS);
	x += w - 1;
	pButton = addButton(x, y, w, h, "Utility", strStyleGroup, UTILITY);

	// game information headers
	x = 149 + 139;
	y = (uiTitleBarHeight - 1) + uiButtonHeight + 10;
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
	y = (uiTitleBarHeight - 1) + uiButtonHeight + 10;
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
	x = 139 + 139;
	y = uiTitleBarHeight;
	w = 139;
	h = uiButtonHeight;
	w2 = w;
	strStyleGroup = "topMenuButton";

	addButton(x, y, w, h, "New", strStyleGroup + " firstItemHorizontally", NEW);
	x += w2;
	addButton(x, y, w, h, "Open", strStyleGroup, OPEN);
	x += w2;
	addButton(x, y, w, h, "Close", strStyleGroup, CLOSE);
	x += w2;
	addButton(x, y, w, h, "Save", strStyleGroup, SAVE);
	x += w2;

	// filter bar - search box
	w2 = 0;
	x += w2;
	w = (m_pWindow->getSize().x - x) - (uiButtonHeight + 1);
	h = uiButtonHeight;
	strStyleGroup = "filter";

	m_pSearchBox = addTextBox(x, y, w, h, "Search", false, strStyleGroup);

	// settings icon
	x += w;
	w = uiButtonHeight + 1;
	h = uiButtonHeight;
	strStyleGroup = "settingsMenu";

	m_pSettingsButton = addButton(x, y, w, h, "", strStyleGroup, SETTINGS);
	m_pSettingsButtonLine1 = addLine(x + 10, y + 10, x + 27, y + 10, "settingsMenuLine");
	m_pSettingsButtonLine2 = addLine(x + 10, y + 19, x + 27, y + 19, "settingsMenuLine");
	m_pSettingsButtonLine3 = addLine(x + 10, y + 28, x + 27, y + 28, "settingsMenuLine");

	// filter bar - entry type
	w = 140;
	w2 = 140;
	x = (m_pWindow->getSize().x - w) - w2;
	y = uiButtonHeight + 75;
	h = 32;
	strStyleGroup = "filter";

	m_pEntryTypeFilter = addDrop(x, y, w, h, "Entry Type", strStyleGroup + " firstItemHorizontally");
	m_pEntryTypeFilter->addItem("No file is open", false, false);

	// filter bar - entry version
	w = w2;
	x = m_pWindow->getSize().x - w;
	y = uiButtonHeight + 75;
	h = 32;

	m_pEntryVersionFilter = addDrop(x, y, w, h, "Entry Version", strStyleGroup);
	m_pEntryVersionFilter->addItem("No file is open", false, false);

	// files tab bar
	x = 139;
	y = 162;
	w = 500;
	h = 30;
	strStyleGroup = "fileTabBar";

	m_pTabBar = addTabBar(x, y, (getWindow()->getSize().x - 10) - 249, h, strStyleGroup);
	m_pTabBar->setDefaultText("No tabs to display");

	/*
	CTabBarControlEntry * pTab;
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
	int32 x, y, iNewX, iNewY, iNewWidth, iNewHeight;
	uint32 uiButtonHeight = 37;

	// progress bar
	point = m_pProgressBar->getPosition();
	iNewX = (pWindow->getSize().x - m_pProgressBar->getSize().x) - 10;
	m_pProgressBar->setPosition(Vec2i(iNewX, point.y));

	// filter bar - search box
	size = m_pSearchBox->getSize();
	iNewWidth = (pWindow->getSize().x - m_pSearchBox->getPosition().x) - (uiButtonHeight + 1);
	m_pSearchBox->setSize(Vec2u(iNewWidth, size.y));

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

	// filter bar - entry type
	point = m_pEntryTypeFilter->getPosition();
	iNewX = (pWindow->getSize().x - m_pEntryTypeFilter->getSize().x) - m_pEntryVersionFilter->getSize().x;
	m_pEntryTypeFilter->setPosition(Vec2i(iNewX, point.y));

	// filter bar - entry version
	point = m_pEntryVersionFilter->getPosition();
	iNewX = pWindow->getSize().x - m_pEntryVersionFilter->getSize().x;
	m_pEntryVersionFilter->setPosition(Vec2i(iNewX, point.y));
}