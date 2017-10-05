#include "InputManager.h"
#include "GUI/Input/EInputItem.h"
#include "Control/Controls/Button.h"
#include "Control/Controls/TextBox.h"
#include "Control/Controls/Grid.h"
#include "Control/Entries/MenuItem.h"
#include "Globals.h"
#include "IMGF.h"
#include "GUI/Window/WindowManager.h"
#include "GUI/Window/Windows/MainWindow/MainWindow.h"
#include "GUI/Layer/Layers/ELayer.h"
#include "GUI/Layer/Layers/MainMenu/EMainMenuType.h"
#include "Task/TaskManager.h"
#include "Task/Tasks/Tasks.h"
#include "Task/Tasks/RecentlyOpen/RecentlyOpenManager.h"
#include "Task/Tasks/Session/SessionManager.h"
#include "GUI/Editor/Editors/IMGEditor.h"
#include "Static/String.h"
#include "Event/EInternalEvent.h"
#include "Static/Path.h"

using namespace std;
using namespace bxcf;
using namespace bxgx;
using namespace bxgx::events;
using namespace imgf;
using namespace imgf::layers;
using namespace imgf::mainLayer::input;
using namespace imgf::mainLayer::mainMenuType;

// main interface
void					InputManager::init(void)
{
	m_pMainWindow = g_pIMGF->getWindowManager()->getMainWindow();
	m_pTasks = g_pIMGF->getTaskManager()->getDispatch();

	bindEvents();
}

// bind events
void					InputManager::bindEvents(void)
{
	bindEvent(KEY_DOWN, &InputManager::onKeyDown);
	bindEvent(KEY_CHAR, &InputManager::onCharDown);
	bindEvent(MOUSE_ENTER_ITEM, &InputManager::onMouseEnterItem);
	bindEvent(MOUSE_EXIT_ITEM, &InputManager::onMouseExitItem);

	bindEvent(PRESS_BUTTON, &InputManager::onPressButton);
	bindEvent(PRESS_MENU_ITEM, &InputManager::onPressMenuItem);
	bindEvent(DROP_FILES, &InputManager::onDropFiles);
}

// key down
void					InputManager::onKeyDown(uint16 uiKey)
{
	IMGEditorTab *pEditorTab = (IMGEditorTab*)m_pMainWindow->getIMGEditor()->getActiveFile();
	if (pEditorTab && m_pMainWindow->getActiveItem() == (LayerItem*)pEditorTab->getEntryGrid())
	{
		if (uiKey == VK_DELETE && pEditorTab->getEntryGrid()->isAnyRowSelected())
		{
			m_pTasks->removeSelected();
		}
		else if (!(uiKey >= 37 && uiKey <= 40) && (String::isAsciiCharacterDisplayable((uint8)uiKey) || uiKey == VK_BACK || uiKey == VK_DELETE))
		{
			pEditorTab->getSearchBox()->onKeyDown(uiKey);
		}
	}
}

// char down
void					InputManager::onCharDown(uint16 uiKey)
{
	IMGEditorTab *pEditorTab = (IMGEditorTab*)m_pMainWindow->getIMGEditor()->getActiveFile();
	if (pEditorTab && m_pMainWindow->getActiveItem() == (LayerItem*)pEditorTab->getEntryGrid() && String::isAsciiCharacterDisplayable((uint8)uiKey))
	{
		pEditorTab->getSearchBox()->onCharDown(uiKey);
	}
}

// mouse enter item
void					InputManager::onMouseEnterItem(RenderItem *pRenderItem)
{
	Button *pSettingsButton = (Button*)m_pMainWindow->getItemById(SETTINGS);
	Layer *pLayer = m_pMainWindow->getLayerById(ELayer::SETTINGS_MENU);
	if (pSettingsButton == pRenderItem)
	{
		pLayer->setEnabled(true);
	}
}

// mouse exit item
void					InputManager::onMouseExitItem(RenderItem *pRenderItem)
{
	Button *pSettingsButton = (Button*)m_pMainWindow->getItemById(SETTINGS);
	Layer *pLayer = m_pMainWindow->getLayerById(ELayer::SETTINGS_MENU);
	Menu *pMenu = (Menu*)m_pMainWindow->getItemById(EInputItem::SETTINGS_MENU);
	Vec2i& vecCursorPoint = BXGX::get()->getCursorPosition();

	if (pRenderItem == pSettingsButton)
	{
		if (!pMenu || !pMenu->isPointInBoundingRectangle(vecCursorPoint, 0))
		{
			pLayer->setEnabled(false);
		}
	}
	else if (pRenderItem == pMenu)
	{
		if (!pSettingsButton->isPointInItem(vecCursorPoint))
		{
			pLayer->setEnabled(false);
		}
	}
}

// forward button press
void					InputManager::onPressButton(Button *pButton)
{
	switch (pButton->getId())
	{
	}
}

