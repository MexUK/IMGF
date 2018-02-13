#pragma warning(disable : 4005)

#include "nsimgf.h"
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
#include "GUI/Editor/Tabs/IMGEditorTab.h"
#include "Format/IMG/Regular/IMGManager.h"
#include "Format/IMG/Regular/IMGFormat.h"
#include "Format/IMG/Regular/IMGEntry.h"
#include "Format/IDE/IDEManager.h"
#include "Format/IPL/IPLManager.h"
#include "Format/COL/COLManager.h"
#include "Format/COL/COLFormat.h"
#include "Format/COL/COLEntry.h"
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
#include "Task/Tasks/FileGroups/FileGroupManager.h"
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
#include "GUI/Input/InputManager.h"
#include "GUI/Input/EInputItem.h"
#include "Engine/RAGE/RageResourceType.h"
#include "Format/FormatVersionManager.h"
#include "Format/FormatVersion.h"
#include <algorithm>
#include <stdio.h>
#include <Shellapi.h>

using namespace std;
using namespace bxcf;
using namespace bxcf::fileType;
using namespace bxgx;
using namespace bxgi;
using namespace imgf;
using namespace imgf::task;
using namespace imgf::mainLayer::input;

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
		// todo
		//increaseProgress();
	}
}

// file/folder input windows
vector<string>	Tasks::openFile(string strExtensionFilters, bool bAllowMultiSelect, string strDefaultFileName)
{
	m_pTaskManager->onPauseTask();
	vector<string> vecFilePaths = Input::openFile(Editor::getEditorName(m_pMainWindow->getActiveEditor()->getEditorType()) + "_" + getTaskName(), strExtensionFilters, bAllowMultiSelect, strDefaultFileName);
	m_pTaskManager->onResumeTask();
	return vecFilePaths;
}

string			Tasks::saveFile(string strExtensionFilters, string strDefaultFileName)
{
	m_pTaskManager->onPauseTask();
	string strFilePath = Input::saveFile(Editor::getEditorName(m_pMainWindow->getActiveEditor()->getEditorType()) + "_" + getTaskName(), strExtensionFilters, strDefaultFileName);
	m_pTaskManager->onResumeTask();
	return strFilePath;
}

string			Tasks::openFolder(string strTitle, string strInitialDir)
{
	m_pTaskManager->onPauseTask();
	string strFolderPath = Input::openFolder(strTitle, Editor::getEditorName(m_pMainWindow->getActiveEditor()->getEditorType()) + "_" + getTaskName());
	m_pTaskManager->onResumeTask();
	return strFolderPath;
}

string			Tasks::saveFolder(string strTitle, string strInitialDir)
{
	m_pTaskManager->onPauseTask();
	string strFolderPath = Input::saveFolder(strTitle, Editor::getEditorName(m_pMainWindow->getActiveEditor()->getEditorType()) + "_" + getTaskName());
	m_pTaskManager->onResumeTask();
	return strFolderPath;
}

uint32			Tasks::showMessage(string strMessage, string strWindowTitle, uint32 uiButtons)
{
	getIMGF()->getTaskManager()->onPauseTask();
	uint32 uiResult = Input::showMessage(strMessage, strWindowTitle, uiButtons);
	getIMGF()->getTaskManager()->onResumeTask();
	return uiResult;
}

// active tab
EditorTab*		Tasks::getTab(void)
{
	return m_pMainWindow->getActiveEditor()->getActiveEditorTab();
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

	string strOutputFilePath = getIMGF()->getActiveProjectFolderPath();
	string strEditorFileExtension = m_pMainWindow->getActiveEditor()->getEditorFileFormats()[0];

	string strNewFileFolderPath;
	if (strOutputFilePath == "")
	{
		strNewFileFolderPath = DataPath::getDataPath() + "New/" + String::toUpperCase(strEditorFileExtension);
	}
	else
	{
		strNewFileFolderPath = strOutputFilePath;
	}
	
	string strNewFilePath = strNewFileFolderPath + "/New." + String::toLowerCase(strEditorFileExtension);
	string strNewFilePath2 = strNewFilePath;
	uint32 uiSuffix = 2;
	while (m_pMainWindow->getActiveEditor()->isFilePathOpen(strNewFilePath) || File::doesFileExist(strNewFilePath))
	{
		strNewFilePath = Path::removeFileExtension(strNewFilePath2) + String::toString(uiSuffix) + "." + Path::getFileExtension(strNewFilePath2);
		uiSuffix++;
	}

	File::createFoldersForPath(strNewFilePath);

	m_pMainWindow->getActiveEditor()->addBlankEditorTab(strNewFilePath);

	onCompleteTask();
}

void		Tasks::newWTD(void)
{
	onStartTask("newWTD");

	string strOutputFilePath = getIMGF()->getActiveProjectFolderPath();
	string strEditorFileExtension = "WTD";

	string strNewFileFolderPath;
	if (strOutputFilePath == "")
	{
		strNewFileFolderPath = DataPath::getDataPath() + "New/" + String::toUpperCase(strEditorFileExtension);
	}
	else
	{
		strNewFileFolderPath = strOutputFilePath;
	}

	string strNewFilePath = strNewFileFolderPath + "/New." + String::toLowerCase(strEditorFileExtension);
	string strNewFilePath2 = strNewFilePath;
	uint32 uiSuffix = 2;
	while (m_pMainWindow->getActiveEditor()->isFilePathOpen(strNewFilePath) || File::doesFileExist(strNewFilePath))
	{
		strNewFilePath = Path::removeFileExtension(strNewFilePath2) + String::toString(uiSuffix) + "." + Path::getFileExtension(strNewFilePath2);
		uiSuffix++;
	}

	File::createFoldersForPath(strNewFilePath);

	m_pMainWindow->getActiveEditor()->addBlankEditorTab(strNewFilePath);

	onCompleteTask();
}

void		Tasks::newIMGV3(void)
{
	onStartTask("newIMGV3");

	string strOutputFilePath = getIMGF()->getActiveProjectFolderPath();
	string strEditorFileExtension = "IMG";

	string strNewFileFolderPath;
	if (strOutputFilePath == "")
	{
		strNewFileFolderPath = DataPath::getDataPath() + "New/" + String::toUpperCase(strEditorFileExtension);
	}
	else
	{
		strNewFileFolderPath = strOutputFilePath;
	}

	string strNewFilePath = strNewFileFolderPath + "/New." + String::toLowerCase(strEditorFileExtension);
	string strNewFilePath2 = strNewFilePath;
	uint32 uiSuffix = 2;
	while (m_pMainWindow->getActiveEditor()->isFilePathOpen(strNewFilePath) || File::doesFileExist(strNewFilePath))
	{
		strNewFilePath = Path::removeFileExtension(strNewFilePath2) + String::toString(uiSuffix) + "." + Path::getFileExtension(strNewFilePath2);
		uiSuffix++;
	}

	File::createFoldersForPath(strNewFilePath);

	if (m_pMainWindow->getActiveEditor()->getEditorType() == IMG_EDITOR)
	{
		((IMGEditor*)m_pMainWindow->getActiveEditor())->addBlankEditorTab(strNewFilePath, IMG_3);
	}
	else if (m_pMainWindow->getActiveEditor()->getEditorType() == RADAR_EDITOR)
	{
		((RadarEditor*)m_pMainWindow->getActiveEditor())->addBlankEditorTab(strNewFilePath, IMG_3);
	}

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

	vector<string> vecFilePaths = openFile(String::join(m_pMainWindow->getActiveEditor()->getFileFormatsForChooseFile(), ","));
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
			showMessage("Unable to detect file format.\r\n\r\n" + strFilePath, "Unknown File Format");
			return m_pTaskManager->onAbortTask();
		}

		bUseExistingFileHandle = true;
		if (uiFormatId == 0) // IMG format
		{
			strExtensionUpper = "DIR";
		}
	}
	*/

	if (strExtensionUpper == "")
	{
		showMessage("File doesn't have an extension.\r\n\r\n" + strFilePath, "Format Not Detected");
		return onAbortTask();
	}
	
	Editor *pEditor = m_pMainWindow->getEditorFromFileExtension(Path::getFileExtension(strFilePath));
	if (!pEditor)
	{
		showMessage(strExtensionUpper + " files are not supported.\r\n\r\n" + strFilePath, "Format Not Supported");
		return onAbortTask();
	}

	m_pMainWindow->setActiveEditor(pEditor);

	if (!pEditor->addEditorTab(strFilePath))
	{
		return onAbortTask();
	}

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

	onCompleteTask();
}

void		Tasks::chooseFolderToOpen(void)
{
	onStartTask("chooseFolderToOpen");

	string strFolderPath = openFolder("Choose a folder to open editor files from.");
	if (strFolderPath == "")
	{
		return m_pTaskManager->onAbortTask();
	}

	vector<string> vecFileNames = File::getFileNames(strFolderPath);
	for (string& strFileName : vecFileNames)
	{
		if (IMGF::isFileExtensionOpenable(Path::getFileExtension(strFileName)))
		{
			_openFile(strFolderPath + strFileName);
		}
	}

	onCompleteTask();
}

void		Tasks::openFolderRecursively(void)
{
	onStartTask("openFolderRecursively");

	string strFolderPath = openFolder("Choose a folder to recursively open editor files from.");
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

	vector<string> vecFilePaths = File::getFilePaths(strFolderPath, true, false, String::join(IMGF::getFileExtensionsOpenable(), ","), true);
	for (string& strFilePath : vecFilePaths)
	{
		_openFile(strFilePath);
	}

	onCompleteTask();
}

void		Tasks::reopenFile(void)
{
	onStartTask("reopenFile");

	string strFilePath = getTab()->getFile()->getFilePath();

	m_pMainWindow->getActiveEditor()->removeActiveEditorTab();
	m_pMainWindow->getActiveEditor()->addEditorTab(strFilePath);

	onCompleteTask();
}

void		Tasks::openLastClosedFile(void)
{
	onStartTask("onRequestOpenLast");

	uint32 uiRecentlyOpenedCount = String::toUint32(INIManager::getItem(AppDataPath::getRecentlyOpenedPath(), Editor::getEditorName(m_pMainWindow->getActiveEditor()->getEditorType()), "Count"));
	if (uiRecentlyOpenedCount > 0)
	{
		string strFilePath = INIManager::getItem(AppDataPath::getRecentlyOpenedPath(), Editor::getEditorName(m_pMainWindow->getActiveEditor()->getEditorType()), String::toString(uiRecentlyOpenedCount));
		m_pMainWindow->getActiveEditor()->addEditorTab(strFilePath);
	}
	
	onCompleteTask();
}

void		Tasks::openFileFolderInExplorer(void)
{
	onStartTask("openFileFolderInExplorer");

	string strFolderPath = Path::getDirectory(getTab()->getFile()->getFilePath());
	Process::openFolder(strFolderPath);

	onCompleteTask();
}

void		Tasks::clearRecentlyOpenFiles(void)
{
	onStartTask("clearRecentlyOpenFiles");

	getIMGF()->getRecentlyOpenManager()->removeRecentlyOpenedEntries(getIMGF()->getWindowManager()->getMainWindow()->getActiveEditor()->getEditorType());

	onCompleteTask();
}

void		Tasks::openTodaysLogsFile(void)
{
	onStartTask("openTodaysLogsFile");

	string strLogsFolderPath = getIMGF()->getSettingsManager()->getSetting("LogsFolderPath");
	if (strLogsFolderPath == "")
	{
		showMessage("The folder for saving logs to file is not set, please choose this in Settings first.", "Save Logs Folder Not Set", MB_OK);
		return onAbortTask();
	}

	string strLogsFilePath = strLogsFolderPath + String::getDateTextForFolder() + ".txt";

	if (!File::doesFileExist(strLogsFilePath))
	{
		showMessage("File does not exist:\n\n" + strLogsFilePath, "File Doesn't Exist", MB_OK);
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
		showMessage("The folder for saving logs to file is not set, please choose this in Settings first.", "Save Logs Folder Not Set", MB_OK);
		return onAbortTask();
	}

	if (!File::doesFolderExist(strLogsFolderPath))
	{
		showMessage("Folder does not exist:\n\n" + strLogsFolderPath, "Folder Doesn't Exist", MB_OK);
		return onAbortTask();
	}

	Process::openFolder(strLogsFolderPath);

	onCompleteTask();
}

void		Tasks::repeatLastTask(void)
{
	uint32 uiMenuItemId = getIMGF()->getInputManager()->getLastTaskId();
	if (uiMenuItemId == -1)
	{
		return;
	}

	getIMGF()->getInputManager()->processTask(uiMenuItemId);
}

void		Tasks::_saveFile(void)
{
	onStartTask("saveFile");

	setMaxProgress(getTab()->getFile()->getEntryCount() * 2);

	getTab()->getFile()->serialize();

	getTab()->logf("Saved %s.", Path::getFileName(getTab()->getFile()->getFilePath()).c_str());

	onCompleteTask();
}

void		Tasks::saveFileAs(void)
{
	onStartTask("saveFileAs");

	vector<string>& vecEditorExtensions = getTab()->getEditor()->getEditorFileFormats();
	string strNewFilePath = saveFile(String::join(vecEditorExtensions, ","), "New " + vecEditorExtensions[0] + "." + vecEditorExtensions[0]);
	if (strNewFilePath == "")
	{
		return onAbortTask();
	}

	setMaxProgress(getTab()->getFile()->getEntryCount() * 2);

	getTab()->getFile()->serialize(strNewFilePath);

	getTab()->getFile()->setFilePath(strNewFilePath);
	getTab()->setFileInfoText();
	getTab()->updateTabText();

	getTab()->logf("Saved as %s.", Path::getFileName(strNewFilePath).c_str());

	onCompleteTask();
}

void		Tasks::saveAllFiles(void)
{
	onStartTask("saveAllFiles");

	uint32 uiEntryCountAllTabs = 0;
	for (EditorTab *pEditorTab : getTab()->getEditor()->getEditorTabs().getEntries())
	{
		uiEntryCountAllTabs += pEditorTab->getFile()->getEntryCount();
	}
	setMaxProgress(uiEntryCountAllTabs * 2);

	for (EditorTab *pEditorTab : getTab()->getEditor()->getEditorTabs().getEntries())
	{
		pEditorTab->getFile()->serialize();

		pEditorTab->log("Saved all files in editor.");
	}

	onCompleteTask();
}

void		Tasks::cloneFile(void)
{
	onStartTask("cloneFile");

	Format *pFile = getTab()->getFile();

	string strFileExtension = Path::getFileExtension(pFile->getFilePath());
	string strClonedPath = Path::getDirectory(pFile->getFilePath()) + Path::removeFileExtension(Path::getFileName(pFile->getFilePath())) + "-cloned." + strFileExtension;
	strClonedPath = File::getNextIncrementingFileName(strClonedPath);

	pFile->serialize(strClonedPath);

	getTab()->logf("Cloned into %s.", Path::getFileName(strClonedPath).c_str());

	setMaxProgress(pFile->getEntryCount() * 2);
	m_pMainWindow->getActiveEditor()->addEditorTab(strClonedPath);

	onCompleteTask();
}

void		Tasks::saveFileGroup(void)
{
	onStartTask("saveFileGroup");

	m_pTaskManager->onPauseTask();
	string strFileGroupName = m_pMainWindow->showSingleLineTextBoxWindow("Choose File Group Name", "Choose a name for the file group.");
	m_pTaskManager->onResumeTask();
	if (strFileGroupName == "")
	{
		return onAbortTask();
	}
	else if (String::isIn(strFileGroupName, ";"))
	{
		showMessage("The file group name cannot contain a semi colon (;).", "Invalid File Group Name", MB_OK);
		return onAbortTask();
	}

	vector<string> vecEditorFilePaths;
	for (EditorTab *pEditorTab : m_pMainWindow->getActiveEditor()->getEditorTabs().getEntries())
	{
		vecEditorFilePaths.push_back(pEditorTab->getFile()->getFilePath());
	}

	EEditor uiEditor = m_pMainWindow->getActiveEditor()->getEditorType();
	getIMGF()->getFileGroupManager()->addFileGroup(uiEditor, strFileGroupName, vecEditorFilePaths); // todo - rename SessionManager to FileGroupManager
	getIMGF()->getFileGroupManager()->loadFileGroups(uiEditor);

	for (EditorTab *pEditorTab : m_pMainWindow->getActiveEditor()->getEditorTabs().getEntries())
	{
		pEditorTab->logf("Saved file group %s", strFileGroupName.c_str());
	}

	onCompleteTask();
}

void		Tasks::saveLogs(void)
{
	onStartTask("saveLogs");
	
	string strLogFilePath = saveFile("txt", "Saved Logs - " + Path::removeFileExtension(Path::getFileName(getTab()->getFile()->getFilePath())) + ".txt");
	if (strLogFilePath == "")
	{
		return onAbortTask();
	}

	File::setTextFile(strLogFilePath, String::join(getTab()->getLog()->getTextLines(), "\n"));

	getTab()->log("Saved logs.");

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
	for (EditorTab *pEditorTab : m_pMainWindow->getActiveEditor()->getEditorTabs().getEntries())
	{
		strAllTabsLogs += "[[" + pEditorTab->getFile()->getFilePath() + "]]\n\n" + String::join(pEditorTab->getLog()->getTextLines(), "\n") + "\n\n\n\n";

		pEditorTab->log("Saved logs for all tabs.");
	}

	File::setTextFile(strLogFilePath, strAllTabsLogs);
	
	onCompleteTask();
}

void			Tasks::clearLogs(void)
{
	onStartTask("clearLogs");

	getTab()->clearLogs();

	getTab()->logf("Cleared logs.");

	onCompleteTask();
}

void			Tasks::clearLogsAllTabs(void)
{
	onStartTask("clearLogsAllTabs");

	for (EditorTab *pEditorTab : m_pMainWindow->getActiveEditor()->getEditorTabs().getEntries())
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
		if (showMessage("Save file before closing?\n\n" + getTab()->getFile()->getFilePath(), "Auto Save?") == MB_OK)
		{
			getTab()->getFile()->serialize();
		}
	}
	m_pMainWindow->getActiveEditor()->removeActiveEditorTab();

	onCompleteTask();
}

void		Tasks::closeAllFiles(void)
{
	onStartTask("closeAllFiles");

	bool bConfirmOnClose = getIMGF()->getSettingsManager()->getSettingBool("RebuildConfirmationOnClose");

	vector<EditorTab*> vecEditorTabs = m_pMainWindow->getActiveEditor()->getEditorTabs().getEntries();
	for (EditorTab *pEditorTab : vecEditorTabs)
	{
		if (bConfirmOnClose)
		{
			if (showMessage("Save file before closing?\n\n" + pEditorTab->getFile()->getFilePath(), "Auto Save?") == 1)
			{
				pEditorTab->getFile()->serialize();
			}
		}
		m_pMainWindow->getActiveEditor()->removeEditorTab(pEditorTab);
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

	vector<string> vecFilePaths = openFile(String::join(m_pMainWindow->getActiveEditor()->getImportEditorFileFormats(), ","));
	if (vecFilePaths.size() == 0)
	{
		return onAbortTask();
	}

	setMaxProgress(vecFilePaths.size());

	for (string& strFilePath : vecFilePaths)
	{
		getTab()->addEntryViaFile(strFilePath);
		increaseProgress();
	}

	if (vecFilePaths.size() == 1)
	{
		getTab()->logf("Added file %s.", Path::getFileName(vecFilePaths[0]).c_str());
	}
	else
	{
		getTab()->logf("Added %u files.", vecFilePaths.size());
	}

	getTab()->setFileUnsaved(true);

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
		getTab()->addEntryViaFile(strFolderPath + strFileName);
		increaseProgress();
	}

	if (vecFileNames.size() > 0)
	{
		getTab()->setFileUnsaved(true);
		getTab()->logf("Added %u files from folder %s.", vecFileNames.size(), Path::getFolderName(strFolderPath).c_str());
	}

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
		getTab()->addEntryViaFile(strFilePath);
		increaseProgress();
	}

	if (vecFilePaths.size() > 0)
	{
		getTab()->setFileUnsaved(true);
		getTab()->logf("Added %u files recursively from folder %s.", vecFilePaths.size(), Path::getFolderName(strFolderPath).c_str());
	}

	onCompleteTask();
}

void		Tasks::importByIDE(void)
{
	onStartTask("importByIDE");

	string strFileExtension = String::toUpperCase(Path::getFileExtension(getTab()->getFile()->getFilePath()));
	IDEInputWindowResult ideInputWindowResult = getIMGF()->getWindowManager()->showIDEInputWindow("Import into " + strFileExtension + " by IDE", "Choose IDE items to import into the " + strFileExtension + ":");
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
			getTab()->addEntryViaFile(strEntryFilePath);
		}

		increaseProgress();
	}

	if (uiImportCount > 0)
	{
		getTab()->setFileUnsaved(true);
		getTab()->logf("Imported %u entries by %u IDE files.", vecAllIDEEntryNames.size(), vecIDEFilePaths.size());
	}

	onCompleteTask();
}

void		Tasks::importByEntryNames(void)
{
	onStartTask("importByEntryNames");

	m_pTaskManager->onPauseTask();
	string strInputEntryNames = m_pMainWindow->showMultiLineTextBoxWindow("Import by Entry Names", "Choose entry names to import, 1 per line.");
	m_pTaskManager->onResumeTask();
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
			getTab()->addEntryViaFile(strFolderPath + strFileName);
			uiImportedEntryCount++;
			increaseProgress();
		}
	}
	getIMGTab()->getEntryGrid()->setActiveItem();

	if (uiImportedEntryCount > 0)
	{
		getIMGTab()->loadFilter_Type();
		getIMGTab()->loadFilter_Version();
		getIMGTab()->setFileUnsaved(true);
	}

	getTab()->logf("Imported %u entries by entry names.", uiImportedEntryCount);

	onCompleteTask();
}

void		Tasks::exportSelected(void)
{
	onStartTask("exportSelected");

	string strFolderPath = getIMGF()->getActiveProjectFolderPath();
	if (strFolderPath == "")
	{
		strFolderPath = openFolder("Choose a folder to export the selected files to.");
		if (strFolderPath == "")
		{
			return onAbortTask();
		}
	}

	EEditor uiEditorType = m_pMainWindow->getActiveEditor()->getEditorType();
	uint32 uiSelectedEntryCount = getTab()->getSelectedEntryCount();
	if (uiEditorType == ITEM_DEFINITION_EDITOR || uiEditorType == ITEM_PLACEMENT_EDITOR || uiEditorType == DAT_EDITOR)
	{
		vector<string> vecSelectedTextLines = getTab()->getSelectedTextLines();
		File::setTextFile(strFolderPath + "Export Selected.ide", String::join(vecSelectedTextLines, "\n"));
	}
	else
	{
		setMaxProgress(uiSelectedEntryCount);

		vector<FormatEntry*> vecEntries = getTab()->getSelectedEntries();
		getTab()->getContainerFile()->exportMultiple(vecEntries, strFolderPath);
	}

	getTab()->logf("Exported %u selected entries.", uiSelectedEntryCount);

	onCompleteTask();
}

