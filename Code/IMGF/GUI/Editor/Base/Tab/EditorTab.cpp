#include "nsbxcf.h"
#include "EditorTab.h"
#include "GUI/Editor/Base/Editor.h"
#include "Control/Controls/TextBox.h"
#include "Control/Controls/ProgressBar.h"
#include "Control/Entries/Tab.h"
#include "IMGF.h"
#include "GUI/Window/WindowManager.h"
#include "GUI/Window/Windows/MainWindow/MainWindow.h"
#include "GUI/Layer/Layers/MainLayer/MainLayerNoTabsOpen.h"
#include "Task/TaskManager.h"
#include <stdarg.h>

using namespace std;
using namespace bxcf;
using namespace bxgx;
using namespace bxgx::events;
using namespace imgf;

EditorTab::EditorTab(void) :
	m_pEditor(nullptr),
	m_pFile(nullptr),
	m_pTab(nullptr),
	m_pLog(nullptr),
	m_pSearchBox(nullptr),
	m_pProgressBar(nullptr)
{
}

// tab index
uint32						EditorTab::getTabIndex(void)
{
	return m_pTab->getIndex();
}

// controls
void						EditorTab::addControls(void)
{
	int32 x, y;
	uint32 w, h, w2, h2, uiTitleBarHeight, uiButtonHeight;

	uiTitleBarHeight = m_pWindow->getTitleBarHeight();
	uiButtonHeight = 37;

	// log
	TextBox *pBlankLog = getIMGF()->getWindowManager()->getMainWindow()->getMainLayerNoTabsOpen()->getLog();

	x = pBlankLog->getPosition().x;
	y = pBlankLog->getPosition().y;
	w = pBlankLog->getSize().x;
	h = pBlankLog->getSize().y;

	m_pLog = addTextBox(x, y, w, h, "", true, "log");
	m_pLog->setReadOnly(true);

	// search box
	w2 = 139;
	x = 139 + 139 + (4 * w2);
	y = uiTitleBarHeight;
	w = (m_pWindow->getSize().x - x) - (uiButtonHeight + 1);
	h = uiButtonHeight;

	m_pSearchBox = addTextBox(x, y, w, h, "Search", false, "filter");

	// progress bar
	w = 150;
	w2 = 10;
	h2 = uiButtonHeight + 10;
	x = (m_pWindow->getSize().x - w2) - w;
	y = uiTitleBarHeight + h2;
	h = 5;

	m_pProgressBar = addProgressBar(x, y, w, h, "progressBar");
}

void						EditorTab::initControls(void)
{
	bindEvent(RESIZE_WINDOW, &EditorTab::repositionAndResizeControls);
	repositionAndResizeControls(Vec2i(0, 0));

	bindEvent(TASK_PROGRESS, &EditorTab::onTaskProgress);
}

void						EditorTab::repositionAndResizeControls(Vec2i& vecSizeDifference)
{
	Vec2i point;
	Vec2u size;
	int32 iNewX, iNewWidth;
	uint32 uiButtonHeight;

	uiButtonHeight = 37;

	// progress bar
	point = m_pProgressBar->getPosition();
	iNewX = (m_pWindow->getSize().x - m_pProgressBar->getSize().x) - 10;
	m_pProgressBar->setPosition(Vec2i(iNewX, point.y));

	// search box
	size = m_pSearchBox->getSize();
	iNewWidth = (m_pWindow->getSize().x - m_pSearchBox->getPosition().x) - (uiButtonHeight + 1);
	m_pSearchBox->setSize(Vec2u(iNewWidth, size.y));
}

// progress bar
void						EditorTab::onTaskProgress(void)
{
	getIMGF()->getTaskManager()->onTaskProgressTick();
}

// log
void						EditorTab::log(string strText)
{
	//getLogLines().addEntry(strText);
	m_pLog->addText(strText);
}

void						EditorTab::logf(string strFormatText, ...)
{
	char szBuffer[8192];
	memset(szBuffer, '\0', 8192);
	va_list va;
	va_start(va, strFormatText);
	vsprintf_s(szBuffer, 8192, strFormatText.c_str(), va);
	va_end(va);

	log(szBuffer);
}