// forward button press
void					InputManager::onPressMenuItem(MenuItem *pMenuItem)
{
	EditorTab *pActiveEditorTab = m_pMainWindow->getIMGEditor()->getActiveFile();

	uint32 uiMenuItemId = pMenuItem->getId();
	if (uiMenuItemId == -1 && pMenuItem->getExpandableMenu() && pMenuItem->getExpandableMenu()->getEntryCount() > 0)
	{
		uiMenuItemId = pMenuItem->getExpandableMenu()->getFirstEntry()->getId();
	}

	if (pActiveEditorTab && uiMenuItemId != CLOSE_FILE && uiMenuItemId != CLOSE_ALL_FILES)
	{
		pActiveEditorTab->getMenuItemsPressed().push_back(pMenuItem);
	}
	else
	{
		processMenuItemPress(pMenuItem);
	}
}

void					InputManager::onDropFiles(vector<string> vecDroppedFilePaths)
{
	IMGEditorTab *pActiveEditorTab = m_pMainWindow->getIMGEditor()->getActiveTab();
	for (string& strDroppedFilePath : vecDroppedFilePaths)
	{
		if (IMGF::isFileExtensionOpenable(Path::getFileExtension(strDroppedFilePath)))
		{
			m_pTasks->_openFile(strDroppedFilePath);
		}
		else
		{
			if (pActiveEditorTab)
			{
				pActiveEditorTab->addFile(strDroppedFilePath);
			}
		}
	}
}

