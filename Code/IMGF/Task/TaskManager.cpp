#include "TaskManager.h"
#include "nsbxcf.h"
#include "nsbxgx.h"
#include "Task/Tasks/Tasks.h"
#include "Task/Duration/TaskDurationManager.h"
#include "Static/String.h"
#include "Static/Path.h"
#include "Static/File.h"
#include "Static/StdVector.h"
#include "Settings/SettingsManager.h"
#include "GUI/Window/WindowManager.h"
#include "GUI/Window/Windows/MainWindow/MainWindow.h"
#include "GUI/Layer/Layers/MainLayer/MainLayer.h"
#include "GUI/Layer/Layers/MainLayer/MainLayerNoTabsOpen.h"
#include "GUI/Editor/Editors/IMGEditor.h"
#include "Control/Controls/ProgressBar.h"
#include "GUI/Input/EInputItem.h"
#include "Task/Task.h"
#include "IMGF.h"

using namespace std;
using namespace bxcf;
using namespace bxgx;
using namespace imgf;
using namespace imgf::mainLayer::input;

// constructor/destructor
TaskManager::TaskManager(void) :
	m_uiTaskProgressTickCount(0),
	m_uiTaskMaxProgressTickCount(0)
{
	m_pTasks = new Tasks;
	m_pTaskDurationManager = new TaskDurationManager;
}

TaskManager::~TaskManager(void)
{
	delete m_pTasks;
}

