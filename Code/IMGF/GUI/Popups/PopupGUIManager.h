#pragma once

#include "nsimgf.h"
#include <Windows.h>
#include "nsbxcf.h"
#include "Object/Manager.h"
#include "Localization/ELanguage.h"
#include "Game/EPlatformedGame.h"
#include "Format/IMG/Regular/EIMGVersion.h"
#include "Compression/ECompressionAlgorithm.h"
#include "Type/Vector/Vec2f.h"
#include "Type/Vector/Vec3f.h"
#include <string>
#include <vector>
#include <unordered_map>

struct imgf::TextInputDialogData;
struct imgf::CConvertDialogData;
struct imgf::CExportViaDialogData;
struct imgf::CSortOptionsDialogData;
struct imgf::CStatsDialogData;
struct imgf::COrphanEntriesData;
struct imgf::CSettingsData;
struct imgf::CConfirmDialogData;
struct imgf::CDumpDialogData;
struct imgf::CListViewDialogData;
struct imgf::TextureListDialogData;
struct imgf::SessionManagerDialogData;
struct imgf::CSplitViaDialogData;
struct imgf::DragDropDialogData;
struct imgf::CDumpResultsDialogData;
struct imgf::CRenamerDialogData;
struct imgf::CDFFConversionDialogData;
struct imgf::CDuplicateEntriesDialogData;
struct imgf::CBuildTXDDialogData;
struct imgf::CIMGVersionSettingsDialogData;
struct imgf::CTXDOrganizerDialogData;
struct imgf::CDATPathsMoverDialogData;
struct imgf::CMapMoverAndIDShifterDialogData;
struct imgf::CDATModelListDialogData;
struct imgf::COverwriteEntryDialogData;
class CDialog;

class imgf::PopupGUIManager : public bxcf::Manager
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
	TextureListDialogData*					showTextureListDialog(std::string strWindowTitle, std::string strStaticText, std::string strCol1Text, std::vector<std::string>& vecLines);
	SessionManagerDialogData*				showSessionManagerDialog(std::vector<std::string>& vecSessionsData);
	uint32									showSplitViaDialog(void);
	DragDropDialogData*					showDragDropDialog(DragDropDialogData *pDragDropDialogData);
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

struct imgf::TextInputDialogData
{
	std::string			m_strWindowTitle;
	std::string			m_strStaticText;
	std::string			m_strResultText;
	std::string			m_strEditText;
};

struct imgf::CConvertDialogData
{
	bool				m_bRadioButtonSelected;
	uint32				m_uiRadioButtonIndex;
	std::string			m_strWindowTitle;
	std::string			m_strButtonText;
};

struct imgf::CExportViaDialogData
{
	bool				m_bRadioButtonSelected;
	uint32				m_uiRadioButtonIndex;
};

struct imgf::CSortOptionsDialogData
{
	std::vector<int>	m_vecSortOptions;
};

struct imgf::CStatsDialogData
{
	std::unordered_map<uint32, uint32>				m_umapStatsRWVersions;
	std::unordered_map<uint32, std::string>			m_umapRWVersionNames;
	std::unordered_map<std::string, uint32>			m_umapStatsExtensions;
};

struct imgf::COrphanEntriesData
{
	std::vector<std::string>		m_vecEntryNames;
	std::string						m_strStaticText;
	std::string						m_strButtonText;
	bool							m_bProcessAction;
};

struct imgf::CSettingsData
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
	bxcf::ELanguage					ELanguage;
	bool							m_bNewLanguageApplied;
	bool							m_bAutoCompressionImportReplace;
};

struct imgf::CConfirmDialogData
{
	std::string						m_strStaticText;
	std::string						m_strWindowTitle;
	bool							m_bResult;
	bool							m_bCancel;
};

struct imgf::CDumpDialogData
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

struct imgf::CListViewDialogData
{
	std::string						m_strWindowTitle;
	std::string						m_strStaticText;
	std::string						m_strCol1Text;
	std::vector<std::string>		m_vecLines;
	std::string						m_strSaveFileName;
	std::string						m_strSaveFolderPartialHandle;
};

struct imgf::TextureListDialogData : public CListViewDialogData
{
	bool							m_bSaveTexturesFormat2;
};

struct imgf::SessionManagerDialogData
{
	std::vector<std::string>		m_vecSessionsData;
	std::vector<std::string>		m_vecSessionsToRemove;
	std::vector<std::string>		m_vecSessionsToAdd;
	std::string						m_strSessionNameToUpdate;
	std::string						m_strSessionDataToUpdate;
};

struct imgf::CSplitViaDialogData
{
	bool							m_bRadioButtonSelected;
	uint32							m_uiRadioButtonIndex;
};

