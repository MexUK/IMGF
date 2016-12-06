#ifndef CPopupGUIManager_H
#define CPopupGUIManager_H

#include <Windows.h>
#include "Object/CManager.h"
#include "Localization/eLanguage.h"
#include "Collection/Games/ePlatformedGame.h"
#include "Format/RockstarGames/IMG/eIMGVersion.h"
#include "Compression/eCompressionAlgorithm.h"
#include "Type/Vector/CVector2D.h"
#include "Type/Vector/CVector3D.h"
#include <string>
#include <vector>
#include <unordered_map>

struct CTextInputDialogData;
struct CConvertDialogData;
struct CExportViaDialogData;
struct CSortOptionsDialogData;
struct CStatsDialogData;
struct COrphanEntriesData;
struct CSettingsData;
struct CConfirmDialogData;
struct CDumpDialogData;
struct CListViewDialogData;
struct CTextureListDialogData;
struct CSessionManagerDialogData;
struct CSplitViaDialogData;
struct CDragDropDialogData;
struct CDumpResultsDialogData;
struct CRenamerDialogData;
struct CDFFConversionDialogData;
struct CDuplicateEntriesDialogData;
struct CBuildTXDDialogData;
struct CIMGVersionSettingsDialogData;
struct CTXDOrganizerDialogData;
struct CDATPathsMoverDialogData;
struct CMapMoverAndIDShifterDialogData;
struct CDATModelListDialogData;
struct COverwriteEntryDialogData;
class CDialog;

class CPopupGUIManager : public mcore::CManager
{
public:
	void									init(void);
	void									uninit(void);

	void									setParentWindowHwnd(HWND hParentWindowHwnd) { m_hParentWindowHwnd = hParentWindowHwnd; }
	HWND									getParentWindowHwnd(void) { return m_hParentWindowHwnd; }

	void									updateGUIControlsTextToLanguage(CDialog *pDialog, std::string strWindowName);

	uint32									show3ButtonDialog(std::string strWindowTitle, std::string strStaticText, std::string strButton1Text, std::string strButton2Text, std::string strButton3Text);
	std::string								showTextAreaDialog(std::string strWindowTitle, std::string strStaticText, std::string strEditText = "");
	std::string								showTextInputDialog(std::string strWindowTitle, std::string strStaticText, std::string strEditText = "");
	uint32									showConvertDialog(std::string strWindowTitle, std::string strButtonText);
	uint32									showExportViaDialog(void);
	std::vector<int>						showSortOptionsDialog(void);
	uint32									showRemoveViaDialog(void);
	uint32									showImportViaDialog(void);
	void									showStatsDialog(std::unordered_map<uint32, uint32>& umapStatsRWVersions, std::unordered_map<std::string, uint32>& umapStatsExtensions, std::unordered_map<uint32, std::string>& umapRWVersionNames);
	bool									showOrphanEntriesDialog(std::vector<std::string>& vecEntryNames, std::string strStaticText, std::string strButtonText = "");
	bool									showSettingsDialog(void);
	bool									showConfirmDialog(std::string strStaticText, std::string strWindowTitle);
	bool									showConfirmDialog(std::string strStaticText, std::string strWindowTitle, bool& bDidCancel);
	CDumpDialogData*						showDumpDialog(std::string strLastUsedPath__DAT, std::string strLastUsedPath__Destination);
	void									showListViewDialog(std::string strWindowTitle, std::string strStaticText, std::string strCol1Text, std::vector<std::string>& vecLines, std::string strSaveFileName, std::string strSaveFolderPartialHandle);
	CTextureListDialogData*					showTextureListDialog(std::string strWindowTitle, std::string strStaticText, std::string strCol1Text, std::vector<std::string>& vecLines);
	CSessionManagerDialogData*				showSessionManagerDialog(std::vector<std::string>& vecSessionsData);
	uint32									showSplitViaDialog(void);
	CDragDropDialogData*					showDragDropDialog(CDragDropDialogData *pDragDropDialogData);
	void									showDumpResultsDialog(CDumpResultsDialogData *pDumpResultsDialogData);
	void									showCreditsDialog(void);
	CRenamerDialogData*						showRenamerDialog(void);
	CDFFConversionDialogData*				showDFFConversionDialog(void);
	CDuplicateEntriesDialogData*			showDuplicateEntriesDialog(void);
	CBuildTXDDialogData*					showBuildTXDDialog(void);
	CIMGVersionSettingsDialogData*			showIMGVersionSettingsDialog(void);
	CTXDOrganizerDialogData*				showTXDOrganizerDialog(void);
	CDATPathsMoverDialogData*				showDATPathsMoverDialogData(void);
	CMapMoverAndIDShifterDialogData*		showMapMoverAndIDShifterDialog(void);
	CDATModelListDialogData*				showDATModelListDialog(void);
	COverwriteEntryDialogData*				showOverwriteEntryDialog(void);

private:
	HWND									m_hParentWindowHwnd;
};

