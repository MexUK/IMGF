#include "nsbxcf.h"
#include "EditorTab.h"
#include "GUI/Editor/Base/Editor.h"
#include "Control/Controls/TextBox.h"
#include "Control/Controls/ProgressBar.h"
#include "Control/Controls/TabBar.h"
#include "Control/Entries/Tab.h"
#include "IMGF.h"
#include "GUI/Input/InputManager.h"
#include "GUI/Window/WindowManager.h"
#include "GUI/Window/Windows/MainWindow/MainWindow.h"
#include "GUI/Layer/Layers/MainLayer/MainLayer.h"
#include "GUI/Layer/Layers/MainLayer/MainLayerNoTabsOpen.h"
#include "Task/TaskManager.h"
#include "Settings/SettingsManager.h"
#include "Static/File.h"
#include "Static/Path.h"
#include "Static/StdVector.h"
#include "BXGX.h"
#include "Format/Format.h"
#include "Stream/DataReader.h"
#include "../bxgi/Event/EEvent.h"
#include <stdarg.h>

using namespace std;
using namespace bxcf;
using namespace bxgx;
using namespace bxgx::events;
using namespace bxgi;
using namespace imgf;

EditorTab::EditorTab(void) :
	m_bMarkedToClose(false),
	m_bThreadHasTerminated(false),
	m_bFileUnsaved(false),

	m_pEditor(nullptr),
	m_pFile(nullptr),

	m_pText_FilePath(nullptr),
	m_pText_FileVersion(nullptr),
	m_pText_FileGame(nullptr),
	m_pText_FileEntryCount(nullptr),

	m_pTab(nullptr),
	m_pLog(nullptr),
	m_pSearchBox(nullptr),
	m_pProgressBar(nullptr)
{
}

EditorTab::~EditorTab(void)
{
	unbindEvents();
}

// events
void						EditorTab::bindEvents(void)
{
	bindEvent(RESIZE_WINDOW, &EditorTab::repositionAndResizeControls);
	bindEvent(TASK_PROGRESS, &EditorTab::onTaskProgress);
	bindEvent(UNSERIALIZE_FILE_PROGRESS, &EditorTab::onUnserializeFileProgress);

	Layer::bindEvents();
}

void						EditorTab::unbindEvents(void)
{
	unbindEvent(RESIZE_WINDOW, &EditorTab::repositionAndResizeControls);
	unbindEvent(TASK_PROGRESS, &EditorTab::onTaskProgress);
	unbindEvent(UNSERIALIZE_FILE_PROGRESS, &EditorTab::onUnserializeFileProgress);

	Layer::unbindEvents();
}

// initialization
bool						EditorTab::init(bool bIsNewFile)
{
	/*
	todo

	// add base editor controls
	m_pEditor->Editor::addControls();

	// add derived editor controls
	m_pEditor->addControls();
	*/

	// add base editor tab controls
	EditorTab::addControls();
	EditorTab::initControls();

	// add derived editor tab controls
	addControls();
	initControls();

	// add thread
	m_thread = thread([&]() { processThread(); });

	// add gui tab
	string strTabText = Path::getFileName(m_pFile->getFilePath());
	if (String::toUpperCase(Path::getFileExtension(strTabText)) == "DIR")
	{
		strTabText = Path::replaceFileExtensionWithCase(strTabText, "IMG");
	}
	strTabText += " (Loading..)";

	TabBar *pTabBar = m_pEditor->getTabBar();
	m_pTab = pTabBar->addTab(strTabText, true);
	pTabBar->bindTabLayer(m_pTab, this);

	// set active editor tab
	m_pEditor->setActiveEditorTab(this);

	// unserialize file
	if (!bIsNewFile && !unserializeFile())
	{
		return false;
	}

	// on file loaded
	onFileLoaded();

	// display editor tab
	//getEditor()->setEnabled(true);

	// set certain menu items enabled
	m_pEditor->getMainWindow()->getMainLayer()->setCertainMenuItemsEnabled(true);

	// log
	string strFileName = Path::getFileName(m_pFile->getFilePath());
	logf("Opened %s", strFileName.c_str());

	return true;
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

	EEditor uiActiveEditor = getIMGF()->getWindowManager()->getMainWindow()->getActiveEditor()->getEditorType();
	if (vecButtonsPressed.size() > 0 || vecMenuItemsPressed.size() > 0)
	{
		// check to render each window or window items
		BXGX::get()->render();
	}
	else if (uiActiveEditor == MODEL_EDITOR || uiActiveEditor == COLLISION_EDITOR || uiActiveEditor == ANIMATION_EDITOR)
	{
		render();
	}
}

