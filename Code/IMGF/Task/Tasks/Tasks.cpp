#pragma warning(disable : 4005)

#include "Tasks.h"
#include "Task/TaskManager.h"
#include "IMGF.h"
#include "Globals.h"
#include "GUI/Window/WindowManager.h"
#include "GUI/Window/Windows/MainWindow/MainWindow.h"
#include "Static/Input.h"
#include "Static/String.h"
#include "Static/StdVector.h"
#include "Static/Path.h"
#include "Static/File.h"
#include "Static/Registry.h"
#include "Window/Window.h"
#include "GUI/Editor/Editors/IMGEditor.h"
#include "GUI/Editor/Editors/Tab/IMGEditorTab.h"
#include "Format/IMG/Regular/IMGManager.h"
#include "Format/IMG/Regular/IMGFormat.h"
#include "Format/IMG/Regular/IMGEntry.h"
#include "Format/IDE/IDEManager.h"
#include "Format/IPL/IPLManager.h"
#include "Format/COL/COLManager.h"
#include "Format/COL/COLFormat.h"
#include "Format/COL/COLEntry.h"
#include "DragDrop/DropTarget.h"
#include "Format/TXD/TXDManager.h"
#include "Format/TXD/TXDFormat.h"
#include "Format/RW/Sections/RWSection_TextureNative.h"
#include "Format/DFF/DFFManager.h"
#include "Format/DFF/DFFFormat.h"
#include "Format/RW/TextureEntry.h"
#include "Format/DAT/Loader/DATLoaderManager.h"
#include "Format/DAT/Path/DATPathManager.h"
#include "Format/DAT/Loader/DATLoaderFormat.h"
#include "Format/DAT/Loader/DATLoaderEntry.h"
#include "Format/Image/BMP/BMPManager.h"
#include "Format/Image/BMP/BMPFormat.h"
#include "Engine/RW/RWVersion.h"
#include "LST/LSTManager.h"
#include "LST/LSTFormat.h"
#include "LST/LSTSection.h"
#include "LST/LSTEntry.h"
#include "Static/Debug.h"
#include "Engine/RW/RWManager.h"
#include "Task/Base/ETask.h"
#include "Task/Repeat/LastUsedValueManager.h"
#include "Task/Tasks/RecentlyOpen/RecentlyOpenManager.h"
#include "Task/Tasks/Session/SessionManager.h"
#include "Task/Tasks/LST/LSTProcessingManager.h"
#include "Task/Tasks/Dump/DumpManager.h"
#include "Task/Tasks/Sort/SortManager.h"
#include "Task/Tasks/Sort/SortPriority.h"
#include "Task/Tasks/Find/SearchEntry.h"
#include "Task/Tasks/Sort/SortPriorities.h"
#include "Task/Tasks/Renamer/RenamedIMGEntry.h"
#include "Settings/SettingsManager.h"
#include "Protocol/HTTP.h"
#include "DB/DBManager.h"
#include "DB/DBFormat.h"
#include "Image/RasterDataFormat.h"
#include "Engine/RW/RWVersionManager.h"
#include "EntryViewer/EntryViewerManager.h"
#include "Format/IDE/IDEFormat.h"
#include "Format/IDE/IDEEntry.h"
#include "Format/IDE/Entry/DataEntry/IDEEntry_OBJS.h"
#include "Format/IDE/Entry/DataEntry/IDEEntry_TOBJ.h"
#include "Format/IDE/Entry/DataEntry/IDEEntry_ANIM.h"
#include "Format/IDE/Entry/DataEntry/IDEEntry_CARS.h"
#include "Format/IDE/Entry/DataEntry/IDEEntry_HAND.h"
#include "Format/IDE/Entry/DataEntry/IDEEntry_HIER.h"
#include "Format/IDE/Entry/DataEntry/IDEEntry_PATH.h"
#include "Format/IDE/Entry/DataEntry/IDEEntry_PEDS.h"
#include "Format/IDE/Entry/DataEntry/IDEEntry_TXDP.h"
#include "Format/IDE/Entry/DataEntry/IDEEntry_WEAP.h"
#include "Format/IDE/Entry/DataEntry/2DFX/IDEEntry_2DFX_Light.h"
#include "Format/IDE/Entry/DataEntry/2DFX/IDEEntry_2DFX_Particle.h"
#include "Format/IDE/Entry/DataEntry/2DFX/IDEEntry_2DFX_Ped.h"
#include "Format/IDE/Entry/DataEntry/2DFX/IDEEntry_2DFX_SunReflection.h"
#include "Format/IDE/Entry/DataEntry/2DFX/IDEEntry_2DFX_Unknown1.h"
#include "Format/IPL/IPLFormat.h"
#include "Format/IPL/IPLEntry.h"
#include "Format/IPL/Entry/DataEntry/IPLEntry_INST.h"
#include "Format/IPL/Entry/DataEntry/IPLEntry_AUZO.h"
#include "Format/IPL/Entry/DataEntry/IPLEntry_CARS.h"
#include "Format/IPL/Entry/DataEntry/IPLEntry_CULL.h"
#include "Format/IPL/Entry/DataEntry/IPLEntry_ENEX.h"
#include "Format/IPL/Entry/DataEntry/IPLEntry_GRGE.h"
#include "Format/IPL/Entry/DataEntry/IPLEntry_JUMP.h"
#include "Format/IPL/Entry/DataEntry/IPLEntry_MULT.h"
#include "Format/IPL/Entry/DataEntry/IPLEntry_MZON.h"
#include "Format/IPL/Entry/DataEntry/IPLEntry_OCCL.h"
#include "Format/IPL/Entry/DataEntry/IPLEntry_PATH.h"
#include "Format/IPL/Entry/DataEntry/IPLEntry_PICK.h"
#include "Format/IPL/Entry/DataEntry/IPLEntry_TCYC.h"
#include "Format/IPL/Entry/DataEntry/IPLEntry_ZONE.h"
#include "Format/RW/Entries/2dEffects/RWEntry_2dEffect_CoverPoint.h"
#include "Format/RW/Entries/2dEffects/RWEntry_2dEffect_EnterExit.h"
#include "Format/RW/Entries/2dEffects/RWEntry_2dEffect_Escalator.h"
#include "Format/RW/Entries/2dEffects/RWEntry_2dEffect_Light.h"
#include "Format/RW/Entries/2dEffects/RWEntry_2dEffect_ParticleEffect.h"
#include "Format/RW/Entries/2dEffects/RWEntry_2dEffect_PedAttractor.h"
#include "Format/RW/Entries/2dEffects/RWEntry_2dEffect_SlotmachineWheel.h"
#include "Format/RW/Entries/2dEffects/RWEntry_2dEffect_StreetSign.h"
#include "Format/RW/Entries/2dEffects/RWEntry_2dEffect_SunGlare.h"
#include "Updater/UpdateManager.h"
#include "Updater/UpdateConnectionManager.h"
#include "Updater/UpdateConnection.h"
#include "Format/COL/COLVersionManager.h"
#include "Format/COL/COLVersion.h"
#include "Static/Math.h"
#include "Static/Process.h"
#include "Format/RW/Sections/RWSection_Geometry.h"
#include "Format/RW/Sections/RWSection_String.h"
#include "Format/RW/Sections/RWSection_Texture.h"
#include "Format/RW/Sections/RWSection_Material.h"
#include "Format/RW/Sections/RWSection_2dEffect.h"
#include "Format/WDR/WDRManager.h"
#include "Format/WDR/WDRFormat.h"
#include "Format/WTD/WTDManager.h"
#include "Format/WTD/WTDFormat.h"
#include "Intermediate/Texture/IntermediateTextureFormat.h"
#include "Format/DAT/Path/DATPathFormat.h"
#include "Localization/LocalizationManager.h"
#include "EntryViewer/TextureViewer.h"
#include "EntryViewer/CollisionViewer.h"
#include "Game/EGame.h"
#include "Stream/DataReader.h"
#include "Control/Controls/ProgressBar.h"
#include "Control/Controls/Grid.h"
#include "Control/Controls/DropDown.h"
#include "Control/Controls/TextBox.h"
#include "Format/GameFormat.h"
#include "Format/Text/INI/INIManager.h"
#include "Static/AppDataPath.h"
#include "Static/DataPath.h"
#include "Layer/Layers/NumericMultiOptionInputLayerResult.h"
#include "Pool/VectorPool.h"
#include "Game/GameManager.h"
#include "Image/ImageManager.h"
#include "Image/RasterDataFormatManager.h"
#include <gdiplus.h>
#include <stdio.h>
#include <algorithm>

using namespace std;
using namespace bxcf;
using namespace bxgx;
using namespace bxgi;
using namespace imgf;
using namespace imgf::task;

Tasks::Tasks(void) :
	m_pMainWindow(nullptr),
	m_pTaskManager(nullptr)
{
}

// main interface
void		Tasks::init(void)
{
	m_pMainWindow = g_pIMGF->getWindowManager()->getMainWindow();
	m_pTaskManager = g_pIMGF->getTaskManager();

	bindEvent(TASK_PROGRESS, &Tasks::onProgressTask);
}

void		Tasks::uninit(void)
{
}

// task
string&		Tasks::getTaskName(void)
{
	return g_pIMGF->getTaskManager()->getTaskName();
}

void		Tasks::onStartTask(string strTaskName)
{
	m_pTaskManager->onStartTask(strTaskName);
}

void		Tasks::onCompleteTask(void)
{
	m_pTaskManager->onCompleteTask();
}

void		Tasks::onAbortTask(void)
{
	m_pTaskManager->onAbortTask();
}

void		Tasks::onProgressTask(void)
{
	if (getTaskName() == "exportAll")
	{
		//increaseProgress();
	}
}

// file/folder input windows
vector<string>	Tasks::openFile(string strExtensionFilters, bool bAllowMultiSelect, string strDefaultFileName)
{
	m_pTaskManager->onPauseTask();
	vector<string> vecFilePaths = Input::openFile(getTaskName(), strExtensionFilters, bAllowMultiSelect, strDefaultFileName);
	m_pTaskManager->onResumeTask();
	return vecFilePaths;
}

string			Tasks::saveFile(string strExtensionFilters, string strDefaultFileName)
{
	m_pTaskManager->onPauseTask();
	string strFilePath = Input::saveFile(getTaskName(), strExtensionFilters, strDefaultFileName);
	m_pTaskManager->onResumeTask();
	return strFilePath;
}

string			Tasks::openFolder(string strTitle, string strInitialDir)
{
	m_pTaskManager->onPauseTask();
	string strFolderPath = Input::openFolder(strTitle, getTaskName());
	m_pTaskManager->onResumeTask();
	return strFolderPath;
}

string			Tasks::saveFolder(string strTitle, string strInitialDir)
{
	m_pTaskManager->onPauseTask();
	string strFolderPath = Input::saveFolder(strTitle, getTaskName());
	m_pTaskManager->onResumeTask();
	return strFolderPath;
}

// active tab
EditorTab*		Tasks::getTab(void)
{
	return nullptr;
	// todo - return m_pMainWindow->getActiveEditor()->getActiveTab();
}

IMGEditorTab*	Tasks::getIMGTab(void)
{
	return m_pMainWindow->getIMGEditor()->getActiveTab();
}

// progress
void			Tasks::setMaxProgress(uint32 uiMaxProgress, bool bResetCurrent)
{
	getIMGF()->getTaskManager()->setTaskMaxProgressTickCount(uiMaxProgress, bResetCurrent);
}

void			Tasks::increaseProgress(void)
{
	getIMGF()->getTaskManager()->onTaskProgressTick();
}





// tasks
void		Tasks::newFile(void)
{
	onStartTask("newFile");

	string strNewIMGFilePath = DataPath::getDataPath() + "New/IMG/New.img";
	strNewIMGFilePath = File::getNextIncrementingFileName(strNewIMGFilePath);

	File::createFoldersForPath(strNewIMGFilePath);

	EIMGVersion uiIMGVersion = IMG_1;
	getIMGF()->getIMGEditor()->addBlankFile(strNewIMGFilePath, uiIMGVersion);

	onCompleteTask();
}

void		Tasks::newWindow(void)
{
	onStartTask("newWindow");

	Process::startProcess(Process::getEXEFilePath());

	onCompleteTask();
}

void		Tasks::chooseFilesToOpen(void)
{
	onStartTask("chooseFilesToOpen");

	vector<string> vecFilePaths = openFile("img,dir");
	if (vecFilePaths.size() == 0)
	{
		return m_pTaskManager->onAbortTask();
	}

	for (string& strFilePath : vecFilePaths)
	{
		_openFile(strFilePath);
	}

	onCompleteTask();
}

void		Tasks::_openFile(string& strFilePath)
{
	onStartTask("openFile");

	string strExtensionUpper = String::toUpperCase(Path::getFileExtension(strFilePath));
	/*
	todo - use this code
	CUnknownFormat unknownFormatFile;
	bool bUseExistingFileHandle = false;
	if (strExtensionUpper == "")
	{
		unknownFormatFile.open(strFilePath);
		uint32 uiFormatId = unknownFormatFile.getFormat();
		if (uiFormat == -1)
		{
			unknownFormatFile.close();
			Input::showMessage("Unable to detect file format.\r\n\r\n" + strFilePath, "Unknown File Format");
			return m_pTaskManager->onAbortTask();
		}

		bUseExistingFileHandle = true;
		if (uiFormatId == 0) // IMG format
		{
			strExtensionUpper = "DIR";
		}
	}
	*/

	if (strExtensionUpper == "IMG" || strExtensionUpper == "DIR")
	{
		// IMG or DIR
		/*
		// todo
		DataReader reader(strFilePath);
		IMGFormat *img = new IMGFormat(reader);
		*/

		/*
		// todo
		if (bUseExistingFileHandle)
		{
			img.setFileHandle(unknownFormatFile.getHandle());
		}
		else
		{
		}
		*/

		if (!m_pMainWindow->getIMGEditor()->addFile(strFilePath))
		{
			return onAbortTask();
		}
	}
	else
	{
		if (strExtensionUpper == "")
		{
			Input::showMessage("File doesn't have an extension.\r\n\r\n" + strFilePath, "Format Not Detected");
		}
		else
		{
			Input::showMessage(strExtensionUpper + " files are not supported.\r\n\r\n" + strFilePath, "Format Not Supported");
		}
		return onAbortTask();
	}

	onCompleteTask();
}

void		Tasks::chooseFolderToOpen(void)
{
	onStartTask("chooseFolderToOpen");

	string strFolderPath = openFolder("Choose a folder to open IMG files from.");
	if (strFolderPath == "")
	{
		return m_pTaskManager->onAbortTask();
	}

	vector<string> vecFileNames = File::getFileNames(strFolderPath);
	for (string& strFileName : vecFileNames)
	{
		string strFileExtension = String::toUpperCase(Path::getFileExtension(strFileName));
		if (strFileExtension == "IMG" || strFileExtension == "DIR")
		{
			_openFile(strFolderPath + strFileName);
		}
	}

	onCompleteTask();
}

void		Tasks::openFolderRecursively(void)
{
	onStartTask("openFolderRecursively");

	string strFolderPath = openFolder("Choose a folder to recursively open IMG files from.");
	if (strFolderPath == "")
	{
		return m_pTaskManager->onAbortTask();
	}

	/*
	todo - add to File:
	getFolderNamesInFolder()
	getFileNamesInFolder(string strExtensionFilters = "")
	getFolderPathsInFolder()
	getFilePathsInFolder(string strExtensionFilters = "")
	getFolderNamesInFolderDeep()
	getFileNamesInFolderDeep(string strExtensionFilters = "")
	getFolderPathsInFolderDeep()
	getFilePathsInFolderDeep(string strExtensionFilters = "")
	*/

	vector<string> vecFilePaths = File::getFilePaths(strFolderPath, true, false, "img,dir", true);
	for (string& strFilePath : vecFilePaths)
	{
		_openFile(strFilePath);
	}

	onCompleteTask();
}

void		Tasks::reopenFile(void)
{
	onStartTask("reopenFile");

	string strFilePath = getIMGTab()->getIMGFile()->getFilePath();

	m_pMainWindow->getIMGEditor()->removeActiveFile();
	m_pMainWindow->getIMGEditor()->addFile(strFilePath);

	onCompleteTask();
}

void		Tasks::openLastClosedFile(void)
{
	onStartTask("onRequestOpenLast");

	uint32 uiRecentlyOpenedCount = String::toUint32(INIManager::getItem(AppDataPath::getRecentlyOpenedPath(), "RecentlyOpened", "Count"));
	if (uiRecentlyOpenedCount > 0)
	{
		string strFilePath = INIManager::getItem(AppDataPath::getRecentlyOpenedPath(), "RecentlyOpened", String::toString(uiRecentlyOpenedCount));
		m_pMainWindow->getIMGEditor()->addFile(strFilePath);
	}
	
	onCompleteTask();
}

void		Tasks::openFileFolderInExplorer(void)
{
	onStartTask("openFileFolderInExplorer");

	string strFolderPath = Path::getDirectory(getIMGTab()->getIMGFile()->getFilePath());
	Process::openFolder(strFolderPath);

	onCompleteTask();
}

void		Tasks::clearRecentlyOpenFiles(void)
{
	onStartTask("clearRecentlyOpenFiles");

	getIMGF()->getRecentlyOpenManager()->removeRecentlyOpenedEntries();

	onCompleteTask();
}

void		Tasks::openTodaysLogsFile(void)
{
	onStartTask("openTodaysLogsFile");

	string strLogsFolderPath = getIMGF()->getSettingsManager()->getSetting("LogsFolderPath");
	if (strLogsFolderPath == "")
	{
		Input::showMessage("The folder for saving logs to file is not set, please choose this in Settings first.", "Save Logs Folder Not Set", MB_OK);
		return onAbortTask();
	}

	string strLogsFilePath = strLogsFolderPath + String::getDateTextForFolder() + ".txt";

	if (!File::doesFileExist(strLogsFilePath))
	{
		Input::showMessage("File does not exist:\n\n" + strLogsFilePath, "File Doesn't Exist", MB_OK);
		return onAbortTask();
	}

	Process::openTextFile(strLogsFilePath);

	onCompleteTask();
}

void		Tasks::openLogsFolder(void)
{
	onStartTask("openLogsFolder");

	string strLogsFolderPath = getIMGF()->getSettingsManager()->getSetting("LogsFolderPath");
	if (strLogsFolderPath == "")
	{
		Input::showMessage("The folder for saving logs to file is not set, please choose this in Settings first.", "Save Logs Folder Not Set", MB_OK);
		return onAbortTask();
	}

	if (!File::doesFolderExist(strLogsFolderPath))
	{
		Input::showMessage("Folder does not exist:\n\n" + strLogsFolderPath, "Folder Doesn't Exist", MB_OK);
		return onAbortTask();
	}

	Process::openFolder(strLogsFolderPath);

	onCompleteTask();
}

void		Tasks::_saveFile(void)
{
	onStartTask("saveFile");

	setMaxProgress(getIMGTab()->getIMGFile()->getEntryCount() * 2);

	getIMGTab()->getIMGFile()->serialize();

	getIMGTab()->logf("Saved %s.", Path::getFileName(getIMGTab()->getIMGFile()->getIMGFilePath()).c_str());

	onCompleteTask();
}

void		Tasks::saveFileAs(void)
{
	onStartTask("saveFileAs");

	string strNewFilePath = saveFile("img,dir", "New IMG Name.IMG");
	if (strNewFilePath == "")
	{
		return onAbortTask();
	}

	setMaxProgress(getIMGTab()->getIMGFile()->getEntryCount() * 2);

	getIMGTab()->getIMGFile()->serialize(strNewFilePath);

	getIMGTab()->logf("Saved as %s.", Path::getFileName(strNewFilePath).c_str());

	onCompleteTask();
}

void		Tasks::saveAllFiles(void)
{
	onStartTask("saveAllFiles");

	uint32 uiEntryCountAllTabs = 0;
	for (IMGEditorTab *pIMGEditorTab : m_pMainWindow->getIMGEditor()->getIMGTabs().getEntries())
	{
		uiEntryCountAllTabs += pIMGEditorTab->getIMGFile()->getEntryCount();
	}
	setMaxProgress(uiEntryCountAllTabs * 2);

	for (IMGEditorTab *pIMGEditorTab : m_pMainWindow->getIMGEditor()->getIMGTabs().getEntries())
	{
		pIMGEditorTab->getIMGFile()->serialize();

		pIMGEditorTab->log("Saved all IMGs.");
	}

	onCompleteTask();
}

void		Tasks::cloneFile(void)
{
	onStartTask("cloneFile");

	IMGFormat *pIMGFile = getIMGTab()->getIMGFile();

	string strIMGFileExtension = Path::getFileExtension(pIMGFile->getIMGFilePath());
	string strClonedIMGPath = Path::getDirectory(pIMGFile->getIMGFilePath()) + Path::removeFileExtension(Path::getFileName(pIMGFile->getIMGFilePath())) + "-cloned." + strIMGFileExtension;
	strClonedIMGPath = File::getNextIncrementingFileName(strClonedIMGPath);

	pIMGFile->serialize(strClonedIMGPath);

	getIMGTab()->logf("Cloned into %s.", Path::getFileName(strClonedIMGPath).c_str());

	setMaxProgress(pIMGFile->getEntryCount() * 2);
	m_pMainWindow->getIMGEditor()->addFile(strClonedIMGPath);

	onCompleteTask();
}

void		Tasks::saveFileGroup(void)
{
	onStartTask("saveFileGroup");

	string strFileGroupName = m_pMainWindow->showSingleLineTextBoxWindow("Choose File Group Name", "Choose a name for the file group.");
	if (strFileGroupName == "")
	{
		return onAbortTask();
	}
	else if (String::isIn(strFileGroupName, ";"))
	{
		Input::showMessage("The file group name cannot contain a semi colon (;).", "Invalid File Group Name", MB_OK);
		return onAbortTask();
	}

	vector<string> vecIMGFilePaths;
	for (IMGEditorTab *pEditorTab : m_pMainWindow->getIMGEditor()->getIMGTabs().getEntries())
	{
		vecIMGFilePaths.push_back(pEditorTab->getIMGFile()->getIMGFilePath());
	}

	getIMGF()->getSessionManager()->addSession(strFileGroupName, vecIMGFilePaths); // todo - rename SessionManager to FileGroupManager
	getIMGF()->getSessionManager()->loadSessions();

	for (IMGEditorTab *pEditorTab : m_pMainWindow->getIMGEditor()->getIMGTabs().getEntries())
	{
		pEditorTab->logf("Saved file group %s", strFileGroupName.c_str());
	}

	onCompleteTask();
}

void		Tasks::saveLogs(void)
{
	onStartTask("saveLogs");
	
	string strLogFilePath = saveFile("txt", "Saved Logs - " + Path::removeFileExtension(Path::getFileName(getIMGTab()->getIMGFile()->getFilePath())) + ".txt");
	if (strLogFilePath == "")
	{
		return onAbortTask();
	}

	File::setTextFile(strLogFilePath, String::join(getIMGTab()->getLog()->getTextLines(), "\n"));

	getIMGTab()->log("Saved logs.");

	onCompleteTask();
}

void		Tasks::saveLogsAllTabs(void)
{
	onStartTask("saveLogsAllTabs");

	string strLogFilePath = saveFile("txt", "Saved Logs All Tabs.txt");
	if (strLogFilePath == "")
	{
		return onAbortTask();
	}

	string strAllTabsLogs = "";
	for (IMGEditorTab *pEditorTab : m_pMainWindow->getIMGEditor()->getIMGTabs().getEntries())
	{
		strAllTabsLogs += "[[" + pEditorTab->getIMGFile()->getFilePath() + "]]\n\n" + String::join(pEditorTab->getLog()->getTextLines(), "\n") + "\n\n\n\n";

		pEditorTab->log("Saved logs for all tabs.");
	}

	File::setTextFile(strLogFilePath, strAllTabsLogs);
	
	onCompleteTask();
}

void			Tasks::clearLogs(void)
{
	onStartTask("clearLogs");

	getIMGTab()->clearLogs();

	getIMGTab()->logf("Cleared logs.");

	onCompleteTask();
}

void			Tasks::clearLogsAllTabs(void)
{
	onStartTask("clearLogsAllTabs");

	for (IMGEditorTab *pEditorTab : m_pMainWindow->getIMGEditor()->getIMGTabs().getEntries())
	{
		pEditorTab->clearLogs();

		pEditorTab->log("Cleared logs for all tabs.");
	}

	onCompleteTask();
}

void		Tasks::closeFile(void)
{
	onStartTask("closeFile");

	if (getIMGF()->getSettingsManager()->getSettingBool("RebuildConfirmationOnClose"))
	{
		if (Input::showMessage("Save file before closing?\n\n" + getIMGTab()->getIMGFile()->getIMGFilePath(), "Auto Save?") == 1)
		{
			saveAllOpenFiles(false);
		}
	}
	m_pMainWindow->getIMGEditor()->removeActiveFile();

	onCompleteTask();
}

void		Tasks::closeAllFiles(void)
{
	onStartTask("closeAllFiles");

	bool bConfirmOnClose = getIMGF()->getSettingsManager()->getSettingBool("RebuildConfirmationOnClose");

	vector<IMGEditorTab*> vecIMGTabs = m_pMainWindow->getIMGEditor()->getIMGTabs().getEntries();
	for (IMGEditorTab *pIMGEditorTab : vecIMGTabs)
	{
		if (bConfirmOnClose)
		{
			if (Input::showMessage("Save file before closing?\n\n" + pIMGEditorTab->getIMGFile()->getIMGFilePath(), "Auto Save?") == 1)
			{
				saveAllOpenFiles(false);
			}
		}
		m_pMainWindow->getIMGEditor()->removeFile(pIMGEditorTab);
	}

	onCompleteTask();
}

void		Tasks::exitTool(void)
{
	onStartTask("exitTool");

	ExitProcess(0);

	onCompleteTask();
}

void		Tasks::importByFiles(void)
{
	onStartTask("importByFiles");

	vector<string> vecFilePaths = openFile();
	if (vecFilePaths.size() == 0)
	{
		return onAbortTask();
	}

	setMaxProgress(vecFilePaths.size());

	for (string& strFilePath : vecFilePaths)
	{
		getIMGTab()->addFile(strFilePath);
		increaseProgress();
	}

	if (vecFilePaths.size() == 1)
	{
		getIMGTab()->logf("Added file %s.", Path::getFileName(vecFilePaths[0]).c_str());
	}
	else
	{
		getIMGTab()->logf("Added %u files.", vecFilePaths.size());
	}

	getIMGTab()->setIMGModifiedSinceRebuild(true);

	onCompleteTask();
}

void		Tasks::importBySingleFolder(void)
{
	onStartTask("importBySingleFolder");

	string strFolderPath = openFolder("Import files from a single folder.");
	if (strFolderPath == "")
	{
		return onAbortTask();
	}

	vector<string> vecFileNames = File::getFileNames(strFolderPath);
	setMaxProgress(vecFileNames.size());

	for (string& strFileName : vecFileNames)
	{
		getIMGTab()->addFile(strFolderPath + strFileName);
		increaseProgress();
	}

	if (vecFileNames.size() > 0)
	{
		getIMGTab()->setIMGModifiedSinceRebuild(true);
	}

	getIMGTab()->logf("Added %u files from folder %s.", vecFileNames.size(), Path::getFolderName(strFolderPath).c_str());

	onCompleteTask();
}

void		Tasks::importByFolderRecursively(void)
{
	onStartTask("importByFolderRecursively");

	string strFolderPath = openFolder("Import files from a folder recursively.");
	if (strFolderPath == "")
	{
		return onAbortTask();
	}

	vector<string> vecFilePaths = File::getFilePaths(strFolderPath, true, false, "", true);
	setMaxProgress(vecFilePaths.size());

	for (string& strFilePath : vecFilePaths)
	{
		getIMGTab()->addFile(strFilePath);
		increaseProgress();
	}

	if (vecFilePaths.size() > 0)
	{
		getIMGTab()->setIMGModifiedSinceRebuild(true);
	}

	getIMGTab()->logf("Added %u files recursively from folder %s.", vecFilePaths.size(), Path::getFolderName(strFolderPath).c_str());

	onCompleteTask();
}

void		Tasks::importByIDE(void)
{
	onStartTask("importByIDE");

	IDEInputWindowResult ideInputWindowResult = getIMGF()->getWindowManager()->showIDEInputWindow("Import into IMG by IDE", "Choose IDE items to import into the IMG:");
	if (getIMGF()->getWindowManager()->m_bWindow2Cancelled)
	{
		return onAbortTask();
	}

	vector<string> vecIDEFilePaths = openFile("IDE");
	if (vecIDEFilePaths.size() == 0)
	{
		return onAbortTask();
	}

	string strImportFolderPath = openFolder("Choose a folder to import file(s) from which are found in the IDE file:");
	if (strImportFolderPath == "")
	{
		return onAbortTask();
	}

	// fetch chosen IDE sections from input window
	vector<EIDESection>
		vecModelSections,
		vecTextureSections;
	ideInputWindowResult.getIDESections(vecModelSections, vecTextureSections);

	set<string>
		stModelNames,
		stTextureSetNames;
	IDEManager::getModelAndTextureSetNamesFromFiles(vecIDEFilePaths, stModelNames, stTextureSetNames, vecModelSections, vecTextureSections);

	vector<string> vecAllIDEEntryNames;
	for (const string& strModelName : stModelNames)
	{
		vecAllIDEEntryNames.push_back(strModelName + ".DFF");
	}
	for (const string& strTextureSetName : stTextureSetNames)
	{
		vecAllIDEEntryNames.push_back(strTextureSetName + ".TXD");
	}
	vecAllIDEEntryNames = StdVector::toUpperCase(vecAllIDEEntryNames);
	vecAllIDEEntryNames = StdVector::removeDuplicates(vecAllIDEEntryNames);

	setMaxProgress(vecAllIDEEntryNames.size());
	uint32 uiImportCount = 0;
	for (string& strIDEEntryName : vecAllIDEEntryNames)
	{
		string strEntryFilePath = strImportFolderPath + strIDEEntryName;
		if (File::doesFileExist(strEntryFilePath))
		{
			uiImportCount++;
			getIMGTab()->addFile(strEntryFilePath);
		}

		increaseProgress();
	}

	if (uiImportCount > 0)
	{
		getIMGTab()->setIMGModifiedSinceRebuild(true);
	}

	getIMGTab()->logf("Imported %u entries by %u IDE files.", vecAllIDEEntryNames.size(), vecIDEFilePaths.size());

	onCompleteTask();
}

void		Tasks::importByEntryNames(void)
{
	onStartTask("importByEntryNames");

	string strInputEntryNames = m_pMainWindow->showMultiLineTextBoxWindow("Import by Entry Names", "Choose entry names to import, 1 per line.");
	if (strInputEntryNames == "")
	{
		return onAbortTask();
	}

	string strFolderPath = openFolder("Choose a folder to import the entries by entry name from.");
	if (strFolderPath == "")
	{
		return onAbortTask();
	}

	vector<string> vecInputEntryNames = String::split(strInputEntryNames, "\n");
	set<string> stEntryNames;
	for (string& strInputEntryName : vecInputEntryNames)
	{
		stEntryNames.insert(Path::removeFileExtension(String::toUpperCase(String::trim(strInputEntryName))));
	}

	vector<string> vecFileNames = File::getFileNames(strFolderPath);
	setMaxProgress(vecFileNames.size());

	uint32 uiImportedEntryCount = 0;
	for (string& strFileName : vecFileNames)
	{
		if (stEntryNames.find(Path::removeFileExtension(String::toUpperCase(strFileName))) != stEntryNames.end())
		{
			getIMGTab()->addFile(strFolderPath + strFileName);
			uiImportedEntryCount++;
			increaseProgress();
		}
	}
	getIMGTab()->getEntryGrid()->setActiveItem();

	if (uiImportedEntryCount > 0)
	{
		getIMGTab()->loadFilter_Type();
		getIMGTab()->loadFilter_Version();
		getIMGTab()->setIMGModifiedSinceRebuild(true);
	}

	getIMGTab()->logf("Imported %u entries by entry names.", uiImportedEntryCount);

	onCompleteTask();
}

void		Tasks::exportSelected(void)
{
	onStartTask("exportSelected");

	string strFolderPath = openFolder("Choose a folder to export the selected files to.");
	if (strFolderPath == "")
	{
		return onAbortTask();
	}

	uint32 uiSelectedEntryCount = getIMGTab()->getEntryGrid()->getSelectedRowCount();
	setMaxProgress(uiSelectedEntryCount);

	vector<IMGEntry*> vecIMGEntries;
	for (GridRow *pRow : getIMGTab()->getEntryGrid()->getSelectedRows())
	{
		IMGEntry *pIMGEntry = (IMGEntry*)pRow->getUserData();

		vecIMGEntries.push_back(pIMGEntry);
	}

	getIMGTab()->getIMGFile()->exportMultiple(vecIMGEntries, strFolderPath);

	getIMGTab()->logf("Exported %u selected entries.", uiSelectedEntryCount);

	onCompleteTask();
}

void		Tasks::exportAll(void)
{
	onStartTask("exportAll");

	string strFolderPath = openFolder("Choose a folder to export all files to.");
	if (strFolderPath == "")
	{
		return onAbortTask();
	}

	uint32 uiTotalEntryCount = getIMGTab()->getEntryGrid()->getEntryCount();
	setMaxProgress(uiTotalEntryCount);

	getIMGTab()->getIMGFile()->exportAll(strFolderPath);

	getIMGTab()->logf("Exported all %u entries.", uiTotalEntryCount);

	onCompleteTask();
}

void		Tasks::exportByIndex(void)
{
	onStartTask("exportByIndex");

	NumericMultiOptionInputLayerResult nmoir = m_pMainWindow->showNumericMultiOptionWindow("Export Entries by Index", "Export entries with an index"); // todo - rename nmoir
	if (nmoir.m_bCancelled)
	{
		return onAbortTask();
	}

	string strFolderPath = openFolder("Choose a folder to export the files to.");
	if (strFolderPath == "")
	{
		return onAbortTask();
	}

	uint32 uiTotalEntryCount = getIMGTab()->getEntryGrid()->getEntryCount();
	setMaxProgress(uiTotalEntryCount * 2);

	vector<IMGEntry*> vecIMGEntries = getIMGTab()->getEntriesByNumericMultiOptionValues(0, nmoir.m_uiOptionIndex, nmoir.m_uiTextBoxValue1, nmoir.m_uiTextBoxValue2); // todo - magic int
	setMaxProgress(uiTotalEntryCount + vecIMGEntries.size(), false);
	for (IMGEntry *pIMGEntry : vecIMGEntries)
	{
		getIMGTab()->getIMGFile()->exportSingle(pIMGEntry, strFolderPath);
		increaseProgress();
	}
	getIMGTab()->getEntryGrid()->setActiveItem();

	getIMGTab()->logf("Exported %u entries with an index %s.", vecIMGEntries.size(), nmoir.getMessageText().c_str());

	onCompleteTask();
}

void		Tasks::exportByName(void)
{
	onStartTask("exportByName");

	string strEntryNameInput = m_pMainWindow->showSingleLineTextBoxWindow("Export Entries by Name", "Export entries with a name that includes:");
	if (strEntryNameInput == "")
	{
		return onAbortTask();
	}

	string strFolderPath = openFolder("Choose a folder to export the files to.");
	if (strFolderPath == "")
	{
		return onAbortTask();
	}

	uint32 uiTotalEntryCount = getIMGTab()->getEntryGrid()->getEntryCount();
	setMaxProgress(uiTotalEntryCount * 2);

	vector<IMGEntry*> vecIMGEntries = getIMGTab()->getIMGFile()->getEntriesByName(strEntryNameInput);
	setMaxProgress(uiTotalEntryCount + vecIMGEntries.size(), false); // todo - increaseMaxProgress
	for (IMGEntry *pIMGEntry : vecIMGEntries)
	{
		getIMGTab()->getIMGFile()->exportSingle(pIMGEntry, strFolderPath);
		increaseProgress();
	}
	getIMGTab()->getEntryGrid()->setActiveItem();

	getIMGTab()->logf("Exported %u entries with a name that includes %s.", vecIMGEntries.size(), strEntryNameInput.c_str());

	onCompleteTask();
}

void		Tasks::exportByOffset(void)
{
	onStartTask("exportByOffset");

	NumericMultiOptionInputLayerResult nmoir = m_pMainWindow->showNumericMultiOptionWindow("Export Entries by Offset", "Export entries with an offset");
	if (nmoir.m_bCancelled)
	{
		return onAbortTask();
	}

	string strFolderPath = openFolder("Choose a folder to export the files to.");
	if (strFolderPath == "")
	{
		return onAbortTask();
	}

	uint32 uiTotalEntryCount = getIMGTab()->getEntryGrid()->getEntryCount();
	setMaxProgress(uiTotalEntryCount * 2);

	vector<IMGEntry*> vecIMGEntries = getIMGTab()->getEntriesByNumericMultiOptionValues(2, nmoir.m_uiOptionIndex, nmoir.m_uiTextBoxValue1, nmoir.m_uiTextBoxValue2); // todo - magic int
	setMaxProgress(uiTotalEntryCount + vecIMGEntries.size(), false);
	for (IMGEntry *pIMGEntry : vecIMGEntries)
	{
		getIMGTab()->getIMGFile()->exportSingle(pIMGEntry, strFolderPath);
		increaseProgress();
	}
	getIMGTab()->getEntryGrid()->setActiveItem();

	getIMGTab()->logf("Exported %u entries with an offset %s.", vecIMGEntries.size(), nmoir.getMessageText().c_str());

	onCompleteTask();
}

