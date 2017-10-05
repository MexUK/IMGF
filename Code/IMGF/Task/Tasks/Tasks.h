#pragma once

#include "nsimgf.h"
#include "nsbxcf.h"
#include "Object/Manager.h"
#include "Format/IMG/Regular/EIMGEntryProperty.h"
#include "Game/EPlatformedGame.h"
#include "Event/EventBindable.h"
#include <string>
#include <vector>
#include <Windows.h>

class bxcf::RasterDataFormat;
class bxgi::RWVersion;
class bxgi::COLVersion;
struct imgf::RenamedIMGEntry;
class imgf::MainWindow;
class imgf::TaskManager;

class imgf::Tasks : public bxcf::Manager, public bxcf::EventBindable
{
public:
	Tasks(void);

	static uint32				showMessage(std::string strMessage, std::string strWindowTitle, uint32 uiButtons = MB_OKCANCEL);

private:
	std::string&				getTaskName(void);

	std::vector<std::string>	openFile(std::string strExtensionFilters = "", bool bAllowMultiSelect = true, std::string strDefaultFileName = "");
	std::string					saveFile(std::string strExtensionFilters = "", std::string strDefaultFileName = "");
	std::string					openFolder(std::string strTitle, std::string strInitialDir = "");
	std::string					saveFolder(std::string strTitle, std::string strInitialDir = "");
	
	void						onStartTask(std::string strTaskName);
	void						onCompleteTask(void);
	void						onAbortTask(void);
	void						onProgressTask(void);

	EditorTab*					getTab(void);
	IMGEditorTab*				getIMGTab(void);

	void						setMaxProgress(uint32 uiMaxProgress, bool bResetCurrent = true);
	void						increaseProgress(void);
	
public:
	void						init(void);
	void						uninit(void);

	void						newFile(void);
	void						newWindow(void);

	void						chooseFilesToOpen(void); // todo - different level function
	void						_openFile(std::string& strFilePath); // todo - rename to openFile eventually after IO windows renamed to showOpenFileWindow() etc
	void						chooseFolderToOpen(void); // todo - rename to openFolder eventually after IO windows renamed to showOpenFileWindow() etc
	void						openFolderRecursively(void);
	void						reopenFile(void);
	void						openLastClosedFile(void);
	void						openFileFolderInExplorer(void);
	void						clearRecentlyOpenFiles(void);
	void						openTodaysLogsFile(void);
	void						openLogsFolder(void);

	void						_saveFile(void); // todo - rename to saveFile eventually after IO windows renamed to showSaveFileWindow() etc
	void						saveFileAs(void);
	void						saveAllFiles(void);
	void						cloneFile(void);
	bool						saveAllOpenFiles(bool bCloseAll); // todo - remove parameter? // todo - different level function
	void						saveFileGroup(void);
	void						saveLogs(void);
	void						saveLogsAllTabs(void);
	void						clearLogs(void);
	void						clearLogsAllTabs(void);

	void						closeFile(void);
	void						closeAllFiles(void);
	void						exitTool(void);

	void						importByFiles(void);
	void						importBySingleFolder(void);
	void						importByFolderRecursively(void);
	void						importByIDE(void);
	void						importByEntryNames(void);

	void						exportSelected(void);
	void						exportAll(void);
	void						exportByIndex(void);
	void						exportByName(void);
	void						exportByOffset(void);
	void						exportBySize(void);
	void						exportByType(void);
	void						exportByVersion(void);
	void						exportAllIntoGroupedFoldersByType(void);
	void						exportAllFromAllTabs(void);
	void						exportAllFromAllTabsIntoGroupedFoldersByType(void);
	void						exportSelectionFromAllTabs(void);
	void						exportByIDE(void);
	void						exportByIDEFromAllTabs(void);
	void						exportByIPL(void);
	void						exportByDAT(void);
	void						exportByEntryNames(void);
	void						exportByEntryNamesFromAllTabs(void);

	void						quickExport(void);

	void						rename(void);

	void						replaceByFiles(void);
	void						replaceBySingleFolder(void);
	void						replaceByFolderRecursively(void);
	void						replaceByIDE(void);

	void						removeSelected(void);
	void						removeAll(void);
	void						removeByIndex(void);
	void						removeByName(void);
	void						removeByOffset(void);
	void						removeBySize(void);
	void						removeByType(void);
	void						removeByVersion(void);
	void						removeByIDE(void);
	void						removeByEntryNames(void);

