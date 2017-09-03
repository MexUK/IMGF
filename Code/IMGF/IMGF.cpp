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
#include "Static/Input.h"
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
#include "Static/String2.h"
#include "Static/File.h"
#include "Static/Path.h"
#include "Static/Registry.h"
#include "DragDrop/DropTarget.h"
#include "DB/DBManager.h"
#include "DB/DBFormat.h"
#include "Static/Debug.h"
#include "Format/IMG/Regular/CIMGEntry.h"
#include "Format/COL/CCOLManager.h"
#include "Format/COL/CCOLVersionManager.h"
#include "Format/COL/CCOLVersion.h"
#include "Static/Input.h"
#include "Tasks/Find/SearchEntry.h"
#include "EntryViewer/EntryViewerManager.h"
#include "Static/StdVector.h"
#include "Updater/UpdateManager.h"
#include "Program/buildnumber.h"
#include "Compression/ECompressionAlgorithm.h"
#include "Format/DAT/Loader/CDATLoaderManager.h"
#include "Format/DAT/Path/CDATPathManager.h"
#include "Localization/LocalizationManager.h"
#include "Language/LanguageManager.h"
#include "Format/Image/BMP/BMPManager.h"
#include "Format/Image/CUR/CURManager.h"
#include "Format/DFF/CDFFManager.h"
#include "DB/DBManager.h"
#include "Format/Image/ICO/ICOManager.h"
#include "Format/IDE/CIDEManager.h"
#include "Image/ImageManager.h"
#include "Format/IPL/CIPLManager.h"
#include "LST/LSTManager.h"
#include "Format/TXD/CTXDManager.h"
#include "Format/WDR/CWDRManager.h"
#include "Format/WTD/CWTDManager.h"
#include "Localization/ELanguage.h"
#include "Language/Language.h"
#include "Game/CGameManager.h"
#include "Platform/Hardware/PlatformManager.h"
#include "Format/RW/CRWSection.h"
#include "Static/Timing.h"
#include "Task/LastUsedValueManager.h"
#include "GUI/Windows/MainWindow.h"
#include "Styles/StyleManager.h"
#include "GUI/Input/InputManager.h"
#include "Static/DataPath.h"

using namespace std;
using namespace bxcf;
using namespace bxgx;
using namespace bxgi;
using namespace imgf;

IMGF::IMGF(void)
{
	DataPath::setAppFolderName("IMGFactory");

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
		if (File::doesFolderExist(strPotentialInstallationPath))
		{
			strInstallationPath = strPotentialInstallationPath;
			SettingsManager::setInternalSetting("InstallationPath", strPotentialInstallationPath);
		}
		else
		{
			/*
			todo
			//string strChosenInstallationFolder = Input::chooseFolderDialog(getDialog()->GetSafeHwnd(), LocalizationManager::get()->getTranslatedText("ChooseFolderPopup_11"), getIMGF()->getLastUsedDirectory("INSTALLATION"));
			string strChosenInstallationFolder = Input::chooseFolderDialog(getActiveWindow() ? getActiveWindow()->getWindowHandle() : NULL, "Choose the installation folder for IMGF. (e.g. In program files x86)", getIMGF()->getLastUsedDirectory("INSTALLATION"));
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
	BMPManager::get()->init();
	CCOLManager::get()->init();
	CURManager::get()->init();
	CDATLoaderManager::get()->init();
	CDATPathManager::get()->init();
	DBManager::get()->init();
	CDFFManager::get()->init();
	CGameManager::get()->init();
	ICOManager::get()->init();
	CIDEManager::get()->init();
	ImageManager::get()->init();
	CIMGManager::get()->init();
	CIPLManager::get()->init();
	LSTManager::get()->init();
	PlatformManager::get()->init();
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
	LocalizationManager::get()->setActivELanguage(eActivELanguage);
	LocalizationManager::get()->setActivELanguageName(getIMGF()->getLanguageManager()->getLanguageById(eActivELanguage)->getLanguageName());
	LocalizationManager::get()->setInstallationPath(SettingsManager::getInternalSetting("InstallationPath"));
	LocalizationManager::get()->loadTranslatedText();
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
			bFileExists = File::doesFileExist(strPreviousVersionExePath);
			if (bFileExists)
			{
				iResult = DeleteFile(String2::convertStdStringToStdWString(strPreviousVersionExePath).c_str());
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
	string strCommandLine = String2::convertStdWStringToStdString(pCommandLine);
	int uiPos1 = strCommandLine.find('"', 0);
	int uiPos2 = strCommandLine.find('"', uiPos1 + 1);
	int uiPos3 = strCommandLine.find('"', uiPos2 + 1);
	if (uiPos3 != string::npos)
	{
		int uiPos4 = strCommandLine.find('"', uiPos3 + 1);
		string strPath = strCommandLine.substr(uiPos3 + 1, (uiPos4 - uiPos3) - 1);
		//MessageBox(NULL, String2::convertStdStringToStdWString(strCommandLine).c_str(), L"S", MB_OK);
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