void		Tasks::exportBySize(void)
{
	onStartTask("exportBySize");

	NumericMultiOptionInputLayerResult nmoir = m_pMainWindow->showNumericMultiOptionWindow("Export Entries by Size", "Export entries with a size");
	if (nmoir.m_bCancelled)
	{
		return onAbortTask();
	}

	string strFolderPath = openFolder("Choose a folder to export the files to.");
	if (strFolderPath == "")
	{
		return onAbortTask();
	}

	uint32 uiTotalEntryCount = getIMGTab()->getEntryGrid()->getEntryCount();
	setMaxProgress(uiTotalEntryCount * 2);

	vector<IMGEntry*> vecIMGEntries = getIMGTab()->getEntriesByNumericMultiOptionValues(3, nmoir.m_uiOptionIndex, nmoir.m_uiTextBoxValue1, nmoir.m_uiTextBoxValue2); // todo - magic int
	setMaxProgress(uiTotalEntryCount + vecIMGEntries.size(), false);
	for (IMGEntry *pIMGEntry : vecIMGEntries)
	{
		getIMGTab()->getIMGFile()->exportSingle(pIMGEntry, strFolderPath);
		increaseProgress();
	}
	getIMGTab()->getEntryGrid()->setActiveItem();

	getIMGTab()->logf("Exported %u entries with a size %s.", vecIMGEntries.size(), nmoir.getMessageText().c_str());

	onCompleteTask();
}

void		Tasks::exportByType(void)
{
	onStartTask("exportByType");

	string strEntryTypeInput = m_pMainWindow->showSingleLineTextBoxWindow("Export Entries by Type", "Export entries with a type that includes:");
	if (strEntryTypeInput == "")
	{
		return onAbortTask();
	}

	string strFolderPath = openFolder("Choose a folder to export the files to.");
	if (strFolderPath == "")
	{
		return onAbortTask();
	}

	uint32 uiTotalEntryCount = getIMGTab()->getEntryGrid()->getEntryCount();
	setMaxProgress(uiTotalEntryCount * 2);

	vector<IMGEntry*> vecIMGEntries = getIMGTab()->getIMGFile()->getEntriesByExtension(strEntryTypeInput, true);
	setMaxProgress(uiTotalEntryCount + vecIMGEntries.size(), false); // todo - increaseMaxProgress
	for (IMGEntry *pIMGEntry : vecIMGEntries)
	{
		getIMGTab()->getIMGFile()->exportSingle(pIMGEntry, strFolderPath);
		increaseProgress();
	}
	getIMGTab()->getEntryGrid()->setActiveItem();

	getIMGTab()->logf("Exported %u entries with a type that includes %s.", vecIMGEntries.size(), strEntryTypeInput.c_str());

	onCompleteTask();
}

void		Tasks::exportByVersion(void)
{
	onStartTask("exportByVersion");

	DropDown *pVersionFilter = getIMGTab()->getEntryVersionFilter();
	vector<string> vecVersionOptions = pVersionFilter->getItems();
	int32 iVersionOptionIndex = m_pMainWindow->showDropDownWindow("Export Entries by Version", "Export entries with version", vecVersionOptions);
	if (iVersionOptionIndex == -1)
	{
		return onAbortTask();
	}

	string strFolderPath = openFolder("Choose a folder to export the files to.");
	if (strFolderPath == "")
	{
		return onAbortTask();
	}

	uint32 uiTotalEntryCount = getIMGTab()->getEntryGrid()->getEntryCount();
	setMaxProgress(uiTotalEntryCount * 2);

	DropDownItem
		*pDropDownItem = pVersionFilter->getEntryByIndex(iVersionOptionIndex);
	uint32
		uiFileTypeId = pDropDownItem->getUserdata2(), // todo - rename to getUserData2()
		uiFileVersionId = pDropDownItem->getUserdata(); // todo - rename to getUserData()

	vector<IMGEntry*> vecIMGEntries = getIMGTab()->getIMGFile()->getEntriesByVersion(uiFileTypeId, uiFileVersionId);
	setMaxProgress(uiTotalEntryCount + vecIMGEntries.size(), false); // todo - increaseMaxProgress
	for (IMGEntry *pIMGEntry : vecIMGEntries)
	{
		getIMGTab()->getIMGFile()->exportSingle(pIMGEntry, strFolderPath);
		increaseProgress();
	}
	getIMGTab()->getEntryGrid()->setActiveItem();

	getIMGTab()->logf("Exported %u entries with version %s.", vecIMGEntries.size(), RWVersion::unpackVersionStampAsStringWithBuild(uiFileVersionId).c_str());

	onCompleteTask();
}


void		Tasks::exportAllIntoGroupedFoldersByType(void)
{
	onStartTask("exportAllIntoGroupedFoldersByType");

	string strFolderPath = openFolder("Choose a folder to export files into grouped folders by type.");
	if (strFolderPath == "")
	{
		return onAbortTask();
	}

	uint32 uiTotalEntryCount = getIMGTab()->getEntryGrid()->getEntryCount();
	setMaxProgress(uiTotalEntryCount);

	set<string> setExtensionsUsed;
	for (GridRow *pRow : getIMGTab()->getEntryGrid()->getEntries())
	{
		IMGEntry *pIMGEntry = (IMGEntry*)pRow->getUserData();
		string strFileExtension = pIMGEntry->getEntryExtension();
		if (strFileExtension == "")
		{
			strFileExtension = "NoExtension";
		}

		string strExportGroupedByTypeFolderPath = strFolderPath + strFileExtension + "/";

		getIMGTab()->getIMGFile()->exportSingle(pIMGEntry, strExportGroupedByTypeFolderPath);

		increaseProgress();

		setExtensionsUsed.insert(strFileExtension);
	}

	getIMGTab()->logf("Exported all %u entries into %u folders.", uiTotalEntryCount, setExtensionsUsed.size());

	onCompleteTask();
}

void		Tasks::exportAllFromAllTabs(void)
{
	onStartTask("exportAllFromAllTabs");

	string strFolderPath = openFolder("Choose a folder to export all files from all tabs to.");
	if (strFolderPath == "")
	{
		return onAbortTask();
	}

	uint32 uiTotalEntryCount = 0;
	for (IMGEditorTab *pEditorTab : getIMGTab()->getIMGEditor()->getIMGTabs().getEntries())
	{
		uiTotalEntryCount += pEditorTab->getIMGFile()->getEntryCount();
	}
	setMaxProgress(uiTotalEntryCount);

	for (IMGEditorTab *pEditorTab : getIMGTab()->getIMGEditor()->getIMGTabs().getEntries())
	{
		pEditorTab->getIMGFile()->exportAll(strFolderPath);
	}

	getIMGTab()->logf("Exported all %u entries from all tabs.", uiTotalEntryCount);

	onCompleteTask();
}

void		Tasks::exportAllFromAllTabsIntoGroupedFoldersByType(void)
{
	onStartTask("exportAllFromAllTabsIntoGroupedFoldersByType");

	string strFolderPath = openFolder("Choose a folder to export all files from all tabs grouped by type to.");
	if (strFolderPath == "")
	{
		return onAbortTask();
	}

	uint32 uiTotalEntryCount = 0;
	for (IMGEditorTab *pEditorTab : getIMGTab()->getIMGEditor()->getIMGTabs().getEntries())
	{
		uiTotalEntryCount += pEditorTab->getIMGFile()->getEntryCount();
	}
	setMaxProgress(uiTotalEntryCount);

	set<string> setExtensionsUsed;
	for (IMGEditorTab *pEditorTab : getIMGTab()->getIMGEditor()->getIMGTabs().getEntries())
	{
		for (GridRow *pRow : pEditorTab->getEntryGrid()->getEntries())
		{
			IMGEntry *pIMGEntry = (IMGEntry*)pRow->getUserData();
			string strFileExtension = pIMGEntry->getEntryExtension();
			if (strFileExtension == "")
			{
				strFileExtension = "NoExtension";
			}

			string strExportGroupedByTypeFolderPath = strFolderPath + strFileExtension + "/";

			pEditorTab->getIMGFile()->exportSingle(pIMGEntry, strExportGroupedByTypeFolderPath);

			increaseProgress();

			setExtensionsUsed.insert(strFileExtension);
		}
	}

	getIMGTab()->logf("Exported all %u entries from all tabs into %u folders.", uiTotalEntryCount, setExtensionsUsed.size());

	onCompleteTask();
}

void		Tasks::exportSelectionFromAllTabs(void)
{
	onStartTask("exportSelectionFromAllTabs");

	string strFolderPath = openFolder("Choose a folder to export selected files from all tabs to.");
	if (strFolderPath == "")
	{
		return onAbortTask();
	}

	uint32 uiSelectedEntryCount = 0;
	for (IMGEditorTab *pEditorTab : getIMGTab()->getIMGEditor()->getIMGTabs().getEntries())
	{
		uiSelectedEntryCount += pEditorTab->getEntryGrid()->getSelectedRowCount();
	}
	setMaxProgress(uiSelectedEntryCount);

	for (IMGEditorTab *pEditorTab : getIMGTab()->getIMGEditor()->getIMGTabs().getEntries())
	{
		vector<IMGEntry*> vecIMGEntries;
		for (GridRow *pRow : pEditorTab->getEntryGrid()->getSelectedRows())
		{
			IMGEntry *pIMGEntry = (IMGEntry*)pRow->getUserData();

			vecIMGEntries.push_back(pIMGEntry);
		}

		pEditorTab->getIMGFile()->exportMultiple(vecIMGEntries, strFolderPath);
	}

	getIMGTab()->logf("Exported %u selected entries from all tabs.", uiSelectedEntryCount);

	onCompleteTask();
}

void		Tasks::exportByIDE(void)
{
	onStartTask("exportByIDE");

	IDEInputWindowResult ideInputWindowResult = getIMGF()->getWindowManager()->showIDEInputWindow("Export from IMG by IDE", "Choose IDE items to export from the IMG:");
	if (getIMGF()->getWindowManager()->m_bWindow2Cancelled)
	{
		return onAbortTask();
	}

	vector<string> vecIDEFilePaths = openFile("IDE");
	if (vecIDEFilePaths.size() == 0)
	{
		return onAbortTask();
	}

	string strFolderPath = openFolder("Choose a folder to export the files to.");
	if (strFolderPath == "")
	{
		return onAbortTask();
	}

	// fetch chosen IDE sections from input window
	vector<EIDESection>
		vecModelSections,
		vecTextureSections;
	ideInputWindowResult.getIDESections(vecModelSections, vecTextureSections);

	// fetch model and TXD names from IDE file
	setMaxProgress(vecIDEFilePaths.size() * 3);

	set<string>
		stModelNames,
		stTextureSetNames;
	IDEManager::getModelAndTextureSetNamesFromFiles(vecIDEFilePaths, stModelNames, stTextureSetNames, vecModelSections, vecTextureSections);

	// fetch model and TXD names from DFF/TXD files inside IMG file
	setMaxProgress((vecIDEFilePaths.size() * 2) + getIMGTab()->getIMGFile()->getEntryCount());

	unordered_map<IMGEntry*, vector<string>>
		umapIMGModelNames,
		umapIMGTextureSetNames;
	getIMGTab()->getIMGFile()->getModelAndTextureSetNamesFromEntries(umapIMGModelNames, umapIMGTextureSetNames);

	// choose IMG entries that have a model name or TXD name found in IDE file
	vector<IMGEntry*> vecIMGEntries = StdVector::getKeysWithMatchingEntries(umapIMGModelNames, stModelNames);
	StdVector::addToVector(vecIMGEntries, StdVector::getKeysWithMatchingEntries(umapIMGTextureSetNames, stTextureSetNames));

	// export the IMG entries
	setMaxProgress((vecIDEFilePaths.size() * 2) + getIMGTab()->getIMGFile()->getEntryCount() + vecIMGEntries.size());
	getIMGTab()->getIMGFile()->exportMultiple(vecIMGEntries, strFolderPath);

	getIMGTab()->logf("Exported %u entries by %u IDE files.", vecIMGEntries.size(), vecIDEFilePaths.size());

	onCompleteTask();
}

void		Tasks::exportByIDEFromAllTabs(void)
{
	onStartTask("exportByIDEFromAllTabs");

	IDEInputWindowResult ideInputWindowResult = getIMGF()->getWindowManager()->showIDEInputWindow("Export from all IMG tabs by IDE", "Choose IDE items to export from the IMGs:");
	if (getIMGF()->getWindowManager()->m_bWindow2Cancelled)
	{
		return onAbortTask();
	}

	vector<string> vecIDEFilePaths = openFile("ide");
	if (vecIDEFilePaths.size() == 0)
	{
		return onAbortTask();
	}

	string strExportFolderPath = openFolder("Choose a folder to export the files to.");
	if (strExportFolderPath == "")
	{
		return onAbortTask();
	}

	// fetch chosen IDE sections from input window
	vector<EIDESection>
		vecModelSections,
		vecTextureSections;
	ideInputWindowResult.getIDESections(vecModelSections, vecTextureSections);

	// fetch model and TXD names from IDE file
	setMaxProgress(vecIDEFilePaths.size() * 3);

	set<string>
		stModelNames,
		stTextureSetNames;
	IDEManager::getModelAndTextureSetNamesFromFiles(vecIDEFilePaths, stModelNames, stTextureSetNames, vecModelSections, vecTextureSections);

	setMaxProgress((vecIDEFilePaths.size() * 2) + getIMGTab()->getIMGFile()->getEntryCount()); // todo - should take into account all IMG files

	uint32 uiIMGEntryExportCount = 0;
	for (IMGEditorTab *pIMGEditorTab : m_pMainWindow->getIMGEditor()->getIMGTabs().getEntries())
	{
		// fetch model and TXD names from DFF/TXD files inside all opened IMG files
		unordered_map<IMGEntry*, vector<string>>
			umapIMGModelNames,
			umapIMGTextureSetNames;
		pIMGEditorTab->getIMGFile()->getModelAndTextureSetNamesFromEntries(umapIMGModelNames, umapIMGTextureSetNames);

		// choose IMG entries that have a model name or TXD name found in IDE file
		vector<IMGEntry*> vecIMGEntries = StdVector::getKeysWithMatchingEntries(umapIMGModelNames, stModelNames);
		StdVector::addToVector(vecIMGEntries, StdVector::getKeysWithMatchingEntries(umapIMGTextureSetNames, stTextureSetNames));

		// export the IMG entries
		setMaxProgress((vecIDEFilePaths.size() * 2) + getIMGTab()->getIMGFile()->getEntryCount() + vecIMGEntries.size());
		pIMGEditorTab->getIMGFile()->exportMultiple(vecIMGEntries, strExportFolderPath);

		uiIMGEntryExportCount += vecIMGEntries.size();
	}

	getIMGTab()->logf("Exported %u entries from all tabs by %u IDE files.", uiIMGEntryExportCount, vecIDEFilePaths.size());

	onCompleteTask();
}

void		Tasks::exportByIPL(void)
{
	onStartTask("exportByIPL");

	vector<string> vecIPLFilePaths = openFile("IPL");
	if (vecIPLFilePaths.size() == 0)
	{
		return onAbortTask();
	}

	string strFolderPath = openFolder("Choose a folder to export the files to.");
	if (strFolderPath == "")
	{
		return onAbortTask();
	}

	// fetch model names from IPL file
	setMaxProgress(vecIPLFilePaths.size() * 3);

	set<string>
		stModelNames,
		stTextureSetNames;
	IPLManager::getModelNamesFromFiles(vecIPLFilePaths, stModelNames);

	// fetch model names from IMG file
	setMaxProgress((vecIPLFilePaths.size() * 2) + getIMGTab()->getIMGFile()->getEntryCount());

	unordered_map<IMGEntry*, vector<string>>
		umapIMGModelNames,
		umapIMGTextureSetNames;
	getIMGTab()->getIMGFile()->getModelAndTextureSetNamesFromEntries(umapIMGModelNames, umapIMGTextureSetNames);

	// choose IMG entries that have a model name found in IPL file
	vector<IMGEntry*> vecIMGEntries = StdVector::getKeysWithMatchingEntries(umapIMGModelNames, stModelNames);

	// export the IMG entries
	setMaxProgress((vecIPLFilePaths.size() * 2) + getIMGTab()->getIMGFile()->getEntryCount() + vecIMGEntries.size());
	getIMGTab()->getIMGFile()->exportMultiple(vecIMGEntries, strFolderPath);

	getIMGTab()->logf("Exported %u entries by %u IPL files.", vecIMGEntries.size(), vecIPLFilePaths.size());

	onCompleteTask();
}

void			Tasks::exportByDAT(void)
{
	onStartTask("exportByDAT");

	IDEInputWindowResult ideInputWindowResult = getIMGF()->getWindowManager()->showIDEInputWindow("Export from all IMG tabs by IDE", "Choose IDE items to export from the IMGs:");
	if (getIMGF()->getWindowManager()->m_bWindow2Cancelled)
	{
		return onAbortTask();
	}

	vector<string> vecDATFilePaths = openFile("dat");
	if (vecDATFilePaths.size() == 0)
	{
		return onAbortTask();
	}

	string strGameFolderPath = openFolder("Choose the game folder.");
	if (strGameFolderPath == "")
	{
		return onAbortTask();
	}

	// fetch IDE paths from DAT files
	vector<string> vecIDEFilePaths = DATLoaderManager::getIDEFilePaths(strGameFolderPath, vecDATFilePaths);

	// choose input IDE files to export entries from
	/*
	todo
	string strIDEFilePaths = m_pMainWindow->showTextBoxWindow("Choose IDE files to export IMG entries from:", String::join(vecIDEFilePaths, "\n"));
	if (strIDEFilePaths == "")
	{
		return onAbortTask();
	}
	vecIDEFilePaths = String::split(strIDEFilePaths, "\n");
	*/

	// choose output folder
	string strOutputFolderPath = openFolder("Choose a folder to export the entries to.");
	if (strOutputFolderPath == "")
	{
		return onAbortTask();
	}

	// fetch chosen IDE sections from input window
	vector<EIDESection>
		vecModelSections,
		vecTextureSections;
	ideInputWindowResult.getIDESections(vecModelSections, vecTextureSections);

	// fetch model and TXD names from IDE file
	set<string>
		stModelNames,
		stTextureSetNames;
	IDEManager::getModelAndTextureSetNamesFromFiles(vecIDEFilePaths, stModelNames, stTextureSetNames, vecModelSections, vecTextureSections);

	// fetch model and TXD names from DFF/TXD files inside IMG file
	setMaxProgress((vecIDEFilePaths.size() * 2) + getIMGTab()->getIMGFile()->getEntryCount());

	unordered_map<IMGEntry*, vector<string>>
		umapIMGModelNames,
		umapIMGTextureSetNames;
	getIMGTab()->getIMGFile()->getModelAndTextureSetNamesFromEntries(umapIMGModelNames, umapIMGTextureSetNames);

	// choose IMG entries that have a model name or TXD name found in IDE file
	vector<IMGEntry*> vecIMGEntries = StdVector::getKeysWithMatchingEntries(umapIMGModelNames, stModelNames);
	StdVector::addToVector(vecIMGEntries, StdVector::getKeysWithMatchingEntries(umapIMGTextureSetNames, stTextureSetNames));

	// export the IMG entries
	setMaxProgress((vecIDEFilePaths.size() * 2) + getIMGTab()->getIMGFile()->getEntryCount() + vecIMGEntries.size());
	getIMGTab()->getIMGFile()->exportMultiple(vecIMGEntries, strOutputFolderPath);

	getIMGTab()->logf("Exported %u entries by %u DAT files.", vecIMGEntries.size(), vecDATFilePaths.size());

	onCompleteTask();
}

void		Tasks::exportByEntryNames(void)
{
	onStartTask("exportByEntryNames");

	string strInputEntryNames = m_pMainWindow->showMultiLineTextBoxWindow("Export by Entry Names", "Choose entry names to export, 1 per line.");
	if (strInputEntryNames == "")
	{
		return onAbortTask();
	}

	string strExportFolderPath = openFolder("Choose a folder to export the entries to:");
	if (strExportFolderPath == "")
	{
		return onAbortTask();
	}

	vector<string> vecInputEntryNames = String::split(strInputEntryNames, "\n");
	for (string& strInputEntryName : vecInputEntryNames) // todo - StdVector::trim
	{
		strInputEntryName = String::trim(strInputEntryName);
	}

	vector<IMGEntry*> vecIMGEntries = getIMGTab()->getIMGFile()->getEntriesByNames(vecInputEntryNames);

	setMaxProgress(vecIMGEntries.size());
	getIMGTab()->getIMGFile()->exportMultiple(vecIMGEntries, strExportFolderPath);
	
	getIMGTab()->logf("Exported %u entries by entry names.", vecIMGEntries.size());

	onCompleteTask();
}

void		Tasks::exportByEntryNamesFromAllTabs(void)
{
	onStartTask("exportByEntryNamesFromAllTabs");

	string strInputEntryNames = m_pMainWindow->showMultiLineTextBoxWindow("Export by Entry Names From All Tabs", "Choose entry names to export from all tabs, 1 per line.");
	if (strInputEntryNames == "")
	{
		return onAbortTask();
	}

	string strExportFolderPath = openFolder("Choose a folder to export the entries from all tabs to:");
	if (strExportFolderPath == "")
	{
		return onAbortTask();
	}

	vector<string> vecInputEntryNames = String::split(strInputEntryNames, "\n");
	for (string& strInputEntryName : vecInputEntryNames)
	{
		strInputEntryName = String::trim(strInputEntryName);
	}

	uint32 uiEntryExportCount = 0;
	for (IMGEditorTab *pEditorTab : m_pMainWindow->getIMGEditor()->getIMGTabs().getEntries())
	{
		vector<IMGEntry*> vecIMGEntries = pEditorTab->getIMGFile()->getEntriesByNames(vecInputEntryNames);

		setMaxProgress(vecIMGEntries.size());
		pEditorTab->getIMGFile()->exportMultiple(vecIMGEntries, strExportFolderPath);

		uiEntryExportCount += vecIMGEntries.size();
	}

	for (IMGEditorTab *pEditorTab : m_pMainWindow->getIMGEditor()->getIMGTabs().getEntries())
	{
		pEditorTab->logf("Exported %u entries by entry names from all tabs.", uiEntryExportCount);
	}

	onCompleteTask();
}

void		Tasks::quickExport(void)
{
	onStartTask("quickExport");

	string strQuickExportFolderPath = getIMGF()->getSettingsManager()->getSetting("QuickExportFolderPath");
	if (strQuickExportFolderPath == "")
	{
		Input::showMessage("The Quick Export folder is not set, please choose this in Settings first.", "Quick Export Folder Not Set", MB_OK);
		return;
	}

	uint32 uiSelectedEntryCount = getIMGTab()->getSelectedEntryCount();
	setMaxProgress(uiSelectedEntryCount);

	getIMGTab()->getIMGFile()->exportMultiple(getIMGTab()->getSelectedEntries(), strQuickExportFolderPath);

	getIMGTab()->logf("Quick exported %u entries.", uiSelectedEntryCount);

	onCompleteTask();
}

void		Tasks::rename(void)
{
	onStartTask("rename");

	if (getIMGTab()->getEntryGrid()->getSelectedRowCount() == 0)
	{
		Input::showMessage("At least one IMG entry must be selected to rename.", "No Entries Selected");
		return onAbortTask();
	}
	else if (getIMGTab()->getEntryGrid()->getSelectedRowCount() > 1)
	{
		Input::showMessage("Only one IMG entry can be selected to rename.", "Too Many Entries Selected");
		return onAbortTask();
	}

	IMGEntry *pIMGEntry = (IMGEntry*)getIMGTab()->getEntryGrid()->getSelectedRows()[0]->getUserData();

	string strNewEntryName = getIMGTab()->getWindow()->showSingleLineTextBoxWindow("New IMG Entry Name", "Choose a new name for the IMG entry:", pIMGEntry->getEntryName());
	if (strNewEntryName == "")
	{
		return onAbortTask();
	}

	if (Path::getFileExtension(strNewEntryName) == "")
	{
		string strOldExtension = Path::getFileExtension(pIMGEntry->getEntryName());
		if (strOldExtension != "")
		{
			strNewEntryName += "." + strOldExtension;
		}
	}

	setMaxProgress(2);
	
	pIMGEntry->setEntryName(strNewEntryName);
	getIMGTab()->updateGridEntry(pIMGEntry);
	increaseProgress();

	getIMGTab()->readdGridEntries(); // for search text
	increaseProgress();

	getIMGTab()->setIMGModifiedSinceRebuild(true);

	onCompleteTask();
}

void		Tasks::replaceByFiles(void)
{
	onStartTask("replaceByFiles");

	vector<string> vecFilePaths = openFile();
	if (vecFilePaths.size() == 0)
	{
		return onAbortTask();
	}

	setMaxProgress(vecFilePaths.size());

	uint32 uiReplacedEntryCount = 0;
	IMGFormat *pIMGFile = getIMGTab()->getIMGFile();
	for (string& strFilePath : vecFilePaths)
	{
		string strFileName = Path::getFileName(strFilePath);

		IMGEntry *pIMGEntry = getIMGTab()->getEntryByName(strFileName);
		if (!pIMGEntry)
		{
			increaseProgress();
			continue;
		}

		pIMGEntry->replace(strFilePath);

		increaseProgress();
		uiReplacedEntryCount++;
	}

	if (uiReplacedEntryCount > 0)
	{
		getIMGTab()->setIMGModifiedSinceRebuild(true);
		getIMGTab()->readdGridEntries();
	}

	getIMGTab()->logf("Replaced %u entries by file.", uiReplacedEntryCount);

	onCompleteTask();
}

void		Tasks::replaceBySingleFolder(void)
{
	onStartTask("replaceBySingleFolder");

	string strFolderPath = openFolder("Choose a folder to replace entries from.");
	if (strFolderPath == "")
	{
		return onAbortTask();
	}

	vector<string> vecFileNames = File::getFileNames(strFolderPath);

	setMaxProgress(vecFileNames.size());

	uint32 uiReplacedEntryCount = 0;
	IMGFormat *pIMGFile = getIMGTab()->getIMGFile();
	for (string& strFileName : vecFileNames)
	{
		string strFilePath = strFolderPath + strFileName;

		IMGEntry *pIMGEntry = getIMGTab()->getEntryByName(strFileName);
		if (!pIMGEntry)
		{
			increaseProgress();
			continue;
		}

		pIMGEntry->replace(strFilePath);

		increaseProgress();
		uiReplacedEntryCount++;
	}

	if (uiReplacedEntryCount > 0)
	{
		getIMGTab()->setIMGModifiedSinceRebuild(true);
		getIMGTab()->readdGridEntries();
	}

	getIMGTab()->logf("Replaced %u entries by folder.", uiReplacedEntryCount);

	onCompleteTask();
}

void		Tasks::replaceByFolderRecursively(void)
{
	onStartTask("replaceByFolderRecursively");

	string strFolderPath = openFolder("Choose a folder to recursively replace entries from.");
	if (strFolderPath == "")
	{
		return onAbortTask();
	}

	vector<string> vecFilePaths = File::getFilePaths(strFolderPath, true, false, "", true);

	setMaxProgress(vecFilePaths.size());

	uint32 uiReplacedEntryCount = 0;
	IMGFormat *pIMGFile = getIMGTab()->getIMGFile();
	for (string& strFilePath : vecFilePaths)
	{
		string strFileName = Path::getFileName(strFilePath);

		IMGEntry *pIMGEntry = getIMGTab()->getEntryByName(strFileName);
		if (!pIMGEntry)
		{
			increaseProgress();
			continue;
		}

		pIMGEntry->replace(strFilePath);

		increaseProgress();
		uiReplacedEntryCount++;
	}

	if (uiReplacedEntryCount > 0)
	{
		getIMGTab()->setIMGModifiedSinceRebuild(true);
		getIMGTab()->readdGridEntries();
	}

	getIMGTab()->logf("Replaced %u entries recursively by folder.", uiReplacedEntryCount);

	onCompleteTask();
}

void		Tasks::replaceByIDE(void)
{
	onStartTask("replaceByIDE");

	IDEInputWindowResult ideInputWindowResult = getIMGF()->getWindowManager()->showIDEInputWindow("Replace in IMG by IDE", "Choose IDE items to replace in the IMG:");
	if (getIMGF()->getWindowManager()->m_bWindow2Cancelled)
	{
		return onAbortTask();
	}

	vector<string> vecIDEFilePaths = openFile("IDE");
	if (vecIDEFilePaths.size() == 0)
	{
		return onAbortTask();
	}

	vector<string> vecFilePaths = openFile();
	if (vecFilePaths.size() == 0)
	{
		return onAbortTask();
	}

	// fetch chosen IDE sections from input window
	vector<EIDESection>
		vecModelSections,
		vecTextureSections;
	ideInputWindowResult.getIDESections(vecModelSections, vecTextureSections);

	// fetch model and TXD names from IDE file
	setMaxProgress(vecIDEFilePaths.size() * 3);

	set<string>
		stModelNames,
		stTextureSetNames;
	IDEManager::getModelAndTextureSetNamesFromFiles(vecIDEFilePaths, stModelNames, stTextureSetNames, vecModelSections, vecTextureSections);

	// fetch model and TXD names from DFF/TXD files inside IMG file
	setMaxProgress((vecIDEFilePaths.size() * 2) + getIMGTab()->getIMGFile()->getEntryCount());

	unordered_map<IMGEntry*, vector<string>>
		umapIMGModelNames,
		umapIMGTextureSetNames;
	getIMGTab()->getIMGFile()->getModelAndTextureSetNamesFromEntries(umapIMGModelNames, umapIMGTextureSetNames);

	// choose IMG entries that have a model name or TXD name found in IDE file
	vector<IMGEntry*> vecIMGEntries = StdVector::getKeysWithMatchingEntries(umapIMGModelNames, stModelNames);
	StdVector::addToVector(vecIMGEntries, StdVector::getKeysWithMatchingEntries(umapIMGTextureSetNames, stTextureSetNames));

	// export the IMG entries
	setMaxProgress((vecIDEFilePaths.size() * 2) + getIMGTab()->getIMGFile()->getEntryCount() + vecFilePaths.size());

	uint32 uiReplacedEntryCount = 0;
	IMGFormat *pIMGFile = getIMGTab()->getIMGFile();
	for (string& strFilePath : vecFilePaths)
	{
		string strFileName = String::toUpperCase(Path::getFileName(strFilePath));

		IMGEntry *pIMGEntry = nullptr;
		for (IMGEntry *pIMGEntry2 : vecIMGEntries)
		{
			if (strFileName == String::toUpperCase(pIMGEntry2->getEntryName()))
			{
				pIMGEntry = pIMGEntry2;
				break;
			}
		}

		if (!pIMGEntry)
		{
			increaseProgress();
			continue;
		}

		pIMGEntry->replace(strFilePath);

		increaseProgress();
		uiReplacedEntryCount++;
	}

	if (uiReplacedEntryCount > 0)
	{
		getIMGTab()->setIMGModifiedSinceRebuild(true);
		getIMGTab()->readdGridEntries();
	}

	getIMGTab()->logf("Replaced %u entries by %u IDE files.", vecIMGEntries.size(), vecIDEFilePaths.size());

	onCompleteTask();
}

void		Tasks::removeSelected(void)
{
	onStartTask("removeSelected");

	uint32 uiSelectedEntryCount = getIMGTab()->getEntryGrid()->getSelectedRowCount();
	setMaxProgress(uiSelectedEntryCount + (uiSelectedEntryCount == 0 ? 0 : (getIMGTab()->getEntryGrid()->getEntryCount() - uiSelectedEntryCount)));

	getIMGTab()->removeSelectedEntries();

	if (uiSelectedEntryCount > 0)
	{
		getIMGTab()->readdGridEntries();
		getIMGTab()->setIMGModifiedSinceRebuild(true);
	}

	getIMGTab()->logf("Removed %u selected entries.", uiSelectedEntryCount);

	onCompleteTask();
}

void		Tasks::removeAll(void)
{
	onStartTask("removeAll");

	uint32 uiTotalEntryCount = getIMGTab()->getEntryGrid()->getEntryCount();
	setMaxProgress(uiTotalEntryCount);

	getIMGTab()->removeAllEntries();

	if (uiTotalEntryCount > 0)
	{
		getIMGTab()->readdGridEntries();
		getIMGTab()->setIMGModifiedSinceRebuild(true);
	}

	getIMGTab()->logf("Removed all %u entries.", uiTotalEntryCount);

	onCompleteTask();
}

void		Tasks::removeByIndex(void)
{
	onStartTask("removeByIndex");

	NumericMultiOptionInputLayerResult nmoir = m_pMainWindow->showNumericMultiOptionWindow("Remove Entries by Index", "Remove entries with an index");
	if (nmoir.m_bCancelled)
	{
		return onAbortTask();
	}

	uint32 uiTotalEntryCount = getIMGTab()->getEntryGrid()->getEntryCount();
	setMaxProgress(uiTotalEntryCount * 3);

	vector<IMGEntry*> vecIMGEntries = getIMGTab()->getEntriesByNumericMultiOptionValues(0, nmoir.m_uiOptionIndex, nmoir.m_uiTextBoxValue1, nmoir.m_uiTextBoxValue2); // todo - magic int
	setMaxProgress(uiTotalEntryCount + vecIMGEntries.size() + (vecIMGEntries.size() == 0 ? 0 : (uiTotalEntryCount - vecIMGEntries.size())), false);
	for (IMGEntry *pIMGEntry : vecIMGEntries)
	{
		getIMGTab()->removeEntry(pIMGEntry);
		increaseProgress();
	}
	getIMGTab()->getEntryGrid()->setActiveItem();

	if (vecIMGEntries.size() > 0)
	{
		getIMGTab()->readdGridEntries();
		getIMGTab()->loadFilter_Type();
		getIMGTab()->loadFilter_Version();
		getIMGTab()->setIMGModifiedSinceRebuild(true);
	}

	getIMGTab()->logf("Removed %u entries with an index %s.", vecIMGEntries.size(), nmoir.getMessageText().c_str());

	onCompleteTask();
}

void		Tasks::removeByName(void)
{
	onStartTask("removeByName");

	string strEntryNameInput = m_pMainWindow->showSingleLineTextBoxWindow("Remove Entries by Name", "Remove entries with a name that includes:");
	if (strEntryNameInput == "")
	{
		return onAbortTask();
	}

	uint32 uiTotalEntryCount = getIMGTab()->getEntryGrid()->getEntryCount();
	setMaxProgress(uiTotalEntryCount * 3);

	vector<IMGEntry*> vecIMGEntries = getIMGTab()->getIMGFile()->getEntriesByName(strEntryNameInput);
	setMaxProgress(uiTotalEntryCount + vecIMGEntries.size() + (vecIMGEntries.size() == 0 ? 0 : (uiTotalEntryCount - vecIMGEntries.size())), false);
	for (IMGEntry *pIMGEntry : vecIMGEntries)
	{
		getIMGTab()->removeEntry(pIMGEntry);
		increaseProgress();
	}
	getIMGTab()->getEntryGrid()->setActiveItem();

	if (vecIMGEntries.size() > 0)
	{
		getIMGTab()->readdGridEntries();
		getIMGTab()->loadFilter_Type();
		getIMGTab()->loadFilter_Version();
		getIMGTab()->setIMGModifiedSinceRebuild(true);
	}

	getIMGTab()->logf("Removed %u entries with a name that includes %s.", vecIMGEntries.size(), strEntryNameInput.c_str());

	onCompleteTask();
}

void		Tasks::removeByOffset(void)
{
	onStartTask("removeByOffset");

	NumericMultiOptionInputLayerResult nmoir = m_pMainWindow->showNumericMultiOptionWindow("Remove Entries by Offset", "Remove entries with an offset");
	if (nmoir.m_bCancelled)
	{
		return onAbortTask();
	}

	uint32 uiTotalEntryCount = getIMGTab()->getEntryGrid()->getEntryCount();
	setMaxProgress(uiTotalEntryCount * 3);

	vector<IMGEntry*> vecIMGEntries = getIMGTab()->getEntriesByNumericMultiOptionValues(2, nmoir.m_uiOptionIndex, nmoir.m_uiTextBoxValue1, nmoir.m_uiTextBoxValue2); // todo - magic int
	setMaxProgress(uiTotalEntryCount + vecIMGEntries.size() + (vecIMGEntries.size() == 0 ? 0 : (uiTotalEntryCount - vecIMGEntries.size())), false);
	for (IMGEntry *pIMGEntry : vecIMGEntries)
	{
		getIMGTab()->removeEntry(pIMGEntry);
		increaseProgress();
	}
	getIMGTab()->getEntryGrid()->setActiveItem();

	if (vecIMGEntries.size() > 0)
	{
		getIMGTab()->readdGridEntries();
		getIMGTab()->loadFilter_Type();
		getIMGTab()->loadFilter_Version();
		getIMGTab()->setIMGModifiedSinceRebuild(true);
	}

	getIMGTab()->logf("Removed %u entries with an offset %s.", vecIMGEntries.size(), nmoir.getMessageText().c_str());

	onCompleteTask();
}

void		Tasks::removeBySize(void)
{
	onStartTask("removeBySize");

	NumericMultiOptionInputLayerResult nmoir = m_pMainWindow->showNumericMultiOptionWindow("Remove Entries by Size", "Remove entries with a size");
	if (nmoir.m_bCancelled)
	{
		return onAbortTask();
	}

	uint32 uiTotalEntryCount = getIMGTab()->getEntryGrid()->getEntryCount();
	setMaxProgress(uiTotalEntryCount * 3);

	vector<IMGEntry*> vecIMGEntries = getIMGTab()->getEntriesByNumericMultiOptionValues(3, nmoir.m_uiOptionIndex, nmoir.m_uiTextBoxValue1, nmoir.m_uiTextBoxValue2); // todo - magic int
	setMaxProgress(uiTotalEntryCount + vecIMGEntries.size() + (vecIMGEntries.size() == 0 ? 0 : (uiTotalEntryCount - vecIMGEntries.size())), false);
	for (IMGEntry *pIMGEntry : vecIMGEntries)
	{
		getIMGTab()->removeEntry(pIMGEntry);
		increaseProgress();
	}
	getIMGTab()->getEntryGrid()->setActiveItem();

	if (vecIMGEntries.size() > 0)
	{
		getIMGTab()->readdGridEntries();
		getIMGTab()->loadFilter_Type();
		getIMGTab()->loadFilter_Version();
		getIMGTab()->setIMGModifiedSinceRebuild(true);
	}

	getIMGTab()->logf("Removed %u entries with a size %s.", vecIMGEntries.size(), nmoir.getMessageText().c_str());

	onCompleteTask();
}

