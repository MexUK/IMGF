#include "nsbxcf.h"
//#include <Windows.h>
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
#include "Task/TaskManager.h"
#include "Settings/SettingsManager.h"
#include "Static/File.h"
#include "Static/Path.h"
#include "Static/StdVector.h"
#include "BXGX.h"
#include "Format/Format.h"
#include "Stream/DataReader.h"
#include "../bxgi/Event/EEvent.h"
#include "DragDrop/DropSource.h"
#include "DragDrop/DataObject.h"
#include "Task/Tasks/RecentlyOpen/RecentlyOpenManager.h"
#include <stdarg.h>
#include <Shlobj.h>

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
	m_pProgressBar(nullptr),

	m_pLayer(nullptr),

	m_bPart1Initialized(false)
{
}

EditorTab::~EditorTab(void)
{
	//EditorTab::unbindEvents();

	/*
	todo
	unbindEvent(CHANGE_TAB, &EditorTab::onChangeTab);
	unbindEvent(REMOVE_TAB, &EditorTab::onRemoveTab);
	unbindEvent(TASK_PROGRESS, &EditorTab::onTaskProgress);
	unbindEvent(UNSERIALIZE_FILE_PROGRESS, &EditorTab::onUnserializeFileProgress);
	unbindEvent(CHANGE_TEXT_BOX, &EditorTab::onChangeTextBox);
	*/
	//m_pLayer->getWindow()->removeLayer(m_pLayer);
}

// events
void						EditorTab::bindEvents(void)
{
	bindDefaultEvent(CHANGE_TAB, &EditorTab::onChangeTab);
	bindDefaultEvent(REMOVE_TAB, &EditorTab::onRemoveTab);
	bindDefaultEvent(TASK_PROGRESS, &EditorTab::onTaskProgress);
	bindDefaultEvent(UNSERIALIZE_FILE_PROGRESS, &EditorTab::onUnserializeFileProgress);
	bindDefaultEvent(CHANGE_TEXT_BOX, &EditorTab::onChangeTextBox);
	bindDefaultEvent(ADD_CONTAINED_WINDOW, &EditorTab::onAddContainedWindow);
	bindDefaultEvent(REMOVE_CONTAINED_WINDOW, &EditorTab::onRemoveContainedWindow);

	//getBaseLayer()->bindEvents();
	//getLayer()->bindEvents();
}

void						EditorTab::unbindEvents(void)
{
	unbindDefaultEvent(CHANGE_TAB, &EditorTab::onChangeTab);
	unbindDefaultEvent(REMOVE_TAB, &EditorTab::onRemoveTab);
	unbindDefaultEvent(TASK_PROGRESS, &EditorTab::onTaskProgress);
	unbindDefaultEvent(UNSERIALIZE_FILE_PROGRESS, &EditorTab::onUnserializeFileProgress);
	unbindDefaultEvent(CHANGE_TEXT_BOX, &EditorTab::onChangeTextBox);
	unbindDefaultEvent(ADD_CONTAINED_WINDOW, &EditorTab::onAddContainedWindow);
	unbindDefaultEvent(REMOVE_CONTAINED_WINDOW, &EditorTab::onRemoveContainedWindow);

	//getBaseLayer()->unbindEvents();
	//getLayer()->unbindEvents();
}