void					InputManager::processMenuItemPress(MenuItem *pMenuItem)
{
	// recently open
	if (getIMGF()->getRecentlyOpenManager()->getRecentlyOpenedFilesContainer().find(pMenuItem->getId()) != getIMGF()->getRecentlyOpenManager()->getRecentlyOpenedFilesContainer().end())
	{
		string strRecentlyOpenFilePath = getIMGF()->getRecentlyOpenManager()->getRecentlyOpenedFilesContainer()[pMenuItem->getId()];
		getIMGF()->getRecentlyOpenManager()->moveRecentlyOpenEntryToTop(strRecentlyOpenFilePath);
		getIMGF()->getIMGEditor()->addFile(strRecentlyOpenFilePath);
		return;
	}

	// file group
	if (getIMGF()->getSessionManager()->getSessionsContainer().find(pMenuItem->getId()) != getIMGF()->getSessionManager()->getSessionsContainer().end())
	{
		string strFileGroupData = getIMGF()->getSessionManager()->getSessionsContainer()[pMenuItem->getId()];
		vector<string> vecFileGroupData = String::split(strFileGroupData, "; ");
		for (uint32 i = 1, j = vecFileGroupData.size(); i < j; i++)
		{
			getIMGF()->getIMGEditor()->addFile(vecFileGroupData[i]);
		}
		return;
	}

	uint32 uiMenuItemId;

	if (pMenuItem->getExpandableMenu() && pMenuItem->getExpandableMenu()->getEntryCount() > 0)
	{
		// menu item with an expandable menu - choose first item in expandable item list
		uiMenuItemId = pMenuItem->getExpandableMenu()->getFirstEntry()->getId();
	}
	else
	{
		// menu item with no expandable menu
		uiMenuItemId = pMenuItem->getId();
	}

	// main
	switch (uiMenuItemId)
	{
	case EInputItem::FORMATS:						return formats();
	case EInputItem::UTILITY:						return utility();

	case DAT:										return dat();
	case IMG:										return img();
	case ITEM_DEFINITION:							return itemDefinition();
	case ITEM_PLACEMENT:							return itemPlacement();
	case MODELS:									return models();
	case COLLISIONS:								return collisions();
	case TEXTURES:									return textures();
	case ANIMATIONS:								return animations();
	case RADAR:										return radar();

	case NEW_FILE:									return newFile();
	case NEW_WINDOW:								return newWindow();

	case OPEN_FILES:								return openFiles();
	case OPEN_FOLDER:								return openFolder();
	case OPEN_FOLDER_RECURSIVELY:					return openFolderRecursively();
	case REOPEN_FILE:								return reopenFile();
	case OPEN_LAST_CLOSED_FILE:						return openLastClosedFile();
	case OPEN_FILE_FOLDER_IN_EXPLORER:				return openFileFolderInExplorer();
	case CLEAR_RECENTLY_OPEN_FILES:					return clearRecentlyOpenFiles();
	case OPEN_TODAYS_LOGS_FILE:						return openTodaysLogsFile();
	case OPEN_LOGS_FOLDER:							return openLogsFolder();

	case CLOSE_FILE:								return closeFile();
	case CLOSE_ALL_FILES:							return closeAllFiles();
	case EXIT_TOOL:									return exitTool();

	case SAVE_FILE:									return saveFile();
	case SAVE_FILE_AS:								return saveFileAs();
	case SAVE_ALL_FILES:							return saveAllFiles();
	case CLONE_FILE:								return cloneFile();
	case SAVE_FILE_GROUP:							return saveFileGroup();
	case SAVE_LOGS:									return saveLogs();
	case SAVE_LOGS_ALL_TABS:						return saveLogsAllTabs();
	case CLEAR_LOGS:								return clearLogs();
	case CLEAR_LOGS_ALL_TABS:						return clearLogsAllTabs();

	case IMPORT_BY_FILES:							return importByFiles();
	case IMPORT_BY_SINGLE_FOLDER:					return importBySingleFolder();
	case IMPORT_BY_FOLDER_RECURSIVELY:				return importByFolderRecursively();
	case IMPORT_BY_IDE:								return importByIDE();
	case IMPORT_BY_ENTRY_NAMES:						return importByEntryNames();

	case EXPORT_SELECTED:							return exportSelected();
	case EXPORT_ALL:								return exportAll();
	case EXPORT_BY_INDEX:							return exportByIndex();
	case EXPORT_BY_NAME:							return exportByName();
	case EXPORT_BY_OFFSET:							return exportByOffset();
	case EXPORT_BY_SIZE:							return exportBySize();
	case EXPORT_BY_TYPE:							return exportByType();
	case EXPORT_BY_VERSION:							return exportByVersion();
	case EXPORT_ALL_INTO_GROUPED_FOLDERS_BY_TYPE:	return exportAllIntoGroupedFoldersByType();
	case EXPORT_ALL_FROM_ALL_TABS:					return exportAllFromAllTabs();
	case EXPORT_ALL_FROM_ALL_TABS_INTO_GROUPED_FOLDERS_BY_TYPE:		return exportAllFromAllTabsIntoGroupedFoldersByType();
	case EXPORT_SELECTION_FROM_ALL_TABS:			return exportSelectionFromAllTabs();
	case EXPORT_BY_IDE:								return exportByIDE();
	case EXPORT_BY_IDE_FROM_ALL_TABS:				return exportByIDEFromAllTabs();
	case EXPORT_BY_IPL:								return exportByIPL();
	case EXPORT_BY_DAT:								return exportByDAT();
	case EXPORT_BY_ENTRY_NAMES:						return exportByEntryNames();
	case EXPORT_BY_ENTRY_NAMES_FROM_ALL_TABS:		return exportByEntryNamesFromAllTabs();

	case QUICK_EXPORT:								return quickExport();

	case RENAME:									return rename();

	case REPLACE_BY_FILES:							return replaceByFiles();
	case REPLACE_BY_SINGLE_FOLDER:					return replaceBySingleFolder();
	case REPLACE_BY_FOLDER_RECURSIVELY:				return replaceByFolderRecursively();
	case REPLACE_BY_IDE:							return replaceByIDE();

	case REMOVE_SELECTED:							return removeSelected();
	case REMOVE_ALL:								return removeAll();
	case REMOVE_BY_INDEX:							return removeByIndex();
	case REMOVE_BY_NAME:							return removeByName();
	case REMOVE_BY_OFFSET:							return removeByOffset();
	case REMOVE_BY_SIZE:							return removeBySize();
	case REMOVE_BY_TYPE:							return removeByType();
	case REMOVE_BY_VERSION:							return removeByVersion();
	case REMOVE_BY_IDE:								return removeByIDE();
	case REMOVE_BY_ENTRY_NAMES:						return removeByEntryNames();

	case MERGE:										return merge();

	case SPLIT_SELECTED:							return splitSelected();
	case SPLIT_BY_IDE:								return splitByIDE();
	case SPLIT_BY_ENTRY_NAMES:						return splitByEntryNames();

	case CONVERT_IMG_VERSION:						return convertIMGVersion();
	case CONVERT_SELECTED_COL_VERSION:				return convertSelectedCOLVersion();
	case CONVERT_SELECTED_DFF_RW_VERSION:			return convertSelectedDFFRWVersion();
	case CONVERT_SELECTED_DFF_TO_WDR:				return convertSelectedDFFToWDR();
	case CONVERT_SELECTED_TXD_RW_VERSION:			return convertSelectedTXDRWVersion();
	case CONVERT_SELECTED_TXD_TO_GAME:				return convertSelectedTXDToGame();
	case CONVERT_SELECTED_TXD_TO_TEXTURE_FORMAT:	return convertSelectedTXDToTextureFormat();
	case CONVERT_SELECTED_WTD_TO_TXD:				return convertWTDFileToTXDFile();

	case SELECT_ALL:								return selectAll();
	case UNSELECT_ALL:								return unselectAll();
	case SELECT_INVERSE:							return selectInverse();
	case SELECT_BY_INDEX:							return selectByIndex();
	case SELECT_BY_NAME:							return selectByName();
	case SELECT_BY_OFFSET:							return selectByOffset();
	case SELECT_BY_SIZE:							return selectBySize();
	case SELECT_BY_TYPE:							return selectByType();
	case SELECT_BY_VERSION:							return selectByVersion();
	case SELECT_BY_IDE:								return selectByIDE();
	case UNSELECT_BY_INDEX:							return unselectByIndex();
	case UNSELECT_BY_NAME:							return unselectByName();
	case UNSELECT_BY_OFFSET:						return unselectByOffset();
	case UNSELECT_BY_SIZE:							return unselectBySize();
	case UNSELECT_BY_TYPE:							return unselectByType();
	case UNSELECT_BY_VERSION:						return unselectByVersion();
	case UNSELECT_BY_IDE:							return unselectByIDE();

	case SORT_BY_INDEX_REVERSE:						return sortByIndexReverse();
	case SORT_BY_NAME_ASCENDING_09AZ:				return sortByNameAscending09AZ();
	case SORT_BY_NAME_ASCENDING_AZ09:				return sortByNameAscendingAZ09();
	case SORT_BY_NAME_DESCENDING_ZA90:				return sortByNameDescendingZA90();
	case SORT_BY_NAME_DESCENDING_90ZA:				return sortByNameDescending90ZA();
	case SORT_BY_OFFSET_LOW_HIGH:					return sortByOffsetLowHigh();
	case SORT_BY_OFFSET_HIGH_LOW:					return sortByOffsetHighLow();
	case SORT_BY_SIZE_SMALL_BIG:					return sortBySizeSmallBig();
	case SORT_BY_SIZE_BIG_SMALL:					return sortBySizeBigSmall();
	case SORT_BY_TYPE_AZ:							return sortByTypeAZ();
	case SORT_BY_TYPE_ZA:							return sortByTypeZA();
	case SORT_BY_VERSION_OLD_NEW:					return sortByVersionOldNew();
	case SORT_BY_VERSION_NEW_OLD:					return sortByVersionNewOld();

	case LST:										return lst();

	case NAME_CASE_LOWER:							return nameCaseLower();
	case NAME_CASE_UPPER:							return nameCaseUpper();
	case NAME_CASE_TITLE:							return nameCaseTitle();

	case COPY_ENTRY_INDEX:							return copyEntryIndex();
	case COPY_ENTRY_TYPE:							return copyEntryType();
	case COPY_ENTRY_NAME:							return copyEntryName();
	case COPY_ENTRY_OFFSET:							return copyEntryOffset();
	case COPY_ENTRY_SIZE:							return copyEntrySize();
	case COPY_ENTRY_VERSION:						return copyEntryVersion();
	case COPY_ENTRY_ROW_DATA:						return copyEntryRowData();

	case SHIFT_ENTRY_UP_1_ROW:						return shiftEntryUp1Row();
	case SHIFT_ENTRY_UP_5_ROWS:						return shiftEntryUp5Rows();
	case SHIFT_ENTRY_UP_10_ROWS:					return shiftEntryUp10Rows();
	case SHIFT_ENTRY_UP_100_ROWS:					return shiftEntryUp100Rows();
	case SHIFT_ENTRY_UP_1000_ROWS:					return shiftEntryUp1000Rows();
	case SHIFT_ENTRY_DOWN_1_ROW:					return shiftEntryDown1Row();
	case SHIFT_ENTRY_DOWN_5_ROWS:					return shiftEntryDown5Rows();
	case SHIFT_ENTRY_DOWN_10_ROWS:					return shiftEntryDown10Rows();
	case SHIFT_ENTRY_DOWN_100_ROWS:					return shiftEntryDown100Rows();
	case SHIFT_ENTRY_DOWN_1000_ROWS:				return shiftEntryDown1000Rows();

	case REMOVE_ORPHAN_TEXTURES_FROM_DFF_ENTRIES:	return removeOrphanTexturesFromDFFEntries();
	case FIND_ORPHAN_IMG_ENTRIES_NOT_IN_IDE:		return findOrphanIMGEntriesNotInIDE();
	case FIND_ORPHAN_IDE_ENTRIES_NOT_IN_IMG:		return findOrphanIDEEntriesNotInIMG();
	case FIND_ORPHAN_TXD_TEXTURES_FOR_DFFS_IN_IMG_BY_IDE:	return findOrphanTXDTexturesForDFFsInIMGByIDE();

	case DUMP:										return dump();
	case SESSION_MANAGER:							return sessionManager();
	case RENAMER:									return renamer();
	case TXD_BUILDER:								return txdBuilder();
	case TXD_ORGANIZER:								return txdOrganizer();
	case DAT_PATHS_MOVER:							return datPathsMover();
	case MAP_MOVER_AND_ID_SHIFTER:					return mapMoverAndIdShifter();

	case TEXTURE_LIST:								return textureList();
	case STATS:										return stats();
	case FIND_DUPLICATE_ENTRIES_IN_SELECTION:		return findDuplicateEntriesInSelection();
	case FIND_DUPLICATE_ENTRIES_IN_TAB:				return findDuplicateEntriesInTab();
	case FIND_DUPLICATE_ENTRIES_IN_ALL_TABS:		return findDuplicateEntriesInAllTabs();
	case FIND_DUPLICATE_ENTRIES_BY_DAT:				return findDuplicateEntriesByDAT();
	case COMPARE_IMGS:								return compareIMGs();
	case MODEL_LIST_FOR_IDE_AND_IPL_BY_DAT:			return modelListForIDEAndIPLByDAT();
	case SAVE_IMG_SIGNATURE:						return saveIMGSignature();
	case VERIFY_IMG_SIGNATURE:						return verifyIMGSignature();
	case VALIDATE_DFF_IN_TAB:						return validateDFFInTab();
	case VALIDATE_TXD_IN_TAB:						return validateTXDInTab();
	case CENTER_COL_MESHES_IN_SELECTION:			return centerCOLMeshesInSelection();
	case ALIGN_COL_MESHES_TO_DFF_MESHES:			return alignCOLMeshesToDFFMeshes();
	case EXTRACT_DVC_AND_NVC_INTO_DFFS:				return extractDVCAndNVCIntoDFFs();
	case EXTRACT_2DFX_INTO_DFFS:					return extract2DFXIntoDFFs();
	case IMG_COMPRESSION:							return imgCompression();

	// top right menu
	case SETTINGS:									return settings();
	case WEBSITES:									return websites();
	case FORMATS2:									return formats2();
	case ABOUT:										return about();
	case UPDATE:									return update();
	}
}

