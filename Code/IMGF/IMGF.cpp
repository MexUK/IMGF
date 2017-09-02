#pragma warning(disable : 4005)

#include "IMGF.h"
#include "Engine/RW/CRWManager.h"
#include "Engine/RW/CRWVersionManager.h"
#include "Engine/RAGE/CRageManager.h"
#include "Tasks/RecentlyOpen/RecentlyOpenManager.h"
#include "Tasks/Session/SessionManager.h"
#include "GUI/Popups/PopupGUIManager.h"
#include "Tasks/LST/LSTProcessingManager.h"
#include "Task/TaskManager.h"
#include "Task/TaskDispatchManager.h"
#include "Settings/SettingsManager.h"
#include "Tasks/Sort/SortManager.h"
#include "Format/IMG/Regular/CIMGManager.h"
#include "Static/CInput.h"
#include "Window/Window.h"
#include "Controls/Text.h"
#include "Controls/Grid.h"
#include "Controls/Button.h"
#include "Controls/CheckBox.h"
#include "Controls/DropDown.h"
#include "Controls/ScrollBar.h"
#include "Controls/ProgressBar.h"
#include "Controls/RadioButton.h"
#include "Controls/TextBox.h"
#include "GUI/Window/WindowManager.h"
#include "GUI/Editors/IMGEditor.h"
#include "GUI/Editors/Tab/IMGEditorTab.h"
#include "Static/CString2.h"
#include "Static/CFile.h"
#include "Static/CPath.h"
#include "Static/CRegistry.h"
#include "DragDrop/DropTarget.h"
#include "DB/DBManager.h"
#include "DB/DBFormat.h"
#include "Static/CDebug.h"
#include "Format/IMG/Regular/CIMGEntry.h"
#include "Format/COL/CCOLManager.h"
#include "Format/COL/CCOLVersionManager.h"
#include "Format/COL/CCOLVersion.h"
#include "Static/CInput.h"
#include "Tasks/Find/SearchEntry.h"
#include "EntryViewer/EntryViewerManager.h"
#include "Static/CStdVector.h"
#include "Updater/UpdateManager.h"
#include "Program/buildnumber.h"
#include "Compression/ECompressionAlgorithm.h"
#include "Format/DAT/Loader/CDATLoaderManager.h"
#include "Format/DAT/Path/CDATPathManager.h"
#include "Localization/CLocalizationManager.h"
#include "Language/LanguageManager.h"
#include "Format/Image/BMP/CBMPManager.h"
#include "Format/Image/CUR/CCURManager.h"
#include "Format/DFF/CDFFManager.h"
#include "DB/DBManager.h"
#include "Format/Image/ICO/CICOManager.h"
#include "Format/IDE/CIDEManager.h"
#include "Image/CImageManager.h"
#include "Format/IPL/CIPLManager.h"
#include "LST/LSTManager.h"
#include "Format/TXD/CTXDManager.h"
#include "Format/WDR/CWDRManager.h"
#include "Format/WTD/CWTDManager.h"
#include "Localization/ELanguage.h"
#include "Language/Language.h"
#include "Game/CGameManager.h"
#include "Platform/Hardware/CPlatformManager.h"
#include "Format/RW/CRWSection.h"
#include "Static/CTiming.h"
#include "Task/LastUsedValueManager.h"
#include "GUI/Windows/MainWindow.h"
#include "Styles/StyleManager.h"
#include "GUI/Input/InputManager.h"
#include "Static/CDataPath.h"

using namespace std;
using namespace bxcf;
using namespace bxgx;
using namespace bxgi;
using namespace imgf;

IMGF::IMGF(void)
{
	CDataPath::setAppFolderName("IMGFactory");

	// construct objects stored by IMGF
	m_pInputManager			= new InputManager;
	m_pEntryViewerManager	= new EntryViewerManager;
	m_pPopupGUIManager		= new PopupGUIManager;
	m_pLanguageManager		= new LanguageManager;
	m_pLSTProcessingManager	= new LSTProcessingManager;
	m_pRecentlyOpenManager	= new RecentlyOpenManager;
	m_pTaskManager			= new TaskManager;
	m_pSessionManager		= new SessionManager;
	m_pSettingsManager		= new SettingsManager;
	m_pSortManager			= new SortManager;
	m_pUpdateManager		= new UpdateManager;
	m_pWindowManager		= new WindowManager;
	m_pLastUsedValueManager	= new LastUsedValueManager;
}

IMGF::~IMGF(void)
{
	// destruct objects stored by IMGF
	delete m_pInputManager;
	delete m_pEntryViewerManager;
	delete m_pPopupGUIManager;
	delete m_pLanguageManager;
	delete m_pLSTProcessingManager;
	delete m_pRecentlyOpenManager;
	delete m_pTaskManager;
	delete m_pSessionManager;
	delete m_pSettingsManager;
	delete m_pSortManager;
	delete m_pUpdateManager;
	delete m_pWindowManager;
	delete m_pLastUsedValueManager;
}

// init/uninit (ocurs in original thread)
void				IMGF::init(void)
{
	m_pWindowManager->init();
	_init();
	//initInitializationThread();
}

