#pragma warning(disable : 4005)

#include "CIMGF.h"
#include "Format/RenderWare/Helper/BinaryStream/CRWManager.h"
#include "Format/RenderWare/Helper/BinaryStream/CRWVersionManager.h"
#include "Format/RAGE/CRageManager.h"
#include "Recently Open/CRecentlyOpenManager.h"
#include "Session/CSessionManager.h"
#include "CPopupGUIManager.h"
#include "CLSTProcessingManager.h"
#include "Task/CTaskManager.h"
#include "Task/CTaskDispatchManager.h"
#include "CSettingsManager.h"
#include "Sort/CSortManager.h"
#include "Format/RockstarGames/IMG/CIMGManager.h"
#include "Event/CEventManager.h"
#include "Event/eEvent.h"
#include "GUI/CGUIManager.h"
#include "Window/CWindow.h"
#include "Controls/CTextControl.h"
#include "Controls/CListControl.h"
#include "Controls/CButtonControl.h"
#include "Controls/CCheckControl.h"
#include "Controls/CDropControl.h"
#include "Controls/CScrollControl.h"
#include "Controls/CProgressControl.h"
#include "Controls/CRadioControl.h"
#include "Controls/CEditControl.h"
#include "GUI/CWindowManager.h"
#include "GUI/Editors/CIMGEditor.h"
#include "GUI/Editors/Tab/CIMGEditorTab.h"
#include "Type/String/CString2.h"
#include "File/CFileManager.h"
#include "Path/CPathManager.h"
#include "Registry/CRegistryManager.h"
#include "Drag Drop/CDropTarget.h"
#include "DB/CDBManager.h"
#include "DB/CDBFormat.h"
#include "Debug/CDebug.h"
#include "Format/RockstarGames/IMG/CIMGEntry.h"
#include "Format/RockstarGames/COL/CCOLManager.h"
#include "Format/RockstarGames/COL/CCOLVersionManager.h"
#include "Format/RockstarGames/COL/CCOLVersion.h"
#include "GUI/CGUIManager.h"
#include "CSearchEntry.h"
#include "Entry Viewer/CEntryViewerManager.h"
#include "Type/StdVector/CStdVector.h"
#include "Update/CUpdateManager.h"
#include "buildnumber.h"
#include "Compression/eCompressionAlgorithm.h"
#include "Format/RockstarGames/DAT/Loader/CDATLoaderManager.h"
#include "Format/RockstarGames/DAT/Path/CDATPathManager.h"
#include "Localization/CLocalizationManager.h"
#include "Language/CLanguageManager.h"
#include "Format/Image/BMP/CBMPManager.h"
#include "Format/Image/CUR/CCURManager.h"
#include "Format/RockstarGames/DFF/CDFFManager.h"
#include "DB/CDBManager.h"
#include "GUI/CGUIManager.h"
#include "Format/Image/ICO/CICOManager.h"
#include "Format/RockstarGames/IDE/CIDEManager.h"
#include "Image/CImageManager.h"
#include "Format/RockstarGames/IPL/CIPLManager.h"
#include "LST/CLSTManager.h"
#include "Format/RockstarGames/TXD/CTXDManager.h"
#include "Format/RockstarGames/WDR/CWDRManager.h"
#include "Format/RockstarGames/WTD/CWTDManager.h"
#include "Localization/eLanguage.h"
#include "Language/CLanguage.h"
#include "Collection/Game/CGameManager.h"
#include "Platform/Hardware/CPlatformManager.h"
#include "Format/RenderWare/Helper/BinaryStream/CRWSection.h"
#include "Timing/CTiming.h"
#include "CLastUsedValueManager.h"
#include "GUI/Window/CIMGFWindow.h"
#include "GUI/ThemeDesigner/CThemeDesigner.h"

using namespace std;
using namespace mcore;

// construct/destruct
CIMGF::CIMGF(void)
{
	// construct objects stored by CIMGF
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
	m_pThemeDesigner		= new CThemeDesigner;
}
CIMGF::~CIMGF(void)
{
	// destruct objects stored by CIMGF
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
	delete m_pThemeDesigner;
}

// init/uninit (ocurs in original thread)
void				CIMGF::init(void)
{
	m_pWindowManager->init();
	m_pThemeDesigner->init();
	initInitializationThread();
}

void				CIMGF::uninit(void)
{
}

// init tasks (ocurs in original thread)
void				CIMGF::initInitializationThread(void)
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
	((CIMGF*)pThreadParameter)->_init();
	return 0;
}

