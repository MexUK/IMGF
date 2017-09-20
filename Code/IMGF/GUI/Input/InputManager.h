#pragma once

#include "nsimgf.h"
#include "nsbxcf.h"
#include "nsbxgx.h"
#include "Event/Events.h"

class bxgx::MenuItem;
class bxgx::Button;
class imgf::MainWindow;
class imgf::Tasks;

class imgf::InputManager : public bxcf::EventBindable
{
public:
	void					init(void);

private:
	void					bindEvents(void);

public:
	void					onPressButton(bxgx::Button *pMenuItem);
	void					onPressMenuItem(bxgx::MenuItem *pMenuItem);

private:
	void					formats(void);
	void					utility(void);

	void					dat(void);
	void					img(void);
	void					itemDefinition(void);
	void					itemPlacement(void);
	void					models(void);
	void					collisions(void);
	void					textures(void);
	void					animations(void);
	void					radar(void);

	void					newFile(void);
	void					newWindow(void);

	void					openFiles(void);
	void					openFolder(void);
	void					openFolderRecursively(void);
	void					reopenFile(void);
	void					openLastClosedFile(void);
	void					openFileFolderInExplorer(void);
	void					clearRecentlyOpenFiles(void);
	void					openTodaysLogsFile(void);
	void					openLogsFolder(void);

	void					saveFile(void);
	void					saveFileAs(void);
	void					saveAllFiles(void);
	void					cloneFile(void);
	void					saveFileGroup(void);
	void					saveLogs(void);
	void					saveLogsAllTabs(void);
	void					clearLogs(void);
	void					clearLogsAllTabs(void);

	void					closeFile(void);
	void					closeAllFiles(void);
	void					exitTool(void);

	void					importByFiles(void);
	void					importBySingleFolder(void);
	void					importByFolderRecursively(void);
	void					importByIDE(void);
	void					importByEntryNames(void);

	void					exportSelected(void);
	void					exportAll(void);
	void					exportByIndex(void);
	void					exportByName(void);
	void					exportByOffset(void);
	void					exportBySize(void);
	void					exportByType(void);
	void					exportByVersion(void);
	void					exportAllIntoGroupedFoldersByType(void);
	void					exportAllFromAllTabs(void);
	void					exportAllFromAllTabsIntoGroupedFoldersByType(void);
	void					exportSelectionFromAllTabs(void);
	void					exportByIDE(void);
	void					exportByIDEFromAllTabs(void);
	void					exportByIPL(void);
	void					exportByDAT(void);
	void					exportByEntryNames(void);
	void					exportByEntryNamesFromAllTabs(void);

	void					quickExport(void);
	
	void					rename(void);

	void					replaceByFiles(void);
	void					replaceBySingleFolder(void);
	void					replaceByFolderRecursively(void);
	void					replaceByIDE(void);

	void					removeSelected(void);
	void					removeAll(void);
	void					removeByIndex(void);
	void					removeByName(void);
	void					removeByOffset(void);
	void					removeBySize(void);
	void					removeByType(void);
	void					removeByVersion(void);
	void					removeByIDE(void);
	void					removeByEntryNames(void);

	void					merge(void);

	void					splitSelected(void);
	void					splitByIDE(void);
	void					splitByEntryNames(void);

	void					convertIMGVersion(void);
	void					convertSelectedCOLVersion(void);
	void					convertSelectedDFFRWVersion(void);
	void					convertSelectedDFFToWDR(void);
	void					convertSelectedTXDRWVersion(void);
	void					convertSelectedTXDToGame(void);
	void					convertSelectedTXDToTextureFormat(void);
	void					convertWTDFileToTXDFile(void);

	void					selectAll(void);
	void					unselectAll(void);
	void					selectInverse(void);
	void					selectByIndex(void);
	void					selectByName(void);
	void					selectByOffset(void);
	void					selectBySize(void);
	void					selectByType(void);
	void					selectByVersion(void);
	void					selectByIDE(void);
	void					unselectByIndex(void);
	void					unselectByName(void);
	void					unselectByOffset(void);
	void					unselectBySize(void);
	void					unselectByType(void);
	void					unselectByVersion(void);
	void					unselectByIDE(void);

	void					sortByIndexReverse(void);
	void					sortByNameAscending09AZ(void);
	void					sortByNameAscendingAZ09(void);
	void					sortByNameDescendingZA90(void);
	void					sortByNameDescending90ZA(void);
	void					sortByOffsetLowHigh(void);
	void					sortByOffsetHighLow(void);
	void					sortBySizeSmallBig(void);
	void					sortBySizeBigSmall(void);
	void					sortByTypeAZ(void);
	void					sortByTypeZA(void);
	void					sortByVersionOldNew(void);
	void					sortByVersionNewOld(void);

	void					nameCaseLower(void);
	void					nameCaseUpper(void);
	void					nameCaseTitle(void);

	void					copyEntryIndex(void);
	void					copyEntryType(void);
	void					copyEntryName(void);
	void					copyEntryOffset(void);
	void					copyEntrySize(void);
	void					copyEntryVersion(void);
	void					copyEntryRowData(void);

	void					shiftEntryUp1Row(void);
	void					shiftEntryUp5Rows(void);
	void					shiftEntryUp10Rows(void);
	void					shiftEntryUp100Rows(void);
	void					shiftEntryUp1000Rows(void);
	void					shiftEntryDown1Row(void);
	void					shiftEntryDown5Rows(void);
	void					shiftEntryDown10Rows(void);
	void					shiftEntryDown100Rows(void);
	void					shiftEntryDown1000Rows(void);

	void					removeOrphanTexturesFromDFFEntries(void);
	void					findOrphanIMGEntriesNotInIDE(void);
	void					findOrphanIDEEntriesNotInIMG(void);
	void					findOrphanTXDTexturesForDFFsInIMGByIDE(void);

	void					textureList(void);
	void					stats(void);

	void					lst(void);

	void					settingsMenu(void);

	void					settings(void);
	void					websites(void);
	void					formats2(void);
	void					about(void);

private:
	MainWindow*				m_pMainWindow;
	Tasks*					m_pTasks;
};