// logs
void						EditorTab::clearLogs(void)
{
	m_pLog->setText("");

	/*
	todo
	
	getLogLinesGUI().clear();
	getLogLinesBasic().clear();
	getLogLinesExtended().clear();
	*/
}

// tab index
uint32						EditorTab::getTabIndex(void)
{
	return m_pTab->getIndex();
}

// controls
void						EditorTab::addControls(void)
{
	int32 x, y, y2;
	uint32 w, h, w2, h2, uiTitleBarHeight, uiButtonHeight, uiLogWidth;
	string strStyleGroup;

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

	m_pText_FilePath = addText(x, y, w, h, "Loading..", strStyleGroup, -1, -150);
	y += h2;
	m_pText_FileVersion = addText(x, y, w2, h, "-", strStyleGroup, -1, -150);
	y += h2;
	m_pText_FileGame = addText(x, y, w2, h, "-", strStyleGroup, -1, -150);
	y += h2;
	m_pText_FileEntryCount = addText(x, y, w2, h, "-", strStyleGroup, -1, -150);
}

void						EditorTab::initControls(void)
{
	// todo bindEvents();
	repositionAndResizeControls(Vec2i(0, 0));
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

// update tab text
void						EditorTab::updateTabText(void)
{
	string strTabText = Path::getFileName(m_pFile->getFilePath());
	m_pTab->setText(strTabText);
}

// unserialize file progress
void						EditorTab::onUnserializeFileProgress(DataReader *pDataReader)
{
	getProgressBar()->setCurrent(pDataReader->getSeek());
}

// add entry
void*						EditorTab::addEntryViaFile(string& strEntryFilePath, string strEntryName)
{
	return _addEntry<FormatEntry*>(strEntryFilePath, true, strEntryName);
}

void*						EditorTab::addEntryViaData(string strEntryName, string& strEntryData)
{
	return _addEntry<FormatEntry*>(strEntryData, false, strEntryName);
}

// selected entries
void						EditorTab::setSelectedEntriesNameCase(uint32 uiNameCaseType)
{
	for (FormatEntry *pEntry : getSelectedEntries())
	{
		string strNewEntryName;
		switch (uiNameCaseType)
		{
		case 0: // lower case
			strNewEntryName = String::toLowerCase(pEntry->getEntryName());
			break;
		case 1: // UPPER CASE
			strNewEntryName = String::toUpperCase(pEntry->getEntryName());
			break;
		case 2: // Title Case
			strNewEntryName = String::toTitleCase(pEntry->getEntryName());
			break;
		}
		pEntry->setEntryName(strNewEntryName);
		onEntryChange(pEntry);
	}

	setFileUnsaved(true);
}

void						EditorTab::copySelectedEntryData(uint32 uiColumnType)
{
	vector<string> vecCopyLines;
	for (FormatEntry *pEntry : getSelectedEntries())
	{
		switch (uiColumnType)
		{
		case 0: // Index
			vecCopyLines.push_back(String::toString(pEntry->getIndex()));
			break;
		case 1: // Type
			vecCopyLines.push_back(pEntry->getEntryExtension());
			break;
		case 2: // Name
			vecCopyLines.push_back(pEntry->getEntryName());
			break;
		case 3: // Offset
			vecCopyLines.push_back(String::toString(pEntry->getEntryOffset()));
			break;
		case 4: // Size
			vecCopyLines.push_back(String::toString(pEntry->getEntrySize()));
			break;
		case 5: // Version
			vecCopyLines.push_back(pEntry->getVersionText());
			break;
		case 6: // All Row Data
			vecCopyLines.push_back(
				String::toString(pEntry->getIndex()) + "," +
				pEntry->getEntryExtension() + "," +
				pEntry->getEntryName() + "," +
				String::toString(pEntry->getEntryOffset()) + "," +
				String::toString(pEntry->getEntrySize()) + "," +
				pEntry->getVersionText()
			);
			break;
		}
	}
	String::setClipboardText(String::join(vecCopyLines, "\r\n"));
}

void						EditorTab::shiftSelectedEntries(int32 uiRowCountOffset)
{
	for (FormatEntry *pEntry1 : getSelectedEntries())
	{
		int32 iEntry1Index = StdVector::findKey(getContainerFile()->getAllEntries(), pEntry1);
		int32 iEntry2Index = Math::limit(iEntry1Index + (int32)uiRowCountOffset, 0, (int32)getTotalEntryCount());
		FormatEntry *pEntry2 = getContainerFile()->getAllEntries()[iEntry2Index];

		getContainerFile()->swapEntries(pEntry1, pEntry2);
	}

	recreateEntryList();
	setFileUnsaved(true);
}