void		Tasks::removeByType(void)
{
	onStartTask("removeByType");

	string strEntryTypeInput = m_pMainWindow->showSingleLineTextBoxWindow("Remove Entries by Type", "Remove entries with a type that includes:");
	if (strEntryTypeInput == "")
	{
		return onAbortTask();
	}

	uint32 uiTotalEntryCount = getIMGTab()->getEntryGrid()->getEntryCount();
	setMaxProgress(uiTotalEntryCount * 3);

	vector<IMGEntry*> vecIMGEntries = getIMGTab()->getIMGFile()->getEntriesByExtension(strEntryTypeInput, true);
	setMaxProgress(uiTotalEntryCount + vecIMGEntries.size() + (vecIMGEntries.size() == 0 ? 0 : (uiTotalEntryCount - vecIMGEntries.size())), false);
	for (IMGEntry *pIMGEntry : vecIMGEntries)
	{
		getIMGTab()->removeEntry(pIMGEntry);
		increaseProgress();
	}
	getIMGTab()->getEntryGrid()->setActiveItem();

	if (vecIMGEntries.size() > 0)
	{
		getIMGTab()->readdGridEntries();
		getIMGTab()->loadFilter_Type();
		getIMGTab()->loadFilter_Version();
		getIMGTab()->setIMGModifiedSinceRebuild(true);
	}

	getIMGTab()->logf("Removed %u entries with a type that includes %s.", vecIMGEntries.size(), strEntryTypeInput.c_str());

	onCompleteTask();
}

void		Tasks::removeByVersion(void)
{
	onStartTask("removeByVersion");

	DropDown *pVersionFilter = getIMGTab()->getEntryVersionFilter();
	vector<string> vecVersionOptions = pVersionFilter->getItems();
	int32 iVersionOptionIndex = m_pMainWindow->showDropDownWindow("Remove Entries by Version", "Remove entries with version", vecVersionOptions);
	if (iVersionOptionIndex == -1)
	{
		return onAbortTask();
	}

	uint32 uiTotalEntryCount = getIMGTab()->getEntryGrid()->getEntryCount();
	setMaxProgress(uiTotalEntryCount * 3);

	DropDownItem
		*pDropDownItem = pVersionFilter->getEntryByIndex(iVersionOptionIndex);
	uint32
		uiFileTypeId = pDropDownItem->getUserdata2(), // todo - rename to getUserData2()
		uiFileVersionId = pDropDownItem->getUserdata(); // todo - rename to getUserData()

	vector<IMGEntry*> vecIMGEntries = getIMGTab()->getIMGFile()->getEntriesByVersion(uiFileTypeId, uiFileVersionId);
	setMaxProgress(uiTotalEntryCount + vecIMGEntries.size() + (vecIMGEntries.size() == 0 ? 0 : (uiTotalEntryCount - vecIMGEntries.size())), false);
	for (IMGEntry *pIMGEntry : vecIMGEntries)
	{
		getIMGTab()->removeEntry(pIMGEntry);
		increaseProgress();
	}
	getIMGTab()->getEntryGrid()->setActiveItem();

	if (vecIMGEntries.size() > 0)
	{
		getIMGTab()->readdGridEntries();
		getIMGTab()->loadFilter_Type();
		getIMGTab()->loadFilter_Version();
		getIMGTab()->setIMGModifiedSinceRebuild(true);
	}

	getIMGTab()->logf("Removed %u entries with version %s.", vecIMGEntries.size(), RWVersion::unpackVersionStampAsStringWithBuild(uiFileVersionId).c_str());

	onCompleteTask();
}

void		Tasks::removeByIDE(void)
{
	onStartTask("removeByIDE");

	IDEInputWindowResult ideInputWindowResult = getIMGF()->getWindowManager()->showIDEInputWindow("Remove from IMG by IDE", "Choose IDE items to remove from the IMG:");
	if (getIMGF()->getWindowManager()->m_bWindow2Cancelled)
	{
		return onAbortTask();
	}

	vector<string> vecIDEFilePaths = openFile("IDE");
	if (vecIDEFilePaths.size() == 0)
	{
		return onAbortTask();
	}

	// fetch chosen IDE sections from input window
	vector<EIDESection>
		vecModelSections,
		vecTextureSections;
	ideInputWindowResult.getIDESections(vecModelSections, vecTextureSections);

	// fetch model and TXD names from IDE file
	setMaxProgress(vecIDEFilePaths.size() * 3);

	set<string>
		stModelNames,
		stTextureSetNames;
	IDEManager::getModelAndTextureSetNamesFromFiles(vecIDEFilePaths, stModelNames, stTextureSetNames, vecModelSections, vecTextureSections);

	// fetch model and TXD names from DFF/TXD files inside IMG file
	setMaxProgress((vecIDEFilePaths.size() * 2) + getIMGTab()->getIMGFile()->getEntryCount());

	unordered_map<IMGEntry*, vector<string>>
		umapIMGModelNames,
		umapIMGTextureSetNames;
	getIMGTab()->getIMGFile()->getModelAndTextureSetNamesFromEntries(umapIMGModelNames, umapIMGTextureSetNames);

	// choose IMG entries that have a model name or TXD name found in IDE file
	vector<IMGEntry*> vecIMGEntries = StdVector::getKeysWithMatchingEntries(umapIMGModelNames, stModelNames);
	StdVector::addToVector(vecIMGEntries, StdVector::getKeysWithMatchingEntries(umapIMGTextureSetNames, stTextureSetNames));

	// export the IMG entries
	setMaxProgress((vecIDEFilePaths.size() * 2) + getIMGTab()->getIMGFile()->getEntryCount() + vecIMGEntries.size());
	for (IMGEntry *pIMGEntry : vecIMGEntries)
	{
		getIMGTab()->removeEntry(pIMGEntry);
		increaseProgress();
	}
	getIMGTab()->getEntryGrid()->setActiveItem();

	if (vecIMGEntries.size() > 0)
	{
		getIMGTab()->readdGridEntries();
		getIMGTab()->loadFilter_Type();
		getIMGTab()->loadFilter_Version();
		getIMGTab()->setIMGModifiedSinceRebuild(true);
	}

	getIMGTab()->logf("Removed %u entries by %u IDE files.", vecIMGEntries.size(), vecIDEFilePaths.size());

	onCompleteTask();
}

void		Tasks::removeByEntryNames(void)
{
	onStartTask("removeByEntryNames");

	string strInputEntryNames = m_pMainWindow->showMultiLineTextBoxWindow("Remove by Entry Names", "Choose entry names to remove, 1 per line.");
	if (strInputEntryNames == "")
	{
		return onAbortTask();
	}

	vector<string> vecInputEntryNames = String::split(strInputEntryNames, "\n");
	for (string& strInputEntryName : vecInputEntryNames)
	{
		strInputEntryName = String::trim(strInputEntryName);
	}

	vector<IMGEntry*> vecIMGEntries = getIMGTab()->getIMGFile()->getEntriesByNames(vecInputEntryNames);

	setMaxProgress(vecIMGEntries.size());
	for (IMGEntry *pIMGEntry : vecIMGEntries) // todo - removeEntries()
	{
		getIMGTab()->removeEntry(pIMGEntry);
		increaseProgress();
	}
	getIMGTab()->getEntryGrid()->setActiveItem();

	if (vecIMGEntries.size() > 0)
	{
		getIMGTab()->readdGridEntries();
		getIMGTab()->loadFilter_Type();
		getIMGTab()->loadFilter_Version();
		getIMGTab()->setIMGModifiedSinceRebuild(true);
	}

	getIMGTab()->logf("Removed %u entries by entry names.", vecIMGEntries.size());

	onCompleteTask();
}

void		Tasks::merge(void)
{
	onStartTask("merge");
	
	vector<string> vecFilePaths = openFile("img,dir");

	uint32 uiMergeEntryCount = 0;
	for (string& strFilePath : vecFilePaths)
	{
		uiMergeEntryCount += IMGManager::getIMGEntryCount(strFilePath, IMGManager::detectIMGVersion(strFilePath));
	}
	setMaxProgress(uiMergeEntryCount);

	vector<string> vecImportedEntryNames;
	for (string& strFilePath : vecFilePaths)
	{
		getIMGTab()->merge(strFilePath, vecImportedEntryNames);
		vecImportedEntryNames.clear();
	}

	if (uiMergeEntryCount > 0)
	{
		getIMGTab()->readdGridEntries();
		getIMGTab()->loadFilter_Type();
		getIMGTab()->loadFilter_Version();
		getIMGTab()->updateEntryCountText();
		getIMGTab()->updateIMGText();
		getIMGTab()->setIMGModifiedSinceRebuild(true);
	}

	getIMGTab()->logf("Merged in %u IMG files (%u entries).", vecFilePaths.size(), uiMergeEntryCount);

	onCompleteTask();
}

void		Tasks::splitSelected(void)
{
	onStartTask("splitSelected");

	uint32 uiSelectedEntryCount = getIMGTab()->getEntryGrid()->getSelectedRowCount();
	if (uiSelectedEntryCount == 0)
	{
		Input::showMessage("At least one entry must be selected to split selected entries.", "Selected Entry Needed", MB_OK);
		return onAbortTask();
	}

	string strNewFilePath = saveFile("img,dir", "Split-IMG.img");
	if (strNewFilePath == "")
	{
		return onAbortTask();
	}

	int32 iNewIMGVersionOptionIndex = getIMGTab()->getWindow()->showDropDownWindow("Choose Output IMG Version", "Create output IMG with version (cancel for same version)", IMGManager::getVersionsText());
	EIMGVersion uiNewIMGVersion = IMGManager::getVersionFromVersionIndex(iNewIMGVersionOptionIndex);
	if (uiNewIMGVersion == IMG_UNKNOWN)
	{
		uiNewIMGVersion = getIMGTab()->getIMGFile()->getVersion();
	}

	bool bDeleteSelectedEntriesFromSourceIMG = Input::showMessage("Also delete selected entries from source IMG?", "Delete Selected Entries?") == MB_OK;

	getIMGTab()->splitSelectedEntries(strNewFilePath, uiNewIMGVersion, bDeleteSelectedEntriesFromSourceIMG);

	if (uiSelectedEntryCount > 0 && bDeleteSelectedEntriesFromSourceIMG)
	{
		getIMGTab()->setIMGModifiedSinceRebuild(true);
	}

	string
		strLogPart3 = bDeleteSelectedEntriesFromSourceIMG ? ", removing selected source entries" : "",
		strLogPart4 = iNewIMGVersionOptionIndex == -1 ? "" : ", creating IMG with version " + IMGManager::getVersionText(uiNewIMGVersion);
	getIMGTab()->logf("Split %u entries into %s%s%s.", uiSelectedEntryCount, Path::getFileName(strNewFilePath).c_str(), strLogPart3.c_str(), strLogPart4.c_str());

	onCompleteTask();
}

void		Tasks::splitByIDE(void)
{
	onStartTask("splitByIDE");

	IDEInputWindowResult ideInputWindowResult = getIMGF()->getWindowManager()->showIDEInputWindow("Split IMG by IDE", "Choose IDE items to split in the IMG:");
	if (getIMGF()->getWindowManager()->m_bWindow2Cancelled)
	{
		return onAbortTask();
	}

	vector<string> vecIDEFilePaths = openFile("ide");
	if (vecIDEFilePaths.size() == 0)
	{
		return onAbortTask();
	}

	string strNewFilePath = saveFile("img,dir", "Split-IMG.img");
	if (strNewFilePath == "")
	{
		return onAbortTask();
	}

	int32 iNewIMGVersionOptionIndex = getIMGTab()->getWindow()->showDropDownWindow("Choose Output IMG Version", "Create output IMG with version (cancel for same version)", IMGManager::getVersionsText());
	EIMGVersion uiNewIMGVersion = IMGManager::getVersionFromVersionIndex(iNewIMGVersionOptionIndex);
	if (uiNewIMGVersion == IMG_UNKNOWN)
	{
		uiNewIMGVersion = getIMGTab()->getIMGFile()->getVersion();
	}

	bool bDeleteSelectedEntriesFromSourceIMG = Input::showMessage("Also delete selected entries from source IMG?", "Delete Selected Entries?") == MB_OK;

	// fetch chosen IDE sections from input window
	vector<EIDESection>
		vecModelSections,
		vecTextureSections;
	ideInputWindowResult.getIDESections(vecModelSections, vecTextureSections);

	// fetch model and TXD names from IDE file
	setMaxProgress(vecIDEFilePaths.size() * 3);

	set<string>
		stModelNames,
		stTextureSetNames;
	IDEManager::getModelAndTextureSetNamesFromFiles(vecIDEFilePaths, stModelNames, stTextureSetNames, vecModelSections, vecTextureSections);

	// fetch model and TXD names from DFF/TXD files inside IMG file
	setMaxProgress((vecIDEFilePaths.size() * 2) + getIMGTab()->getIMGFile()->getEntryCount());

	unordered_map<IMGEntry*, vector<string>>
		umapIMGModelNames,
		umapIMGTextureSetNames;
	getIMGTab()->getIMGFile()->getModelAndTextureSetNamesFromEntries(umapIMGModelNames, umapIMGTextureSetNames);

	// choose IMG entries that have a model name or TXD name found in IDE file
	vector<IMGEntry*> vecIMGEntries = StdVector::getKeysWithMatchingEntries(umapIMGModelNames, stModelNames);
	StdVector::addToVector(vecIMGEntries, StdVector::getKeysWithMatchingEntries(umapIMGTextureSetNames, stTextureSetNames));

	// split the IMG
	setMaxProgress(vecIMGEntries.size() * (bDeleteSelectedEntriesFromSourceIMG ? 2 : 1));
	getIMGTab()->getIMGFile()->split(vecIMGEntries, strNewFilePath, uiNewIMGVersion);

	// delete source entries
	if (bDeleteSelectedEntriesFromSourceIMG)
	{
		getIMGTab()->removeSelectedEntries();
	}

	// mark IMG as modified
	if (vecIMGEntries.size() > 0 && bDeleteSelectedEntriesFromSourceIMG)
	{
		getIMGTab()->setIMGModifiedSinceRebuild(true); // todo - rename to setUnsavedChanges(bool)
	}

	// log
	string
		strLogPart3 = bDeleteSelectedEntriesFromSourceIMG ? ", removing selected source entries" : "",
		strLogPart4 = iNewIMGVersionOptionIndex == -1 ? "" : ", creating IMG with version " + IMGManager::getVersionText(uiNewIMGVersion);
	getIMGTab()->logf("Split %u entries by %u IDE files into %s%s%s.", vecIMGEntries.size(), vecIDEFilePaths.size(), Path::getFileName(strNewFilePath).c_str(), strLogPart3.c_str(), strLogPart4.c_str());

	onCompleteTask();
}

void		Tasks::splitByEntryNames(void)
{
	onStartTask("splitByEntryNames");

	string strInputEntryNames = m_pMainWindow->showMultiLineTextBoxWindow("Split by Entry Names", "Choose entry names to split, 1 per line.");
	if (strInputEntryNames == "")
	{
		return onAbortTask();
	}

	string strNewFilePath = saveFile("img,dir", "Split-IMG.img");
	if (strNewFilePath == "")
	{
		return onAbortTask();
	}

	vector<string> vecInputEntryNames = String::split(strInputEntryNames, "\n");
	for (string& strInputEntryName : vecInputEntryNames)
	{
		strInputEntryName = String::trim(strInputEntryName);
	}

	vector<IMGEntry*> vecIMGEntries = getIMGTab()->getIMGFile()->getEntriesByNames(vecInputEntryNames);

	int32 iNewIMGVersionOptionIndex = getIMGTab()->getWindow()->showDropDownWindow("Choose Output IMG Version", "Create output IMG with version (cancel for same version)", IMGManager::getVersionsText());
	EIMGVersion uiNewIMGVersion = IMGManager::getVersionFromVersionIndex(iNewIMGVersionOptionIndex);
	if (uiNewIMGVersion == IMG_UNKNOWN)
	{
		uiNewIMGVersion = getIMGTab()->getIMGFile()->getVersion();
	}

	bool bDeleteSelectedEntriesFromSourceIMG = Input::showMessage("Also delete split entries from source IMG?", "Delete Split Entries?") == MB_OK;

	getIMGTab()->getIMGFile()->split(vecIMGEntries, strNewFilePath, uiNewIMGVersion);

	if (bDeleteSelectedEntriesFromSourceIMG)
	{
		for (IMGEntry *pIMGEntry : vecIMGEntries)
		{
			getIMGTab()->removeEntry(pIMGEntry);
		}
	}

	if (vecIMGEntries.size() > 0 && bDeleteSelectedEntriesFromSourceIMG)
	{
		getIMGTab()->setIMGModifiedSinceRebuild(true);
	}

	string
		strLogPart3 = bDeleteSelectedEntriesFromSourceIMG ? ", removing selected source entries" : "",
		strLogPart4 = iNewIMGVersionOptionIndex == -1 ? "" : ", creating IMG with version " + IMGManager::getVersionText(uiNewIMGVersion);
	getIMGTab()->logf("Split %u entries into %s by entry names%s%s.", vecIMGEntries.size(), Path::getFileName(strNewFilePath).c_str(), strLogPart3.c_str(), strLogPart4.c_str());

	onCompleteTask();
}

void		Tasks::convertIMGVersion(void)
{
	onStartTask("convertIMGVersion");

	EIMGVersion uiCurrentIMGVersion = getIMGTab()->getIMGFile()->getVersion();

	// show new version selection window
	int32 iNewIMGVersionOptionIndex = getIMGTab()->getWindow()->showDropDownWindow("Convert IMG Version", "Convert IMG to version", IMGManager::getVersionsText());
	if (iNewIMGVersionOptionIndex == -1)
	{
		return onAbortTask();
	}
	EIMGVersion uiNewIMGVersion = IMGManager::getVersionFromVersionIndex(iNewIMGVersionOptionIndex);

	// check to remove DIR file
	if (uiCurrentIMGVersion == IMG_1)
	{
		// todo bool bRemoveDIRFile = getIMGTab()->getWindow()->showBoolWindow("Remove DIR file previously associated with IMG file?");
		bool bRemoveDIRFile = Input::showMessage("Remove DIR file previously associated with IMG file?", "Remove DIR File?") == MB_OK;
		if (bRemoveDIRFile)
		{
			File::removeFile(getIMGTab()->getIMGFile()->getDIRFilePath());
		}
	}

	// set new IMG version
	IMGFormat *pOldIMGFormat = getIMGTab()->getIMGFile();
	IMGFormat *pNewIMGFormat = getIMGTab()->getIMGFile()->setVersion(uiNewIMGVersion);
	getIMGTab()->setIMGFile(pNewIMGFormat);
	delete pOldIMGFormat;
	
	// check to rebuild
	if (getIMGF()->getSettingsManager()->getSettingBool("RebuildOnConvert"))
	{
		getIMGF()->getEntryListTab()->rebuild();
	}

	// render
	getIMGTab()->getIMGEditor()->refreshActiveTab();

	// set modified status
	getIMGTab()->setIMGModifiedSinceRebuild(true);

	// log
	getIMGTab()->logf("Converted IMG file to version %s.", IMGManager::getVersionText(uiNewIMGVersion, false).c_str());

	onCompleteTask();
}

void		Tasks::convertSelectedCOLVersion(void)
{
	onStartTask("convertSelectedCOLVersion");

	vector<string> vecDropDownOptions = { "COL 1", "COL 2", "COL 3", "COL 4" };
	int32 iNewCOLVersionOptionIndex = m_pMainWindow->showDropDownWindow("New COL Version", "Convert selected COL entries to version", vecDropDownOptions);
	if (iNewCOLVersionOptionIndex == -1)
	{
		return onAbortTask();
	}
	ECOLVersion uiNewCOLVersion = (ECOLVersion)(iNewCOLVersionOptionIndex + 1);

	uint32 uiSelectedRowCount = getIMGTab()->getEntryGrid()->getSelectedRowCount();
	setMaxProgress(uiSelectedRowCount);

	uint32 uiConvertedEntryCount = 0;
	for (GridRow *pRow : getIMGTab()->getEntryGrid()->getSelectedRows())
	{
		IMGEntry *pIMGEntry = (IMGEntry*) pRow->getUserData();

		if (pIMGEntry->isCollisionFile())
		{
			COLFormat colFile(pIMGEntry->getEntryData(), false);
			if (colFile.unserialize())
			{
				for (COLEntry *pCOLEntry : colFile.getEntries())
				{
					pCOLEntry->setCOLVersion(uiNewCOLVersion);
				}

				string strNewFileData = colFile.serialize();
				pIMGEntry->setEntryData(strNewFileData);

				getIMGTab()->updateGridEntry(pIMGEntry);
				uiConvertedEntryCount++;
			}
			colFile.unload();
		}

		increaseProgress();
	}

	if (uiSelectedRowCount > 0)
	{
		getIMGTab()->setIMGModifiedSinceRebuild(true);
	}

	getIMGTab()->logf("Converted COL version to %u for %u entries.", uiNewCOLVersion, uiConvertedEntryCount);

	onCompleteTask();
}

void		Tasks::convertSelectedDFFRWVersion(void)
{
	onStartTask("convertSelectedDFFRWVersion");

	vector<RWVersion*> vecRWVersions = RWManager::get()->getVersionManager()->getEntries();
	vector<string> vecDropDownOptions;
	for (RWVersion *pRWVersion : vecRWVersions)
	{
		vecDropDownOptions.push_back(pRWVersion->getVersionTextWithGames());
	}

	int32 iNewRWVersionOptionIndex = m_pMainWindow->showDropDownWindow("New DFF RW Version", "Convert selected DFF entries to RW version", vecDropDownOptions);
	if (iNewRWVersionOptionIndex == -1)
	{
		return onAbortTask();
	}
	RWVersion *pNewRWVersion = vecRWVersions[iNewRWVersionOptionIndex];
	uint32 uiNewRawRWVersion = pNewRWVersion->getRawVersion();
	string strNewRWVersionText = pNewRWVersion->getVersionTextWithGames();

	uint32 uiSelectedRowCount = getIMGTab()->getEntryGrid()->getSelectedRowCount();
	setMaxProgress(uiSelectedRowCount);

	uint32 uiConvertedEntryCount = 0;
	for (GridRow *pRow : getIMGTab()->getEntryGrid()->getSelectedRows())
	{
		IMGEntry *pIMGEntry = (IMGEntry*)pRow->getUserData();

		if (pIMGEntry->isModelFile())
		{
			DFFFormat dffFile(pIMGEntry->getEntryData(), false);
			if (dffFile.unserialize())
			{
				for (RWSection *pRWSection : dffFile.getEntries())
				{
					pRWSection->setSectionRWVersion(uiNewRawRWVersion);
				}

				string strNewFileData = dffFile.serialize();
				pIMGEntry->setEntryData(strNewFileData);

				getIMGTab()->updateGridEntry(pIMGEntry);
				uiConvertedEntryCount++;
			}
			dffFile.unload();
		}

		increaseProgress();
	}

	if (uiSelectedRowCount > 0)
	{
		getIMGTab()->setIMGModifiedSinceRebuild(true);
	}

	getIMGTab()->logf("Converted DFF version to %s for %u entries.", strNewRWVersionText.c_str(), uiConvertedEntryCount);

	onCompleteTask();
}

void			Tasks::convertSelectedDFFToWDR(void)
{
	onStartTask("convertSelectedDFFToWDR");

	uint32 uiSelectedRowCount = getIMGTab()->getEntryGrid()->getSelectedRowCount();
	setMaxProgress(uiSelectedRowCount);

	uint32 uiConvertedEntryCount = 0;
	for (GridRow *pRow : getIMGTab()->getEntryGrid()->getSelectedRows())
	{
		IMGEntry *pIMGEntry = (IMGEntry*)pRow->getUserData();

		if (pIMGEntry->isModelFile())
		{
			DFFFormat dffFile(pIMGEntry->getEntryData(), false);
			if (dffFile.unserialize())
			{
				IntermediateModelFormat *pGeneralModelFile = dffFile.convertToIntermediateModelFormat();
				WDRFormat *pWDRFile = WDRManager::get()->convertIntermediateModelFileToWDRFile(pGeneralModelFile);
				pGeneralModelFile->unload();
				delete pGeneralModelFile;
				string strWDRFileData = pWDRFile->serialize();
				pWDRFile->unload();
				delete pWDRFile;

				pIMGEntry->setEntryData(strWDRFileData);
				pIMGEntry->setEntryName(Path::replaceFileExtensionWithCase(pIMGEntry->getEntryName(), "wdr"));
				
				getIMGTab()->updateGridEntry(pIMGEntry);
				uiConvertedEntryCount++;
			}
			dffFile.unload();
		}

		increaseProgress();
	}

	if (uiSelectedRowCount > 0)
	{
		getIMGTab()->setIMGModifiedSinceRebuild(true);
	}

	getIMGTab()->logf("Converted %u DFF entries to WDR entries.", uiConvertedEntryCount);

	onCompleteTask();
}

void		Tasks::convertSelectedTXDRWVersion(void)
{
	onStartTask("convertSelectedTXDRWVersion");

	vector<RWVersion*> vecRWVersions = RWManager::get()->getVersionManager()->getEntries();
	vector<string> vecDropDownOptions;
	for (RWVersion *pRWVersion : vecRWVersions)
	{
		vecDropDownOptions.push_back(pRWVersion->getVersionTextWithGames());
	}

	int32 iNewRWVersionOptionIndex = m_pMainWindow->showDropDownWindow("Convert TXD RW Version", "Convert selected TXD entries to RW version", vecDropDownOptions);
	if (iNewRWVersionOptionIndex == -1)
	{
		return onAbortTask();
	}
	RWVersion *pNewRWVersion = vecRWVersions[iNewRWVersionOptionIndex];
	uint32 uiNewRawRWVersion = pNewRWVersion->getRawVersion();
	string strNewRWVersionText = pNewRWVersion->getVersionTextWithGames();

	uint32 uiSelectedRowCount = getIMGTab()->getEntryGrid()->getSelectedRowCount();
	setMaxProgress(uiSelectedRowCount);

	uint32 uiConvertedEntryCount = 0;
	for (GridRow *pRow : getIMGTab()->getEntryGrid()->getSelectedRows())
	{
		IMGEntry *pIMGEntry = (IMGEntry*)pRow->getUserData();

		if (pIMGEntry->isTextureFile())
		{
			TXDFormat txdFile(pIMGEntry->getEntryData(), false);
			if (txdFile.unserialize())
			{
				for (RWSection *pRWSection : txdFile.getEntries())
				{
					pRWSection->setSectionRWVersion(uiNewRawRWVersion);
				}

				string strNewFileData = txdFile.serialize();
				pIMGEntry->setEntryData(strNewFileData);

				getIMGTab()->updateGridEntry(pIMGEntry);
				uiConvertedEntryCount++;
			}
			txdFile.unload();
		}

		increaseProgress();
	}

	if (uiSelectedRowCount > 0)
	{
		getIMGTab()->setIMGModifiedSinceRebuild(true);
	}

	getIMGTab()->logf("Converted TXD version to %s for %u entries.", strNewRWVersionText.c_str(), uiConvertedEntryCount);

	onCompleteTask();
}

void		Tasks::convertSelectedTXDToGame(void)
{
	onStartTask("convertSelectedTXDToGame");

	vector<PlatformedGame*> vecPlatformedGames = GameManager::get()->getPlatformedGames().getEntries();
	vector<string> vecDropDownOptions;
	for (PlatformedGame *pPlatformedGame : vecPlatformedGames)
	{
		vecDropDownOptions.push_back(pPlatformedGame->getText());
	}

	int32 iNewPlatformedGameOptionIndex = m_pMainWindow->showDropDownWindow("Convert TXD to Game", "Convert selected TXD entries to game", vecDropDownOptions);
	if (iNewPlatformedGameOptionIndex == -1)
	{
		return onAbortTask();
	}
	PlatformedGame *pNewPlatformedGame = vecPlatformedGames[iNewPlatformedGameOptionIndex];
	EPlatformedGame uiNewPlatformedGame = pNewPlatformedGame->getPlatformedGameId();
	string strNewPlatformedGameText = pNewPlatformedGame->getText();

	uint32 uiSelectedRowCount = getIMGTab()->getEntryGrid()->getSelectedRowCount();
	setMaxProgress(uiSelectedRowCount);

	uint32 uiConvertedEntryCount = 0;
	for (GridRow *pRow : getIMGTab()->getEntryGrid()->getSelectedRows())
	{
		IMGEntry *pIMGEntry = (IMGEntry*)pRow->getUserData();

		if (pIMGEntry->isTextureFile())
		{
			TXDFormat txdFile(pIMGEntry->getEntryData(), false);
			vector<string> vecMipmapsRemoved;
			if (txdFile.unserialize())
			{
				txdFile.convertToGame(uiNewPlatformedGame, vecMipmapsRemoved);

				string strNewFileData = txdFile.serialize();
				pIMGEntry->setEntryData(strNewFileData);

				getIMGTab()->updateGridEntry(pIMGEntry);
				uiConvertedEntryCount++;
			}
			txdFile.unload();
		}

		increaseProgress();
	}

	if (uiSelectedRowCount > 0)
	{
		getIMGTab()->setIMGModifiedSinceRebuild(true);
	}

	getIMGTab()->logf("Converted TXD to game %s for %u entries.", strNewPlatformedGameText.c_str(), uiConvertedEntryCount);

	onCompleteTask();
}

void		Tasks::convertSelectedTXDToTextureFormat(void)
{
	onStartTask("convertSelectedTXDToTextureFormat");

	vector<RasterDataFormat*> vecRasterDataFormats = ImageManager::get()->getRasterDataFormatManager()->getEntries();
	vector<string> vecDropDownOptions;
	for (RasterDataFormat *pRasterDataFormat : vecRasterDataFormats)
	{
		vecDropDownOptions.push_back(pRasterDataFormat->getText());
	}

	int32 iNewTextureFormatOptionIndex = m_pMainWindow->showDropDownWindow("Convert TXD to Texture Format", "Convert selected TXD entries to texture format", vecDropDownOptions);
	if (iNewTextureFormatOptionIndex == -1)
	{
		return onAbortTask();
	}
	RasterDataFormat *pNewRasterDataFormat = vecRasterDataFormats[iNewTextureFormatOptionIndex];
	ERasterDataFormat uiNewRasterDataFormat = pNewRasterDataFormat->getRasterDataFormatId();
	string strNewRasterDataFormatText = pNewRasterDataFormat->getText();

	uint32 uiSelectedRowCount = getIMGTab()->getEntryGrid()->getSelectedRowCount();
	setMaxProgress(uiSelectedRowCount);

	uint32 uiConvertedEntryCount = 0;
	for (GridRow *pRow : getIMGTab()->getEntryGrid()->getSelectedRows())
	{
		IMGEntry *pIMGEntry = (IMGEntry*)pRow->getUserData();

		if (pIMGEntry->isTextureFile())
		{
			TXDFormat txdFile(pIMGEntry->getEntryData(), false);
			vector<string> vecMipmapsRemoved;
			if (txdFile.unserialize())
			{
				txdFile.convertToRasterDataFormat(pNewRasterDataFormat->getRasterDataFormatId(), vecMipmapsRemoved);

				string strNewFileData = txdFile.serialize();
				pIMGEntry->setEntryData(strNewFileData);

				getIMGTab()->updateGridEntry(pIMGEntry);
				uiConvertedEntryCount++;
			}
			txdFile.unload();
		}

		increaseProgress();
	}

	if (uiSelectedRowCount > 0)
	{
		getIMGTab()->setIMGModifiedSinceRebuild(true);
	}

	getIMGTab()->logf("Converted TXD to texture format %s for %u entries.", strNewRasterDataFormatText.c_str(), uiConvertedEntryCount);

	onCompleteTask();
}

void			Tasks::convertWTDFileToTXDFile(void)
{
	onStartTask("convertWTDFileToTXDFile");

	uint32 uiSelectedRowCount = getIMGTab()->getEntryGrid()->getSelectedRowCount();
	setMaxProgress(uiSelectedRowCount);

	uint32 uiConvertedEntryCount = 0;
	for (GridRow *pRow : getIMGTab()->getEntryGrid()->getSelectedRows())
	{
		IMGEntry *pIMGEntry = (IMGEntry*)pRow->getUserData();

		if (pIMGEntry->isTextureFile() && !pIMGEntry->isRWFile())
		{
			WTDFormat wtdFile(pIMGEntry->getEntryData(), false);
			if (wtdFile.unserialize())
			{
				IntermediateTextureFormat *pGeneralTextureFile = wtdFile.convertToIntermediateFormat();
				TXDFormat *pTXDFile = TXDManager::get()->convertIntermediateTextureFileToTXDFile(pGeneralTextureFile);
				pGeneralTextureFile->unload();
				delete pGeneralTextureFile;
				string strTXDFileData = pTXDFile->serialize();
				pTXDFile->unload();
				delete pTXDFile;

				pIMGEntry->setEntryData(strTXDFileData);
				pIMGEntry->setEntryName(Path::replaceFileExtensionWithCase(pIMGEntry->getEntryName(), "txd"));

				getIMGTab()->updateGridEntry(pIMGEntry);
				uiConvertedEntryCount++;
			}
			wtdFile.unload();
		}

		increaseProgress();
	}

	if (uiSelectedRowCount > 0)
	{
		getIMGTab()->setIMGModifiedSinceRebuild(true);
	}

	getIMGTab()->logf("Converted %u WTD entries to TXD entries.", uiConvertedEntryCount);

	onCompleteTask();
}

void		Tasks::selectAll(void)
{
	onStartTask("selectAll");

	IMGEditorTab *pEditorTab = m_pMainWindow->getIMGEditor()->getActiveTab();
	Grid *pEntryGrid = pEditorTab->getEntryGrid();

	pEntryGrid->selectAllRows();
	pEntryGrid->setActiveItem();

	pEditorTab->log("Selected all entries.");

	onCompleteTask();
}

void		Tasks::unselectAll(void)
{
	onStartTask("unselectAll");

	IMGEditorTab *pEditorTab = m_pMainWindow->getIMGEditor()->getActiveTab();
	Grid *pEntryGrid = pEditorTab->getEntryGrid();

	pEntryGrid->unselectAllRows();
	pEntryGrid->setActiveItem();

	pEditorTab->log("Unselected all entries.");

	onCompleteTask();
}

void		Tasks::selectInverse(void)
{
	onStartTask("selectInverse");

	IMGEditorTab *pEditorTab = m_pMainWindow->getIMGEditor()->getActiveTab();
	Grid *pEntryGrid = pEditorTab->getEntryGrid();

	pEntryGrid->selectInverseRows();
	pEntryGrid->setActiveItem();

	pEditorTab->logf("Selected inverse entries. (%u)", pEntryGrid->getSelectedRowCount());

	onCompleteTask();
}

void		Tasks::selectByIndex(void)
{
	onStartTask("selectByIndex");

	NumericMultiOptionInputLayerResult nmoir = m_pMainWindow->showNumericMultiOptionWindow("Select Entries by Index", "Select entries with an index");
	if (nmoir.m_bCancelled)
	{
		return onAbortTask();
	}

	uint32 uiTotalEntryCount = getIMGTab()->getEntryGrid()->getEntryCount();
	setMaxProgress(uiTotalEntryCount * 2);

	vector<IMGEntry*> vecIMGEntries = getIMGTab()->getEntriesByNumericMultiOptionValues(0, nmoir.m_uiOptionIndex, nmoir.m_uiTextBoxValue1, nmoir.m_uiTextBoxValue2); // todo - magic int
	setMaxProgress(uiTotalEntryCount + vecIMGEntries.size(), false);
	for (IMGEntry *pIMGEntry : vecIMGEntries)
	{
		getIMGTab()->getEntryGrid()->getRowByUserData((uint32)pIMGEntry)->setSelected(true);
		increaseProgress();
	}
	getIMGTab()->getEntryGrid()->setActiveItem();

	getIMGTab()->logf("Selected %u entries with an index %s.", vecIMGEntries.size(), nmoir.getMessageText().c_str());

	onCompleteTask();
}

void		Tasks::selectByName(void)
{
	onStartTask("selectByName");

	string strEntryNameInput = m_pMainWindow->showSingleLineTextBoxWindow("Select Entries by Name", "Select entries with a name that includes:");
	if (strEntryNameInput == "")
	{
		return onAbortTask();
	}

	uint32 uiTotalEntryCount = getIMGTab()->getEntryGrid()->getEntryCount();
	setMaxProgress(uiTotalEntryCount * 2);

	vector<IMGEntry*> vecIMGEntries = getIMGTab()->getIMGFile()->getEntriesByName(strEntryNameInput);
	setMaxProgress(uiTotalEntryCount + vecIMGEntries.size(), false); // todo - increaseMaxProgress
	for (IMGEntry *pIMGEntry : vecIMGEntries)
	{
		getIMGTab()->getEntryGrid()->getRowByUserData((uint32)pIMGEntry)->setSelected(true);
		increaseProgress();
	}
	getIMGTab()->getEntryGrid()->setActiveItem();

	getIMGTab()->logf("Selected %u entries with a name that includes %s.", vecIMGEntries.size(), strEntryNameInput.c_str());

	onCompleteTask();
}

void		Tasks::selectByOffset(void)
{
	onStartTask("selectByOffset");

	NumericMultiOptionInputLayerResult nmoir = m_pMainWindow->showNumericMultiOptionWindow("Select Entries by Offset", "Select entries with an offset");
	if (nmoir.m_bCancelled)
	{
		return onAbortTask();
	}

	uint32 uiTotalEntryCount = getIMGTab()->getEntryGrid()->getEntryCount();
	setMaxProgress(uiTotalEntryCount * 2);

	vector<IMGEntry*> vecIMGEntries = getIMGTab()->getEntriesByNumericMultiOptionValues(2, nmoir.m_uiOptionIndex, nmoir.m_uiTextBoxValue1, nmoir.m_uiTextBoxValue2); // todo - magic int
	setMaxProgress(uiTotalEntryCount + vecIMGEntries.size(), false);
	for (IMGEntry *pIMGEntry : vecIMGEntries)
	{
		getIMGTab()->getEntryGrid()->getRowByUserData((uint32)pIMGEntry)->setSelected(true);
		increaseProgress();
	}
	getIMGTab()->getEntryGrid()->setActiveItem();

	getIMGTab()->logf("Selected %u entries with an offset %s.", vecIMGEntries.size(), nmoir.getMessageText().c_str());

	onCompleteTask();
}