// button press - menu type menu
void					InputManager::formats(void)
{
	m_pMainWindow->setMainMenuType(EMainMenuType::FORMATS);
}

void					InputManager::utility(void)
{
	m_pMainWindow->setMainMenuType(EMainMenuType::UTILITY);
}

// button press - format menu
void					InputManager::dat(void)
{
}

void					InputManager::img(void)
{
}

void					InputManager::itemDefinition(void)
{
}

void					InputManager::itemPlacement(void)
{
}

void					InputManager::models(void)
{
}

void					InputManager::collisions(void)
{
}

void					InputManager::textures(void)
{
}

void					InputManager::animations(void)
{
}

void					InputManager::radar(void)
{
}

// button press - file menu
// new
void					InputManager::newFile(void)
{
	m_pTasks->newFile();
}

void					InputManager::newWindow(void)
{
	m_pTasks->newWindow();
}

// open
void					InputManager::openFiles(void)
{
	m_pTasks->chooseFilesToOpen();
}

void					InputManager::openFolder(void)
{
	m_pTasks->chooseFolderToOpen();
}

void					InputManager::openFolderRecursively(void)
{
	m_pTasks->openFolderRecursively();
}

void					InputManager::reopenFile(void)
{
	m_pTasks->reopenFile();
}

void					InputManager::openLastClosedFile(void)
{
	m_pTasks->openLastClosedFile();
}

