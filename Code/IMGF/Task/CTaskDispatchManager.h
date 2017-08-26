#pragma once

#include <Windows.h>
#include "Object/CManager.h"
#include <string>
#include <vector>
#include "bxcf.h"
#include "Format/IMG/Regular/CIMGFormat.h"
#include "Format/IMG/Regular/eIMGEntryProperty.h"
#include "Game/ePlatformedGame.h"

class bxcf::CRasterDataFormat;
class bxgi::CRWVersion;
class bxgi::CCOLVersion;
struct CRenamedIMGEntry;
class CMainWindow;
class CTaskManager;

class CTaskDispatchManager : public bxcf::CManager
{
public:
	CTaskDispatchManager(void);

private:
	std::string&				getTaskName(void);

	std::vector<std::string>	openFile(std::string strExtensionFilters = "", bool bAllowMultiSelect = true, std::string strDefaultFileName = "");
	std::string					saveFile(std::string strExtensionFilters = "", std::string strDefaultFileName = "");
	std::string					openFolder(std::string strTitle, std::string strInitialDir = "");
	std::string					saveFolder(std::string strTitle, std::string strInitialDir = "");

	void						onStartTask(std::string strTaskName);
	void						onCompleteTask(void);
	void						onAbortTask(void);

public:
	void						init(void);
	void						uninit(void);

	void						chooseFilesToOpen(void); // todo - remove all "onRequest" from start of function names and change first characters to lowercase.
	void						_openFile(std::string& strFilePath);
	void						closeActiveFile(void);
	bool						saveAllOpenFiles(bool bCloseAll);