	void						merge(void);

	void						splitSelected(void);
	void						splitByIDE(void);
	void						splitByEntryNames(void);

	void						convertIMGVersion(void);
	void						convertSelectedCOLVersion(void);
	void						convertSelectedDFFRWVersion(void);
	void						convertSelectedDFFToWDR(void);
	void						convertSelectedTXDRWVersion(void);
	void						convertSelectedTXDToGame(void);
	void						convertSelectedTXDToTextureFormat(void);
	void						convertWTDFileToTXDFile(void);

	void						selectAll(void);
	void						unselectAll(void);
	void						selectInverse(void);
	void						selectByIndex(void);
	void						selectByName(void);
	void						selectByOffset(void);
	void						selectBySize(void);
	void						selectByType(void);
	void						selectByVersion(void);
	void						selectByIDE(void);
	void						unselectByIndex(void);
	void						unselectByName(void);
	void						unselectByOffset(void);
	void						unselectBySize(void);
	void						unselectByType(void);
	void						unselectByVersion(void);
	void						unselectByIDE(void);

	void						sortByIndexReverse(void);
	void						sortByNameAscending09AZ(void);
	void						sortByNameAscendingAZ09(void);
	void						sortByNameDescendingZA90(void);
	void						sortByNameDescending90ZA(void);
	void						sortByOffsetLowHigh(void);
	void						sortByOffsetHighLow(void);
	void						sortBySizeSmallBig(void);
	void						sortBySizeBigSmall(void);
	void						sortByTypeAZ(void);
	void						sortByTypeZA(void);
	void						sortByVersionOldNew(void);
	void						sortByVersionNewOld(void);

	void						lst(void);

	void						nameCaseLower(void);
	void						nameCaseUpper(void);
	void						nameCaseTitle(void);

	void						copyEntryIndex(void);
	void						copyEntryType(void);
	void						copyEntryName(void);
	void						copyEntryOffset(void);
	void						copyEntrySize(void);
	void						copyEntryVersion(void);
	void						copyEntryRowData(void);

	void						shiftEntryUp1Row(void);
	void						shiftEntryUp5Rows(void);
	void						shiftEntryUp10Rows(void);
	void						shiftEntryUp100Rows(void);
	void						shiftEntryUp1000Rows(void);
	void						shiftEntryDown1Row(void);
	void						shiftEntryDown5Rows(void);
	void						shiftEntryDown10Rows(void);
	void						shiftEntryDown100Rows(void);
	void						shiftEntryDown1000Rows(void);

	void						removeOrphanTexturesFromDFFEntries(void);
	void						findOrphanIMGEntriesNotInIDE(void);
	void						findOrphanIDEEntriesNotInIMG(void);
	void						findOrphanTXDTexturesForDFFsInIMGByIDE(void);

	void						dump(void);
	void						sessionManager(void);
	void						renamer(void);
	void						txdBuilder(void);
	void						txdOrganizer(void);
	void						datPathsMover(void);
	void						mapMoverAndIdShifter(void);

	void						textureList(void);
	void						stats(void);
	void						findDuplicateEntriesInSelection(void);
	void						findDuplicateEntriesInTab(void);
	void						findDuplicateEntriesInAllTabs(void);
	void						findDuplicateEntriesByDAT(void);
	void						compareIMGs(void);
	void						modelListForIDEAndIPLByDAT(void);
	void						saveIMGSignature(void);
	void						verifyIMGSignature(void);
	void						validateDFFInTab(void);
	void						validateTXDInTab(void);
	void						centerCOLMeshesInSelection(void);
	void						alignCOLMeshesToDFFMeshes(void);
	void						extractDVCAndNVCIntoDFFs(void);
	void						extract2DFXIntoDFFs(void);
	void						imgCompression(void);
	void						update(void);
	void						associateIMGExtension(void);






	
	void						onRequestAutoUpdate(void);
	static int CALLBACK			sortMainListView(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort);
	void						onRequestFeatureByName(std::string strFeatureName);
	void						onRequestLastFeatureUsed(void);





	void						onRequestSessionManager(void);
	void						onRequestRenamer(void);
	void						onRequestBuildTXD(void);
	void						onRequestTXDOrganizer(void);
	void						onRequestDATPathsMover(void);
	void						onRequestMapMoverAndIDShifter(void);

private:
	MainWindow*					m_pMainWindow;
	TaskManager*				m_pTaskManager;
};