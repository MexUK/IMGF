#include "MainLayerNoTabsOpen.h"
#include "Control/Controls/ProgressBar.h"
#include "Control/Controls/TextBox.h"
#include "Event/EInputEvent.h"

using namespace bxcf;
using namespace bxgx;
using namespace bxgx::events;
using namespace imgf;

MainLayerNoTabsOpen::MainLayerNoTabsOpen(void) :
	m_pMainWindow(nullptr),
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
	int32 x, y;
	uint32 w, h, w2, h2, uiTitleBarHeight, uiButtonHeight, uiLogWidth;

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