// initialization
void							TaskManager::init(void)
{
	m_pTasks->init();

	addTask(NEW_FILE, "New File", &Tasks::newFile);
	addTask(NEW_WINDOW, "New Window", &Tasks::newWindow);

	addTask(OPEN_FILES, "Open Files", &Tasks::chooseFilesToOpen);
	addTask(OPEN_FOLDER, "Open Folder", &Tasks::chooseFolderToOpen);
	addTask(OPEN_FOLDER_RECURSIVELY, "Open Folder Recursively", &Tasks::openFolderRecursively);
	addTask(REOPEN_FILE, "Reopen", &Tasks::reopenFile);
	addTask(OPEN_LAST_CLOSED_FILE, "Open Last Closed File", &Tasks::openLastClosedFile);
	addTask(OPEN_FILE_FOLDER_IN_EXPLORER, "Open File Folder in Explorer", &Tasks::openFileFolderInExplorer);
	addTask(CLEAR_RECENTLY_OPEN_FILES, "Clear Recently Open Files", &Tasks::clearRecentlyOpenFiles);
	addTask(OPEN_TODAYS_LOGS_FILE, "Open Today's Logs File", &Tasks::openTodaysLogsFile);
	addTask(OPEN_LOGS_FOLDER, "Open Logs Folder", &Tasks::openLogsFolder);

	addTask(SAVE_FILE, "Save File", &Tasks::_saveFile);
	addTask(SAVE_FILE_AS, "Save File As", &Tasks::saveFileAs);
	addTask(SAVE_ALL_FILES, "Save All Files", &Tasks::saveAllFiles);
	addTask(CLONE_FILE, "Clone File", &Tasks::cloneFile);
	addTask(SAVE_FILE_GROUP, "Save File Group", &Tasks::saveFileGroup);
	addTask(SAVE_LOGS, "Save Logs", &Tasks::saveLogs);
	addTask(SAVE_LOGS_ALL_TABS, "Save Logs All Tabs", &Tasks::saveLogsAllTabs);
	addTask(CLEAR_LOGS, "Clear Logs", &Tasks::clearLogs);
	addTask(CLEAR_LOGS_ALL_TABS, "Clear Logs All Tabs", &Tasks::clearLogsAllTabs);

	addTask(CLOSE_FILE, "Close File", &Tasks::closeFile);
	addTask(CLOSE_ALL_FILES, "Close All Files", &Tasks::closeAllFiles);
	addTask(EXIT_TOOL, "Exit Tool", &Tasks::exitTool);

	addTask(IMPORT_BY_FILES, "Import by Files", &Tasks::importByFiles);
	addTask(IMPORT_BY_SINGLE_FOLDER, "Import by Single Folder", &Tasks::importBySingleFolder);
	addTask(IMPORT_BY_FOLDER_RECURSIVELY, "Import by Single Folder", &Tasks::importByFolderRecursively);
	addTask(IMPORT_BY_IDE, "Import by IDE", &Tasks::importByIDE);
	addTask(IMPORT_BY_ENTRY_NAMES, "Import by Entry Names", &Tasks::importByEntryNames);
	
	addTask(EXPORT_SELECTED, "Export Selected", &Tasks::importByEntryNames);
	addTask(EXPORT_ALL, "Export All", &Tasks::importByEntryNames);
	addTask(EXPORT_BY_INDEX, "Export by Index", &Tasks::importByEntryNames);
	addTask(EXPORT_BY_NAME, "Export by Name", &Tasks::importByEntryNames);
	addTask(EXPORT_BY_OFFSET, "Export by Offset", &Tasks::importByEntryNames);
	addTask(EXPORT_BY_SIZE, "Export by Size", &Tasks::importByEntryNames);
	addTask(EXPORT_BY_TYPE, "Export by Type", &Tasks::importByEntryNames);
	addTask(EXPORT_BY_VERSION, "Export by Version", &Tasks::importByEntryNames);
	addTask(EXPORT_ALL_INTO_GROUPED_FOLDERS_BY_TYPE, "Export All Entries into Grouped Folders by Type", &Tasks::importByEntryNames);
	addTask(EXPORT_ALL_FROM_ALL_TABS, "Export All Entries from All Tabs", &Tasks::importByEntryNames);
	addTask(EXPORT_ALL_FROM_ALL_TABS_INTO_GROUPED_FOLDERS_BY_TYPE, "Export All Entries from All Tabs into Grouped Folders by Type", &Tasks::importByEntryNames);
	addTask(EXPORT_SELECTION_FROM_ALL_TABS, "Selection from All Tabs", &Tasks::importByEntryNames);
	addTask(EXPORT_BY_IDE, "Export by IDE", &Tasks::importByEntryNames);
	addTask(EXPORT_BY_IDE_FROM_ALL_TABS, "Export by IDE from All Tabs", &Tasks::importByEntryNames);
	addTask(EXPORT_BY_IPL, "Export by IPL", &Tasks::importByEntryNames);
	addTask(EXPORT_BY_DAT, "Export by DA", &Tasks::importByEntryNames);
	addTask(EXPORT_BY_ENTRY_NAMES, "Export by Entry Names", &Tasks::importByEntryNames);
	addTask(EXPORT_BY_ENTRY_NAMES_FROM_ALL_TABS, "Export by Entry Names from All Tabs", &Tasks::importByEntryNames);

	addTask(QUICK_EXPORT, "Quick Export", &Tasks::quickExport);

	addTask(RENAME, "Rename", &Tasks::rename);

	addTask(REPLACE_BY_FILES, "Replace by Files", &Tasks::replaceByFiles);
	addTask(REPLACE_BY_SINGLE_FOLDER, "Replace by Single Folder", &Tasks::replaceBySingleFolder);
	addTask(REPLACE_BY_FOLDER_RECURSIVELY, "Replace by Folder Recursively", &Tasks::replaceByFolderRecursively);
	addTask(REPLACE_BY_IDE, "Replace by IDE", &Tasks::replaceByIDE);

	addTask(REMOVE_SELECTED, "Remove Selected", &Tasks::removeSelected);
	addTask(REMOVE_ALL, "Remove All", &Tasks::removeAll);
	addTask(REMOVE_BY_INDEX, "Remove by Index", &Tasks::removeByIndex);
	addTask(REMOVE_BY_NAME, "Remove by Name", &Tasks::removeByName);
	addTask(REMOVE_BY_OFFSET, "Remove by Offset", &Tasks::removeByOffset);
	addTask(REMOVE_BY_SIZE, "Remove by Size", &Tasks::removeBySize);
	addTask(REMOVE_BY_TYPE, "Remove by Type", &Tasks::removeByType);
	addTask(REMOVE_BY_VERSION, "Remove by Version", &Tasks::removeByVersion);
	addTask(REMOVE_BY_IDE, "Remove by IDE", &Tasks::removeByIDE);
	addTask(REMOVE_BY_ENTRY_NAMES, "Remove by Entry Names", &Tasks::removeByEntryNames);

	addTask(MERGE, "Merge", &Tasks::merge);

	addTask(SPLIT_SELECTED, "Split Selected", &Tasks::splitSelected);
	addTask(SPLIT_BY_IDE, "Split by IDE", &Tasks::splitByIDE);
	addTask(SPLIT_BY_ENTRY_NAMES, "Split by Entry Names", &Tasks::splitByEntryNames);

	addTask(CONVERT_IMG_VERSION, "Convert IMG Version", &Tasks::convertIMGVersion);
	addTask(CONVERT_SELECTED_COL_VERSION, "Convert Selected COL Version", &Tasks::convertSelectedCOLVersion);
	addTask(CONVERT_SELECTED_DFF_RW_VERSION, "Convert Selected DFF RW Version", &Tasks::convertSelectedDFFRWVersion);
	addTask(CONVERT_SELECTED_DFF_TO_WDR, "Convert Selected DFF to WDR", &Tasks::convertSelectedDFFToWDR);
	addTask(CONVERT_SELECTED_TXD_RW_VERSION, "Convert Selected TXD RW Version", &Tasks::convertSelectedTXDRWVersion);
	addTask(CONVERT_SELECTED_TXD_TO_GAME, "Convert Selected TXD to Game", &Tasks::convertSelectedTXDToGame);
	addTask(CONVERT_SELECTED_TXD_TO_TEXTURE_FORMAT, "Convert Selected TXD to Texture Format", &Tasks::convertSelectedTXDToTextureFormat);
	addTask(CONVERT_SELECTED_WTD_TO_TXD, "Convert Selected WTD to TXD", &Tasks::convertWTDFileToTXDFile);

	addTask(SELECT_ALL, "Select All", &Tasks::selectAll);
	addTask(UNSELECT_ALL, "Unselect All", &Tasks::unselectAll);
	addTask(SELECT_INVERSE, "Select Inverse", &Tasks::selectInverse);
	addTask(SELECT_BY_INDEX, "Select by Index", &Tasks::selectByIndex);
	addTask(SELECT_BY_NAME, "Select by Name", &Tasks::selectByName);
	addTask(SELECT_BY_OFFSET, "Select by Offset", &Tasks::selectByOffset);
	addTask(SELECT_BY_SIZE, "Select by Size", &Tasks::selectBySize);
	addTask(SELECT_BY_TYPE, "Select by Type", &Tasks::selectByType);
	addTask(SELECT_BY_VERSION, "Select by Version", &Tasks::selectByVersion);
	addTask(SELECT_BY_IDE, "Select by IDE", &Tasks::selectByIDE);
	addTask(UNSELECT_BY_INDEX, "Unselect by Index", &Tasks::unselectByIndex);
	addTask(UNSELECT_BY_NAME, "Unselect by Name", &Tasks::unselectByName);
	addTask(UNSELECT_BY_OFFSET, "Unselect by Offset", &Tasks::unselectByOffset);
	addTask(UNSELECT_BY_SIZE, "Unselect by Size", &Tasks::unselectBySize);
	addTask(UNSELECT_BY_TYPE, "Unselect by Type", &Tasks::unselectByType);
	addTask(UNSELECT_BY_VERSION, "Unselect by Version", &Tasks::unselectByVersion);
	addTask(UNSELECT_BY_IDE, "Unselect by IDE", &Tasks::unselectByIDE);

	addTask(SORT_BY_INDEX_REVERSE, "Sort by Index Reverse", &Tasks::sortByIndexReverse);
	addTask(SORT_BY_NAME_ASCENDING_09AZ, "Sort by Name Ascending 09-AZ", &Tasks::sortByNameAscending09AZ);
	addTask(SORT_BY_NAME_DESCENDING_ZA90, "Sort by Name Decending ZA-90", &Tasks::sortByNameDescendingZA90);
	addTask(SORT_BY_OFFSET_LOW_HIGH, "Sort by Offset Low-High", &Tasks::sortByOffsetLowHigh);
	addTask(SORT_BY_OFFSET_HIGH_LOW, "Sort by Offset High-Low", &Tasks::sortByOffsetHighLow);
	addTask(SORT_BY_SIZE_SMALL_BIG, "Sort by Size Small-Big", &Tasks::sortBySizeSmallBig);
	addTask(SORT_BY_SIZE_BIG_SMALL, "Sort by Size Big-Small", &Tasks::sortBySizeBigSmall);
	addTask(SORT_BY_TYPE_AZ, "Sort by Type A-Z", &Tasks::sortByTypeAZ);
	addTask(SORT_BY_TYPE_ZA, "Sort by Type Z-A", &Tasks::sortByTypeZA);
	addTask(SORT_BY_VERSION_OLD_NEW, "Sort by Version Old-New", &Tasks::sortByVersionOldNew);
	addTask(SORT_BY_VERSION_NEW_OLD, "Sort by Version New-Old", &Tasks::sortByVersionNewOld);

	addTask(LST, "LST", &Tasks::lst);

	addTask(NAME_CASE_LOWER, "Name Case Lower", &Tasks::nameCaseUpper);
	addTask(NAME_CASE_UPPER, "Name Case Upper", &Tasks::nameCaseLower);
	addTask(NAME_CASE_TITLE, "Name Case Title", &Tasks::nameCaseTitle);
	addTask(COPY_ENTRY_INDEX, "Copy Entry Index", &Tasks::copyEntryIndex);
	addTask(COPY_ENTRY_TYPE, "Copy Entry Type", &Tasks::copyEntryType);
	addTask(COPY_ENTRY_NAME, "Copy Entry Name", &Tasks::copyEntryName);
	addTask(COPY_ENTRY_OFFSET, "Copy Entry Offse", &Tasks::copyEntryOffset);
	addTask(COPY_ENTRY_SIZE, "Copy Entry Size", &Tasks::copyEntrySize);
	addTask(COPY_ENTRY_VERSION, "Copy Entry Version", &Tasks::copyEntryVersion);
	addTask(COPY_ENTRY_ROW_DATA, "Copy Entry Row Data", &Tasks::copyEntryRowData);

	addTask(SHIFT_ENTRY_UP_1_ROW, "Shift Entry Up 1 Row", &Tasks::shiftEntryUp1Row);
	addTask(SHIFT_ENTRY_UP_5_ROWS, "Shift Entry Up 5 Rows", &Tasks::shiftEntryUp5Rows);
	addTask(SHIFT_ENTRY_UP_10_ROWS, "Shift Entry Up 10 Rows", &Tasks::shiftEntryUp10Rows);
	addTask(SHIFT_ENTRY_UP_100_ROWS, "Shift Entry Up 100 Rows", &Tasks::shiftEntryUp100Rows);
	addTask(SHIFT_ENTRY_UP_1000_ROWS, "Shift Entry Up 1000 Rows", &Tasks::shiftEntryUp1000Rows);
	addTask(SHIFT_ENTRY_DOWN_1_ROW, "Shift Entry Down 1 Row", &Tasks::shiftEntryDown1Row);
	addTask(SHIFT_ENTRY_DOWN_5_ROWS, "Shift Entry Down 5 Rows", &Tasks::shiftEntryDown5Rows);
	addTask(SHIFT_ENTRY_DOWN_10_ROWS, "Shift Entry Down 10 Rows", &Tasks::shiftEntryDown10Rows);
	addTask(SHIFT_ENTRY_DOWN_100_ROWS, "Shift Entry Down 100 Rows", &Tasks::shiftEntryDown100Rows);
	addTask(SHIFT_ENTRY_DOWN_1000_ROWS, "Shift Entry Down 1000 Rows", &Tasks::shiftEntryDown1000Rows);

	addTask(REMOVE_ORPHAN_TEXTURES_FROM_DFF_ENTRIES, "Remove Orphan Textures from DFF Entries", &Tasks::removeOrphanTexturesFromDFFEntries);
	addTask(FIND_ORPHAN_IMG_ENTRIES_NOT_IN_IDE, "Find Orphan IMG Entries not in IDE", &Tasks::findOrphanIMGEntriesNotInIDE);
	addTask(FIND_ORPHAN_IDE_ENTRIES_NOT_IN_IMG, "Find Orphan IDE Entries not in IMG", &Tasks::findOrphanIDEEntriesNotInIMG);
	addTask(FIND_ORPHAN_TXD_TEXTURES_FOR_DFFS_IN_IMG_BY_IDE, "Find rphan TXD Textures for DFFs in IMG by IDE", &Tasks::findOrphanTXDTexturesForDFFsInIMGByIDE);

	addTask(DUMP, "Dump", &Tasks::dump);
	addTask(SESSION_MANAGER, "Session Manager", &Tasks::sessionManager);
	addTask(RENAMER, "Renamer", &Tasks::renamer);
	addTask(TXD_BUILDER, "TXD Builder", &Tasks::txdBuilder);
	addTask(TXD_ORGANIZER, "TXD Organizer", &Tasks::txdOrganizer);
	addTask(DAT_PATHS_MOVER, "DAT Paths Mover", &Tasks::datPathsMover);
	addTask(MAP_MOVER_AND_ID_SHIFTER, "Map Mover and ID Shifter", &Tasks::mapMoverAndIDShifter);

	addTask(TEXTURE_LIST, "Texture List", &Tasks::textureList);
	addTask(STATS, "Stats", &Tasks::stats);
	addTask(FIND_DUPLICATE_ENTRIES_IN_SELECTION, "Find Duplicate Entries in Selection", &Tasks::findDuplicateEntriesInSelection);
	addTask(FIND_DUPLICATE_ENTRIES_IN_TAB, "Find Duplicate Entries in Active Tab", &Tasks::findDuplicateEntriesInTab);
	addTask(FIND_DUPLICATE_ENTRIES_IN_ALL_TABS, "Find Duplicate Entries in All Tabs", &Tasks::findDuplicateEntriesInAllTabs);
	addTask(FIND_DUPLICATE_ENTRIES_BY_DAT, "Find Duplicate Entries by DAT", &Tasks::findDuplicateEntriesByDAT);
	addTask(COMPARE_IMGS, "Compare IMGs", &Tasks::compareIMGs);
	addTask(MODEL_LIST_FOR_IDE_AND_IPL_BY_DAT, "Model List for IDE and IPL by DAT", &Tasks::modelListForIDEAndIPLByDAT);
	addTask(SAVE_IMG_SIGNATURE, "Save IMG Signature", &Tasks::saveIMGSignature);
	addTask(VERIFY_IMG_SIGNATURE, "Verify IMG Signature", &Tasks::verifyIMGSignature);
	addTask(VALIDATE_DFF_IN_TAB, "Validate DFF in Active Tab", &Tasks::validateDFFInTab);
	addTask(VALIDATE_TXD_IN_TAB, "Validate TXD in Active Tab", &Tasks::validateTXDInTab);
	addTask(CENTER_COL_MESHES_IN_SELECTION, "Center COL Meshes in Selection", &Tasks::centerCOLMeshesInSelection);
	addTask(ALIGN_COL_MESHES_TO_DFF_MESHES, "Align COL Meshes to DFF Meshes", &Tasks::alignCOLMeshesToDFFMeshes);
	addTask(EXTRACT_DVC_AND_NVC_INTO_DFFS, "Extract DVC and NVC into DFFs", &Tasks::extractDVCAndNVCIntoDFFs);
	addTask(EXTRACT_2DFX_INTO_DFFS, "Extract 2DFX into DFFs", &Tasks::extract2DFXIntoDFFs);
	addTask(IMG_COMPRESSION, "IMG Compression", &Tasks::imgCompression);
}

