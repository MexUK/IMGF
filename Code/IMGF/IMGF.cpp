#pragma warning(disable : 4005)

#include "IMGF.h"
#include "Engine/RW/CRWManager.h"
#include "Engine/RW/CRWVersionManager.h"
#include "Engine/RAGE/CRageManager.h"
#include "Tasks/RecentlyOpen/CRecentlyOpenManager.h"
#include "Tasks/Session/CSessionManager.h"
#include "GUI/Popups/CPopupGUIManager.h"
#include "Tasks/LST/CLSTProcessingManager.h"
#include "Task/CTaskManager.h"
#include "Task/CTaskDispatchManager.h"
#include "Settings/CSettingsManager.h"
#include "Tasks/Sort/CSortManager.h"
#include "Format/IMG/Regular/CIMGManager.h"
#include "Static/CInput.h"
#include "Window/CWindow.h"
#include "Controls/CText.h"
#include "Controls/CGrid.h"
#include "Controls/CButton.h"
#include "Controls/CCheckBox.h"
#include "Controls/CDropDown.h"
#include "Controls/CScrollBar.h"
#include "Controls/CProgressBar.h"
#include "Controls/CRadioButton.h"
#include "Controls/CTextBox.h"
#include "GUI/Window/CWindowManager.h"
#include "GUI/Editors/CIMGEditor.h"
#include "GUI/Editors/Tab/CIMGEditorTab.h"
#include "Static/CString2.h"
#include "Static/CFile.h"
#include "Static/CPath.h"
#include "Static/CRegistry.h"
#include "DragDrop/CDropTarget.h"
#include "DB/CDBManager.h"
#include "DB/CDBFormat.h"
#include "Static/CDebug.h"
#include "Format/IMG/Regular/CIMGEntry.h"
#include "Format/COL/CCOLManager.h"
#include "Format/COL/CCOLVersionManager.h"
#include "Format/COL/CCOLVersion.h"
#include "Static/CInput.h"
#include "Tasks/Find/CSearchEntry.h"
#include "EntryViewer/CEntryViewerManager.h"
#include "Static/CStdVector.h"
#include "Updater/CUpdateManager.h"
#include "Program/buildnumber.h"
#include "Compression/eCompressionAlgorithm.h"
#include "Format/DAT/Loader/CDATLoaderManager.h"
#include "Format/DAT/Path/CDATPathManager.h"
#include "Localization/CLocalizationManager.h"
#include "Language/CLanguageManager.h"
#include "Format/Image/BMP/CBMPManager.h"
#include "Format/Image/CUR/CCURManager.h"
#include "Format/DFF/CDFFManager.h"
#include "DB/CDBManager.h"
#include "Format/Image/ICO/CICOManager.h"
#include "Format/IDE/CIDEManager.h"
#include "Image/CImageManager.h"
#include "Format/IPL/CIPLManager.h"
#include "LST/CLSTManager.h"
#include "Format/TXD/CTXDManager.h"
#include "Format/WDR/CWDRManager.h"
#include "Format/WTD/CWTDManager.h"
#include "Localization/eLanguage.h"
#include "Language/CLanguage.h"
#include "Game/CGameManager.h"
#include "Platform/Hardware/CPlatformManager.h"
#include "Format/RW/CRWSection.h"
#include "Static/CTiming.h"
#include "Task/CLastUsedValueManager.h"
#include "GUI/Windows/CMainWindow.h"
#include "Styles/CStyleManager.h"
#include "GUI/Input/Buttons/CButtonPressManager.h"
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
	m_pButtonPressManager	= new CButtonPressManager;
	m_pEntryViewerManager	= new CEntryViewerManager;
	m_pPopupGUIManager		= new CPopupGUIManager;
	m_pLanguageManager		= new CLanguageManager;
	m_pLSTProcessingManager	= new CLSTProcessingManager;
	m_pRecentlyOpenManager	= new CRecentlyOpenManager;
	m_pTaskManager			= new CTaskManager;
	m_pSessionManager		= new CSessionManager;
	m_pSettingsManager		= new CSettingsManager;
	m_pSortManager			= new CSortManager;
	m_pUpdateManager		= new CUpdateManager;
	m_pWindowManager		= new CWindowManager;
	m_pLastUsedValueManager	= new CLastUsedValueManager;
}