void		Tasks::selectBySize(void)
{
	onStartTask("selectBySize");

	NumericMultiOptionInputLayerResult nmoir = m_pMainWindow->showNumericMultiOptionWindow("Select Entries by Size", "Select entries with a size");
	if (nmoir.m_bCancelled)
	{
		return onAbortTask();
	}

	uint32 uiTotalEntryCount = getIMGTab()->getEntryGrid()->getEntryCount();
	setMaxProgress(uiTotalEntryCount * 2);

	vector<IMGEntry*> vecIMGEntries = getIMGTab()->getEntriesByNumericMultiOptionValues(3, nmoir.m_uiOptionIndex, nmoir.m_uiTextBoxValue1, nmoir.m_uiTextBoxValue2); // todo - magic int
	setMaxProgress(uiTotalEntryCount + vecIMGEntries.size(), false);
	for (IMGEntry *pIMGEntry : vecIMGEntries)
	{
		getIMGTab()->getEntryGrid()->getRowByUserData((uint32)pIMGEntry)->setSelected(true);
		increaseProgress();
	}
	getIMGTab()->getEntryGrid()->setActiveItem();

	getIMGTab()->logf("Selected %u entries with a size %s.", vecIMGEntries.size(), nmoir.getMessageText().c_str());

	onCompleteTask();
}

void		Tasks::selectByType(void)
{
	onStartTask("selectByType");

	string strEntryTypeInput = m_pMainWindow->showSingleLineTextBoxWindow("Select Entries by Type", "Select entries with a type that includes:");
	if (strEntryTypeInput == "")
	{
		return onAbortTask();
	}

	uint32 uiTotalEntryCount = getIMGTab()->getEntryGrid()->getEntryCount();
	setMaxProgress(uiTotalEntryCount * 2);

	vector<IMGEntry*> vecIMGEntries = getIMGTab()->getIMGFile()->getEntriesByExtension(strEntryTypeInput, true);
	setMaxProgress(uiTotalEntryCount + vecIMGEntries.size(), false); // todo - increaseMaxProgress
	for (IMGEntry *pIMGEntry : vecIMGEntries)
	{
		getIMGTab()->getEntryGrid()->getRowByUserData((uint32)pIMGEntry)->setSelected(true);
		increaseProgress();
	}
	getIMGTab()->getEntryGrid()->setActiveItem();

	getIMGTab()->logf("Selected %u entries with a type that includes %s.", vecIMGEntries.size(), strEntryTypeInput.c_str());

	onCompleteTask();
}

void		Tasks::selectByVersion(void)
{
	onStartTask("selectByVersion");

	DropDown *pVersionFilter = getIMGTab()->getEntryVersionFilter();
	vector<string> vecVersionOptions = pVersionFilter->getItems();
	int32 iVersionOptionIndex = m_pMainWindow->showDropDownWindow("Select Entries by Version", "Select entries with version", vecVersionOptions);
	if (iVersionOptionIndex == -1)
	{
		return onAbortTask();
	}

	uint32 uiTotalEntryCount = getIMGTab()->getEntryGrid()->getEntryCount();
	setMaxProgress(uiTotalEntryCount * 2);

	DropDownItem
		*pDropDownItem = pVersionFilter->getEntryByIndex(iVersionOptionIndex);
	uint32
		uiFileTypeId = pDropDownItem->getUserdata2(), // todo - rename to getUserData2()
		uiFileVersionId = pDropDownItem->getUserdata(); // todo - rename to getUserData()

	vector<IMGEntry*> vecIMGEntries = getIMGTab()->getIMGFile()->getEntriesByVersion(uiFileTypeId, uiFileVersionId);
	setMaxProgress(uiTotalEntryCount + vecIMGEntries.size(), false); // todo - increaseMaxProgress
	for (IMGEntry *pIMGEntry : vecIMGEntries)
	{
		getIMGTab()->getEntryGrid()->getRowByUserData((uint32)pIMGEntry)->setSelected(true);
		increaseProgress();
	}
	getIMGTab()->getEntryGrid()->setActiveItem();

	getIMGTab()->logf("Selected %u entries with version %s.", vecIMGEntries.size(), RWVersion::unpackVersionStampAsStringWithBuild(uiFileVersionId).c_str());

	onCompleteTask();
}

void		Tasks::selectByIDE(void)
{
	onStartTask("selectByIDE");

	IDEInputWindowResult ideInputWindowResult = getIMGF()->getWindowManager()->showIDEInputWindow("Select in IMG by IDE", "Choose IDE items to select in the IMG:");
	if (getIMGF()->getWindowManager()->m_bWindow2Cancelled)
	{
		return onAbortTask();
	}

	vector<string> vecIDEFilePaths = openFile("IDE");
	if (vecIDEFilePaths.size() == 0)
	{
		return onAbortTask();
	}

	// fetch chosen IDE sections from input window
	vector<EIDESection>
		vecModelSections,
		vecTextureSections;
	ideInputWindowResult.getIDESections(vecModelSections, vecTextureSections);

	// fetch model and TXD names from IDE file
	setMaxProgress(vecIDEFilePaths.size() * 3);

	set<string>
		stModelNames,
		stTextureSetNames;
	IDEManager::getModelAndTextureSetNamesFromFiles(vecIDEFilePaths, stModelNames, stTextureSetNames, vecModelSections, vecTextureSections);

	// fetch model and TXD names from DFF/TXD files inside IMG file
	setMaxProgress((vecIDEFilePaths.size() * 2) + getIMGTab()->getIMGFile()->getEntryCount());

	unordered_map<IMGEntry*, vector<string>>
		umapIMGModelNames,
		umapIMGTextureSetNames;
	getIMGTab()->getIMGFile()->getModelAndTextureSetNamesFromEntries(umapIMGModelNames, umapIMGTextureSetNames);

	// choose IMG entries that have a model name or TXD name found in IDE file
	vector<IMGEntry*> vecIMGEntries = StdVector::getKeysWithMatchingEntries(umapIMGModelNames, stModelNames);
	StdVector::addToVector(vecIMGEntries, StdVector::getKeysWithMatchingEntries(umapIMGTextureSetNames, stTextureSetNames));

	// export the IMG entries
	setMaxProgress((vecIDEFilePaths.size() * 2) + getIMGTab()->getIMGFile()->getEntryCount() + vecIMGEntries.size());
	for (IMGEntry *pIMGEntry : vecIMGEntries)
	{
		getIMGTab()->getEntryGrid()->getRowByUserData((uint32)pIMGEntry)->setSelected(true);
		increaseProgress();
	}
	getIMGTab()->getEntryGrid()->setActiveItem();

	getIMGTab()->logf("Selected %u entries by %u IDE files.", vecIMGEntries.size(), vecIDEFilePaths.size());

	onCompleteTask();
}

void		Tasks::unselectByIndex(void)
{
	onStartTask("unselectByIndex");

	NumericMultiOptionInputLayerResult nmoir = m_pMainWindow->showNumericMultiOptionWindow("Unselect Entries by Index", "Unselect entries with an index");
	if (nmoir.m_bCancelled)
	{
		return onAbortTask();
	}

	uint32 uiTotalEntryCount = getIMGTab()->getEntryGrid()->getEntryCount();
	setMaxProgress(uiTotalEntryCount * 2);

	vector<IMGEntry*> vecIMGEntries = getIMGTab()->getEntriesByNumericMultiOptionValues(0, nmoir.m_uiOptionIndex, nmoir.m_uiTextBoxValue1, nmoir.m_uiTextBoxValue2); // todo - magic int
	setMaxProgress(uiTotalEntryCount + vecIMGEntries.size(), false);
	for (IMGEntry *pIMGEntry : vecIMGEntries)
	{
		getIMGTab()->getEntryGrid()->getRowByUserData((uint32)pIMGEntry)->setSelected(false);
		increaseProgress();
	}
	getIMGTab()->getEntryGrid()->setActiveItem();

	getIMGTab()->logf("Unselected %u entries with an index %s.", vecIMGEntries.size(), nmoir.getMessageText().c_str());

	onCompleteTask();
}

void		Tasks::unselectByName(void)
{
	onStartTask("unselectByName");

	string strEntryNameInput = m_pMainWindow->showSingleLineTextBoxWindow("Unselect Entries by Name", "Unselect entries with a name that includes:");
	if (strEntryNameInput == "")
	{
		return onAbortTask();
	}

	uint32 uiTotalEntryCount = getIMGTab()->getEntryGrid()->getEntryCount();
	setMaxProgress(uiTotalEntryCount * 2);

	vector<IMGEntry*> vecIMGEntries = getIMGTab()->getIMGFile()->getEntriesByName(strEntryNameInput);
	setMaxProgress(uiTotalEntryCount + vecIMGEntries.size(), false); // todo - increaseMaxProgress
	for (IMGEntry *pIMGEntry : vecIMGEntries)
	{
		getIMGTab()->getEntryGrid()->getRowByUserData((uint32)pIMGEntry)->setSelected(false);
		increaseProgress();
	}
	getIMGTab()->getEntryGrid()->setActiveItem();

	getIMGTab()->logf("Unselected %u entries with a name that includes %s.", vecIMGEntries.size(), strEntryNameInput.c_str());

	onCompleteTask();
}

void		Tasks::unselectByOffset(void)
{
	onStartTask("unselectByOffset");

	NumericMultiOptionInputLayerResult nmoir = m_pMainWindow->showNumericMultiOptionWindow("Unselect Entries by Offset", "Unselect entries with an offset");
	if (nmoir.m_bCancelled)
	{
		return onAbortTask();
	}

	uint32 uiTotalEntryCount = getIMGTab()->getEntryGrid()->getEntryCount();
	setMaxProgress(uiTotalEntryCount * 2);

	vector<IMGEntry*> vecIMGEntries = getIMGTab()->getEntriesByNumericMultiOptionValues(2, nmoir.m_uiOptionIndex, nmoir.m_uiTextBoxValue1, nmoir.m_uiTextBoxValue2); // todo - magic int
	setMaxProgress(uiTotalEntryCount + vecIMGEntries.size(), false);
	for (IMGEntry *pIMGEntry : vecIMGEntries)
	{
		getIMGTab()->getEntryGrid()->getRowByUserData((uint32)pIMGEntry)->setSelected(false);
		increaseProgress();
	}
	getIMGTab()->getEntryGrid()->setActiveItem();

	getIMGTab()->logf("Unselected %u entries with an offset %s.", vecIMGEntries.size(), nmoir.getMessageText().c_str());

	onCompleteTask();
}

void		Tasks::unselectBySize(void)
{
	onStartTask("unselectBySize");

	NumericMultiOptionInputLayerResult nmoir = m_pMainWindow->showNumericMultiOptionWindow("Unselect Entries by Size", "Unselect entries with a size");
	if (nmoir.m_bCancelled)
	{
		return onAbortTask();
	}

	uint32 uiTotalEntryCount = getIMGTab()->getEntryGrid()->getEntryCount();
	setMaxProgress(uiTotalEntryCount * 2);

	vector<IMGEntry*> vecIMGEntries = getIMGTab()->getEntriesByNumericMultiOptionValues(3, nmoir.m_uiOptionIndex, nmoir.m_uiTextBoxValue1, nmoir.m_uiTextBoxValue2); // todo - magic int
	setMaxProgress(uiTotalEntryCount + vecIMGEntries.size(), false);
	for (IMGEntry *pIMGEntry : vecIMGEntries)
	{
		getIMGTab()->getEntryGrid()->getRowByUserData((uint32)pIMGEntry)->setSelected(false);
		increaseProgress();
	}
	getIMGTab()->getEntryGrid()->setActiveItem();

	getIMGTab()->logf("Unselected %u entries with a size %s.", vecIMGEntries.size(), nmoir.getMessageText().c_str());

	onCompleteTask();
}

void		Tasks::unselectByType(void)
{
	onStartTask("unselectByType");

	string strEntryTypeInput = m_pMainWindow->showSingleLineTextBoxWindow("Unselect Entries by Type", "Unselect entries with a type that includes:");
	if (strEntryTypeInput == "")
	{
		return onAbortTask();
	}

	uint32 uiTotalEntryCount = getIMGTab()->getEntryGrid()->getEntryCount();
	setMaxProgress(uiTotalEntryCount * 2);

	vector<IMGEntry*> vecIMGEntries = getIMGTab()->getIMGFile()->getEntriesByExtension(strEntryTypeInput, true);
	setMaxProgress(uiTotalEntryCount + vecIMGEntries.size(), false); // todo - increaseMaxProgress
	for (IMGEntry *pIMGEntry : vecIMGEntries)
	{
		getIMGTab()->getEntryGrid()->getRowByUserData((uint32)pIMGEntry)->setSelected(false);
		increaseProgress();
	}
	getIMGTab()->getEntryGrid()->setActiveItem();

	getIMGTab()->logf("Unselected %u entries with a type that includes %s.", vecIMGEntries.size(), strEntryTypeInput.c_str());

	onCompleteTask();
}

void		Tasks::unselectByVersion(void)
{
	onStartTask("unselectByVersion");

	DropDown *pVersionFilter = getIMGTab()->getEntryVersionFilter();
	vector<string> vecVersionOptions = pVersionFilter->getItems();
	int32 iVersionOptionIndex = m_pMainWindow->showDropDownWindow("Unselect Entries by Version", "Unselect entries with version", vecVersionOptions);
	if (iVersionOptionIndex == -1)
	{
		return onAbortTask();
	}

	uint32 uiTotalEntryCount = getIMGTab()->getEntryGrid()->getEntryCount();
	setMaxProgress(uiTotalEntryCount * 2);

	DropDownItem
		*pDropDownItem = pVersionFilter->getEntryByIndex(iVersionOptionIndex);
	uint32
		uiFileTypeId = pDropDownItem->getUserdata2(), // todo - rename to getUserData2()
		uiFileVersionId = pDropDownItem->getUserdata(); // todo - rename to getUserData()

	vector<IMGEntry*> vecIMGEntries = getIMGTab()->getIMGFile()->getEntriesByVersion(uiFileTypeId, uiFileVersionId);
	setMaxProgress(uiTotalEntryCount + vecIMGEntries.size(), false); // todo - increaseMaxProgress
	for (IMGEntry *pIMGEntry : vecIMGEntries)
	{
		getIMGTab()->getEntryGrid()->getRowByUserData((uint32)pIMGEntry)->setSelected(false);
		increaseProgress();
	}
	getIMGTab()->getEntryGrid()->setActiveItem();

	getIMGTab()->logf("Unselected %u entries with version %s.", vecIMGEntries.size(), RWVersion::unpackVersionStampAsStringWithBuild(uiFileVersionId).c_str());

	onCompleteTask();
}

void		Tasks::unselectByIDE(void)
{
	onStartTask("unselectByIDE");

	IDEInputWindowResult ideInputWindowResult = getIMGF()->getWindowManager()->showIDEInputWindow("Unselect in IMG by IDE", "Choose IDE items to unselect in the IMG:");
	if (getIMGF()->getWindowManager()->m_bWindow2Cancelled)
	{
		return onAbortTask();
	}

	vector<string> vecIDEFilePaths = openFile("IDE");
	if (vecIDEFilePaths.size() == 0)
	{
		return onAbortTask();
	}

	// fetch chosen IDE sections from input window
	vector<EIDESection>
		vecModelSections,
		vecTextureSections;
	ideInputWindowResult.getIDESections(vecModelSections, vecTextureSections);

	// fetch model and TXD names from IDE file
	setMaxProgress(vecIDEFilePaths.size() * 3);

	set<string>
		stModelNames,
		stTextureSetNames;
	IDEManager::getModelAndTextureSetNamesFromFiles(vecIDEFilePaths, stModelNames, stTextureSetNames, vecModelSections, vecTextureSections);

	// fetch model and TXD names from DFF/TXD files inside IMG file
	setMaxProgress((vecIDEFilePaths.size() * 2) + getIMGTab()->getIMGFile()->getEntryCount());

	unordered_map<IMGEntry*, vector<string>>
		umapIMGModelNames,
		umapIMGTextureSetNames;
	getIMGTab()->getIMGFile()->getModelAndTextureSetNamesFromEntries(umapIMGModelNames, umapIMGTextureSetNames);

	// choose IMG entries that have a model name or TXD name found in IDE file
	vector<IMGEntry*> vecIMGEntries = StdVector::getKeysWithMatchingEntries(umapIMGModelNames, stModelNames);
	StdVector::addToVector(vecIMGEntries, StdVector::getKeysWithMatchingEntries(umapIMGTextureSetNames, stTextureSetNames));

	// export the IMG entries
	setMaxProgress((vecIDEFilePaths.size() * 2) + getIMGTab()->getIMGFile()->getEntryCount() + vecIMGEntries.size());
	for (IMGEntry *pIMGEntry : vecIMGEntries)
	{
		getIMGTab()->getEntryGrid()->getRowByUserData((uint32)pIMGEntry)->setSelected(false);
		increaseProgress();
	}
	getIMGTab()->getEntryGrid()->setActiveItem();

	getIMGTab()->logf("Unselected %u entries by %u IDE files.", vecIMGEntries.size(), vecIDEFilePaths.size());

	onCompleteTask();
}

void		Tasks::sortByIndexReverse(void)
{
	onStartTask("sortByIndexReverse");

	uint32 uiTotalEntryCount = getIMGTab()->getEntryGrid()->getEntryCount();
	setMaxProgress(uiTotalEntryCount);

	unordered_map<IMGEntry*, uint32> umapEntryIndexes;
	for (IMGEntry *pIMGEntry : getIMGTab()->getIMGFile()->getEntries())
	{
		umapEntryIndexes[pIMGEntry] = pIMGEntry->getIMGFile()->getIndexByEntry(pIMGEntry);
	}

	auto sortIMGEntries_IndexReverse = [&](IMGEntry *pIMGEntry1, IMGEntry *pIMGEntry2) -> bool
	{
		return umapEntryIndexes[pIMGEntry1] > umapEntryIndexes[pIMGEntry2];
	};
	std::sort(getIMGTab()->getIMGFile()->getEntries().begin(), getIMGTab()->getIMGFile()->getEntries().end(), sortIMGEntries_IndexReverse);

	if (uiTotalEntryCount > 0)
	{
		getIMGTab()->readdGridEntries();
		getIMGTab()->setIMGModifiedSinceRebuild(true);
	}

	getIMGTab()->log("Sorted all entries by index (reverse).");

	onCompleteTask();
}

void		Tasks::sortByNameAscending09AZ(void)
{
	onStartTask("sortByNameAscending09AZ");

	uint32 uiTotalEntryCount = getIMGTab()->getEntryGrid()->getEntryCount();
	setMaxProgress(uiTotalEntryCount);

	auto sortIMGEntries_NameAscending09AZ = [](IMGEntry *pIMGEntry1, IMGEntry *pIMGEntry2) -> bool
	{
		return strcmp(String::toLowerCase(pIMGEntry1->getEntryName()).c_str(), String::toLowerCase(pIMGEntry2->getEntryName()).c_str()) < 0;
	};
	std::sort(getIMGTab()->getIMGFile()->getEntries().begin(), getIMGTab()->getIMGFile()->getEntries().end(), sortIMGEntries_NameAscending09AZ);

	if (uiTotalEntryCount > 0)
	{
		getIMGTab()->readdGridEntries();
		getIMGTab()->setIMGModifiedSinceRebuild(true);
	}

	getIMGTab()->log("Sorted all entries by name (ascending 0-9 A-Z).");

	onCompleteTask();
}

void		Tasks::sortByNameAscendingAZ09(void)
{
	// todo
	/*
	onStartTask("sortByNameAscendingAZ09");

	uint32 uiTotalEntryCount = getIMGTab()->getEntryGrid()->getEntryCount();
	setMaxProgress(uiTotalEntryCount);

	auto sortIMGEntries_NameAscendingAZ09 = [](IMGEntry *pIMGEntry1, IMGEntry *pIMGEntry2) -> bool
	{
		const char
			*pEntryName1 = pIMGEntry1->getEntryName().c_str(),
			*pEntryName2 = pIMGEntry2->getEntryName().c_str();
		for (uint32 i = 0, j = pIMGEntry1->getEntryName().length(); i < j; i++)
		{
			bool
				bEntry1CharIsDigit = pEntryName1[i] >= 48 && pEntryName1[i] <= 57,
				bEntry2CharIsDigit = pEntryName2[i] >= 48 && pEntryName2[i] <= 57;
			if (bEntry1CharIsDigit && !bEntry2CharIsDigit)
			{
				return false;
			}
			else if (!bEntry1CharIsDigit && bEntry2CharIsDigit)
			{
				return true;
			}
			else if (bEntry1CharIsDigit && bEntry2CharIsDigit)
			{
				continue;
			}
			else if (!bEntry1CharIsDigit && !bEntry2CharIsDigit)
			{
				continue;
			}
		}

		return strcmp(String::toLowerCase(pIMGEntry1->getEntryName()).c_str(), String::toLowerCase(pIMGEntry2->getEntryName()).c_str()) < 0;
	};
	std::sort(getIMGTab()->getIMGFile()->getEntries().begin(), getIMGTab()->getIMGFile()->getEntries().end(), sortIMGEntries_NameAscendingAZ09);

	if (uiTotalEntryCount > 0)
	{
		getIMGTab()->readdGridEntries();
		getIMGTab()->setIMGModifiedSinceRebuild(true);
	}

	getIMGTab()->log("Sorted all entries by name (ascending A-Z 0-9).");

	onCompleteTask();
	*/
}


void		Tasks::sortByNameDescendingZA90(void)
{
	onStartTask("sortByNameDescendingZA90");

	uint32 uiTotalEntryCount = getIMGTab()->getEntryGrid()->getEntryCount();
	setMaxProgress(uiTotalEntryCount);

	auto sortIMGEntries_NameDescendingZA90 = [](IMGEntry *pIMGEntry1, IMGEntry *pIMGEntry2) -> bool
	{
		return strcmp(String::toLowerCase(pIMGEntry1->getEntryName()).c_str(), String::toLowerCase(pIMGEntry2->getEntryName()).c_str()) > 0;
	};
	std::sort(getIMGTab()->getIMGFile()->getEntries().begin(), getIMGTab()->getIMGFile()->getEntries().end(), sortIMGEntries_NameDescendingZA90);

	if (uiTotalEntryCount > 0)
	{
		getIMGTab()->readdGridEntries();
		getIMGTab()->setIMGModifiedSinceRebuild(true);
	}

	getIMGTab()->log("Sorted all entries by name (descending Z-A 9-0).");

	onCompleteTask();
}

void		Tasks::sortByNameDescending90ZA(void)
{
	// todo
}

void		Tasks::sortByOffsetLowHigh(void)
{
	onStartTask("sortByOffsetLowHigh");

	uint32 uiTotalEntryCount = getIMGTab()->getEntryGrid()->getEntryCount();
	setMaxProgress(uiTotalEntryCount);

	auto sortIMGEntries_OffsetLowToHigh = [](IMGEntry *pIMGEntry1, IMGEntry *pIMGEntry2) -> bool
	{
		return pIMGEntry1->getEntryOffset() < pIMGEntry2->getEntryOffset();
	};
	std::sort(getIMGTab()->getIMGFile()->getEntries().begin(), getIMGTab()->getIMGFile()->getEntries().end(), sortIMGEntries_OffsetLowToHigh);

	if (uiTotalEntryCount > 0)
	{
		getIMGTab()->readdGridEntries();
		getIMGTab()->setIMGModifiedSinceRebuild(true);
	}

	getIMGTab()->log("Sorted all entries by offset (low to high).");

	onCompleteTask();
}

void		Tasks::sortByOffsetHighLow(void)
{
	onStartTask("sortByOffsetHighLow");

	uint32 uiTotalEntryCount = getIMGTab()->getEntryGrid()->getEntryCount();
	setMaxProgress(uiTotalEntryCount);

	auto sortIMGEntries_OffsetHighToLow = [](IMGEntry *pIMGEntry1, IMGEntry *pIMGEntry2) -> bool
	{
		return pIMGEntry1->getEntryOffset() > pIMGEntry2->getEntryOffset();
	};
	std::sort(getIMGTab()->getIMGFile()->getEntries().begin(), getIMGTab()->getIMGFile()->getEntries().end(), sortIMGEntries_OffsetHighToLow);

	if (uiTotalEntryCount > 0)
	{
		getIMGTab()->readdGridEntries();
		getIMGTab()->setIMGModifiedSinceRebuild(true);
	}

	getIMGTab()->log("Sorted all entries by offset (high to low).");

	onCompleteTask();
}

void		Tasks::sortBySizeSmallBig(void)
{
	onStartTask("sortBySizeSmallBig");

	uint32 uiTotalEntryCount = getIMGTab()->getEntryGrid()->getEntryCount();
	setMaxProgress(uiTotalEntryCount);

	auto sortIMGEntries_SizeSmallToBig = [](IMGEntry *pIMGEntry1, IMGEntry *pIMGEntry2) -> bool
	{
		return pIMGEntry1->getEntrySize() < pIMGEntry2->getEntrySize();
	};
	std::sort(getIMGTab()->getIMGFile()->getEntries().begin(), getIMGTab()->getIMGFile()->getEntries().end(), sortIMGEntries_SizeSmallToBig);

	if (uiTotalEntryCount > 0)
	{
		getIMGTab()->readdGridEntries();
		getIMGTab()->setIMGModifiedSinceRebuild(true);
	}

	getIMGTab()->log("Sorted all entries by size (small to big).");

	onCompleteTask();
}

void		Tasks::sortBySizeBigSmall(void)
{
	onStartTask("sortBySizeBigSmall");

	uint32 uiTotalEntryCount = getIMGTab()->getEntryGrid()->getEntryCount();
	setMaxProgress(uiTotalEntryCount);

	auto sortIMGEntries_SizeBigToSmall = [](IMGEntry *pIMGEntry1, IMGEntry *pIMGEntry2) -> bool
	{
		return pIMGEntry1->getEntrySize() > pIMGEntry2->getEntrySize();
	};
	std::sort(getIMGTab()->getIMGFile()->getEntries().begin(), getIMGTab()->getIMGFile()->getEntries().end(), sortIMGEntries_SizeBigToSmall);

	if (uiTotalEntryCount > 0)
	{
		getIMGTab()->readdGridEntries();
		getIMGTab()->setIMGModifiedSinceRebuild(true);
	}

	getIMGTab()->log("Sorted all entries by size (big to small).");

	onCompleteTask();
}

void		Tasks::sortByTypeAZ(void)
{
	onStartTask("sortByTypeAZ");

	uint32 uiTotalEntryCount = getIMGTab()->getEntryGrid()->getEntryCount();
	setMaxProgress(uiTotalEntryCount);

	auto sortIMGEntries_TypeAscending09AZ = [](IMGEntry *pIMGEntry1, IMGEntry *pIMGEntry2) -> bool
	{
		return strcmp(String::toLowerCase(pIMGEntry1->getEntryExtension()).c_str(), String::toLowerCase(pIMGEntry2->getEntryExtension()).c_str()) < 0;
	};
	std::sort(getIMGTab()->getIMGFile()->getEntries().begin(), getIMGTab()->getIMGFile()->getEntries().end(), sortIMGEntries_TypeAscending09AZ);

	if (uiTotalEntryCount > 0)
	{
		getIMGTab()->readdGridEntries();
		getIMGTab()->setIMGModifiedSinceRebuild(true);
	}

	getIMGTab()->log("Sorted all entries by type (ascending 0-9 A-Z).");

	onCompleteTask();
}

void		Tasks::sortByTypeZA(void)
{
	onStartTask("sortByTypeZA");

	uint32 uiTotalEntryCount = getIMGTab()->getEntryGrid()->getEntryCount();
	setMaxProgress(uiTotalEntryCount);

	auto sortIMGEntries_TypeDescendingZA90 = [](IMGEntry *pIMGEntry1, IMGEntry *pIMGEntry2) -> bool
	{
		return strcmp(String::toLowerCase(pIMGEntry1->getEntryExtension()).c_str(), String::toLowerCase(pIMGEntry2->getEntryExtension()).c_str()) > 0;
	};
	std::sort(getIMGTab()->getIMGFile()->getEntries().begin(), getIMGTab()->getIMGFile()->getEntries().end(), sortIMGEntries_TypeDescendingZA90);

	if (uiTotalEntryCount > 0)
	{
		getIMGTab()->readdGridEntries();
		getIMGTab()->setIMGModifiedSinceRebuild(true);
	}

	getIMGTab()->log("Sorted all entries by type (descending Z-A 9-0).");

	onCompleteTask();
}

void		Tasks::sortByVersionOldNew(void)
{
	onStartTask("sortByVersionOldNew");

	uint32 uiTotalEntryCount = getIMGTab()->getEntryGrid()->getEntryCount();
	setMaxProgress(uiTotalEntryCount);

	auto sortIMGEntries_VersionOldToNew = [](IMGEntry *pIMGEntry1, IMGEntry *pIMGEntry2) -> bool
	{
		return pIMGEntry1->getRawVersion() < pIMGEntry2->getRawVersion();
	};
	std::sort(getIMGTab()->getIMGFile()->getEntries().begin(), getIMGTab()->getIMGFile()->getEntries().end(), sortIMGEntries_VersionOldToNew);

	if (uiTotalEntryCount > 0)
	{
		getIMGTab()->readdGridEntries();
		getIMGTab()->setIMGModifiedSinceRebuild(true);
	}

	getIMGTab()->log("Sorted all entries by version (old to new).");

	onCompleteTask();
}

void		Tasks::sortByVersionNewOld(void)
{
	onStartTask("sortByVersionNewOld");

	uint32 uiTotalEntryCount = getIMGTab()->getEntryGrid()->getEntryCount();
	setMaxProgress(uiTotalEntryCount);

	auto sortIMGEntries_VersionNewToOld = [](IMGEntry *pIMGEntry1, IMGEntry *pIMGEntry2) -> bool
	{
		return pIMGEntry1->getRawVersion() > pIMGEntry2->getRawVersion();
	};
	std::sort(getIMGTab()->getIMGFile()->getEntries().begin(), getIMGTab()->getIMGFile()->getEntries().end(), sortIMGEntries_VersionNewToOld);

	if (uiTotalEntryCount > 0)
	{
		getIMGTab()->readdGridEntries();
		getIMGTab()->setIMGModifiedSinceRebuild(true);
	}

	getIMGTab()->log("Sorted all entries by version (new to old).");

	onCompleteTask();
}

void		Tasks::lst(void)
{
	onStartTask("lst");

	string strGameFolderPath = openFolder("Choose a game folder to run the LST file on.");
	if (strGameFolderPath == "")
	{
		return onAbortTask();
	}

	vector<string> vecLSTFilePaths = openFile("LST");
	if (vecLSTFilePaths.size() == 0)
	{
		return onAbortTask();
	}

	setMaxProgress(vecLSTFilePaths.size());

	LSTProcessingManager *lstProcessingManager = getIMGF()->getLSTProcessingManager();
	for (string& strLSTFilePath : vecLSTFilePaths)
	{
		LSTFormat lstFormat(strLSTFilePath);
		if (lstFormat.unserialize())
		{
			lstProcessingManager->process(&lstFormat);
		}
		lstFormat.unload();

		increaseProgress();
	}

	getIMGTab()->logf("Processed %u LST files.", vecLSTFilePaths.size());

	onCompleteTask();
}

// entry
void						Tasks::nameCaseLower(void)
{
	onStartTask("nameCaseLower");

	getIMGTab()->setSelectedEntriesNameCase(0);
	getIMGTab()->logf("Set entry name to lower case for %u entries.", getIMGTab()->getSelectedEntryCount());

	onCompleteTask();
}

void						Tasks::nameCaseUpper(void)
{
	onStartTask("nameCaseUpper");

	getIMGTab()->setSelectedEntriesNameCase(1);
	getIMGTab()->logf("Set entry name to UPPER CASE for %u entries.", getIMGTab()->getSelectedEntryCount());

	onCompleteTask();
}

void						Tasks::nameCaseTitle(void)
{
	onStartTask("nameCaseTitle");

	getIMGTab()->setSelectedEntriesNameCase(2);
	getIMGTab()->logf("Set entry name to Title Case for %u entries.", getIMGTab()->getSelectedEntryCount());

	onCompleteTask();
}

void						Tasks::copyEntryIndex(void)
{
	onStartTask("copyEntryIndex");

	getIMGTab()->copySelectedEntryData(0);
	getIMGTab()->logf("Copied entry index for %u entries.", getIMGTab()->getSelectedEntryCount());

	onCompleteTask();
}

void						Tasks::copyEntryType(void)
{
	onStartTask("copyEntryType");

	getIMGTab()->copySelectedEntryData(1);
	getIMGTab()->logf("Copied entry type for %u entries.", getIMGTab()->getSelectedEntryCount());

	onCompleteTask();
}

void						Tasks::copyEntryName(void)
{
	onStartTask("copyEntryName");

	getIMGTab()->copySelectedEntryData(2);
	getIMGTab()->logf("Copied entry name for %u entries.", getIMGTab()->getSelectedEntryCount());

	onCompleteTask();
}

void						Tasks::copyEntryOffset(void)
{
	onStartTask("copyEntryOffset");

	getIMGTab()->copySelectedEntryData(3);
	getIMGTab()->logf("Copied entry offset for %u entries.", getIMGTab()->getSelectedEntryCount());

	onCompleteTask();
}

void						Tasks::copyEntrySize(void)
{
	onStartTask("copyEntrySize");

	getIMGTab()->copySelectedEntryData(4);
	getIMGTab()->logf("Copied entry size for %u entries.", getIMGTab()->getSelectedEntryCount());

	onCompleteTask();
}

void						Tasks::copyEntryVersion(void)
{
	onStartTask("copyEntryVersion");

	getIMGTab()->copySelectedEntryData(5);
	getIMGTab()->logf("Copied entry version for %u entries.", getIMGTab()->getSelectedEntryCount());

	onCompleteTask();
}

void						Tasks::copyEntryRowData(void)
{
	onStartTask("copyEntryRowData");

	getIMGTab()->copySelectedEntryData(6);
	getIMGTab()->logf("Copied row data for %u entries.", getIMGTab()->getSelectedEntryCount());

	onCompleteTask();
}

void						Tasks::shiftEntryUp1Row(void)
{
	onStartTask("shiftEntryUp1Row");

	getIMGTab()->shiftSelectedEntries(-1);
	getIMGTab()->logf("Shifted %u entries up by %u rows.", getIMGTab()->getSelectedEntryCount(), 1);

	onCompleteTask();
}

void						Tasks::shiftEntryUp5Rows(void)
{
	onStartTask("shiftEntryUp5Rows");

	getIMGTab()->shiftSelectedEntries(-5);
	getIMGTab()->logf("Shifted %u entries up by %u rows.", getIMGTab()->getSelectedEntryCount(), 5);

	onCompleteTask();
}

void						Tasks::shiftEntryUp10Rows(void)
{
	onStartTask("shiftEntryUp10Rows");

	getIMGTab()->shiftSelectedEntries(-10);
	getIMGTab()->logf("Shifted %u entries up by %u rows.", getIMGTab()->getSelectedEntryCount(), 10);

	onCompleteTask();
}

void						Tasks::shiftEntryUp100Rows(void)
{
	onStartTask("shiftEntryUp100Rows");

	getIMGTab()->shiftSelectedEntries(-100);
	getIMGTab()->logf("Shifted %u entries up by %u rows.", getIMGTab()->getSelectedEntryCount(), 100);

	onCompleteTask();
}

void						Tasks::shiftEntryUp1000Rows(void)
{
	onStartTask("shiftEntryUp1000Rows");

	getIMGTab()->shiftSelectedEntries(-1000);
	getIMGTab()->logf("Shifted %u entries up by %u rows.", getIMGTab()->getSelectedEntryCount(), 1000);

	onCompleteTask();
}

void						Tasks::shiftEntryDown1Row(void)
{
	onStartTask("shiftEntryDown1Row");

	getIMGTab()->shiftSelectedEntries(1);
	getIMGTab()->logf("Shifted %u entries down by %u rows.", getIMGTab()->getSelectedEntryCount(), 1);

	onCompleteTask();
}

void						Tasks::shiftEntryDown5Rows(void)
{
	onStartTask("shiftEntryDown5Rows");

	getIMGTab()->shiftSelectedEntries(5);
	getIMGTab()->logf("Shifted %u entries down by %u rows.", getIMGTab()->getSelectedEntryCount(), 5);

	onCompleteTask();
}

void						Tasks::shiftEntryDown10Rows(void)
{
	onStartTask("shiftEntryDown10Rows");

	getIMGTab()->shiftSelectedEntries(10);
	getIMGTab()->logf("Shifted %u entries down by %u rows.", getIMGTab()->getSelectedEntryCount(), 10);

	onCompleteTask();
}

void						Tasks::shiftEntryDown100Rows(void)
{
	onStartTask("shiftEntryDown100Rows");

	getIMGTab()->shiftSelectedEntries(100);
	getIMGTab()->logf("Shifted %u entries down by %u rows.", getIMGTab()->getSelectedEntryCount(), 100);

	onCompleteTask();
}

void						Tasks::shiftEntryDown1000Rows(void)
{
	onStartTask("shiftEntryDown1000Rows");

	getIMGTab()->shiftSelectedEntries(1000);
	getIMGTab()->logf("Shifted %u entries down by %u rows.", getIMGTab()->getSelectedEntryCount(), 1000);

	onCompleteTask();
}