void					InputManager::openFileFolderInExplorer(void)
{
	m_pTasks->openFileFolderInExplorer();
}

void					InputManager::clearRecentlyOpenFiles(void)
{
	m_pTasks->clearRecentlyOpenFiles();
}

void					InputManager::openTodaysLogsFile(void)
{
	m_pTasks->openTodaysLogsFile();
}

void					InputManager::openLogsFolder(void)
{
	m_pTasks->openLogsFolder();
}

// save
void					InputManager::saveFile(void)
{
	m_pTasks->_saveFile();
}

void					InputManager::saveFileAs(void)
{
	m_pTasks->saveFileAs();
}

void					InputManager::saveAllFiles(void)
{
	m_pTasks->saveAllFiles();
}

void					InputManager::cloneFile(void)
{
	m_pTasks->cloneFile();
}

void					InputManager::saveFileGroup(void)
{
	m_pTasks->saveFileGroup();
}

void					InputManager::saveLogs(void)
{
	m_pTasks->saveLogs();
}

void					InputManager::saveLogsAllTabs(void)
{
	m_pTasks->saveLogsAllTabs();
}

void					InputManager::clearLogs(void)
{
	m_pTasks->clearLogs();
}

void					InputManager::clearLogsAllTabs(void)
{
	m_pTasks->clearLogsAllTabs();
}

// close
void					InputManager::closeFile(void)
{
	m_pTasks->closeFile();
}

void					InputManager::closeAllFiles(void)
{
	m_pTasks->closeAllFiles();
}

void					InputManager::exitTool(void)
{
	m_pTasks->exitTool();
}

// button press - action menu
// import
void					InputManager::importByFiles(void)
{
	m_pTasks->importByFiles();
}

void					InputManager::importBySingleFolder(void)
{
	m_pTasks->importBySingleFolder();
}

