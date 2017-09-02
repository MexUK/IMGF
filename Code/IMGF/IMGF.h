#pragma once

#include "nsimgf.h"
#include "nsbxgx.h"
#include "Type/Types.h"
#include "Globals.h"
#include "Object/CManager.h"
#include "Program/BuildMeta.h"

#define WINAPI __stdcall
uint32 WINAPI		onInitializationThreadStart(void *pThreadParameter);

class imgf::MainWindow;
class bxgx::Window;
class imgf::EditorTab;
class imgf::IMGEditor;
class imgf::IMGEditorTab;

class imgf::InputManager;
class imgf::SessionManager;
class imgf::RecentlyOpenManager;
class imgf::PopupGUIManager;
class imgf::TaskManager;
class imgf::LSTProcessingManager;
class bxcf::CLocalizationManager;
class imgf::LanguageManager;
class imgf::DumpManager;
class imgf::SettingsManager;
class imgf::SortManager;
class imgf::EntryViewerManager;
class imgf::UpdateManager;
class imgf::LastUsedValueManager;
class imgf::WindowManager;

class CWnd; // temp

class imgf::IMGF : public bxcf::CManager
{
public:
	IMGF(void);
	~IMGF(void);

	void						init(void);
	void						uninit(void);

	void						_init(void);

	void						openWindow(void);
	void						process(void);
	
	BuildMeta&					getBuildMeta(void) { return m_buildMeta; }

	bxgx::Window*				getActiveWindow(void);
	EditorTab*					getActiveTab(void);
	IMGEditor*					getIMGEditor(void);
	IMGEditorTab*				getEntryListTab(void); // todo
	
	DumpManager*				getDumpManager(void) { return m_pDumpManager; }
	EntryViewerManager*		getEntryViewerManager(void) { return m_pEntryViewerManager; }
	PopupGUIManager*			getPopupGUIManager(void) { return m_pPopupGUIManager; }
	LanguageManager*			getLanguageManager(void) { return m_pLanguageManager; }
	LSTProcessingManager*		getLSTProcessingManager(void) { return m_pLSTProcessingManager; }
	WindowManager*				getWindowManager(void) { return m_pWindowManager; }
	RecentlyOpenManager*		getRecentlyOpenManager(void) { return m_pRecentlyOpenManager; }
	TaskManager*				getTaskManager(void) { return m_pTaskManager; }
	SessionManager*			getSessionManager(void) { return m_pSessionManager; }
	SettingsManager*			getSettingsManager(void) { return m_pSettingsManager; }
	SortManager*				getSortManager(void) { return m_pSortManager; }
	UpdateManager*				getUpdateManager(void) { return m_pUpdateManager; }
	LastUsedValueManager*		getLastUsedValueManager(void) { return m_pLastUsedValueManager; }

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
	BuildMeta					m_buildMeta;

	InputManager*				m_pInputManager;
	DumpManager*				m_pDumpManager;
	EntryViewerManager*		m_pEntryViewerManager;
	PopupGUIManager*			m_pPopupGUIManager;
	LanguageManager*			m_pLanguageManager;
	LSTProcessingManager*		m_pLSTProcessingManager;
	WindowManager*				m_pWindowManager;
	RecentlyOpenManager*		m_pRecentlyOpenManager;
	TaskManager*				m_pTaskManager;
	SessionManager*			m_pSessionManager;
	SettingsManager*			m_pSettingsManager;
	SortManager*				m_pSortManager;
	UpdateManager*				m_pUpdateManager;
	LastUsedValueManager*		m_pLastUsedValueManager;
};