// orphan entries
void						Tasks::removeOrphanTexturesFromDFFEntries(void)
{
	onStartTask("removeOrphanTexturesFromDFFEntries");

	vector<string> vecTXDFilePaths = openFile("txd");
	if (vecTXDFilePaths.size() == 0)
	{
		return onAbortTask();
	}

	// progess bar
	uint32 uiSelectedDFFCount = 0;
	for (IMGEntry *pIMGEntry : getIMGTab()->getSelectedEntries())
	{
		if (pIMGEntry->isModelFile())
		{
			uiSelectedDFFCount++;
		}
	}
	setMaxProgress((uiSelectedDFFCount  * 2) + vecTXDFilePaths.size());

	// fetch texture names from DFF files (selected IMG entries)
	vector<string> vecDFFTextureNames;
	vector<DFFFormat*> vecDFFFormatsInput;
	vector<IMGEntry*> vecIMGEntries;
	uint32 uiProgressMaxTicksDecudctionForCorruptDFFFiles = 0;
	for (IMGEntry *pIMGEntry : getIMGTab()->getSelectedEntries())
	{
		if (pIMGEntry->isModelFile())
		{
			DFFFormat *pDFFFile = DFFManager::unserializeMemory(pIMGEntry->getEntryData());
			if (pDFFFile->unserialize())
			{
				StdVector::addToVector(vecDFFTextureNames, pDFFFile->getTextureNames());
				vecDFFFormatsInput.push_back(pDFFFile);
				vecIMGEntries.push_back(pIMGEntry);
			}
			else
			{
				uiProgressMaxTicksDecudctionForCorruptDFFFiles++;
				pDFFFile->unload();
				delete pDFFFile;
			}
			increaseProgress();
		}
	}
	setMaxProgress(getIMGF()->getTaskManager()->getTaskMaxProgressTickCount() - uiProgressMaxTicksDecudctionForCorruptDFFFiles); // for below

	// fetch texture names from TXD files (files input)
	vector<string> vecTXDTextureNames;
	for (string& strTXDFilePath : vecTXDFilePaths)
	{
		TXDFormat txdFile(strTXDFilePath);
		if (txdFile.unserialize())
		{
			StdVector::addToVector(vecTXDTextureNames, txdFile.getTextureNames());
		}
		txdFile.unload();
		increaseProgress();
	}

	// find texture names found in DFF files but not found in TXD files
	vecTXDTextureNames = StdVector::toUpperCase(vecTXDTextureNames);
	unordered_map<string, bool> umapTXDTextureNames = StdVector::convertVectorToUnorderedMap(vecTXDTextureNames);
	vecTXDTextureNames.clear();

	vector<string> vecTexturesInDFFMissingFromTXD;
	unordered_map<string, bool> umapTexturesInDFFMissingFromTXD;
	for (string& strDFFTextureName : vecDFFTextureNames)
	{
		string strDFFTextureNameUpper = String::toUpperCase(strDFFTextureName);
		if (umapTXDTextureNames.count(strDFFTextureNameUpper) == 0)
		{
			if (umapTexturesInDFFMissingFromTXD.count(strDFFTextureNameUpper) == 0)
			{
				umapTexturesInDFFMissingFromTXD[strDFFTextureNameUpper] = true;
				vecTexturesInDFFMissingFromTXD.push_back(strDFFTextureName);
			}
		}
	}
	umapTexturesInDFFMissingFromTXD.clear();

	// remove textures entries from DFF files that are not found in TXD files
	uint32 i = 0;
	uint32 uiDFFFileCountWithRemovedSections = 0;
	for (DFFFormat *pDFFFile : vecDFFFormatsInput)
	{
		bool bRemovedSection = false;
		for (string& strDFFTextureName : vecTexturesInDFFMissingFromTXD)
		{
			TextureEntry *pDFFTextureEntry = pDFFFile->getTextureByDiffuseOrAlphaName(strDFFTextureName);
			if (pDFFTextureEntry != nullptr)
			{
				RWSection_Material *pMaterial = (RWSection_Material*)pDFFTextureEntry->getRWTextureSection()->getParentNode();
				pMaterial->removeSection();
				pDFFFile->removeTextureEntry(pDFFTextureEntry);
				bRemovedSection = true;
			}
		}

		IMGEntry *pIMGEntry = vecIMGEntries[i];
		pIMGEntry->setEntryData(pDFFFile->serialize());
		getIMGTab()->updateGridEntry(pIMGEntry);

		if (bRemovedSection)
		{
			uiDFFFileCountWithRemovedSections++;
		}

		increaseProgress();

		i++;
	}

	getIMGTab()->logf("Removed orphan txtures from %u DFF files.", uiDFFFileCountWithRemovedSections);

	// clean up
	for (DFFFormat *pDFFFile : vecDFFFormatsInput)
	{
		pDFFFile->unload();
		delete pDFFFile;
	}
	
	onCompleteTask();
}

void		Tasks::findOrphanIMGEntriesNotInIDE(void)
{
	onStartTask("findOrphanIMGEntriesNotInIDE");

	vector<string> vecIDEFilePaths = openFile("ide");
	if (vecIDEFilePaths.size() == 0)
	{
		return onAbortTask();
	}

	vector<string> vecIDEEntryNames = IDEManager::getIDEEntryNamesWithoutExtension(vecIDEFilePaths);
	
	vector<string> vecIMGEntryNames = getIMGTab()->getIMGFile()->getEntryNames(); // todo - getEntryNamesWithoutExtension
	for (string& strIMGEntryNames : vecIMGEntryNames)
	{
		strIMGEntryNames = Path::removeFileExtension(strIMGEntryNames);
	}

	vector<string> vecOrphanEntryNames = StdVector::getUniqueEntries(vecIMGEntryNames, vecIDEEntryNames);

	bool bRemoveEntriesFromIMG = m_pMainWindow->showGridWindow("Orphan IMG Entries not in IDE", String::toString(vecOrphanEntryNames.size()) + " Orphan IMG Entries not in IDE:", vector<string>({ "Orphan Entry Name" }), StdVector::swap2D(vector<vector<string>>({ vecOrphanEntryNames })), "Remove Entries from IMG");
	
	if(bRemoveEntriesFromIMG)
	{
		vector<IMGEntry*> vecOrphanEntries = getIMGTab()->getIMGFile()->getEntriesByNames(vecOrphanEntryNames);

		for (IMGEntry *pIMGEntry : vecOrphanEntries)
		{
			getIMGTab()->removeEntry(pIMGEntry);
		}

		if (vecOrphanEntries.size() > 0)
		{
			getIMGTab()->readdGridEntries();
			getIMGTab()->setIMGModifiedSinceRebuild(true);
		}

		getIMGTab()->logf("Removed %u orphan entries in IMG missing from IDE.", vecOrphanEntries.size());
	}
	
	onCompleteTask();
}

void		Tasks::findOrphanIDEEntriesNotInIMG(void)
{
	onStartTask("findOrphanIDEEntriesNotInIMG");

	vector<string> vecIDEFilePaths = openFile("ide");
	if (vecIDEFilePaths.size() == 0)
	{
		return onAbortTask();
	}

	vector<string> vecIDEEntryNames = IDEManager::getIDEEntryNamesWithoutExtension(vecIDEFilePaths);

	vector<string> vecIMGEntryNames = getIMGTab()->getIMGFile()->getEntryNames(); // todo - getEntryNamesWithoutExtension
	for (string& strIMGEntryNames : vecIMGEntryNames)
	{
		strIMGEntryNames = Path::removeFileExtension(strIMGEntryNames);
	}

	vector<string> vecOrphanEntryNames = StdVector::getUniqueEntries(vecIDEEntryNames, vecIMGEntryNames);

	bool bImportEntriesIntoIMG = m_pMainWindow->showGridWindow("Orphan IDE Entries not in IMG", String::toString(vecOrphanEntryNames.size()) + " Orphan IDE Entries not in IMG:", vector<string>({ "Orphan Entry Name" }), StdVector::swap2D(vector<vector<string>>({ vecOrphanEntryNames })), "Import Entries into IMG");

	if (bImportEntriesIntoIMG)
	{
		string strImportFolderPath = openFolder("Choose a folder to import orphan IDE entries from:");
		if (strImportFolderPath == "")
		{
			return onAbortTask();
		}

		uint32 uiImportCount = 0;
		for (string& strIDEEntryName : vecIDEEntryNames)
		{
			string strEntryFilePath = strImportFolderPath + strIDEEntryName;
			if (File::doesFileExist(strEntryFilePath))
			{
				uiImportCount++;
				getIMGTab()->addFile(strEntryFilePath);
			}

			increaseProgress();
		}

		if (uiImportCount > 0)
		{
			getIMGTab()->setIMGModifiedSinceRebuild(true);
		}

		getIMGTab()->logf("Imported %u orphan IDE entries into IMG.", uiImportCount);
	}

	onCompleteTask();
}

void		Tasks::findOrphanTXDTexturesForDFFsInIMGByIDE(void)
{
	onStartTask("findOrphanTXDTexturesForDFFsInIMGByIDE");

	// fetch IDE model and texture set names
	vector<string> vecIDEFilePaths = openFile("ide");
	if (vecIDEFilePaths.size() == 0)
	{
		return onAbortTask();
	}

	set<string> stModelNames, stTextureSetNames;
	IDEManager::getModelAndTextureSetNamesFromFiles(vecIDEFilePaths, stModelNames, stTextureSetNames, vector<EIDESection>(), vector<EIDESection>());

	// fetch texture names for DFF and TXD entries in the IMG that are found in the IDE
	vector<string> vecDFFTextureNames, vecTXDTextureNames;
	for (IMGEntry *pIMGEntry : getIMGTab()->getSelectedEntries())
	{
		if (pIMGEntry->isModelFile())
		{
			if (stModelNames.find(String::toUpperCase(Path::removeFileExtension(pIMGEntry->getEntryName()))) != stModelNames.end())
			{
				DFFFormat dffFile(pIMGEntry->getEntryData(), false);
				if (dffFile.unserialize())
				{
					StdVector::addToVector(vecDFFTextureNames, dffFile.getTextureNames());
				}
				dffFile.unload();
			}
		}

		if(pIMGEntry->isTextureFile())
		{
			if (stTextureSetNames.find(String::toUpperCase(Path::removeFileExtension(pIMGEntry->getEntryName()))) != stTextureSetNames.end())
			{
				TXDFormat txdFile(pIMGEntry->getEntryData(), false);
				if (txdFile.unserialize())
				{
					StdVector::addToVector(vecTXDTextureNames, txdFile.getTextureNames());
				}
				txdFile.unload();
			}
		}
	}

	vector<string> vecOrphanEntryNames = StdVector::getUniqueEntries(vecTXDTextureNames, vecDFFTextureNames);

	m_pMainWindow->showGridWindow("Orphan TXD Textures for DFFs in IMG by IDE", String::toString(vecOrphanEntryNames.size()) + " Orphan TXD textures for DFFs in IMG by IDE:", vector<string>({ "Orphan Entry Name" }), StdVector::swap2D(vector<vector<string>>({ vecOrphanEntryNames })), "");

	onCompleteTask();
}

// tools
void		Tasks::dump(void)
{
	onStartTask("dump");

	getIMGF()->getDumpManager()->process();

	onCompleteTask();
}

void		Tasks::sessionManager(void)
{
	onStartTask("sessionManager");

	getIMGF()->getWindowManager()->showSessionManagerWindow();

	onCompleteTask();
}

void		Tasks::renamer(void)
{
	onStartTask("renamer");

	getIMGF()->getWindowManager()->showRenamerWindow();

	onCompleteTask();
}

void		Tasks::txdBuilder(void)
{
	onStartTask("txdBuilder");

	getIMGF()->getWindowManager()->showTXDBuilderWindow();

	onCompleteTask();
}

void		Tasks::txdOrganizer(void)
{
	onStartTask("txdOrganizer");

	getIMGF()->getWindowManager()->showTXDOrganizerWindow();

	onCompleteTask();
}

void		Tasks::datPathsMover(void)
{
	onStartTask("datPathsMover");

	getIMGF()->getWindowManager()->showDATPathsMoverWindow();

	onCompleteTask();
}

void		Tasks::mapMoverAndIdShifter(void)
{
	onStartTask("mapMoverAndIdShifter");

	getIMGF()->getWindowManager()->showMapMoverAndIdShifterWindow();

	onCompleteTask();
}

// other
void		Tasks::textureList(void)
{
	onStartTask("textureList");

	vector<string> vecTextureNames;
	for (IMGEntry *pIMGEntry : getIMGTab()->getSelectedEntries())
	{
		if (pIMGEntry->isModelFile())
		{
			DFFFormat dffFile(pIMGEntry->getEntryData(), false);
			if (dffFile.unserialize())
			{
				StdVector::addToVector(vecTextureNames, dffFile.getTextureNames());
			}
			dffFile.unload();
		}
		else if (pIMGEntry->isTextureFile())
		{
			TXDFormat txdFile(pIMGEntry->getEntryData(), false);
			if (txdFile.unserialize())
			{
				StdVector::addToVector(vecTextureNames, txdFile.getTextureNames());
			}
			txdFile.unload();
		}
	}
	vecTextureNames = StdVector::removeDuplicates(vecTextureNames);

	m_pMainWindow->showGridWindow("Texture List for DFFs and TXDs", String::toString(vecTextureNames.size()) + " textures in selected DFF & TXD entries:", vector<string>({ "Texture Name" }), StdVector::swap2D(vector<vector<string>>({ vecTextureNames })), "");

	onCompleteTask();
}

void		Tasks::stats(void)
{
	onStartTask("stats");

	unordered_map<uint32, uint32> umapStatsRWVersions;
	unordered_map<string, uint32> umapStatsExtensions;

	for (IMGEntry *pIMGEntry : getIMGTab()->getIMGFile()->getEntries())
	{
		if (pIMGEntry->isRWFile())
		{
			if (umapStatsRWVersions.count(pIMGEntry->getRawVersion()) == 0)
			{
				umapStatsRWVersions[pIMGEntry->getRawVersion()] = 1;
			}
			else
			{
				umapStatsRWVersions[pIMGEntry->getRWVersion()]++;
			}
		}

		string strExtension = String::toUpperCase(Path::getFileExtension(pIMGEntry->getEntryName()));
		if (umapStatsExtensions.count(strExtension) == 0)
		{
			umapStatsExtensions[strExtension] = 1;
		}
		else
		{
			umapStatsExtensions[strExtension]++;
		}
	}

	vector<vector<string>> vecTextCells;
	for (auto it : umapStatsRWVersions)
	{
		vector<string> vecRowCells;
		vecRowCells.push_back(RWVersion::unpackVersionStampAsStringWithBuild(it.first) + " (" + String::toString(it.second) + ")");
		vecTextCells.push_back(vecRowCells);
	}
	uint32 i = 0;
	for (auto it : umapStatsExtensions)
	{
		string strValue = it.first + " (" + String::toString(it.second) + ")";
		if (i < vecTextCells.size())
		{
			vecTextCells[i].push_back(strValue);
		}
		else
		{
			vector<string> vecRowCells = {
				"",
				strValue
			};
			vecTextCells.push_back(vecRowCells);
		}
		i++;
	}

	m_pMainWindow->showGridWindow("IMG Stats", "IMG Stats:", vector<string>({ "RW Version Counts", "Extension Counts" }), vecTextCells, "");

	onCompleteTask();
}

void		Tasks::findDuplicateEntriesInSelection(void)
{
	onStartTask("findDuplicateEntriesInSelection");

	// max progress tick
	setMaxProgress(getIMGTab()->getSelectedEntryCount());

	// fetch selected entries
	vector<IMGEntry*> vecIMGEntries = getIMGTab()->getSelectedEntries();

	// store IMG entry names for checking
	unordered_map<string, vector<IMGEntry*>> umapIMGEntries;
	for (IMGEntry *pIMGEntry : vecIMGEntries)
	{
		umapIMGEntries[String::toUpperCase(pIMGEntry->getEntryName())].push_back(pIMGEntry);

		increaseProgress();
	}

	// find duplicate entries
	vector<vector<string>> vecDuplicateEntries;
	for (auto it : umapIMGEntries)
	{
		vector<IMGEntry*>& vecEntries = it.second;
		if (vecEntries.size() > 1)
		{
			vector<string> vecEntryIMGFileNames;
			for (IMGEntry *pIMGEntry : vecEntries)
			{
				vecEntryIMGFileNames.push_back(Path::getFileName(pIMGEntry->getIMGFile()->getIMGFilePath()));
			}
			vecDuplicateEntries.push_back({ vecEntries[0]->getEntryName(), String::join(vecEntryIMGFileNames, ", ") });
		}
	}
	umapIMGEntries.clear();

	// log
	getIMGTab()->logf("Found %u dupliate entries in selection.", vecDuplicateEntries.size());

	// results window
	vector<string> vecGridHeaders = { "Entry Name", "IMG File(s)" };
	m_pMainWindow->showGridWindow("Find Duplicate Entries in Selection", String::toString(vecDuplicateEntries.size()) + " duplicate entries found in selection:", vecGridHeaders, vecDuplicateEntries, "");

	onCompleteTask();
}

void		Tasks::findDuplicateEntriesInTab(void)
{
	onStartTask("findDuplicateEntriesInTab");

	// max progress tick
	setMaxProgress(getIMGTab()->getIMGFile()->getEntryCount());

	// fetch entries
	vector<IMGEntry*> vecIMGEntries = getIMGTab()->getIMGFile()->getEntries();

	// store IMG entry names for checking
	unordered_map<string, vector<IMGEntry*>> umapIMGEntries;
	for (IMGEntry *pIMGEntry : vecIMGEntries)
	{
		umapIMGEntries[String::toUpperCase(pIMGEntry->getEntryName())].push_back(pIMGEntry);

		increaseProgress();
	}

	// find duplicate entries
	vector<vector<string>> vecDuplicateEntries;
	for (auto it : umapIMGEntries)
	{
		vector<IMGEntry*>& vecEntries = it.second;
		if (vecEntries.size() > 1)
		{
			vector<string> vecEntryIMGFileNames;
			for (IMGEntry *pIMGEntry : vecEntries)
			{
				vecEntryIMGFileNames.push_back(Path::getFileName(pIMGEntry->getIMGFile()->getIMGFilePath()));
			}
			vecDuplicateEntries.push_back({ vecEntries[0]->getEntryName(), String::join(vecEntryIMGFileNames, ", ") });
		}
	}
	umapIMGEntries.clear();

	// log
	getIMGTab()->logf("Found %u dupliate entries in tab.", vecDuplicateEntries.size());

	// results window
	vector<string> vecGridHeaders = { "Entry Name", "IMG File(s)" };
	m_pMainWindow->showGridWindow("Find Duplicate Entries in Tab", String::toString(vecDuplicateEntries.size()) + " duplicate entries found in tab:", vecGridHeaders, vecDuplicateEntries, "");

	onCompleteTask();
}

void		Tasks::findDuplicateEntriesInAllTabs(void)
{
	onStartTask("findDuplicateEntriesInAllTabs");

	// max progress tick
	uint32 uiTickCount = 0;
	for (IMGEditorTab *pEditorTab : m_pMainWindow->getIMGEditor()->getIMGTabs().getEntries())
	{
		uiTickCount += pEditorTab->getIMGFile()->getEntryCount();
	}
	setMaxProgress(uiTickCount);

	// fetch entries
	vector<IMGEntry*> vecIMGEntries;
	for (IMGEditorTab *pEditorTab : m_pMainWindow->getIMGEditor()->getIMGTabs().getEntries())
	{
		StdVector::addToVector(vecIMGEntries, pEditorTab->getIMGFile()->getEntries());
	}

	// store IMG entry names for checking
	unordered_map<string, vector<IMGEntry*>> umapIMGEntries;
	for (IMGEntry *pIMGEntry : vecIMGEntries)
	{
		umapIMGEntries[String::toUpperCase(pIMGEntry->getEntryName())].push_back(pIMGEntry);

		increaseProgress();
	}

	// find duplicate entries
	vector<vector<string>> vecDuplicateEntries;
	for (auto it : umapIMGEntries)
	{
		vector<IMGEntry*>& vecEntries = it.second;
		if (vecEntries.size() > 1)
		{
			vector<string> vecEntryIMGFileNames;
			for (IMGEntry *pIMGEntry : vecEntries)
			{
				vecEntryIMGFileNames.push_back(Path::getFileName(pIMGEntry->getIMGFile()->getIMGFilePath()));
			}
			vecDuplicateEntries.push_back({ vecEntries[0]->getEntryName(), String::join(vecEntryIMGFileNames, ", ") });
		}
	}
	umapIMGEntries.clear();

	// log
	for (IMGEditorTab *pEditorTab : m_pMainWindow->getIMGEditor()->getIMGTabs().getEntries())
	{
		pEditorTab->logf("Found %u dupliate entries in all tabs.", vecDuplicateEntries.size());
	}

	// results window
	vector<string> vecGridHeaders = { "Entry Name", "IMG File(s)" };
	m_pMainWindow->showGridWindow("Find Duplicate Entries in All Tabs", String::toString(vecDuplicateEntries.size()) + " duplicate entries found in all tabs:", vecGridHeaders, vecDuplicateEntries, "");

	onCompleteTask();
}

void		Tasks::findDuplicateEntriesByDAT(void)
{
	onStartTask("findDuplicateEntriesByDAT");

	// choose DAT file
	vector<string> vecDATFilePaths = openFile("dat");
	if (vecDATFilePaths.size() == 0)
	{
		return onAbortTask();
	}

	// choose game folder
	string strGameFolderPath = openFolder("Choose a root game folder:");
	if (strGameFolderPath == "")
	{
		return onAbortTask();
	}

	// parse IMG files listed inside DAT files
	vector<IMGFormat*> vecIMGFiles;
	for (string& strDATFilePath : vecDATFilePaths)
	{
		DATLoaderFormat datFile(strDATFilePath);
		if (datFile.unserialize())
		{
			StdVector::addToVector(vecIMGFiles, datFile.parseIMGFiles(strGameFolderPath));
		}
		datFile.unload();
	}

	// fetch entries
	vector<IMGEntry*> vecIMGEntries;
	for (IMGFormat *pIMGFile : vecIMGFiles)
	{
		StdVector::addToVector(vecIMGEntries, pIMGFile->getEntries());
	}

	// store IMG entry names for checking
	unordered_map<string, vector<IMGEntry*>> umapIMGEntries;
	for (IMGEntry *pIMGEntry : vecIMGEntries)
	{
		umapIMGEntries[String::toUpperCase(pIMGEntry->getEntryName())].push_back(pIMGEntry);

		increaseProgress();
	}

	// find duplicate entries
	vector<vector<string>> vecDuplicateEntries;
	for (auto it : umapIMGEntries)
	{
		vector<IMGEntry*>& vecEntries = it.second;
		if (vecEntries.size() > 1)
		{
			vector<string> vecEntryIMGFileNames;
			for (IMGEntry *pIMGEntry : vecEntries)
			{
				vecEntryIMGFileNames.push_back(Path::getFileName(pIMGEntry->getIMGFile()->getIMGFilePath()));
			}
			vecDuplicateEntries.push_back({ vecEntries[0]->getEntryName(), String::join(vecEntryIMGFileNames, ", ") });
		}
	}
	umapIMGEntries.clear();

	// results window
	vector<string> vecGridHeaders = { "Entry Name", "IMG File(s)" };
	m_pMainWindow->showGridWindow("Find Duplicate Entries by DAT", String::toString(vecDuplicateEntries.size()) + " duplicate entries found by DAT:", vecGridHeaders, vecDuplicateEntries, "");

	// clean up
	for (IMGFormat *pIMGFile : vecIMGFiles)
	{
		pIMGFile->unload();
		delete pIMGFile;
	}

	onCompleteTask();
}

void		Tasks::compareIMGs(void)
{
	onStartTask("compareIMGs");

	// choose IMG files
	vector<string> vecIMGFilePaths = openFile("img");
	if (vecIMGFilePaths.size() == 0)
	{
		return onAbortTask();
	}

	// store IMG objects
	vector<IMGFormat*> vecIMGFiles = { getIMGTab()->getIMGFile() };
	for (string& strIMGFilePath : vecIMGFilePaths)
	{
		IMGFormat *pIMGFile = new IMGFormat(strIMGFilePath);
		if (pIMGFile->unserialize())
		{
			vecIMGFiles.push_back(pIMGFile);
		}
		else
		{
			pIMGFile->unload();
			delete pIMGFile;
		}
	}

	// verify there are at least 2 IMG files to compare
	if (vecIMGFiles.size() < 2)
	{
		Input::showMessage("There needs to be at least 2 valid IMG files to compare.", "Not Enough Valid IMG Files", MB_OK);
		return onAbortTask();
	}

	// stroe IMG entry names
	unordered_map<IMGFormat*, set<string>> umapIMGFormatEntryNames;
	for (IMGFormat *pIMGFormat : vecIMGFiles)
	{
		for (IMGEntry *pIMGEntry : pIMGFormat->getEntries())
		{
			umapIMGFormatEntryNames[pIMGFormat].insert(String::toUpperCase(pIMGEntry->getEntryName()));
		}
	}

	// compare all IMG files
	vector<vector<string>> vecGridCellsText, vecGridCellsText2;
	vecGridCellsText.push_back({ "Entries missing from other IMGs:", "" });
	vecGridCellsText2.push_back({ "Entries in all IMGs:", "" });

	for (IMGFormat *pIMGFormat1 : vecIMGFiles)
	{
		for (IMGEntry *pIMGEntry1 : pIMGFormat1->getEntries())
		{
			bool bEntry1IsInAllIMGs = true;
			string strEntryName1 = pIMGEntry1->getEntryName();

			for (IMGFormat *pIMGFormat2 : vecIMGFiles)
			{
				if (pIMGFormat1 != pIMGFormat2)
				{
					string strIMGFileName2 = Path::getFileName(pIMGFormat2->getIMGFilePath());

					if (umapIMGFormatEntryNames[pIMGFormat2].find(String::toUpperCase(strEntryName1)) == umapIMGFormatEntryNames[pIMGFormat2].end())
					{
						bEntry1IsInAllIMGs = false;
						vecGridCellsText.push_back({ strEntryName1, strIMGFileName2 });
					}
				}
			}
			if (bEntry1IsInAllIMGs)
			{
				vecGridCellsText2.push_back({ strEntryName1, "" });
			}
		}
	}
	if (vecGridCellsText.size() == 1)
	{
		vecGridCellsText.push_back({ "(None)", "" });
	}
	if (vecGridCellsText2.size() == 1)
	{
		vecGridCellsText2.push_back({ "(None)", "" });
	}
	StdVector::addToVector(vecGridCellsText, vecGridCellsText2);

	// show results window
	vector<string> vecGridHeaders = { "Entry Name", "Missing from IMG" };
	m_pMainWindow->showGridWindow("Compare IMGs", "IMG comparison results:", vecGridHeaders, vecGridCellsText, "");

	// clean up
	for (IMGFormat *pIMGFile : vecIMGFiles)
	{
		pIMGFile->unload();
		delete pIMGFile;
	}

	onCompleteTask();
}

void						Tasks::modelListForIDEAndIPLByDAT(void)
{
	onStartTask("modelListForIDEAndIPLByDAT");

	// choose DAT file paths
	vector<string> vecDATFilePaths = openFile("dat");
	if (vecDATFilePaths.size() == 0)
	{
		return onAbortTask();
	}

	// choose game folder
	string strGameFolderPath = openFolder("Choose a root game folder:");
	if (strGameFolderPath == "")
	{
		return onAbortTask();
	}

	// parse DAT files
	vector<DATLoaderFormat*> vecDATFiles;
	for (string& strDATFilePath : vecDATFilePaths)
	{
		DATLoaderFormat *pDATFile = new DATLoaderFormat(strDATFilePath);
		if (pDATFile->unserialize())
		{
			vecDATFiles.push_back(pDATFile);
		}
		else
		{
			pDATFile->unload();
			delete pDATFile;
		}
	}

	// fetch model names in DAT files
	vector<string> vecModelNames;
	for (DATLoaderFormat *pDATFile : vecDATFiles)
	{
		vector<string>
			vecRelativeIDEPaths = pDATFile->getRelativeIDEPaths(),
			vecRelativeIPLPaths = pDATFile->getRelativeIPLPaths();

		for (string& strRelativeIDEPath : vecRelativeIDEPaths)
		{
			IDEFormat ideFile(strGameFolderPath + strRelativeIDEPath);
			if (ideFile.unserialize())
			{
				StdVector::addToVector(vecModelNames, ideFile.getModelNames());
			}
			ideFile.unload();
		}
		for (string& strRelativeIPLPath : vecRelativeIPLPaths)
		{
			IPLFormat iplFile(strGameFolderPath + strRelativeIPLPath);
			if (iplFile.unserialize())
			{
				StdVector::addToVector(vecModelNames, iplFile.getModelNames());
			}
			iplFile.unload();
		}
	}
	vecModelNames = StdVector::removeDuplicates(vecModelNames);

	// show results window
	vector<string> vecGridHeaders = { "Model Name" };
	vector<vector<string>> vecGridCellsText = { vecModelNames };
	vecGridCellsText = StdVector::swap2D(vecGridCellsText);
	m_pMainWindow->showGridWindow("Model List for IDE/IPL by DAT", String::toString(vecModelNames.size()) + " models in IDE/IPL files in DAT files:", vecGridHeaders, vecGridCellsText, "");

	// clean up
	for (DATLoaderFormat *pDATFile : vecDATFiles)
	{
		pDATFile->unload();
		delete pDATFile;
	}

	onCompleteTask();
}

void		Tasks::saveIMGSignature(void)
{
	onStartTask("saveIMGSignature");

	IMGFormat *pIMGFile = getIMGTab()->getIMGFile();
	DBFormat *pDBFile = DBManager::get()->createDBFileFromIMGFile(pIMGFile);
	string strDBPath = Path::replaceFileExtension(pIMGFile->getFilePath(), "db");
	pDBFile->serialize(strDBPath);

	if (getIMGTab()->m_pDBFile != nullptr)
	{
		delete getIMGTab()->m_pDBFile;
	}
	getIMGTab()->m_pDBFile = pDBFile;

	getIMGTab()->loadProtectedEntryStates();
	getIMGTab()->readdGridEntries();

	getIMGTab()->logf("Saved DB file for %s.", Path::getFileName(pIMGFile->getIMGFilePath()).c_str());

	onCompleteTask();
}

void		Tasks::verifyIMGSignature(void)
{
	onStartTask("verifyIMGSignature");

	IMGFormat *pIMGFile = getIMGTab()->getIMGFile();
	string strDBFilePath = Path::replaceFileExtension(pIMGFile->getFilePath(), "db");

	if (!File::doesFileExist(strDBFilePath))
	{
		Input::showMessage("DB file does not exist for " + Path::getFileName(pIMGFile->getIMGFilePath()), "DB File Doesn't Exist", MB_OK);
		return onAbortTask();
	}

	DBFormat *pDBFileForIMGTab = DBManager::get()->createDBFileFromIMGFile(pIMGFile);
	DBFormat *pDBFileForIMGFile = DBManager::get()->unserializeFile(strDBFilePath);
	
	if(!pDBFileForIMGFile)
	{
		delete pDBFileForIMGTab;
		delete pDBFileForIMGFile;
		Input::showMessage("Failed to open DB file for " + Path::getFileName(pIMGFile->getIMGFilePath()), "Failed to Open DB File", MB_OK);
		return onAbortTask();
	}
	
	bool bComparedEqual = DBManager::get()->compareDBFiles(pDBFileForIMGTab, pDBFileForIMGFile);
	if(bComparedEqual)
	{
		Input::showMessage("The IMG matches the DB file.", "IMG Matches DB", MB_OK);
	}
	else
	{
		Input::showMessage("The IMG does not match the DB file.", "IMG Doesn't Match DB", MB_OK);
	}

	delete pDBFileForIMGTab;
	delete pDBFileForIMGFile;
	
	onCompleteTask();
}

void			Tasks::validateDFFInTab(void)
{
	onStartTask("validateDFFInTab");

	vector<vector<string>> vecGridCellsText;
	for (IMGEntry *pIMGEntry : getIMGTab()->getIMGFile()->getEntries())
	{
		if (pIMGEntry->isModelFile())
		{
			DFFFormat dffFile(pIMGEntry->getEntryData(), false);
			if (!dffFile.unserialize())
			{
				vecGridCellsText.push_back({ pIMGEntry->getEntryName(), dffFile.getErrorReason() });
			}
			dffFile.unload();
		}
	}

	if (vecGridCellsText.size() == 0)
	{
		Input::showMessage("All DFF entries in this tab are valid.", "All DFF Valid", MB_OK);
	}
	else
	{
		vector<string> vecGridHeadersText = { "Entry Name", "Error Reason" };
		m_pMainWindow->showGridWindow("Invalid DFF Entries", String::toString(vecGridCellsText.size()) + " invalid DFF entries:", vecGridHeadersText, vecGridCellsText, "");
	}
	
	onCompleteTask();
}

void			Tasks::validateTXDInTab(void)
{
	onStartTask("validateTXDInTab");

	vector<vector<string>> vecGridCellsText;
	for (IMGEntry *pIMGEntry : getIMGTab()->getIMGFile()->getEntries())
	{
		if (pIMGEntry->isTextureFile())
		{
			string strEntryData = pIMGEntry->getEntryData();
			TXDFormat txdFile(strEntryData, false);
			if (!txdFile.unserialize())
			{
				vecGridCellsText.push_back({ pIMGEntry->getEntryName(), txdFile.getErrorReason() });
				continue;
			}

			if (!TXDFormat::isTXDSizeValid(strEntryData.size()))
			{
				vecGridCellsText.push_back({ pIMGEntry->getEntryName(), "TXD size" });
			}
			else
			{
				if (!TXDFormat::isTextureCountValid(txdFile.getTextures().size(), txdFile.getPlatformedGames()))
				{
					vecGridCellsText.push_back({ pIMGEntry->getEntryName(), "Texture count for game" });
				}
				else
				{
					uint32 uiTextureIndex = 0;
					for (RWSection_TextureNative *pTexture : txdFile.getTextures())
					{
						if (!TXDFormat::isTextureResolutionValid((uint16)pTexture->getImageSize().x, (uint16)pTexture->getImageSize().y, txdFile.getPlatformedGames()))
						{
							vecGridCellsText.push_back({ pIMGEntry->getEntryName(), "Texture resolution: " + pTexture->getDiffuseName() + " (" + String::toString(pTexture->getImageSize().x) + " x " + String::toString(pTexture->getImageSize().y) + ")" });
							break;
						}

						if (!TXDFormat::isTextureNameValid(pTexture->getDiffuseName()) || !TXDFormat::isTextureNameValid(pTexture->getAlphaName(), true))
						{
							vecGridCellsText.push_back({ pIMGEntry->getEntryName(), "Texture name for texture at index: " + String::toString(uiTextureIndex + 1) });
							break;
						}

						uiTextureIndex++;
					}
				}
			}

			txdFile.unload();
		}
	}

	if (vecGridCellsText.size() == 0)
	{
		Input::showMessage("All TXD entries in this tab are valid.", "All TXD Valid", MB_OK);
	}
	else
	{
		vector<string> vecGridHeadersText = { "Entry Name", "Error Reason" };
		m_pMainWindow->showGridWindow("Invalid TXD Entries", String::toString(vecGridCellsText.size()) + " invalid DFF entries:", vecGridHeadersText, vecGridCellsText, "");
	}

	onCompleteTask();
}

void			Tasks::centerCOLMeshesInSelection(void)
{
	onStartTask("centerCOLMeshesInSelection");

	vector<IMGEntry*> vecIMGEntries = getIMGTab()->getSelectedEntries();
	setMaxProgress(vecIMGEntries.size());

	uint32 uiEntryCount = 0;
	for(IMGEntry *pIMGEntry : vecIMGEntries)
	{
		if (!pIMGEntry->isCollisionFile())
		{
			continue;
		}

		COLFormat colFile(pIMGEntry->getEntryData(), false);
		if (!colFile.unserialize())
		{
			colFile.unload();
			continue;
		}

		for (COLEntry *pCOLEntry : colFile.getEntries())
		{
			if (pCOLEntry->getCollisionMeshVertexCount() > 1)
			{
				vector<Vec3f>& vecVertices = (vector<Vec3f>&) pCOLEntry->getCollisionMeshVertices(); // Vec3f is the same size and data types as TVertex so the cast should work.
				Vec3f vecCollisionMeshCenter = Math::getPolygonCenter(vecVertices);
				if (vecCollisionMeshCenter != 0.0f)
				{
					pCOLEntry->applyCollisionMeshVerticesOffset(-vecCollisionMeshCenter);
				}
			}
		}

		string strNewEntryData = colFile.serialize();
		pIMGEntry->setEntryData(strNewEntryData);
		
		getIMGTab()->updateGridEntry(pIMGEntry);

		colFile.unload();
		increaseProgress();
		uiEntryCount++;
	}

	getIMGTab()->logf("Centered meshes for %u COL files.", uiEntryCount);

	getIMGTab()->setIMGModifiedSinceRebuild(true);

	onCompleteTask();
}

void			Tasks::alignCOLMeshesToDFFMeshes(void)
{
	onStartTask("alignCOLMeshesToDFFMeshes");

	// choose COL files folder
	string strCOLFolderPath = openFolder("Choose a folder containing COL files.");
	if (strCOLFolderPath == "")
	{
		return onAbortTask();
	}

	// choose DFF files folder
	string strDFFFolderPath = openFolder("Choose a folder containing DFF files.");
	if (strDFFFolderPath == "")
	{
		return onAbortTask();
	}

	// initialize
	unordered_map<string, Vec3f>
		umapGeometryPolygonCenters;
	vector<string>
		vecFilePaths_DFF = File::getFileNamesByExtension(strDFFFolderPath, "dff"),
		vecFilePaths_BSP = File::getFileNamesByExtension(strDFFFolderPath, "bsp"),
		vecFilePaths_COL = File::getFileNamesByExtension(strCOLFolderPath, "col");

	vecFilePaths_DFF = StdVector::combineVectors(vecFilePaths_DFF, vecFilePaths_BSP);

	setMaxProgress(vecFilePaths_DFF.size() + vecFilePaths_COL.size());
	
	// fetch DFF texture names and mesh centers
	for (string& strDFFFilePath : vecFilePaths_DFF)
	{
		DFFFormat dffFile(strDFFFolderPath + strDFFFilePath);
		if(!dffFile.unserialize())
		{
			dffFile.unload();
			increaseProgress();
			continue;
		}
		
		vector<RWSection*> vecDFFGeometrySections = dffFile.getSectionsByType(RW_SECTION_GEOMETRY);
		for (RWSection *pRWSection : vecDFFGeometrySections)
		{
			RWSection_Geometry *pGeometry = (RWSection_Geometry*) pRWSection;

			string strTextureDiffuseName = pGeometry->getTextureDiffuseName();
			vector<Vec3f> vecVertices = pGeometry->getVertexPositions();
			Vec3f vecPolygonCenter = Math::getPolygonCenter(vecVertices);
			umapGeometryPolygonCenters[String::toUpperCase(strTextureDiffuseName)] = vecPolygonCenter;
		}

		dffFile.unload();
		increaseProgress();
	}

	// check if COL mesh centers are the same as DFF mesh centers, if not then align the COLs to match DFFs
	uint32 uiAlignedEntryCount = 0;
	for (string& strCOLFilePath : vecFilePaths_COL)
	{
		COLFormat colFile(strCOLFolderPath + strCOLFilePath);
		if(!colFile.unserialize())
		{
			colFile.unload();
			increaseProgress();
			continue;
		}
		colFile.setFilePath(strCOLFilePath);

		for (COLEntry *pCOLEntry : colFile.getEntries())
		{
			if (umapGeometryPolygonCenters.find(String::toUpperCase(pCOLEntry->getModelName())) == umapGeometryPolygonCenters.end())
			{
				continue;
			}
			Vec3f vecDFFPolygonCenter = umapGeometryPolygonCenters[String::toUpperCase(pCOLEntry->getModelName())];

			if (pCOLEntry->getCollisionMeshVertexCount() > 1)
			{
				vector<Vec3f>& vecVertices = (vector<Vec3f>&) pCOLEntry->getCollisionMeshVertices(); // Vec3f is the same size and data types as TVertex so the cast should work.
				Vec3f vecCollisionMeshCenter = Math::getPolygonCenter(vecVertices);
				if (vecCollisionMeshCenter != vecDFFPolygonCenter)
				{
					pCOLEntry->applyCollisionMeshVerticesOffset(-(vecCollisionMeshCenter - vecDFFPolygonCenter));
				}
			}
		}

		colFile.serialize();

		colFile.unload();
		increaseProgress();
	}
	
	Input::showMessage("Aligned " + String::toString(uiAlignedEntryCount) + " COL meshes to DFF meshes.", "Aligned COL to DFF", MB_OK);

	onCompleteTask();
}