class bxgi::CRWVersion;
class bxcf::RasterDataFormat;
class bxgi::CCOLVersion;
struct imgf::DragDropDialogData
{
	bxgi::EIMGVersion				m_uiDestinationIMGVersion;
	bool							m_bCancel;
	bool							m_bCopy;
	bool							m_bConvert;
	bxgi::CRWVersion*				m_pDFFConversionRWVersion;
	bxgi::CCOLVersion*				m_pNewCOLVersion;
	uint32							m_uiTXDConversionOption;
	union
	{
		bxgi::EPlatformedGame			m_uiTXDConversionGame;
		bxgi::CRWVersion*				m_pTXDConversionRWVersion;
		bxcf::RasterDataFormat*		m_pTXDConversionRasterDataFormat;
	};
};

struct imgf::CDumpResultsDialogData
{
	CDumpResultsDialogData(void);

	uint32					m_uiCorruptTXDCount;
	uint32					m_uiTooLargeTXDCount;
	uint32					m_uiInvalidResolutionTXDCount;
	uint32					m_uiInvalidTextureNameCount;
	uint32					m_uiTXDCountExceededTextureCountLimit;
	uint32					m_uiMipmapSkippedCount;
	bool					m_bOpenAdvancedLog;
};

struct imgf::CRenamerDialogData
{
	CRenamerDialogData(void);

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

struct imgf::CDFFConversionDialogData
{
	bool					m_bConvert;
	uint8					m_ucPrelightningOption;
	uint8					m_ucAdjustPrelightningOption;
	int16					m_ssAdjustColourValues[4];
};

struct imgf::CDuplicateEntriesDialogData
{
	bool							m_bCheck;
	uint8							m_ucEntriesType;
	std::string						m_strDATPath;
	uint32							m_uiDATGameIndex;
	std::string						m_strDATGameDirectoryPath;
};

struct imgf::CBuildTXDDialogData
{
	bool							m_bBuild;
	uint8							m_uCDFFFormatsType;
	std::string						m_strDFFsFolderPath;
	std::string						m_strIDEFilePath;
	std::string						m_strTexturesFolderPath;
	std::string						m_strDestinationFolderPath;
	uint32							m_uiTextureCountPerTXD;
	bxgi::CRWVersion*						m_pRWVersion;
};

struct imgf::CIMGVersionSettingsDialogData
{
	bool							m_bSave;
	uint8							m_ucEntriesType;
	bxcf::ECompressionAlgorithm			m_ECompressionAlgorithm;
	uint32							m_uiCompressionLevel;
};

struct imgf::CTXDOrganizerDialogData
{
	bool							m_bOrganize;
	uint32							m_uiEveryNDFFFiles;
	std::string						m_strTXDNamePrefix;
	std::string						m_strTextureImportFolderPath;
	bool							m_bIDEUpdate;
	std::string						m_strIDEUpdateFolderPath;
	std::string						m_strOutputFolderPath;
	bxcf::RasterDataFormat*				m_pRasterDataFormat;
};

struct imgf::CDATPathsMoverDialogData
{
	bool							m_bMove;
	bxcf::Vec2f						m_vecOutputMapRangeMin;
	bxcf::Vec2f						m_vecOutputMapRangeMax;
	bxcf::Vec2f						m_vecOutputTileSize;
	bxcf::Vec3f						m_vecPositionOffset;
	std::string						m_strInputFolderPath;
	std::string						m_strOutputFolderPath;
};

struct imgf::CMapMoverAndIDShifterDialogData
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
	bxcf::Vec3f						m_vecPositionOffset;
	bool							m_bIgnoreDefaultObjects;
	bxgi::EPlatformedGame			m_uiIgnoreDefaultObjectsGame;
	bool							m_bIgnoreFilesShifter;
	bool							m_bIgnoreFilesMover;
	std::vector<std::string>		m_vecIgnoreFilesShifter;
	std::vector<std::string>		m_vecIgnoreFilesMover;
	std::unordered_map<std::string, bool>	m_umapShifterIgnoreFilenames;
	std::unordered_map<std::string, bool>	m_umapMoverIgnoreFilenames;
	bool							m_bMovePosition;
	bool							m_bShiftIds;
};

struct imgf::CDATModelListDialogData
{
	bool							m_bFetch;
	std::string						m_strDATFilePath;
	std::string						m_strGameFolderPath;
	std::string						m_strOutputFilePath;
};

struct imgf::COverwriteEntryDialogData
{
	bool							m_bCancel;
	uint32							m_uiResultOption;
};

struct imgf::C3ButtonDialogData
{
	bool							m_bCancel;
	uint32							m_uiResult;
	std::string						m_strWindowTitle;
	std::string						m_strStaticText;
	std::string						m_strButton1Text;
	std::string						m_strButton2Text;
	std::string						m_strButton3Text;
};