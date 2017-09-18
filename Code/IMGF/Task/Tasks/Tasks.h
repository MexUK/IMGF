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

	void						_saveFile(void); // todo - rename to saveFile eventually after IO windows renamed to showSaveFileWindow() etc
	void						saveFileAs(void);
	void						saveAllFiles(void);
	void						cloneFile(void);
	bool						saveAllOpenFiles(bool bCloseAll); // todo - remove parameter? // todo - different level function
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
	void						exportByDAT(void);

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

	void						merge(void);

	void						splitSelected(void);
	void						splitByIDE(void);

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
	











	
	void						onRequestSplitViaTextLines(void);
	void						onRequestExportViaTextLines(void);
	void						onRequestRemoveViaTextLines(void);
	void						onRequestImportViaTextLines(void);
	void						onRequestStats(void);
	void						onRequestQuickExport(void);
	void						onRequestVersion(void);
	void						onRequestTextureList(void);
	void						onRequestAssociateIMGExtension(void);
	
	void						onRequestSaveSession(void);
	void						onRequestOrphanIMGEntriesNotInIDE(void);
	void						onRequestOrphanIDEEntriesNotInIMG(void);
	void						onRequestSettings(void);
	
	void						onRequestMissingTextures(void);
	void						onRequestExportEntriesViaTextLinesFromAllTabs(void);
	void						onRequestDuplicateEntries(void);

	void						onRequestDump(void);
	void						onRequestSessionManager(void);
	void						onRequestWebsite(void);
	void						onRequestOpenLogBasic(void);
	void						onRequestOpenLogExtended(void);
	void						onRequestOpenLogFolder(void);
	void						onRequestExportViaIPLFile(void);
	void						onRequestUpdate(void);
	void						onRequestAutoUpdate(void);
	void						onRequestSaveIMGSignature(void);
	void						onRequestVerifyIMGSignature(void);
	void						onRequestCompareIMG(void);

	void						onRequestValidateAllDFFInActiveTab(void);
	void						onRequestValidateAllTXDInActiveTab(void);
	void						onRequestCredits(void);
	void						onRequestRenamer(void);
	void						onRequestBuildTXD(void);
	void						onRequestIMGVersionSettings(void);
	void						onRequestFeatureByName(std::string strFeatureName);
	void						onRequestLastFeatureUsed(void);
	
	void						onRequestReportIssueOrIdea(void);
	static int CALLBACK			sortMainListView(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort);
	void						onRequestCenterCOLCollisionMeshes(void);
	void						onRequestAlignCOLCollisionMeshesToDFFMesh(void);
	void						onRequestTXDOrganizer(void);
	void						onRequestDATPathsMover(void);
	void						onRequestMapMoverAndIDShifter(void);
	void						onRequestDATModelList(void);
	void						onRequestFindTXDMissingFromIMGFoundInIDE(void);
	void						onRequestFindDFFMissingFromIMGFoundInIDE(void);

	void						onRequestExtractDVCAndNVColoursIntoDFFs(void);
	void						onRequestExtract2DFXIntoDFFs(void);

private:
	MainWindow*					m_pMainWindow;
	TaskManager*				m_pTaskManager;
};