void					InputManager::importByFolderRecursively(void)
{
	m_pTasks->importByFolderRecursively();
}

void					InputManager::importByIDE(void)
{
	m_pTasks->importByIDE();
}

void					InputManager::importByEntryNames(void)
{
	m_pTasks->importByEntryNames();
}

// export
void					InputManager::exportSelected(void)
{
	m_pTasks->exportSelected();
}

void					InputManager::exportAll(void)
{
	m_pTasks->exportAll();
}

void					InputManager::exportByIndex(void)
{
	m_pTasks->exportByIndex();
}

void					InputManager::exportByName(void)
{
	m_pTasks->exportByName();
}

void					InputManager::exportByOffset(void)
{
	m_pTasks->exportByOffset();
}

void					InputManager::exportBySize(void)
{
	m_pTasks->exportBySize();
}

void					InputManager::exportByType(void)
{
	m_pTasks->exportByType();
}

void					InputManager::exportByVersion(void)
{
	m_pTasks->exportByVersion();
}

void					InputManager::exportAllIntoGroupedFoldersByType(void)
{
	m_pTasks->exportAllIntoGroupedFoldersByType();
}

void					InputManager::exportAllFromAllTabs(void)
{
	m_pTasks->exportAllFromAllTabs();
}

void					InputManager::exportAllFromAllTabsIntoGroupedFoldersByType(void)
{
	m_pTasks->exportAllFromAllTabsIntoGroupedFoldersByType();
}

void					InputManager::exportSelectionFromAllTabs(void)
{
	m_pTasks->exportSelectionFromAllTabs();
}

void					InputManager::exportByIDE(void)
{
	m_pTasks->exportByIDE();
}

void					InputManager::exportByIPL(void)
{
	m_pTasks->exportByIPL();
}

void					InputManager::exportByIDEFromAllTabs(void)
{
	m_pTasks->exportByIDEFromAllTabs();
}

void					InputManager::exportByDAT(void)
{
	m_pTasks->exportByDAT();
}

void					InputManager::exportByEntryNames(void)
{
	m_pTasks->exportByEntryNames();
}

void					InputManager::exportByEntryNamesFromAllTabs(void)
{
	m_pTasks->exportByEntryNamesFromAllTabs();
}

// quick export
void					InputManager::quickExport(void)
{
	m_pTasks->quickExport();
}

// rename
void					InputManager::rename(void)
{
	m_pTasks->rename();
}

// replace
void					InputManager::replaceByFiles(void)
{
	m_pTasks->replaceByFiles();
}

void					InputManager::replaceBySingleFolder(void)
{
	m_pTasks->replaceBySingleFolder();
}

void					InputManager::replaceByFolderRecursively(void)
{
	m_pTasks->replaceByFolderRecursively();
}

void					InputManager::replaceByIDE(void)
{
	m_pTasks->replaceByIDE();
}

// remove
void					InputManager::removeSelected(void)
{
	m_pTasks->removeSelected();
}

void					InputManager::removeAll(void)
{
	m_pTasks->removeAll();
}

void					InputManager::removeByIndex(void)
{
	m_pTasks->removeByIndex();
}

void					InputManager::removeByName(void)
{
	m_pTasks->removeByName();
}

void					InputManager::removeByOffset(void)
{
	m_pTasks->removeByOffset();
}

void					InputManager::removeBySize(void)
{
	m_pTasks->removeBySize();
}

void					InputManager::removeByType(void)
{
	m_pTasks->removeByType();
}

void					InputManager::removeByVersion(void)
{
	m_pTasks->removeByVersion();
}

void					InputManager::removeByIDE(void)
{
	m_pTasks->removeByIDE();
}

void					InputManager::removeByEntryNames(void)
{
	m_pTasks->removeByEntryNames();
}

// merge
void					InputManager::merge(void)
{
	m_pTasks->merge();
}

// split
void					InputManager::splitSelected(void)
{
	m_pTasks->splitSelected();
}

void					InputManager::splitByIDE(void)
{
	m_pTasks->splitByIDE();
}

void					InputManager::splitByEntryNames(void)
{
	m_pTasks->splitByEntryNames();
}

// convert
void					InputManager::convertIMGVersion(void)
{
	m_pTasks->convertIMGVersion();
}

void					InputManager::convertSelectedCOLVersion(void)
{
	m_pTasks->convertSelectedCOLVersion();
}

void					InputManager::convertSelectedDFFRWVersion(void)
{
	m_pTasks->convertSelectedDFFRWVersion();
}

void					InputManager::convertSelectedDFFToWDR(void)
{
	m_pTasks->convertSelectedDFFToWDR();
}

void					InputManager::convertSelectedTXDRWVersion(void)
{
	m_pTasks->convertSelectedTXDRWVersion();
}

void					InputManager::convertSelectedTXDToGame(void)
{
	m_pTasks->convertSelectedTXDToGame();
}