void				CIMGF::_init(void)
{
	initBuildMeta();
	initInstallationMeta();
	initStoredObjects();
	initSingletonObjects();
	initStaticData();
	initEventBinding();
	initSettings();
	initLocalization();
	initSorting();
	initOldVersionMigration();
	initTempStuff();
	initCommandLine();
	initAutoUpdateCheck();
}

// init tasks (occurs in different thread)
void				CIMGF::initBuildMeta(void)
{
	getBuildMeta().setCurrentVersion(1.3f);
	getBuildMeta().setIsAlphaBuild(true);
	getBuildMeta().setCurrentVersionString("1.3" + string(getBuildMeta().isAlphaBuild() ? " Alpha" : ""));
}

void				CIMGF::initInstallationMeta(void)
{
	// choose installation folder
	string strInstallationPath = CRegistryManager::getSoftwareValueString("IMGF\\InternalSettings", "InstallationPath");
	if (strInstallationPath == "")
	{
		string strPotentialInstallationPath = "C:\\Program Files (x86)\\IMGF\\" + getIMGF()->getBuildMeta().getCurrentVersionString() + "\\";
		if (CFileManager::doesFolderExist(strPotentialInstallationPath))
		{
			strInstallationPath = strPotentialInstallationPath;
			CRegistryManager::setSoftwareValueString("IMGF\\InternalSettings", "InstallationPath", strPotentialInstallationPath);
		}
		else
		{
			//string strChosenInstallationFolder = mcore::CGUIManager::chooseFolderDialog(getDialog()->GetSafeHwnd(), CLocalizationManager::getInstance()->getTranslatedText("ChooseFolderPopup_11"), getIMGF()->getLastUsedDirectory("INSTALLATION"));
			string strChosenInstallationFolder = mcore::CGUIManager::chooseFolderDialog(getActiveWindow()->getWindowHandle(), "Choose the installation folder for IMGF. (e.g. In program files x86)", getIMGF()->getLastUsedDirectory("INSTALLATION"));
			if (strChosenInstallationFolder == "")
			{
			}
			else
			{
				strInstallationPath = strChosenInstallationFolder;
				getIMGF()->setLastUsedDirectory("INSTALLATION", strChosenInstallationFolder);
				CRegistryManager::setSoftwareValueString("IMGF\\InternalSettings", "InstallationPath", strChosenInstallationFolder);
			}
		}
	}
}

void				CIMGF::initStoredObjects(void)
{
	// initialize objects stored by CIMGF
	// Excludes: CWindowManager and CSortManager
	m_pEntryViewerManager->init();
	m_pPopupGUIManager->init();
	m_pLanguageManager->init();
	m_pLSTProcessingManager->init();
	m_pRecentlyOpenManager->init();
	m_pTaskManager->init();
	m_pSessionManager->init();
	m_pSettingsManager->init();
	m_pUpdateManager->init();
}

void				CIMGF::initSingletonObjects(void)
{
	// initialize singleton objects
	CBMPManager::getInstance()->init();
	CCOLManager::getInstance()->init();
	CCURManager::getInstance()->init();
	CDATLoaderManager::getInstance()->init();
	CDATPathManager::getInstance()->init();
	CDBManager::getInstance()->init();
	CDFFManager::getInstance()->init();
	CGameManager::getInstance()->init();
	gui::CGUIManager::getInstance()->init();
	CICOManager::getInstance()->init();
	CIDEManager::getInstance()->init();
	CImageManager::getInstance()->init();
	CIMGManager::getInstance()->init();
	CIPLManager::getInstance()->init();
	CLSTManager::getInstance()->init();
	CPlatformManager::getInstance()->init();
	CRageManager::getInstance()->init();
	CRWManager::getInstance()->init();
	CTXDManager::getInstance()->init();
	CWDRManager::getInstance()->init();
	CWTDManager::getInstance()->init();
}

void				CIMGF::initStaticData(void)
{
	CRWSection::initStatic();
}

void				CIMGF::initEventBinding(void)
{
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
	
	CEventManager::getInstance()->bindEvent(EVENT_onTaskProgress,				pOnTaskProgress);
	CEventManager::getInstance()->bindEvent(EVENT_onParseIMGEntry,				pOnTaskProgress);
	CEventManager::getInstance()->bindEvent(EVENT_onStoreIMGEntry,				pOnTaskProgress);
	CEventManager::getInstance()->bindEvent(EVENT_onAddIMGEntryExtension,		pOnEntriesExtensionChange);
	CEventManager::getInstance()->bindEvent(EVENT_onRemoveIMGEntryExtension,	pOnEntriesExtensionChange);
}