// initialization
bool						EditorTab::init(bool bIsNewFile)
{
	// base layer
	m_pBaseLayer = m_pEditor->getMainWindow()->getLayerById(90)->copyLayer();
	m_pBaseLayer->setId(-1);
	m_pBaseLayer->setEnabledWithoutEvents(false);
	m_pEditor->getMainWindow()->addLayer(m_pBaseLayer);

	// derived layer
	initLayer();
	m_pLayer = m_pLayer->copyLayer();
	m_pLayer->setId(-1);
	m_pLayer->setEnabledWithoutEvents(false);
	m_pEditor->getMainWindow()->addLayer(m_pLayer);

	// store controls - base and derived
	EditorTab::storeControls();
	storeControls();

	// add gui tab
	string strTabText = Path::getFileName(m_pFile->getFilePath());
	if (String::toUpperCase(Path::getFileExtension(strTabText)) == "DIR")
	{
		strTabText = Path::replaceFileExtensionWithCase(strTabText, "IMG");
	}
	strTabText += " (Loading..)";

	TabBar *pTabBar = m_pEditor->getTabBar();
	m_pTab = pTabBar->addTab(strTabText, true);
	pTabBar->bindTabLayer(m_pTab, getLayer());

	// set active editor tab
	m_pEditor->setActiveEditorTab(this);

	// add thread
	m_thread = thread([&]() { processThread(); });

	// unserialize file
	if (!bIsNewFile && !unserializeFile())
	{
		return false;
	}

	// add file path to recently opened files list
	getIMGF()->getRecentlyOpenManager()->addRecentlyOpenEntry(m_pEditor->getEditorType(), m_pEditor->getResolvedFilePath(getFile()->getFilePath()));

	// on file loaded
	onFileLoaded();

	// set certain menu items enabled
	m_pEditor->getMainWindow()->setCertainMenuItemsEnabled(true);

	// log
	string strFileName = Path::getFileName(m_pFile->getFilePath());
	logf("Opened %s", strFileName.c_str());

	// mark part 1 as initialized
	m_bPart1Initialized = true;

	// render
	getLayer()->getWindow()->render();

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
		Events::triggerDefault(bxgx::events::PRESS_BUTTON, pButtonPressed);
	}
	if (isMarkedToClose())
	{
		return;
	}

	for (MenuItem *pMenuItem : vecMenuItemsPressed)
	{
		getIMGF()->getInputManager()->processMenuItemPress(pMenuItem);
	}
	if (isMarkedToClose())
	{
		return;
	}

	Editor *pActiveEditor = getIMGF()->getWindowManager()->getMainWindow()->getActiveEditor();
	if (pActiveEditor)
	{
		EEditor uiActiveEditor = pActiveEditor->getEditorType();
		if (vecButtonsPressed.size() > 0 || vecMenuItemsPressed.size() > 0)
		{
			// check to render each window or window items
			BXGX::get()->render();
		}
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
void						EditorTab::storeControls(void)
{
	m_pProgressBar = (ProgressBar*)m_pBaseLayer->getItemById(80);
	m_pLog = (TextBox*)m_pBaseLayer->getItemById(81);
	m_pText_FilePath = (Text*)m_pBaseLayer->getItemById(91);
	m_pText_FileEntryCount = (Text*)m_pBaseLayer->getItemById(92);
	m_pText_FileVersion = (Text*)m_pBaseLayer->getItemById(93);
	m_pText_FileGame = (Text*)m_pBaseLayer->getItemById(79);
	m_pSearchBox = (TextBox*)m_pBaseLayer->getItemById(85);
}

// event callbacks
void						EditorTab::onTaskProgress(void)
{
	getIMGF()->getTaskManager()->onTaskProgressTick();
}

void						EditorTab::onChangeTextBox(TextBox *pTextBox)
{
	if (pTextBox == m_pSearchBox)
	{
		recreateEntryList();
	}
}

void						EditorTab::onChangeTab(TabBar *pTabBar)
{
	EditorTab *pNewActiveEditorTab = getEditor()->getEditorTabs().getEntryByIndex(pTabBar->getIndexByEntry(pTabBar->getActiveTab()));
	getEditor()->setActiveEditorTab(pNewActiveEditorTab);
}

void						EditorTab::onRemoveTab(Tab *pTab)
{
	int32 iTabIndex = pTab->getTabBar()->getIndexByEntry(pTab);
	if (iTabIndex == -1)
	{
		return;
	}

	EditorTab *pEditorTab = getEditor()->getEditorTabs().getEntryByIndex(iTabIndex);
	m_pEditor->getMainWindow()->onCloseEditorTab(pEditorTab);
}

void						EditorTab::onAddContainedWindow(void)
{
	unbindEvents();
	getLayer()->setEnabled(false);
	getBaseLayer()->setEnabled(false);
	m_pEditor->getMainWindow()->getLayerById(45)->setEnabled(false);
	bindDefaultEvent(REMOVE_CONTAINED_WINDOW, &EditorTab::onRemoveContainedWindow);
}

void						EditorTab::onRemoveContainedWindow(void)
{
	unbindDefaultEvent(REMOVE_CONTAINED_WINDOW, &EditorTab::onRemoveContainedWindow);
	m_pEditor->getMainWindow()->getLayerById(45)->setEnabled(true);
	getBaseLayer()->setEnabled(true);
	getLayer()->setEnabled(true);
	bindEvents();
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

vector<FormatEntry*>			EditorTab::getEntriesByNumericMultiOptionValues(uint32 uiEntryAttribute, uint32 uiMatchType, uint32 uiValue1, uint32 uiValue2)
{
	vector<FormatEntry*> vecEntries;
	switch (uiEntryAttribute)
	{
	case 0: // Index
	{
		uiValue1--;
		uiValue2--;
		unordered_map<FormatEntry*, uint32> umapEntryIndices;
		uint32 uiIndex = 0;
		for (FormatEntry *pEntry : getContainerFile()->getAllEntries())
		{
			umapEntryIndices[pEntry] = uiIndex++;
		}
		switch (uiMatchType)
		{
		case 0: // Equal to
			for (FormatEntry *pEntry : getContainerFile()->getAllEntries()) {	if (umapEntryIndices[pEntry] == uiValue1)	vecEntries.push_back(pEntry);		Events::triggerDefault(TASK_PROGRESS); }
			break;
		case 1: // Not equal to
			for (FormatEntry *pEntry : getContainerFile()->getAllEntries()) {	if (umapEntryIndices[pEntry] != uiValue1)	vecEntries.push_back(pEntry);		Events::triggerDefault(TASK_PROGRESS); }
			break;
		case 2: // Between
			for (FormatEntry *pEntry : getContainerFile()->getAllEntries()) {	if (umapEntryIndices[pEntry] >= uiValue1 && umapEntryIndices[pEntry] <= uiValue2)	vecEntries.push_back(pEntry);	Events::triggerDefault(TASK_PROGRESS); }
			break;
		case 3: // Less than
			for (FormatEntry *pEntry : getContainerFile()->getAllEntries()) {	if (umapEntryIndices[pEntry] < uiValue1)	vecEntries.push_back(pEntry);		Events::triggerDefault(TASK_PROGRESS); }
			break;
		case 4: // More than
			for (FormatEntry *pEntry : getContainerFile()->getAllEntries()) {	if (umapEntryIndices[pEntry] > uiValue1)	vecEntries.push_back(pEntry);		Events::triggerDefault(TASK_PROGRESS); }
			break;
		case 5: // Less than or equal to
			for (FormatEntry *pEntry : getContainerFile()->getAllEntries()) {	if (umapEntryIndices[pEntry] <= uiValue1)	vecEntries.push_back(pEntry);		Events::triggerDefault(TASK_PROGRESS); }
			break;
		case 6: // More than or equal to
			for (FormatEntry *pEntry : getContainerFile()->getAllEntries()) {	if (umapEntryIndices[pEntry] >= uiValue1)	vecEntries.push_back(pEntry);		Events::triggerDefault(TASK_PROGRESS); }
			break;
		}
		break;
		}
	case 1: // Name
		break;
	case 2: // Offset
		switch (uiMatchType)
		{
		case 0: // Equal to
			for (FormatEntry *pEntry : getContainerFile()->getAllEntries()) {	if (pEntry->getEntryOffset() == uiValue1)	vecEntries.push_back(pEntry);		Events::triggerDefault(TASK_PROGRESS); }
			break;
		case 1: // Not equal to
			for (FormatEntry *pEntry : getContainerFile()->getAllEntries()) {	if (pEntry->getEntryOffset() != uiValue1)	vecEntries.push_back(pEntry);		Events::triggerDefault(TASK_PROGRESS); }
			break;
		case 2: // Between
			for (FormatEntry *pEntry : getContainerFile()->getAllEntries()) {	if (pEntry->getEntryOffset() >= uiValue1 && pEntry->getEntryOffset() <= uiValue2)	vecEntries.push_back(pEntry);		Events::triggerDefault(TASK_PROGRESS); }
			break;
		case 3: // Less than
			for (FormatEntry *pEntry : getContainerFile()->getAllEntries()) {	if (pEntry->getEntryOffset() < uiValue1)	vecEntries.push_back(pEntry);		Events::triggerDefault(TASK_PROGRESS); }
			break;
		case 4: // More than
			for (FormatEntry *pEntry : getContainerFile()->getAllEntries()) {	if (pEntry->getEntryOffset() > uiValue1)	vecEntries.push_back(pEntry);		Events::triggerDefault(TASK_PROGRESS); }
			break;
		case 5: // Less than or equal to
			for (FormatEntry *pEntry : getContainerFile()->getAllEntries()) {	if (pEntry->getEntryOffset() <= uiValue1)	vecEntries.push_back(pEntry);		Events::triggerDefault(TASK_PROGRESS); }
			break;
		case 6: // More than or equal to
			for (FormatEntry *pEntry : getContainerFile()->getAllEntries()) {	if (pEntry->getEntryOffset() >= uiValue1)	vecEntries.push_back(pEntry);		Events::triggerDefault(TASK_PROGRESS); }
			break;
		}
		break;
	case 3: // Size
		switch (uiMatchType)
		{
		case 0: // Equal to
			for (FormatEntry *pEntry : getContainerFile()->getAllEntries()) {	if (pEntry->getEntrySize() == uiValue1)		vecEntries.push_back(pEntry);		Events::triggerDefault(TASK_PROGRESS); }
			break;
		case 1: // Not equal to
			for (FormatEntry *pEntry : getContainerFile()->getAllEntries()) {	if (pEntry->getEntrySize() != uiValue1)		vecEntries.push_back(pEntry);		Events::triggerDefault(TASK_PROGRESS); }
			break;
		case 2: // Between
			for (FormatEntry *pEntry : getContainerFile()->getAllEntries()) {	if (pEntry->getEntrySize() >= uiValue1 && pEntry->getEntrySize() <= uiValue2)	vecEntries.push_back(pEntry);		Events::triggerDefault(TASK_PROGRESS); }
			break;
		case 3: // Less than
			for (FormatEntry *pEntry : getContainerFile()->getAllEntries()) {	if (pEntry->getEntrySize() < uiValue1)		vecEntries.push_back(pEntry);		Events::triggerDefault(TASK_PROGRESS); }
			break;
		case 4: // More than
			for (FormatEntry *pEntry : getContainerFile()->getAllEntries()) {	if (pEntry->getEntrySize() > uiValue1)		vecEntries.push_back(pEntry);		Events::triggerDefault(TASK_PROGRESS); }
			break;
		case 5: // Less than or equal to
			for (FormatEntry *pEntry : getContainerFile()->getAllEntries()) {	if (pEntry->getEntrySize() <= uiValue1)		vecEntries.push_back(pEntry);		Events::triggerDefault(TASK_PROGRESS); }
			break;
		case 6: // More than or equal to
			for (FormatEntry *pEntry : getContainerFile()->getAllEntries()) {	if (pEntry->getEntrySize() >= uiValue1)		vecEntries.push_back(pEntry);		Events::triggerDefault(TASK_PROGRESS); }
			break;
		}
		break;
	case 4: // Type
		break;
	case 5: // Version
		switch (uiMatchType)
		{
		case 0: // Equal to
			for (FormatEntry *pEntry : getContainerFile()->getAllEntries()) {	if (pEntry->getRawVersion() == uiValue1)	vecEntries.push_back(pEntry);		Events::triggerDefault(TASK_PROGRESS); }
			break;
		case 1: // Not equal to
			for (FormatEntry *pEntry : getContainerFile()->getAllEntries()) {	if (pEntry->getRawVersion() != uiValue1)	vecEntries.push_back(pEntry);		Events::triggerDefault(TASK_PROGRESS); }
			break;
		case 2: // Between
			for (FormatEntry *pEntry : getContainerFile()->getAllEntries()) {	if (pEntry->getRawVersion() >= uiValue1 && pEntry->getRawVersion() <= uiValue2)	vecEntries.push_back(pEntry);		Events::triggerDefault(TASK_PROGRESS); }
			break;
		case 3: // Less than
			for (FormatEntry *pEntry : getContainerFile()->getAllEntries()) {	if (pEntry->getRawVersion() < uiValue1)		vecEntries.push_back(pEntry);		Events::triggerDefault(TASK_PROGRESS); }
			break;
		case 4: // More than
			for (FormatEntry *pEntry : getContainerFile()->getAllEntries()) {	if (pEntry->getRawVersion() > uiValue1)		vecEntries.push_back(pEntry);		Events::triggerDefault(TASK_PROGRESS); }
			break;
		case 5: // Less than or equal to
			for (FormatEntry *pEntry : getContainerFile()->getAllEntries()) {	if (pEntry->getRawVersion() <= uiValue1)	vecEntries.push_back(pEntry);		Events::triggerDefault(TASK_PROGRESS); }
			break;
		case 6: // More than or equal to
			for (FormatEntry *pEntry : getContainerFile()->getAllEntries()) {	if (pEntry->getRawVersion() >= uiValue1)	vecEntries.push_back(pEntry);		Events::triggerDefault(TASK_PROGRESS); }
			break;
		}
		break;
	}
	return vecEntries;
}

vector<FormatEntry*>			EditorTab::getEntriesByStringMultiOptionValues(uint32 uiEntryAttribute, uint32 uiMatchType, string& strValue1, string& strValue2, bool bMatchWildcard)
{
	vector<FormatEntry*>
		vecEntries;
	string
		strValue1Lower = String::toLowerCase(strValue1),
		strValue2Lower = String::toLowerCase(strValue2);
	switch (uiEntryAttribute)
	{
	case 1: // Name
		if (bMatchWildcard)
		{
			// Wildcard
			switch (uiMatchType)
			{
			case 0: // Equal to
				for (FormatEntry *pEntry : getContainerFile()->getAllEntries()) {	if (String::isIn(String::toLowerCase(pEntry->getEntryName()), strValue1Lower))		vecEntries.push_back(pEntry);		Events::triggerDefault(TASK_PROGRESS); }
				break;
			case 1: // Not equal to
				for (FormatEntry *pEntry : getContainerFile()->getAllEntries()) {	if (String::isIn(String::toLowerCase(pEntry->getEntryName()), strValue1Lower))		vecEntries.push_back(pEntry);		Events::triggerDefault(TASK_PROGRESS); }
				break;
			case 2: // Between
				for (FormatEntry *pEntry : getContainerFile()->getAllEntries()) {	if (String::isIn(String::toLowerCase(pEntry->getEntryName()), strValue1Lower) && String::isIn(String::toLowerCase(pEntry->getEntryName()), strValue2Lower))	vecEntries.push_back(pEntry);		Events::triggerDefault(TASK_PROGRESS); }
				break;
			case 3: // Less than
				for (FormatEntry *pEntry : getContainerFile()->getAllEntries()) {	if (String::isIn(String::toLowerCase(pEntry->getEntryName()), strValue1Lower))		vecEntries.push_back(pEntry);		Events::triggerDefault(TASK_PROGRESS); }
				break;
			case 4: // More than
				for (FormatEntry *pEntry : getContainerFile()->getAllEntries()) {	if (String::isIn(String::toLowerCase(pEntry->getEntryName()), strValue1Lower))		vecEntries.push_back(pEntry);		Events::triggerDefault(TASK_PROGRESS); }
				break;
			case 5: // Less than or equal to
				for (FormatEntry *pEntry : getContainerFile()->getAllEntries()) {	if (String::isIn(String::toLowerCase(pEntry->getEntryName()), strValue1Lower))		vecEntries.push_back(pEntry);		Events::triggerDefault(TASK_PROGRESS); }
				break;
			case 6: // More than or equal to
				for (FormatEntry *pEntry : getContainerFile()->getAllEntries()) {	if (String::isIn(String::toLowerCase(pEntry->getEntryName()), strValue1Lower))		vecEntries.push_back(pEntry);		Events::triggerDefault(TASK_PROGRESS); }
				break;
			}
		}
		else
		{
			// Not Wildcard
			switch (uiMatchType)
			{
			case 0: // Equal to
				for (FormatEntry *pEntry : getContainerFile()->getAllEntries()) {	if (String::toLowerCase(pEntry->getEntryName()) == strValue1Lower)		vecEntries.push_back(pEntry);		Events::triggerDefault(TASK_PROGRESS); }
				break;
			case 1: // Not equal to
				for (FormatEntry *pEntry : getContainerFile()->getAllEntries()) {	if (String::toLowerCase(pEntry->getEntryName()) != strValue1Lower)		vecEntries.push_back(pEntry);		Events::triggerDefault(TASK_PROGRESS); }
				break;
			case 2: // Between
				for (FormatEntry *pEntry : getContainerFile()->getAllEntries()) {	if (String::toLowerCase(pEntry->getEntryName()) >= strValue1Lower && String::toLowerCase(pEntry->getEntryName()) <= strValue2Lower)	vecEntries.push_back(pEntry);		Events::triggerDefault(TASK_PROGRESS); }
				break;
			case 3: // Less than
				for (FormatEntry *pEntry : getContainerFile()->getAllEntries()) {	if (String::toLowerCase(pEntry->getEntryName()) < strValue1Lower)		vecEntries.push_back(pEntry);		Events::triggerDefault(TASK_PROGRESS); }
				break;
			case 4: // More than
				for (FormatEntry *pEntry : getContainerFile()->getAllEntries()) {	if (String::toLowerCase(pEntry->getEntryName()) > strValue1Lower)		vecEntries.push_back(pEntry);		Events::triggerDefault(TASK_PROGRESS); }
				break;
			case 5: // Less than or equal to
				for (FormatEntry *pEntry : getContainerFile()->getAllEntries()) {	if (String::toLowerCase(pEntry->getEntryName()) <= strValue1Lower)		vecEntries.push_back(pEntry);		Events::triggerDefault(TASK_PROGRESS); }
				break;
			case 6: // More than or equal to
				for (FormatEntry *pEntry : getContainerFile()->getAllEntries()) {	if (String::toLowerCase(pEntry->getEntryName()) >= strValue1Lower)		vecEntries.push_back(pEntry);		Events::triggerDefault(TASK_PROGRESS); }
				break;
			}
		}
		break;
	case 4: // Type
		if (bMatchWildcard)
		{
			// Wildcard
			switch (uiMatchType)
			{
			case 0: // Equal to
				for (FormatEntry *pEntry : getContainerFile()->getAllEntries()) {	if (String::isIn(String::toLowerCase(pEntry->getEntryExtension()), strValue1Lower))		vecEntries.push_back(pEntry);		Events::triggerDefault(TASK_PROGRESS); }
				break;
			case 1: // Not equal to
				for (FormatEntry *pEntry : getContainerFile()->getAllEntries()) {	if (String::isIn(String::toLowerCase(pEntry->getEntryExtension()), strValue1Lower))		vecEntries.push_back(pEntry);		Events::triggerDefault(TASK_PROGRESS); }
				break;
			case 2: // Between
				for (FormatEntry *pEntry : getContainerFile()->getAllEntries()) {	if (String::isIn(String::toLowerCase(pEntry->getEntryExtension()), strValue1Lower) && String::isIn(String::toLowerCase(pEntry->getEntryExtension()), strValue2Lower))		vecEntries.push_back(pEntry);		Events::triggerDefault(TASK_PROGRESS); }
				break;
			case 3: // Less than
				for (FormatEntry *pEntry : getContainerFile()->getAllEntries()) {	if (String::isIn(String::toLowerCase(pEntry->getEntryExtension()), strValue1Lower))		vecEntries.push_back(pEntry);		Events::triggerDefault(TASK_PROGRESS); }
				break;
			case 4: // More than
				for (FormatEntry *pEntry : getContainerFile()->getAllEntries()) {	if (String::isIn(String::toLowerCase(pEntry->getEntryExtension()), strValue1Lower))		vecEntries.push_back(pEntry);		Events::triggerDefault(TASK_PROGRESS); }
				break;
			case 5: // Less than or equal to
				for (FormatEntry *pEntry : getContainerFile()->getAllEntries()) {	if (String::isIn(String::toLowerCase(pEntry->getEntryExtension()), strValue1Lower))		vecEntries.push_back(pEntry);		Events::triggerDefault(TASK_PROGRESS); }
				break;
			case 6: // More than or equal to
				for (FormatEntry *pEntry : getContainerFile()->getAllEntries()) {	if (String::isIn(String::toLowerCase(pEntry->getEntryExtension()), strValue1Lower))		vecEntries.push_back(pEntry);		Events::triggerDefault(TASK_PROGRESS); }
				break;
			}
		}
		else
		{
			// Not Wildcard
			switch (uiMatchType)
			{
			case 0: // Equal to
				for (FormatEntry *pEntry : getContainerFile()->getAllEntries()) {	if (String::toLowerCase(pEntry->getEntryExtension()) == strValue1Lower)		vecEntries.push_back(pEntry);		Events::triggerDefault(TASK_PROGRESS); }
				break;
			case 1: // Not equal to
				for (FormatEntry *pEntry : getContainerFile()->getAllEntries()) {	if (String::toLowerCase(pEntry->getEntryExtension()) != strValue1Lower)		vecEntries.push_back(pEntry);		Events::triggerDefault(TASK_PROGRESS); }
				break;
			case 2: // Between
				for (FormatEntry *pEntry : getContainerFile()->getAllEntries()) {	if (String::toLowerCase(pEntry->getEntryExtension()) >= strValue1Lower && String::toLowerCase(pEntry->getEntryExtension()) <= strValue2Lower)		vecEntries.push_back(pEntry);		Events::triggerDefault(TASK_PROGRESS); }
				break;
			case 3: // Less than
				for (FormatEntry *pEntry : getContainerFile()->getAllEntries()) {	if (String::toLowerCase(pEntry->getEntryExtension()) < strValue1Lower)		vecEntries.push_back(pEntry);		Events::triggerDefault(TASK_PROGRESS); }
				break;
			case 4: // More than
				for (FormatEntry *pEntry : getContainerFile()->getAllEntries()) {	if (String::toLowerCase(pEntry->getEntryExtension()) > strValue1Lower)		vecEntries.push_back(pEntry);		Events::triggerDefault(TASK_PROGRESS); }
				break;
			case 5: // Less than or equal to
				for (FormatEntry *pEntry : getContainerFile()->getAllEntries()) {	if (String::toLowerCase(pEntry->getEntryExtension()) <= strValue1Lower)		vecEntries.push_back(pEntry);		Events::triggerDefault(TASK_PROGRESS); }
				break;
			case 6: // More than or equal to
				for (FormatEntry *pEntry : getContainerFile()->getAllEntries()) {	if (String::toLowerCase(pEntry->getEntryExtension()) >= strValue1Lower)		vecEntries.push_back(pEntry);		Events::triggerDefault(TASK_PROGRESS); }
				break;
			}
		}
		break;
	}
	return vecEntries;
}

// drag drop
void								EditorTab::startDragDrop(EditorTab *pEditorTab, string strFileExtension)
{
	MainWindow *pMainWindow = (MainWindow*)getLayer()->getWindow();
	pMainWindow->m_bDragDropOutIsOccurring = true;

	vector<string>
		vecFileNames,
		vecFileDatas;
	uint32
		uiDragDropEntryCount = getSelectedEntryCount(),
		i = 0;

	vecFileNames.resize(uiDragDropEntryCount);
	vecFileDatas.resize(uiDragDropEntryCount);

	for (FormatEntry *pEntry : getSelectedEntries())
	{
		vecFileNames[i] = pEntry->getEntryName();
		vecFileDatas[i] = pEntry->getEntryData();

		if (strFileExtension != "")
		{
			vecFileNames[i] += "." + strFileExtension;
		}

		i++;
	}

	EditorTab::startDragDrop2(pEditorTab, vecFileNames, vecFileDatas);

	pMainWindow->m_bDragDropOutIsOccurring = false;
}

void								EditorTab::startDragDrop2(EditorTab *pEditorTab, vector<string>& vecFileNames, vector<string>& vecFileDatas)
{
	HRESULT hr = OleInitialize(NULL);

	IDataObject		*pDataObject;
	IDropSource		*pDropSource;
	DWORD			dwEffect;
	HRESULT			iResult;

	// prepare data
	uint32 uiDragDropEntryCount = vecFileNames.size();

	// create FORMATETC
	FORMATETC *fmtetc = new FORMATETC[uiDragDropEntryCount + 1];
	fmtetc[0] = { (CLIPFORMAT)RegisterClipboardFormat(CFSTR_FILEDESCRIPTOR), NULL, DVASPECT_CONTENT, -1, TYMED_HGLOBAL };
	for (uint32 i = 0; i < uiDragDropEntryCount; i++)
	{
		fmtetc[i + 1] = { (CLIPFORMAT)RegisterClipboardFormat(CFSTR_FILECONTENTS), NULL, DVASPECT_CONTENT, (LONG)i + 1, TYMED_HGLOBAL };
	}

	// create file data into HGLOBAL
	HGLOBAL *hgblFileDatas = new HGLOBAL[uiDragDropEntryCount];
	for (uint32 i = 0; i < uiDragDropEntryCount; i++)
	{
		string strFileData = vecFileDatas[i];

		hgblFileDatas[i] = GlobalAlloc(GMEM_FIXED | GMEM_ZEROINIT, strFileData.length());
		LPSTR lpszFileData = (LPSTR)GlobalLock(hgblFileDatas[i]);
		memcpy(lpszFileData, strFileData.c_str(), strFileData.length());
		GlobalUnlock(hgblFileDatas[i]);
	}

	// create file description into HGLOBAL
	HGLOBAL hgblDescriptorData = GlobalAlloc(GMEM_FIXED | GMEM_ZEROINIT, sizeof(FILEGROUPDESCRIPTOR) + (sizeof(FILEDESCRIPTOR) * (uiDragDropEntryCount - 1)));
	FILEGROUPDESCRIPTOR *pfgd = (FILEGROUPDESCRIPTOR*)GlobalLock(hgblDescriptorData);
	pfgd->cItems = uiDragDropEntryCount;
	for (uint32 i = 0; i < uiDragDropEntryCount; i++)
	{
		string strFileName = vecFileNames[i];

		pfgd->fgd[i].dwFlags = FD_ATTRIBUTES | FD_FILESIZE | FD_PROGRESSUI;
		pfgd->fgd[i].dwFileAttributes = FILE_ATTRIBUTE_NORMAL;
		pfgd->fgd[i].nFileSizeHigh = 0;
		pfgd->fgd[i].nFileSizeLow = GlobalSize(hgblFileDatas[i]);
		lstrcpyn(pfgd->fgd[i].cFileName, String::convertStdStringToStdWString(strFileName).c_str(), sizeof(pfgd->fgd[i].cFileName));
	}
	GlobalUnlock(hgblDescriptorData);

	// create STGMEDIUM
	STGMEDIUM *stgmed = new STGMEDIUM[uiDragDropEntryCount + 1];

	memset((void far *)(&(stgmed[0])), 0, sizeof(stgmed[0]));
	stgmed[0].tymed = TYMED_HGLOBAL;
	stgmed[0].hGlobal = hgblDescriptorData;
	stgmed[0].pUnkForRelease = NULL;

	for (uint32 i = 0; i < uiDragDropEntryCount; i++)
	{
		memset((void far *)(&(stgmed[i + 1])), 0, sizeof(stgmed[i + 1]));
		stgmed[i + 1].tymed = TYMED_HGLOBAL;
		stgmed[i + 1].hGlobal = hgblFileDatas[i];
		stgmed[i + 1].pUnkForRelease = NULL;
	}

	pDropSource = new DropSource;

	if (CreateDataObject(fmtetc, stgmed, uiDragDropEntryCount + 1, &pDataObject) != S_OK)
	{
		return;
	}

	((DataObject*)pDataObject)->m_pEditorTab = pEditorTab;

	iResult = DoDragDrop(pDataObject, pDropSource, DROPEFFECT_COPY | DROPEFFECT_MOVE, &dwEffect);

	if (iResult == DRAGDROP_S_DROP)
	{
		if (dwEffect & DROPEFFECT_MOVE)
		{
			// move
		}
		else if (dwEffect & DROPEFFECT_COPY)
		{
			// copy
		}
	}
	else if (iResult == DRAGDROP_S_CANCEL)
	{
		// cancelled
	}
	else
	{
		// error
	}

	pDataObject->Release();
	pDropSource->Release();
}