void				Tasks::extractDVCAndNVCIntoDFFs(void)
{
	onStartTask("extractDVCAndNVCIntoDFFs");

	// choose DVC, NVC, or both
	uint32 uiUpdateType = m_pMainWindow->show3ButtonWindow("DVC/NVC Extraction Type", "Extract DVC, NVC, or both?", "DVC", "NVC", "Both");
	if (m_pMainWindow->m_bWindow2Cancelled)
	{
		return onAbortTask();
	}

	// choose DFF input folder for colours
	string strDFFColoursFolderPath = openFolder("Choose a folder containing DFF files, to extract the colours from.");
	if (strDFFColoursFolderPath == "")
	{
		return onAbortTask();
	}

	// choose DFF input folder for models
	string strDFFModelDataFolderPath = openFolder("Choose a folder containing DFF files, to extract the model data from.");
	if (strDFFModelDataFolderPath == "")
	{
		return onAbortTask();
	}

	// choose output folder
	string strOutputFolderPath = openFolder("Choose a folder to put the output DFF files.");
	if (strOutputFolderPath == "")
	{
		return onAbortTask();
	}

	// fetch DFF file paths
	vector<string> vecDFFInputFilenamesForColours = File::getFileNamesByExtension(strDFFColoursFolderPath, "DFF");
	vector<string> vecDFFInputFilenamesForModels = File::getFileNamesByExtension(strDFFModelDataFolderPath, "DFF");

	unordered_map<string, bool> umapDFFInputFilenamesUpperForModels = StdVector::convertVectorToUnorderedMap(StdVector::toUpperCase(vecDFFInputFilenamesForModels));

	setMaxProgress(vecDFFInputFilenamesForColours.size());

	// iterate around input DFFs
	uint32 uiDFFUpdatedFileCount = 0;
	for (string& strDFFFilename_Colours : vecDFFInputFilenamesForColours)
	{
		if (umapDFFInputFilenamesUpperForModels.count(String::toUpperCase(strDFFFilename_Colours)) == 0)
		{
			increaseProgress();
			continue;
		}
		string& strDFFFilename_Model = strDFFFilename_Colours;

		DFFFormat *pDFFFile_Colours = DFFManager::get()->unserializeFile(strDFFColoursFolderPath + strDFFFilename_Colours);
		if (pDFFFile_Colours->doesHaveError())
		{
			pDFFFile_Colours->unload();
			delete pDFFFile_Colours;
			increaseProgress();
			continue;
		}

		vector<Vec4u8> vecDFFColours_DVC;
		vector<Vec4u8> vecDFFColours_NVC;
		if (uiUpdateType == 1 || uiUpdateType == 3) // DVC or both
		{
			vecDFFColours_DVC = pDFFFile_Colours->getDVColours();
		}
		if (uiUpdateType == 2 || uiUpdateType == 3) // NVC or both
		{
			vecDFFColours_NVC = pDFFFile_Colours->getNVColours();
			if (vecDFFColours_NVC.size() == 0)
			{
				vecDFFColours_NVC = vecDFFColours_DVC;
			}
		}

		pDFFFile_Colours->unload();
		delete pDFFFile_Colours;

		//DFFFormat *pDFFFile_Model = DFFManager::get()->unserializeFile(strDFFInputFolderForModels + strDFFFilename_Model);
		DFFFormat *pDFFFile_Model = DFFManager::get()->unserializeMemory(File::getFileContent(strDFFModelDataFolderPath + strDFFFilename_Model, true));
		if (pDFFFile_Model->doesHaveError())
		{
			pDFFFile_Model->unload();
			delete pDFFFile_Model;
			increaseProgress();
			continue;
		}

		if (uiUpdateType == 1 || uiUpdateType == 3) // DVC or both
		{
			if (vecDFFColours_DVC.size() > 0)
			{
				pDFFFile_Model->setDVColours(vecDFFColours_DVC);
			}
		}
		if (uiUpdateType == 2 || uiUpdateType == 3) // NVC or both
		{
			if (vecDFFColours_NVC.size() > 0)
			{
				pDFFFile_Model->setNVColours(vecDFFColours_NVC);
			}
		}

		pDFFFile_Model->serialize(strOutputFolderPath + strDFFFilename_Colours);

		pDFFFile_Model->unload();
		delete pDFFFile_Model;
		increaseProgress();
		uiDFFUpdatedFileCount++;
	}

	// log
	string strLogPart1 = uiUpdateType == 1 ? "DVC" : (uiUpdateType == 2 ? "NVC" : "DVC and NVC");
	getIMGTab()->logf("Extracted " + strLogPart1 + " into %u DFF files.", uiDFFUpdatedFileCount);

	// end
	onCompleteTask();
}

void				Tasks::extract2DFXIntoDFFs(void)
{
	onStartTask("extract2DFXIntoDFFs");

	// choose DFF input folder for colours
	string strDFFInputFolderFor2DFX = openFolder("Choose a folder containing DFF files, to extract the colours from.");
	if (strDFFInputFolderFor2DFX == "")
	{
		return onAbortTask();
	}

	// choose DFF input folder for models
	string strDFFInputFolderForModels = openFolder("Choose a folder containing DFF files, to extract the model data from.");
	if (strDFFInputFolderForModels == "")
	{
		return onAbortTask();
	}

	// choose output folder
	string strOutputFolderPath = openFolder("Choose a folder to put the output DFF files.");
	if (strOutputFolderPath == "")
	{
		return onAbortTask();
	}

	// fetch DFF file paths
	vector<string> vecDFFInputFilenamesFor2DFX = File::getFileNamesByExtension(strDFFInputFolderFor2DFX, "DFF");
	vector<string> vecDFFInputFilenamesForModels = File::getFileNamesByExtension(strDFFInputFolderForModels, "DFF");

	unordered_map<string, bool> umapDFFInputFilenamesUpperForModels = StdVector::convertVectorToUnorderedMap(StdVector::toUpperCase(vecDFFInputFilenamesForModels));

	setMaxProgress(vecDFFInputFilenamesFor2DFX.size());

	// iterate around input DFFs
	uint32 uiDFFUpdatedFileCount = 0;
	for (string& strDFFFilename_2DFX : vecDFFInputFilenamesFor2DFX)
	{
		if (umapDFFInputFilenamesUpperForModels.count(String::toUpperCase(strDFFFilename_2DFX)) == 0)
		{
			increaseProgress();
			continue;
		}
		string& strDFFFilename_Model = strDFFFilename_2DFX;

		DFFFormat *pDFFFile_2DFX = DFFManager::get()->unserializeFile(strDFFInputFolderFor2DFX + strDFFFilename_2DFX);
		if (pDFFFile_2DFX->doesHaveError())
		{
			pDFFFile_2DFX->unload();
			delete pDFFFile_2DFX;
			increaseProgress();
			continue;
		}

		vector<vector<_2dEffect*>> vec2dEffects = pDFFFile_2DFX->get2dEffects();

		DFFFormat *pDFFFile_Model = DFFManager::get()->unserializeFile(strDFFInputFolderForModels + strDFFFilename_Model);
		if (pDFFFile_Model->doesHaveError())
		{
			pDFFFile_2DFX->unload();
			delete pDFFFile_2DFX;
			pDFFFile_Model->unload();
			delete pDFFFile_Model;
			increaseProgress();
			continue;
		}

		pDFFFile_Model->set2dEffects(vec2dEffects);

		pDFFFile_Model->serialize(strOutputFolderPath + strDFFFilename_2DFX);

		pDFFFile_2DFX->unload();
		delete pDFFFile_2DFX;
		pDFFFile_Model->unload();
		delete pDFFFile_Model;
		increaseProgress();
		uiDFFUpdatedFileCount++;
	}

	// log
	getIMGTab()->logf("Extracted 2DFX into %u DFF files.", uiDFFUpdatedFileCount);

	onCompleteTask();
}

void		Tasks::imgCompression(void)
{
	onStartTask("imgCompression");

	// ensure IMG version has settings
	if (getIMGTab()->getIMGFile()->getVersion() != IMG_FASTMAN92)
	{
		Input::showMessage("IMG version must be Fastman92's IMG version for compression or encryption.", "Invalid IMG Version for Compression/Encryption", MB_OK);
		return onAbortTask();
	}

	// choose compression status
	uint32 uiButtonIndex = m_pMainWindow->show3ButtonWindow("Compress IMG", "Should IMG be compressed?", "Yes", "No", "");
	if (uiButtonIndex == -1)
	{
		return onAbortTask();
	}

	ECompressionAlgorithm uiCompressionAlgorithm;
	uint32 uiCompressionLevel;
	if (uiButtonIndex == 0) // Button: Yes
	{
		vector<string> vecOptions = { "ZLib", "LZ4" };
		uint32 uiOptionIndex = m_pMainWindow->showDropDownWindow("IMG Compression Algorithm", "IMG compression algorithm:", vecOptions);
		if (uiOptionIndex == -1)
		{
			return onAbortTask();
		}
		if (uiOptionIndex == 0)
		{
			uiCompressionAlgorithm = COMPRESSION_ZLIB;
		}
		else if (uiOptionIndex == 1)
		{
			uiCompressionAlgorithm = COMPRESSION_LZ4;
		}

		vecOptions.clear();
		for (uint32 i = 0; i < 10; i++)
		{
			vecOptions.push_back("Level " + String::toString(i + 1));
		}
		uiOptionIndex = m_pMainWindow->showDropDownWindow("Compression Level", "Compression level:", vecOptions);
		if (uiOptionIndex == -1)
		{
			return onAbortTask();
		}
		uiCompressionLevel = uiOptionIndex + 1;
	}
	else if (uiButtonIndex == 1) // Button: No
	{
		uiCompressionAlgorithm = COMPRESSION_NONE;
	}

	// fetch selected entries
	vector<IMGEntry*> vecIMGEntries = getIMGTab()->getSelectedEntries();
	
	// apply new compression type to IMG entries
	setMaxProgress(vecIMGEntries.size());
	for (IMGEntry *pIMGEntry : vecIMGEntries)
	{
		pIMGEntry->applyCompression(uiCompressionAlgorithm, uiCompressionLevel);
		getIMGTab()->updateGridEntry(pIMGEntry);

		increaseProgress();
	}

	// update IMG version text in main window
	getIMGTab()->updateIMGText();

	// log
	getIMGTab()->logf("Updated IMG compression for %u entries.", vecIMGEntries.size());

	// mark as modified since rebuild
	getIMGTab()->setIMGModifiedSinceRebuild(true);

	onCompleteTask();
}

void		Tasks::associateIMGExtension(void)
{
	// todo
	Registry::assoicateFileExtension("img", Process::getEXEFilePath());
}




























bool		Tasks::saveAllOpenFiles(bool bCloseAll)
{
	getIMGF()->getLastUsedValueManager()->setLastUsedValue_Close2_CloseAll(bCloseAll);
	getIMGF()->getTaskManager()->onStartTask("saveAllOpenFiles");
	string strText = "";
	if (bCloseAll)
	{
		uint32 uiModifiedSinceRebuildCount = 0;
		for (auto pEditorTab : getIMGF()->getIMGEditor()->getTabs().getEntries())
		{
			if (((IMGEditorTab*)pEditorTab)->getIMGModifiedSinceRebuild())
			{
				uiModifiedSinceRebuildCount++;
			}
		}
		if (uiModifiedSinceRebuildCount > 0)
		{
			strText = LocalizationManager::get()->getTranslatedFormattedText("Window_Confirm_3_Message", uiModifiedSinceRebuildCount);
		}
	}
	else
	{
		if (getIMGF()->getEntryListTab()->getIMGModifiedSinceRebuild())
		{
			strText = LocalizationManager::get()->getTranslatedFormattedText("Window_Confirm_4_Message", Path::getFileName(getIMGF()->getEntryListTab()->getIMGFile()->getFilePath()).c_str());
		}
	}

	if (strText == "")
	{
		getIMGF()->getTaskManager()->onTaskEnd("onRequestClose2", true);
		return false;
	}

	bool bDidCancel = false;
	getIMGF()->getTaskManager()->onPauseTask();
	bool bResult = false; // todo false; // todo - getIMGF()->getPopupGUIManager()->showConfirmDialog(strText, LocalizationManager::get()->getTranslatedText("Window_Confirm_3_Title"), bDidCancel);
	getIMGF()->getTaskManager()->onResumeTask();
	if (bDidCancel)
	{
		getIMGF()->getTaskManager()->onTaskEnd("onRequestClose2", true);
		return true;
	}
	if (!bResult)
	{
		getIMGF()->getTaskManager()->onTaskEnd("onRequestClose2", true);
		return false;
	}

	if (bCloseAll)
	{
		for (auto pEditorTab : getIMGF()->getIMGEditor()->getTabs().getEntries())
		{
			if (((IMGEditorTab*)pEditorTab)->getIMGModifiedSinceRebuild())
			{
				((IMGEditorTab*)pEditorTab)->rebuild();
			}
		}
	}
	else
	{
		getIMGF()->getEntryListTab()->rebuild();
	}
	getIMGF()->getTaskManager()->onTaskEnd("onRequestClose2");
	return true;
}

void		Tasks::onRequestSessionManager(void)
{
	/*
	getIMGF()->getTaskManager()->onStartTask("onRequestSessionManager");
	SessionManagerDialogData *pSessionManagerDialogData = nullptr;
	bool bReopenWindow;
	do
	{
		vector<string> vecSessionsData;
		uint32 uiSessionCount = String::toUint32(INIManager::getItem(AppDataPath::getSessionsPath(), "Sessions", "Count"));
		for (int32 i = uiSessionCount; i >= 1; i--)
		{
			string strIMGPaths = INIManager::getItem(AppDataPath::getSessionsPath(), "Sessions", String::toString(i));
			vecSessionsData.push_back(strIMGPaths);
		}

		getIMGF()->getTaskManager()->onPauseTask();
		pSessionManagerDialogData = getIMGF()->getPopupGUIManager()->showSessionManagerDialog(vecSessionsData);
		getIMGF()->getTaskManager()->onResumeTask();
		bReopenWindow = pSessionManagerDialogData->m_vecSessionsToRemove.size() > 0 || pSessionManagerDialogData->m_vecSessionsToAdd.size() > 0 || pSessionManagerDialogData->m_strSessionNameToUpdate != "";

		for (auto strSessionName : pSessionManagerDialogData->m_vecSessionsToRemove)
		{
			getIMGF()->getSessionManager()->removeSession(getIMGF()->getSessionManager()->getSessionByName(strSessionName));
		}
		for (auto strSessionData : pSessionManagerDialogData->m_vecSessionsToAdd)
		{
			deque<string> deqIMGPaths = StdVector::convertVectorToDeque(String::split(strSessionData, "; "));
			string strSessionName = deqIMGPaths[0];
			deqIMGPaths.pop_front();

			vector<string> vecIMGPaths;
			for (auto strIMGPath : deqIMGPaths)
			{
				vecIMGPaths.push_back(strIMGPath);
			}

			getIMGF()->getSessionManager()->addSession(strSessionName, vecIMGPaths);
		}
		if (pSessionManagerDialogData->m_strSessionNameToUpdate != "")
		{
			//pSessionManagerDialogData->m_strSessionDataToUpdate
			deque<string> deqIMGPaths = StdVector::convertVectorToDeque(String::split(pSessionManagerDialogData->m_strSessionDataToUpdate, "; "));
			string strNewSessionName = deqIMGPaths[0];
			deqIMGPaths.pop_front();

			vector<string> vecIMGPaths;
			for (auto strIMGPath : deqIMGPaths)
			{
				vecIMGPaths.push_back(strIMGPath);
			}

			getIMGF()->getSessionManager()->getSessionByName(pSessionManagerDialogData->m_strSessionNameToUpdate)->setName(strNewSessionName);
			getIMGF()->getSessionManager()->getSessionByName(pSessionManagerDialogData->m_strSessionNameToUpdate)->setPaths(vecIMGPaths);
		}

		delete pSessionManagerDialogData;
		getIMGF()->getSessionManager()->loadSessions();
	} while (bReopenWindow);
	getIMGF()->getTaskManager()->onTaskEnd("onRequestSessionManager");
	*/
}

void		Tasks::onRequestUpdate(void)
{
	getIMGF()->getTaskManager()->onStartTask("onRequestUpdate");

	//vector<UpdateConnection*> vecUpdateConnections;
	if (getIMGF()->getBuildMeta().isAlphaBuild())
	{
		// alpha version
		string strFileContent;
		UpdateConnection *pActiveUpdateConnection = nullptr;
		for (auto pUpdateConnection : getIMGF()->getUpdateManager()->getUpdateConnectionManager()->getEntries())
		{
			if (!pUpdateConnection->isAlpha())
			{
				continue;
			}

			pActiveUpdateConnection = pUpdateConnection;
			strFileContent = HTTP::get()->getFileContent(pUpdateConnection->getLatestVersionURL());
			if (strFileContent == "")
			{
				continue;
			}

			break;
		}
		if (strFileContent == "")
		{
			getIMGF()->getTaskManager()->onPauseTask();
			uint32 uiMirrorCount = getIMGF()->getUpdateManager()->getUpdateConnectionManager()->getEntryCount();
			Input::showMessage(LocalizationManager::get()->getTranslatedFormattedText("TextPopup_40", uiMirrorCount), LocalizationManager::get()->getTranslatedText("UnableToCheckForUpdates"), MB_OK);
			getIMGF()->getTaskManager()->onResumeTask();
			getIMGF()->getTaskManager()->onTaskEnd("onRequestUpdate", true);
			return;
		}

		vector<string> vecData = String::split(strFileContent, "\n");
		string strLatestVersion = vecData[0];
		string strLatestVersionFileName = vecData[1];
		string strLatestBuildNumber = vecData[2];

		uint32 uiLatestBuildNumber = String::toUint32(strLatestBuildNumber);

		if (uiLatestBuildNumber > 5000) // todo BUILDNUMBER)
		{
			getIMGF()->getTaskManager()->onPauseTask();
			uint32 uiResult = false; // todo - Input::showMessage(LocalizationManager::get()->getTranslatedFormattedText("TextPopup_41", strLatestVersion.c_str(), strLatestBuildNumber.c_str(), getIMGF()->getBuildMeta().getCurrentVersionString().c_str(), BUILDNUMBER_STR), LocalizationManager::get()->getTranslatedText("TextPopupTitle_41"), MB_OKCANCEL);
			getIMGF()->getTaskManager()->onResumeTask();
			if (uiResult == IDOK)
			{
				string strNewProgramData = HTTP::get()->getFileContent(pActiveUpdateConnection->getDownloadFolderURL() + strLatestVersionFileName);

				TCHAR szFilename[MAX_PATH];
				GetModuleFileName(NULL, szFilename, MAX_PATH);
				string strRunningProgramPath = String::convertStdWStringToStdString(szFilename);

				//File::overwriteLockedFileViaContent(strRunningProgramPath, strLatestVersionFileName, strNewProgramData);

				string strLockedFileDirectory = Path::getDirectory(strRunningProgramPath);
				string strNewProgramPath = strLockedFileDirectory + strLatestVersionFileName;
				//rename(strRunningProgramPath.c_str(), (strLockedFileDirectory + "Temp File").c_str());
				strNewProgramPath = File::getNextIncrementingFileName(strNewProgramPath);
				File::storeFile(strNewProgramPath, strNewProgramData, false, true);

				// delete previous version's exe file
				if (getIMGF()->getSettingsManager()->getSettingBool("RemoveOldVersionOnUpdate"))
				{
					TCHAR szModuleName[MAX_PATH];
					GetModuleFileName(NULL, szModuleName, MAX_PATH);
					string strExePath = String::convertStdWStringToStdString(szModuleName);
					if (strNewProgramPath != strExePath)
					{
						SettingsManager::setInternalSetting("DeletePreviousVersionOnNextLaunch", strExePath);
					}
				}

				getIMGF()->getTaskManager()->onPauseTask();
				uint32 uiResult2 = Input::showMessage(LocalizationManager::get()->getTranslatedText("TextPopup_42"), LocalizationManager::get()->getTranslatedText("TextPopupTitle_42"), MB_OKCANCEL);
				getIMGF()->getTaskManager()->onResumeTask();
				if (uiResult2 == IDOK)
				{
					ShellExecute(NULL, NULL, String::convertStdStringToStdWString(strNewProgramPath).c_str(), NULL, NULL, SW_SHOWNORMAL);
				}

				if (uiResult2 == IDOK)
				{
					getIMGF()->getTaskManager()->onTaskEnd("onRequestUpdate");
					ExitProcess(0);
				}
			}
		}
		else
		{
			getIMGF()->getTaskManager()->onPauseTask();
			// todo - Input::showMessage(LocalizationManager::get()->getTranslatedFormattedText("TextPopup_43", getIMGF()->getBuildMeta().getCurrentVersionString().c_str(), BUILDNUMBER_STR), LocalizationManager::get()->getTranslatedText("UpToDate"), MB_OK);
			getIMGF()->getTaskManager()->onResumeTask();
		}
	}
	else
	{
		// non-alpha version
		string strFileContent;
		UpdateConnection *pActiveUpdateConnection = nullptr;
		for (auto pUpdateConnection : getIMGF()->getUpdateManager()->getUpdateConnectionManager()->getEntries())
		{
			if (pUpdateConnection->isAlpha())
			{
				continue;
			}

			pActiveUpdateConnection = pUpdateConnection;
			strFileContent = HTTP::get()->getFileContent(pUpdateConnection->getLatestVersionURL());
			if (strFileContent == "")
			{
				continue;
			}

			break;
		}
		if (strFileContent == "")
		{
			getIMGF()->getTaskManager()->onPauseTask();
			uint32 uiMirrorCount = getIMGF()->getUpdateManager()->getUpdateConnectionManager()->getEntryCount();
			Input::showMessage(LocalizationManager::get()->getTranslatedFormattedText("TextPopup_44", uiMirrorCount), LocalizationManager::get()->getTranslatedText("UnableToCheckForUpdates"), MB_OK);
			getIMGF()->getTaskManager()->onResumeTask();
			getIMGF()->getTaskManager()->onTaskEnd("onRequestUpdate", true);
			return;
		}

		vector<string> vecData = String::split(HTTP::get()->getFileContent(pActiveUpdateConnection->getLatestVersionURL()), "\n");
		string strLatestVersion = vecData[0];
		string strLatestVersionFileName = vecData[1];

		float32 fLatestVersion = String::toFloat32(vecData[0]);

		if (fLatestVersion > getIMGF()->getBuildMeta().getCurrentVersion())
		{
			getIMGF()->getTaskManager()->onPauseTask();
			uint32 uiResult = Input::showMessage(LocalizationManager::get()->getTranslatedFormattedText("TextPopup_45", strLatestVersion.c_str(), getIMGF()->getBuildMeta().getCurrentVersionString().c_str()), LocalizationManager::get()->getTranslatedText("TextPopupTitle_45"), MB_OKCANCEL);
			getIMGF()->getTaskManager()->onResumeTask();
			if (uiResult == IDOK)
			{
				string strNewProgramData = HTTP::get()->getFileContent(pActiveUpdateConnection->getDownloadFolderURL() + strLatestVersionFileName);

				TCHAR szFilename[MAX_PATH];
				GetModuleFileName(NULL, szFilename, MAX_PATH);
				string strRunningProgramPath = String::convertStdWStringToStdString(szFilename);

				//File::overwriteLockedFileViaContent(strRunningProgramPath, strLatestVersionFileName, strNewProgramData);

				string strLockedFileDirectory = Path::getDirectory(strRunningProgramPath);
				string strNewProgramPath = strLockedFileDirectory + strLatestVersionFileName;
				//rename(strRunningProgramPath.c_str(), (strLockedFileDirectory + "Temp File").c_str());
				File::storeFile(strNewProgramPath, strNewProgramData, false, true);

				// delete previous version's exe file
				if (getIMGF()->getSettingsManager()->getSettingBool("RemoveOldVersionOnUpdate"))
				{
					TCHAR szModuleName[MAX_PATH];
					GetModuleFileName(NULL, szModuleName, MAX_PATH);
					string strExePath = String::convertStdWStringToStdString(szModuleName);
					if (strNewProgramPath != strExePath)
					{
						SettingsManager::setInternalSetting("DeletePreviousVersionOnNextLaunch", strExePath);
					}
				}

				getIMGF()->getTaskManager()->onPauseTask();
				uint32 uiResult2 = Input::showMessage(LocalizationManager::get()->getTranslatedText("TextPopup_42"), LocalizationManager::get()->getTranslatedText("TextPopupTitle_42"), MB_OKCANCEL);
				getIMGF()->getTaskManager()->onResumeTask();
				if (uiResult2 == IDOK)
				{
					ShellExecute(NULL, NULL, String::convertStdStringToStdWString(strNewProgramPath).c_str(), NULL, NULL, SW_SHOWNORMAL);
				}

				if (uiResult2 == IDOK)
				{
					getIMGF()->getTaskManager()->onTaskEnd("onRequestUpdate");
					ExitProcess(0);
				}
			}
		}
		else
		{
			getIMGF()->getTaskManager()->onPauseTask();
			Input::showMessage(LocalizationManager::get()->getTranslatedFormattedText("TextPopup_46", getIMGF()->getBuildMeta().getCurrentVersionString().c_str()), LocalizationManager::get()->getTranslatedText("UpToDate"), MB_OK);
			getIMGF()->getTaskManager()->onResumeTask();
		}
	}

	getIMGF()->getTaskManager()->onTaskEnd("onRequestUpdate");
}
void		Tasks::onRequestAutoUpdate(void)
{
	getIMGF()->getTaskManager()->onStartTask("onRequestAutoUpdate");
	vector<string> vecData = String::split(HTTP::get()->getFileContent("http://updater.imgfactory.mvec.io/latest-version.txt"), "\n");
	if (vecData.size() == 0)
	{
		// e.g. no network connection
		getIMGF()->getTaskManager()->onTaskEnd("onRequestAutoUpdate", true);
		return;
	}
	string strLatestVersion = vecData[0];
	string strLatestVersionFileName = vecData[1];

	float32 fLatestVersion = String::toFloat32(vecData[0]);

	if (fLatestVersion > getIMGF()->getBuildMeta().getCurrentVersion())
	{
		getIMGF()->getTaskManager()->onPauseTask();
		uint32 uiResult = Input::showMessage(LocalizationManager::get()->getTranslatedFormattedText("TextPopup_45", strLatestVersion.c_str(), getIMGF()->getBuildMeta().getCurrentVersionString().c_str()), LocalizationManager::get()->getTranslatedText("TextPopupTitle_45"), MB_OKCANCEL);
		getIMGF()->getTaskManager()->onResumeTask();
		if (uiResult == IDOK)
		{
			string strNewProgramData = HTTP::get()->getFileContent("http://updater.imgfactory.mvec.io/versions/" + strLatestVersionFileName);

			TCHAR szFilename[MAX_PATH];
			GetModuleFileName(NULL, szFilename, MAX_PATH);
			string strRunningProgramPath = String::convertStdWStringToStdString(szFilename);

			//File::overwriteLockedFileViaContent(strRunningProgramPath, strLatestVersionFileName, strNewProgramData);

			string strLockedFileDirectory = Path::getDirectory(strRunningProgramPath);
			string strNewProgramPath = strLockedFileDirectory + strLatestVersionFileName;
			//rename(strRunningProgramPath.c_str(), (strLockedFileDirectory + "Temp File").c_str());
			File::storeFile(strNewProgramPath, strNewProgramData, false, true);

			// delete previous version's exe file
			if (getIMGF()->getSettingsManager()->getSettingBool("RemoveOldVersionOnUpdate"))
			{
				TCHAR szModuleName[MAX_PATH];
				GetModuleFileName(NULL, szModuleName, MAX_PATH);
				string strExePath = String::convertStdWStringToStdString(szModuleName);
				SettingsManager::setInternalSetting("DeletePreviousVersionOnNextLaunch", strExePath);
			}

			getIMGF()->getTaskManager()->onPauseTask();
			uint32 uiResult2 = Input::showMessage(LocalizationManager::get()->getTranslatedText("TextPopup_42"), LocalizationManager::get()->getTranslatedText("TextPopupTitle_42"), MB_OKCANCEL);
			getIMGF()->getTaskManager()->onResumeTask();
			if (uiResult2 == IDOK)
			{
				ShellExecute(NULL, NULL, String::convertStdStringToStdWString(strNewProgramPath).c_str(), NULL, NULL, SW_SHOWNORMAL);
			}

			// close the currently open program
			if (uiResult2 == IDOK)
			{
				getIMGF()->getTaskManager()->onTaskEnd("onRequestAutoUpdate");
				ExitProcess(0);
			}
		}
	}
	getIMGF()->getTaskManager()->onTaskEnd("onRequestAutoUpdate");
}