void				IMGF::uninit(void)
{
}

// init tasks (ocurs in original thread)
void				IMGF::initInitializationThread(void)
{
	SECURITY_ATTRIBUTES sa;
	sa.nLength = sizeof(SECURITY_ATTRIBUTES);
	sa.lpSecurityDescriptor = NULL;
	sa.bInheritHandle = TRUE;
	CreateThread(&sa, 0, onInitializationThreadStart, this, 0, NULL);
}

// init (occurs in different thread)
uint32 WINAPI		onInitializationThreadStart(void *pThreadParameter)
{
	((IMGF*)pThreadParameter)->_init();
	return 0;
}

void				IMGF::_init(void)
{
	initBuildMeta();
	initInstallationMeta();
	initStoredObjects();
	initSingletonObjects();
	initStaticData();
	initEventBinding();
	initSettings();
	//initLocalization();
	initSorting();
	initOldVersionMigration();
	initTempStuff();
	initCommandLine();
	initAutoUpdateCheck();
}

// init tasks (occurs in different thread)
void				IMGF::initBuildMeta(void)
{
	getBuildMeta().setCurrentVersion(1.3f);
	getBuildMeta().setIsAlphaBuild(true);
	getBuildMeta().setCurrentVersionString("1.3" + string(getBuildMeta().isAlphaBuild() ? " Alpha" : ""));
}

void				IMGF::initInstallationMeta(void)
{
	// choose installation folder
	string strInstallationPath = SettingsManager::getInternalSetting("InstallationPath");
	if (strInstallationPath == "")
	{
		string strProgramFilesx86FolderName = "IMG Factory";
		string strPotentialInstallationPath = "C:\\Program Files (x86)\\" + strProgramFilesx86FolderName + "\\" + getIMGF()->getBuildMeta().getCurrentVersionString() + "\\";
		if (CFile::doesFolderExist(strPotentialInstallationPath))
		{
			strInstallationPath = strPotentialInstallationPath;
			SettingsManager::setInternalSetting("InstallationPath", strPotentialInstallationPath);
		}
		else
		{
			/*
			todo
			//string strChosenInstallationFolder = CInput::chooseFolderDialog(getDialog()->GetSafeHwnd(), CLocalizationManager::get()->getTranslatedText("ChooseFolderPopup_11"), getIMGF()->getLastUsedDirectory("INSTALLATION"));
			string strChosenInstallationFolder = CInput::chooseFolderDialog(getActiveWindow() ? getActiveWindow()->getWindowHandle() : NULL, "Choose the installation folder for IMGF. (e.g. In program files x86)", getIMGF()->getLastUsedDirectory("INSTALLATION"));
			if (strChosenInstallationFolder == "")
			{
			}
			else
			{
				strInstallationPath = strChosenInstallationFolder;
				getIMGF()->setLastUsedDirectory("INSTALLATION", strChosenInstallationFolder);
				SettingsManager::setInternalSetting("InstallationPath", strChosenInstallationFolder);
			}
			*/
		}
	}
}

void				IMGF::initStoredObjects(void)
{
	// initialize objects stored by IMGF
	// Excludes: WindowManager and SortManager
	m_pEntryViewerManager->init();
	m_pPopupGUIManager->init();
	m_pLanguageManager->init();
	m_pLSTProcessingManager->init();
	m_pRecentlyOpenManager->init();
	m_pSessionManager->init();
	m_pSettingsManager->init();
	m_pUpdateManager->init();
}

void				IMGF::initSingletonObjects(void)
{
	// initialize singleton objects
	CBMPManager::get()->init();
	CCOLManager::get()->init();
	CCURManager::get()->init();
	CDATLoaderManager::get()->init();
	CDATPathManager::get()->init();
	DBManager::get()->init();
	CDFFManager::get()->init();
	CGameManager::get()->init();
	CICOManager::get()->init();
	CIDEManager::get()->init();
	CImageManager::get()->init();
	CIMGManager::get()->init();
	CIPLManager::get()->init();
	LSTManager::get()->init();
	CPlatformManager::get()->init();
	CRageManager::get()->init();
	CRWManager::get()->init();
	CTXDManager::get()->init();
	CWDRManager::get()->init();
	CWTDManager::get()->init();
}

void				IMGF::initStaticData(void)
{
	CRWSection::initStatic();
}

void				IMGF::initEventBinding(void)
{
	/*
	auto pOnEntriesExtensionChange = [](void *pData)
	{
		if (getIMGF()->getEntryListTab() != nullptr) // When opening an IMG parseIMG() will call addEntry() which will trigger this callback, but the active view instance won't be set yet.
		{
			getIMGF()->getEntryListTab()->loadFilter_Type();
		}
	};
	
	auto pOnTaskProgress = [](void *pData)
	{
		getIMGF()->getTaskManager()->onTaskProgressTick();
	};
	
	bindEvent(TASK_PROGRESS,					pOnTaskProgress);
	bindEvent(UNSERIALIZE_IMG_ENTRY,			pOnTaskProgress);
	bindEvent(SERIALIZE_IMG_ENTRY,				pOnTaskProgress);
	bindEvent(ADD_IMG_ENTRY_FILE_EXTENSION,		pOnEntriesExtensionChange);
	bindEvent(REMOVE_IMG_ENTRY_FILE_EXTENSION,	pOnEntriesExtensionChange);
	*/
}