IMGF::~IMGF(void)
{
	// destruct objects stored by IMGF
	delete m_pButtonPressManager;
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
	string strInstallationPath = CSettingsManager::getInternalSetting("InstallationPath");
	if (strInstallationPath == "")
	{
		string strProgramFilesx86FolderName = "IMG Factory";
		string strPotentialInstallationPath = "C:\\Program Files (x86)\\" + strProgramFilesx86FolderName + "\\" + getIMGF()->getBuildMeta().getCurrentVersionString() + "\\";
		if (CFile::doesFolderExist(strPotentialInstallationPath))
		{
			strInstallationPath = strPotentialInstallationPath;
			CSettingsManager::setInternalSetting("InstallationPath", strPotentialInstallationPath);
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
				CSettingsManager::setInternalSetting("InstallationPath", strChosenInstallationFolder);
			}
			*/
		}
	}
}

void				IMGF::initStoredObjects(void)
{
	// initialize objects stored by IMGF
	// Excludes: CWindowManager and CSortManager
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
	CDBManager::get()->init();
	CDFFManager::get()->init();
	CGameManager::get()->init();
	CICOManager::get()->init();
	CIDEManager::get()->init();
	CImageManager::get()->init();
	CIMGManager::get()->init();
	CIPLManager::get()->init();
	CLSTManager::get()->init();
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
	eLanguage eActiveLanguage = (eLanguage)getIMGF()->getSettingsManager()->getSettingInt("Language");
	CLocalizationManager::get()->setActiveLanguage(eActiveLanguage);
	CLocalizationManager::get()->setActiveLanguageName(getIMGF()->getLanguageManager()->getLanguageById(eActiveLanguage)->getLanguageName());
	CLocalizationManager::get()->setInstallationPath(CSettingsManager::getInternalSetting("InstallationPath"));
	CLocalizationManager::get()->loadTranslatedText();
}

void				IMGF::initSorting(void)
{
	m_pSortManager->init();
}

void				IMGF::initOldVersionMigration(void)
{
	// delete previous version's exe file
	string strPreviousVersionExePath = CSettingsManager::getInternalSetting("DeletePreviousVersionOnNextLaunch");
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
		CSettingsManager::setInternalSetting("DeletePreviousVersionOnNextLaunch", "0");
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
	This currently calls a onRequestBlah which eventualls calls CTaskManager::onFeatureEnd which can crash before the CIMGEditor object has been created.
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
	
	m_pButtonPressManager->init();
	m_pTaskManager->init();

	//Events::trigger(TOOL_READY);
}

void				IMGF::process(void)
{
	getWindowManager()->process();
}

CWindow*			IMGF::getActiveWindow(void)
{
	return BXGX::get()->getActiveWindow();
}

CEditorTab*			IMGF::getActiveTab(void)
{
	CMainWindow *pIMGFWindow = (CMainWindow*) BXGX::get()->getEntryByIndex(0);
	CIMGEditor *pIMGEditor = (CIMGEditor*) pIMGFWindow->getEntryByIndex(0);
	CEditorTab *pEditorTab = pIMGEditor->getActiveTab();
	return pEditorTab;
}

CIMGEditor*			IMGF::getIMGEditor(void)
{
	CMainWindow *pIMGFWindow = (CMainWindow*) BXGX::get()->getEntryByIndex(0);
	CIMGEditor *pIMGEditor = (CIMGEditor*) pIMGFWindow->getEntryByIndex(0);
	return pIMGEditor;
}

CIMGEditorTab*		IMGF::getEntryListTab(void)
{
	CMainWindow *pIMGFWindow = (CMainWindow*) BXGX::get()->getEntryByIndex(0);
	CIMGEditor *pIMGEditor = (CIMGEditor*) pIMGFWindow->getEntryByIndex(0);
	CIMGEditorTab *pIMGEditorTab = (CIMGEditorTab*) pIMGEditor->getTabs().getEntryByIndex(0);
	return pIMGEditorTab;
}

// last used directory
void				IMGF::setLastUsedDirectory(string strHandleName, string strDirectory)
{
	// todo - remove after CTaskDispatchManager is done
}
string				IMGF::getLastUsedDirectory(string strHandleName)
{
	return ""; // todo - remove after CTaskDispatchManager is done
}