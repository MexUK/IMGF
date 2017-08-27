#pragma once

namespace imgf
{
	namespace layers
	{
		enum ELayer;
	};

	namespace editor
	{
		namespace items
		{
			enum EEditorItem;
		};
	};

	namespace mainLayer
	{
		namespace buttons
		{
			enum EButton;
		};

		namespace mainMenuType
		{
			enum EMainMenuType;
		};
	};

	namespace task
	{
		enum ETask;
	};

	class CAutomatedTesting;
	
	class CDragDrop;
	struct CDraggableFile;
	class CDragListCtrl;
	class CDropSource;
	class CDropTarget;

	class CCollisionViewer;
	class CEntryViewer;
	class CEntryViewerManager;
	class CTextureViewer;
	struct CTextureViewerTextureData;
	enum eEntryViewerDisplayType;

	enum EEvent;

	class CDBEntry;
	class CDBFormat;
	class CDBManager;

	class CLSTEntry;
	class CLSTFormat;
	class CLSTManager;
	class CLSTSection;

	class CEditorTab;
	class CEditor;

	class CIMGEditorTab;
	class CIMGEditor;
	class CTextureEditor;

	class CButtonPressManager;

	class CMainLayer;

	class CPopupGUIManager;
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
	struct C3ButtonDialogData;

	class CWindowManager;

	class CMainWindow;

	class CLanguage;
	class CLanguageManager;

	class CBuildMeta;

	class CSettingsManager;

	class CAppDataPath;

	class CLastUsedValueManager;
	class CTaskDispatchManager;
	class CTaskDurationManager;
	class CTaskManager;

	class CDumpManager;
	
	struct CFilterOptions;
	
	class CSearchEntry;
	
	class CLSTProcessingManager;
	
	class CRecentlyOpenEntry;
	class CRecentlyOpenManager;

	struct CRenamedIMGEntry;

	class CSession;
	class CSessionManager;

	class CSortManager;
	class CSortMenuItem;
	class CSortMenuItems;
	class CSortPriorities;
	class CSortPriority;
	class CSortType;
	class CSortTypes;
	enum eSortType;

	class CUpdateConnection;
	class CUpdateConnectionManager;
	class CUpdateManager;
	class CExeBuild;

	class CIMGF;
};