void		Tasks::exportAll(void)
{
	onStartTask("exportAll");

	string strFolderPath = getIMGF()->getActiveProjectFolderPath();
	if (strFolderPath == "")
	{
		strFolderPath = openFolder("Choose a folder to export all files to.");
		if (strFolderPath == "")
		{
			return onAbortTask();
		}
	}

	EEditor uiEditorType = m_pMainWindow->getActiveEditor()->getEditorType();
	uint32 uiTotalEntryCount;
	if (uiEditorType == ITEM_DEFINITION_EDITOR || uiEditorType == ITEM_PLACEMENT_EDITOR || uiEditorType == DAT_EDITOR)
	{
		uiTotalEntryCount = getTab()->getTotalEntryCount();
		vector<string> vecTextLines = getTab()->getTextLines();
		File::setTextFile(strFolderPath + "Export All.ide", String::join(vecTextLines, "\n"));
	}
	else
	{
		uiTotalEntryCount = getTab()->getTotalEntryCount();
		setMaxProgress(uiTotalEntryCount);

		getTab()->getContainerFile()->exportAll(strFolderPath);
	}

	getTab()->logf("Exported all %u entries.", uiTotalEntryCount);

	onCompleteTask();
}

void		Tasks::exportByIndex(void)
{
	onStartTask("exportByIndex");

	m_pTaskManager->onPauseTask();
	NumericMultiOptionInputLayerResult nmoir = m_pMainWindow->showNumericMultiOptionWindow("Export Entries by Index", "Export entries with an index"); // todo - rename nmoir
	m_pTaskManager->onResumeTask();
	if (nmoir.m_bCancelled)
	{
		return onAbortTask();
	}

	string strFolderPath = getIMGF()->getActiveProjectFolderPath();
	if (strFolderPath == "")
	{
		strFolderPath = openFolder("Choose a folder to export the files to.");
		if (strFolderPath == "")
		{
			return onAbortTask();
		}
	}

	uint32 uiTotalEntryCount = getTab()->getTotalEntryCount();
	setMaxProgress(uiTotalEntryCount * 2);

	vector<FormatEntry*> vecEntries = getTab()->getEntriesByNumericMultiOptionValues(0, nmoir.m_uiOptionIndex, nmoir.m_uiTextBoxValue1, nmoir.m_uiTextBoxValue2); // todo - magic int
	setMaxProgress(uiTotalEntryCount + vecEntries.size(), false);
	for (FormatEntry *pEntry : vecEntries)
	{
		getTab()->getContainerFile()->exportSingle(pEntry, strFolderPath);
		increaseProgress();
	}

	getTab()->logf("Exported %u entries with an index %s.", vecEntries.size(), nmoir.getMessageText().c_str());

	onCompleteTask();
}

void		Tasks::exportByName(void)
{
	onStartTask("exportByName");

	m_pTaskManager->onPauseTask();
	string strEntryNameInput = m_pMainWindow->showSingleLineTextBoxWindow("Export Entries by Name", "Export entries with a name that includes:");
	m_pTaskManager->onResumeTask();
	if (strEntryNameInput == "")
	{
		return onAbortTask();
	}

	string strFolderPath = getIMGF()->getActiveProjectFolderPath();
	if (strFolderPath == "")
	{
		strFolderPath = openFolder("Choose a folder to export the files to.");
		if (strFolderPath == "")
		{
			return onAbortTask();
		}
	}

	uint32 uiTotalEntryCount = getTab()->getFile()->getEntryCount();
	setMaxProgress(uiTotalEntryCount * 2);

	vector<FormatEntry*> vecEntries = getTab()->getContainerFile()->getEntriesByName(strEntryNameInput, true);
	setMaxProgress(uiTotalEntryCount + vecEntries.size(), false); // todo - increaseMaxProgress
	for (FormatEntry *pEntry : vecEntries)
	{
		getTab()->getContainerFile()->exportSingle(pEntry, strFolderPath);
		increaseProgress();
	}

	getTab()->logf("Exported %u entries with a name that includes %s.", vecEntries.size(), strEntryNameInput.c_str());

	onCompleteTask();
}

void		Tasks::exportByOffset(void)
{
	onStartTask("exportByOffset");

	m_pTaskManager->onPauseTask();
	NumericMultiOptionInputLayerResult nmoir = m_pMainWindow->showNumericMultiOptionWindow("Export Entries by Offset", "Export entries with an offset");
	m_pTaskManager->onResumeTask();
	if (nmoir.m_bCancelled)
	{
		return onAbortTask();
	}

	string strFolderPath = getIMGF()->getActiveProjectFolderPath();
	if (strFolderPath == "")
	{
		strFolderPath = openFolder("Choose a folder to export the files to.");
		if (strFolderPath == "")
		{
			return onAbortTask();
		}
	}

	uint32 uiTotalEntryCount = getTab()->getFile()->getEntryCount();
	setMaxProgress(uiTotalEntryCount * 2);

	vector<FormatEntry*> vecEntries = getTab()->getEntriesByNumericMultiOptionValues(2, nmoir.m_uiOptionIndex, nmoir.m_uiTextBoxValue1, nmoir.m_uiTextBoxValue2); // todo - magic int
	setMaxProgress(uiTotalEntryCount + vecEntries.size(), false);
	for (FormatEntry *pEntry : vecEntries)
	{
		getTab()->getContainerFile()->exportSingle(pEntry, strFolderPath);
		increaseProgress();
	}

	getTab()->logf("Exported %u entries with an offset %s.", vecEntries.size(), nmoir.getMessageText().c_str());

	onCompleteTask();
}

void		Tasks::exportBySize(void)
{
	onStartTask("exportBySize");

	m_pTaskManager->onPauseTask();
	NumericMultiOptionInputLayerResult nmoir = m_pMainWindow->showNumericMultiOptionWindow("Export Entries by Size", "Export entries with a size");
	m_pTaskManager->onResumeTask();
	if (nmoir.m_bCancelled)
	{
		return onAbortTask();
	}

	string strFolderPath = getIMGF()->getActiveProjectFolderPath();
	if (strFolderPath == "")
	{
		strFolderPath = openFolder("Choose a folder to export the files to.");
		if (strFolderPath == "")
		{
			return onAbortTask();
		}
	}

	uint32 uiTotalEntryCount = getTab()->getFile()->getEntryCount();
	setMaxProgress(uiTotalEntryCount * 2);

	vector<FormatEntry *> vecIMGEntries = getTab()->getEntriesByNumericMultiOptionValues(3, nmoir.m_uiOptionIndex, nmoir.m_uiTextBoxValue1, nmoir.m_uiTextBoxValue2); // todo - magic int
	setMaxProgress(uiTotalEntryCount + vecIMGEntries.size(), false);
	for (FormatEntry *pEntry : vecIMGEntries)
	{
		getTab()->getContainerFile()->exportSingle(pEntry, strFolderPath);
		increaseProgress();
	}

	getTab()->logf("Exported %u entries with a size %s.", vecIMGEntries.size(), nmoir.getMessageText().c_str());

	onCompleteTask();
}

void		Tasks::exportByType(void)
{
	onStartTask("exportByType");

	m_pTaskManager->onPauseTask();
	string strEntryTypeInput = m_pMainWindow->showSingleLineTextBoxWindow("Export Entries by Type", "Export entries with a type that includes:");
	m_pTaskManager->onResumeTask();
	if (strEntryTypeInput == "")
	{
		return onAbortTask();
	}

	string strFolderPath = getIMGF()->getActiveProjectFolderPath();
	if (strFolderPath == "")
	{
		strFolderPath = openFolder("Choose a folder to export the files to.");
		if (strFolderPath == "")
		{
			return onAbortTask();
		}
	}

	uint32 uiTotalEntryCount = getTab()->getFile()->getEntryCount();
	setMaxProgress(uiTotalEntryCount * 2);

	vector<FormatEntry*> vecEntries = getTab()->getContainerFile()->getEntriesByExtension(strEntryTypeInput, true);
	setMaxProgress(uiTotalEntryCount + vecEntries.size(), false); // todo - increaseMaxProgress
	for (FormatEntry *pEntry : vecEntries)
	{
		getTab()->getContainerFile()->exportSingle(pEntry, strFolderPath);
		increaseProgress();
	}

	getTab()->logf("Exported %u entries with a type that includes %s.", vecEntries.size(), strEntryTypeInput.c_str());

	onCompleteTask();
}

void		Tasks::exportByVersion(void)
{
	onStartTask("exportByVersion");

	vector<string> vecEntriesVersionsText = FormatVersionManager::get()->getEntriesVersionsText();
	m_pTaskManager->onPauseTask();
	int32 iVersionOptionIndex = m_pMainWindow->showDropDownWindow("Export Entries by Version", "Export entries with version", vecEntriesVersionsText);
	m_pTaskManager->onResumeTask();
	if (iVersionOptionIndex == -1)
	{
		return onAbortTask();
	}

	string strFolderPath = getIMGF()->getActiveProjectFolderPath();
	if (strFolderPath == "")
	{
		strFolderPath = openFolder("Choose a folder to export the files to.");
		if (strFolderPath == "")
		{
			return onAbortTask();
		}
	}

	uint32 uiTotalEntryCount = getTab()->getFile()->getEntryCount();
	setMaxProgress(uiTotalEntryCount * 2);

	FormatVersion
		*pEntryVersion = FormatVersionManager::get()->getEntryByVersionText(vecEntriesVersionsText[iVersionOptionIndex]);
	vector<FormatEntry*>
		vecEntries = getTab()->getContainerFile()->getEntriesByVersion(pEntryVersion->m_uiFileType, pEntryVersion->m_uiRawVersion);
	setMaxProgress(uiTotalEntryCount + vecEntries.size(), false); // todo - increaseMaxProgress
	for (FormatEntry *pEntry : vecEntries)
	{
		getTab()->getContainerFile()->exportSingle(pEntry, strFolderPath);
		increaseProgress();
	}

	getTab()->logf("Exported %u entries with version %s.", vecEntries.size(), pEntryVersion->m_strVersionText.c_str());

	onCompleteTask();
}


void		Tasks::exportAllIntoGroupedFoldersByType(void)
{
	onStartTask("exportAllIntoGroupedFoldersByType");

	string strFolderPath = getIMGF()->getActiveProjectFolderPath();
	if (strFolderPath == "")
	{
		strFolderPath = openFolder("Choose a folder to export files into grouped folders by type.");
		if (strFolderPath == "")
		{
			return onAbortTask();
		}
	}

	uint32 uiTotalEntryCount = getTab()->getFile()->getEntryCount();
	setMaxProgress(uiTotalEntryCount);

	set<string> setExtensionsUsed;
	for (FormatEntry *pEntry : getTab()->getContainerFile()->getAllEntries())
	{
		string strFileExtension = pEntry->getEntryExtension();
		if (strFileExtension == "")
		{
			strFileExtension = "NoExtension";
		}

		string strExportGroupedByTypeFolderPath = strFolderPath + strFileExtension + "/";

		getTab()->getContainerFile()->exportSingle(pEntry, strExportGroupedByTypeFolderPath);

		increaseProgress();

		setExtensionsUsed.insert(strFileExtension);
	}

	getTab()->logf("Exported all %u entries into %u folders.", uiTotalEntryCount, setExtensionsUsed.size());

	onCompleteTask();
}

void		Tasks::exportAllFromAllTabs(void)
{
	onStartTask("exportAllFromAllTabs");

	string strFolderPath = getIMGF()->getActiveProjectFolderPath();
	if (strFolderPath == "")
	{
		strFolderPath = openFolder("Choose a folder to export all files from all tabs to.");
		if (strFolderPath == "")
		{
			return onAbortTask();
		}
	}

	uint32 uiTotalEntryCount = 0;
	for (EditorTab *pEditorTab : getTab()->getEditor()->getEditorTabs().getEntries())
	{
		uiTotalEntryCount += pEditorTab->getFile()->getEntryCount();
	}
	setMaxProgress(uiTotalEntryCount);

	for (EditorTab *pEditorTab : getTab()->getEditor()->getEditorTabs().getEntries())
	{
		pEditorTab->getContainerFile()->exportAll(strFolderPath);
	}

	getTab()->logf("Exported all %u entries from all tabs.", uiTotalEntryCount);

	onCompleteTask();
}

void		Tasks::exportAllFromAllTabsIntoGroupedFoldersByType(void)
{
	onStartTask("exportAllFromAllTabsIntoGroupedFoldersByType");

	string strFolderPath = getIMGF()->getActiveProjectFolderPath();
	if (strFolderPath == "")
	{
		strFolderPath = openFolder("Choose a folder to export all files from all tabs grouped by type to.");
		if (strFolderPath == "")
		{
			return onAbortTask();
		}
	}

	uint32 uiTotalEntryCount = 0;
	for (EditorTab *pEditorTab : getTab()->getEditor()->getEditorTabs().getEntries())
	{
		uiTotalEntryCount += pEditorTab->getFile()->getEntryCount();
	}
	setMaxProgress(uiTotalEntryCount);

	set<string> setExtensionsUsed;
	for (EditorTab *pEditorTab : getTab()->getEditor()->getEditorTabs().getEntries())
	{
		for (FormatEntry *pEntry : pEditorTab->getContainerFile()->getAllEntries())
		{
			string strFileExtension = pEntry->getEntryExtension();
			if (strFileExtension == "")
			{
				strFileExtension = "NoExtension";
			}

			string strExportGroupedByTypeFolderPath = strFolderPath + strFileExtension + "/";

			pEditorTab->getContainerFile()->exportSingle(pEntry, strExportGroupedByTypeFolderPath);

			increaseProgress();

			setExtensionsUsed.insert(strFileExtension);
		}
	}

	getTab()->logf("Exported all %u entries from all tabs into %u folders.", uiTotalEntryCount, setExtensionsUsed.size());

	onCompleteTask();
}

