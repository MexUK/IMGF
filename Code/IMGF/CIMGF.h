#pragma once

#include "nsimgf.h"
#include "nsbxgx.h"
#include "Type/Types.h"
#include "Globals.h"
#include "Object/CManager.h"
#include "Program/CBuildMeta.h"

#define WINAPI __stdcall
uint32 WINAPI		onInitializationThreadStart(void *pThreadParameter);

class imgf::CMainWindow;
class bxgx::CWindow;
class imgf::CEditorTab;
class imgf::CIMGEditor;
class imgf::CIMGEditorTab;

class imgf::CButtonPressManager;
class imgf::CSessionManager;
class imgf::CRecentlyOpenManager;
class imgf::CPopupGUIManager;
class imgf::CTaskManager;
class imgf::CLSTProcessingManager;
class bxcf::CLocalizationManager;
class imgf::CLanguageManager;
class imgf::CDumpManager;
class imgf::CSettingsManager;
class imgf::CSortManager;
class imgf::CEntryViewerManager;
class imgf::CUpdateManager;
class imgf::CLastUsedValueManager;
class imgf::CWindowManager;

class CWnd; // temp

class imgf::CIMGF : public bxcf::CManager
{
public:
	CIMGF(void);
	~CIMGF(void);

	void						init(void);
	void						uninit(void);

	void						_init(void);

	void						openWindow(void);
	void						process(void);
	
	CBuildMeta&					getBuildMeta(void) { return m_buildMeta; }

	bxgx::CWindow*				getActiveWindow(void);
	CEditorTab*					getActiveTab(void);
	CIMGEditor*					getIMGEditor(void);
	CIMGEditorTab*				getEntryListTab(void); // todo
	
	CDumpManager*				getDumpManager(void) { return m_pDumpManager; }
	CEntryViewerManager*		getEntryViewerManager(void) { return m_pEntryViewerManager; }
	CPopupGUIManager*			getPopupGUIManager(void) { return m_pPopupGUIManager; }
	CLanguageManager*			getLanguageManager(void) { return m_pLanguageManager; }
	CLSTProcessingManager*		getLSTProcessingManager(void) { return m_pLSTProcessingManager; }
	CWindowManager*				getWindowManager(void) { return m_pWindowManager; }
	CRecentlyOpenManager*		getRecentlyOpenManager(void) { return m_pRecentlyOpenManager; }
	CTaskManager*				getTaskManager(void) { return m_pTaskManager; }
	CSessionManager*			getSessionManager(void) { return m_pSessionManager; }
	CSettingsManager*			getSettingsManager(void) { return m_pSettingsManager; }
	CSortManager*				getSortManager(void) { return m_pSortManager; }
	CUpdateManager*				getUpdateManager(void) { return m_pUpdateManager; }
	CLastUsedValueManager*		getLastUsedValueManager(void) { return m_pLastUsedValueManager; }

	void						setLastUsedDirectory(std::string strHandleName, std::string strDirectory);
	std::string					getLastUsedDirectory(std::string strHandleName);

	CWnd*						getDialog(void) { return nullptr; } // temp

private:
	void						initInitializationThread(void);

	void						initBuildMeta(void);
	void						initInstallationMeta(void);
	void						initStoredObjects(void);
	void						initSingletonObjects(void);
	void						initStaticData(void);
	void						initEventBinding(void);
	void						initSettings(void);
	void						initLocalization(void);
	void						initSorting(void);
	void						initOldVersionMigration(void);
	void						initCommandLine(void);
	void						initAutoUpdateCheck(void);
	void						initTempStuff(void);

private:
	CBuildMeta					m_buildMeta;

	CButtonPressManager*		m_pButtonPressManager;
	CDumpManager*				m_pDumpManager;
	CEntryViewerManager*		m_pEntryViewerManager;
	CPopupGUIManager*			m_pPopupGUIManager;
	CLanguageManager*			m_pLanguageManager;
	CLSTProcessingManager*		m_pLSTProcessingManager;
	CWindowManager*				m_pWindowManager;
	CRecentlyOpenManager*		m_pRecentlyOpenManager;
	CTaskManager*				m_pTaskManager;
	CSessionManager*			m_pSessionManager;
	CSettingsManager*			m_pSettingsManager;
	CSortManager*				m_pSortManager;
	CUpdateManager*				m_pUpdateManager;
	CLastUsedValueManager*		m_pLastUsedValueManager;
};