void							TaskManager::uninit(void)
{
	m_pTasks->uninit();
}

// task start/stop
void							TaskManager::onStartTask(string strTaskName)
{
	m_vecActiveTaskNames.push_back(strTaskName);
	m_pTaskDurationManager->onStartTask(strTaskName);
}

void							TaskManager::onCompleteTask(void)
{
	string& strTaskName = m_vecActiveTaskNames[m_vecActiveTaskNames.size() - 1];

	// task duration
	m_pTaskDurationManager->onCompleteTask(strTaskName);

	// rebuild after task
	string strSaveAfterTasks = getIMGF()->getSettingsManager()->getSetting("SaveAfterTasks");
	vector<string> vecSaveAfterTasks = String::split(strSaveAfterTasks, ",");
	if (std::find(vecSaveAfterTasks.begin(), vecSaveAfterTasks.end(), strTaskName) != vecSaveAfterTasks.end())
	{
		getIMGF()->getTaskManager()->getDispatch()->_saveFile();
	}

	// clean up
	m_vecActiveTaskNames.pop_back();
}

void							TaskManager::onAbortTask(void)
{
	string& strTaskName = m_vecActiveTaskNames[m_vecActiveTaskNames.size() - 1];

	// task duration
	m_pTaskDurationManager->onAbortTask(strTaskName);

	// clean up
	m_vecActiveTaskNames.pop_back();
}