void		Tasks::exportSelectionFromAllTabs(void)
{
	onStartTask("exportSelectionFromAllTabs");

	string strFolderPath = getIMGF()->getActiveProjectFolderPath();
	if (strFolderPath == "")
	{
		strFolderPath = openFolder("Choose a folder to export selected files from all tabs to.");
		if (strFolderPath == "")
		{
			return onAbortTask();
		}
	}

	uint32 uiSelectedEntryCount = 0;
	for (EditorTab *pEditorTab : getTab()->getEditor()->getEditorTabs().getEntries())
	{
		uiSelectedEntryCount += pEditorTab->getSelectedEntryCount();
	}
	setMaxProgress(uiSelectedEntryCount);

	for (EditorTab *pEditorTab : getTab()->getEditor()->getEditorTabs().getEntries())
	{
		pEditorTab->getContainerFile()->exportMultiple(getTab()->getSelectedEntries(), strFolderPath);
	}

	getTab()->logf("Exported %u selected entries from all tabs.", uiSelectedEntryCount);

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

	string strFolderPath = getIMGF()->getActiveProjectFolderPath();
	if (strFolderPath == "")
	{
		strFolderPath = openFolder("Choose a folder to export the files to.");
		if (strFolderPath == "")
		{
			return onAbortTask();
		}
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

	vecIMGEntries = StdVector::removeDuplicates(vecIMGEntries);

	// export the IMG entries
	setMaxProgress((vecIDEFilePaths.size() * 2) + getIMGTab()->getIMGFile()->getEntryCount() + vecIMGEntries.size());
	getIMGTab()->getIMGFile()->exportMultiple(vecIMGEntries, strFolderPath);

	getTab()->logf("Exported %u entries by %u IDE files.", vecIMGEntries.size(), vecIDEFilePaths.size());

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

	string strExportFolderPath = getIMGF()->getActiveProjectFolderPath();
	if (strExportFolderPath == "")
	{
		strExportFolderPath = openFolder("Choose a folder to export the files to.");
		if (strExportFolderPath == "")
		{
			return onAbortTask();
		}
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
	for (IMGEditorTab *pIMGEditorTab : m_pMainWindow->getIMGEditor()->getIMGEditorTabs().getEntries())
	{
		// fetch model and TXD names from DFF/TXD files inside all opened IMG files
		unordered_map<IMGEntry*, vector<string>>
			umapIMGModelNames,
			umapIMGTextureSetNames;
		pIMGEditorTab->getIMGFile()->getModelAndTextureSetNamesFromEntries(umapIMGModelNames, umapIMGTextureSetNames);

		// choose IMG entries that have a model name or TXD name found in IDE file
		vector<IMGEntry*> vecIMGEntries = StdVector::getKeysWithMatchingEntries(umapIMGModelNames, stModelNames);
		StdVector::addToVector(vecIMGEntries, StdVector::getKeysWithMatchingEntries(umapIMGTextureSetNames, stTextureSetNames));

		vecIMGEntries = StdVector::removeDuplicates(vecIMGEntries);

		// export the IMG entries
		setMaxProgress((vecIDEFilePaths.size() * 2) + getIMGTab()->getIMGFile()->getEntryCount() + vecIMGEntries.size());
		pIMGEditorTab->getIMGFile()->exportMultiple(vecIMGEntries, strExportFolderPath);

		uiIMGEntryExportCount += vecIMGEntries.size();
	}

	getTab()->logf("Exported %u entries from all tabs by %u IDE files.", uiIMGEntryExportCount, vecIDEFilePaths.size());

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

	string strFolderPath = getIMGF()->getActiveProjectFolderPath();
	if (strFolderPath == "")
	{
		strFolderPath = openFolder("Choose a folder to export the files to.");
		if (strFolderPath == "")
		{
			return onAbortTask();
		}
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

	getTab()->logf("Exported %u entries by %u IPL files.", vecIMGEntries.size(), vecIPLFilePaths.size());

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

	string strGameFolderPath = getIMGF()->getActiveProjectFolderPath();
	if (strGameFolderPath == "")
	{
		strGameFolderPath = openFolder("Choose the game folder.");
		if (strGameFolderPath == "")
		{
			return onAbortTask();
		}
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

	getTab()->logf("Exported %u entries by %u DAT files.", vecIMGEntries.size(), vecDATFilePaths.size());

	onCompleteTask();
}

void		Tasks::exportByEntryNames(void)
{
	onStartTask("exportByEntryNames");

	m_pTaskManager->onPauseTask();
	string strInputEntryNames = m_pMainWindow->showMultiLineTextBoxWindow("Export by Entry Names", "Choose entry names to export, 1 per line.");
	m_pTaskManager->onResumeTask();
	if (strInputEntryNames == "")
	{
		return onAbortTask();
	}

	string strExportFolderPath = getIMGF()->getActiveProjectFolderPath();
	if (strExportFolderPath == "")
	{
		strExportFolderPath = openFolder("Choose a folder to export the entries to:");
		if (strExportFolderPath == "")
		{
			return onAbortTask();
		}
	}

	vector<string> vecInputEntryNames = String::split(strInputEntryNames, "\n");
	for (string& strInputEntryName : vecInputEntryNames) // todo - StdVector::trim
	{
		strInputEntryName = String::trim(strInputEntryName);
	}

	vector<FormatEntry*> vecEntries = getTab()->getContainerFile()->getEntriesByNames(vecInputEntryNames);

	setMaxProgress(vecEntries.size());
	getTab()->getContainerFile()->exportMultiple(vecEntries, strExportFolderPath);
	
	getTab()->logf("Exported %u entries by entry names.", vecEntries.size());

	onCompleteTask();
}

void		Tasks::exportByEntryNamesFromAllTabs(void)
{
	onStartTask("exportByEntryNamesFromAllTabs");

	m_pTaskManager->onPauseTask();
	string strInputEntryNames = m_pMainWindow->showMultiLineTextBoxWindow("Export by Entry Names From All Tabs", "Choose entry names to export from all tabs, 1 per line.");
	m_pTaskManager->onResumeTask();
	if (strInputEntryNames == "")
	{
		return onAbortTask();
	}

	string strExportFolderPath = getIMGF()->getActiveProjectFolderPath();
	if (strExportFolderPath == "")
	{
		strExportFolderPath = openFolder("Choose a folder to export the entries from all tabs to:");
		if (strExportFolderPath == "")
		{
			return onAbortTask();
		}
	}

	vector<string> vecInputEntryNames = String::split(strInputEntryNames, "\n");
	for (string& strInputEntryName : vecInputEntryNames)
	{
		strInputEntryName = String::trim(strInputEntryName);
	}

	uint32 uiEntryExportCount = 0;
	for (EditorTab *pEditorTab : m_pMainWindow->getActiveEditor()->getEditorTabs().getEntries())
	{
		vector<FormatEntry*> vecEntries = pEditorTab->getContainerFile()->getEntriesByNames(vecInputEntryNames);

		setMaxProgress(vecEntries.size());
		pEditorTab->getContainerFile()->exportMultiple(vecEntries, strExportFolderPath);

		uiEntryExportCount += vecEntries.size();
	}

	for (EditorTab *pEditorTab : m_pMainWindow->getActiveEditor()->getEditorTabs().getEntries())
	{
		pEditorTab->logf("Exported %u entries by entry names from all tabs.", uiEntryExportCount);
	}

	onCompleteTask();
}

void		Tasks::exportTextureNameList(void)
{
	onStartTask("exportTextureNameList");

	string strTextureImagesFolderPath = Input::openFolder("Choose a folder containing texture images: (BMP, JPG, GIF, PNG, etc)");
	if (strTextureImagesFolderPath == "")
	{
		return onAbortTask();
	}

	string strOutputFilePath = getIMGF()->getActiveProjectFolderPath();
	if (strOutputFilePath == "")
	{
		strOutputFilePath = Input::saveFile("", "TXT", "Texture List.txt");
		if (strOutputFilePath == "")
		{
			return onAbortTask();
		}
	}

	vector<string> vecImagesFilePaths = File::getFilePaths(strTextureImagesFolderPath, true, false, "bmp,jpg,jpeg,gif,png,col,ico,dds", false);
	unordered_map<string, string> vecImagesFilePathsUpper;
	for (string& strImagesFilePath : vecImagesFilePaths)
	{
		vecImagesFilePathsUpper[String::toUpperCase(Path::removeFileExtension(Path::getFileName(strImagesFilePath)))] = strImagesFilePath;
	}

	string strOutputData;
	uint32 uiTextureNumber = 1;
	for (IMGEntry *pIMGEntry : (vector<IMGEntry*>&)getIMGTab()->getSelectedEntries())
	{
		if (pIMGEntry->getEntryType() == MODEL)
		{
			if (pIMGEntry->getRageResourceType() && pIMGEntry->getRageResourceType()->getResourceTypeId() == RAGE_MODEL)
			{
				 // WDR etc
			}
			else
			{
				// DFF
				DFFFormat dffFormat(pIMGEntry->getEntryData(), false);
				if (!dffFormat.unserialize())
				{
					continue;
				}

				string strTextureFileNotFoundText = "(Texture not found)";
				string& strTextureFilePath = g_strBlankString;
				for (string& strTextureName : dffFormat.getTextureNames())
				{
					string strTextureNameUpper = String::toUpperCase(strTextureName);
					if (vecImagesFilePathsUpper.count(strTextureNameUpper) == 0)
					{
						strTextureFilePath = strTextureFileNotFoundText;
					}
					else
					{
						strTextureFilePath = vecImagesFilePathsUpper[strTextureNameUpper];
					}

					strOutputData += "[Texture" + String::toString(uiTextureNumber) + "]\n";
					strOutputData += "name=" + strTextureName + "\n";
					strOutputData += "path=" + strTextureFilePath + "\n";

					uiTextureNumber++;
				}

				dffFormat.unload();
			}
		}
	}

	strOutputData = "[TXDList]\ncount=" + String::toString(uiTextureNumber - 1) + "\napp=IMG Factory 2.0\n" + strOutputData;

	File::setTextFile(strOutputFilePath, strOutputData);

	getTab()->log("Created texture list.");

	onCompleteTask();
}

void		Tasks::quickExport(void)
{
	onStartTask("quickExport");

	string strQuickExportFolderPath = getIMGF()->getActiveProjectFolderPath();
	if (strQuickExportFolderPath == "")
	{
		strQuickExportFolderPath = getIMGF()->getSettingsManager()->getSetting("QuickExportFolderPath");
		if (strQuickExportFolderPath == "")
		{
			showMessage("The Quick Export folder is not set, please choose this in Settings first.", "Quick Export Folder Not Set", MB_OK);
			return;
		}
	}
	
	EEditor uiEditorType = m_pMainWindow->getActiveEditor()->getEditorType();
	uint32 uiSelectedEntryCount = getTab()->getSelectedEntryCount();
	if (uiEditorType == ITEM_DEFINITION_EDITOR || uiEditorType == ITEM_PLACEMENT_EDITOR || uiEditorType == DAT_EDITOR)
	{
		vector<string> vecSelectedTextLines = getTab()->getSelectedTextLines();
		File::setTextFile(strQuickExportFolderPath + "Export All.ide", String::join(vecSelectedTextLines, "\n"));
	}
	else
	{
		setMaxProgress(uiSelectedEntryCount);

		getTab()->getContainerFile()->exportMultiple(getTab()->getSelectedEntries(), strQuickExportFolderPath);
	}

	getTab()->logf("Quick exported %u entries.", uiSelectedEntryCount);

	onCompleteTask();
}

void		Tasks::rename(void)
{
	onStartTask("rename");

	if (getTab()->getSelectedEntryCount() == 0)
	{
		showMessage("At least one entry must be selected to rename.", "No Entries Selected");
		return onAbortTask();
	}
	else if (getTab()->getSelectedEntryCount() > 1)
	{
		showMessage("Only one entry can be selected to rename.", "Too Many Entries Selected");
		return onAbortTask();
	}

	FormatEntry *pEntry = getTab()->getSelectedEntry();

	m_pTaskManager->onPauseTask();
	string strNewEntryName = getTab()->getLayer()->getWindow()->showSingleLineTextBoxWindow("New Entry Name", "Choose a new name for the entry:", pEntry->getEntryName());
	m_pTaskManager->onResumeTask();
	if (strNewEntryName == "")
	{
		return onAbortTask();
	}

	if (Path::getFileExtension(strNewEntryName) == "")
	{
		string strOldExtension = Path::getFileExtension(pEntry->getEntryName());
		if (strOldExtension != "")
		{
			strNewEntryName += "." + strOldExtension;
		}
	}

	setMaxProgress(1);

	if (getTab()->getContainerFile()->doesEntryNameExist(strNewEntryName))
	{
		showMessage("Entry name already exists.\n\n" + strNewEntryName, "Name Already Used", MB_OK);
		return onAbortTask();
	}

	pEntry->setEntryName(strNewEntryName);
	getTab()->onEntryChange(pEntry);
	increaseProgress();

	getTab()->setFileUnsaved(true);

	getTab()->getLayer()->getWindow()->render();

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
	Format *pFile = getTab()->getFile();
	for (string& strFilePath : vecFilePaths)
	{
		string strFileName = Path::getFileName(strFilePath);

		FormatEntry *pEntry = getTab()->getContainerFile()->getEntryByName(strFileName);
		if (!pEntry)
		{
			increaseProgress();
			continue;
		}

		pEntry->replace(strFilePath);
		// todo getTab()->onEntryChange(pEntry);

		increaseProgress();
		uiReplacedEntryCount++;
	}

	if (uiReplacedEntryCount > 0)
	{
		getTab()->setFileUnsaved(true);
		getTab()->recreateEntryList();
		getTab()->getLayer()->getWindow()->render();
	}

	getTab()->logf("Replaced %u entries by file.", uiReplacedEntryCount);

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
	Format *pFile = getTab()->getFile();
	for (string& strFileName : vecFileNames)
	{
		string strFilePath = strFolderPath + strFileName;

		FormatEntry *pEntry = getTab()->getContainerFile()->getEntryByName(strFileName);
		if (!pEntry)
		{
			increaseProgress();
			continue;
		}

		pEntry->replace(strFilePath);

		increaseProgress();
		uiReplacedEntryCount++;
	}

	if (uiReplacedEntryCount > 0)
	{
		getTab()->setFileUnsaved(true);
		getTab()->recreateEntryList();
	}

	getTab()->logf("Replaced %u entries by folder.", uiReplacedEntryCount);

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
	Format *pFile = getTab()->getFile();
	for (string& strFilePath : vecFilePaths)
	{
		string strFileName = Path::getFileName(strFilePath);

		FormatEntry *pEntry = getTab()->getContainerFile()->getEntryByName(strFileName);
		if (!pEntry)
		{
			increaseProgress();
			continue;
		}

		pEntry->replace(strFilePath);

		increaseProgress();
		uiReplacedEntryCount++;
	}

	if (uiReplacedEntryCount > 0)
	{
		getTab()->setFileUnsaved(true);
		getTab()->recreateEntryList();
	}

	getTab()->logf("Replaced %u entries recursively by folder.", uiReplacedEntryCount);

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

	vecIMGEntries = StdVector::removeDuplicates(vecIMGEntries);

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
		getIMGTab()->setFileUnsaved(true);
		getIMGTab()->readdGridEntries();
	}

	getTab()->logf("Replaced %u entries by %u IDE files.", vecIMGEntries.size(), vecIDEFilePaths.size());

	onCompleteTask();
}

void		Tasks::removeSelected(void)
{
	onStartTask("removeSelected");

	uint32 uiSelectedEntryCount = getTab()->getSelectedEntryCount();
	setMaxProgress(uiSelectedEntryCount + (uiSelectedEntryCount == 0 ? 0 : (getTab()->getFile()->getEntryCount() - uiSelectedEntryCount)));

	EEditor uiEditorType = getTab()->getEditor()->getEditorType();
	if (uiEditorType == ITEM_DEFINITION_EDITOR || uiEditorType == ITEM_PLACEMENT_EDITOR || uiEditorType == DAT_EDITOR)
	{
		getTab()->removeSelectedText();
	}
	else
	{
		getTab()->removeSelectedEntries();
	}

	if (uiSelectedEntryCount > 0)
	{
		getTab()->recreateEntryList();
		getTab()->setFileUnsaved(true);
	}

	getTab()->logf("Removed %u selected entries.", uiSelectedEntryCount);

	onCompleteTask();
}

void		Tasks::removeAll(void)
{
	onStartTask("removeAll");

	uint32 uiTotalEntryCount = getTab()->getTotalEntryCount();
	setMaxProgress(uiTotalEntryCount);

	EEditor uiEditorType = getTab()->getEditor()->getEditorType();
	if (uiEditorType == ITEM_DEFINITION_EDITOR || uiEditorType == ITEM_PLACEMENT_EDITOR || uiEditorType == DAT_EDITOR)
	{
		getTab()->removeAllText();
	}
	else
	{
		getTab()->removeAllEntries();
	}

	if (uiTotalEntryCount > 0)
	{
		getTab()->recreateEntryList();
		getTab()->setFileUnsaved(true);
	}

	getTab()->logf("Removed all %u entries.", uiTotalEntryCount);

	onCompleteTask();
}

void		Tasks::removeByIndex(void)
{
	onStartTask("removeByIndex");

	m_pTaskManager->onPauseTask();
	NumericMultiOptionInputLayerResult nmoir = m_pMainWindow->showNumericMultiOptionWindow("Remove Entries by Index", "Remove entries with an index");
	m_pTaskManager->onResumeTask();
	if (nmoir.m_bCancelled)
	{
		return onAbortTask();
	}

	uint32 uiTotalEntryCount = getTab()->getFile()->getEntryCount();
	setMaxProgress(uiTotalEntryCount * 3);

	vector<FormatEntry*> vecEntries = getTab()->getEntriesByNumericMultiOptionValues(0, nmoir.m_uiOptionIndex, nmoir.m_uiTextBoxValue1, nmoir.m_uiTextBoxValue2); // todo - magic int
	setMaxProgress(uiTotalEntryCount + vecEntries.size() + (vecEntries.size() == 0 ? 0 : (uiTotalEntryCount - vecEntries.size())), false);
	getTab()->removeEntries(vecEntries);

	if (vecEntries.size() > 0)
	{
		getTab()->recreateEntryList();
		getTab()->setFileUnsaved(true);
	}

	getTab()->logf("Removed %u entries with an index %s.", vecEntries.size(), nmoir.getMessageText().c_str());

	onCompleteTask();
}

void		Tasks::removeByName(void)
{
	onStartTask("removeByName");

	m_pTaskManager->onPauseTask();
	string strEntryNameInput = m_pMainWindow->showSingleLineTextBoxWindow("Remove Entries by Name", "Remove entries with a name that includes:");
	m_pTaskManager->onResumeTask();
	if (strEntryNameInput == "")
	{
		return onAbortTask();
	}

	uint32 uiTotalEntryCount = getTab()->getFile()->getEntryCount();
	setMaxProgress(uiTotalEntryCount * 3);

	vector<FormatEntry*> vecEntries = getTab()->getContainerFile()->getEntriesByName(strEntryNameInput, true);
	setMaxProgress(uiTotalEntryCount + vecEntries.size() + (vecEntries.size() == 0 ? 0 : (uiTotalEntryCount - vecEntries.size())), false);
	getTab()->removeEntries(vecEntries);

	if (vecEntries.size() > 0)
	{
		getTab()->recreateEntryList();
		getTab()->setFileUnsaved(true);
	}

	getTab()->logf("Removed %u entries with a name that includes %s.", vecEntries.size(), strEntryNameInput.c_str());

	onCompleteTask();
}

void		Tasks::removeByOffset(void)
{
	onStartTask("removeByOffset");

	m_pTaskManager->onPauseTask();
	NumericMultiOptionInputLayerResult nmoir = m_pMainWindow->showNumericMultiOptionWindow("Remove Entries by Offset", "Remove entries with an offset");
	m_pTaskManager->onResumeTask();
	if (nmoir.m_bCancelled)
	{
		return onAbortTask();
	}

	uint32 uiTotalEntryCount = getTab()->getFile()->getEntryCount();
	setMaxProgress(uiTotalEntryCount * 3);

	vector<FormatEntry*> vecEntries = getTab()->getEntriesByNumericMultiOptionValues(2, nmoir.m_uiOptionIndex, nmoir.m_uiTextBoxValue1, nmoir.m_uiTextBoxValue2); // todo - magic int
	setMaxProgress(uiTotalEntryCount + vecEntries.size() + (vecEntries.size() == 0 ? 0 : (uiTotalEntryCount - vecEntries.size())), false);
	getTab()->removeEntries(vecEntries);

	if (vecEntries.size() > 0)
	{
		getTab()->recreateEntryList();
		getTab()->setFileUnsaved(true);
	}

	getTab()->logf("Removed %u entries with an offset %s.", vecEntries.size(), nmoir.getMessageText().c_str());

	onCompleteTask();
}

void		Tasks::removeBySize(void)
{
	onStartTask("removeBySize");

	m_pTaskManager->onPauseTask();
	NumericMultiOptionInputLayerResult nmoir = m_pMainWindow->showNumericMultiOptionWindow("Remove Entries by Size", "Remove entries with a size");
	m_pTaskManager->onResumeTask();
	if (nmoir.m_bCancelled)
	{
		return onAbortTask();
	}

	uint32 uiTotalEntryCount = getTab()->getFile()->getEntryCount();
	setMaxProgress(uiTotalEntryCount * 3);

	vector<FormatEntry*> vecEntries = getTab()->getEntriesByNumericMultiOptionValues(3, nmoir.m_uiOptionIndex, nmoir.m_uiTextBoxValue1, nmoir.m_uiTextBoxValue2); // todo - magic int
	setMaxProgress(uiTotalEntryCount + vecEntries.size() + (vecEntries.size() == 0 ? 0 : (uiTotalEntryCount - vecEntries.size())), false);
	getTab()->removeEntries(vecEntries);

	if (vecEntries.size() > 0)
	{
		getTab()->recreateEntryList();
		getTab()->setFileUnsaved(true);
	}

	getTab()->logf("Removed %u entries with a size %s.", vecEntries.size(), nmoir.getMessageText().c_str());

	onCompleteTask();
}

void		Tasks::removeByType(void)
{
	onStartTask("removeByType");

	m_pTaskManager->onPauseTask();
	string strEntryTypeInput = m_pMainWindow->showSingleLineTextBoxWindow("Remove Entries by Type", "Remove entries with a type that includes:");
	m_pTaskManager->onResumeTask();
	if (strEntryTypeInput == "")
	{
		return onAbortTask();
	}

	uint32 uiTotalEntryCount = getTab()->getFile()->getEntryCount();
	setMaxProgress(uiTotalEntryCount * 3);

	vector<FormatEntry*> vecEntries = getTab()->getContainerFile()->getEntriesByExtension(strEntryTypeInput, true);
	setMaxProgress(uiTotalEntryCount + vecEntries.size() + (vecEntries.size() == 0 ? 0 : (uiTotalEntryCount - vecEntries.size())), false);
	getTab()->removeEntries(vecEntries);

	if (vecEntries.size() > 0)
	{
		getTab()->recreateEntryList();
		getTab()->setFileUnsaved(true);
	}

	getTab()->logf("Removed %u entries with a type that includes %s.", vecEntries.size(), strEntryTypeInput.c_str());

	onCompleteTask();
}

void		Tasks::removeByVersion(void)
{
	onStartTask("removeByVersion");

	vector<string> vecEntriesVersionsText = FormatVersionManager::get()->getEntriesVersionsText();
	m_pTaskManager->onPauseTask();
	int32 iVersionOptionIndex = m_pMainWindow->showDropDownWindow("Remove Entries by Version", "Remove entries with version", vecEntriesVersionsText);
	m_pTaskManager->onResumeTask();
	if (iVersionOptionIndex == -1)
	{
		return onAbortTask();
	}

	uint32 uiTotalEntryCount = getTab()->getFile()->getEntryCount();
	setMaxProgress(uiTotalEntryCount * 3);

	FormatVersion
		*pEntryVersion = FormatVersionManager::get()->getEntryByVersionText(vecEntriesVersionsText[iVersionOptionIndex]);
	vector<FormatEntry*>
		vecEntries = getTab()->getContainerFile()->getEntriesByVersion(pEntryVersion->m_uiFileType, pEntryVersion->m_uiRawVersion);
	setMaxProgress(uiTotalEntryCount + vecEntries.size() + (vecEntries.size() == 0 ? 0 : (uiTotalEntryCount - vecEntries.size())), false);
	getTab()->removeEntries(vecEntries);

	if (vecEntries.size() > 0)
	{
		getTab()->recreateEntryList();
		getTab()->setFileUnsaved(true);
	}

	getTab()->logf("Removed %u entries with version %s.", vecEntries.size(), pEntryVersion->m_strVersionText.c_str());

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

	vecIMGEntries = StdVector::removeDuplicates(vecIMGEntries);

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
		getIMGTab()->setFileUnsaved(true);
	}

	getTab()->logf("Removed %u entries by %u IDE files.", vecIMGEntries.size(), vecIDEFilePaths.size());

	onCompleteTask();
}

void		Tasks::removeByEntryNames(void)
{
	onStartTask("removeByEntryNames");

	m_pTaskManager->onPauseTask();
	string strInputEntryNames = m_pMainWindow->showMultiLineTextBoxWindow("Remove by Entry Names", "Choose entry names to remove, 1 per line.");
	m_pTaskManager->onResumeTask();
	if (strInputEntryNames == "")
	{
		return onAbortTask();
	}

	vector<string> vecInputEntryNames = String::split(strInputEntryNames, "\n");
	for (string& strInputEntryName : vecInputEntryNames)
	{
		strInputEntryName = String::trim(strInputEntryName);
	}

	vector<FormatEntry*> vecEntries = getTab()->getContainerFile()->getEntriesByNames(vecInputEntryNames);

	setMaxProgress(vecEntries.size());
	getTab()->removeEntries(vecEntries);

	if (vecEntries.size() > 0)
	{
		getTab()->recreateEntryList();
		getTab()->setFileUnsaved(true);
	}

	getTab()->logf("Removed %u entries by entry names.", vecEntries.size());

	onCompleteTask();
}

void		Tasks::merge(void)
{
	onStartTask("merge");
	
	vector<string> vecFilePaths = openFile(String::join(getTab()->getEditor()->getEditorFileFormats(), ","));

	/*
	todo
	uint32 uiMergeEntryCount = 0;
	for (string& strFilePath : vecFilePaths)
	{
		uiMergeEntryCount += IMGManager::getIMGEntryCount(strFilePath, IMGManager::detectIMGVersion(strFilePath));
	}
	setMaxProgress(uiMergeEntryCount);
	*/

	for (string& strFilePath : vecFilePaths)
	{
		getTab()->merge(strFilePath);
	}

	// todo
	//if (uiMergeEntryCount > 0)
	//{
		getTab()->recreateEntryList();
		getTab()->updateEntryCountText();
		getTab()->setFileUnsaved(true);
	//}

	getTab()->logf("Merged in %u files.", vecFilePaths.size());

	onCompleteTask();
}

void		Tasks::splitSelected(void)
{
	onStartTask("splitSelected");

	uint32 uiSelectedEntryCount = getTab()->getSelectedEntryCount();
	if (uiSelectedEntryCount == 0)
	{
		showMessage("At least one entry must be selected to split selected entries.", "Selected Entry Needed", MB_OK);
		return onAbortTask();
	}

	string strNewFilePath = saveFile(String::join(getTab()->getEditor()->getEditorFileFormats(), ","), "Split." + Path::getFileExtension(getTab()->getFile()->getFilePath()));
	if (strNewFilePath == "")
	{
		return onAbortTask();
	}

	EFileType uiEditorFileType = getTab()->getEditor()->getEditorFileType();
	vector<string> vecDropDownOptions = FormatVersionManager::get()->getEntriesVersionsText(uiEditorFileType);
	m_pTaskManager->onPauseTask();
	int32 iNewFileVersionOptionIndex = getTab()->getLayer()->getWindow()->showDropDownWindow("Choose Output File Version", "Create output with version (cancel for same version)", vecDropDownOptions);
	m_pTaskManager->onResumeTask();

	FormatVersion *pFormatVersion = nullptr;
	if (iNewFileVersionOptionIndex == -1)
	{
		pFormatVersion = new FormatVersion;
		pFormatVersion->m_uiFileType = uiEditorFileType;
		pFormatVersion->m_uiRawVersion = getTab()->getContainerFile()->getRawVersion();
		pFormatVersion->m_uiFileType = uiEditorFileType;
	}
	else
	{
		pFormatVersion = FormatVersionManager::get()->getEntryByVersionText(vecDropDownOptions[iNewFileVersionOptionIndex]);
	}

	bool bDeleteSelectedEntriesFromSourceFile = showMessage("Also delete selected entries from source file?", "Delete Selected Entries?") == MB_OK;

	EEditor uiEditorType = getTab()->getEditor()->getEditorType();
	if (uiEditorType == ITEM_DEFINITION_EDITOR || uiEditorType == ITEM_PLACEMENT_EDITOR || uiEditorType == DAT_EDITOR)
	{
		vector<string> vecSelectedTextLines = getTab()->getSelectedTextLines();
		getTab()->split(vecSelectedTextLines, strNewFilePath, pFormatVersion->m_uiRawVersion);
	}
	else
	{
		vector<FormatEntry*> vecEntries = getTab()->getSelectedEntries();
		getTab()->getContainerFile()->split(vecEntries, strNewFilePath, pFormatVersion->m_uiRawVersion);
	}

	if (uiSelectedEntryCount > 0 && bDeleteSelectedEntriesFromSourceFile)
	{
		getTab()->setFileUnsaved(true);
	}

	string
		strLogPart3 = bDeleteSelectedEntriesFromSourceFile ? ", removing selected source entries" : "",
		strLogPart4 = iNewFileVersionOptionIndex == -1 ? "" : ", creating file with version " + pFormatVersion->m_strVersionText;
	getTab()->logf("Split %u entries into %s%s%s.", uiSelectedEntryCount, Path::getFileName(strNewFilePath).c_str(), strLogPart3.c_str(), strLogPart4.c_str());

	if (iNewFileVersionOptionIndex == -1)
	{
		delete pFormatVersion;
	}

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

	m_pTaskManager->onPauseTask();
	int32 iNewIMGVersionOptionIndex = getTab()->getLayer()->getWindow()->showDropDownWindow("Choose Output IMG Version", "Create output IMG with version (cancel for same version)", IMGManager::getVersionsText());
	m_pTaskManager->onResumeTask();
	EIMGVersion uiNewIMGVersion = IMGManager::getVersionFromVersionIndex(iNewIMGVersionOptionIndex);
	if (uiNewIMGVersion == IMG_UNKNOWN)
	{
		uiNewIMGVersion = getIMGTab()->getIMGFile()->getVersion();
	}

	bool bDeleteSelectedEntriesFromSourceIMG = showMessage("Also delete selected entries from source IMG?", "Delete Selected Entries?") == MB_OK;

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
	vector<FormatEntry*> vecEntries = (vector<FormatEntry*>&)vecIMGEntries;
	getIMGTab()->getIMGFile()->split(vecEntries, strNewFilePath, uiNewIMGVersion);

	vecIMGEntries = StdVector::removeDuplicates(vecIMGEntries);

	// delete source entries
	if (bDeleteSelectedEntriesFromSourceIMG)
	{
		getIMGTab()->removeSelectedEntries();
	}

	// mark IMG as modified
	if (vecIMGEntries.size() > 0 && bDeleteSelectedEntriesFromSourceIMG)
	{
		getIMGTab()->setFileUnsaved(true); // todo - rename to setUnsavedChanges(bool)
	}

	// log
	string
		strLogPart3 = bDeleteSelectedEntriesFromSourceIMG ? ", removing selected source entries" : "",
		strLogPart4 = iNewIMGVersionOptionIndex == -1 ? "" : ", creating IMG with version " + IMGManager::getVersionText(uiNewIMGVersion);
	getTab()->logf("Split %u entries by %u IDE files into %s%s%s.", vecIMGEntries.size(), vecIDEFilePaths.size(), Path::getFileName(strNewFilePath).c_str(), strLogPart3.c_str(), strLogPart4.c_str());

	onCompleteTask();
}

void		Tasks::splitByEntryNames(void)
{
	onStartTask("splitByEntryNames");

	m_pTaskManager->onPauseTask();
	string strInputEntryNames = m_pMainWindow->showMultiLineTextBoxWindow("Split by Entry Names", "Choose entry names to split, 1 per line.");
	m_pTaskManager->onResumeTask();
	if (strInputEntryNames == "")
	{
		return onAbortTask();
	}

	string strNewFilePath = saveFile(String::join(getTab()->getEditor()->getEditorFileFormats(), ","), "Split." + Path::getFileExtension(getTab()->getFile()->getFilePath()));
	if (strNewFilePath == "")
	{
		return onAbortTask();
	}

	vector<string> vecInputEntryNames = String::split(strInputEntryNames, "\n");
	for (string& strInputEntryName : vecInputEntryNames)
	{
		strInputEntryName = String::trim(strInputEntryName);
	}

	vector<FormatEntry*> vecEntries = getTab()->getContainerFile()->getEntriesByNames(vecInputEntryNames);

	EFileType uiEditorFileType = getTab()->getEditor()->getEditorFileType();
	vector<string> vecDropDownOptions = FormatVersionManager::get()->getEntriesVersionsText(uiEditorFileType);
	m_pTaskManager->onPauseTask();
	int32 iNewFileVersionOptionIndex = getTab()->getLayer()->getWindow()->showDropDownWindow("Choose Output File Version", "Create output file with version (cancel for same version)", vecDropDownOptions);
	m_pTaskManager->onResumeTask();

	FormatVersion *pFormatVersion = nullptr;
	if (iNewFileVersionOptionIndex == -1)
	{
		pFormatVersion = new FormatVersion;
		pFormatVersion->m_uiFileType = uiEditorFileType;
		pFormatVersion->m_uiRawVersion = getTab()->getContainerFile()->getRawVersion();
		pFormatVersion->m_uiFileType = uiEditorFileType;
	}
	else
	{
		pFormatVersion = FormatVersionManager::get()->getEntryByVersionText(vecDropDownOptions[iNewFileVersionOptionIndex]);
	}

	bool bDeleteSelectedEntriesFromSource = showMessage("Also delete split entries from source file?", "Delete Split Entries?") == MB_OK;

	getTab()->getContainerFile()->split(vecEntries, strNewFilePath, pFormatVersion->m_uiRawVersion);

	if (bDeleteSelectedEntriesFromSource)
	{
		getTab()->removeEntries(vecEntries);
	}

	if (vecEntries.size() > 0 && bDeleteSelectedEntriesFromSource)
	{
		getTab()->setFileUnsaved(true);
	}

	string
		strLogPart3 = bDeleteSelectedEntriesFromSource ? ", removing selected source entries" : "",
		strLogPart4 = iNewFileVersionOptionIndex == -1 ? "" : ", creating file with version " + pFormatVersion->m_strVersionText;
	getTab()->logf("Split %u entries into %s by entry names%s%s.", vecEntries.size(), Path::getFileName(strNewFilePath).c_str(), strLogPart3.c_str(), strLogPart4.c_str());

	if (iNewFileVersionOptionIndex == -1)
	{
		delete pFormatVersion;
	}

	onCompleteTask();
}

void		Tasks::convertIMGVersion(void)
{
	onStartTask("convertIMGVersion");

	EIMGVersion uiCurrentIMGVersion = getIMGTab()->getIMGFile()->getVersion();

	// show new version selection window
	m_pTaskManager->onPauseTask();
	int32 iNewIMGVersionOptionIndex = getTab()->getLayer()->getWindow()->showDropDownWindow("Convert IMG Version", "Convert IMG to version", IMGManager::getVersionsText());
	m_pTaskManager->onResumeTask();
	if (iNewIMGVersionOptionIndex == -1)
	{
		return onAbortTask();
	}
	EIMGVersion uiNewIMGVersion = IMGManager::getVersionFromVersionIndex(iNewIMGVersionOptionIndex);

	// check to remove DIR file
	if (uiCurrentIMGVersion == IMG_1)
	{
		// todo bool bRemoveDIRFile = getIMGTab()->getWindow()->showBoolWindow("Remove DIR file previously associated with IMG file?");
		bool bRemoveDIRFile = showMessage("Remove DIR file previously associated with IMG file?", "Remove DIR File?") == MB_OK;
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
		getIMGTab()->rebuild();
	}

	// render
	getIMGTab()->getIMGEditor()->refreshActiveTab();

	// set modified status
	getIMGTab()->setFileUnsaved(true);

	// log
	getTab()->logf("Converted IMG file to version %s.", IMGManager::getVersionText(uiNewIMGVersion, false).c_str());

	onCompleteTask();
}

void		Tasks::convertSelectedCOLVersion(void)
{
	onStartTask("convertSelectedCOLVersion");

	vector<string> vecDropDownOptions = { "COL 1", "COL 2", "COL 3", "COL 4" };
	m_pTaskManager->onPauseTask();
	int32 iNewCOLVersionOptionIndex = m_pMainWindow->showDropDownWindow("New COL Version", "Convert selected COL entries to version", vecDropDownOptions);
	m_pTaskManager->onResumeTask();
	if (iNewCOLVersionOptionIndex == -1)
	{
		return onAbortTask();
	}
	ECOLVersion uiNewCOLVersion = (ECOLVersion)(iNewCOLVersionOptionIndex + 1);

	uint32 uiSelectedRowCount = getTab()->getSelectedEntryCount();
	setMaxProgress(uiSelectedRowCount);

	uint32 uiConvertedEntryCount = 0;
	for (FormatEntry *pEntry : getTab()->getSelectedEntries())
	{
		IMGEntry *pIMGEntry = (IMGEntry*)pEntry;

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
		getTab()->setFileUnsaved(true);
	}

	getTab()->logf("Converted COL version to %u for %u entries.", uiNewCOLVersion, uiConvertedEntryCount);

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

	m_pTaskManager->onPauseTask();
	int32 iNewRWVersionOptionIndex = m_pMainWindow->showDropDownWindow("New DFF RW Version", "Convert selected DFF entries to RW version", vecDropDownOptions);
	m_pTaskManager->onResumeTask();
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
				for (RWSection *pRWSection : dffFile.VectorPool::getEntries())
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
		getIMGTab()->setFileUnsaved(true);
	}

	getTab()->logf("Converted DFF version to %s for %u entries.", strNewRWVersionText.c_str(), uiConvertedEntryCount);

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
		getIMGTab()->setFileUnsaved(true);
	}

	getTab()->logf("Converted %u DFF entries to WDR entries.", uiConvertedEntryCount);

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

	m_pTaskManager->onPauseTask();
	int32 iNewRWVersionOptionIndex = m_pMainWindow->showDropDownWindow("Convert TXD RW Version", "Convert selected TXD entries to RW version", vecDropDownOptions);
	m_pTaskManager->onResumeTask();
	if (iNewRWVersionOptionIndex == -1)
	{
		return onAbortTask();
	}
	RWVersion *pNewRWVersion = vecRWVersions[iNewRWVersionOptionIndex];
	uint32 uiNewRawRWVersion = pNewRWVersion->getRawVersion();
	string strNewRWVersionText = pNewRWVersion->getVersionTextWithGames();

	uint32 uiSelectedRowCount = getTab()->getSelectedEntryCount();
	setMaxProgress(uiSelectedRowCount);

	uint32 uiConvertedEntryCount = 0;
	EEditor uiEditorType = m_pMainWindow->getActiveEditor()->getEditorType();

	if (uiEditorType == IMG_EDITOR || uiEditorType == RADAR_EDITOR)
	{
		for (FormatEntry *pFormatEntry : getTab()->getSelectedEntries())
		{
			IMGEntry *pIMGEntry = (IMGEntry*)pFormatEntry;

			if (pIMGEntry->isTextureFile())
			{
				TXDFormat txdFile(pIMGEntry->getEntryData(), false);
				if (txdFile.unserialize())
				{
					for (RWSection *pRWSection : txdFile.VectorPool::getEntries())
					{
						pRWSection->setSectionRWVersion(uiNewRawRWVersion);
					}

					string strNewFileData = txdFile.serialize();
					pIMGEntry->setEntryData(strNewFileData);

					getTab()->onEntryChange(pFormatEntry);
					uiConvertedEntryCount++;
				}
				txdFile.unload();
			}

			increaseProgress();
		}
	}
	else if (uiEditorType == TEXTURE_EDITOR)
	{
		TextureEditorTab *pTextureEditorTab = (TextureEditorTab*)getTab();
		for (FormatEntry *pFormatEntry : getTab()->getSelectedEntries())
		{
			if (pTextureEditorTab->isTXDFile())
			{
				RWSection_TextureNative *pTextureNative = (RWSection_TextureNative*)pFormatEntry;
				pTextureNative->setSectionRWVersion(uiNewRawRWVersion);
			}

			getTab()->onEntryChange(pFormatEntry);
			uiConvertedEntryCount++;

			increaseProgress();
		}
	}

	if (uiSelectedRowCount > 0)
	{
		getTab()->setFileUnsaved(true);
		getTab()->setFileInfoText();
		getTab()->getLayer()->getWindow()->render();
	}

	getTab()->logf("Converted TXD version to %s for %u entries.", strNewRWVersionText.c_str(), uiConvertedEntryCount);

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

	m_pTaskManager->onPauseTask();
	int32 iNewPlatformedGameOptionIndex = m_pMainWindow->showDropDownWindow("Convert TXD to Game", "Convert selected TXD entries to game", vecDropDownOptions);
	m_pTaskManager->onResumeTask();
	if (iNewPlatformedGameOptionIndex == -1)
	{
		return onAbortTask();
	}
	PlatformedGame *pNewPlatformedGame = vecPlatformedGames[iNewPlatformedGameOptionIndex];
	EPlatformedGame uiNewPlatformedGame = pNewPlatformedGame->getPlatformedGameId();
	string strNewPlatformedGameText = pNewPlatformedGame->getText();

	uint32 uiSelectedRowCount = getTab()->getSelectedEntryCount();
	setMaxProgress(uiSelectedRowCount);

	uint32 uiConvertedEntryCount = 0;
	EEditor uiEditorType = m_pMainWindow->getActiveEditor()->getEditorType();

	if (uiEditorType == IMG_EDITOR || uiEditorType == RADAR_EDITOR)
	{
		for (FormatEntry *pEntry : getTab()->getSelectedEntries())
		{
			IMGEntry *pIMGEntry = (IMGEntry*)pEntry;

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
	}
	else if (uiEditorType == TEXTURE_EDITOR)
	{
		TextureEditorTab *pTextureEditorTab = (TextureEditorTab*)getTab();
		for (FormatEntry *pFormatEntry : getTab()->getSelectedEntries())
		{
			if (pTextureEditorTab->isTXDFile())
			{
				RWSection_TextureNative *pTextureNative = (RWSection_TextureNative*)pFormatEntry;
				vector<string> vecMipmapsRemoved;
				pTextureNative->convertToGame(uiNewPlatformedGame, vecMipmapsRemoved);
			}

			getTab()->onEntryChange(pFormatEntry);
			uiConvertedEntryCount++;

			increaseProgress();
		}
	}

	if (uiSelectedRowCount > 0)
	{
		getTab()->setFileUnsaved(true);
		getTab()->setFileInfoText();
		getTab()->recreateEntryList();
		getTab()->getLayer()->getWindow()->render();
	}

	getTab()->logf("Converted TXD to game %s for %u entries.", strNewPlatformedGameText.c_str(), uiConvertedEntryCount);

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

	m_pTaskManager->onPauseTask();
	int32 iNewTextureFormatOptionIndex = m_pMainWindow->showDropDownWindow("Convert TXD to Texture Format", "Convert selected TXD entries to texture format", vecDropDownOptions);
	m_pTaskManager->onResumeTask();
	if (iNewTextureFormatOptionIndex == -1)
	{
		return onAbortTask();
	}
	RasterDataFormat *pNewRasterDataFormat = vecRasterDataFormats[iNewTextureFormatOptionIndex];
	ERasterDataFormat uiNewRasterDataFormat = pNewRasterDataFormat->getRasterDataFormatId();
	string strNewRasterDataFormatText = pNewRasterDataFormat->getText();

	uint32 uiSelectedRowCount = getTab()->getSelectedEntryCount();
	setMaxProgress(uiSelectedRowCount);

	uint32 uiConvertedEntryCount = 0;
	EEditor uiEditorType = m_pMainWindow->getActiveEditor()->getEditorType();

	if (uiEditorType == IMG_EDITOR || uiEditorType == RADAR_EDITOR)
	{
		for (FormatEntry *pEntry : getTab()->getSelectedEntries())
		{
			IMGEntry *pIMGEntry = (IMGEntry*)pEntry;

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
	}
	else if (uiEditorType == TEXTURE_EDITOR)
	{
		TextureEditorTab *pTextureEditorTab = (TextureEditorTab*)getTab();
		for (FormatEntry *pFormatEntry : getTab()->getSelectedEntries())
		{
			if (pTextureEditorTab->isTXDFile())
			{
				RWSection_TextureNative *pTextureNative = (RWSection_TextureNative*)pFormatEntry;
				vector<string> vecMipmapsRemoved;
				pTextureNative->convertToRasterDataFormat(pNewRasterDataFormat->getRasterDataFormatId(), vecMipmapsRemoved);
			}

			getTab()->onEntryChange(pFormatEntry);
			uiConvertedEntryCount++;

			increaseProgress();
		}
	}

	if (uiSelectedRowCount > 0)
	{
		getTab()->setFileUnsaved(true);
		getTab()->setFileInfoText();
		getTab()->recreateEntryList();
		getTab()->getLayer()->getWindow()->render();
	}

	getTab()->logf("Converted TXD to texture format %s for %u entries.", strNewRasterDataFormatText.c_str(), uiConvertedEntryCount);

	onCompleteTask();
}

void			Tasks::convertWTDFileToTXDFile(void)
{
	onStartTask("convertWTDFileToTXDFile");

	uint32 uiSelectedRowCount = getTab()->getSelectedEntryCount();
	setMaxProgress(uiSelectedRowCount);

	uint32 uiConvertedEntryCount = 0;
	EEditor uiEditorType = m_pMainWindow->getActiveEditor()->getEditorType();

	if (uiEditorType == IMG_EDITOR || uiEditorType == RADAR_EDITOR)
	{
		for (FormatEntry *pEntry : getTab()->getSelectedEntries())
		{
			IMGEntry *pIMGEntry = (IMGEntry*)pEntry;

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
	}
	else if (uiEditorType == TEXTURE_EDITOR)
	{
		TextureEditorTab *pTextureEditorTab = (TextureEditorTab*)getTab();

		WTDFormat *pWTDFile = (WTDFormat *)getTab()->getFile();

		IntermediateTextureFormat *pGeneralTextureFile = pWTDFile->convertToIntermediateFormat();
		TXDFormat *pTXDFile = TXDManager::get()->convertIntermediateTextureFileToTXDFile(pGeneralTextureFile);
		pGeneralTextureFile->unload();
		delete pGeneralTextureFile;
		string strTXDFileData = pTXDFile->serialize();
		pTXDFile->unload();
		delete pTXDFile;

		string strWTDFilePath = pWTDFile->getFilePath();
		string strTXDFilePath = Path::replaceFileExtensionWithCase(strWTDFilePath, "TXD");
		Editor *pEditor = pTextureEditorTab->getEditor();

		File::setBinaryFile(strTXDFilePath, strTXDFileData);
		
		pEditor->removeEditorTab(pTextureEditorTab);
		if (pEditor->addEditorTab(strTXDFilePath))
		{
			uiConvertedEntryCount++;
		}
	}

	if (uiConvertedEntryCount > 0)
	{
		getTab()->setFileUnsaved(true);
		getTab()->setFileInfoText();
		getTab()->getLayer()->getWindow()->render();
	}

	getTab()->logf("Converted %u WTD entries to TXD entries.", uiConvertedEntryCount);

	onCompleteTask();
}

void		Tasks::selectAll(void)
{
	onStartTask("selectAll");

	EEditor uiEditorType = getTab()->getEditor()->getEditorType();
	if (uiEditorType == ITEM_DEFINITION_EDITOR || uiEditorType == ITEM_PLACEMENT_EDITOR || uiEditorType == DAT_EDITOR)
	{
		getTab()->setAllLinesSelected(true);
	}
	else
	{
		getTab()->setEntriesSelected(getTab()->getEntriesRef(), true);
	}
	getTab()->log("Selected all entries.");

	onCompleteTask();
}

void		Tasks::unselectAll(void)
{
	onStartTask("unselectAll");

	EEditor uiEditorType = getTab()->getEditor()->getEditorType();
	if (uiEditorType == ITEM_DEFINITION_EDITOR || uiEditorType == ITEM_PLACEMENT_EDITOR || uiEditorType == DAT_EDITOR)
	{
		getTab()->setAllLinesSelected(false);
	}
	else
	{
		getTab()->setEntriesSelected(getTab()->getEntriesRef(), false);
	}
	getTab()->log("Unselected all entries.");

	onCompleteTask();
}

void		Tasks::selectInverse(void)
{
	onStartTask("selectInverse");

	EEditor uiEditorType = getTab()->getEditor()->getEditorType();
	if (uiEditorType == ITEM_DEFINITION_EDITOR || uiEditorType == ITEM_PLACEMENT_EDITOR || uiEditorType == DAT_EDITOR)
	{
		//getTab()->setAllLinesSelected(!getTab()->m_pTextBox->isTextSelected());
	}
	else
	{
		for (FormatEntry *pEntry : getTab()->getEntriesRef())
		{
			getTab()->setEntrySelected(pEntry, !getTab()->isEntrySelected(pEntry));
		}
	}

	getTab()->log("Selected inverse entries.");

	onCompleteTask();
}

void		Tasks::selectByIndex(void)
{
	onStartTask("selectByIndex");

	m_pTaskManager->onPauseTask();
	NumericMultiOptionInputLayerResult nmoir = m_pMainWindow->showNumericMultiOptionWindow("Select Entries by Index", "Select entries with an index");
	m_pTaskManager->onResumeTask();
	if (nmoir.m_bCancelled)
	{
		return onAbortTask();
	}

	uint32 uiTotalEntryCount = getTab()->getTotalEntryCount();
	setMaxProgress(uiTotalEntryCount * 2);

	vector<FormatEntry*> vecEntries = getTab()->getEntriesByNumericMultiOptionValues(0, nmoir.m_uiOptionIndex, nmoir.m_uiTextBoxValue1, nmoir.m_uiTextBoxValue2); // todo - magic int
	setMaxProgress(uiTotalEntryCount + vecEntries.size(), false);
	getTab()->setEntriesSelected(vecEntries, true);

	getTab()->logf("Selected %u entries with an index %s.", vecEntries.size(), nmoir.getMessageText().c_str());

	onCompleteTask();
}

void		Tasks::selectByName(void)
{
	onStartTask("selectByName");

	m_pTaskManager->onPauseTask();
	string strEntryNameInput = m_pMainWindow->showSingleLineTextBoxWindow("Select Entries by Name", "Select entries with a name that includes:");
	m_pTaskManager->onResumeTask();
	if (strEntryNameInput == "")
	{
		return onAbortTask();
	}

	uint32 uiTotalEntryCount = getTab()->getFile()->getEntryCount();
	setMaxProgress(uiTotalEntryCount * 2);

	vector<FormatEntry*> vecEntries = getTab()->getContainerFile()->getEntriesByName(strEntryNameInput, true);
	setMaxProgress(uiTotalEntryCount + vecEntries.size(), false); // todo - increaseMaxProgress
	getTab()->setEntriesSelected(vecEntries, true);

	getTab()->logf("Selected %u entries with a name that includes %s.", vecEntries.size(), strEntryNameInput.c_str());

	onCompleteTask();
}

void		Tasks::selectByOffset(void)
{
	onStartTask("selectByOffset");

	m_pTaskManager->onPauseTask();
	NumericMultiOptionInputLayerResult nmoir = m_pMainWindow->showNumericMultiOptionWindow("Select Entries by Offset", "Select entries with an offset");
	m_pTaskManager->onResumeTask();
	if (nmoir.m_bCancelled)
	{
		return onAbortTask();
	}

	uint32 uiTotalEntryCount = getTab()->getFile()->getEntryCount();
	setMaxProgress(uiTotalEntryCount * 2);

	vector<FormatEntry*> vecEntries = getTab()->getEntriesByNumericMultiOptionValues(2, nmoir.m_uiOptionIndex, nmoir.m_uiTextBoxValue1, nmoir.m_uiTextBoxValue2); // todo - magic int
	setMaxProgress(uiTotalEntryCount + vecEntries.size(), false);
	getTab()->setEntriesSelected(vecEntries, true);

	getTab()->logf("Selected %u entries with an offset %s.", vecEntries.size(), nmoir.getMessageText().c_str());

	onCompleteTask();
}

void		Tasks::selectBySize(void)
{
	onStartTask("selectBySize");

	m_pTaskManager->onPauseTask();
	NumericMultiOptionInputLayerResult nmoir = m_pMainWindow->showNumericMultiOptionWindow("Select Entries by Size", "Select entries with a size");
	m_pTaskManager->onResumeTask();
	if (nmoir.m_bCancelled)
	{
		return onAbortTask();
	}

	uint32 uiTotalEntryCount = getTab()->getFile()->getEntryCount();
	setMaxProgress(uiTotalEntryCount * 2);

	vector<FormatEntry*> vecEntries = getTab()->getEntriesByNumericMultiOptionValues(3, nmoir.m_uiOptionIndex, nmoir.m_uiTextBoxValue1, nmoir.m_uiTextBoxValue2); // todo - magic int
	setMaxProgress(uiTotalEntryCount + vecEntries.size(), false);
	getTab()->setEntriesSelected(vecEntries, true);

	getTab()->logf("Selected %u entries with a size %s.", vecEntries.size(), nmoir.getMessageText().c_str());

	onCompleteTask();
}

void		Tasks::selectByType(void)
{
	onStartTask("selectByType");

	m_pTaskManager->onPauseTask();
	string strEntryTypeInput = m_pMainWindow->showSingleLineTextBoxWindow("Select Entries by Type", "Select entries with a type that includes:");
	m_pTaskManager->onResumeTask();
	if (strEntryTypeInput == "")
	{
		return onAbortTask();
	}

	uint32 uiTotalEntryCount = getTab()->getFile()->getEntryCount();
	setMaxProgress(uiTotalEntryCount * 2);

	vector<FormatEntry*> vecEntries = getTab()->getContainerFile()->getEntriesByExtension(strEntryTypeInput, true);
	setMaxProgress(uiTotalEntryCount + vecEntries.size(), false); // todo - increaseMaxProgress
	getTab()->setEntriesSelected(vecEntries, true);

	getTab()->logf("Selected %u entries with a type that includes %s.", vecEntries.size(), strEntryTypeInput.c_str());

	onCompleteTask();
}

void		Tasks::selectByVersion(void)
{
	onStartTask("selectByVersion");

	vector<string> vecEntriesVersionsText = FormatVersionManager::get()->getEntriesVersionsText();
	m_pTaskManager->onPauseTask();
	int32 iVersionOptionIndex = m_pMainWindow->showDropDownWindow("Select Entries by Version", "Select entries with version", vecEntriesVersionsText);
	m_pTaskManager->onResumeTask();
	if (iVersionOptionIndex == -1)
	{
		return onAbortTask();
	}

	uint32 uiTotalEntryCount = getTab()->getFile()->getEntryCount();
	setMaxProgress(uiTotalEntryCount * 2);

	FormatVersion
		*pEntryVersion = FormatVersionManager::get()->getEntryByVersionText(vecEntriesVersionsText[iVersionOptionIndex]);
	vector<FormatEntry*>
		vecEntries = getTab()->getContainerFile()->getEntriesByVersion(pEntryVersion->m_uiFileType, pEntryVersion->m_uiRawVersion);
	setMaxProgress(uiTotalEntryCount + vecEntries.size(), false); // todo - increaseMaxProgress
	getTab()->setEntriesSelected(vecEntries, true);

	getTab()->logf("Selected %u entries with version %s.", vecEntries.size(), pEntryVersion->m_strVersionText.c_str());

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

	vecIMGEntries = StdVector::removeDuplicates(vecIMGEntries);

	// export the IMG entries
	setMaxProgress((vecIDEFilePaths.size() * 2) + getIMGTab()->getIMGFile()->getEntryCount() + vecIMGEntries.size());
	for (IMGEntry *pIMGEntry : vecIMGEntries)
	{
		getIMGTab()->getEntryGrid()->getRowByUserData((uint32)pIMGEntry)->setSelected(true);
		increaseProgress();
	}
	getIMGTab()->getEntryGrid()->setActiveItem();

	getTab()->logf("Selected %u entries by %u IDE files.", vecIMGEntries.size(), vecIDEFilePaths.size());

	onCompleteTask();
}

void		Tasks::unselectByIndex(void)
{
	onStartTask("unselectByIndex");

	m_pTaskManager->onPauseTask();
	NumericMultiOptionInputLayerResult nmoir = m_pMainWindow->showNumericMultiOptionWindow("Unselect Entries by Index", "Unselect entries with an index");
	m_pTaskManager->onResumeTask();
	if (nmoir.m_bCancelled)
	{
		return onAbortTask();
	}

	uint32 uiTotalEntryCount = getTab()->getFile()->getEntryCount();
	setMaxProgress(uiTotalEntryCount * 2);

	vector<FormatEntry*> vecEntries = getTab()->getEntriesByNumericMultiOptionValues(0, nmoir.m_uiOptionIndex, nmoir.m_uiTextBoxValue1, nmoir.m_uiTextBoxValue2); // todo - magic int
	setMaxProgress(uiTotalEntryCount + vecEntries.size(), false);
	getTab()->setEntriesSelected(vecEntries, false);

	getTab()->logf("Unselected %u entries with an index %s.", vecEntries.size(), nmoir.getMessageText().c_str());

	onCompleteTask();
}

void		Tasks::unselectByName(void)
{
	onStartTask("unselectByName");

	m_pTaskManager->onPauseTask();
	string strEntryNameInput = m_pMainWindow->showSingleLineTextBoxWindow("Unselect Entries by Name", "Unselect entries with a name that includes:");
	m_pTaskManager->onResumeTask();
	if (strEntryNameInput == "")
	{
		return onAbortTask();
	}

	uint32 uiTotalEntryCount = getTab()->getFile()->getEntryCount();
	setMaxProgress(uiTotalEntryCount * 2);

	vector<FormatEntry*> vecEntries = getTab()->getContainerFile()->getEntriesByName(strEntryNameInput, true);
	setMaxProgress(uiTotalEntryCount + vecEntries.size(), false); // todo - increaseMaxProgress
	getTab()->setEntriesSelected(vecEntries, false);

	getTab()->logf("Unselected %u entries with a name that includes %s.", vecEntries.size(), strEntryNameInput.c_str());

	onCompleteTask();
}

void		Tasks::unselectByOffset(void)
{
	onStartTask("unselectByOffset");

	m_pTaskManager->onPauseTask();
	NumericMultiOptionInputLayerResult nmoir = m_pMainWindow->showNumericMultiOptionWindow("Unselect Entries by Offset", "Unselect entries with an offset");
	m_pTaskManager->onResumeTask();
	if (nmoir.m_bCancelled)
	{
		return onAbortTask();
	}

	uint32 uiTotalEntryCount = getTab()->getFile()->getEntryCount();
	setMaxProgress(uiTotalEntryCount * 2);

	vector<FormatEntry*> vecEntries = getTab()->getEntriesByNumericMultiOptionValues(2, nmoir.m_uiOptionIndex, nmoir.m_uiTextBoxValue1, nmoir.m_uiTextBoxValue2); // todo - magic int
	setMaxProgress(uiTotalEntryCount + vecEntries.size(), false);
	getTab()->setEntriesSelected(vecEntries, false);

	getTab()->logf("Unselected %u entries with an offset %s.", vecEntries.size(), nmoir.getMessageText().c_str());

	onCompleteTask();
}

void		Tasks::unselectBySize(void)
{
	onStartTask("unselectBySize");

	m_pTaskManager->onPauseTask();
	NumericMultiOptionInputLayerResult nmoir = m_pMainWindow->showNumericMultiOptionWindow("Unselect Entries by Size", "Unselect entries with a size");
	m_pTaskManager->onResumeTask();
	if (nmoir.m_bCancelled)
	{
		return onAbortTask();
	}

	uint32 uiTotalEntryCount = getTab()->getFile()->getEntryCount();
	setMaxProgress(uiTotalEntryCount * 2);

	vector<FormatEntry*> vecEntries = getTab()->getEntriesByNumericMultiOptionValues(3, nmoir.m_uiOptionIndex, nmoir.m_uiTextBoxValue1, nmoir.m_uiTextBoxValue2); // todo - magic int
	setMaxProgress(uiTotalEntryCount + vecEntries.size(), false);
	getTab()->setEntriesSelected(vecEntries, false);

	getTab()->logf("Unselected %u entries with a size %s.", vecEntries.size(), nmoir.getMessageText().c_str());

	onCompleteTask();
}

void		Tasks::unselectByType(void)
{
	onStartTask("unselectByType");

	m_pTaskManager->onPauseTask();
	string strEntryTypeInput = m_pMainWindow->showSingleLineTextBoxWindow("Unselect Entries by Type", "Unselect entries with a type that includes:");
	m_pTaskManager->onResumeTask();
	if (strEntryTypeInput == "")
	{
		return onAbortTask();
	}

	uint32 uiTotalEntryCount = getTab()->getFile()->getEntryCount();
	setMaxProgress(uiTotalEntryCount * 2);

	vector<FormatEntry*> vecEntries = getTab()->getContainerFile()->getEntriesByExtension(strEntryTypeInput, true);
	setMaxProgress(uiTotalEntryCount + vecEntries.size(), false); // todo - increaseMaxProgress
	getTab()->setEntriesSelected(vecEntries, false);

	getTab()->logf("Unselected %u entries with a type that includes %s.", vecEntries.size(), strEntryTypeInput.c_str());

	onCompleteTask();
}

void		Tasks::unselectByVersion(void)
{
	onStartTask("unselectByVersion");

	vector<string> vecEntriesVersionsText = FormatVersionManager::get()->getEntriesVersionsText();
	m_pTaskManager->onPauseTask();
	int32 iVersionOptionIndex = m_pMainWindow->showDropDownWindow("Unselect Entries by Version", "Unselect entries with version", vecEntriesVersionsText);
	m_pTaskManager->onResumeTask();
	if (iVersionOptionIndex == -1)
	{
		return onAbortTask();
	}

	uint32 uiTotalEntryCount = getTab()->getFile()->getEntryCount();
	setMaxProgress(uiTotalEntryCount * 2);

	FormatVersion
		*pEntryVersion = FormatVersionManager::get()->getEntryByVersionText(vecEntriesVersionsText[iVersionOptionIndex]);
	vector<FormatEntry*>
		vecEntries = getTab()->getContainerFile()->getEntriesByVersion(pEntryVersion->m_uiFileType, pEntryVersion->m_uiRawVersion);
	setMaxProgress(uiTotalEntryCount + vecEntries.size(), false); // todo - increaseMaxProgress
	getTab()->setEntriesSelected(vecEntries, false);

	getTab()->logf("Unselected %u entries with version %s.", vecEntries.size(), pEntryVersion->m_strVersionText.c_str());

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

	vecIMGEntries = StdVector::removeDuplicates(vecIMGEntries);

	// export the IMG entries
	setMaxProgress((vecIDEFilePaths.size() * 2) + getIMGTab()->getIMGFile()->getEntryCount() + vecIMGEntries.size());
	for (IMGEntry *pIMGEntry : vecIMGEntries)
	{
		getIMGTab()->getEntryGrid()->getRowByUserData((uint32)pIMGEntry)->setSelected(false);
		increaseProgress();
	}
	getIMGTab()->getEntryGrid()->setActiveItem();

	getTab()->logf("Unselected %u entries by %u IDE files.", vecIMGEntries.size(), vecIDEFilePaths.size());

	onCompleteTask();
}

void		Tasks::sortByIndexReverse(void)
{
	onStartTask("sortByIndexReverse");

	uint32 uiTotalEntryCount = getTab()->getTotalEntryCount();
	setMaxProgress(uiTotalEntryCount);

	unordered_map<FormatEntry*, uint32> umapEntryIndexes;
	vector<FormatEntry*>& vecEntries = getTab()->getEntriesRef();
	for (FormatEntry *pEntry : vecEntries)
	{
		umapEntryIndexes[pEntry] = StdVector::findKey(vecEntries, pEntry);
	}

	auto sortEntries_IndexReverse = [&](FormatEntry *pEntry1, FormatEntry *pEntry2) -> bool
	{
		return umapEntryIndexes[pEntry1] > umapEntryIndexes[pEntry2];
	};
	std::sort(vecEntries.begin(), vecEntries.end(), sortEntries_IndexReverse);
	getTab()->onSortEntries(vecEntries);

	if (uiTotalEntryCount > 0)
	{
		getTab()->recreateEntryList();
		getTab()->setFileUnsaved(true);
	}

	getTab()->log("Sorted all entries by index (reverse).");

	onCompleteTask();
}

void		Tasks::sortByNameAscending09AZ(void)
{
	onStartTask("sortByNameAscending09AZ");

	uint32 uiTotalEntryCount = getTab()->getTotalEntryCount();
	setMaxProgress(uiTotalEntryCount);

	auto sortEntries_NameAscending09AZ = [](FormatEntry *pEntry1, FormatEntry *pEntry2) -> bool
	{
		return strcmp(String::toLowerCase(pEntry1->getEntryName()).c_str(), String::toLowerCase(pEntry2->getEntryName()).c_str()) < 0;
	};
	std::sort(getTab()->getEntriesRef().begin(), getTab()->getEntriesRef().end(), sortEntries_NameAscending09AZ);
	getTab()->onSortEntries(getTab()->getEntriesRef());

	if (uiTotalEntryCount > 0)
	{
		getTab()->recreateEntryList();
		getTab()->setFileUnsaved(true);
	}

	getTab()->log("Sorted all entries by name (ascending 0-9 A-Z).");

	onCompleteTask();
}

void		Tasks::sortByNameAscendingAZ09(void)
{
	// todo
	/*
	onStartTask("sortByNameAscendingAZ09");

	uint32 uiTotalEntryCount = getTab()->getTotalEntryCount();
	setMaxProgress(uiTotalEntryCount);

	auto sortEntries_NameAscendingAZ09 = [](FormatEntry *pEntry1, FormatEntry *pEntry2) -> bool
	{
		const char
			*pEntryName1 = pEntry1->getEntryName().c_str(),
			*pEntryName2 = pEntry2->getEntryName().c_str();
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
	std::sort(getTab()->getEntriesRef().begin(), getTab()->getEntriesRef().end(), sortEntries_NameAscendingAZ09);
	getTab()->onSortEntries(getTab()->getEntriesRef());

	if (uiTotalEntryCount > 0)
	{
		getTab()->recreateEntryList();
		getTab()->setFileUnsaved(true);
	}

	getTab()->log("Sorted all entries by name (ascending A-Z 0-9).");

	onCompleteTask();
	*/
}


void		Tasks::sortByNameDescendingZA90(void)
{
	onStartTask("sortByNameDescendingZA90");

	uint32 uiTotalEntryCount = getTab()->getTotalEntryCount();
	setMaxProgress(uiTotalEntryCount);

	auto sortEntries_NameDescendingZA90 = [](FormatEntry *pEntry1, FormatEntry *pEntry2) -> bool
	{
		return strcmp(String::toLowerCase(pEntry1->getEntryName()).c_str(), String::toLowerCase(pEntry2->getEntryName()).c_str()) > 0;
	};
	std::sort(getTab()->getEntriesRef().begin(), getTab()->getEntriesRef().end(), sortEntries_NameDescendingZA90);
	getTab()->onSortEntries(getTab()->getEntriesRef());

	if (uiTotalEntryCount > 0)
	{
		getTab()->recreateEntryList();
		getTab()->setFileUnsaved(true);
	}

	getTab()->log("Sorted all entries by name (descending Z-A 9-0).");

	onCompleteTask();
}

void		Tasks::sortByNameDescending90ZA(void)
{
	// todo
}

void		Tasks::sortByOffsetLowHigh(void)
{
	onStartTask("sortByOffsetLowHigh");

	uint32 uiTotalEntryCount = getTab()->getTotalEntryCount();
	setMaxProgress(uiTotalEntryCount);

	auto sortEntries_OffsetLowToHigh = [](FormatEntry *pEntry1, FormatEntry *pEntry2) -> bool
	{
		return pEntry1->getEntryOffset() < pEntry2->getEntryOffset();
	};
	std::sort(getTab()->getEntriesRef().begin(), getTab()->getEntriesRef().end(), sortEntries_OffsetLowToHigh);
	getTab()->onSortEntries(getTab()->getEntriesRef());

	if (uiTotalEntryCount > 0)
	{
		getTab()->recreateEntryList();
		getTab()->setFileUnsaved(true);
	}

	getTab()->log("Sorted all entries by offset (low to high).");

	onCompleteTask();
}

void		Tasks::sortByOffsetHighLow(void)
{
	onStartTask("sortByOffsetHighLow");

	uint32 uiTotalEntryCount = getTab()->getTotalEntryCount();
	setMaxProgress(uiTotalEntryCount);

	auto sortEntries_OffsetHighToLow = [](FormatEntry *pEntry1, FormatEntry *pEntry2) -> bool
	{
		return pEntry1->getEntryOffset() > pEntry2->getEntryOffset();
	};
	std::sort(getTab()->getEntriesRef().begin(), getTab()->getEntriesRef().end(), sortEntries_OffsetHighToLow);
	getTab()->onSortEntries(getTab()->getEntriesRef());

	if (uiTotalEntryCount > 0)
	{
		getTab()->recreateEntryList();
		getTab()->setFileUnsaved(true);
	}

	getTab()->log("Sorted all entries by offset (high to low).");

	onCompleteTask();
}

void		Tasks::sortBySizeSmallBig(void)
{
	onStartTask("sortBySizeSmallBig");

	uint32 uiTotalEntryCount = getTab()->getTotalEntryCount();
	setMaxProgress(uiTotalEntryCount);

	auto sortEntries_SizeSmallToBig = [](FormatEntry *pEntry1, FormatEntry *pEntry2) -> bool
	{
		return pEntry1->getEntrySize() < pEntry2->getEntrySize();
	};
	std::sort(getTab()->getEntriesRef().begin(), getTab()->getEntriesRef().end(), sortEntries_SizeSmallToBig);
	getTab()->onSortEntries(getTab()->getEntriesRef());

	if (uiTotalEntryCount > 0)
	{
		getTab()->recreateEntryList();
		getTab()->setFileUnsaved(true);
	}

	getTab()->log("Sorted all entries by size (small to big).");

	onCompleteTask();
}

void		Tasks::sortBySizeBigSmall(void)
{
	onStartTask("sortBySizeBigSmall");

	uint32 uiTotalEntryCount = getTab()->getTotalEntryCount();
	setMaxProgress(uiTotalEntryCount);

	auto sortEntries_SizeBigToSmall = [](FormatEntry *pEntry1, FormatEntry *pEntry2) -> bool
	{
		return pEntry1->getEntrySize() > pEntry2->getEntrySize();
	};
	std::sort(getTab()->getEntriesRef().begin(), getTab()->getEntriesRef().end(), sortEntries_SizeBigToSmall);
	getTab()->onSortEntries(getTab()->getEntriesRef());

	if (uiTotalEntryCount > 0)
	{
		getTab()->recreateEntryList();
		getTab()->setFileUnsaved(true);
	}

	getTab()->log("Sorted all entries by size (big to small).");

	onCompleteTask();
}

void		Tasks::sortByTypeAZ(void)
{
	onStartTask("sortByTypeAZ");

	uint32 uiTotalEntryCount = getTab()->getTotalEntryCount();
	setMaxProgress(uiTotalEntryCount);

	auto sortEntries_TypeAscending09AZ = [](FormatEntry *pEntry1, FormatEntry *pEntry2) -> bool
	{
		return strcmp(String::toLowerCase(pEntry1->getEntryExtension()).c_str(), String::toLowerCase(pEntry2->getEntryExtension()).c_str()) < 0;
	};
	std::sort(getTab()->getEntriesRef().begin(), getTab()->getEntriesRef().end(), sortEntries_TypeAscending09AZ);
	getTab()->onSortEntries(getTab()->getEntriesRef());

	if (uiTotalEntryCount > 0)
	{
		getTab()->recreateEntryList();
		getTab()->setFileUnsaved(true);
	}

	getTab()->log("Sorted all entries by type (ascending 0-9 A-Z).");

	onCompleteTask();
}

void		Tasks::sortByTypeZA(void)
{
	onStartTask("sortByTypeZA");

	uint32 uiTotalEntryCount = getTab()->getTotalEntryCount();
	setMaxProgress(uiTotalEntryCount);

	auto sortEntries_TypeDescendingZA90 = [](FormatEntry *pEntry1, FormatEntry *pEntry2) -> bool
	{
		return strcmp(String::toLowerCase(pEntry1->getEntryExtension()).c_str(), String::toLowerCase(pEntry2->getEntryExtension()).c_str()) > 0;
	};
	std::sort(getTab()->getEntriesRef().begin(), getTab()->getEntriesRef().end(), sortEntries_TypeDescendingZA90);
	getTab()->onSortEntries(getTab()->getEntriesRef());

	if (uiTotalEntryCount > 0)
	{
		getTab()->recreateEntryList();
		getTab()->setFileUnsaved(true);
	}

	getTab()->log("Sorted all entries by type (descending Z-A 9-0).");

	onCompleteTask();
}

void		Tasks::sortByVersionOldNew(void)
{
	onStartTask("sortByVersionOldNew");

	uint32 uiTotalEntryCount = getTab()->getTotalEntryCount();
	setMaxProgress(uiTotalEntryCount);

	auto sortEntries_VersionOldToNew = [](FormatEntry *pEntry1, FormatEntry *pEntry2) -> bool
	{
		return pEntry1->getRawVersion() < pEntry2->getRawVersion();
	};
	std::sort(getTab()->getEntriesRef().begin(), getTab()->getEntriesRef().end(), sortEntries_VersionOldToNew);
	getTab()->onSortEntries(getTab()->getEntriesRef());

	if (uiTotalEntryCount > 0)
	{
		getTab()->recreateEntryList();
		getTab()->setFileUnsaved(true);
	}

	getTab()->log("Sorted all entries by version (old to new).");

	onCompleteTask();
}

void		Tasks::sortByVersionNewOld(void)
{
	onStartTask("sortByVersionNewOld");

	uint32 uiTotalEntryCount = getTab()->getTotalEntryCount();
	setMaxProgress(uiTotalEntryCount);

	auto sortEntries_VersionNewToOld = [](FormatEntry *pEntry1, FormatEntry *pEntry2) -> bool
	{
		return pEntry1->getRawVersion() > pEntry2->getRawVersion();
	};
	std::sort(getTab()->getEntriesRef().begin(), getTab()->getEntriesRef().end(), sortEntries_VersionNewToOld);
	getTab()->onSortEntries(getTab()->getEntriesRef());

	if (uiTotalEntryCount > 0)
	{
		getTab()->recreateEntryList();
		getTab()->setFileUnsaved(true);
	}

	getTab()->log("Sorted all entries by version (new to old).");

	onCompleteTask();
}

void		Tasks::sortByIDE(void)
{
	onStartTask("sortByIDE");

	vector<string> vecIDEFilePaths = openFile("ide", false);
	if (vecIDEFilePaths.size() == 0)
	{
		return onAbortTask();
	}

	IDEFormat ideFile(vecIDEFilePaths[0]);
	if (!ideFile.unserialize())
	{
		ideFile.unload();
	}

	uint32 uiTotalEntryCount = getIMGTab()->getEntryGrid()->getEntryCount();
	setMaxProgress(uiTotalEntryCount);

	VectorPool<string> vecModelNamesInIDEFile;
	vecModelNamesInIDEFile.setEntries(StdVector::toLowerCase(ideFile.getModelNames()));

	auto sortIMGEntries_IDEFile = [&](IMGEntry *pIMGEntry1, IMGEntry *pIMGEntry2) -> bool
	{
		return vecModelNamesInIDEFile.getIndexByEntry(String::toLowerCase(pIMGEntry1->getEntryName())) < vecModelNamesInIDEFile.getIndexByEntry(String::toLowerCase(pIMGEntry2->getEntryName()));
	};
	std::sort(getIMGTab()->getIMGFile()->VectorPool::getEntries().begin(), getIMGTab()->getIMGFile()->VectorPool::getEntries().end(), sortIMGEntries_IDEFile);
	getTab()->onSortEntries(getTab()->getEntriesRef());

	if (uiTotalEntryCount > 0)
	{
		getIMGTab()->readdGridEntries();
		getIMGTab()->setFileUnsaved(true);
	}

	getTab()->log("Sorted all entries by IDE file " + Path::getFileName(vecIDEFilePaths[0]) + ".");

	onCompleteTask();
}

void		Tasks::sortByCOL(void)
{
	onStartTask("sortByCOL");

	vector<string> vecCOLFilePaths = openFile("col", false);
	if (vecCOLFilePaths.size() == 0)
	{
		return onAbortTask();
	}

	COLFormat colFile(vecCOLFilePaths[0]);
	if (!colFile.unserialize())
	{
		colFile.unload();
	}

	uint32 uiTotalEntryCount = getIMGTab()->getEntryGrid()->getEntryCount();
	setMaxProgress(uiTotalEntryCount);

	VectorPool<string> vecModelNamesInCOLFile;
	vecModelNamesInCOLFile.setEntries(StdVector::toLowerCase(colFile.getModelNames()));

	auto sortIMGEntries_COLFile = [&](IMGEntry *pIMGEntry1, IMGEntry *pIMGEntry2) -> bool
	{
		return vecModelNamesInCOLFile.getIndexByEntry(String::toLowerCase(pIMGEntry1->getEntryName())) < vecModelNamesInCOLFile.getIndexByEntry(String::toLowerCase(pIMGEntry2->getEntryName()));
	};
	std::sort(getIMGTab()->getIMGFile()->VectorPool::getEntries().begin(), getIMGTab()->getIMGFile()->VectorPool::getEntries().end(), sortIMGEntries_COLFile);
	getTab()->onSortEntries(getTab()->getEntriesRef());

	if (uiTotalEntryCount > 0)
	{
		getIMGTab()->readdGridEntries();
		getIMGTab()->setFileUnsaved(true);
	}

	getTab()->log("Sorted all entries by COL file " + Path::getFileName(vecCOLFilePaths[0]) + ".");

	onCompleteTask();
}

void		Tasks::sortByMultipleTypes(void)
{
	onStartTask("sortByMultipleTypes");
	
	uint32
		uiSortTypeIndex = 0;
	vector<string>
		vecIDEFilePaths,
		vecCOLFilePaths,
		vecIDEModelNamesUpper,
		vecCOLModelNamesUpper,
		vecDropDownOptions = {
			"Index",
			"Type",
			"Name",
			"Offset",
			"Size",
			"Version",
			"IDE",
			"COL"
		};
	vector<int32>
		vecSortTypes;
	while (uiSortTypeIndex < 10)
	{
		int32 iSortType = m_pMainWindow->showDropDownWindow("Sort Type #" + String::toString(uiSortTypeIndex), "Choose a sort type for sort index " + String::toString(uiSortTypeIndex), vecDropDownOptions);
		if (iSortType == -1)
		{
			break;
		}

		if (iSortType == 6)
		{
			vecIDEFilePaths = openFile("IDE");
			vecIDEModelNamesUpper = IDEManager::get()->getIDEEntryNamesWithoutExtension(vecIDEFilePaths, true, true);
		}
		else if (iSortType == 7)
		{
			vecCOLFilePaths = openFile("COL");
			vecCOLModelNamesUpper = COLManager::get()->getEntryNames(vecCOLFilePaths);
		}

		vecSortTypes.push_back(iSortType);

		uiSortTypeIndex++;
	}
	
	std::function<bool(IMGEntry *, IMGEntry *)> sortByMultipleTypes = [&](IMGEntry *pIMGEntry1, IMGEntry *pIMGEntry2) -> bool
	{
		bool bResult;
		vector<string>::iterator itIndex1;
		vector<string>::iterator itIndex2;

		unordered_map<IMGEntry*, uint32> umapEntryIndexes;
		for (IMGEntry *pIMGEntry : getIMGTab()->getIMGFile()->VectorPool::getEntries())
		{
			umapEntryIndexes[pIMGEntry] = pIMGEntry->getIMGFile()->getIndexByEntry(pIMGEntry);
		}

		switch (uiSortTypeIndex)
		{
		case 0: // Index
			if (umapEntryIndexes[pIMGEntry1] == umapEntryIndexes[pIMGEntry2])
			{
				uiSortTypeIndex++;
				bResult = sortByMultipleTypes(pIMGEntry1, pIMGEntry2);
				uiSortTypeIndex--;
				return bResult;
			}
			else
			{
				return umapEntryIndexes[pIMGEntry1] < umapEntryIndexes[pIMGEntry2];
			}
			break;
		case 1: // Type
			if (pIMGEntry1->getEntryExtension() == pIMGEntry2->getEntryExtension())
			{
				uiSortTypeIndex++;
				bResult = sortByMultipleTypes(pIMGEntry1, pIMGEntry2);
				uiSortTypeIndex--;
				return bResult;
			}
			else
			{
				return strcmp(String::toLowerCase(pIMGEntry1->getEntryExtension()).c_str(), String::toLowerCase(pIMGEntry2->getEntryExtension()).c_str()) < 0;
			}
			break;
		case 2: // Name
			if (pIMGEntry1->getEntryName() == pIMGEntry2->getEntryName())
			{
				uiSortTypeIndex++;
				bResult = sortByMultipleTypes(pIMGEntry1, pIMGEntry2);
				uiSortTypeIndex--;
				return bResult;
			}
			else
			{
				return strcmp(String::toLowerCase(pIMGEntry1->getEntryName()).c_str(), String::toLowerCase(pIMGEntry2->getEntryName()).c_str()) < 0;
			}
			break;
		case 3: // Offset
			if (pIMGEntry1->getEntryOffset() == pIMGEntry2->getEntryOffset())
			{
				uiSortTypeIndex++;
				bResult = sortByMultipleTypes(pIMGEntry1, pIMGEntry2);
				uiSortTypeIndex--;
				return bResult;
			}
			else
			{
				return pIMGEntry1->getEntryOffset() < pIMGEntry2->getEntryOffset();
			}
			break;
		case 4: // Size
			if (pIMGEntry1->getEntrySize() == pIMGEntry2->getEntrySize())
			{
				uiSortTypeIndex++;
				bResult = sortByMultipleTypes(pIMGEntry1, pIMGEntry2);
				uiSortTypeIndex--;
				return bResult;
			}
			else
			{
				return pIMGEntry1->getEntrySize() < pIMGEntry2->getEntrySize();
			}
			break;
		case 5: // Version
			if (pIMGEntry1->getRawVersion() == pIMGEntry2->getRawVersion())
			{
				uiSortTypeIndex++;
				bResult = sortByMultipleTypes(pIMGEntry1, pIMGEntry2);
				uiSortTypeIndex--;
				return bResult;
			}
			else
			{
				return pIMGEntry1->getRawVersion() < pIMGEntry2->getRawVersion();
			}
			break;
		case 6: // IDE
			itIndex1 = std::find(vecIDEModelNamesUpper.begin(), vecIDEModelNamesUpper.end(), String::toUpperCase(pIMGEntry1->getEntryName()));
			itIndex2 = std::find(vecIDEModelNamesUpper.begin(), vecIDEModelNamesUpper.end(), String::toUpperCase(pIMGEntry2->getEntryName()));
			if (itIndex1 == itIndex2)
			{
				uiSortTypeIndex++;
				bResult = sortByMultipleTypes(pIMGEntry1, pIMGEntry2);
				uiSortTypeIndex--;
				return bResult;
			}
			else
			{
				return itIndex1 < itIndex2;
			}
			break;
		case 7: // COL
			itIndex1 = std::find(vecCOLModelNamesUpper.begin(), vecCOLModelNamesUpper.end(), String::toUpperCase(pIMGEntry1->getEntryName()));
			itIndex2 = std::find(vecCOLModelNamesUpper.begin(), vecCOLModelNamesUpper.end(), String::toUpperCase(pIMGEntry2->getEntryName()));
			if (itIndex1 == itIndex2)
			{
				uiSortTypeIndex++;
				bResult = sortByMultipleTypes(pIMGEntry1, pIMGEntry2);
				uiSortTypeIndex--;
				return bResult;
			}
			else
			{
				return itIndex1 < itIndex2;
			}
			break;
		}
		return true;
	};
	uiSortTypeIndex = 0;
	std::sort(getIMGTab()->getIMGFile()->VectorPool::getEntries().begin(), getIMGTab()->getIMGFile()->VectorPool::getEntries().end(), sortByMultipleTypes);
	getTab()->onSortEntries(getTab()->getEntriesRef());

	getTab()->log("Sorted IMG by multiple types.");

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

	getTab()->logf("Processed %u LST files.", vecLSTFilePaths.size());

	onCompleteTask();
}

// entry
void						Tasks::nameCaseLower(void)
{
	onStartTask("nameCaseLower");

	getTab()->setSelectedEntriesNameCase(0);
	getTab()->logf("Set entry name to lower case for %u entries.", getTab()->getSelectedEntryCount());

	onCompleteTask();
}

void						Tasks::nameCaseUpper(void)
{
	onStartTask("nameCaseUpper");

	getTab()->setSelectedEntriesNameCase(1);
	getTab()->logf("Set entry name to UPPER CASE for %u entries.", getTab()->getSelectedEntryCount());

	onCompleteTask();
}

void						Tasks::nameCaseTitle(void)
{
	onStartTask("nameCaseTitle");

	getTab()->setSelectedEntriesNameCase(2);
	getTab()->logf("Set entry name to Title Case for %u entries.", getTab()->getSelectedEntryCount());

	onCompleteTask();
}

void						Tasks::copyEntryIndex(void)
{
	onStartTask("copyEntryIndex");

	getTab()->copySelectedEntryData(0);
	getTab()->logf("Copied entry index for %u entries.", getTab()->getSelectedEntryCount());

	onCompleteTask();
}

void						Tasks::copyEntryType(void)
{
	onStartTask("copyEntryType");

	getTab()->copySelectedEntryData(1);
	getTab()->logf("Copied entry type for %u entries.", getTab()->getSelectedEntryCount());

	onCompleteTask();
}

void						Tasks::copyEntryName(void)
{
	onStartTask("copyEntryName");

	getTab()->copySelectedEntryData(2);
	getTab()->logf("Copied entry name for %u entries.", getTab()->getSelectedEntryCount());

	onCompleteTask();
}

void						Tasks::copyEntryOffset(void)
{
	onStartTask("copyEntryOffset");

	getTab()->copySelectedEntryData(3);
	getTab()->logf("Copied entry offset for %u entries.", getTab()->getSelectedEntryCount());

	onCompleteTask();
}

void						Tasks::copyEntrySize(void)
{
	onStartTask("copyEntrySize");

	getTab()->copySelectedEntryData(4);
	getTab()->logf("Copied entry size for %u entries.", getTab()->getSelectedEntryCount());

	onCompleteTask();
}

void						Tasks::copyEntryVersion(void)
{
	onStartTask("copyEntryVersion");

	getTab()->copySelectedEntryData(5);
	getTab()->logf("Copied entry version for %u entries.", getTab()->getSelectedEntryCount());

	onCompleteTask();
}

void						Tasks::copyEntryRowData(void)
{
	onStartTask("copyEntryRowData");

	getTab()->copySelectedEntryData(6);
	getTab()->logf("Copied row data for %u entries.", getTab()->getSelectedEntryCount());

	onCompleteTask();
}

void						Tasks::shiftEntryUp1Row(void)
{
	onStartTask("shiftEntryUp1Row");

	getTab()->shiftSelectedEntries(-1);
	getTab()->logf("Shifted %u entries up by %u rows.", getTab()->getSelectedEntryCount(), 1);

	onCompleteTask();
}

void						Tasks::shiftEntryUp5Rows(void)
{
	onStartTask("shiftEntryUp5Rows");

	getTab()->shiftSelectedEntries(-5);
	getTab()->logf("Shifted %u entries up by %u rows.", getTab()->getSelectedEntryCount(), 5);

	onCompleteTask();
}

void						Tasks::shiftEntryUp10Rows(void)
{
	onStartTask("shiftEntryUp10Rows");

	getTab()->shiftSelectedEntries(-10);
	getTab()->logf("Shifted %u entries up by %u rows.", getTab()->getSelectedEntryCount(), 10);

	onCompleteTask();
}

void						Tasks::shiftEntryUp100Rows(void)
{
	onStartTask("shiftEntryUp100Rows");

	getTab()->shiftSelectedEntries(-100);
	getTab()->logf("Shifted %u entries up by %u rows.", getTab()->getSelectedEntryCount(), 100);

	onCompleteTask();
}

void						Tasks::shiftEntryUp1000Rows(void)
{
	onStartTask("shiftEntryUp1000Rows");

	getTab()->shiftSelectedEntries(-1000);
	getTab()->logf("Shifted %u entries up by %u rows.", getTab()->getSelectedEntryCount(), 1000);

	onCompleteTask();
}

void						Tasks::shiftEntryDown1Row(void)
{
	onStartTask("shiftEntryDown1Row");

	getTab()->shiftSelectedEntries(1);
	getTab()->logf("Shifted %u entries down by %u rows.", getTab()->getSelectedEntryCount(), 1);

	onCompleteTask();
}

void						Tasks::shiftEntryDown5Rows(void)
{
	onStartTask("shiftEntryDown5Rows");

	getTab()->shiftSelectedEntries(5);
	getTab()->logf("Shifted %u entries down by %u rows.", getTab()->getSelectedEntryCount(), 5);

	onCompleteTask();
}

void						Tasks::shiftEntryDown10Rows(void)
{
	onStartTask("shiftEntryDown10Rows");

	getTab()->shiftSelectedEntries(10);
	getTab()->logf("Shifted %u entries down by %u rows.", getTab()->getSelectedEntryCount(), 10);

	onCompleteTask();
}

void						Tasks::shiftEntryDown100Rows(void)
{
	onStartTask("shiftEntryDown100Rows");

	getTab()->shiftSelectedEntries(100);
	getTab()->logf("Shifted %u entries down by %u rows.", getTab()->getSelectedEntryCount(), 100);

	onCompleteTask();
}

void						Tasks::shiftEntryDown1000Rows(void)
{
	onStartTask("shiftEntryDown1000Rows");

	getTab()->shiftSelectedEntries(1000);
	getTab()->logf("Shifted %u entries down by %u rows.", getTab()->getSelectedEntryCount(), 1000);

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
	for (IMGEntry *pIMGEntry : (vector<IMGEntry*>&)getIMGTab()->getSelectedEntries())
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
	for (IMGEntry *pIMGEntry : (vector<IMGEntry*>&)getIMGTab()->getSelectedEntries())
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

	getTab()->logf("Removed orphan txtures from %u DFF files.", uiDFFFileCountWithRemovedSections);

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

	m_pTaskManager->onPauseTask();
	bool bRemoveEntriesFromIMG = m_pMainWindow->showGridWindow("Orphan IMG Entries not in IDE", String::toString(vecOrphanEntryNames.size()) + " Orphan IMG Entries not in IDE:", vector<string>({ "Orphan Entry Name" }), StdVector::swap2D(vector<vector<string>>({ vecOrphanEntryNames })), "Remove Entries from IMG");
	m_pTaskManager->onResumeTask();

	if(bRemoveEntriesFromIMG)
	{
		vector<FormatEntry*> vecOrphanEntries = getTab()->getContainerFile()->getEntriesByNames(vecOrphanEntryNames);

		for (FormatEntry *pEntry : vecOrphanEntries)
		{
			getIMGTab()->removeEntry((IMGEntry*)pEntry);
		}

		if (vecOrphanEntries.size() > 0)
		{
			getIMGTab()->readdGridEntries();
			getIMGTab()->setFileUnsaved(true);
		}

		getTab()->logf("Removed %u orphan entries in IMG missing from IDE.", vecOrphanEntries.size());
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

	m_pTaskManager->onPauseTask();
	bool bImportEntriesIntoIMG = m_pMainWindow->showGridWindow("Orphan IDE Entries not in IMG", String::toString(vecOrphanEntryNames.size()) + " Orphan IDE Entries not in IMG:", vector<string>({ "Orphan Entry Name" }), StdVector::swap2D(vector<vector<string>>({ vecOrphanEntryNames })), "Import Entries into IMG");
	m_pTaskManager->onResumeTask();

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
				getIMGTab()->addEntryViaFile(strEntryFilePath);
			}

			increaseProgress();
		}

		if (uiImportCount > 0)
		{
			getIMGTab()->setFileUnsaved(true);
		}

		getTab()->logf("Imported %u orphan IDE entries into IMG.", uiImportCount);
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
	for (IMGEntry *pIMGEntry : (vector<IMGEntry*>&)getIMGTab()->getSelectedEntries())
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

	m_pTaskManager->onPauseTask();
	m_pMainWindow->showGridWindow("Orphan TXD Textures for DFFs in IMG by IDE", String::toString(vecOrphanEntryNames.size()) + " Orphan TXD textures for DFFs in IMG by IDE:", vector<string>({ "Orphan Entry Name" }), StdVector::swap2D(vector<vector<string>>({ vecOrphanEntryNames })), "");
	m_pTaskManager->onResumeTask();

	onCompleteTask();
}

// tools
void		Tasks::dump(void)
{
	onStartTask("dump");

	if (getIMGF()->getDumpManager()->process())
	{
		onCompleteTask();
	}
	else
	{
		onAbortTask();
	}
}

void		Tasks::sessionManager(void)
{
	onStartTask("sessionManager");

	m_pTaskManager->onPauseTask();
	getIMGF()->getWindowManager()->showSessionManagerWindow();
	m_pTaskManager->onResumeTask();

	onCompleteTask();
}

void		Tasks::renamer(void)
{
	onStartTask("renamer");

	m_pTaskManager->onPauseTask();
	getIMGF()->getWindowManager()->showRenamerWindow();
	m_pTaskManager->onResumeTask();

	onCompleteTask();
}

void		Tasks::txdBuilder(void)
{
	onStartTask("txdBuilder");

	m_pTaskManager->onPauseTask();
	TXDBuilderWindowResult txdBuilderWindowResult = getIMGF()->getWindowManager()->showTXDBuilderWindow();
	m_pTaskManager->onResumeTask();

	if (m_pMainWindow->m_bWindow2Cancelled)
	{
		// cancel
		return onAbortTask();
	}

	// choose DFF files
	//vector<DFFFormat*> veDFFFormats;
	unordered_map<DFFFormat*, string> umapDFFEntries;
	if (txdBuilderWindowResult.m_uiDFFFilesType == 0) // All DFF entries in active tab
	{
		if (!getIMGTab())
		{
			return onAbortTask();
		}

		vector<FormatEntry*> vecIMGEntries = getIMGTab()->getIMGFile()->getEntriesByExtension("DFF");
		vector<FormatEntry*> vecIMGEntries_BSP = getIMGTab()->getIMGFile()->getEntriesByExtension("BSP");
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
	else if (txdBuilderWindowResult.m_uiDFFFilesType == 1) // Selected DFF entries in active tab
	{
		if (!getIMGTab())
		{
			return onAbortTask();
		}

		vector<IMGEntry*> vecIMGEntries = (vector<IMGEntry*>&)getIMGTab()->getSelectedEntries();
		
		for(auto pIMGEntry : vecIMGEntries)
		{
			if (GameFormat::isModelExtension(String::toUpperCase(Path::getFileExtension(pIMGEntry->getEntryName()))))
			{
				DFFFormat *pDFFFile = DFFManager::get()->unserializeMemory(pIMGEntry->getEntryData());
				umapDFFEntries[pDFFFile] = Path::removeFileExtension(pIMGEntry->getEntryName());
			}
		}
	}
	else if (txdBuilderWindowResult.m_uiDFFFilesType == 2) // All DFF entries in all tabs
	{
		if (!getIMGTab())
		{
			return onAbortTask();
		}

		for (auto pEditorTab : getIMGF()->getIMGEditor()->getEditorTabs().getEntries())
		{
			vector<FormatEntry*> vecIMGEntries = ((IMGEditorTab*)pEditorTab)->getContainerFile()->getEntriesByExtension("DFF");
			vector<FormatEntry*> vecIMGEntries_BSP = ((IMGEditorTab*)pEditorTab)->getContainerFile()->getEntriesByExtension("BSP");
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
	else if (txdBuilderWindowResult.m_uiDFFFilesType == 3) // Folder containing DFF files
	{
		vector<string> vecFileNames = File::getFileNames(txdBuilderWindowResult.m_strDFFsFolderPath);

		for (string strFileName : vecFileNames)
		{
			string strExtensionUpper = String::toUpperCase(Path::getFileExtension(strFileName));
			if (GameFormat::isModelExtension(strExtensionUpper))
			{
				DFFFormat *pDFFFile = DFFManager::get()->unserializeMemory(txdBuilderWindowResult.m_strDFFsFolderPath + strFileName);
				umapDFFEntries[pDFFFile] = Path::removeFileExtension(strFileName);
			}
		}
	}
	else if (txdBuilderWindowResult.m_uiDFFFilesType == 4) // IDE file referencing DFF files
	{
		IDEFormat *pIDEFile = IDEManager::get()->unserializeFile(txdBuilderWindowResult.m_strIDEFilePath);
		if(!pIDEFile->doesHaveError())
		{
			// todo - make it work with all IDE sections
			for (auto pIDEEntry : pIDEFile->getEntriesBySection<IDEEntry_OBJS>(IDE_SECTION_OBJS))
			{
				DFFFormat *pDFFFile = DFFManager::get()->unserializeMemory(txdBuilderWindowResult.m_strDFFsFolderPath + pIDEEntry->getModelName());
				umapDFFEntries[pDFFFile] = pIDEEntry->getTXDName();
			}
			for (auto pIDEEntry : pIDEFile->getEntriesBySection<IDEEntry_TOBJ>(IDE_SECTION_TOBJ))
			{
				DFFFormat *pDFFFile = DFFManager::get()->unserializeMemory(txdBuilderWindowResult.m_strDFFsFolderPath + pIDEEntry->getModelName());
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

		uint32 uiTXDFileCount = txdBuilderWindowResult.m_uiTextureCountPerTXD == 0 ? 1 : (uint32) ceil((float32)vecTextureNames.size() / (float32)txdBuilderWindowResult.m_uiTextureCountPerTXD);
		uiTotalTXDFileCount += uiTXDFileCount;
		uint32 uiTXDFileIndex = 0;
		for (uint32 i = 0; i < uiTXDFileCount; i++)
		{
			string strFilePath = txdBuilderWindowResult.m_strOutputFolderPath + strOutputFileName;
			strFilePath = Path::getNextFileName(strFilePath, uiTXDFileIndex, "-part");

			TXDFormat *pTXDFile = TXDManager::get()->createFormat();
			pTXDFile->setRWVersion(RWManager::get()->getVersionManager()->getEntryByVersionId(txdBuilderWindowResult.m_uiRWVersion));
			for (uint32 i2 = i * txdBuilderWindowResult.m_uiTextureCountPerTXD , j2 = i2 + (txdBuilderWindowResult.m_uiTextureCountPerTXD == 0 ? vecTextureNames.size() : txdBuilderWindowResult.m_uiTextureCountPerTXD); i2 < j2; i2++)
			{
				if (i2 >= vecTextureNames.size())
				{
					break;
				}

				string strTextureName = vecTextureNames[i2];
				string strTextureImagePath = File::findImageFile(strTextureName, txdBuilderWindowResult.m_strTexturesBMPsFolderPath);

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
				pTXDFile->serialize(strFilePath);
				veTXDFormatNames.push_back(Path::getFileName(strFilePath));
				uiTXDFileIndex++;
			}
			
			pTXDFile->unload();
			delete pTXDFile;
		}

		increaseProgress();
	}

	// log
	// todo - getTab()->log(LocalizationManager::get()->getTranslatedFormattedText("Log_118", uiTotalTXDFileCount, uiTotalTextureCountUsed));
	// todo - getTab()->log(LocalizationManager::get()->getTranslatedFormattedText("Log_119", pBuildTXDDialogData->m_strTexturesFolderPath.c_str()), true);
	// todo - getTab()->log(String::join(vecTextureImagesNotFound, "\n"), true);
	// todo - getTab()->log(LocalizationManager::get()->getTranslatedText("Log_120"), true);
	// todo - getTab()->log(String::join(veTXDFormatNames, "\n"), true);

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
	
	onCompleteTask();
}

void		Tasks::txdOrganizer(void)
{
	onStartTask("txdOrganizer");

	TXDOrganizerWindowResult txdOrganizerWindowResult = getIMGF()->getWindowManager()->showTXDOrganizerWindow();

	if (m_pMainWindow->m_bWindow2Cancelled)
	{
		return onAbortTask();
	}

	vector<string> vecFilePaths;
	if (txdOrganizerWindowResult.m_bUpdateIDE)
	{
		vecFilePaths = File::getFilePaths(txdOrganizerWindowResult.m_strIDEUpdateFolder, true);
	}

	setMaxProgress(getIMGTab()->getEntryGrid()->getEntryCount() + (txdOrganizerWindowResult.m_bUpdateIDE ? vecFilePaths.size() : 0));

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

	for (uint32 i = 0, j = getIMGTab()->getEntryGrid()->getEntryCount(); i < j; i++)
	{
		pIMGEntry = (IMGEntry*)getIMGTab()->getEntryGrid()->getEntryByIndex(i)->getUserData();

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
			string strTextureImagePath = File::findImageFile(strDFFTextureName, txdOrganizerWindowResult.m_strTextureImportFolder);
			if (strTextureImagePath != "")
			{
				// add texture to TXD
				umapTextureNamesUsedInTXD[String::toUpperCase(strDFFTextureName)] = true;
				RWSection_TextureNative *pTexture = pTXDFile->addTextureViaFile(strTextureImagePath, strDFFTextureName, strDFFTextureName + "a");

				if (pTexture != nullptr)
				{
					vector<string> vecMipmapsRemoved;
					//Debugger::log("pTXDOrganizerDialogData->m_pTextureFormat->getId(): " + String::toString(pTXDOrganizerDialogData->m_pTextureFormat->getId()));
					pTexture->convertToRasterDataFormat(txdOrganizerWindowResult.m_pRasterDataFormat->getRasterDataFormatId(), vecMipmapsRemoved);
				}
			}
		}

		string strNextTXDFileName = txdOrganizerWindowResult.m_strTXDNamePrefix + ((uiTXDCount + 1) < 10 ? "0" : "") + String::toString(uiTXDCount + 1) + ".txd";
		string strDFFFileNameWithoutExtension = Path::removeFileExtension(pIMGEntry->getEntryName());
		string strTXDFileNameWithoutExtension = Path::removeFileExtension(strNextTXDFileName);
		umapNewEntryNames[strDFFFileNameWithoutExtension] = strTXDFileNameWithoutExtension;

		uiDFFFileCount++;
		if (uiDFFFileCount == txdOrganizerWindowResult.m_uiEveryNDFFFiles)
		{
			uiTXDCount++;
			string strTXDFileName = txdOrganizerWindowResult.m_strTXDNamePrefix + (uiTXDCount < 10 ? "0" : "") + String::toString(uiTXDCount) + ".txd";
			pTXDFile->serialize(txdOrganizerWindowResult.m_strOutputFolder + strTXDFileName);
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
		string strTXDFileName = txdOrganizerWindowResult.m_strTXDNamePrefix + (uiTXDCount < 10 ? "0" : "") + String::toString(uiTXDCount) + ".txd";
		pTXDFile->serialize(txdOrganizerWindowResult.m_strOutputFolder + strTXDFileName);
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
	if (txdOrganizerWindowResult.m_bUpdateIDE)
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

			pIDEFile->serialize();

			pIDEFile->unload();
			delete pIDEFile;
			increaseProgress();
		}
	}

	onCompleteTask();
}

void		Tasks::datPathsMover(void)
{
	onStartTask("datPathsMover");

	getIMGF()->getTaskManager()->onPauseTask();
	DATPathsMoverWindowResult datPathsMoverWindowResult = getIMGF()->getWindowManager()->showDATPathsMoverWindow();
	getIMGF()->getTaskManager()->onResumeTask();

	if (m_pMainWindow->m_bWindow2Cancelled)
	{
		return onAbortTask();
	}

	vector<string>
		vecFileNames = File::getFileNamesByExtension(datPathsMoverWindowResult.m_strDATInputFolderPath, "DAT");
	vector<DATPathFormat*>
		vecDATInputFiles,
		vecDATOutputFiles;
	for (auto strFileName : vecFileNames)
	{
		uint32 uiAreaId = String::toNumber(Path::removeFileExtension(strFileName).substr(5)); // example filename: nodes0.dat, nodes1.dat, nodes63.dat

		DATPathFormat *pDATFile = DATPathManager::get()->unserializeMemory(File::getBinaryFile(datPathsMoverWindowResult.m_strDATInputFolderPath + strFileName));//////, uiAreaId///////);
		if (!pDATFile->doesHaveError())
		{
			vecDATInputFiles.push_back(pDATFile);
		}
	}
	for (uint32 i = 0, j = DATPathManager::getTileCount(datPathsMoverWindowResult.m_vecMinOutputMapRange, datPathsMoverWindowResult.m_vecMaxOutputMapRange, datPathsMoverWindowResult.m_vecOutputTileSize); i < j; i++)
	{
		DATPathFormat *pDATFile = new DATPathFormat;
		pDATFile->setPathsFormat(DAT_PATH_FASTMAN92);
		pDATFile->m_uiFileIndex = i;
		vecDATOutputFiles.push_back(pDATFile);
	}

	std::sort(vecDATInputFiles.begin(), vecDATInputFiles.end(), sortDATFiles);

	setMaxProgress((vecDATInputFiles.size() * 2) + (vecDATOutputFiles.size() * 4));

	for (DATPathFormat *pDATFile : vecDATInputFiles)
	{
		pDATFile->applyOffsetToPositions(datPathsMoverWindowResult.m_vecPositionOffset);

		increaseProgress();
	}

	// process
	//unordered_map<DATEntry_Paths_General_PathNode&, CNodeAddress> umapNewAddresses_PathNode;
	for (DATPathFormat *pDATFile : vecDATInputFiles)
	{
		uint32 uiAreaId_SA = pDATFile->m_uiFileIndex;

		for (auto& pathNode : pDATFile->m_vecPathNodes)
		{
			Vec2f vecPathNodePosition = { (float32)pathNode.m_vecPosition.x / 8.0f, (float32)pathNode.m_vecPosition.y / 8.0f };
			uint32 uiNewAreaIdForPathNode = DATPathManager::getAreaIdFromPosition(vecPathNodePosition, datPathsMoverWindowResult.m_vecMinOutputMapRange, datPathsMoverWindowResult.m_vecMaxOutputMapRange, datPathsMoverWindowResult.m_vecOutputTileSize);

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
			uint32 uiNewAreaIdForNaviNode = DATPathManager::getAreaIdFromPosition(vecNaviNodePosition, datPathsMoverWindowResult.m_vecMinOutputMapRange, datPathsMoverWindowResult.m_vecMaxOutputMapRange, datPathsMoverWindowResult.m_vecOutputTileSize);

			vecDATOutputFiles[uiNewAreaIdForNaviNode]->addNaviNode(naviNode);
			i++;
		}

		increaseProgress();
	}

	for (DATPathFormat *pDATFile : vecDATOutputFiles)
	{
		std::sort(pDATFile->m_vecPathNodes.begin(), pDATFile->m_vecPathNodes.end(), sortDATPathsEntries);

		increaseProgress();
	}

	for (DATPathFormat *pDATFile : vecDATOutputFiles)
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

	for (DATPathFormat *pDATFile : vecDATOutputFiles)
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
	for (DATPathFormat *pDATFile : vecDATOutputFiles)
	{
		uint32 uiNaviNodeAreaId = pDATFile->m_uiFileIndex;
		uint32 uiNaviNodeNodeId = 0;
		for (auto& naviNode : pDATFile->m_vecNaviNodes)
		{
			DATEntry_Paths_General_PathNode pathNode1 = vecDATOutputFiles[naviNode.m_usTargetNode_AreaId]->m_vecPathNodes[naviNode.m_usTargetNode_NodeId];
			uint32 uiLinkId_Out;
			vector<DATEntry_Paths_General_PathNode> vecTargetPathNodes = DATPathManager::getTargetPathNodesForNaviNode(vecDATOutputFiles, naviNode, uiNaviNodeAreaId, uiNaviNodeNodeId, uiLinkId_Out);
			vecTargetPathNodes.push_back(pathNode1);
			//if (vecTargetPathNodes.size() != 2)
			//{
			//	Debugger::log("vecTargetPathNodes.size(): " + String::toString(vecTargetPathNodes.size()));
			//}

			//DATEntry_Paths_General_PathNode lowestTargetPathNode = DATManager::getLowestPathNode(vecTargetPathNodes);
			//naviNode.m_usTargetNode_AreaId = lowestTargetPathNode.m_wAreaId;
			//naviNode.m_usTargetNode_NodeId = lowestTargetPathNode.m_wNodeId;

			DATEntry_Paths_General_PathNode lowerTargetPathNode = DATPathManager::getLowestPathNode(vecTargetPathNodes);
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
	for (DATPathFormat *pDATFile : vecDATOutputFiles)
	{
		File::setBinaryFile(datPathsMoverWindowResult.m_strDATOutputFolderPath + "nodes" + String::toString(i) + ".dat", pDATFile->serialize());
		increaseProgress();
		i++;
	}

	// clean up
	for (DATPathFormat *pDATFile : vecDATInputFiles)
	{
		pDATFile->unload();
		delete pDATFile;
	}
	for (DATPathFormat *pDATFile : vecDATOutputFiles)
	{
		pDATFile->unload();
		delete pDATFile;
	}

	onCompleteTask();
}

void						Tasks::mapMoverAndIDShifter(void)
{
	onStartTask("mapMoverAndIDShifter");

	getIMGF()->getTaskManager()->onPauseTask();
	MapMoverAndIDShifterWindowResult mapMoverAndIDShifterWindowResult = getIMGF()->getWindowManager()->showMapMoverAndIdShifterWindow();
	getIMGF()->getTaskManager()->onResumeTask();

	if (m_pMainWindow->m_bWindow2Cancelled)
	{
		return onAbortTask();
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
		umapIgnoreDefaultObjectFileNamesVector[PC_GTA_III] = String::split(File::getTextFile(strModelNamesPath_PC_GTA_III), ", ");
	}
	if (File::doesFileExist(strModelNamesPath_PC_GTA_VC))
	{
		umapIgnoreDefaultObjectFileNamesVector[PC_GTA_VC] = String::split(File::getTextFile(strModelNamesPath_PC_GTA_VC), ", ");
	}
	if (File::doesFileExist(strModelNamesPath_PC_GTA_SA))
	{
		umapIgnoreDefaultObjectFileNamesVector[PC_GTA_SA] = String::split(File::getTextFile(strModelNamesPath_PC_GTA_SA), ", ");
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

	DATLoaderFormat *pDATFile = DATLoaderManager::get()->unserializeFile(mapMoverAndIDShifterWindowResult.m_strDATFile);
	if(pDATFile->doesHaveError())
	{
		return onAbortTask();
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
		vecIDEPaths[i] = mapMoverAndIDShifterWindowResult.m_strGameFolder + strRelativeIDEPath;
		i++;
	}
	i = 0;
	for (string& strRelativeIPLPath : vecRelativeIPLPaths)
	{
		vecIPLPaths[i] = mapMoverAndIDShifterWindowResult.m_strGameFolder + strRelativeIPLPath;
		i++;
	}
	vecRelativeIDEPaths.clear();
	vecRelativeIPLPaths.clear();
	if (mapMoverAndIDShifterWindowResult.m_bUseIDEFolder)
	{
		vecIDEPaths = StdVector::combineVectors(vecIDEPaths, File::getFilePaths(mapMoverAndIDShifterWindowResult.m_strIDEFolder, true, false, "IDE"));
	}
	if (mapMoverAndIDShifterWindowResult.m_bUseIPLFolder)
	{
		vecIPLPaths = StdVector::combineVectors(vecIPLPaths, File::getFilePaths(mapMoverAndIDShifterWindowResult.m_strIPLFolder, true, false, "IPL"));
	}

	setMaxProgress(vecIDEPaths.size() + vecIPLPaths.size());


	mapMoverAndIDShifterWindowResult.m_vecIgnoreFilesForIDShifter = StdVector::toUpperCase(mapMoverAndIDShifterWindowResult.m_vecIgnoreFilesForIDShifter);
	mapMoverAndIDShifterWindowResult.m_vecIgnoreFilesForMapMover = StdVector::toUpperCase(mapMoverAndIDShifterWindowResult.m_vecIgnoreFilesForMapMover);

	uint32 uiIDEEntryNewObjectId = mapMoverAndIDShifterWindowResult.m_uiIDStart;
	unordered_map<uint32, uint32> umapNewObjectIds;
	uint32
		uiIPLCount_Text = 0,
		uiIPLCount_Binary = 0;
	if (mapMoverAndIDShifterWindowResult.m_bUseIDStart)
	{
		for (string& strIDEPath : vecIDEPaths)
		{
			bool bIgnoreShifter = std::find(mapMoverAndIDShifterWindowResult.m_vecIgnoreFilesForIDShifter.begin(), mapMoverAndIDShifterWindowResult.m_vecIgnoreFilesForIDShifter.end(), String::toUpperCase(Path::getFileName(strIDEPath))) != mapMoverAndIDShifterWindowResult.m_vecIgnoreFilesForIDShifter.end();
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

				pIDEFile->setFilePath(mapMoverAndIDShifterWindowResult.m_strOutputFolder + Path::getFileName(strIDEPath));
				pIDEFile->serialize();
			}
			pIDEFile->unload();
			delete pIDEFile;

			increaseProgress();
		}
	}

	for (string& strIPLPath : vecIPLPaths)
	{
		bool
			bIgnoreShifter = !mapMoverAndIDShifterWindowResult.m_bUseIDStart,
			bIgnoreMover = !mapMoverAndIDShifterWindowResult.m_bUsePositionOffset;
		if (!bIgnoreShifter)
		{
			bIgnoreShifter = std::find(mapMoverAndIDShifterWindowResult.m_vecIgnoreFilesForIDShifter.begin(), mapMoverAndIDShifterWindowResult.m_vecIgnoreFilesForIDShifter.end(), String::toUpperCase(Path::getFileName(strIPLPath))) != mapMoverAndIDShifterWindowResult.m_vecIgnoreFilesForIDShifter.end();
		}
		if (!bIgnoreMover)
		{
			bIgnoreMover = std::find(mapMoverAndIDShifterWindowResult.m_vecIgnoreFilesForMapMover.begin(), mapMoverAndIDShifterWindowResult.m_vecIgnoreFilesForMapMover.end(), String::toUpperCase(Path::getFileName(strIPLPath))) != mapMoverAndIDShifterWindowResult.m_vecIgnoreFilesForMapMover.end();
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
					pIPLEntry->getPosition().x += mapMoverAndIDShifterWindowResult.m_vecPositionOffset.x;
					pIPLEntry->getPosition().y += mapMoverAndIDShifterWindowResult.m_vecPositionOffset.y;
					pIPLEntry->getPosition().z += mapMoverAndIDShifterWindowResult.m_vecPositionOffset.z;
				}
			}
			if (!bIgnoreMover)
			{
				for (auto pIPLEntry : pIPLFile->getEntriesBySection<IPLEntry_AUZO>(IPL_SECTION_AUZO))
				{
					switch (pIPLEntry->getFormatType())
					{
					case 0:
						pIPLEntry->getLowerLeftPosition().x += mapMoverAndIDShifterWindowResult.m_vecPositionOffset.x;
						pIPLEntry->getLowerLeftPosition().y += mapMoverAndIDShifterWindowResult.m_vecPositionOffset.y;
						pIPLEntry->getLowerLeftPosition().z += mapMoverAndIDShifterWindowResult.m_vecPositionOffset.z;
						pIPLEntry->getUpperRightPosition().x += mapMoverAndIDShifterWindowResult.m_vecPositionOffset.x;
						pIPLEntry->getUpperRightPosition().y += mapMoverAndIDShifterWindowResult.m_vecPositionOffset.y;
						pIPLEntry->getUpperRightPosition().z += mapMoverAndIDShifterWindowResult.m_vecPositionOffset.z;
						break;
					case 1:
						pIPLEntry->getCenterPosition().x += mapMoverAndIDShifterWindowResult.m_vecPositionOffset.x;
						pIPLEntry->getCenterPosition().y += mapMoverAndIDShifterWindowResult.m_vecPositionOffset.y;
						pIPLEntry->getCenterPosition().z += mapMoverAndIDShifterWindowResult.m_vecPositionOffset.z;
						break;
					}
				}
				for (auto pIPLEntry : pIPLFile->getEntriesBySection<IPLEntry_CARS>(IPL_SECTION_CARS))
				{
					pIPLEntry->getPosition().x += mapMoverAndIDShifterWindowResult.m_vecPositionOffset.x;
					pIPLEntry->getPosition().y += mapMoverAndIDShifterWindowResult.m_vecPositionOffset.y;
					pIPLEntry->getPosition().z += mapMoverAndIDShifterWindowResult.m_vecPositionOffset.z;
				}
				for (auto pIPLEntry : pIPLFile->getEntriesBySection<IPLEntry_CULL>(IPL_SECTION_CULL))
				{
					switch (pIPLEntry->getFormatType())
					{
					case 1:
						pIPLEntry->getLowerLeftPosition().x += mapMoverAndIDShifterWindowResult.m_vecPositionOffset.x;
						pIPLEntry->getLowerLeftPosition().y += mapMoverAndIDShifterWindowResult.m_vecPositionOffset.y;
						pIPLEntry->getLowerLeftPosition().z += mapMoverAndIDShifterWindowResult.m_vecPositionOffset.z;
						pIPLEntry->getUpperRightPosition().x += mapMoverAndIDShifterWindowResult.m_vecPositionOffset.x;
						pIPLEntry->getUpperRightPosition().y += mapMoverAndIDShifterWindowResult.m_vecPositionOffset.y;
						pIPLEntry->getUpperRightPosition().z += mapMoverAndIDShifterWindowResult.m_vecPositionOffset.z;
						// no break intended
					case 0:
					case 2:
						pIPLEntry->getCenterPosition().x += mapMoverAndIDShifterWindowResult.m_vecPositionOffset.x;
						pIPLEntry->getCenterPosition().y += mapMoverAndIDShifterWindowResult.m_vecPositionOffset.y;
						pIPLEntry->getCenterPosition().z += mapMoverAndIDShifterWindowResult.m_vecPositionOffset.z;
						break;
					}
				}
				for (auto pIPLEntry : pIPLFile->getEntriesBySection<IPLEntry_ENEX>(IPL_SECTION_ENEX))
				{
					pIPLEntry->getEntrancePosition().x += mapMoverAndIDShifterWindowResult.m_vecPositionOffset.x;
					pIPLEntry->getEntrancePosition().y += mapMoverAndIDShifterWindowResult.m_vecPositionOffset.y;
					pIPLEntry->getEntrancePosition().z += mapMoverAndIDShifterWindowResult.m_vecPositionOffset.z;
					pIPLEntry->getExitPosition().x += mapMoverAndIDShifterWindowResult.m_vecPositionOffset.x;
					pIPLEntry->getExitPosition().y += mapMoverAndIDShifterWindowResult.m_vecPositionOffset.y;
					pIPLEntry->getExitPosition().z += mapMoverAndIDShifterWindowResult.m_vecPositionOffset.z;
				}
				for (auto pIPLEntry : pIPLFile->getEntriesBySection<IPLEntry_GRGE>(IPL_SECTION_GRGE))
				{
					pIPLEntry->getPosition().x += mapMoverAndIDShifterWindowResult.m_vecPositionOffset.x;
					pIPLEntry->getPosition().y += mapMoverAndIDShifterWindowResult.m_vecPositionOffset.y;
					pIPLEntry->getPosition().z += mapMoverAndIDShifterWindowResult.m_vecPositionOffset.z;
					pIPLEntry->getLine().x += mapMoverAndIDShifterWindowResult.m_vecPositionOffset.x;
					pIPLEntry->getLine().y += mapMoverAndIDShifterWindowResult.m_vecPositionOffset.y;
					pIPLEntry->getCubePosition().x += mapMoverAndIDShifterWindowResult.m_vecPositionOffset.x;
					pIPLEntry->getCubePosition().y += mapMoverAndIDShifterWindowResult.m_vecPositionOffset.y;
					pIPLEntry->getCubePosition().z += mapMoverAndIDShifterWindowResult.m_vecPositionOffset.z;
				}
				for (auto pIPLEntry : pIPLFile->getEntriesBySection<IPLEntry_JUMP>(IPL_SECTION_JUMP))
				{
					pIPLEntry->getStartLowerPosition().x += mapMoverAndIDShifterWindowResult.m_vecPositionOffset.x;
					pIPLEntry->getStartLowerPosition().y += mapMoverAndIDShifterWindowResult.m_vecPositionOffset.y;
					pIPLEntry->getStartLowerPosition().z += mapMoverAndIDShifterWindowResult.m_vecPositionOffset.z;
					pIPLEntry->getStartUpperPosition().x += mapMoverAndIDShifterWindowResult.m_vecPositionOffset.x;
					pIPLEntry->getStartUpperPosition().y += mapMoverAndIDShifterWindowResult.m_vecPositionOffset.y;
					pIPLEntry->getStartUpperPosition().z += mapMoverAndIDShifterWindowResult.m_vecPositionOffset.z;
					pIPLEntry->getTargetLowerPosition().x += mapMoverAndIDShifterWindowResult.m_vecPositionOffset.x;
					pIPLEntry->getTargetLowerPosition().y += mapMoverAndIDShifterWindowResult.m_vecPositionOffset.y;
					pIPLEntry->getTargetLowerPosition().z += mapMoverAndIDShifterWindowResult.m_vecPositionOffset.z;
					pIPLEntry->getTargetUpperPosition().x += mapMoverAndIDShifterWindowResult.m_vecPositionOffset.x;
					pIPLEntry->getTargetUpperPosition().y += mapMoverAndIDShifterWindowResult.m_vecPositionOffset.y;
					pIPLEntry->getTargetUpperPosition().z += mapMoverAndIDShifterWindowResult.m_vecPositionOffset.z;
					pIPLEntry->getCameraPosition().x += mapMoverAndIDShifterWindowResult.m_vecPositionOffset.x;
					pIPLEntry->getCameraPosition().y += mapMoverAndIDShifterWindowResult.m_vecPositionOffset.y;
					pIPLEntry->getCameraPosition().z += mapMoverAndIDShifterWindowResult.m_vecPositionOffset.z;
				}
				for (auto pIPLEntry : pIPLFile->getEntriesBySection<IPLEntry_OCCL>(IPL_SECTION_OCCL))
				{
					pIPLEntry->getMidPosition().x += mapMoverAndIDShifterWindowResult.m_vecPositionOffset.x;
					pIPLEntry->getMidPosition().y += mapMoverAndIDShifterWindowResult.m_vecPositionOffset.y;
				}
				for (auto pIPLEntry : pIPLFile->getEntriesBySection<IPLEntry_PICK>(IPL_SECTION_PICK))
				{
					pIPLEntry->getPosition().x += mapMoverAndIDShifterWindowResult.m_vecPositionOffset.x;
					pIPLEntry->getPosition().y += mapMoverAndIDShifterWindowResult.m_vecPositionOffset.y;
					pIPLEntry->getPosition().z += mapMoverAndIDShifterWindowResult.m_vecPositionOffset.z;
				}
				for (auto pIPLEntry : pIPLFile->getEntriesBySection<IPLEntry_ZONE>(IPL_SECTION_ZONE))
				{
					pIPLEntry->getBottomLeftPosition().x += mapMoverAndIDShifterWindowResult.m_vecPositionOffset.x;
					pIPLEntry->getBottomLeftPosition().y += mapMoverAndIDShifterWindowResult.m_vecPositionOffset.y;
					pIPLEntry->getBottomLeftPosition().z += mapMoverAndIDShifterWindowResult.m_vecPositionOffset.z;
					pIPLEntry->getTopRightPosition().x += mapMoverAndIDShifterWindowResult.m_vecPositionOffset.x;
					pIPLEntry->getTopRightPosition().y += mapMoverAndIDShifterWindowResult.m_vecPositionOffset.y;
					pIPLEntry->getTopRightPosition().z += mapMoverAndIDShifterWindowResult.m_vecPositionOffset.z;
				}
			}
			
			pIPLFile->setFilePath(mapMoverAndIDShifterWindowResult.m_strOutputFolder + Path::getFileName(strIPLPath));
			pIPLFile->serialize();
		}
		
		pIPLFile->unload();
		delete pIPLFile;

		increaseProgress();
	}

	Input::showMessage("Moved and ID shifted " + String::toString(vecIDEPaths.size()) + " IDE files and " + String::toString(vecIPLPaths.size()) + " IPL files (" + String::toString(uiIPLCount_Text) + " text, " + String::toString(uiIPLCount_Binary) + " binary) in " + Path::getFileName(mapMoverAndIDShifterWindowResult.m_strDATFile), "Result", MB_OK);

	onCompleteTask();
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

// other
void		Tasks::textureList(void)
{
	onStartTask("textureList");

	vector<string> vecTextureNames;
	for (IMGEntry *pIMGEntry : (vector<IMGEntry*>&)getIMGTab()->getSelectedEntries())
	{
		//Debug::log("pIMGEntry = " + pIMGEntry->getEntryName());
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

	m_pTaskManager->onPauseTask();
	m_pMainWindow->showGridWindow("Texture List for DFFs and TXDs", String::toString(vecTextureNames.size()) + " textures in selected DFF & TXD entries:", vector<string>({ "Texture Name" }), StdVector::swap2D(vector<vector<string>>({ vecTextureNames })), "");
	m_pTaskManager->onResumeTask();

	onCompleteTask();
}

void		Tasks::stats(void)
{
	onStartTask("stats");

	unordered_map<uint32, uint32> umapStatsRWVersions;
	unordered_map<string, uint32> umapStatsExtensions;

	for (IMGEntry *pIMGEntry : getIMGTab()->getIMGFile()->VectorPool::getEntries())
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

	m_pTaskManager->onPauseTask();
	m_pMainWindow->showGridWindow("IMG Stats", "IMG Stats:", vector<string>({ "RW Version Counts", "Extension Counts" }), vecTextCells, "");
	m_pTaskManager->onResumeTask();

	onCompleteTask();
}

void		Tasks::findDuplicateEntriesInSelection(void)
{
	onStartTask("findDuplicateEntriesInSelection");

	// max progress tick
	setMaxProgress(getIMGTab()->getSelectedEntryCount());

	// fetch selected entries
	vector<IMGEntry*> vecIMGEntries = (vector<IMGEntry*>&)getIMGTab()->getSelectedEntries();

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
	getTab()->logf("Found %u dupliate entries in selection.", vecDuplicateEntries.size());

	// results window
	vector<string> vecGridHeaders = { "Entry Name", "IMG File(s)" };
	m_pTaskManager->onPauseTask();
	m_pMainWindow->showGridWindow("Find Duplicate Entries in Selection", String::toString(vecDuplicateEntries.size()) + " duplicate entries found in selection:", vecGridHeaders, vecDuplicateEntries, "");
	m_pTaskManager->onResumeTask();

	onCompleteTask();
}

void		Tasks::findDuplicateEntriesInTab(void)
{
	onStartTask("findDuplicateEntriesInTab");

	// max progress tick
	setMaxProgress(getIMGTab()->getIMGFile()->getEntryCount());

	// fetch entries
	vector<IMGEntry*> vecIMGEntries = getIMGTab()->getIMGFile()->VectorPool::getEntries();

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
	getTab()->logf("Found %u dupliate entries in tab.", vecDuplicateEntries.size());

	// results window
	vector<string> vecGridHeaders = { "Entry Name", "IMG File(s)" };
	m_pTaskManager->onPauseTask();
	m_pMainWindow->showGridWindow("Find Duplicate Entries in Tab", String::toString(vecDuplicateEntries.size()) + " duplicate entries found in tab:", vecGridHeaders, vecDuplicateEntries, "");
	m_pTaskManager->onResumeTask();

	onCompleteTask();
}

void		Tasks::findDuplicateEntriesInAllTabs(void)
{
	onStartTask("findDuplicateEntriesInAllTabs");

	// max progress tick
	uint32 uiTickCount = 0;
	for (IMGEditorTab *pEditorTab : m_pMainWindow->getIMGEditor()->getIMGEditorTabs().getEntries())
	{
		uiTickCount += pEditorTab->getIMGFile()->getEntryCount();
	}
	setMaxProgress(uiTickCount);

	// fetch entries
	vector<IMGEntry*> vecIMGEntries;
	for (IMGEditorTab *pEditorTab : m_pMainWindow->getIMGEditor()->getIMGEditorTabs().getEntries())
	{
		StdVector::addToVector(vecIMGEntries, pEditorTab->getIMGFile()->VectorPool::getEntries());
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
	for (IMGEditorTab *pEditorTab : m_pMainWindow->getIMGEditor()->getIMGEditorTabs().getEntries())
	{
		pEditorTab->logf("Found %u dupliate entries in all tabs.", vecDuplicateEntries.size());
	}

	// results window
	vector<string> vecGridHeaders = { "Entry Name", "IMG File(s)" };
	m_pTaskManager->onPauseTask();
	m_pMainWindow->showGridWindow("Find Duplicate Entries in All Tabs", String::toString(vecDuplicateEntries.size()) + " duplicate entries found in all tabs:", vecGridHeaders, vecDuplicateEntries, "");
	m_pTaskManager->onResumeTask();

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
		StdVector::addToVector(vecIMGEntries, pIMGFile->VectorPool::getEntries());
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
	m_pTaskManager->onPauseTask();
	m_pMainWindow->showGridWindow("Find Duplicate Entries by DAT", String::toString(vecDuplicateEntries.size()) + " duplicate entries found by DAT:", vecGridHeaders, vecDuplicateEntries, "");
	m_pTaskManager->onResumeTask();

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
		showMessage("There needs to be at least 2 valid IMG files to compare.", "Not Enough Valid IMG Files", MB_OK);
		return onAbortTask();
	}

	// stroe IMG entry names
	unordered_map<IMGFormat*, set<string>> umapIMGFormatEntryNames;
	for (IMGFormat *pIMGFormat : vecIMGFiles)
	{
		for (IMGEntry *pIMGEntry : pIMGFormat->VectorPool::getEntries())
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
		for (IMGEntry *pIMGEntry1 : pIMGFormat1->VectorPool::getEntries())
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
	m_pTaskManager->onPauseTask();
	m_pMainWindow->showGridWindow("Compare IMGs", "IMG comparison results:", vecGridHeaders, vecGridCellsText, "");
	m_pTaskManager->onResumeTask();

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
	m_pTaskManager->onPauseTask();
	m_pMainWindow->showGridWindow("Model List for IDE/IPL by DAT", String::toString(vecModelNames.size()) + " models in IDE/IPL files in DAT files:", vecGridHeaders, vecGridCellsText, "");
	m_pTaskManager->onResumeTask();

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

	getTab()->logf("Saved DB file for %s.", Path::getFileName(pIMGFile->getIMGFilePath()).c_str());

	onCompleteTask();
}

void		Tasks::verifyIMGSignature(void)
{
	onStartTask("verifyIMGSignature");

	IMGFormat *pIMGFile = getIMGTab()->getIMGFile();
	string strDBFilePath = Path::replaceFileExtension(pIMGFile->getFilePath(), "db");

	if (!File::doesFileExist(strDBFilePath))
	{
		showMessage("DB file does not exist for " + Path::getFileName(pIMGFile->getIMGFilePath()), "DB File Doesn't Exist", MB_OK);
		return onAbortTask();
	}

	DBFormat *pDBFileForIMGTab = DBManager::get()->createDBFileFromIMGFile(pIMGFile);
	DBFormat *pDBFileForIMGFile = DBManager::get()->unserializeFile(strDBFilePath);
	
	if(!pDBFileForIMGFile)
	{
		delete pDBFileForIMGTab;
		delete pDBFileForIMGFile;
		showMessage("Failed to open DB file for " + Path::getFileName(pIMGFile->getIMGFilePath()), "Failed to Open DB File", MB_OK);
		return onAbortTask();
	}
	
	bool bComparedEqual = DBManager::get()->compareDBFiles(pDBFileForIMGTab, pDBFileForIMGFile);
	if(bComparedEqual)
	{
		showMessage("The IMG matches the DB file.", "IMG Matches DB", MB_OK);
	}
	else
	{
		showMessage("The IMG does not match the DB file.", "IMG Doesn't Match DB", MB_OK);
	}

	delete pDBFileForIMGTab;
	delete pDBFileForIMGFile;
	
	onCompleteTask();
}

void			Tasks::validateDFFInTab(void)
{
	onStartTask("validateDFFInTab");

	vector<vector<string>> vecGridCellsText;
	for (IMGEntry *pIMGEntry : getIMGTab()->getIMGFile()->VectorPool::getEntries())
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
		showMessage("All DFF entries in this tab are valid.", "All DFF Valid", MB_OK);
	}
	else
	{
		vector<string> vecGridHeadersText = { "Entry Name", "Error Reason" };
		m_pTaskManager->onPauseTask();
		m_pMainWindow->showGridWindow("Invalid DFF Entries", String::toString(vecGridCellsText.size()) + " invalid DFF entries:", vecGridHeadersText, vecGridCellsText, "");
		m_pTaskManager->onResumeTask();
	}
	
	onCompleteTask();
}

void			Tasks::validateTXDInTab(void)
{
	onStartTask("validateTXDInTab");

	vector<vector<string>> vecGridCellsText;
	for (IMGEntry *pIMGEntry : getIMGTab()->getIMGFile()->VectorPool::getEntries())
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
		showMessage("All TXD entries in this tab are valid.", "All TXD Valid", MB_OK);
	}
	else
	{
		vector<string> vecGridHeadersText = { "Entry Name", "Error Reason" };
		m_pTaskManager->onPauseTask();
		m_pMainWindow->showGridWindow("Invalid TXD Entries", String::toString(vecGridCellsText.size()) + " invalid DFF entries:", vecGridHeadersText, vecGridCellsText, "");
		m_pTaskManager->onResumeTask();
	}

	onCompleteTask();
}

void			Tasks::centerCOLMeshesInSelection(void)
{
	onStartTask("centerCOLMeshesInSelection");

	vector<IMGEntry*> vecIMGEntries = (vector<IMGEntry*>&)getIMGTab()->getSelectedEntries();
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

	getTab()->logf("Centered meshes for %u COL files.", uiEntryCount);

	getIMGTab()->setFileUnsaved(true);

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
	
	showMessage("Aligned " + String::toString(uiAlignedEntryCount) + " COL meshes to DFF meshes.", "Aligned COL to DFF", MB_OK);

	onCompleteTask();
}

void				Tasks::extractDVCAndNVCIntoDFFs(void)
{
	onStartTask("extractDVCAndNVCIntoDFFs");

	// choose DVC, NVC, or both
	m_pTaskManager->onPauseTask();
	uint32 uiUpdateType = m_pMainWindow->show3ButtonWindow("DVC/NVC Extraction Type", "Extract DVC, NVC, or both?", "DVC", "NVC", "Both");
	m_pTaskManager->onResumeTask();
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
		DFFFormat *pDFFFile_Model = DFFManager::get()->unserializeMemory(File::getBinaryFile(strDFFModelDataFolderPath + strDFFFilename_Model));
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
	getTab()->logf("Extracted " + strLogPart1 + " into %u DFF files.", uiDFFUpdatedFileCount);

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
	getTab()->logf("Extracted 2DFX into %u DFF files.", uiDFFUpdatedFileCount);

	onCompleteTask();
}

void		Tasks::imgCompression(void)
{
	onStartTask("imgCompression");

	// ensure IMG version has settings
	if (getIMGTab()->getIMGFile()->getVersion() != IMG_FASTMAN92)
	{
		showMessage("IMG version must be Fastman92's IMG version for compression or encryption.", "Invalid IMG Version for Compression/Encryption", MB_OK);
		return onAbortTask();
	}

	// choose compression status
	m_pTaskManager->onPauseTask();
	uint32 uiButtonIndex = m_pMainWindow->show3ButtonWindow("Compress IMG", "Should IMG be compressed?", "Yes", "No", "");
	m_pTaskManager->onResumeTask();
	if (uiButtonIndex == -1)
	{
		return onAbortTask();
	}

	ECompressionAlgorithm uiCompressionAlgorithm;
	uint32 uiCompressionLevel;
	if (uiButtonIndex == 0) // Button: Yes
	{
		vector<string> vecOptions = { "ZLib", "LZ4" };
		m_pTaskManager->onPauseTask();
		uint32 uiOptionIndex = m_pMainWindow->showDropDownWindow("IMG Compression Algorithm", "IMG compression algorithm:", vecOptions);
		m_pTaskManager->onResumeTask();
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
		m_pTaskManager->onPauseTask();
		uiOptionIndex = m_pMainWindow->showDropDownWindow("Compression Level", "Compression level:", vecOptions);
		m_pTaskManager->onResumeTask();
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
	vector<IMGEntry*> vecIMGEntries = (vector<IMGEntry*>&)getIMGTab()->getSelectedEntries();
	
	// apply new compression type to IMG entries
	setMaxProgress(vecIMGEntries.size());
	for (IMGEntry *pIMGEntry : vecIMGEntries)
	{
		pIMGEntry->applyCompression(uiCompressionAlgorithm, uiCompressionLevel);
		getIMGTab()->updateGridEntry(pIMGEntry);

		increaseProgress();
	}

	// update IMG version text in main window
	getIMGTab()->updateIMGVersionAndCompressionText();

	// log
	getTab()->logf("Updated IMG compression for %u entries.", vecIMGEntries.size());

	// mark as modified since rebuild
	getIMGTab()->setFileUnsaved(true);

	onCompleteTask();
}

void		Tasks::generateCOLFromDFF(void)
{
	onStartTask("generateCOLFromDFF");

	// choose DFF files folder
	string strDFFFolderPath = openFolder("Choose a folder containing DFF files.");
	if (strDFFFolderPath == "")
	{
		return onAbortTask();
	}

	// choose output COL files folder
	string strOutputFolderPath = openFolder("Choose an output folder for the COL files.");
	if (strOutputFolderPath == "")
	{
		return onAbortTask();
	}

	// initialize
	unordered_map<string, Vec3f>
		umapGeometryPolygonCenters;
	vector<string>
		vecFilePaths_DFF = File::getFileNamesByExtension(strDFFFolderPath, "dff"),
		vecFilePaths_BSP = File::getFileNamesByExtension(strDFFFolderPath, "bsp");

	vecFilePaths_DFF = StdVector::combineVectors(vecFilePaths_DFF, vecFilePaths_BSP);

	setMaxProgress(vecFilePaths_DFF.size());

	// convert DFF files to COL files
	uint32 uiGeneratedCount = 0;
	for (string& strDFFFilePath : vecFilePaths_DFF)
	{
		DFFFormat dffFile(strDFFFolderPath + strDFFFilePath);
		if (!dffFile.unserialize())
		{
			dffFile.unload();
			increaseProgress();
			continue;
		}

		COLFormat colFile;
		colFile.setCOLVersion(COL_2);

		vector<RWSection*> vecDFFGeometrySections = dffFile.getSectionsByType(RW_SECTION_GEOMETRY);
		for (RWSection *pRWSection : vecDFFGeometrySections)
		{
			RWSection_Geometry *pGeometry = (RWSection_Geometry*)pRWSection;

			string strTextureDiffuseName = pGeometry->getTextureDiffuseName();
			vector<Vec3f> vecVertices = pGeometry->getVertexPositions();

			vector<TVertex> vecCOLVertices;
			for (Vec3f& vecVertex : vecVertices)
			{
				TVertex vertex;
				vertex.x = vecVertex.x;
				vertex.y = vecVertex.y;
				vertex.z = vecVertex.z;
				vecCOLVertices.push_back(vertex);
			}
			COLEntry *pCOLEntry = new COLEntry(&colFile);
			pCOLEntry->getCollisionMeshVertices() = vecCOLVertices;
			colFile.addEntry(pCOLEntry);
		}

		colFile.serialize(strOutputFolderPath + Path::replaceFileExtensionWithCase(Path::getFileName(strDFFFilePath), "COL"));

		dffFile.unload();
		increaseProgress();

		uiGeneratedCount++;
	}

	showMessage("Generated " + String::toString(uiGeneratedCount) + " COL files from DFF files.", "Generated COL from DFF", MB_OK);

	onCompleteTask();
}

void		Tasks::update(bool bOnlyShowWindowIfUpdateIsAvailable)
{
	onStartTask("update");

	// fetch latest version number
	string strFileContent;
	vector<string> vecFileLines;
	float32 fLatestVersion;
	UpdateConnection *pActiveUpdateConnection = nullptr;
	for (UpdateConnection *pUpdateConnection : getIMGF()->getUpdateManager()->getUpdateConnectionManager()->getEntries())
	{
		pActiveUpdateConnection = pUpdateConnection;

		strFileContent = HTTP::get()->getFileContent(pUpdateConnection->getLatestVersionURL());
		vecFileLines = String::split(strFileContent, "\n");
		fLatestVersion = String::toFloat32(vecFileLines[0]);

		if (fLatestVersion > 0.0f)
		{
			break;
		}
	}

	if (fLatestVersion == 0.0f)
	{
		if (!bOnlyShowWindowIfUpdateIsAvailable)
		{
			Tasks::showMessage("Unable to fetch the latest version.", "Network Error");
		}
		return;
	}

	// compare version numbers
	float32 fCurrentVersion = getIMGF()->getBuildMeta().getCurrentVersion();
	if (fCurrentVersion >= fLatestVersion)
	{
		if (!bOnlyShowWindowIfUpdateIsAvailable)
		{
			Tasks::showMessage("You are already using the latest version, which is " + String::toString(fLatestVersion), "Already Using Latest Version", MB_OK);
		}
		return onAbortTask();
	}

	// ask to update now
	uint32 uiUpdateWindowResult = Tasks::showMessage("Version " + String::toString(fLatestVersion) + " is available, currently using " + String::toString(fCurrentVersion) + "\n\nUpdate now?", "Update Now?", MB_YESNOCANCEL);
	if (uiUpdateWindowResult != IDYES)
	{
		return onAbortTask();
	}

	// fetch latest version
	string strNewProgramFileName = vecFileLines[1];
	string strNewProgramData = HTTP::get()->getFileContent(pActiveUpdateConnection->getDownloadFolderURL() + String::toString(fLatestVersion) + "/" + strNewProgramFileName);

	// update program version
	string strRunningProgramPath = Process::getEXEFilePath();
	string strLockedFileDirectory = Path::getDirectory(strRunningProgramPath);
	string strNewProgramPath = File::getNextIncrementingFileName(strLockedFileDirectory + strNewProgramFileName);

	File::setBinaryFile(strNewProgramPath, strNewProgramData);

	// mark previous version to be deleted
	if (getIMGF()->getSettingsManager()->getSettingBool("RemoveOldVersionOnUpdate"))
	{
		SettingsManager::setInternalSetting("DeletePreviousVersionOnNextLaunch", strRunningProgramPath);
	}

	// open new version
	if (Tasks::showMessage("Update complete, open version " + String::toString(fLatestVersion) + " now?", "Open New Version Now?", MB_YESNO) == IDYES)
	{
		Process::startProcess(strNewProgramPath);
		onCompleteTask();
		ExitProcess(0);
		return;
	}

	onCompleteTask();
}

void		Tasks::associateIMGExtension(void)
{
	// todo
	Registry::assoicateFileExtension("IMG", Process::getEXEFilePath(), "IMGFactory.2");
}



























/*
todo

bool		Tasks::saveAllOpenFiles(bool bCloseAll)
{
	getIMGF()->getLastUsedValueManager()->setLastUsedValue_Close2_CloseAll(bCloseAll); // todo - remove?
	getIMGF()->getTaskManager()->onStartTask("saveAllOpenFiles");
	string strText = "";
	if (bCloseAll)
	{
		uint32 uiModifiedSinceRebuildCount = 0;
		for (auto pEditorTab : getIMGF()->getIMGEditor()->getEditorTabs().getEntries())
		{
			if (((IMGEditorTab*)pEditorTab)->isFileUnsaved())
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
		if (getIMGTab()->isFileUnsaved())
		{
			strText = LocalizationManager::get()->getTranslatedFormattedText("Window_Confirm_4_Message", Path::getFileName(getIMGTab()->getIMGFile()->getFilePath()).c_str());
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
		for (auto pEditorTab : getIMGF()->getIMGEditor()->getEditorTabs().getEntries())
		{
			if (((IMGEditorTab*)pEditorTab)->isFileUnsaved())
			{
				((IMGEditorTab*)pEditorTab)->rebuild();
			}
		}
	}
	else
	{
		getIMGTab()->rebuild();
	}
	getIMGF()->getTaskManager()->onTaskEnd("onRequestClose2");
	return true;
}
*/

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
		uint32 uiResult = showMessage(LocalizationManager::get()->getTranslatedFormattedText("TextPopup_45", strLatestVersion.c_str(), getIMGF()->getBuildMeta().getCurrentVersionString().c_str()), LocalizationManager::get()->getTranslatedText("TextPopupTitle_45"), MB_OKCANCEL);
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
			File::setBinaryFile(strNewProgramPath, strNewProgramData);

			// delete previous version's exe file
			if (getIMGF()->getSettingsManager()->getSettingBool("RemoveOldVersionOnUpdate"))
			{
				TCHAR szModuleName[MAX_PATH];
				GetModuleFileName(NULL, szModuleName, MAX_PATH);
				string strExePath = String::convertStdWStringToStdString(szModuleName);
				SettingsManager::setInternalSetting("DeletePreviousVersionOnNextLaunch", strExePath);
			}

			getIMGF()->getTaskManager()->onPauseTask();
			uint32 uiResult2 = showMessage(LocalizationManager::get()->getTranslatedText("TextPopup_42"), LocalizationManager::get()->getTranslatedText("TextPopupTitle_42"), MB_OKCANCEL);
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

void		Tasks::processTaskByName(string strFeatureName)
{
	/*
	todo

	if (strFeatureName == "processTaskByName")
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