void			Tasks::onRequestRenamer(void)
{
	/*
	todo
	getIMGF()->getTaskManager()->onStartTask("onRequestRenamer");
	getIMGF()->getTaskManager()->onPauseTask();
	CRenamerDialogData *pRenamerDialogData = getIMGF()->getPopupGUIManager()->showRenamerDialog();
	getIMGF()->getTaskManager()->onResumeTask();

	if (!pRenamerDialogData->m_bRename)
	{
		delete pRenamerDialogData;
		getIMGF()->getTaskManager()->onTaskEnd("onRequestRenamer", true);
		return;
	}

	// ensure a tab is open
	if (getIMGF()->getEntryListTab() == nullptr)
	{
		Input::showMessage(LocalizationManager::get()->getTranslatedText("TextPopup_50"), LocalizationManager::get()->getTranslatedText("TextPopupTitle_50"), MB_OK);
		delete pRenamerDialogData;
		getIMGF()->getTaskManager()->onTaskEnd("onRequestRenamer", true);
		return;
	}

	// choose entries to rename
	vector<IMGEntry*> vecIMGEntries;
	if (pRenamerDialogData->m_ucEntriesType == 0) // all entries
	{
		vecIMGEntries = getIMGF()->getEntryListTab()->getIMGFile()->getEntries();
	}
	else if (pRenamerDialogData->m_ucEntriesType == 1) // selected entries
	{
		vecIMGEntries = getIMGF()->getEntryListTab()->getSelectedEntries();
	}

	setMaxProgress(vecIMGEntries.size() * 2); // x1 for the main loop, and x1 for the refreshing the main list view display

	vector<RenamedIMGEntry*> vecIMGEntriesWithNewNames;

	// loop around entries
	for (auto pIMGEntry : vecIMGEntries)
	{
		// skip LODs if "update LOD names to match new name" is enabled, as matching LOD entries will be updated anyway
		if (pRenamerDialogData->m_bUpdateLODNamesToMatch)
		{
			if (String::toUpperCase(pIMGEntry->getEntryName().substr(0, 3)) == "LOD")
			{
				increaseProgress();
				continue;
			}
		}

		string strEntryPreviousName = pIMGEntry->getEntryName();

		// character adding/replacing
		if (pRenamerDialogData->m_ucCharReplacementType == 0) // don't replace characters
		{
			if (pRenamerDialogData->m_strCharAdding_Front != "")
			{
				pIMGEntry->setEntryName(pRenamerDialogData->m_strCharAdding_Front + pIMGEntry->getEntryName());
			}

			if (pRenamerDialogData->m_strCharAdding_End != "")
			{
				pIMGEntry->setEntryName(pIMGEntry->getEntryName() + pRenamerDialogData->m_strCharAdding_End);
			}

			if (pRenamerDialogData->m_strCharAdding_AtPosition != "")
			{
				uint32
					uiPosition = pRenamerDialogData->m_uiCharAddingAtPosition_Position;
				if (uiPosition <= pIMGEntry->getEntryName().length())
				{
					string
						strNameBefore = pIMGEntry->getEntryName().substr(0, uiPosition),
						strNameAfter = pIMGEntry->getEntryName().substr(uiPosition);
					pIMGEntry->setEntryName(strNameBefore + pRenamerDialogData->m_strCharAdding_AtPosition + strNameAfter);
				}
			}
		}
		else if (pRenamerDialogData->m_ucCharReplacementType == 1) // always replace characters
		{
			if (pRenamerDialogData->m_strCharAdding_Front != "")
			{
				string strNewEntryName = pRenamerDialogData->m_strCharAdding_Front + pIMGEntry->getEntryName().substr(pRenamerDialogData->m_strCharAdding_Front.length());
				pIMGEntry->setEntryName(strNewEntryName);
			}

			if (pRenamerDialogData->m_strCharAdding_End != "")
			{
				string strNewEntryName = pIMGEntry->getEntryName().substr(0, pIMGEntry->getEntryName().length() - pRenamerDialogData->m_strCharAdding_End.length()) + pRenamerDialogData->m_strCharAdding_End;
				pIMGEntry->setEntryName(strNewEntryName);
			}

			if (pRenamerDialogData->m_strCharAdding_AtPosition != "")
			{
				uint32
					uiPosition = pRenamerDialogData->m_uiCharAddingAtPosition_Position;
				if (uiPosition <= pIMGEntry->getEntryName().length())
				{
					string
						strNameBefore = pIMGEntry->getEntryName().substr(0, uiPosition),
						strNameAfter = pIMGEntry->getEntryName().substr(uiPosition + pRenamerDialogData->m_strCharAdding_AtPosition.length());
					pIMGEntry->setEntryName(strNameBefore + pRenamerDialogData->m_strCharAdding_AtPosition + strNameAfter);
				}
			}
		}
		else if (pRenamerDialogData->m_ucCharReplacementType == 2) // only replace characters if length exceeds
		{
			uint32
				uiExceedLength = pRenamerDialogData->m_uiCharReplaceConditional_Length;

			if (pRenamerDialogData->m_strCharAdding_Front != "")
			{
				string strPrefixText = pRenamerDialogData->m_strCharAdding_Front;
				string strEntryName = pIMGEntry->getEntryName();

				string strExtension = Path::getFileExtension(pIMGEntry->getEntryName());
				uint32 uiCharCountLeft = uiExceedLength - (strExtension.length() + 1);

				string strEntryNewName = String::mergeStrings(strPrefixText, Path::removeFileExtension(strEntryName), uiExceedLength) + "." + strExtension;


				//////////////////////////////////////
				uint32 uiNewLength = pRenamerDialogData->m_strCharAdding_Front.length() + pIMGEntry->getEntryName().length();
				uint32 uiNameAfterSubstrPosition = uiNewLength > uiExceedLength ? (uiNewLength - uiExceedLength) : 0;
				//Debugger::log("pRenamerDialogData->m_strCharAdding_Front.length(): " + String::toString(pRenamerDialogData->m_strCharAdding_Front.length()));
				//Debugger::log("pIMGEntry->getEntryName().length(): " + String::toString(pIMGEntry->getEntryName().length()));
				//Debugger::log("uiNewLength: " + String::toString(uiNewLength));
				//Debugger::log("uiNameAfterSubstrPosition: " + String::toString(uiNameAfterSubstrPosition));
				string strNameAfter = pIMGEntry->getEntryName().substr(uiNameAfterSubstrPosition); // substr(12) causes crash when str.size() == 11
				string strNewEntryName = pRenamerDialogData->m_strCharAdding_Front + strNameAfter;
				/////////////////////////////////////
				pIMGEntry->setEntryName(strEntryNewName);
			}

			if (pRenamerDialogData->m_strCharAdding_End != "")
			{
				uint32 uiNewLength = pRenamerDialogData->m_strCharAdding_End.length() + pIMGEntry->getEntryName().length();
				uint32 uiNameBeforeSubstrLength = uiNewLength > uiExceedLength ? (pIMGEntry->getEntryName().length() - (uiNewLength - uiExceedLength)) : 0;
				string strNameBefore = pIMGEntry->getEntryName().substr(0, uiNameBeforeSubstrLength);
				string strNewEntryName = strNameBefore + pRenamerDialogData->m_strCharAdding_End;
				pIMGEntry->setEntryName(strNewEntryName);
			}

			if (pRenamerDialogData->m_strCharAdding_AtPosition != "")
			{
				uint32
					uiPosition = pRenamerDialogData->m_uiCharAddingAtPosition_Position;
				if (uiPosition <= pIMGEntry->getEntryName().length())
				{
					uint32 uiNewLength = pRenamerDialogData->m_strCharAdding_AtPosition.length() + pIMGEntry->getEntryName().length();
					uint32 uiNameAfterSubstrPosition = uiNewLength > uiExceedLength ? (uiPosition + (uiNewLength - uiExceedLength)) : 0;
					string
						strNameBefore = pIMGEntry->getEntryName().substr(0, uiPosition),
						strNameAfter = pIMGEntry->getEntryName().substr(uiNameAfterSubstrPosition);
					string strNewEntryName = strNameBefore + pRenamerDialogData->m_strCharAdding_AtPosition + strNameAfter;
					pIMGEntry->setEntryName(strNewEntryName);
				}
			}
		}

		// character removing
		if (pRenamerDialogData->m_uiCharRemoving_Front > 0)
		{
			if ((pIMGEntry->getEntryName().length() - pRenamerDialogData->m_uiCharRemoving_Front) > 0)
			{
				pIMGEntry->setEntryName(pIMGEntry->getEntryName().substr(pRenamerDialogData->m_uiCharRemoving_Front));
			}
		}

		if (pRenamerDialogData->m_uiCharRemoving_End > 0)
		{
			if ((pIMGEntry->getEntryName().length() - pRenamerDialogData->m_uiCharRemoving_End) > 0)
			{
				pIMGEntry->setEntryName(pIMGEntry->getEntryName().substr(pIMGEntry->getEntryName().length() - pRenamerDialogData->m_uiCharRemoving_End));
			}
		}

		if (pRenamerDialogData->m_uiCharRemoving_AtPosition > 0)
		{
			uint32
				uiPosition = pRenamerDialogData->m_uiCharRemovingAtPosition_Position,
				uiLength = pRenamerDialogData->m_uiCharRemoving_AtPosition;
			if ((pIMGEntry->getEntryName().length() - uiLength) > 0)
			{
				string
					strNameBefore = pIMGEntry->getEntryName().substr(0, uiPosition),
					strNameAfter = pIMGEntry->getEntryName().substr(uiPosition + uiLength);
				pIMGEntry->setEntryName(strNameBefore + strNameAfter);
			}
		}

		// character case
		if (pRenamerDialogData->m_ucCharCaseType == 0)
		{
			// leave untouched
		}
		else if (pRenamerDialogData->m_ucCharCaseType == 1)
		{
			// uppercase
			pIMGEntry->setEntryName(String::toUpperCase(pIMGEntry->getEntryName()));
		}
		else if (pRenamerDialogData->m_ucCharCaseType == 2)
		{
			// lowercase
			pIMGEntry->setEntryName(String::toLowerCase(pIMGEntry->getEntryName()));
		}
		else if (pRenamerDialogData->m_ucCharCaseType == 3)
		{
			// title case
			pIMGEntry->setEntryName(String::toTitleCase(pIMGEntry->getEntryName()));
		}

		// mark IMG entry as renamed
		if (strEntryPreviousName != pIMGEntry->getEntryName())
		{
			RenamedIMGEntry *pRenamedIMGEntry = new RenamedIMGEntry;
			pRenamedIMGEntry->m_pIMGEntry = pIMGEntry;
			pRenamedIMGEntry->m_strPreviousName = strEntryPreviousName;
			vecIMGEntriesWithNewNames.push_back(pRenamedIMGEntry);
		}

		// update LOD names to match new name
		if (pRenamerDialogData->m_bUpdateLODNamesToMatch)
		{
			string strLODPreviousName = "LOD" + strEntryPreviousName.substr(3);
			IMGEntry *pIMGEntryLOD = getIMGF()->getEntryListTab()->getIMGFile()->getEntryByName(strLODPreviousName);
			if (pIMGEntryLOD != nullptr)
			{
				string strLODNewName = pIMGEntryLOD->getEntryName().substr(0, 3) + pIMGEntry->getEntryName().substr(3);
				pIMGEntryLOD->setEntryName(strLODNewName);

				// mark IMG entry as renamed
				if (strLODPreviousName != strLODNewName)
				{
					RenamedIMGEntry *pRenamedIMGEntry = new RenamedIMGEntry;
					pRenamedIMGEntry->m_pIMGEntry = pIMGEntryLOD;
					pRenamedIMGEntry->m_strPreviousName = strLODPreviousName;
					vecIMGEntriesWithNewNames.push_back(pRenamedIMGEntry);
				}
			}
		}

		// progress bar
		increaseProgress();
	}

	// matching entries
	vector<string> vecFilePaths;

	// matching entries - IDE
	if (pRenamerDialogData->m_bMatchingState_IDE)
	{
		vecFilePaths = File::getFilePaths(pRenamerDialogData->m_strMatchingPath_IDE, true);
		for (auto strFilePath : vecFilePaths)
		{
			if (String::toUpperCase(Path::getFileExtension(strFilePath)) == "IDE")
			{
				IDEFormat *pIDEFile = IDEManager::get()->unserializeFile(strFilePath);
				
				if(pIDEFile->doesHaveError())
				{
					pIDEFile->unload();
					delete pIDEFile;
					continue;
				}
				
				for (auto pRenamedIMGEntry : vecIMGEntriesWithNewNames)
				{
					vector<IDEEntry*> vecIDEEntries;

					// OBJS/TOBJ model name
					vecIDEEntries = pIDEFile->getEntriesByModelName(Path::removeFileExtension(pRenamedIMGEntry->m_strPreviousName));
					for (auto pIDEEntry : vecIDEEntries)
					{
						switch (pIDEEntry->getSectionType()) // todo - make work with all sections with setModelName on IDEEntry_Data and IPLEntry_Data
						{
						case IDE_SECTION_OBJS:
							((IDEEntry_OBJS*)pIDEEntry)->setModelName(Path::removeFileExtension(pRenamedIMGEntry->m_pIMGEntry->getEntryName()));
							break;
						case IDE_SECTION_TOBJ:
							((IDEEntry_TOBJ*)pIDEEntry)->setModelName(Path::removeFileExtension(pRenamedIMGEntry->m_pIMGEntry->getEntryName()));
							break;
						}
					}

					// OBJS/TOBJ texture name
					vecIDEEntries = pIDEFile->getEntriesByTXDName(Path::removeFileExtension(pRenamedIMGEntry->m_strPreviousName));
					for (auto pIDEEntry : vecIDEEntries)
					{
						switch (pIDEEntry->getSectionType()) // todo - make work with all sections with setTXDName on IDEEntry_Data and IPLEntry_Data
						{
						case IDE_SECTION_OBJS:
							((IDEEntry_OBJS*)pIDEEntry)->setTXDName(Path::removeFileExtension(pRenamedIMGEntry->m_pIMGEntry->getEntryName()));
							break;
						case IDE_SECTION_TOBJ:
							((IDEEntry_TOBJ*)pIDEEntry)->setTXDName(Path::removeFileExtension(pRenamedIMGEntry->m_pIMGEntry->getEntryName()));
							break;
						}
					}
				}

				pIDEFile->serializeViaFile();
				pIDEFile->unload();
				delete pIDEFile;
			}
		}
	}

	// matching entries - IPL
	if (pRenamerDialogData->m_bMatchingState_IPL)
	{
		vecFilePaths = File::getFilePaths(pRenamerDialogData->m_strMatchingPath_IPL, true);
		for (auto strFilePath : vecFilePaths)
		{
			if (String::toUpperCase(Path::getFileExtension(strFilePath)) == "IPL")
			{
				IPLFormat *pIPLFile = IPLManager::get()->unserializeFile(strFilePath);
				
				if(pIPLFile->doesHaveError())
				{
					pIPLFile->unload();
					delete pIPLFile;
					continue;
				}
				
				if (pIPLFile->isBinary()) // skip binary IPL files as they don't contain a model name
				{
					pIPLFile->unload();
					delete pIPLFile;
					continue;
				}

				for (auto pRenamedIMGEntry : vecIMGEntriesWithNewNames)
				{
					vector<IPLEntry*> vecIPLEntries;

					// INST model name
					vecIPLEntries = pIPLFile->getEntriesByModelName(Path::removeFileExtension(pRenamedIMGEntry->m_strPreviousName));
					for (auto pIPLEntry : vecIPLEntries)
					{
						// todo - make work with all sections with setModelName on IDEEntry_Data and IPLEntry_Data
						if (pIPLEntry->getSectionType() == IPL_SECTION_INST)
						{
							((IPLEntry_INST*)pIPLEntry)->setModelName(Path::removeFileExtension(pRenamedIMGEntry->m_pIMGEntry->getEntryName()));
						}
					}
				}

				pIPLFile->serializeViaFile();
				pIPLFile->unload();
				delete pIPLFile;
			}
		}
	}

	// matching entries - COL
	vector<string> vecCorruptCOLFiles;
	if (pRenamerDialogData->m_bMatchingState_COL)
	{
		vecFilePaths = File::getFilePaths(pRenamerDialogData->m_strMatchingPath_COL, true);
		for (auto strFilePath : vecFilePaths)
		{
			if (String::toUpperCase(Path::getFileExtension(strFilePath)) == "COL")
			{
				//Debugger::log("strFilePath: " + strFilePath);
				COLFormat *pCOLFile = COLManager::get()->unserializeFile(strFilePath);
				pCOLFile->setFilePath(strFilePath);
				if (pCOLFile->doesHaveError())
				{
					vecCorruptCOLFiles.push_back(Path::getFileName(pCOLFile->getFilePath()) + " - Corrupt Reason: " + pCOLFile->getErrorReason());
					//Debugger::log(Path::getFileName(pCOLFile->getFilePath()) + " - CORRUPT REASON: " + pCOLFile->getCorruptReason());
					pCOLFile->unload();
					delete pCOLFile;
					continue;
				}

				for (auto pRenamedIMGEntry : vecIMGEntriesWithNewNames)
				{
					vector<COLEntry*> vecCOLEntries;

					// COL model name
					vecCOLEntries = pCOLFile->getEntriesByModelName(Path::removeFileExtension(pRenamedIMGEntry->m_strPreviousName));
					for (auto pCOLEntry : vecCOLEntries)
					{
						pCOLEntry->setModelName(Path::removeFileExtension(pRenamedIMGEntry->m_pIMGEntry->getEntryName()));
					}
				}

				pCOLFile->serializeViaFile();
				pCOLFile->unload();
				delete pCOLFile;
			}
		}
	}

	// log
	// todo - getIMGF()->getEntryListTab()->log(LocalizationManager::get()->getTranslatedFormattedText("Log_116", vecIMGEntriesWithNewNames.size()));
	// todo - getIMGF()->getEntryListTab()->log(LocalizationManager::get()->getTranslatedText("Log_117"), true);
	// todo - getIMGF()->getEntryListTab()->log(String::join(vecCorruptCOLFiles, "\n"), true);

	// mark tab as modified
	getIMGTab()->setIMGModifiedSinceRebuild(true);

	// refresh tab's main list view
	getIMGF()->getIMGEditor()->refreshActiveTab();

	// clean up
	for (auto pRenamedIMGEntry : vecIMGEntriesWithNewNames)
	{
		delete pRenamedIMGEntry;
	}
	vecIMGEntriesWithNewNames.clear();
	delete pRenamerDialogData;
	getIMGF()->getTaskManager()->onTaskEnd("onRequestRenamer");
	*/
}

void		Tasks::onRequestBuildTXD(void)
{
	/*
	getIMGF()->getTaskManager()->onStartTask("onRequestBuildTXD");

	getIMGF()->getTaskManager()->onPauseTask();
	CBuildTXDDialogData *pBuildTXDDialogData = getIMGF()->getPopupGUIManager()->showBuildTXDDialog();
	getIMGF()->getTaskManager()->onResumeTask();

	if (!pBuildTXDDialogData->m_bBuild) // cancel
	{
		getIMGF()->getTaskManager()->onTaskEnd("onRequestBuildTXD", true);
		delete pBuildTXDDialogData;
		return;
	}

	// choose DFF files
	//vector<DFFFormat*> veDFFFormats;
	unordered_map<DFFFormat*, string> umapDFFEntries;
	if (pBuildTXDDialogData->m_uDFFFormatsType == 0) // All DFF entries in active tab
	{
		if (!getIMGF()->getEntryListTab())
		{
			getIMGF()->getTaskManager()->onTaskEnd("onRequestBuildTXD", true);
			delete pBuildTXDDialogData;
			return;
		}

		vector<IMGEntry*> vecIMGEntries = getIMGF()->getEntryListTab()->getIMGFile()->getEntriesByExtension("DFF");
		vector<IMGEntry*> vecIMGEntries_BSP = getIMGF()->getEntryListTab()->getIMGFile()->getEntriesByExtension("BSP");
		for (auto pIMGEntry : vecIMGEntries_BSP)
		{
			vecIMGEntries.push_back(pIMGEntry);
		}
		for (auto pIMGEntry : vecIMGEntries)
		{
			DFFFormat *pDFFFile = DFFManager::get()->unserializeMemory(pIMGEntry->getEntryData());
			umapDFFEntries[pDFFFile] = Path::removeFileExtension(pIMGEntry->getEntryName());
		}
	}
	else if (pBuildTXDDialogData->m_uDFFFormatsType == 1) // Selected DFF entries in active tab
	{
		if (!getIMGF()->getEntryListTab())
		{
			getIMGF()->getTaskManager()->onTaskEnd("onRequestBuildTXD", true);
			delete pBuildTXDDialogData;
			return;
		}

		vector<IMGEntry*> vecIMGEntries = getIMGF()->getEntryListTab()->getSelectedEntries();
		
		for(auto pIMGEntry : vecIMGEntries)
		{
			if (GameFormat::isModelExtension(String::toUpperCase(Path::getFileExtension(pIMGEntry->getEntryName()))))
			{
				DFFFormat *pDFFFile = DFFManager::get()->unserializeMemory(pIMGEntry->getEntryData());
				umapDFFEntries[pDFFFile] = Path::removeFileExtension(pIMGEntry->getEntryName());
			}
		}
	}
	else if (pBuildTXDDialogData->m_uDFFFormatsType == 2) // All DFF entries in all tabs
	{
		if (!getIMGF()->getEntryListTab())
		{
			getIMGF()->getTaskManager()->onTaskEnd("onRequestBuildTXD", true);
			delete pBuildTXDDialogData;
			return;
		}

		for (auto pEditorTab : getIMGF()->getIMGEditor()->getTabs().getEntries())
		{
			vector<IMGEntry*> vecIMGEntries = ((IMGEditorTab*)pEditorTab)->getIMGFile()->getEntriesByExtension("DFF");
			vector<IMGEntry*> vecIMGEntries_BSP = ((IMGEditorTab*)pEditorTab)->getIMGFile()->getEntriesByExtension("BSP");
			for (auto pIMGEntry : vecIMGEntries_BSP)
			{
				vecIMGEntries.push_back(pIMGEntry);
			}
			for (auto pIMGEntry : vecIMGEntries)
			{
				DFFFormat *pDFFFile = DFFManager::get()->unserializeMemory(pIMGEntry->getEntryData());
				umapDFFEntries[pDFFFile] = Path::removeFileExtension(pIMGEntry->getEntryName());
			}
		}
	}
	else if (pBuildTXDDialogData->m_uDFFFormatsType == 3) // Folder containing DFF files
	{
		vector<string> vecFileNames = File::getFileNames(pBuildTXDDialogData->m_strDFFsFolderPath);

		for (string strFileName : vecFileNames)
		{
			string strExtensionUpper = String::toUpperCase(Path::getFileExtension(strFileName));
			if (GameFormat::isModelExtension(strExtensionUpper))
			{
				DFFFormat *pDFFFile = DFFManager::get()->unserializeMemory(pBuildTXDDialogData->m_strDFFsFolderPath + strFileName);
				umapDFFEntries[pDFFFile] = Path::removeFileExtension(strFileName);
			}
		}
	}
	else if (pBuildTXDDialogData->m_uDFFFormatsType == 4) // IDE file referencing DFF files
	{
		IDEFormat *pIDEFile = IDEManager::get()->unserializeFile(pBuildTXDDialogData->m_strIDEFilePath);
		if(!pIDEFile->doesHaveError())
		{
			// todo - make it work with all IDE sections
			for (auto pIDEEntry : pIDEFile->getEntriesBySection<IDEEntry_OBJS>(IDE_SECTION_OBJS))
			{
				DFFFormat *pDFFFile = DFFManager::get()->unserializeMemory(pBuildTXDDialogData->m_strDFFsFolderPath + pIDEEntry->getModelName());
				umapDFFEntries[pDFFFile] = pIDEEntry->getTXDName();
			}
			for (auto pIDEEntry : pIDEFile->getEntriesBySection<IDEEntry_TOBJ>(IDE_SECTION_TOBJ))
			{
				DFFFormat *pDFFFile = DFFManager::get()->unserializeMemory(pBuildTXDDialogData->m_strDFFsFolderPath + pIDEEntry->getModelName());
				umapDFFEntries[pDFFFile] = pIDEEntry->getTXDName();
			}
		}
		
		pIDEFile->unload();
		delete pIDEFile;
	}

	// process
	//for (auto pDFFFile : veDFFFormats)
	uint32
		uiTotalTXDFileCount = 0,
		uiTotalTextureCountUsed = 0;
	vector<string>
		vecTextureImagesNotFound,
		veTXDFormatNames;
	setMaxProgress(umapDFFEntries.size());
	for (auto it : umapDFFEntries)
	{
		DFFFormat *pDFFFile = it.first;
		string strOutputFileName = it.second + ".txd";

		if (pDFFFile->doesHaveError())
		{
			increaseProgress();
			continue;
		}

		vector<string> vecTextureNames = pDFFFile->getTextureNames();
		vecTextureNames = StdVector::removeDuplicates(vecTextureNames);

		uint32 uiTXDFileCount = pBuildTXDDialogData->m_uiTextureCountPerTXD == 0 ? 1 : (uint32) ceil((float32)vecTextureNames.size() / (float32)pBuildTXDDialogData->m_uiTextureCountPerTXD);
		uiTotalTXDFileCount += uiTXDFileCount;
		uint32 uiTXDFileIndex = 0;
		for (uint32 i = 0; i < uiTXDFileCount; i++)
		{
			string strFilePath = pBuildTXDDialogData->m_strDestinationFolderPath + strOutputFileName;
			strFilePath = Path::getNextFileName(strFilePath, uiTXDFileIndex, "-part");

			TXDFormat *pTXDFile = TXDManager::get()->createFormat();
			pTXDFile->setRWVersion(pBuildTXDDialogData->m_pRWVersion);
			for (uint32 i2 = i * pBuildTXDDialogData->m_uiTextureCountPerTXD, j2 = i2 + (pBuildTXDDialogData->m_uiTextureCountPerTXD == 0 ? vecTextureNames.size() : pBuildTXDDialogData->m_uiTextureCountPerTXD); i2 < j2; i2++)
			{
				if (i2 >= vecTextureNames.size())
				{
					break;
				}

				string strTextureName = vecTextureNames[i2];
				string strTextureImagePath = File::findImageFile(strTextureName, pBuildTXDDialogData->m_strTexturesFolderPath);

				// check if texture file exists
				if (strTextureImagePath != "")
				{
					uiTotalTextureCountUsed++;

					// add texture to TXD
					RWSection_TextureNative *pTexture = pTXDFile->addTextureViaFile(strTextureImagePath, strTextureName, strTextureName + "a");

					if (pTexture != nullptr)
					{
						//vector<string> vecMipmapsRemoved;
						//pTexture->convertToRasterDataFormat(pBuildTXDDialogData->m_pRasterDataFormat->getId(), vecMipmapsRemoved);
					}
				}
				else
				{
					vecTextureImagesNotFound.push_back(strTextureName + ".BMP");
				}
			}
			if (pTXDFile->getTextures().size() > 0)
			{
				pTXDFile->storeViaFile(strFilePath);
				veTXDFormatNames.push_back(Path::getFileName(strFilePath));
				uiTXDFileIndex++;
			}
			
			pTXDFile->unload();
			delete pTXDFile;
		}

		increaseProgress();
	}

	// log
	// todo - getIMGF()->getEntryListTab()->log(LocalizationManager::get()->getTranslatedFormattedText("Log_118", uiTotalTXDFileCount, uiTotalTextureCountUsed));
	// todo - getIMGF()->getEntryListTab()->log(LocalizationManager::get()->getTranslatedFormattedText("Log_119", pBuildTXDDialogData->m_strTexturesFolderPath.c_str()), true);
	// todo - getIMGF()->getEntryListTab()->log(String::join(vecTextureImagesNotFound, "\n"), true);
	// todo - getIMGF()->getEntryListTab()->log(LocalizationManager::get()->getTranslatedText("Log_120"), true);
	// todo - getIMGF()->getEntryListTab()->log(String::join(veTXDFormatNames, "\n"), true);

	// clean up
	//for (DFFFormat *pDFFFile : veDFFFormats)
	for (auto it : umapDFFEntries)
	{
		DFFFormat *pDFFFile = it.first;
		pDFFFile->unload();
		delete pDFFFile;
	}
	//veDFFFormats.clear();
	umapDFFEntries.clear();
	delete pBuildTXDDialogData;
	getIMGF()->getTaskManager()->onTaskEnd("onRequestBuildTXD");
	*/
}

void		Tasks::onRequestFeatureByName(string strFeatureName)
{
	/*
	todo

	if (strFeatureName == "onRequestFeatureByName")
	{
	}
	else if (strFeatureName == "chooseFilesToOpen")
	{
		chooseFilesToOpen();
	}
	else if (strFeatureName == "openFile")
	{
		openFile(getIMGF()->getLastUsedValueManager()->getLastUsedValue_Open2_IMGPath());
	}
	else if (strFeatureName == "closeFile")
	{
		closeFile();
	}
	else if (strFeatureName == "onRequestExitTool")
	{
		onRequestExitTool();
	}
	else if (strFeatureName == "importByFiles")
	{
		importByFiles();
	}
	else if (strFeatureName == "importBySingleFolder")
	{
		importBySingleFolder();
	}
	else if (strFeatureName == "importByFolderRecursively")
	{
		importByFolderRecursively();
	}
	else if (strFeatureName == "removeSelected")
	{
		removeSelected();
	}
	else if (strFeatureName == "rename")
	{
		rename();
	}
	else if (strFeatureName == "selectAll")
	{
		selectAll();
	}
	else if (strFeatureName == "unselectAll")
	{
		unselectAll();
	}
	else if (strFeatureName == "selectInverse")
	{
		selectInverse();
	}
	else if (strFeatureName == "onRequestRebuild")
	{
		onRequestRebuild();
	}
	else if (strFeatureName == "onRequestRebuildAs")
	{
		onRequestRebuildAs();
	}
	else if (strFeatureName == "onRequestRebuildAll")
	{
		onRequestRebuildAll();
	}
	else if (strFeatureName == "convertIMGVersion")
	{
		convertIMGVersion();
	}
	else if (strFeatureName == "merge")
	{
		merge();
	}
	else if (strFeatureName == "split")
	{
		split();
	}
	else if (strFeatureName == "onRequestSplitViaIDEFile")
	{
		onRequestSplitViaIDEFile();
	}
	else if (strFeatureName == "onRequestSplitViaTextLines")
	{
		onRequestSplitViaTextLines();
	}
	else if (strFeatureName == "replaceByFiles")
	{
		replaceByFiles();
	}
	else if (strFeatureName == "replaceBySingleFolder")
	{
		replaceBySingleFolder();
	}
	else if (strFeatureName == "replaceByFolderRecursively")
	{
		replaceByFolderRecursively();
	}
	else if (strFeatureName == "onRequestExportSelected")
	{
		exportSelected();
	}
	else if (strFeatureName == "onRequestSearchText")
	{
		onRequestSearchText();
	}
	else if (strFeatureName == "onRequestSearchSelection")
	{
		onRequestSearchSelection();
	}
	else if (strFeatureName == "onRequestFilter")
	{
		onRequestFilter();
	}
	else if (strFeatureName == "onRequestFind")
	{
		onRequestFind();
	}
	else if (strFeatureName == "onRequestExportViaIDEFile")
	{
		onRequestExportViaIDEFile();
	}
	else if (strFeatureName == "onRequestExportViaTextLines")
	{
		onRequestExportViaTextLines();
	}
	else if (strFeatureName == "onRequestSortEntries")
	{
		onRequestSortEntries();
	}
	else if (strFeatureName == "onRequestSortButton")
	{
		onRequestSortButton();
	}
	else if (strFeatureName == "onRequestRemoveViaIDEFile")
	{
		onRequestRemoveViaIDEFile();
	}
	else if (strFeatureName == "onRequestRemoveViaTextLines")
	{
		onRequestRemoveViaTextLines();
	}
	else if (strFeatureName == "importByIDE")
	{
		importByIDE();
	}
	else if (strFeatureName == "onRequestImportViaTextLines")
	{
		onRequestImportViaTextLines();
	}
	else if (strFeatureName == "_newFile")
	{
		_newFile();
	}
	else if (strFeatureName == "onRequestStats")
	{
		onRequestStats();
	}
	else if (strFeatureName == "onRequestNameCase")
	{
		onRequestNameCase(getIMGF()->getLastUsedValueManager()->getLastUsedValue_NameCase_CaseType(), getIMGF()->getLastUsedValueManager()->getLastUsedValue_NameCase_FilenameType());
	}
	else if (strFeatureName == "onRequestCopyEntryData")
	{
		onRequestCopyEntryData(getIMGF()->getLastUsedValueManager()->getLastUsedValue_Copy_IMGEntryProperty());
	}
	else if (strFeatureName == "onRequestShift")
	{
		onRequestShift(getIMGF()->getLastUsedValueManager()->getLastUsedValue_Shift_Direction());
	}
	else if (strFeatureName == "onRequestQuickExport")
	{
		onRequestQuickExport();
	}
	else if (strFeatureName == "onRequestSelectViaFileExtension")
	{
		onRequestSelectViaFileExtension();
	}
	else if (strFeatureName == "onRequestVersion")
	{
		onRequestVersion();
	}
	else if (strFeatureName == "onRequestTextureList")
	{
		onRequestTextureList();
	}
	else if (strFeatureName == "onRequestAssociateIMGExtension")
	{
		onRequestAssociateIMGExtension();
	}
	else if (strFeatureName == "onRequestSaveLog")
	{
		onRequestSaveLog(getIMGF()->getLastUsedValueManager()->getLastUsedValue_SaveLog_ActiveTab(), getIMGF()->getLastUsedValueManager()->getLastUsedValue_SaveLog_NormalFormat());
	}
	else if (strFeatureName == "onRequestSaveSession")
	{
		onRequestSaveSession();
	}
	else if (strFeatureName == "onRequestSettings")
	{
		onRequestSettings();
	}
	else if (strFeatureName == "onRequestReopen")
	{
		onRequestReopen();
	}
	else if (strFeatureName == "onRequestConvertDFFToRWVersion")
	{
		onRequestConvertDFFToRWVersion(getIMGF()->getLastUsedValueManager()->getLastUsedValue_ConvertDFF_RWVersion());
	}
	else if (strFeatureName == "onRequestMissingTextures")
	{
		onRequestMissingTextures();
	}
	else if (strFeatureName == "saveAllOpenFiles")
	{
		saveAllOpenFiles(getIMGF()->getLastUsedValueManager()->getLastUsedValue_Close2_CloseAll());
	}
	else if (strFeatureName == "onRequestReplaceAllFromFolder")
	{
		onRequestReplaceAllFromFolder();
	}
	else if (strFeatureName == "onRequestExportAllEntriesFromAllTabs")
	{
		onRequestExportAllEntriesFromAllTabs();
	}
	else if (strFeatureName == "onRequestExportEntriesViaIDEFileFromAllTabs")
	{
		onRequestExportEntriesViaIDEFileFromAllTabs();
	}
	else if (strFeatureName == "onRequestExportEntriesViaTextLinesFromAllTabs")
	{
		onRequestExportEntriesViaTextLinesFromAllTabs();
	}
	else if (strFeatureName == "onRequestDuplicateEntries")
	{
		onRequestDuplicateEntries();
	}
	else if (strFeatureName == "exportAllIntoGroupedFoldersByType")
	{
		exportAllIntoGroupedFoldersByType();
	}
	else if (strFeatureName == "onRequestOpenLast")
	{
		onRequestOpenLast();
	}
	else if (strFeatureName == "onRequestConvertTXDToGame")
	{
		onRequestConvertTXDToGame(getIMGF()->getLastUsedValueManager()->getLastUsedValue_ConvertTXD_Game());
	}
	else if (strFeatureName == "onRequestConvertTXDToRWVersion")
	{
		onRequestConvertTXDToRWVersion(getIMGF()->getLastUsedValueManager()->getLastUsedValue_ConvertTXD_RWVersion());
	}
	else if (strFeatureName == "onRequestDump")
	{
		onRequestDump();
	}
	else if (strFeatureName == "onRequestSessionManager")
	{
		onRequestSessionManager();
	}
	else if (strFeatureName == "onRequestWebsite")
	{
		onRequestWebsite();
	}
	else if (strFeatureName == "onRequestOpenLogBasic")
	{
		onRequestOpenLogBasic();
	}
	else if (strFeatureName == "onRequestOpenLogExtended")
	{
		onRequestOpenLogExtended();
	}
	else if (strFeatureName == "onRequestOpenLogFolder")
	{
		onRequestOpenLogFolder();
	}
	else if (strFeatureName == "lst")
	{
		lst();
	}
	else if (strFeatureName == "onRequestSelectViaIDE")
	{
		onRequestSelectViaIDE();
	}
	else if (strFeatureName == "onRequestExportViaIPLFile")
	{
		onRequestExportViaIPLFile();
	}
	else if (strFeatureName == "onRequestRenameIMG")
	{
		onRequestRenameIMG();
	}
	else if (strFeatureName == "onRequestUpdate")
	{
		onRequestUpdate();
	}
	else if (strFeatureName == "onRequestAutoUpdate")
	{
		onRequestAutoUpdate();
	}
	else if (strFeatureName == "onRequestSaveIMGSignature")
	{
		onRequestSaveIMGSignature();
	}
	else if (strFeatureName == "onRequestVerifyIMGSignature")
	{
		onRequestVerifyIMGSignature();
	}
	else if (strFeatureName == "onRequestCompareIMG")
	{
		onRequestCompareIMG();
	}
	else if (strFeatureName == "onRequestConvertTXDToTextureFormat")
	{
		onRequestConvertTXDToTextureFormat(getIMGF()->getLastUsedValueManager()->getLastUsedValue_ConvertTXD_TextureFormat());
	}
	else if (strFeatureName == "onRequestClearLogs")
	{
		onRequestClearLogs(getIMGF()->getLastUsedValueManager()->getLastUsedValue_ClearLogs_AllTabs());
	}
	else if (strFeatureName == "onRequestValidateAllDFFInActiveTab")
	{
		onRequestValidateAllDFFInActiveTab();
	}
	else if (strFeatureName == "onRequestValidateAllTXDInActiveTab")
	{
		onRequestValidateAllTXDInActiveTab();
	}
	else if (strFeatureName == "onRequestCredits")
	{
		onRequestCredits();
	}
	else if (strFeatureName == "onRequestEntryViewer")
	{
		onRequestEntryViewer();
	}
	else if (strFeatureName == "onRequestRenamer")
	{
		onRequestRenamer();
	}
	else if (strFeatureName == "onRequestClearRecentlyOpenedList")
	{
		onRequestClearRecentlyOpenedList();
	}
	else if (strFeatureName == "onRequestBuildTXD")
	{
		onRequestBuildTXD();
	}
	else if (strFeatureName == "onRequestIMGVersionSettings")
	{
		onRequestIMGVersionSettings();
	}
	else if (strFeatureName == "onRequestConvertCOLtoCOLVersion")
	{
		onRequestConvertCOLtoCOLVersion(getIMGF()->getLastUsedValueManager()->getLastUsedValue_ConvertCOL_COLVersion());
	}
	else if (strFeatureName == "onRequestReportIssueOrIdea")
	{
		onRequestReportIssueOrIdea();
	}
	else if (strFeatureName == "onRequestSortViaColumn")
	{
		onRequestSortViaColumn(getIMGF()->getLastUsedValueManager()->getLastUsedValue_SortViaColumn_Column());
	}
	else if (strFeatureName == "onRequestCenterCOLCollisionMeshes")
	{
		onRequestCenterCOLCollisionMeshes();
	}
	else if (strFeatureName == "onRequestAlignCOLCollisionMeshesToDFFMesh")
	{
		onRequestAlignCOLCollisionMeshesToDFFMesh();
	}
	else if (strFeatureName == "onRequestConvertDFFFileToWDRFile")
	{
		onRequestConvertDFFFileToWDRFile();
	}
	else if (strFeatureName == "onRequestTXDOrganizer")
	{
		onRequestTXDOrganizer();
	}
	else if (strFeatureName == "onRequestConvertWTDFileToTXDFile")
	{
		onRequestConvertWTDFileToTXDFile();
	}
	else if (strFeatureName == "onRequestDATPathsMover")
	{
		onRequestDATPathsMover();
	}
	else if (strFeatureName == "onRequestExportViaDATFile")
	{
		onRequestExportViaDATFile();
	}
	else if (strFeatureName == "onRequestMapMoverAndIDShifter")
	{
		onRequestMapMoverAndIDShifter();
	}
	else if (strFeatureName == "onRequestDATModelList")
	{
		onRequestDATModelList();
	}
	else if (strFeatureName == "onRequestFindTXDMissingFromIMGFoundInIDE")
	{
		onRequestFindTXDMissingFromIMGFoundInIDE();
	}
	else if (strFeatureName == "onRequestFindCOLMissingFromCOLFoundInIDE")
	{
		onRequestFindCOLMissingFromCOLFoundInIDE();
	}
	else if (strFeatureName == "onRequestFindDFFMissingFromIMGFoundInIDE")
	{
		onRequestFindDFFMissingFromIMGFoundInIDE();
	}
	else if (strFeatureName == "onRequestCloneIMG")
	{
		onRequestCloneIMG();
	}
	else if (strFeatureName == "onRequestOpenIMGFolder")
	{
		onRequestOpenIMGFolder();
	}
	else if (strFeatureName == "onRequestRemoveOrphanTexturesFromModel")
	{
		onRequestRemoveOrphanTexturesFromModel();
	}
	else if (strFeatureName == "onRequestNewWindow")
	{
		onRequestNewWindow();
	}
	else if (strFeatureName == "onRequestOrphanDFFEntriesNotInCOL")
	{
		onRequestOrphanDFFEntriesNotInCOL();
	}
	else if (strFeatureName == "onRequestOrphanIDEEntriesNotInCOL")
	{
		onRequestOrphanIDEEntriesNotInCOL();
	}
	else if (strFeatureName == "onRequestOrphanCOLEntriesNotInIDE")
	{
		onRequestOrphanCOLEntriesNotInIDE();
	}
	else if (strFeatureName == "onRequestOrphanDFFEntriesNotInIDE")
	{
		onRequestOrphanDFFEntriesNotInIDE();
	}
	else if (strFeatureName == "onRequestOrphanIMGEntriesNotInIDE")
	{
		onRequestOrphanIMGEntriesNotInIDE();
	}
	else if (strFeatureName == "onRequestOrphanIPLEntriesNotInIDE")
	{
		//onRequestOrphanIPLEntriesNotInIDE();
	}
	else if (strFeatureName == "onRequestOrphanTXDEntriesNotInIDE")
	{
		onRequestOrphanTXDEntriesNotInIDE();
	}
	else if (strFeatureName == "onRequestOrphanIDEEntriesNotInIMG")
	{
		onRequestOrphanIDEEntriesNotInIMG();
	}
	else if (strFeatureName == "onRequestFindDFFMissingFromIDEFoundInIPL")
	{
		onRequestFindDFFMissingFromIDEFoundInIPL();
	}
	else
	{
	}
	*/
}

void		Tasks::onRequestLastFeatureUsed(void)
{
	string strPreviousTaskName = getIMGF()->getTaskManager()->getTaskName();
	if (strPreviousTaskName == "")
	{
		return;
	}

	onRequestFeatureByName(strPreviousTaskName);
}

uint32 uiSortPreviousColumnIndex; // todo - namespace
bool bSortDirectionIsAscending = true; // todo - namespace

int CALLBACK		Tasks::sortMainListView(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort)
{
	/*
	todo
	int nRetVal = 0;

	CListCtrl *pListCtrl = (CListCtrl*)getIMGF()->getDialog()->GetDlgItem(37);

	IMGEntry *pIMGEntry1 = (IMGEntry*)lParam1;
	IMGEntry *pIMGEntry2 = (IMGEntry*)lParam2;

	switch (lParamSort)
	{
	case 0: // ID
		break;

	case 1: // Type
		nRetVal = strcmp(String::toUpperCase(Path::getFileExtension(pIMGEntry1->getEntryName())).c_str(), String::toUpperCase(Path::getFileExtension(pIMGEntry2->getEntryName())).c_str());
		break;

	case 2: // Name
		nRetVal = strcmp(pIMGEntry1->getEntryName().c_str(), pIMGEntry2->getEntryName().c_str());
		break;

	case 3: // Offset
		nRetVal = pIMGEntry1->getEntryOffset() - pIMGEntry2->getEntryOffset();
		break;

	case 4: // Size
		nRetVal = pIMGEntry1->getEntrySize() - pIMGEntry2->getEntrySize();
		break;

	case 5: // RW Version / Resource Type
		break;

	default:
		break;
	}

	if (!bSortDirectionIsAscending)
	{
		nRetVal = -nRetVal;
	}

	return nRetVal;
	*/
	return 0;
}