// task pause/resume
void							TaskManager::onPauseTask(void)
{
	m_pTaskDurationManager->onPauseTask();
}

void							TaskManager::onResumeTask(void)
{
	m_pTaskDurationManager->onResumeTask();
}

// active tasks
string&							TaskManager::getTaskName(void)
{
	if (m_vecActiveTaskNames.size() == 0)
	{
		return bxcf::g_strBlankString;
	}
	else
	{
		return m_vecActiveTaskNames[m_vecActiveTaskNames.size() - 1];
	}
}

// task progress
void							TaskManager::onTaskProgressTick(void)
{
	//setTaskProgressTickCount(getTaskProgressTickCount() + 1);

	ProgressBar *pProgressBar;
	if (getIMGF()->getWindowManager()->getMainWindow()->getActiveEditor()->getActiveEditorTab())
	{
		pProgressBar = getIMGF()->getWindowManager()->getMainWindow()->getActiveEditor()->getActiveEditorTab()->getProgressBar();
	}
	else
	{
		pProgressBar = getIMGF()->getWindowManager()->getMainWindow()->getMainLayerNoTabsOpen()->getProgressBar();
	}
	pProgressBar->increaseCurrent();
}

void							TaskManager::onTaskProgressComplete(void)
{
	setTaskProgressTickCount(getTaskProgressTickCount() + 1);

	/*
	todo
	ProgressBarCtrl *pProgressCtrl = (ProgressBarCtrl*)getDialog()->GetDlgItem(60);
	pProgressCtrl->SetPos(getProgressTicks());
	*/
}