void					InputManager::convertSelectedTXDToTextureFormat(void)
{
	m_pTasks->convertSelectedTXDToTextureFormat();
}

void					InputManager::convertWTDFileToTXDFile(void)
{
	m_pTasks->convertWTDFileToTXDFile();
}

// select
void					InputManager::selectAll(void)
{
	m_pTasks->selectAll();
}

void					InputManager::unselectAll(void)
{
	m_pTasks->unselectAll();
}

void					InputManager::selectInverse(void)
{
	m_pTasks->selectInverse();
}

void					InputManager::selectByIndex(void)
{
	m_pTasks->selectByIndex();
}

void					InputManager::selectByName(void)
{
	m_pTasks->selectByName();
}

void					InputManager::selectByOffset(void)
{
	m_pTasks->selectByOffset();
}

void					InputManager::selectBySize(void)
{
	m_pTasks->selectBySize();
}

void					InputManager::selectByType(void)
{
	m_pTasks->selectByType();
}

void					InputManager::selectByVersion(void)
{
	m_pTasks->selectByVersion();
}

void					InputManager::selectByIDE(void)
{
	m_pTasks->selectByIDE();
}

void					InputManager::unselectByIndex(void)
{
	m_pTasks->unselectByIndex();
}

void					InputManager::unselectByName(void)
{
	m_pTasks->unselectByName();
}

void					InputManager::unselectByOffset(void)
{
	m_pTasks->unselectByOffset();
}

void					InputManager::unselectBySize(void)
{
	m_pTasks->unselectBySize();
}

void					InputManager::unselectByType(void)
{
	m_pTasks->unselectByType();
}

void					InputManager::unselectByVersion(void)
{
	m_pTasks->unselectByVersion();
}

void					InputManager::unselectByIDE(void)
{
	m_pTasks->unselectByIDE();
}

// sort
void					InputManager::sortByIndexReverse(void)
{
	m_pTasks->sortByIndexReverse();
}

void					InputManager::sortByNameAscending09AZ(void)
{
	m_pTasks->sortByNameAscending09AZ();
}

void					InputManager::sortByNameAscendingAZ09(void)
{
	m_pTasks->sortByNameAscendingAZ09();
}

void					InputManager::sortByNameDescendingZA90(void)
{
	m_pTasks->sortByNameDescendingZA90();
}

void					InputManager::sortByNameDescending90ZA(void)
{
	m_pTasks->sortByNameDescending90ZA();
}

void					InputManager::sortByOffsetLowHigh(void)
{
	m_pTasks->sortByOffsetLowHigh();
}

void					InputManager::sortByOffsetHighLow(void)
{
	m_pTasks->sortByOffsetHighLow();
}

void					InputManager::sortBySizeSmallBig(void)
{
	m_pTasks->sortBySizeSmallBig();
}

void					InputManager::sortBySizeBigSmall(void)
{
	m_pTasks->sortBySizeBigSmall();
}

void					InputManager::sortByTypeAZ(void)
{
	m_pTasks->sortByTypeAZ();
}

void					InputManager::sortByTypeZA(void)
{
	m_pTasks->sortByTypeZA();
}

void					InputManager::sortByVersionOldNew(void)
{
	m_pTasks->sortByVersionOldNew();
}

void					InputManager::sortByVersionNewOld(void)
{
	m_pTasks->sortByVersionNewOld();
}

// entry
void					InputManager::nameCaseLower(void)
{
	m_pTasks->nameCaseLower();
}

void					InputManager::nameCaseUpper(void)
{
	m_pTasks->nameCaseUpper();
}

void					InputManager::nameCaseTitle(void)
{
	m_pTasks->nameCaseTitle();
}


void					InputManager::copyEntryIndex(void)
{
	m_pTasks->copyEntryIndex();
}

void					InputManager::copyEntryType(void)
{
	m_pTasks->copyEntryType();
}

void					InputManager::copyEntryName(void)
{
	m_pTasks->copyEntryName();
}

void					InputManager::copyEntryOffset(void)
{
	m_pTasks->copyEntryOffset();
}

void					InputManager::copyEntrySize(void)
{
	m_pTasks->copyEntrySize();
}

void					InputManager::copyEntryVersion(void)
{
	m_pTasks->copyEntryVersion();
}

void					InputManager::copyEntryRowData(void)
{
	m_pTasks->copyEntryRowData();
}


void					InputManager::shiftEntryUp1Row(void)
{
	m_pTasks->shiftEntryUp1Row();
}

void					InputManager::shiftEntryUp5Rows(void)
{
	m_pTasks->shiftEntryUp5Rows();
}

void					InputManager::shiftEntryUp10Rows(void)
{
	m_pTasks->shiftEntryUp10Rows();
}

void					InputManager::shiftEntryUp100Rows(void)
{
	m_pTasks->shiftEntryUp100Rows();
}