void				IMGF::initSettings(void)
{
	getSettingsManager()->loadSettings();
}

void				IMGF::initLocalization(void)
{
	ELanguage eActivELanguage = (ELanguage)getIMGF()->getSettingsManager()->getSettingInt("Language");
	CLocalizationManager::get()->setActivELanguage(eActivELanguage);
	CLocalizationManager::get()->setActivELanguageName(getIMGF()->getLanguageManager()->getLanguageById(eActivELanguage)->getLanguageName());
	CLocalizationManager::get()->setInstallationPath(SettingsManager::getInternalSetting("InstallationPath"));
	CLocalizationManager::get()->loadTranslatedText();
}

void				IMGF::initSorting(void)
{
	m_pSortManager->init();
}

void				IMGF::initOldVersionMigration(void)
{
	// delete previous version's exe file
	string strPreviousVersionExePath = SettingsManager::getInternalSetting("DeletePreviousVersionOnNextLaunch");
	if (strPreviousVersionExePath == "1")
	{
		int iResult;
		bool bFileExists;
		uint32 uiIterationCount = 0;
		do
		{
			bFileExists = CFile::doesFileExist(strPreviousVersionExePath);
			if (bFileExists)
			{
				iResult = DeleteFile(CString2::convertStdStringToStdWString(strPreviousVersionExePath).c_str());
				if (iResult == 0)
				{
					Sleep(250);
				}
			}
			uiIterationCount++;
			if (uiIterationCount == 10)
			{
				break; // 2.5 seconds max
			}
		}
		while (bFileExists && iResult == 0);
		SettingsManager::setInternalSetting("DeletePreviousVersionOnNextLaunch", "0");
	}
}

void				IMGF::initCommandLine(void)
{
	// command line
	wchar_t *pCommandLine = GetCommandLine();
	string strCommandLine = CString2::convertStdWStringToStdString(pCommandLine);
	int uiPos1 = strCommandLine.find('"', 0);
	int uiPos2 = strCommandLine.find('"', uiPos1 + 1);
	int uiPos3 = strCommandLine.find('"', uiPos2 + 1);
	if (uiPos3 != string::npos)
	{
		int uiPos4 = strCommandLine.find('"', uiPos3 + 1);
		string strPath = strCommandLine.substr(uiPos3 + 1, (uiPos4 - uiPos3) - 1);
		//MessageBox(NULL, CString2::convertStdStringToStdWString(strCommandLine).c_str(), L"S", MB_OK);
		getTaskManager()->getDispatch()->_openFile(strPath);
	}
}

void				IMGF::initAutoUpdateCheck(void)
{
	/*
	todo
	This currently calls a onRequestBlah which eventualls calls TaskManager::onFeatureEnd which can crash before the IMGEditor object has been created.
	So move this to like lambda: onWindowOpen()
	getIMGF()->getTaskManager()->getDispatch()->onRequestAutoUpdate();
	*/
}

void				IMGF::initTempStuff(void)
{
}

// windows/tabs
void				IMGF::openWindow(void)
{
	getWindowManager()->openWindow();
	
	m_pInputManager->init();
	m_pTaskManager->init();

	//Events::trigger(TOOL_READY);
}

void				IMGF::process(void)
{
	getWindowManager()->process();
}

Window*			IMGF::getActiveWindow(void)
{
	return BXGX::get()->getActiveWindow();
}

EditorTab*			IMGF::getActiveTab(void)
{
	MainWindow *pIMGFWindow = (MainWindow*) BXGX::get()->getEntryByIndex(0);
	IMGEditor *pIMGEditor = (IMGEditor*) pIMGFWindow->getEntryByIndex(0);
	EditorTab *pEditorTab = pIMGEditor->getActiveTab();
	return pEditorTab;
}

IMGEditor*			IMGF::getIMGEditor(void)
{
	MainWindow *pIMGFWindow = (MainWindow*) BXGX::get()->getEntryByIndex(0);
	IMGEditor *pIMGEditor = (IMGEditor*) pIMGFWindow->getEntryByIndex(0);
	return pIMGEditor;
}

IMGEditorTab*		IMGF::getEntryListTab(void)
{
	MainWindow *pIMGFWindow = (MainWindow*) BXGX::get()->getEntryByIndex(0);
	IMGEditor *pIMGEditor = (IMGEditor*) pIMGFWindow->getEntryByIndex(0);
	IMGEditorTab *pIMGEditorTab = (IMGEditorTab*) pIMGEditor->getTabs().getEntryByIndex(0);
	return pIMGEditorTab;
}

// last used directory
void				IMGF::setLastUsedDirectory(string strHandleName, string strDirectory)
{
	// todo - remove after TaskDispatchManager is done
}
string				IMGF::getLastUsedDirectory(string strHandleName)
{
	return ""; // todo - remove after TaskDispatchManager is done
}