void							TaskManager::setTaskMaxProgressTickCount(uint32 uiProgressMaxTicks, bool bResetCurrent)
{
	if (bResetCurrent)
	{
		setTaskProgressTickCount(0);
	}
	m_uiTaskMaxProgressTickCount = uiProgressMaxTicks;

	ProgressBar *pProgressBar;
	if (getIMGF()->getWindowManager()->getMainWindow()->getIMGEditor()->getActiveTab())
	{
		pProgressBar = getIMGF()->getWindowManager()->getMainWindow()->getIMGEditor()->getActiveTab()->getProgressBar();
	}
	else
	{
		pProgressBar = getIMGF()->getWindowManager()->getMainWindow()->getMainLayerNoTabsOpen()->getProgressBar();
	}
	pProgressBar->setMax(uiProgressMaxTicks, bResetCurrent);

	/*
	todo
	ProgressBarCtrl *pProgressCtrl = (ProgressBarCtrl*)getDialog()->GetDlgItem(60);
	pProgressCtrl->SetRange(0, (short)m_uiProgressMaxTicks);
	if (bReset)
	{
	pProgressCtrl->SetPos(0);
	}
	*/
}

// add task
Task*							TaskManager::addTask(EInputItem uiTaskId, string strTaskName, void(imgf::Tasks::* pTaskFunction)(void))
{
	Task *pTask = new Task;
	pTask->m_uiTaskId = uiTaskId;
	pTask->m_strTaskName = strTaskName;
	pTask->m_pTaskFunction = pTaskFunction;
	addEntry(pTask);
	return pTask;
}

// task names
vector<string>					TaskManager::getTaskNames(void)
{
	vector<string> vecTaskNames;
	vecTaskNames.resize(getEntryCount());
	uint32 i = 0;
	for (Task *pTask : getEntries())
	{
		vecTaskNames[i++] = pTask->getTaskName();
	}
	return vecTaskNames;
}