#pragma once

#include "nsimgf.h"
#include "nsbxgx.h"
#include "Type/Types.h"
#include "Globals.h"
#include "Object/Manager.h"
#include "Program/BuildMeta.h"

#define WINAPI __stdcall
uint32 WINAPI		onInitializationThreadStart(void *pThreadParameter);

class imgf::MainWindow;
class bxgx::Window;
class imgf::EditorTab;
class imgf::IMGEditor;
class imgf::IMGEditorTab;

class imgf::InputManager;
class imgf::FileGroupManager;
class imgf::RecentlyOpenManager;
class imgf::TaskManager;
class imgf::LSTProcessingManager;
class bxcf::LocalizationManager;
class imgf::LanguageManager;
class imgf::DumpManager;
class imgf::SettingsManager;
class imgf::SortManager;
class imgf::UpdateManager;
class imgf::LastUsedValueManager;
class imgf::WindowManager;

class imgf::IMGF : public bxcf::Manager
{
public:
	IMGF(void);
	~IMGF(void);

	void						init(void);
	void						uninit(void);

	void						_init(void);
	void						initCommandLine(void);

	void						openWindow(void);
	void						process(void);
	
	BuildMeta&					getBuildMeta(void) { return m_buildMeta; }

	bxgx::Window*				getActiveWindow(void);
	EditorTab*					getActiveTab(void);
	IMGEditor*					getIMGEditor(void);
	IMGEditorTab*				getEntryListTab(void); // todo
	
	InputManager*				getInputManager(void) { return m_pInputManager; }
	DumpManager*				getDumpManager(void) { return m_pDumpManager; }
	LanguageManager*			getLanguageManager(void) { return m_pLanguageManager; }
	LSTProcessingManager*		getLSTProcessingManager(void) { return m_pLSTProcessingManager; }
	WindowManager*				getWindowManager(void) { return m_pWindowManager; }
	RecentlyOpenManager*		getRecentlyOpenManager(void) { return m_pRecentlyOpenManager; }
	TaskManager*				getTaskManager(void) { return m_pTaskManager; }
	FileGroupManager*			getFileGroupManager(void) { return m_pFileGroupManager; }
	SettingsManager*			getSettingsManager(void) { return m_pSettingsManager; }
	SortManager*				getSortManager(void) { return m_pSortManager; }
	UpdateManager*				getUpdateManager(void) { return m_pUpdateManager; }
	LastUsedValueManager*		getLastUsedValueManager(void) { return m_pLastUsedValueManager; }

	void						setLastUsedDirectory(std::string strHandleName, std::string strDirectory); // todo - still needed?
	std::string					getLastUsedDirectory(std::string strHandleName); // todo - still needed?

	std::vector<std::string>	getProjectFilePaths(void);
	void						addProjectFolderPath(std::string& strProjectFolderPath);
	void						removeProjectFolderPath(std::string& strProjectFolderPath);

	void						setActiveProjectFolderPath(std::string& strProjectFolderPath);
	std::string					getActiveProjectFolderPath(void);
	void						removeActiveProjectFolderPath(void);

	static bool							isFileExtensionOpenable(std::string& strFileExtension);
	static std::vector<std::string>		getFileExtensionsOpenable(void);

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
	void						initAutoUpdateCheck(void);
	void						initTempStuff(void);

private:
	BuildMeta					m_buildMeta;

	InputManager*				m_pInputManager;
	DumpManager*				m_pDumpManager;
	LanguageManager*			m_pLanguageManager;
	LSTProcessingManager*		m_pLSTProcessingManager;
	WindowManager*				m_pWindowManager;
	RecentlyOpenManager*		m_pRecentlyOpenManager;
	TaskManager*				m_pTaskManager;
	FileGroupManager*			m_pFileGroupManager;
	SettingsManager*			m_pSettingsManager;
	SortManager*				m_pSortManager;
	UpdateManager*				m_pUpdateManager;
	LastUsedValueManager*		m_pLastUsedValueManager;
};