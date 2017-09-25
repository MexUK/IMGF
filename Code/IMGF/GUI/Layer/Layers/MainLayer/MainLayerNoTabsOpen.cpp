#include "MainLayerNoTabsOpen.h"
#include "Control/Controls/ProgressBar.h"
#include "Control/Controls/TextBox.h"
#include "Event/EInputEvent.h"

using namespace std;
using namespace bxcf;
using namespace bxgx;
using namespace bxgx::events;
using namespace imgf;

MainLayerNoTabsOpen::MainLayerNoTabsOpen(void) :
	m_pMainWindow(nullptr),
	m_pText_FilePath(nullptr),
	m_pText_FileVersion(nullptr),
	m_pText_FileGame(nullptr),
	m_pText_FileEntryCount(nullptr),
	m_pLog(nullptr),
	m_pSearchBox(nullptr),
	m_pProgressBar(nullptr)
{
}

// main interface
void						MainLayerNoTabsOpen::init(void)
{
	addControls();
	initControls();
}

// controls
void						MainLayerNoTabsOpen::addControls(void)
{
	int32 x, y, y2;
	uint32 w, h, w2, h2, uiTitleBarHeight, uiButtonHeight, uiLogWidth;
	string strStyleGroup;

	uiTitleBarHeight = m_pWindow->getTitleBarHeight();
	uiButtonHeight = 37;
	uiLogWidth = 335;

	// log
	w = 335;
	h = 300;
	x = m_pWindow->getSize().x - w;
	y = m_pWindow->getTitleBarHeight() + uiButtonHeight;

	m_pLog = addTextBox(x, y, w, h, "", true, "log");
	m_pLog->setReadOnly(true);

	// search box
	w2 = 139;
	x = 139 + 139 + (4 * w2);
	y = uiTitleBarHeight;
	w = m_pWindow->getSize().x - x - (uiButtonHeight + 1);
	h = uiButtonHeight;

	m_pSearchBox = addTextBox(x, y, w, h, "Search", false, "filter");

	// progress bar
	w = 150;
	w2 = 10;
	h2 = uiButtonHeight + 10;
	x = m_pWindow->getSize().x - w2 - w - uiLogWidth;
	y = uiTitleBarHeight + h2;
	h = 5;

	m_pProgressBar = addProgressBar(x, y, w, h, "progressBar");

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
}

void						MainLayerNoTabsOpen::initControls(void)
{
	bindEvent(RESIZE_WINDOW, &MainLayerNoTabsOpen::repositionAndResizeControls);
	repositionAndResizeControls(Vec2i(0, 0));
}

void						MainLayerNoTabsOpen::repositionAndResizeControls(Vec2i& vecSizeDifference)
{
	Vec2i point;
	Vec2u size;
	int32 iNewX, iNewWidth;
	uint32 uiButtonHeight, uiLogWidth;

	uiButtonHeight = 37;
	uiLogWidth = 335;

	// progress bar
	point = m_pProgressBar->getPosition();
	iNewX = (m_pWindow->getSize().x - m_pProgressBar->getSize().x) - 10 - uiLogWidth;
	m_pProgressBar->setPosition(Vec2i(iNewX, point.y));

	// search box
	size = m_pSearchBox->getSize();
	iNewWidth = (m_pWindow->getSize().x - m_pSearchBox->getPosition().x) - (uiButtonHeight + 1);
	m_pSearchBox->setSize(Vec2u(iNewWidth, size.y));

	// log
	point = m_pLog->getPosition();
	iNewX = m_pWindow->getSize().x - uiLogWidth;
	m_pLog->setPosition(Vec2i(iNewX, point.y));
}