void				CIMGF::initSettings(void)
{
	getSettingsManager()->loadSettings();
}

void				CIMGF::initLocalization(void)
{
	eLanguage eActiveLanguage = (eLanguage)getIMGF()->getSettingsManager()->getSettingInt("Language");
	CLocalizationManager::getInstance()->setActiveLanguage(eActiveLanguage);
	CLocalizationManager::getInstance()->setActiveLanguageName(getIMGF()->getLanguageManager()->getLanguageById(eActiveLanguage)->getLanguageName());
	CLocalizationManager::getInstance()->setInstallationPath(CRegistryManager::getSoftwareValueString("IMGF\\InternalSettings", "InstallationPath"));
	CLocalizationManager::getInstance()->loadTranslatedText();
}

void				CIMGF::initSorting(void)
{
	m_pSortManager->init();
}

void				CIMGF::initOldVersionMigration(void)
{
	// delete previous version's exe file
	string strPreviousVersionExePath = CRegistryManager::getSoftwareValueString("IMGF\\InternalSettings", "DeletePreviousVersionOnNextLaunch");
	if (strPreviousVersionExePath != "")
	{
		int iResult;
		bool bFileExists;
		uint32 uiIterationCount = 0;
		do
		{
			bFileExists = CFileManager::doesFileExist(strPreviousVersionExePath);
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
		CRegistryManager::removeSoftwareValue("IMGF\\InternalSettings", "DeletePreviousVersionOnNextLaunch");
	}
}

void				CIMGF::initCommandLine(void)
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
		getTaskManager()->getDispatch()->onRequestOpen2(strPath);
	}
}

void				CIMGF::initAutoUpdateCheck(void)
{
	/*
	todo
	This currently calls a onRequestBlah which eventualls calls CTaskManager::onFeatureEnd which can crash before the CIMGEditor object has been created.
	So move this to like lambda: onWindowOpen()
	getIMGF()->getTaskManager()->getDispatch()->onRequestAutoUpdate();
	*/
}

void				CIMGF::initTempStuff(void)
{
}

// windows/tabs
void				CIMGF::openWindow(void)
{
	getWindowManager()->openWindow();
	CEventManager::getInstance()->triggerEvent(EVENT_onToolReady);
}

void				CIMGF::processWindows(void)
{
	getWindowManager()->processWindows();
}

CWindow*			CIMGF::getActiveWindow(void)
{
	return gui::CGUIManager::getInstance()->getActiveWindow();
}

CEditorTab*			CIMGF::getActiveTab(void)
{
	CIMGFWindow *pIMGFWindow = (CIMGFWindow*) gui::CGUIManager::getInstance()->getEntryByIndex(0);
	CIMGEditor *pIMGEditor = (CIMGEditor*) pIMGFWindow->getEntryByIndex(0);
	CEditorTab *pEditorTab = pIMGEditor->getActiveTab();
	return pEditorTab;
}

CIMGEditor*			CIMGF::getIMGEditor(void)
{
	CIMGFWindow *pIMGFWindow = (CIMGFWindow*) gui::CGUIManager::getInstance()->getEntryByIndex(0);
	CIMGEditor *pIMGEditor = (CIMGEditor*) pIMGFWindow->getEntryByIndex(0);
	return pIMGEditor;
}

CIMGEditorTab*		CIMGF::getEntryListTab(void)
{
	CIMGFWindow *pIMGFWindow = (CIMGFWindow*) gui::CGUIManager::getInstance()->getEntryByIndex(0);
	CIMGEditor *pIMGEditor = (CIMGEditor*) pIMGFWindow->getEntryByIndex(0);
	CIMGEditorTab *pIMGEditorTab = (CIMGEditorTab*) pIMGEditor->getTabs().getEntryByIndex(0);
	return pIMGEditorTab;
}

// last used directory
void				CIMGF::setLastUsedDirectory(string strHandleName, string strDirectory)
{
	CRegistryManager::setSoftwareValueString("IMGF\\LastUsedDirectories", strHandleName, strDirectory);
}
string				CIMGF::getLastUsedDirectory(string strHandleName)
{
	return CRegistryManager::getSoftwareValueString("IMGF\\LastUsedDirectories", strHandleName);
}