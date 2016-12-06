#ifndef CIMGF_H
#define CIMGF_H

#include "Type/Types.h"
#include "Globals.h"
#include "Object/CManager.h"
#include "CBuildMeta.h"
#include "CInstallationMeta.h"

#define WINAPI __stdcall
uint32 WINAPI		onInitializationThreadStart(void *pThreadParameter);

class CMainWindow;
class CWindow;
class CEditorTab;
class CIMGEditor;
class CIMGEditorTab;

class CSessionManager;
class CRecentlyOpenManager;
class CPopupGUIManager;
class CTaskManager;
class CLSTProcessingManager;
class mcore::CLocalizationManager;
class CLanguageManager;
class CDumpManager;
class CSettingsManager;
class CSortManager;
class CEntryViewerManager;
class CUpdateManager;
class CLastUsedValueManager;
class CWindowManager;
class CThemeDesigner;

class CWnd; // temp

class CIMGF : public mcore::CManager
{
public:
	CIMGF(void);
	~CIMGF(void);

	void						init(void);
	void						uninit(void);

	void						_init(void);

	void						openWindow(void);
	void						processWindows(void);
	
	CBuildMeta&					getBuildMeta(void) { return m_buildMeta; }
	CInstallationMeta&			getInstallationMeta(void) { return m_installationMeta; }

	CWindow*					getActiveWindow(void);
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
	CThemeDesigner*				getThemeDesigner(void) { return m_pThemeDesigner; }

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
	CInstallationMeta			m_installationMeta;

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
	CThemeDesigner*				m_pThemeDesigner;
};

#endif