struct CTextInputDialogData
{
	std::string			m_strWindowTitle;
	std::string			m_strStaticText;
	std::string			m_strResultText;
	std::string			m_strEditText;
};

struct CConvertDialogData
{
	bool				m_bRadioButtonSelected;
	uint32				m_uiRadioButtonIndex;
	std::string			m_strWindowTitle;
	std::string			m_strButtonText;
};

struct CExportViaDialogData
{
	bool				m_bRadioButtonSelected;
	uint32				m_uiRadioButtonIndex;
};

struct CSortOptionsDialogData
{
	std::vector<int>	m_vecSortOptions;
};

struct CStatsDialogData
{
	std::unordered_map<uint32, uint32>				m_umapStatsRWVersions;
	std::unordered_map<uint32, std::string>			m_umapRWVersionNames;
	std::unordered_map<std::string, uint32>			m_umapStatsExtensions;
};

struct COrphanEntriesData
{
	std::vector<std::string>		m_vecEntryNames;
	std::string						m_strStaticText;
	std::string						m_strButtonText;
	bool							m_bProcessAction;
};

struct CSettingsData
{
	bool							m_bSave;
	std::string						m_strQuickExportPath;
	bool							m_bColouredButtons;
	bool							m_bColouredTabs;
	bool							m_bRebuildConfirmationOnClose;
	bool							m_bRebuildOnConvert;
	std::string						m_strAutomaticLoggingPath;
	bool							m_bAutomaticLoggingBasic;
	bool							m_bAutomaticLoggingExtended;
	bool							m_bAskBeforeOverwritingFiles;
	bool							m_bOverwriteOlderFiles;
	bool							m_bOverwriteNewerFiles;
	bool							m_bOverwriteProtectedFiles;
	bool							m_bAutoSave;
	bool							m_bRemoveOldVersionOnUpdate;
	mcore::eLanguage				eLanguage;
	bool							m_bNewLanguageApplied;
	bool							m_bAutoCompressionImportReplace;
};

struct CConfirmDialogData
{
	std::string						m_strStaticText;
	std::string						m_strWindowTitle;
	bool							m_bResult;
	bool							m_bCancel;
};

struct CDumpDialogData
{
	bool							m_bResult;
	uint32							m_uiDumpType;
	std::string						m_strDATPath;
	uint32							m_uiDATOptionIndex;
	std::string						m_strGameDirectoryPath;
	std::string						m_strDumpDestinationFolderPath;
	uint32							m_uiGameIndex;
	std::vector<std::string>		m_vecDumpExtensions;
	std::vector<std::string>		m_vecDumpImageTypes;
	std::string						m_strLastUsedPath__DAT;
	std::string						m_strLastUsedPath__Destination;
	bool							m_bDumpTextureImagesAsFolders;
	bool							m_bDumpAllTextureMipmaps;
};

struct CListViewDialogData
{
	std::string						m_strWindowTitle;
	std::string						m_strStaticText;
	std::string						m_strCol1Text;
	std::vector<std::string>		m_vecLines;
	std::string						m_strSaveFileName;
	std::string						m_strSaveFolderPartialHandle;
};

struct CTextureListDialogData : public CListViewDialogData
{
	bool							m_bSaveTexturesFormat2;
};

struct CSessionManagerDialogData
{
	std::vector<std::string>		m_vecSessionsData;
	std::vector<std::string>		m_vecSessionsToRemove;
	std::vector<std::string>		m_vecSessionsToAdd;
	std::string						m_strSessionNameToUpdate;
	std::string						m_strSessionDataToUpdate;
};

struct CSplitViaDialogData
{
	bool							m_bRadioButtonSelected;
	uint32							m_uiRadioButtonIndex;
};

class mcore::CRWVersion;
class mcore::CRasterDataFormat;
class mcore::CCOLVersion;
struct CDragDropDialogData
{
	mcore::eIMGVersion						m_eDestinationIMGVersion;
	bool							m_bCancel;
	bool							m_bCopy;
	bool							m_bConvert;
	mcore::CRWVersion*						m_pDFFConversionRWVersion;
	mcore::CCOLVersion*					m_pNewCOLVersion;
	uint32							m_uiTXDConversionOption;
	union
	{
		mcore::ePlatformedGame				m_eTXDConversionGame;
		mcore::CRWVersion*					m_pTXDConversionRWVersion;
		mcore::CRasterDataFormat*			m_pTXDConversionRasterDataFormat;
	};
};

struct CDumpResultsDialogData
{
	CDumpResultsDialogData(void) :
		m_bOpenAdvancedLog(false)
	{};

	uint32					m_uiCorruptTXDCount;
	uint32					m_uiTooLargeTXDCount;
	uint32					m_uiInvalidResolutionTXDCount;
	uint32					m_uiInvalidTextureNameCount;
	uint32					m_uiTXDCountExceededTextureCountLimit;
	uint32					m_uiMipmapSkippedCount;
	bool					m_bOpenAdvancedLog;
};