void					InputManager::shiftEntryUp1000Rows(void)
{
	m_pTasks->shiftEntryUp1000Rows();
}

void					InputManager::shiftEntryDown1Row(void)
{
	m_pTasks->shiftEntryDown1Row();
}

void					InputManager::shiftEntryDown5Rows(void)
{
	m_pTasks->shiftEntryDown5Rows();
}

void					InputManager::shiftEntryDown10Rows(void)
{
	m_pTasks->shiftEntryDown10Rows();
}

void					InputManager::shiftEntryDown100Rows(void)
{
	m_pTasks->shiftEntryDown100Rows();
}

void					InputManager::shiftEntryDown1000Rows(void)
{
	m_pTasks->shiftEntryDown1000Rows();
}

// orphan entries
void					InputManager::removeOrphanTexturesFromDFFEntries(void)
{
	m_pTasks->removeOrphanTexturesFromDFFEntries();
}

void					InputManager::findOrphanIMGEntriesNotInIDE(void)
{
	m_pTasks->findOrphanIMGEntriesNotInIDE();
}

void					InputManager::findOrphanIDEEntriesNotInIMG(void)
{
	m_pTasks->findOrphanIDEEntriesNotInIMG();
}

void					InputManager::findOrphanTXDTexturesForDFFsInIMGByIDE(void)
{
	m_pTasks->findOrphanTXDTexturesForDFFsInIMGByIDE();
}

// tools
void					InputManager::dump(void)
{
	m_pTasks->dump();
}

void					InputManager::sessionManager(void)
{
	m_pTasks->sessionManager();
}

void					InputManager::renamer(void)
{
	m_pTasks->renamer();
}

void					InputManager::txdBuilder(void)
{
	m_pTasks->txdBuilder();
}

void					InputManager::txdOrganizer(void)
{
	m_pTasks->txdOrganizer();
}

void					InputManager::datPathsMover(void)
{
	m_pTasks->datPathsMover();
}

void					InputManager::mapMoverAndIdShifter(void)
{
	m_pTasks->mapMoverAndIdShifter();
}

// other
void					InputManager::textureList(void)
{
	m_pTasks->textureList();
}

void					InputManager::stats(void)
{
	m_pTasks->stats();
}

void					InputManager::findDuplicateEntriesInSelection(void)
{
	m_pTasks->findDuplicateEntriesInSelection();
}

void					InputManager::findDuplicateEntriesInTab(void)
{
	m_pTasks->findDuplicateEntriesInTab();
}

void					InputManager::findDuplicateEntriesInAllTabs(void)
{
	m_pTasks->findDuplicateEntriesInAllTabs();
}

void					InputManager::findDuplicateEntriesByDAT(void)
{
	m_pTasks->findDuplicateEntriesByDAT();
}

void					InputManager::compareIMGs(void)
{
	m_pTasks->compareIMGs();
}

void					InputManager::modelListForIDEAndIPLByDAT(void)
{
	m_pTasks->modelListForIDEAndIPLByDAT();
}

void					InputManager::saveIMGSignature(void)
{
	m_pTasks->saveIMGSignature();
}

void					InputManager::verifyIMGSignature(void)
{
	m_pTasks->verifyIMGSignature();
}

void					InputManager::validateDFFInTab(void)
{
	m_pTasks->validateDFFInTab();
}

void					InputManager::validateTXDInTab(void)
{
	m_pTasks->validateTXDInTab();
}

void					InputManager::centerCOLMeshesInSelection(void)
{
	m_pTasks->centerCOLMeshesInSelection();
}

void					InputManager::alignCOLMeshesToDFFMeshes(void)
{
	m_pTasks->alignCOLMeshesToDFFMeshes();
}

void					InputManager::extractDVCAndNVCIntoDFFs(void)
{
	m_pTasks->extractDVCAndNVCIntoDFFs();
}

void					InputManager::extract2DFXIntoDFFs(void)
{
	m_pTasks->extract2DFXIntoDFFs();
}

void					InputManager::imgCompression(void)
{
	m_pTasks->imgCompression();
}

// LST
void					InputManager::lst(void)
{
	m_pTasks->lst();
}

// button press - top right menu
// settings
void					InputManager::settingsMenu(void)
{
	Layer *pLayer = m_pMainWindow->getLayerById(ELayer::SETTINGS_MENU);
	pLayer->setEnabled(!pLayer->isEnabled());
}

// menu item press - top right menu
void					InputManager::settings(void)
{
	getIMGF()->getWindowManager()->showSettingsWindow();
}

void					InputManager::websites(void)
{
	getIMGF()->getWindowManager()->showWebsitesWindow();
}

void					InputManager::formats2(void)
{
	getIMGF()->getWindowManager()->showFormatsWindow();
}

void					InputManager::about(void)
{
	getIMGF()->getWindowManager()->showAboutWindow();
}

void					InputManager::update(void)
{
	m_pTasks->update(false);
}