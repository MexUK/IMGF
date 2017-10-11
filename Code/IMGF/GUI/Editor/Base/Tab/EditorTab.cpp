#include "nsbxcf.h"
#include "EditorTab.h"
#include "GUI/Editor/Base/Editor.h"
#include "Control/Controls/TextBox.h"
#include "Control/Controls/ProgressBar.h"
#include "Control/Entries/Tab.h"
#include "IMGF.h"
#include "GUI/Input/InputManager.h"
#include "GUI/Window/WindowManager.h"
#include "GUI/Window/Windows/MainWindow/MainWindow.h"
#include "GUI/Layer/Layers/MainLayer/MainLayerNoTabsOpen.h"
#include "Task/TaskManager.h"
#include "Settings/SettingsManager.h"
#include "Static/File.h"
#include "Static/Path.h"
#include "BXGX.h"
#include <stdarg.h>

using namespace std;
using namespace bxcf;
using namespace bxgx;
using namespace bxgx::events;
using namespace imgf;

EditorTab::EditorTab(void) :
	m_bMarkedToClose(false),
	m_bThreadHasTerminated(false),
	m_pEditor(nullptr),
	m_pFile(nullptr),
	m_pTab(nullptr),
	m_pLog(nullptr),
	m_pSearchBox(nullptr),
	m_pProgressBar(nullptr)
{
}

EditorTab::~EditorTab(void)
{
	unbindEvent(RESIZE_WINDOW, &EditorTab::repositionAndResizeControls);
	unbindEvent(TASK_PROGRESS, &EditorTab::onTaskProgress);
}

// initialization
void						EditorTab::init(void)
{
	addControls();
	initControls();

	m_thread = thread([&]() { processThread(); });
}

// tab processing
void						EditorTab::processThread(void)
{
	while (!m_bMarkedToClose)
	{
		processThreadOnce();
		Sleep(1);
	}

	m_bThreadHasTerminated = true;
}

void						EditorTab::processThreadOnce(void)
{
	mutexControlInput.lock();
	vector<Button*> vecButtonsPressed = m_vecButtonsPressed;
	vector<MenuItem*> vecMenuItemsPressed = m_vecMenuItemsPressed;
	m_vecButtonsPressed.clear();
	m_vecMenuItemsPressed.clear();
	mutexControlInput.unlock();

	for (Button *pButtonPressed : vecButtonsPressed)
	{
		Events::trigger(bxgx::events::PRESS_BUTTON, pButtonPressed);
	}

	for (MenuItem *pMenuItem : vecMenuItemsPressed)
	{
		getIMGF()->getInputManager()->processMenuItemPress(pMenuItem);
	}

	if (vecButtonsPressed.size() > 0 || vecMenuItemsPressed.size() > 0)
	{
		// check to render each window or window items
		BXGX::get()->render();
	}
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
	uint32 w, h, w2, h2, uiTitleBarHeight, uiButtonHeight, uiLogWidth;

	uiTitleBarHeight = m_pWindow->getTitleBarHeight();
	uiButtonHeight = 37;
	uiLogWidth = 335;

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
	w = m_pWindow->getSize().x - x - (uiButtonHeight + 1);
	h = uiButtonHeight;

	m_pSearchBox = addTextBox(x, y, w, h, "Search", false, "filter filterSearchBox");

	// progress bar
	w = 150;
	w2 = 10;
	h2 = uiButtonHeight + 10;
	x = m_pWindow->getSize().x - w2 - w - uiLogWidth;
	y = uiTitleBarHeight + h2;
	h = 5;

	m_pProgressBar = addProgressBar(x, y, w, h, "progressBar");
}

void						EditorTab::initControls(void)
{
	bindEvent(RESIZE_WINDOW, &EditorTab::repositionAndResizeControls);
	repositionAndResizeControls(Vec2i(0, 0));

	// todo
	//static bool bTaskProgressEventBound = false;
	//if (!bTaskProgressEventBound)
	//{
		bindEvent(TASK_PROGRESS, &EditorTab::onTaskProgress);
		//bTaskProgressEventBound = true;
	//}
}

void						EditorTab::repositionAndResizeControls(Vec2i& vecSizeDifference)
{
	Vec2i point;
	Vec2u size;
	int32 iNewX, iNewWidth;
	uint32 uiButtonHeight, uiLogWidth;

	uiButtonHeight = 37;
	uiLogWidth = 335;

	// progress bar
	point = m_pProgressBar->getPosition();
	iNewX = m_pWindow->getSize().x - m_pProgressBar->getSize().x - uiLogWidth - 10;
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

// progress bar
void						EditorTab::onTaskProgress(void)
{
	getIMGF()->getTaskManager()->onTaskProgressTick();
}

// log
void						EditorTab::log(string strText)
{
	m_pLog->addText(strText);

	SettingsManager *pSettingsManager = getIMGF()->getSettingsManager();
	bool bSaveLogsToFolder = pSettingsManager->getSetting("SaveLogsToFolder") == "1";
	if (bSaveLogsToFolder)
	{
		string strLogsFolderPath = pSettingsManager->getSetting("LogsFolderPath");
		if (strLogsFolderPath != "")
		{
			string strLogsFilePath = Path::addSlashToEnd(strLogsFolderPath) + String::getDateTextForFolder() + ".txt";
			File::addToTextFile(strLogsFilePath, strText + "\n");
		}
	}
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