void				Tasks::onRequestTXDOrganizer(void)
{
	/*
	todo
	getIMGF()->getTaskManager()->onStartTask("onRequestTXDOrganizer");
	if (getIMGF()->getEntryListTab() == nullptr)
	{
		getIMGF()->getTaskManager()->onTaskEnd("onRequestTXDOrganizer", true);
		return;
	}

	TXDOrganizerDialogData *pTXDOrganizerDialogData = getIMGF()->getPopupGUIManager()->showTXDOrganizerDialog();

	if (!pTXDOrganizerDialogData->m_bOrganize)
	{
		getIMGF()->getTaskManager()->onTaskEnd("onRequestTXDOrganizer", true);
		return;
	}

	vector<string> vecFilePaths;
	if (pTXDOrganizerDialogData->m_bIDEUpdate)
	{
		vecFilePaths = File::getFilePaths(pTXDOrganizerDialogData->m_strIDEUpdateFolderPath, true);
	}

	CListCtrl *pListControl = ((CListCtrl*)getIMGF()->getDialog()->GetDlgItem(37));
	setMaxProgress(pListControl->GetItemCount() + (pTXDOrganizerDialogData->m_bIDEUpdate ? vecFilePaths.size() : 0));

	uint32 uiTXDCount = 0;
	TXDFormat *pTXDFile = TXDManager::get()->createFormat();
	pTXDFile->setDeviceId(0);
	pTXDFile->setRWVersion(RWManager::get()->getVersionManager()->getEntryByVersionId(RW_3_6_0_3));

	IMGEntry *pIMGEntry = nullptr;
	uint32
		uiEntryCount = 0,
		uiDFFFileCount = 0;
	unordered_map<string, string> umapNewEntryNames;
	unordered_map<string, bool> umapTextureNamesUsedInTXD;

	for (uint32 i = 0, j = pListControl->GetItemCount(); i < j; i++)
	{
		pIMGEntry = (IMGEntry*)pListControl->GetItemData(i);

		if (!pIMGEntry->isModelFile())
		{
			increaseProgress();
			continue;
		}

		DFFFormat *pDFFFile = DFFManager::get()->unserializeMemory(pIMGEntry->getEntryData());
		if (pDFFFile->doesHaveError())
		{
			pDFFFile->unload();
			delete pDFFFile;
			increaseProgress();
			continue;
		}

		vector<string> vecDFFTextureNames = pDFFFile->getTextureNames();
		for (string strDFFTextureName : vecDFFTextureNames)
		{
			// check if texture is already in TXD
			if (umapTextureNamesUsedInTXD.find(String::toUpperCase(strDFFTextureName)) != umapTextureNamesUsedInTXD.end())
			{
				continue;
			}

			// check if texture file exists
			string strTextureImagePath = File::findImageFile(strDFFTextureName, pTXDOrganizerDialogData->m_strTextureImportFolderPath);
			if (strTextureImagePath != "")
			{
				// add texture to TXD
				umapTextureNamesUsedInTXD[String::toUpperCase(strDFFTextureName)] = true;
				RWSection_TextureNative *pTexture = pTXDFile->addTextureViaFile(strTextureImagePath, strDFFTextureName, strDFFTextureName + "a");

				if (pTexture != nullptr)
				{
					vector<string> vecMipmapsRemoved;
					//Debugger::log("pTXDOrganizerDialogData->m_pTextureFormat->getId(): " + String::toString(pTXDOrganizerDialogData->m_pTextureFormat->getId()));
					pTexture->convertToRasterDataFormat(pTXDOrganizerDialogData->m_pRasterDataFormat->getRasterDataFormatId(), vecMipmapsRemoved);
				}
			}
		}

		string strNextTXDFileName = pTXDOrganizerDialogData->m_strTXDNamePrefix + ((uiTXDCount + 1) < 10 ? "0" : "") + String::toString(uiTXDCount + 1) + ".txd";
		string strDFFFileNameWithoutExtension = Path::removeFileExtension(pIMGEntry->getEntryName());
		string strTXDFileNameWithoutExtension = Path::removeFileExtension(strNextTXDFileName);
		umapNewEntryNames[strDFFFileNameWithoutExtension] = strTXDFileNameWithoutExtension;

		uiDFFFileCount++;
		if (uiDFFFileCount == pTXDOrganizerDialogData->m_uiEveryNDFFFiles)
		{
			uiTXDCount++;
			string strTXDFileName = pTXDOrganizerDialogData->m_strTXDNamePrefix + (uiTXDCount < 10 ? "0" : "") + String::toString(uiTXDCount) + ".txd";
			pTXDFile->storeViaFile(pTXDOrganizerDialogData->m_strOutputFolderPath + strTXDFileName);
			pTXDFile->unload();
			delete pTXDFile;
			pTXDFile = nullptr;
			
			uiDFFFileCount = 0;
			umapTextureNamesUsedInTXD.clear();
			pTXDFile = TXDManager::get()->createFormat();
			pTXDFile->setDeviceId(0);
			pTXDFile->setRWVersion(RWManager::get()->getVersionManager()->getEntryByVersionId(RW_3_6_0_3));
		}
		
		pDFFFile->unload();
		delete pDFFFile;
		
		increaseProgress();
		uiEntryCount++;
	}

	if (uiDFFFileCount > 0)
	{
		uiTXDCount++;
		string strTXDFileName = pTXDOrganizerDialogData->m_strTXDNamePrefix + (uiTXDCount < 10 ? "0" : "") + String::toString(uiTXDCount) + ".txd";
		pTXDFile->storeViaFile(pTXDOrganizerDialogData->m_strOutputFolderPath + strTXDFileName);
		pTXDFile->unload();
		delete pTXDFile;
		pTXDFile = nullptr;
	}
	
	if(pTXDFile != nullptr)
	{
		pTXDFile->unload();
		delete pTXDFile;
		pTXDFile = nullptr;
	}

	// update IDE files
	if (pTXDOrganizerDialogData->m_bIDEUpdate)
	{
		for (string strFilePath : vecFilePaths)
		{
			if (String::toUpperCase(Path::getFileExtension(strFilePath)) != "IDE")
			{
				continue;
			}

			IDEFormat *pIDEFile = IDEManager::get()->unserializeFile(strFilePath);

			if (pIDEFile->doesHaveError())
			{
				increaseProgress();
				continue;
			}

			for (auto it : umapNewEntryNames)
			{
				string strDFFFileName = it.first;
				string strTXDFileName = it.second;
				vector<IDEEntry*> vecIDEEntries = pIDEFile->getEntriesByModelName(strDFFFileName);

				for (IDEEntry *pIDEEntry : vecIDEEntries)
				{
					switch (pIDEEntry->getSectionType())
					{
						// todo - make it work with all IDE sections
					case IDE_SECTION_OBJS:
					{
						IDEEntry_OBJS *pIDEEntry_OBJS = (IDEEntry_OBJS*) pIDEEntry;
						pIDEEntry_OBJS->setTXDName(strTXDFileName);
						break;
					}
					case IDE_SECTION_TOBJ:
					{
						IDEEntry_TOBJ *pIDEEntry_TOBJ = (IDEEntry_TOBJ*)pIDEEntry;
						pIDEEntry_TOBJ->setTXDName(strTXDFileName);
						break;
					}
					}
				}
			}

			pIDEFile->serializeViaFile();

			pIDEFile->unload();
			delete pIDEFile;
			increaseProgress();
		}
	}

	// log
	// todo - getIMGF()->getEntryListTab()->log(LocalizationManager::get()->getTranslatedFormattedText("Log_TXDOrganizer", uiEntryCount, uiTXDCount));

	// clean up
	delete pTXDOrganizerDialogData;
	getIMGF()->getTaskManager()->onTaskEnd("onRequestTXDOrganizer");
	*/
}

bool			sortDATFiles(DATPathFormat *pDATFile_Paths1, DATPathFormat *pDATFile_Paths2) // todo - namespace
{
	return pDATFile_Paths1->m_uiFileIndex < pDATFile_Paths2->m_uiFileIndex;
}
bool			sortDATPathsEntries(DATEntry_Paths_General_PathNode &pathNode1, DATEntry_Paths_General_PathNode& pathNode2) // todo - namespace
{
	if (pathNode1.m_bIsVehiclePathNode && pathNode2.m_bIsVehiclePathNode)
	{
		return false;
	}
	if (pathNode1.m_bIsVehiclePathNode)
	{
		return true;
	}
	return false;
}
void			Tasks::onRequestDATPathsMover(void)
{
	/*
	getIMGF()->getTaskManager()->onStartTask("onRequestDATPathsMover");
	
	getIMGF()->getTaskManager()->onPauseTask();
	DATPathsMoverDialogData *pDATPathsMoverDialogData = getIMGF()->getPopupGUIManager()->showDATPathsMoverDialogData();
	getIMGF()->getTaskManager()->onResumeTask();

	if (!pDATPathsMoverDialogData->m_bMove)
	{
		getIMGF()->getTaskManager()->onTaskEnd("onRequestDATPathsMover", true);
		return;
	}

	vector<string>
		vecFileNames = File::getFileNamesByExtension(pDATPathsMoverDialogData->m_strInputFolderPath, "DAT");
	vector<DATPathFormat*>
		vecDATInputFiles,
		vecDATOutputFiles;
	for (auto strFileName : vecFileNames)
	{
		uint32 uiAreaId = String::toNumber(Path::removeFileExtension(strFileName).substr(5)); // example filename: nodes0.dat, nodes1.dat, nodes63.dat

		DATPathFormat *pDATFile = DATPathManager::get()->unserializeMemory(File::getFileContent(pDATPathsMoverDialogData->m_strInputFolderPath + strFileName, true)//////, uiAreaId///////);
		if(!pDATFile->doesHaveError())
		{
			vecDATInputFiles.push_back(pDATFile);
		}
	}
	for (uint32 i = 0, j = DATPathManager::getTileCount(pDATPathsMoverDialogData->m_vecOutputMapRangeMin, pDATPathsMoverDialogData->m_vecOutputMapRangeMax, pDATPathsMoverDialogData->m_vecOutputTileSize); i < j; i++)
	{
		DATPathFormat *pDATFile = new DATPathFormat;
		pDATFile->setPathsFormat(DAT_PATH_FASTMAN92);
		pDATFile->m_uiFileIndex = i;
		vecDATOutputFiles.push_back(pDATFile);
	}
	
	std::sort(vecDATInputFiles.begin(), vecDATInputFiles.end(), sortDATFiles);

	setMaxProgress((vecDATInputFiles.size() * 2) + (vecDATOutputFiles.size() * 4));

	for (auto pDATFile : vecDATInputFiles)
	{
		pDATFile->applyOffsetToPositions(pDATPathsMoverDialogData->m_vecPositionOffset);

		increaseProgress();
	}

	// process
	//unordered_map<DATEntry_Paths_General_PathNode&, CNodeAddress> umapNewAddresses_PathNode;
	for (auto pDATFile : vecDATInputFiles)
	{
		uint32 uiAreaId_SA = pDATFile->m_uiFileIndex;

		for (auto& pathNode : pDATFile->m_vecPathNodes)
		{
			Vec2f vecPathNodePosition = { (float32)pathNode.m_vecPosition.x / 8.0f, (float32)pathNode.m_vecPosition.y / 8.0f };
			uint32 uiNewAreaIdForPathNode = DATPathManager::getAreaIdFromPosition(vecPathNodePosition, pDATPathsMoverDialogData->m_vecOutputMapRangeMin, pDATPathsMoverDialogData->m_vecOutputMapRangeMax, pDATPathsMoverDialogData->m_vecOutputTileSize);

			uint32 uiFirstLinkIndex = pathNode.m_wConnectedNodesStartId;
			uint32 uiLinkCountForNode = pathNode.m_uiFlags & 0xF;
			pathNode.m_wConnectedNodesStartId = (uint16)vecDATOutputFiles[uiNewAreaIdForPathNode]->m_vecLinks.size();

			DATEntry_Paths_General_Link link;
			for (uint32 i = 0; i < uiLinkCountForNode; i++)
			{
				link = pDATFile->m_vecLinks[uiFirstLinkIndex + i];
				vecDATOutputFiles[uiNewAreaIdForPathNode]->addLink(link);
			}
			//uint32 uiNewPathNodeId = vecDATOutputFiles[uiNewAreaIdForPathNode].size();
			vecDATOutputFiles[uiNewAreaIdForPathNode]->addPathNode(pathNode);
			
			//umapNewAddresses_PathNode[vecDATOutputFiles[uiNewAreaIdForPathNode]->m_vecPathNodes[uiNewPathNodeId]] = { uiNewAreaIdForPathNode, uiNewPathNodeId };
		}

		uint32 i = 0;
		for (auto& naviNode : pDATFile->m_vecNaviNodes)
		{
			Vec2f vecNaviNodePosition = { (float32)naviNode.m_iPosition[0] / 8.0f, (float32)naviNode.m_iPosition[1] / 8.0f };
			uint32 uiNewAreaIdForNaviNode = DATPathManager::getAreaIdFromPosition(vecNaviNodePosition, pDATPathsMoverDialogData->m_vecOutputMapRangeMin, pDATPathsMoverDialogData->m_vecOutputMapRangeMax, pDATPathsMoverDialogData->m_vecOutputTileSize);

			vecDATOutputFiles[uiNewAreaIdForNaviNode]->addNaviNode(naviNode);
			i++;
		}

		increaseProgress();
	}

	for (auto pDATFile : vecDATOutputFiles)
	{
		std::sort(pDATFile->m_vecPathNodes.begin(), pDATFile->m_vecPathNodes.end(), sortDATPathsEntries);

		increaseProgress();
	}

	for (auto pDATFile : vecDATOutputFiles)
	{
		for (auto& naviNode : pDATFile->m_vecNaviNodes)
		{
			// this code is in a separate loop because the new position may not have been applied yet.
			
			auto& targetPathNode_Input = vecDATInputFiles[naviNode.m_usTargetNode_AreaId]->m_vecPathNodes[naviNode.m_usTargetNode_NodeId]; // the position has already been updated for this target node.

			uint32 uiAreaId_Out;
			uint32 uiNodeId_Out;
			bool bFound = DATPathManager::findPathNode(vecDATOutputFiles, targetPathNode_Input, uiAreaId_Out, uiNodeId_Out);
			if (bFound)
			{
				naviNode.m_usTargetNode_AreaId = (uint16)uiAreaId_Out;
				naviNode.m_usTargetNode_NodeId = (uint16)uiNodeId_Out;
			}
		}

		increaseProgress();
	}
	
	for (auto pDATFile : vecDATOutputFiles)
	{
		for (auto& link : pDATFile->m_vecLinks)
		{
			auto& pathNode_Input = vecDATInputFiles[link.m_usAreaId]->m_vecPathNodes[link.m_usNodeId];

			uint32 uiAreaId_Out;
			uint32 uiNodeId_Out;
			bool bFound = DATPathManager::findPathNode(vecDATOutputFiles, pathNode_Input, uiAreaId_Out, uiNodeId_Out);
			if (bFound)
			{
				link.m_usAreaId = (uint16)uiAreaId_Out;
				link.m_usNodeId = (uint16)uiNodeId_Out;
			}



			if (link.m_usNaviAreaId == 0 && link.m_usNaviNodeId == 0)
			{
				// do nothing
			}
			else
			{
				auto& naviNode_Input2 = vecDATInputFiles[link.m_usNaviAreaId]->m_vecNaviNodes[link.m_usNaviNodeId];

				uint32 uiAreaId_Out2;
				uint32 uiNodeId_Out2;
				bool bFound2 = DATPathManager::findNaviNode(vecDATOutputFiles, naviNode_Input2, uiAreaId_Out2, uiNodeId_Out2);
				if (bFound2)
				{
					link.m_usNaviAreaId = (uint16)uiAreaId_Out2;
					link.m_usNaviNodeId = (uint16)uiNodeId_Out2;
				}
			}
		}

		increaseProgress();
	}

	// update target nodes of navi nodes to always be the "lower" node
	////////////////////////////////
	for (auto pDATFile : vecDATOutputFiles)
	{
		uint32 uiNaviNodeAreaId = pDATFile->m_uiFileIndex;
		uint32 uiNaviNodeNodeId = 0;
		for (auto& naviNode : pDATFile->m_vecNaviNodes)
		{
			DATEntry_Paths_General_PathNode pathNode1 = vecDATOutputFiles[naviNode.m_usTargetNode_AreaId]->m_vecPathNodes[naviNode.m_usTargetNode_NodeId];
			uint32 uiLinkId_Out;
			vector<DATEntry_Paths_General_PathNode> vecTargetPathNodes = DATManager::getTargetPathNodesForNaviNode(vecDATOutputFiles, naviNode, uiNaviNodeAreaId, uiNaviNodeNodeId, uiLinkId_Out);
			vecTargetPathNodes.push_back(pathNode1);
			//if (vecTargetPathNodes.size() != 2)
			//{
			//	Debugger::log("vecTargetPathNodes.size(): " + String::toString(vecTargetPathNodes.size()));
			//}

			//DATEntry_Paths_General_PathNode lowestTargetPathNode = DATManager::getLowestPathNode(vecTargetPathNodes);
			//naviNode.m_usTargetNode_AreaId = lowestTargetPathNode.m_wAreaId;
			//naviNode.m_usTargetNode_NodeId = lowestTargetPathNode.m_wNodeId;

			DATEntry_Paths_General_PathNode lowerTargetPathNode = DATManager::getLowestPathNode(vecTargetPathNodes);
			DATEntry_Paths_General_PathNode higherTargetPathNode;
			if (vecTargetPathNodes[0].m_vecPosition.x == lowerTargetPathNode.m_vecPosition.x
			 && vecTargetPathNodes[0].m_vecPosition.y == lowerTargetPathNode.m_vecPosition.y
			 && vecTargetPathNodes[0].m_vecPosition.z == lowerTargetPathNode.m_vecPosition.z
			 && vecTargetPathNodes[0].m_ucPathWidth == lowerTargetPathNode.m_ucPathWidth)
			{
				higherTargetPathNode = vecTargetPathNodes[1];
			}
			else
			{
				higherTargetPathNode = vecTargetPathNodes[0];
			}

			auto& link = vecDATOutputFiles[vecTargetPathNodes[0].m_wAreaId]->m_vecLinks[uiLinkId_Out];
			link.m_usNaviAreaId = higherTargetPathNode.m_wAreaId;
			link.m_usNaviNodeId = higherTargetPathNode.m_wNodeId;
			naviNode.m_usTargetNode_AreaId = lowerTargetPathNode.m_wAreaId;
			naviNode.m_usTargetNode_NodeId = lowerTargetPathNode.m_wNodeId;

			//
			DATEntry_Paths_General_PathNode previousPathNode = vecTargetPathNodes[0];
			naviNode.m_usTargetNode_AreaId = previousPathNode.m_wAreaId;
			naviNode.m_usTargetNode_NodeId = previousPathNode.m_wNodeId;
			naviNode.m_ucDirection[0] = -((int8)naviNode.m_ucDirection[0]);
			naviNode.m_ucDirection[1] = -((int8)naviNode.m_ucDirection[1]);
			
			uint32 uiLeftLaneCount = naviNode.m_uiFlags & 1792;
			uint32 uiRightLaneCount = naviNode.m_uiFlags & 14336;
			
			uint32 uiNewLeftLaneCount = uiRightLaneCount;
			uint32 uiNewRightLaneCount = uiLeftLaneCount;

			naviNode.m_uiFlags &= 0xFFFFF8FF;
			naviNode.m_uiFlags |= uiNewLeftLaneCount;

			naviNode.m_uiFlags &= 0xFFFFC7FF;
			naviNode.m_uiFlags |= uiNewRightLaneCount;
			//

			uiNaviNodeNodeId++;
		}
	}
	////////////////////////////////////////

	// store output DAT files
	uint32 i = 0;
	for (auto pDATFile : vecDATOutputFiles)
	{
		File::storeFile(pDATPathsMoverDialogData->m_strOutputFolderPath + "nodes" + String::toString(i) + ".dat", pDATFile->serializeViaMemory(), false, true);
		increaseProgress();
		i++;
	}

	// clean up
	for (auto pDATFile : vecDATInputFiles)
	{
		pDATFile->unload();
		delete pDATFile;
	}
	for (auto pDATFile : vecDATOutputFiles)
	{
		pDATFile->unload();
		delete pDATFile;
	}
	delete pDATPathsMoverDialogData;

	getIMGF()->getTaskManager()->onTaskEnd("onRequestDATPathsMover");
	*/
}

void						Tasks::onRequestMapMoverAndIDShifter(void)
{
	/*
	getIMGF()->getTaskManager()->onStartTask("onRequestMapMoverAndIDShifter");

	CMapMoverAndIDShifterDialogData *pMapMoverAndIDShifterDialogData = getIMGF()->getPopupGUIManager()->showMapMoverAndIDShifterDialog();
	if (!pMapMoverAndIDShifterDialogData->m_bGo)
	{
		getIMGF()->getTaskManager()->onTaskEnd("onRequestMapMoverAndIDShifter", true);
		return;
	}

	unordered_map<EPlatformedGame, vector<string>>
		umapIgnoreDefaultObjectFileNamesVector;
	string
		strDefaultModelNamesFolder = DataPath::getDataPath() + "DefaultFiles/ModelNames/",
		strModelNamesPath_PC_GTA_III = strDefaultModelNamesFolder + "ModelNames-PC-GTA-III.txt",
		strModelNamesPath_PC_GTA_VC = strDefaultModelNamesFolder + "ModelNames-PC-GTA-VC.txt",
		strModelNamesPath_PC_GTA_SA = strDefaultModelNamesFolder + "ModelNames-PC-GTA-SA.txt"
	;
	if (File::doesFileExist(strModelNamesPath_PC_GTA_III))
	{
		umapIgnoreDefaultObjectFileNamesVector[PC_GTA_III] = String::split(File::getFileContent(strModelNamesPath_PC_GTA_III), ", ");
	}
	if (File::doesFileExist(strModelNamesPath_PC_GTA_VC))
	{
		umapIgnoreDefaultObjectFileNamesVector[PC_GTA_VC] = String::split(File::getFileContent(strModelNamesPath_PC_GTA_VC), ", ");
	}
	if (File::doesFileExist(strModelNamesPath_PC_GTA_SA))
	{
		umapIgnoreDefaultObjectFileNamesVector[PC_GTA_SA] = String::split(File::getFileContent(strModelNamesPath_PC_GTA_SA), ", ");
	}

	unordered_map<string, bool> umapIgnoreDefaultObjectFileNames;
	for (auto it : umapIgnoreDefaultObjectFileNamesVector)
	{
		for (string& strFileName : it.second)
		{
			umapIgnoreDefaultObjectFileNames[strFileName] = true;
		}
	}
	umapIgnoreDefaultObjectFileNamesVector.clear();

	DATLoaderFormat *pDATFile = DATLoaderManager::get()->unserializeFile(pMapMoverAndIDShifterDialogData->m_strDATFilePath);
	if(pDATFile->doesHaveError())
	{
		getIMGF()->getTaskManager()->onTaskEnd("onRequestMapMoverAndIDShifter", true);
		return;
	}
	vector<string>
		vecRelativeIDEPaths = pDATFile->getRelativeIDEPaths(),
		vecRelativeIPLPaths = pDATFile->getRelativeIPLPaths();
	pDATFile->unload();
	delete pDATFile;

	vector<string>
		vecIDEPaths,
		vecIPLPaths;
	uint32 i;
	vecIDEPaths.resize(vecRelativeIDEPaths.size());
	vecIPLPaths.resize(vecRelativeIPLPaths.size());
	i = 0;
	for (string& strRelativeIDEPath : vecRelativeIDEPaths)
	{
		vecIDEPaths[i] = pMapMoverAndIDShifterDialogData->m_strGameFolderPath + strRelativeIDEPath;
		i++;
	}
	i = 0;
	for (string& strRelativeIPLPath : vecRelativeIPLPaths)
	{
		vecIPLPaths[i] = pMapMoverAndIDShifterDialogData->m_strGameFolderPath + strRelativeIPLPath;
		i++;
	}
	vecRelativeIDEPaths.clear();
	vecRelativeIPLPaths.clear();
	if (pMapMoverAndIDShifterDialogData->m_bUpdateIDEInFolder)
	{
		vecIDEPaths = StdVector::combineVectors(vecIDEPaths, File::getFilePaths(pMapMoverAndIDShifterDialogData->m_strUpdateIDEInFolderPath, true, false, "IDE"));
	}
	if (pMapMoverAndIDShifterDialogData->m_bUpdateIPLInFolder)
	{
		vecIPLPaths = StdVector::combineVectors(vecIPLPaths, File::getFilePaths(pMapMoverAndIDShifterDialogData->m_strUpdateIPLInFolderPath, true, false, "IPL"));
	}

	setMaxProgress(vecIDEPaths.size() + vecIPLPaths.size());

	uint32 uiIDEEntryNewObjectId = pMapMoverAndIDShifterDialogData->m_uiIDStart;
	unordered_map<uint32, uint32> umapNewObjectIds;
	uint32
		uiIPLCount_Text = 0,
		uiIPLCount_Binary = 0;
	if (pMapMoverAndIDShifterDialogData->m_bShiftIds)
	{
		for (string& strIDEPath : vecIDEPaths)
		{
			bool bIgnoreShifter = pMapMoverAndIDShifterDialogData->m_umapShifterIgnoreFilenames.find(String::toUpperCase(Path::getFileName(strIDEPath))) != pMapMoverAndIDShifterDialogData->m_umapShifterIgnoreFilenames.end();
			if (bIgnoreShifter)
			{
				// ignore file for ID shifter
				continue;
			}
			IDEFormat *pIDEFile = IDEManager::get()->unserializeFile(strIDEPath);
			if(!pIDEFile->doesHaveError())
			{
				for (auto it : pIDEFile->getSectionEntries())
				{
					for (IDEEntry *pIDEEntry : it.second)
					{
						if (pIDEEntry->getEntryType() == SECTION_LINES_ENTRY_DATA)
						{
							IDEEntry_Data *pIDEEntry_Data = (IDEEntry_Data*)pIDEEntry;
							umapNewObjectIds[pIDEEntry_Data->getObjectId()] = uiIDEEntryNewObjectId;
							//pIDEEntry_Data->setObjectId(uiIDEEntryNewObjectId); // todo - must be uncommented
							uiIDEEntryNewObjectId++;
						}
					}
				}

				pIDEFile->setFilePath(pMapMoverAndIDShifterDialogData->m_strOutputFolderPath + Path::getFileName(strIDEPath));
				pIDEFile->serializeViaFile();
			}
			pIDEFile->unload();
			delete pIDEFile;

			increaseProgress();
		}
	}

	for (string& strIPLPath : vecIPLPaths)
	{
		bool
			bIgnoreShifter = !pMapMoverAndIDShifterDialogData->m_bShiftIds,
			bIgnoreMover = !pMapMoverAndIDShifterDialogData->m_bMovePosition;
		if (!bIgnoreShifter)
		{
			bIgnoreShifter = pMapMoverAndIDShifterDialogData->m_umapShifterIgnoreFilenames.find(String::toUpperCase(Path::getFileName(strIPLPath))) != pMapMoverAndIDShifterDialogData->m_umapShifterIgnoreFilenames.end();
		}
		if (!bIgnoreMover)
		{
			bIgnoreMover = pMapMoverAndIDShifterDialogData->m_umapMoverIgnoreFilenames.find(String::toUpperCase(Path::getFileName(strIPLPath))) != pMapMoverAndIDShifterDialogData->m_umapMoverIgnoreFilenames.end();
		}

		IPLFormat *pIPLFile = IPLManager::get()->unserializeFile(strIPLPath);
		if(!pIPLFile->doesHaveError())
		{
			if (pIPLFile->isBinary())
			{
				uiIPLCount_Binary++;
			}
			else
			{
				uiIPLCount_Text++;
			}
			for (auto pIPLEntry : pIPLFile->getEntriesBySection<IPLEntry_INST>(IPL_SECTION_INST))
			{
				if (umapNewObjectIds.find(pIPLEntry->getObjectId()) != umapNewObjectIds.end())
				{
					if (!bIgnoreShifter)
					{
						pIPLEntry->setObjectId(umapNewObjectIds[pIPLEntry->getObjectId()]);
					}
				}
				if (!bIgnoreMover)
				{
					pIPLEntry->getPosition().x += pMapMoverAndIDShifterDialogData->m_vecPositionOffset.x;
					pIPLEntry->getPosition().y += pMapMoverAndIDShifterDialogData->m_vecPositionOffset.y;
					pIPLEntry->getPosition().z += pMapMoverAndIDShifterDialogData->m_vecPositionOffset.z;
				}
			}
			if (!bIgnoreMover)
			{
				for (auto pIPLEntry : pIPLFile->getEntriesBySection<IPLEntry_AUZO>(IPL_SECTION_AUZO))
				{
					switch (pIPLEntry->getFormatType())
					{
					case 0:
						pIPLEntry->getLowerLeftPosition().x += pMapMoverAndIDShifterDialogData->m_vecPositionOffset.x;
						pIPLEntry->getLowerLeftPosition().y += pMapMoverAndIDShifterDialogData->m_vecPositionOffset.y;
						pIPLEntry->getLowerLeftPosition().z += pMapMoverAndIDShifterDialogData->m_vecPositionOffset.z;
						pIPLEntry->getUpperRightPosition().x += pMapMoverAndIDShifterDialogData->m_vecPositionOffset.x;
						pIPLEntry->getUpperRightPosition().y += pMapMoverAndIDShifterDialogData->m_vecPositionOffset.y;
						pIPLEntry->getUpperRightPosition().z += pMapMoverAndIDShifterDialogData->m_vecPositionOffset.z;
						break;
					case 1:
						pIPLEntry->getCenterPosition().x += pMapMoverAndIDShifterDialogData->m_vecPositionOffset.x;
						pIPLEntry->getCenterPosition().y += pMapMoverAndIDShifterDialogData->m_vecPositionOffset.y;
						pIPLEntry->getCenterPosition().z += pMapMoverAndIDShifterDialogData->m_vecPositionOffset.z;
						break;
					}
				}
				for (auto pIPLEntry : pIPLFile->getEntriesBySection<IPLEntry_CARS>(IPL_SECTION_CARS))
				{
					pIPLEntry->getPosition().x += pMapMoverAndIDShifterDialogData->m_vecPositionOffset.x;
					pIPLEntry->getPosition().y += pMapMoverAndIDShifterDialogData->m_vecPositionOffset.y;
					pIPLEntry->getPosition().z += pMapMoverAndIDShifterDialogData->m_vecPositionOffset.z;
				}
				for (auto pIPLEntry : pIPLFile->getEntriesBySection<IPLEntry_CULL>(IPL_SECTION_CULL))
				{
					switch (pIPLEntry->getFormatType())
					{
					case 1:
						pIPLEntry->getLowerLeftPosition().x += pMapMoverAndIDShifterDialogData->m_vecPositionOffset.x;
						pIPLEntry->getLowerLeftPosition().y += pMapMoverAndIDShifterDialogData->m_vecPositionOffset.y;
						pIPLEntry->getLowerLeftPosition().z += pMapMoverAndIDShifterDialogData->m_vecPositionOffset.z;
						pIPLEntry->getUpperRightPosition().x += pMapMoverAndIDShifterDialogData->m_vecPositionOffset.x;
						pIPLEntry->getUpperRightPosition().y += pMapMoverAndIDShifterDialogData->m_vecPositionOffset.y;
						pIPLEntry->getUpperRightPosition().z += pMapMoverAndIDShifterDialogData->m_vecPositionOffset.z;
						// no break intended
					case 0:
					case 2:
						pIPLEntry->getCenterPosition().x += pMapMoverAndIDShifterDialogData->m_vecPositionOffset.x;
						pIPLEntry->getCenterPosition().y += pMapMoverAndIDShifterDialogData->m_vecPositionOffset.y;
						pIPLEntry->getCenterPosition().z += pMapMoverAndIDShifterDialogData->m_vecPositionOffset.z;
						break;
					}
				}
				for (auto pIPLEntry : pIPLFile->getEntriesBySection<IPLEntry_ENEX>(IPL_SECTION_ENEX))
				{
					pIPLEntry->getEntrancePosition().x += pMapMoverAndIDShifterDialogData->m_vecPositionOffset.x;
					pIPLEntry->getEntrancePosition().y += pMapMoverAndIDShifterDialogData->m_vecPositionOffset.y;
					pIPLEntry->getEntrancePosition().z += pMapMoverAndIDShifterDialogData->m_vecPositionOffset.z;
					pIPLEntry->getExitPosition().x += pMapMoverAndIDShifterDialogData->m_vecPositionOffset.x;
					pIPLEntry->getExitPosition().y += pMapMoverAndIDShifterDialogData->m_vecPositionOffset.y;
					pIPLEntry->getExitPosition().z += pMapMoverAndIDShifterDialogData->m_vecPositionOffset.z;
				}
				for (auto pIPLEntry : pIPLFile->getEntriesBySection<IPLEntry_GRGE>(IPL_SECTION_GRGE))
				{
					pIPLEntry->getPosition().x += pMapMoverAndIDShifterDialogData->m_vecPositionOffset.x;
					pIPLEntry->getPosition().y += pMapMoverAndIDShifterDialogData->m_vecPositionOffset.y;
					pIPLEntry->getPosition().z += pMapMoverAndIDShifterDialogData->m_vecPositionOffset.z;
					pIPLEntry->getLine().x += pMapMoverAndIDShifterDialogData->m_vecPositionOffset.x;
					pIPLEntry->getLine().y += pMapMoverAndIDShifterDialogData->m_vecPositionOffset.y;
					pIPLEntry->getCubePosition().x += pMapMoverAndIDShifterDialogData->m_vecPositionOffset.x;
					pIPLEntry->getCubePosition().y += pMapMoverAndIDShifterDialogData->m_vecPositionOffset.y;
					pIPLEntry->getCubePosition().z += pMapMoverAndIDShifterDialogData->m_vecPositionOffset.z;
				}
				for (auto pIPLEntry : pIPLFile->getEntriesBySection<IPLEntry_JUMP>(IPL_SECTION_JUMP))
				{
					pIPLEntry->getStartLowerPosition().x += pMapMoverAndIDShifterDialogData->m_vecPositionOffset.x;
					pIPLEntry->getStartLowerPosition().y += pMapMoverAndIDShifterDialogData->m_vecPositionOffset.y;
					pIPLEntry->getStartLowerPosition().z += pMapMoverAndIDShifterDialogData->m_vecPositionOffset.z;
					pIPLEntry->getStartUpperPosition().x += pMapMoverAndIDShifterDialogData->m_vecPositionOffset.x;
					pIPLEntry->getStartUpperPosition().y += pMapMoverAndIDShifterDialogData->m_vecPositionOffset.y;
					pIPLEntry->getStartUpperPosition().z += pMapMoverAndIDShifterDialogData->m_vecPositionOffset.z;
					pIPLEntry->getTargetLowerPosition().x += pMapMoverAndIDShifterDialogData->m_vecPositionOffset.x;
					pIPLEntry->getTargetLowerPosition().y += pMapMoverAndIDShifterDialogData->m_vecPositionOffset.y;
					pIPLEntry->getTargetLowerPosition().z += pMapMoverAndIDShifterDialogData->m_vecPositionOffset.z;
					pIPLEntry->getTargetUpperPosition().x += pMapMoverAndIDShifterDialogData->m_vecPositionOffset.x;
					pIPLEntry->getTargetUpperPosition().y += pMapMoverAndIDShifterDialogData->m_vecPositionOffset.y;
					pIPLEntry->getTargetUpperPosition().z += pMapMoverAndIDShifterDialogData->m_vecPositionOffset.z;
					pIPLEntry->getCameraPosition().x += pMapMoverAndIDShifterDialogData->m_vecPositionOffset.x;
					pIPLEntry->getCameraPosition().y += pMapMoverAndIDShifterDialogData->m_vecPositionOffset.y;
					pIPLEntry->getCameraPosition().z += pMapMoverAndIDShifterDialogData->m_vecPositionOffset.z;
				}
				for (auto pIPLEntry : pIPLFile->getEntriesBySection<IPLEntry_OCCL>(IPL_SECTION_OCCL))
				{
					pIPLEntry->getMidPosition().x += pMapMoverAndIDShifterDialogData->m_vecPositionOffset.x;
					pIPLEntry->getMidPosition().y += pMapMoverAndIDShifterDialogData->m_vecPositionOffset.y;
				}
				for (auto pIPLEntry : pIPLFile->getEntriesBySection<IPLEntry_PICK>(IPL_SECTION_PICK))
				{
					pIPLEntry->getPosition().x += pMapMoverAndIDShifterDialogData->m_vecPositionOffset.x;
					pIPLEntry->getPosition().y += pMapMoverAndIDShifterDialogData->m_vecPositionOffset.y;
					pIPLEntry->getPosition().z += pMapMoverAndIDShifterDialogData->m_vecPositionOffset.z;
				}
				for (auto pIPLEntry : pIPLFile->getEntriesBySection<IPLEntry_ZONE>(IPL_SECTION_ZONE))
				{
					pIPLEntry->getBottomLeftPosition().x += pMapMoverAndIDShifterDialogData->m_vecPositionOffset.x;
					pIPLEntry->getBottomLeftPosition().y += pMapMoverAndIDShifterDialogData->m_vecPositionOffset.y;
					pIPLEntry->getBottomLeftPosition().z += pMapMoverAndIDShifterDialogData->m_vecPositionOffset.z;
					pIPLEntry->getTopRightPosition().x += pMapMoverAndIDShifterDialogData->m_vecPositionOffset.x;
					pIPLEntry->getTopRightPosition().y += pMapMoverAndIDShifterDialogData->m_vecPositionOffset.y;
					pIPLEntry->getTopRightPosition().z += pMapMoverAndIDShifterDialogData->m_vecPositionOffset.z;
				}
			}
			
			pIPLFile->setFilePath(pMapMoverAndIDShifterDialogData->m_strOutputFolderPath + Path::getFileName(strIPLPath));
			pIPLFile->serializeViaFile();
		}
		
		pIPLFile->unload();
		delete pIPLFile;

		increaseProgress();
	}

	if (getIMGF()->getEntryListTab() == nullptr)
	{
		getIMGF()->getIMGEditor()->logWithNoTabsOpen("Moved and ID shifted " + String::toString(vecIDEPaths.size()) + " IDE files and " + String::toString(vecIPLPaths.size()) + " IPL files (" + String::toString(uiIPLCount_Text) + " text, " + String::toString(uiIPLCount_Binary) + " binary) in " + Path::getFileName(pMapMoverAndIDShifterDialogData->m_strDATFilePath));
	}
	else
	{
		// todo - getIMGF()->getEntryListTab()->log("Moved and ID shifted " + String::toString(vecIDEPaths.size()) + " IDE files and " + String::toString(vecIPLPaths.size()) + " IPL files in " + Path::getFileName(pMapMoverAndIDShifterDialogData->m_strDATFilePath));
	}

	delete pMapMoverAndIDShifterDialogData;
	getIMGF()->getTaskManager()->onTaskEnd("onRequestMapMoverAndIDShifter");
	*/
}