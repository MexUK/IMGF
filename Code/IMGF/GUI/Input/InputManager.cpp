#include "InputManager.h"
#include "GUI/Input/EInputItem.h"
#include "Control/Controls/Button.h"
#include "Control/Entries/MenuItem.h"
#include "Globals.h"
#include "IMGF.h"
#include "GUI/Window/WindowManager.h"
#include "GUI/Window/Windows/MainWindow/MainWindow.h"
#include "GUI/Layer/Layers/ELayer.h"
#include "GUI/Layer/Layers/MainMenu/EMainMenuType.h"
#include "Task/TaskManager.h"
#include "Task/Tasks/Tasks.h"

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
	bindEvent(PRESS_BUTTON, &InputManager::onPressButton);
	bindEvent(PRESS_MENU_ITEM, &InputManager::onPressMenuItem);
}

// forward button press
void					InputManager::onPressButton(Button *pButton)
{
	switch (pButton->getId())
	{
	case SETTINGS:			return settings();
	}
}

// forward button press
void					InputManager::onPressMenuItem(MenuItem *pMenuItem)
{
	switch (pMenuItem->getId())
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

	case OPEN:										return open();
	case CLOSE:										return close();
	case SAVE:										return save();

	case IMPORT_BY_FILES:							return importByFiles();
	case IMPORT_BY_SINGLE_FOLDER:					return importBySingleFolder();
	case IMPORT_BY_FOLDER_RECURSIVELY:				return importByFolderRecursively();

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

	case MERGE:										return merge();
	case SPLIT:										return split();

	case CONVERT_IMG_VERSION:						return convertIMGVersion();

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
void					InputManager::open(void)
{
	m_pTasks->chooseFilesToOpen();
}

void					InputManager::close(void)
{
	m_pTasks->closeActiveFile();
}

void					InputManager::save(void)
{
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

// quick export
void					InputManager::quickExport(void)
{
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

// merge
void					InputManager::merge(void)
{
	m_pTasks->merge();
}

// split
void					InputManager::split(void)
{
	m_pTasks->split();
}

// convert
void					InputManager::convertIMGVersion(void)
{
	m_pTasks->convertIMGVersion();
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

// LST
void					InputManager::lst(void)
{
}

// button press - top right menu
// settings
void					InputManager::settings(void)
{
	Layer *pLayer = m_pMainWindow->getLayerById(SETTINGS_MENU);
	pLayer->setEnabled(!pLayer->isEnabled());
}