struct CRenamerDialogData
{
	CRenamerDialogData(void) :
		m_bRename(false),
		m_bMatchingState_IDE(false),
		m_bMatchingState_IPL(false),
		m_bMatchingState_COL(false),
		m_bUpdateLODNamesToMatch(false)
	{};

	bool							m_bRename;
	uint8							m_ucEntriesType; // 0 = all, 1 = selected
	bool							m_bMatchingState_IDE;
	bool							m_bMatchingState_IPL;
	bool							m_bMatchingState_COL;
	std::string						m_strMatchingPath_IDE;
	std::string						m_strMatchingPath_IPL;
	std::string						m_strMatchingPath_COL;
	std::string						m_strCharAdding_Front;
	std::string						m_strCharAdding_End;
	std::string						m_strCharAdding_AtPosition;
	uint32							m_uiCharAddingAtPosition_Position;
	uint8							m_ucCharReplacementType;
	uint32							m_uiCharReplaceConditional_Length;
	uint32							m_uiCharRemoving_Front;
	uint32							m_uiCharRemoving_End;
	uint32							m_uiCharRemoving_AtPosition;
	uint32							m_uiCharRemovingAtPosition_Position;
	uint8							m_ucCharCaseType;
	bool							m_bUpdateLODNamesToMatch;
};

struct CDFFConversionDialogData
{
	bool					m_bConvert;
	uint8					m_ucPrelightningOption;
	uint8					m_ucAdjustPrelightningOption;
	int16					m_ssAdjustColourValues[4];
};

struct CDuplicateEntriesDialogData
{
	bool							m_bCheck;
	uint8							m_ucEntriesType;
	std::string						m_strDATPath;
	uint32							m_uiDATGameIndex;
	std::string						m_strDATGameDirectoryPath;
};

struct CBuildTXDDialogData
{
	bool							m_bBuild;
	uint8							m_uCDFFFormatsType;
	std::string						m_strDFFsFolderPath;
	std::string						m_strIDEFilePath;
	std::string						m_strTexturesFolderPath;
	std::string						m_strDestinationFolderPath;
	uint32							m_uiTextureCountPerTXD;
	mcore::CRWVersion*						m_pRWVersion;
};

struct CIMGVersionSettingsDialogData
{
	bool							m_bSave;
	uint8							m_ucEntriesType;
	mcore::eCompressionAlgorithm			m_eCompressionAlgorithm;
	uint32							m_uiCompressionLevel;
};

struct CTXDOrganizerDialogData
{
	bool							m_bOrganize;
	uint32							m_uiEveryNDFFFiles;
	std::string						m_strTXDNamePrefix;
	std::string						m_strTextureImportFolderPath;
	bool							m_bIDEUpdate;
	std::string						m_strIDEUpdateFolderPath;
	std::string						m_strOutputFolderPath;
	mcore::CRasterDataFormat*				m_pRasterDataFormat;
};

struct CDATPathsMoverDialogData
{
	bool							m_bMove;
	mcore::CVector2D						m_vecOutputMapRangeMin;
	mcore::CVector2D						m_vecOutputMapRangeMax;
	mcore::CVector2D						m_vecOutputTileSize;
	mcore::CVector3D						m_vecPositionOffset;
	std::string						m_strInputFolderPath;
	std::string						m_strOutputFolderPath;
};

struct CMapMoverAndIDShifterDialogData
{
	bool							m_bGo;
	std::string						m_strDATFilePath;
	std::string						m_strGameFolderPath;
	bool							m_bUpdateIDEInFolder;
	bool							m_bUpdateIPLInFolder;
	std::string						m_strUpdateIDEInFolderPath;
	std::string						m_strUpdateIPLInFolderPath;
	std::string						m_strOutputFolderPath;
	uint32							m_uiIDStart;
	mcore::CVector3D						m_vecPositionOffset;
	bool							m_bIgnoreDefaultObjects;
	mcore::ePlatformedGame					m_eIgnoreDefaultObjectsGame;
	bool							m_bIgnoreFilesShifter;
	bool							m_bIgnoreFilesMover;
	std::vector<std::string>		m_vecIgnoreFilesShifter;
	std::vector<std::string>		m_vecIgnoreFilesMover;
	std::unordered_map<std::string, bool>	m_umapShifterIgnoreFilenames;
	std::unordered_map<std::string, bool>	m_umapMoverIgnoreFilenames;
	bool							m_bMovePosition;
	bool							m_bShiftIds;
};

struct CDATModelListDialogData
{
	bool							m_bFetch;
	std::string						m_strDATFilePath;
	std::string						m_strGameFolderPath;
	std::string						m_strOutputFilePath;
};

struct COverwriteEntryDialogData
{
	bool							m_bCancel;
	uint32							m_uiResultOption;
};

struct C3ButtonDialogData
{
	bool							m_bCancel;
	uint32							m_uiResult;
	std::string						m_strWindowTitle;
	std::string						m_strStaticText;
	std::string						m_strButton1Text;
	std::string						m_strButton2Text;
	std::string						m_strButton3Text;
};

#endif