	void						onRequestCloseAll(void);
	void						onRequestExitTool(void);
	void						onRequestImportViaFiles(void);
	void						onRequestRemoveSelected(void);
	void						onRequestRenameEntry(void);
	void						onRequestSelectAll(void);
	void						onRequestSelectInverse(void);
	void						onRequestRebuild(void);
	void						onRequestRebuildAs(void);
	void						onRequestRebuildAll(void);
	void						onRequestConvertIMGVersion(bxgi::eIMGVersion eIMGVersion);
	void						onRequestConvertIMGVersionViaButton(void);
	void						onRequestMerge(void);
	void						onRequestSplitViaButton(void);
	void						onRequestSplitSelectedEntries(void);
	void						onRequestSplitViaIDEFile(void);
	void						onRequestSplitViaTextLines(void);
	void						onRequestReplace(void);
	void						onRequestExportSelected(void);
	void						onRequestSearchText(void);
	void						onRequestSearchSelection(void);
	void						onRequestFilter(void);
	void						onRequestFind(bool bFindInAllOpenedFiles = false);
	void						onRequestExportViaButton(void);
	void						onRequestExportViaIDEFile(void);
	void						onRequestExportViaTextLines(void);
	void						onRequestSortEntries(void);
	void						onRequestSortButton(void);
	void						onRequestRemoveViaIDEFile(void);
	void						onRequestRemoveViaTextLines(void);
	void						onRequestRemoveViaButton(void);
	void						onRequestImportViaButton(void);
	void						onRequestImportViaIDEFile(void);
	void						onRequestImportViaTextLines(void);
	void						onRequestNew(bxgi::eIMGVersion eIMGVersion);
	void						onRequestStats(void);
	void						onRequestNameCase(uint8 ucCaseType, uint8 ucFilenameType);
	void						onRequestCopyEntryData(bxgi::eIMGEntryProperty eIMGEntryProperty);
	void						onRequestShift(uint8 ucDirection);
	void						onRequestQuickExport(void);
	void						onRequestSelectViaFileExtension(void);
	void						onRequestSelectViaRWVersion(bxgi::CRWVersion *pRWVersion);
	void						onRequestVersion(void);
	void						onRequestTextureList(void);
	void						onRequestAssociateIMGExtension(void);
	std::string					onRequestSaveLog(bool bActiveTab, bool bNormalFormat);
	void						onRequestSaveSession(void);
	void						onRequestOrphanDFFEntriesNotInCOL(void);
	void						onRequestOrphanIDEEntriesNotInCOL(void);
	void						onRequestOrphanCOLEntriesNotInIDE(void);
	void						onRequestOrphanDFFEntriesNotInIDE(void);
	void						onRequestOrphanIMGEntriesNotInIDE(void);
	void						onRequestOrphanIPLEntriesNotInIDE(void);
	void						onRequestOrphanTXDEntriesNotInIDE(void);
	void						onRequestOrphanIDEEntriesNotInIMG(void);
	void						onRequestSettings(void);
	void						onRequestReopen(void);
	void						onRequestConvertDFFToRWVersion(bxgi::CRWVersion *pRWVersion);
	void						onRequestMissingTextures(void);
	void						onRequestReplaceAllFromFolder(void);
	void						onRequestExportAllEntriesFromAllTabs(void);
	void						onRequestExportEntriesViaIDEFileFromAllTabs(void);
	void						onRequestExportEntriesViaTextLinesFromAllTabs(void);
	void						onRequestImportViaFolder(void);
	void						onRequestDuplicateEntries(void);
	void						onRequestExportAllEntriesFromAllTabsIntoMultipleFolders(void);
	void						onRequestOpenLast(void);
	void						onRequestConvertTXDToGame(bxgi::ePlatformedGame ePlatformedGame);
	void						onRequestConvertTXDToRWVersion(bxgi::CRWVersion *pRWVersion);
	void						onRequestDump(void);
	void						onRequestSessionManager(void);
	void						onRequestWebsite(void);
	void						onRequestOpenLogBasic(void);
	void						onRequestOpenLogExtended(void);
	void						onRequestOpenLogFolder(void);
	void						onRequestProcessLSTFile(void);
	void						onRequestSelectViaIDE(void);
	void						onRequestExportViaIPLFile(void);
	void						onRequestRenameIMG(void);
	void						onRequestUpdate(void);
	void						onRequestAutoUpdate(void);
	void						onRequestSaveIMGSignature(void);
	void						onRequestVerifyIMGSignature(void);
	void						onRequestCompareIMG(void);
	void						onRequestConvertTXDToTextureFormat(bxcf::CRasterDataFormat *pRasterDataFormat);
	void						onRequestClearLogs(bool bAllTabs);
	void						onRequestValidateAllDFFInActiveTab(void);
	void						onRequestValidateAllTXDInActiveTab(void);
	void						onRequestCredits(void);
	void						onRequestEntryViewer(bool bDontOpenWindow = false);
	void						onRequestRenamer(void);
	void						onRequestClearRecentlyOpenedList(void);
	void						onRequestBuildTXD(void);
	void						onRequestIMGVersionSettings(void);
	void						onRequestFeatureByName(std::string strFeatureName);
	void						onRequestLastFeatureUsed(void);
	void						onRequestConvertCOLtoCOLVersion(bxgi::CCOLVersion *pCOLVersion);
	void						onRequestReportIssueOrIdea(void);
	static int CALLBACK			sortMainListView(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort);
	void						onRequestSortViaColumn(uint32 uiColumnIndex);
	void						onRequestCenterCOLCollisionMeshes(void);
	void						onRequestAlignCOLCollisionMeshesToDFFMesh(void);
	void						onRequestConvertDFFFileToWDRFile(void);
	void						onRequestTXDOrganizer(void);
	void						onRequestConvertWTDFileToTXDFile(void);
	void						onRequestDATPathsMover(void);
	void						onRequestExportViaDATFile(void);
	void						onRequestMapMoverAndIDShifter(void);
	void						onRequestDATModelList(void);
	void						onRequestFindTXDMissingFromIMGFoundInIDE(void);
	void						onRequestFindCOLMissingFromCOLFoundInIDE(void);
	void						onRequestFindDFFMissingFromIMGFoundInIDE(void);
	void						onRequestCloneIMG(void);
	void						onRequestOpenIMGFolder(void);
	void						onRequestRemoveOrphanTexturesFromModel(void);
	void						onRequestNewWindow(void);
	void						onRequestFindDFFMissingFromIDEFoundInIPL(void);
	void						onRequestSortIDEAndIPLFilesByObjectId(void);
	void						onRequestExtractDVCAndNVCColoursIntoDFFs(void);
	void						onRequestExtract2DFXIntoDFFs(void);

private:
	CMainWindow*				m_pMainWindow;
	CTaskManager*				m_pTaskManager;
};