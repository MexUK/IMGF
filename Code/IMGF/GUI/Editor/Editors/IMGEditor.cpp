#include "IMGEditor.h"
#include "Globals.h"
#include "IMGF.h"
#include "Format/IMG/Regular/IMGManager.h"
#include "Format/IMG/Regular/IMGFormatVersion1.h"
#include "Format/IMG/Regular/IMGFormatVersion2.h"
#include "Format/IMG/Regular/IMGFormatVersion3.h"
#include "Format/IMG/Regular/IMGFormatVersionFastman92.h"
#include "Static/String.h"
#include "Static/Path.h"
#include "Static/File.h"
#include "Localization/LocalizationManager.h"
#include "Settings/SettingsManager.h"
#include "Format/COL/COLManager.h"
#include "Format/IMG/Regular/IMGEntry.h"
#include "Engine/RW/RWVersion.h"
#include "Task/TaskManager.h"
#include "Task/Tasks/Tasks.h"
#include "Type/Colour/Colour.h"
#include "BXGX.h"
#include "Control/Controls/Grid.h"
#include "GUI/Editor/Editors/EEditorItem.h"
#include "GUI/Window/Windows/MainWindow/MainWindow.h"
#include "GUI/Layer/Layers/MainLayer/MainLayer.h"
#include "Control/Controls/TabBar.h"
#include "Control/Controls/ProgressBar.h"
#include "Control/Controls/TextBox.h"
#include "Control/Controls/Text.h"
#include "Control/Controls/DropDown.h"
#include "Static/Input.h"
#include "Control/Components/ScrollBarPool.h"
#include "Event/EInputEvent.h"
#include "../BXGI/Event/EEvent.h"
#include "../IMGF/Event/EEvent.h"
#include "GUI/Window/WindowManager.h"
#include "GUI/Layer/Layers/MainLayer/MainLayerNoTabsOpen.h"
#include "GUI/Editor/EEditor.h"

// for menu start - todo
#include "Engine/RW/RWManager.h"
#include "Engine/RW/RWVersionManager.h"
#include "Task/Tasks/RecentlyOpen/RecentlyOpenManager.h"
#include "Task/Tasks/Sort/SortManager.h"
#include "Task/Tasks/Sort/SortType.h"
#include "Task/Tasks/Sort/SortPriority.h"
#include "Task/Tasks/Sort/SortTypes.h"
#include "Task/Tasks/Sort/SortPriorities.h"
#include "Task/Tasks/Sort/SortMenuItems.h"
#include "Image/ImageManager.h"
#include "Image/RasterDataFormatManager.h"
#include "Format/COL/COLVersionManager.h"
#include "Format/COL/COLVersion.h"
// for menu end

using namespace std;
using namespace bxcf;
using namespace bxcf::fileType;
using namespace bxgx;
using namespace bxgx::events;
using namespace bxgi;
using namespace imgf;
using namespace imgf::editor::items;

IMGEditor::IMGEditor(void) :
	Editor(IMG_EDITOR),
	m_pEntryGrid(nullptr),
	m_pEntryTypeFilter(nullptr),
	m_pEntryVersionFilter(nullptr),
	m_uiSelectedEntryCount(0),
	m_uiSearchHitCount(0), // todo - rename to SearchHitEntryCount
	m_uiSearchFileCount(0) // todo - rename to SearchHitFileCount
{
}

void						IMGEditor::init(void)
{
	setEditorFileType(IMG);
	setEditorFileFormats({ "IMG", "DIR" });
	//setImportEditorFileFormats({});

	m_pEditorButton = (Button*)m_pMainWindow->getItemById(1005);

	Editor::init();

	Editor::addControls();
	Editor::initControls();

	addControls();
	initControls();
}

// events
void						IMGEditor::bindEvents(void)
{
	Editor::bindEvents();

	if (m_pActiveEditorTab)
	{
		m_pActiveEditorTab->bindEvents();
	}
}

void						IMGEditor::unbindEvents(void)
{
	Editor::unbindEvents();

	if (m_pActiveEditorTab)
	{
		m_pActiveEditorTab->unbindEvents();
	}
}

IMGEditorTab*				IMGEditor::addEditorTab(string& strFilePath)
{
	IMGFormat imgFormat(strFilePath);
	if(!imgFormat.readMetaData())
	{
		return nullptr;
	}

	IMGEditorTab *pIMGEditorTab;

	switch (imgFormat.getVersion())
	{
	case IMG_1:
		pIMGEditorTab = Editor::_addEditorTab<IMGFormatVersion1, IMGEditorTab>(strFilePath, false);
		break;
	case IMG_2:
		pIMGEditorTab = Editor::_addEditorTab<IMGFormatVersion2, IMGEditorTab>(strFilePath, false);
		break;
	case IMG_3:
		pIMGEditorTab = Editor::_addEditorTab<IMGFormatVersion3, IMGEditorTab>(strFilePath, false);
		break;
	case IMG_FASTMAN92:
		pIMGEditorTab = Editor::_addEditorTab<IMGFormatVersionFastman92, IMGEditorTab>(strFilePath, false);
		break;
	default:
		pIMGEditorTab = nullptr;
		break;
	}

	if (pIMGEditorTab)
	{
		pIMGEditorTab->setIMGEditor(this);
		pIMGEditorTab->setIMGFile((IMGFormat*)pIMGEditorTab->getFile());
		if (!pIMGEditorTab->init(false))
		{
			removeEditorTab(pIMGEditorTab);
			return nullptr;
		}
	}
	return pIMGEditorTab;
}

// add editor tab
IMGEditorTab*				IMGEditor::addBlankEditorTab(string& strFilePath)
{
	return addBlankEditorTab(strFilePath, IMG_1);
}

IMGEditorTab*				IMGEditor::addBlankEditorTab(string& strFilePath, EIMGVersion uiIMGVersion)
{
	IMGEditorTab *pIMGEditorTab;

	switch (uiIMGVersion)
	{
	case IMG_1:
		pIMGEditorTab = Editor::_addEditorTab<IMGFormatVersion1, IMGEditorTab>(strFilePath, true);
		break;
	case IMG_2:
		pIMGEditorTab = Editor::_addEditorTab<IMGFormatVersion2, IMGEditorTab>(strFilePath, true);
		break;
	case IMG_3:
		pIMGEditorTab = Editor::_addEditorTab<IMGFormatVersion3, IMGEditorTab>(strFilePath, true);
		break;
	case IMG_FASTMAN92:
		pIMGEditorTab = Editor::_addEditorTab<IMGFormatVersionFastman92, IMGEditorTab>(strFilePath, true);
		break;
	default:
		pIMGEditorTab = nullptr;
		break;
	}

	if (pIMGEditorTab)
	{
		pIMGEditorTab->setIMGEditor(this);
		pIMGEditorTab->setIMGFile((IMGFormat*)pIMGEditorTab->getFile());
		if (uiIMGVersion == IMG_3)
		{
			pIMGEditorTab->getIMGFile()->setEncrypted(true);
		}
		pIMGEditorTab->init(true);
	}
	
	return pIMGEditorTab;
}

// remove editor tab
void						IMGEditor::removeEditorTab(IMGEditorTab *pIMGEditorTab)
{
	pIMGEditorTab->setMarkedToClose(true);
	while (!pIMGEditorTab->hasThreadTerminated())
	{
		Sleep(10);
	}
	pIMGEditorTab->getThread().join();

	Editor::removeEditorTab(pIMGEditorTab);

	mutexRenderItems.lock();

	m_pMainWindow->removeLayer(pIMGEditorTab->getLayer());
	delete pIMGEditorTab;

	mutexRenderItems.unlock();

	mutexRendering.lock();

	if (getEditorTabs().getEntryCount() == 0)
	{
		// todo getLayer()->setEnabled(true);
		getIMGF()->getWindowManager()->getMainWindow()->getMainLayerNoTabsOpen()->setEnabled(true);
		m_pMainWindow->getMainLayer()->setCertainMenuItemsEnabled(false);
	}
	else
	{
		m_pActiveEditorTab->getLayer()->setEnabled(true);
	}

	mutexRendering.unlock();
}

void						IMGEditor::removeActiveEditorTab(void)
{
	if (getEditorTabs().getEntryCount() == 0)
	{
		return;
	}

	removeEditorTab((IMGEditorTab*)getActiveEditorTab());
}

// active tab
void						IMGEditor::setActiveTab(IMGEditorTab *pEditorTab)
{
	Editor::setActiveEditorTab(pEditorTab);
	
	//pEditorTab->readdAllEntriesToMainListView();
	
	// todo
	return;

	vector<uint16> vecButtonIds = {16,17,18,25,26,27,28,29,31,32,33,34,35,36,40,41,42,43,45,47};

	if (pEditorTab == nullptr)
	{
		/*
		todo
		getIMGF()->getTaskManager()->setTaskMaxProgressTickCount(((CListCtrl*)getIMGF()->getDialog()->GetDlgItem(37))->GetItemCount());

		// disable buttons
		for (uint16 usButtonId : vecButtonIds)
		{
			((Button*)getIMGF()->getDialog()->GetDlgItem(usButtonId))->EnableWindow(0);
		}

		// IMG path
		((CEdit*)getIMGF()->getDialog()->GetDlgItem(38))->SetWindowTextW(_T(""));

		// IMG entry count
		((CStatic*)getIMGF()->getDialog()->GetDlgItem(20))->SetWindowTextW(LocalizationManager::get()->getTranslatedFormattedTextW("Window_Main_Text_EntryCount", 0).c_str());

		// selected entry count
		((CStatic*)getIMGF()->getDialog()->GetDlgItem(51))->SetWindowTextW(LocalizationManager::get()->getTranslatedFormattedTextW("Window_Main_Text_SelectedEntryCount", 0).c_str());

		// IMG version
		((CStatic*)getIMGF()->getDialog()->GetDlgItem(19))->SetWindowTextW(LocalizationManager::get()->getTranslatedTextW("Window_Main_Text_IMGVersion").c_str());
		*/

		// 6th column name in main list view
		readdColumnsToMainListView(IMG_UNKNOWN);

		/*
		// search text
		((CEdit*)getIMGF()->getDialog()->GetDlgItem(24))->SetWindowTextW(_T(""));
		((CStatic*)getIMGF()->getDialog()->GetDlgItem(0))->SetWindowTextW(LocalizationManager::get()->getTranslatedFormattedTextW("Window_Main_Text_SearchResult_ActiveTab", 0).c_str());
		((CListCtrl*)getIMGF()->getDialog()->GetDlgItem(22))->DeleteAllItems();
		for (auto pSearchEntry : m_vecSearchEntries)
		{
			delete pSearchEntry;
		}
		m_vecSearchEntries.clear();

		// filter
		pEditorTab->unloadFilter_Type();
		pEditorTab->unloadFilter_Version();

		// log
		((CEdit*)getIMGF()->getDialog()->GetDlgItem(14))->SetWindowTextW(_T(""));

		// IMG entries
		//((CListCtrl*)m_pDialog->GetDlgItem(37))->DeleteAllItems();
		CListCtrl *pMainListCtrl = ((CListCtrl*)getIMGF()->getDialog()->GetDlgItem(37));
		for (uint32 i = 0, j = pMainListCtrl->GetItemCount(); i < j; i++)
		{
			pMainListCtrl->DeleteItem((j - 1) - i);
			getIMGF()->getTaskManager()->onTaskProgressTick();
		}
		*/
	}
	else
	{
		/*
		todo
		// enable buttons
		for (uint16 usButtonId : vecButtonIds)
		{
			((Button*)getIMGF()->getDialog()->GetDlgItem(usButtonId))->EnableWindow(1);
		}

		// tab focus
		((TabCtrl*)getIMGF()->getDialog()->GetDlgItem(1))->SetCurFocus(pEditorTab->getIndex());

		// IMG path
		((CEdit*)getIMGF()->getDialog()->GetDlgItem(38))->SetWindowTextW(String::convertStdStringToStdWString(pEditorTab->getIMGFile()->getFilePath()).c_str());

		// IMG entry count
		pEditorTab->updateEntryCountText();

		// selected entry count
		m_uiSelectedEntryCount = 0;
		((CStatic*)getIMGF()->getDialog()->GetDlgItem(51))->SetWindowTextW(LocalizationManager::get()->getTranslatedFormattedTextW("Window_Main_Text_SelectedEntryCount", 0).c_str());

		// IMG version
		pEditorTab->updateIMGText();
		*/

		// 6th column name in main list view
		readdColumnsToMainListView(pEditorTab->getIMGFile()->getVersion());

		/*
		// search text
		if (((Button*)getIMGF()->getDialog()->GetDlgItem(46))->GetCheck() == BST_UNCHECKED)
		{
			((CEdit*)getIMGF()->getDialog()->GetDlgItem(24))->SetWindowTextW(String::convertStdStringToStdWString(pEditorTab->getSearchText()).c_str());
			pEditorTab->searchText();
		}

		// filter
		pEditorTab->loadFilter_Type();
		pEditorTab->loadFilter_Version();

		// log
		CEdit *pEdit = ((CEdit*)getIMGF()->getDialog()->GetDlgItem(14));
		pEdit->SetWindowTextW(String::convertStdStringToStdWString(String::join(pEditorTab->getLogLinesGUI(), "\r\n")).c_str());
		pEdit->LineScroll(pEdit->GetLineCount());

		// IMG entries
		pEditorTab->readdAllEntriesToMainListView();
		*/
	}
}

void					IMGEditor::readdColumnsToMainListView(EIMGVersion EIMGVersionValue)
{
	removeColumnsFromMainListView();
	((IMGEditorTab*)getActiveEditorTab())->addGridHeaders(EIMGVersionValue);
}

void					IMGEditor::removeColumnsFromMainListView(void)
{
	/*
	todo
	CListCtrl *pListCtrl = (CListCtrl*)getIMGF()->getDialog()->GetDlgItem(37);
	while (pListCtrl->DeleteColumn(0) != 0)
	{
	}
	*/
}
int						IMGEditor::getMainListControlItemByEntry(IMGEntry *pIMGEntry)
{
	/*
	todo
	CListCtrl *pListControlMain = (CListCtrl*)getIMGF()->getDialog()->GetDlgItem(37);
	for (uint32 i = 0, j = pListControlMain->GetItemCount(); i < j; i++)
	{
		if (pListControlMain->GetItemData(i) == (DWORD)pIMGEntry)
		{
			return i;
		}
	}
	*/
	return 0;
}

void					IMGEditor::onSelectIMGEntry(bool bEntryIsSelected)
{
	// todo - have onSelectIMGEntry and onUnselectIMGEntry
	if (bEntryIsSelected)
	{
		m_uiSelectedEntryCount++;
	}
	else
	{
		m_uiSelectedEntryCount--;
	}

	// selected entry count
	updateSelectedEntryCountText();
}

void					IMGEditor::updateSelectedEntryCountText(void)
{
	// todo ((CStatic*)getIMGF()->getDialog()->GetDlgItem(51))->SetWindowTextW(LocalizationManager::get()->getTranslatedFormattedTextW("Window_Main_Text_SelectedEntryCount", m_uiSelectedEntryCount).c_str());
}

void					IMGEditor::logAllTabs(string strText, bool bExtendedModeOnly)
{
	for (auto pEditorTab : getEditorTabs().getEntries())
	{
		// todo - ((IMGEditorTab*)pEditorTab)->log(strText, bExtendedModeOnly);
	}
}

void					IMGEditor::logWithNoTabsOpen(string strText, bool bExtendedModeOnly)
{
	// todo - remove function?
	string strLogEntryWithTimestampAndIMG = "[" + String::getTimestampText() + "] [" + LocalizationManager::get()->getTranslatedText("NoTabsOpen") + "] " + strText;

	if (bExtendedModeOnly)
	{
		//m_vecLogLinesExtended.push_back(strLogEntryWithTimestampAndIMG);

		// automatic logging to file
		if (getIMGF()->getSettingsManager()->getSetting("AutomaticLoggingPath") != "")
		{
			// extended file
			if (getIMGF()->getSettingsManager()->getSettingBool("AutomaticLoggingExtended"))
			{
				string strExtendedLogPath = Path::addSlashToEnd(getIMGF()->getSettingsManager()->getSetting("AutomaticLoggingPath"));
				strExtendedLogPath += String::getDateTextForFolder() + "/" + LocalizationManager::get()->getTranslatedText("LogFilename_Extended");
				File::addToTextFile(strExtendedLogPath, strLogEntryWithTimestampAndIMG + "\n");
			}
		}
	}
	else
	{
		//m_vecLogLinesGUI.push_back(strText);
		//m_vecLogLinesBasic.push_back(strLogEntryWithTimestampAndIMG);
		//m_vecLogLinesExtended.push_back(strLogEntryWithTimestampAndIMG);

		// automatic logging to file
		if (getIMGF()->getSettingsManager()->getSetting("AutomaticLoggingPath") != "")
		{
			// basic file
			if (getIMGF()->getSettingsManager()->getSettingBool("AutomaticLoggingBasic"))
			{
				string strExtendedLogPath = Path::addSlashToEnd(getIMGF()->getSettingsManager()->getSetting("AutomaticLoggingPath"));
				strExtendedLogPath += String::getDateTextForFolder() + "/" + LocalizationManager::get()->getTranslatedText("LogFilename_Basic");
				File::addToTextFile(strExtendedLogPath, strLogEntryWithTimestampAndIMG + "\n");
			}

			// extended file
			if (getIMGF()->getSettingsManager()->getSettingBool("AutomaticLoggingExtended"))
			{
				string strExtendedLogPath = Path::addSlashToEnd(getIMGF()->getSettingsManager()->getSetting("AutomaticLoggingPath"));
				strExtendedLogPath += String::getDateTextForFolder() + "/" + LocalizationManager::get()->getTranslatedText("LogFilename_Extended");
				File::addToTextFile(strExtendedLogPath, strLogEntryWithTimestampAndIMG + "\n");
			}
		}
	}
}

uint32					IMGEditor::getEntryCountForAllTabs(void)
{
	uint32 uiTotalEntryCount = 0;
	for (auto pEditorTab : getEditorTabs().getEntries())
	{
		uiTotalEntryCount += ((IMGEditorTab*)pEditorTab)->getIMGFile()->getEntryCount();
	}
	return uiTotalEntryCount;
}

vector<IMGFormat*>		IMGEditor::getAllMainWindowTabsIMGFiles(void)
{
	vector<IMGFormat*> vecIMGFormats;
	for (auto pEditorTab : getEditorTabs().getEntries())
	{
		vecIMGFormats.push_back(((IMGEditorTab*)pEditorTab)->getIMGFile());
	}
	return vecIMGFormats;
}

void					IMGEditor::refreshActiveTab(void)
{
	setActiveTab(getActiveTab());
}

void					IMGEditor::initMenu(void) // todo - move menu stuff to like MenuManager
{
	/*
	HMENU hMenubar = CreateMenu();

	getIMGF()->m_hMenu_File = CreateMenu();
	HMENU
		hMenu_File = getIMGF()->m_hMenu_File,
		hMenu_Edit = CreateMenu(),
		hMenu_DAT = CreateMenu(),
		hMenu_IMG = CreateMenu(),
		hMenu_Model = CreateMenu(),
		hMenu_Texture = CreateMenu(),
		hMenu_Collision = CreateMenu(),
		hMenu_ItemDefinition = CreateMenu(),
		hMenu_ItemPlacement = CreateMenu(),
		hMenu_Entry = CreateMenu(),
		hMenu_Settings = CreateMenu(),
		hMenu_Help = CreateMenu()
		;

	HMENU hMenu_File_New = CreatePopupMenu();
	HMENU hMenu_File_New_Version3 = CreatePopupMenu();
	HMENU hMenu_File_SaveLog = CreatePopupMenu();
	HMENU hMenu_File_SaveLog_ActiveTab = CreatePopupMenu();
	HMENU hMenu_File_SaveLog_AllTabs = CreatePopupMenu();
	getIMGF()->m_hSubMenu_File_OpenRecent = CreatePopupMenu();
	getIMGF()->m_hSubMenu_File_Sessions = CreatePopupMenu();
	HMENU hMenu_File_Sessions = CreateMenu();

	HMENU hMenu_Edit_Select = CreatePopupMenu();
	HMENU hMenu_Edit_SelectViaRWVersion = CreatePopupMenu();

	HMENU hMenu_IMG_ConvertTo = CreatePopupMenu();
	HMENU hMenu_IMG_ConvertTo_Version3 = CreatePopupMenu();
	HMENU hMenu_IMG_Split = CreatePopupMenu();
	HMENU hMenu_IMG_Validation = CreatePopupMenu();

	getIMGF()->m_hMenu_Entry_Sort = CreatePopupMenu();
	HMENU hMenu_Entry_Import = CreatePopupMenu();
	HMENU hMenu_Entry_Export = CreatePopupMenu();
	HMENU hMenu_Entry_Remove = CreatePopupMenu();
	HMENU hMenu_Entry_Replace = CreatePopupMenu();
	HMENU hMenu_Entry_Case = CreatePopupMenu();
	HMENU hMenu_Entry_Copy = CreatePopupMenu();
	HMENU hMenu_Entry_LowerCase = CreatePopupMenu();
	HMENU hMenu_Entry_UpperCase = CreatePopupMenu();
	HMENU hMenu_Entry_TitleCase = CreatePopupMenu();
	HMENU hMenu_Entry_Shift = CreatePopupMenu();

	HMENU hMenu_Collision_Convert = CreatePopupMenu();

	HMENU hMenu_Model_Convert = CreatePopupMenu();
	HMENU hMenu_Model_Convert_DFFRWVersion = CreatePopupMenu();
	HMENU hMenu_Model_Convert_DFFFileFormat = CreatePopupMenu();

	HMENU hMenu_Texture_Convert = CreatePopupMenu();
	HMENU hMenu_Texture_Convert_TXDGame = CreatePopupMenu();
	HMENU hMenu_Texture_Convert_TXDRWVersion = CreatePopupMenu();
	HMENU hMenu_Texture_Convert_TXDTextureFormat = CreatePopupMenu();
	HMENU hMenu_Texture_Convert_WTDFileFormat = CreatePopupMenu();

	HMENU hMenu_ItemDefinition_FindOrphanEntries = CreatePopupMenu();
	HMENU hMenu_ItemDefinition_FindMissing = CreatePopupMenu();

	HMENU hMenu_ItemPlacement_FindMissing = CreatePopupMenu();

	HMENU hMenu_Entry_Sort_Priorities[10];
	for (uint32 i = 0; i < 10; i++)
	{
		hMenu_Entry_Sort_Priorities[i] = CreatePopupMenu();
	}

	AppendMenu(hMenubar, MF_POPUP, (UINT_PTR)hMenu_File, LocalizationManager::get()->getTranslatedTextW("Menu_File").c_str());
	AppendMenu(hMenubar, MF_POPUP, (UINT_PTR)hMenu_Edit, LocalizationManager::get()->getTranslatedTextW("Menu_Edit").c_str());
	AppendMenu(hMenubar, MF_POPUP, (UINT_PTR)hMenu_DAT, LocalizationManager::get()->getTranslatedTextW("Menu_DAT").c_str());
	AppendMenu(hMenubar, MF_POPUP, (UINT_PTR)hMenu_IMG, LocalizationManager::get()->getTranslatedTextW("Menu_IMG").c_str());
	AppendMenu(hMenubar, MF_POPUP, (UINT_PTR)hMenu_Model, LocalizationManager::get()->getTranslatedTextW("Menu_Model").c_str());
	AppendMenu(hMenubar, MF_POPUP, (UINT_PTR)hMenu_Texture, LocalizationManager::get()->getTranslatedTextW("Menu_Texture").c_str());
	AppendMenu(hMenubar, MF_POPUP, (UINT_PTR)hMenu_Collision, LocalizationManager::get()->getTranslatedTextW("Menu_Collision").c_str());
	AppendMenu(hMenubar, MF_POPUP, (UINT_PTR)hMenu_ItemDefinition, LocalizationManager::get()->getTranslatedTextW("Menu_ItemDefinition").c_str());
	AppendMenu(hMenubar, MF_POPUP, (UINT_PTR)hMenu_ItemPlacement, LocalizationManager::get()->getTranslatedTextW("Menu_ItemPlacement").c_str());
	AppendMenu(hMenubar, MF_POPUP, (UINT_PTR)hMenu_Entry, LocalizationManager::get()->getTranslatedTextW("Menu_Entry").c_str());
	AppendMenu(hMenubar, MF_POPUP, (UINT_PTR)hMenu_Settings, LocalizationManager::get()->getTranslatedTextW("Menu_Settings").c_str());
	AppendMenu(hMenubar, MF_POPUP, (UINT_PTR)hMenu_Help, LocalizationManager::get()->getTranslatedTextW("Menu_Help").c_str());

	//AppendMenu(hMenubar, MF_POPUP, (UINT_PTR)hMenu_File, _T("&File"));
	AppendMenu(hMenu_File, MF_STRING | MF_POPUP, (UINT_PTR)hMenu_File_New, LocalizationManager::get()->getTranslatedTextW("Menu_NewIMG").c_str());
	AppendMenu(hMenu_File_New, MF_STRING, 1108, LocalizationManager::get()->getTranslatedTextW("Menu_New_V1").c_str());
	AppendMenu(hMenu_File_New, MF_STRING, 1109, LocalizationManager::get()->getTranslatedTextW("Menu_New_V2").c_str());
	AppendMenu(hMenu_File_New, MF_STRING | MF_POPUP, (UINT_PTR)hMenu_File_New_Version3, LocalizationManager::get()->getTranslatedTextW("Menu_New_V3").c_str());
	AppendMenu(hMenu_File_New_Version3, MF_STRING, 1112, LocalizationManager::get()->getTranslatedTextW("Menu_New_V3_Encrypted").c_str());
	AppendMenu(hMenu_File_New_Version3, MF_STRING, 1113, LocalizationManager::get()->getTranslatedTextW("Menu_New_V3_Unencrypted").c_str());
	AppendMenu(hMenu_File_New, MF_SEPARATOR, 1942, _T(""));
	AppendMenu(hMenu_File_New, MF_STRING, 1943, LocalizationManager::get()->getTranslatedTextW("Menu_New_VFastman92").c_str());
	AppendMenu(hMenu_File, MF_STRING, 2084, LocalizationManager::get()->getTranslatedTextW("Menu_NewWindow").c_str());
	AppendMenu(hMenu_File, MF_SEPARATOR, 1760, _T(""));
	AppendMenu(hMenu_File, MF_STRING, 1100, LocalizationManager::get()->getTranslatedTextW("Open").c_str());
	AppendMenu(hMenu_File, MF_STRING | MF_POPUP, (UINT_PTR)getIMGF()->m_hSubMenu_File_OpenRecent, LocalizationManager::get()->getTranslatedTextW("Menu_OpenRecent").c_str());
	AppendMenu(hMenu_File, MF_STRING, 1117, String::convertStdStringToStdWString(LocalizationManager::get()->getTranslatedText("Menu_OpenLast") + (getIMGF()->getRecentlyOpenManager()->getLastOpenEntry() == "" ? "" : " (" + Path::getFileName(getIMGF()->getRecentlyOpenManager()->getLastOpenEntry()) + ")")).c_str());
	AppendMenu(hMenu_File, MF_STRING, 1114, LocalizationManager::get()->getTranslatedTextW("Menu_Reopen").c_str());
	//AppendMenu(hMenu_File, MF_STRING, 1109, _T("Associate IMG extension"));
	AppendMenu(hMenu_File, MF_STRING | MF_POPUP, (UINT_PTR)hMenu_File_Sessions, LocalizationManager::get()->getTranslatedTextW("Menu_Sessions").c_str());
	AppendMenu(hMenu_File_Sessions, MF_STRING | MF_POPUP, (UINT_PTR)getIMGF()->m_hSubMenu_File_Sessions, LocalizationManager::get()->getTranslatedTextW("Menu_LoadSession").c_str());
	AppendMenu(hMenu_File_Sessions, MF_STRING, 1111, LocalizationManager::get()->getTranslatedTextW("Menu_SaveSession").c_str());
	AppendMenu(hMenu_File_Sessions, MF_STRING, 1118, LocalizationManager::get()->getTranslatedTextW("SessionManager").c_str());
	AppendMenu(hMenu_File, MF_SEPARATOR, 1761, _T(""));
	AppendMenu(hMenu_File, MF_STRING | MF_POPUP, (UINT_PTR)hMenu_File_SaveLog, LocalizationManager::get()->getTranslatedTextW("Log").c_str());
	AppendMenu(hMenu_File_SaveLog, MF_STRING | MF_POPUP, (UINT_PTR)hMenu_File_SaveLog_ActiveTab, LocalizationManager::get()->getTranslatedTextW("Menu_Log_ActiveTab").c_str());
	AppendMenu(hMenu_File_SaveLog, MF_STRING | MF_POPUP, (UINT_PTR)hMenu_File_SaveLog_AllTabs, LocalizationManager::get()->getTranslatedTextW("AllTabs").c_str());
	AppendMenu(hMenu_File_SaveLog_ActiveTab, MF_STRING, 1101, LocalizationManager::get()->getTranslatedTextW("Menu_Log_ActiveTab_SaveBasic").c_str());
	AppendMenu(hMenu_File_SaveLog_ActiveTab, MF_STRING, 1102, LocalizationManager::get()->getTranslatedTextW("Menu_Log_ActiveTab_SaveExtended").c_str());
	AppendMenu(hMenu_File_SaveLog_ActiveTab, MF_STRING, 1121, LocalizationManager::get()->getTranslatedTextW("Menu_Log_ActiveTab_Clear").c_str());
	AppendMenu(hMenu_File_SaveLog_ActiveTab, MF_STRING, 1103, LocalizationManager::get()->getTranslatedTextW("Menu_Log_ActiveTab_OpenFileBasic").c_str());
	AppendMenu(hMenu_File_SaveLog_ActiveTab, MF_STRING, 1104, LocalizationManager::get()->getTranslatedTextW("Menu_Log_ActiveTab_OpenFileExtended").c_str());
	AppendMenu(hMenu_File_SaveLog_ActiveTab, MF_STRING, 1120, LocalizationManager::get()->getTranslatedTextW("Menu_Log_ActiveTab_OpenFolder").c_str());
	AppendMenu(hMenu_File_SaveLog_AllTabs, MF_STRING, 1115, LocalizationManager::get()->getTranslatedTextW("Menu_Log_AllTabs_SaveBasic").c_str());
	AppendMenu(hMenu_File_SaveLog_AllTabs, MF_STRING, 1116, LocalizationManager::get()->getTranslatedTextW("Menu_Log_AllTabs_SaveExtended").c_str());
	AppendMenu(hMenu_File_SaveLog_AllTabs, MF_STRING, 1122, LocalizationManager::get()->getTranslatedTextW("Menu_Log_AllTabs_Clear").c_str());
	AppendMenu(hMenu_File, MF_SEPARATOR, 1762, _T(""));
	AppendMenu(hMenu_File, MF_STRING, 1926, LocalizationManager::get()->getTranslatedTextW("Menu_RepeatLastAction").c_str());
	AppendMenu(hMenu_File, MF_STRING, 1179, LocalizationManager::get()->getTranslatedTextW("RenameIMG").c_str());
	AppendMenu(hMenu_File, MF_STRING, 1752, LocalizationManager::get()->getTranslatedTextW("Menu_OpenIMGFolder").c_str());
	AppendMenu(hMenu_File, MF_SEPARATOR, 1927, _T(""));
	AppendMenu(hMenu_File, MF_STRING, 1105, LocalizationManager::get()->getTranslatedTextW("Close").c_str());
	AppendMenu(hMenu_File, MF_STRING, 1106, LocalizationManager::get()->getTranslatedTextW("CloseAll").c_str());
	AppendMenu(hMenu_File, MF_STRING, 1107, LocalizationManager::get()->getTranslatedTextW("Menu_ExitTool").c_str());

	AppendMenu(hMenu_Edit, MF_STRING, 1180, LocalizationManager::get()->getTranslatedTextW("Find").c_str());
	AppendMenu(hMenu_Edit, MF_STRING, 1181, LocalizationManager::get()->getTranslatedTextW("Menu_Find_AllTabs").c_str());
	AppendMenu(hMenu_Edit, MF_SEPARATOR, 1720, _T(""));
	AppendMenu(hMenu_Edit, MF_STRING | MF_POPUP, (UINT_PTR)hMenu_Edit_Select, LocalizationManager::get()->getTranslatedTextW("Menu_Select").c_str());
	AppendMenu(hMenu_Edit_Select, MF_STRING, 1167, LocalizationManager::get()->getTranslatedTextW("Select_All").c_str());
	AppendMenu(hMenu_Edit_Select, MF_STRING, 1168, LocalizationManager::get()->getTranslatedTextW("Select_Inverse").c_str());
	AppendMenu(hMenu_Edit_Select, MF_SEPARATOR, 1730, _T(""));
	AppendMenu(hMenu_Edit_Select, MF_STRING, 1560, LocalizationManager::get()->getTranslatedTextW("Menu_Select_Extensions").c_str());
	AppendMenu(hMenu_Edit_Select, MF_STRING | MF_POPUP, (UINT_PTR)hMenu_Edit_SelectViaRWVersion, LocalizationManager::get()->getTranslatedTextW("Menu_Select_RWVersion").c_str());
	AppendMenu(hMenu_Edit_Select, MF_STRING, 1900, LocalizationManager::get()->getTranslatedTextW("Menu_Select_IDE").c_str());
	uint32 i = 0;
	for (auto pRWVersion : RWManager::get()->getVersionManager()->getEntries())
	{
		getIMGF()->m_umapMenuItemMapping_SelectRWVersion[1561 + i] = pRWVersion;
		string strMenuText = LocalizationManager::get()->getTranslatedText("Menu_Select_RWVersion_Prefix") + " " + String::escapeMenuText((pRWVersion->getVersionText() + " (" + LocalizationManager::get()->getTranslatedText(pRWVersion->getLocalizationKey()) + ")").substr(0, 2)) + "&" + String::escapeMenuText((pRWVersion->getVersionText() + " (" + LocalizationManager::get()->getTranslatedText(pRWVersion->getLocalizationKey()) + ")").substr(2));
		AppendMenu(hMenu_Edit_SelectViaRWVersion, MF_STRING, 1561 + i, String::convertStdStringToStdWString(strMenuText).c_str());
		i++;
	}
	AppendMenu(hMenu_Edit_SelectViaRWVersion, MF_SEPARATOR, 1731, _T(""));
	AppendMenu(hMenu_Edit_SelectViaRWVersion, MF_STRING, 1568, String::convertStdStringToStdWString(LocalizationManager::get()->getTranslatedText("Menu_Select_RWVersion_Prefix") + " " + LocalizationManager::get()->getTranslatedText("Window_Main_Combo_RWVersion_Unknown")).c_str());
	AppendMenu(hMenu_Edit, MF_SEPARATOR, 1185, _T(""));
	AppendMenu(hMenu_Edit, MF_STRING, 1182, LocalizationManager::get()->getTranslatedTextW("Menu_Import").c_str());
	AppendMenu(hMenu_Edit, MF_STRING, 1183, LocalizationManager::get()->getTranslatedTextW("Menu_Replace").c_str());
	AppendMenu(hMenu_Edit, MF_STRING, 1184, LocalizationManager::get()->getTranslatedTextW("Menu_Remove").c_str());

	AppendMenu(hMenu_DAT, MF_STRING, 2056, LocalizationManager::get()->getTranslatedTextW("Menu_DATPathsMover").c_str());
	AppendMenu(hMenu_DAT, MF_STRING, 2057, LocalizationManager::get()->getTranslatedTextW("Menu_DATModelList").c_str());

	AppendMenu(hMenu_IMG, MF_STRING, 1140, LocalizationManager::get()->getTranslatedTextW("Rebuild").c_str());
	AppendMenu(hMenu_IMG, MF_STRING, 1141, LocalizationManager::get()->getTranslatedTextW("Menu_RebuildAs").c_str());
	AppendMenu(hMenu_IMG, MF_STRING, 1142, LocalizationManager::get()->getTranslatedTextW("RebuildAll").c_str());
	AppendMenu(hMenu_IMG, MF_SEPARATOR, 1740, _T(""));
	AppendMenu(hMenu_IMG, MF_STRING | MF_POPUP, (UINT_PTR)hMenu_IMG_ConvertTo, LocalizationManager::get()->getTranslatedTextW("Menu_ConvertToVersion").c_str());
	AppendMenu(hMenu_IMG_ConvertTo, MF_STRING, 1143, LocalizationManager::get()->getTranslatedTextW("Menu_ConvertToVersion1").c_str());
	AppendMenu(hMenu_IMG_ConvertTo, MF_STRING, 1144, LocalizationManager::get()->getTranslatedTextW("Menu_ConvertToVersion2").c_str());
	AppendMenu(hMenu_IMG_ConvertTo, MF_STRING | MF_POPUP, (UINT_PTR)hMenu_IMG_ConvertTo_Version3, LocalizationManager::get()->getTranslatedTextW("Menu_ConvertToVersion3").c_str());
	AppendMenu(hMenu_IMG_ConvertTo_Version3, MF_STRING, 1145, LocalizationManager::get()->getTranslatedTextW("Menu_ConvertToVersion3Encrypted").c_str());
	AppendMenu(hMenu_IMG_ConvertTo_Version3, MF_STRING, 1146, LocalizationManager::get()->getTranslatedTextW("Menu_ConvertToVersion3Unencrypted").c_str());
	AppendMenu(hMenu_IMG_ConvertTo, MF_SEPARATOR, 2200, _T(""));
	AppendMenu(hMenu_IMG_ConvertTo, MF_STRING, 2201, LocalizationManager::get()->getTranslatedTextW("Menu_ConvertToVersionFastman92").c_str());
	AppendMenu(hMenu_IMG, MF_STRING, 1147, LocalizationManager::get()->getTranslatedTextW("Merge").c_str());
	AppendMenu(hMenu_IMG, MF_STRING | MF_POPUP, (UINT_PTR)hMenu_IMG_Split, LocalizationManager::get()->getTranslatedTextW("Split").c_str());
	AppendMenu(hMenu_IMG_Split, MF_STRING, 1156, LocalizationManager::get()->getTranslatedTextW("Menu_SplitSelected").c_str());
	AppendMenu(hMenu_IMG_Split, MF_STRING, 1157, LocalizationManager::get()->getTranslatedTextW("Menu_SplitIDE").c_str());
	AppendMenu(hMenu_IMG_Split, MF_STRING, 1158, LocalizationManager::get()->getTranslatedTextW("Menu_SplitTextLines").c_str());
	AppendMenu(hMenu_IMG, MF_SEPARATOR, 1741, _T(""));

	AppendMenu(hMenu_IMG, MF_STRING | MF_POPUP, (UINT_PTR)getIMGF()->m_hMenu_Entry_Sort, LocalizationManager::get()->getTranslatedTextW("Sort").c_str());
	for (uint32 i = 0; i < 10; i++)
	{
		AppendMenu(getIMGF()->m_hMenu_Entry_Sort, MF_STRING | MF_POPUP, (UINT_PTR)hMenu_Entry_Sort_Priorities[i], LocalizationManager::get()->getTranslatedFormattedTextW("Sort_Priority_N", (i + 1)).c_str());
		uint32 i2 = 0;
		for (auto pSortType : getIMGF()->getSortManager()->getSortTypes()->getEntries())
		{
			SortPriority *pSortPriority = getIMGF()->getSortManager()->getSortPriorities()->getEntryByIndex((uint16)i);

			uint32 uiMenuHandle = 1200 + (20 * i) + i2;
			AppendMenu(hMenu_Entry_Sort_Priorities[i], MF_STRING, uiMenuHandle, LocalizationManager::get()->getTranslatedFormattedTextW("Sort_ByText", pSortType->getTextForMenu().c_str()).c_str());
			getIMGF()->getSortManager()->getSortMenuItems()->addEntry(new SortMenuItem(uiMenuHandle, pSortPriority, pSortType));
			i2++;
		}
	}

	AppendMenu(hMenu_IMG, MF_STRING, 2050, LocalizationManager::get()->getTranslatedTextW("Renamer").c_str());
	AppendMenu(hMenu_IMG, MF_STRING, 1155, LocalizationManager::get()->getTranslatedTextW("UpdateLST").c_str());
	AppendMenu(hMenu_IMG, MF_SEPARATOR, 1743, _T(""));
	AppendMenu(hMenu_IMG, MF_STRING, 2090, LocalizationManager::get()->getTranslatedTextW("CloneIMG").c_str());
	AppendMenu(hMenu_IMG, MF_STRING, 1153, LocalizationManager::get()->getTranslatedTextW("DuplicateEntries").c_str());
	AppendMenu(hMenu_IMG, MF_STRING | MF_POPUP, (UINT_PTR)hMenu_IMG_Validation, LocalizationManager::get()->getTranslatedTextW("Menu_Validation").c_str());
	AppendMenu(hMenu_IMG_Validation, MF_STRING, 2002, LocalizationManager::get()->getTranslatedTextW("Menu_Validation_SaveIMGSignature").c_str());
	AppendMenu(hMenu_IMG_Validation, MF_STRING, 2003, LocalizationManager::get()->getTranslatedTextW("Menu_Validation_VerifyIMGSignature").c_str());
	AppendMenu(hMenu_IMG_Validation, MF_STRING, 2005, LocalizationManager::get()->getTranslatedTextW("Menu_Validation_DFF").c_str());
	AppendMenu(hMenu_IMG_Validation, MF_STRING, 2006, LocalizationManager::get()->getTranslatedTextW("Menu_Validation_TXD").c_str());
	AppendMenu(hMenu_IMG, MF_STRING, 2004, LocalizationManager::get()->getTranslatedTextW("Menu_Compare").c_str());
	AppendMenu(hMenu_IMG, MF_SEPARATOR, 1742, _T(""));
	AppendMenu(hMenu_IMG, MF_STRING, 1149, LocalizationManager::get()->getTranslatedTextW("Menu_Stats").c_str());
	AppendMenu(hMenu_IMG, MF_SEPARATOR, 2052, _T(""));
	AppendMenu(hMenu_IMG, MF_STRING, 2053, LocalizationManager::get()->getTranslatedTextW("Menu_IMGVersionSettings").c_str());

	//AppendMenu(hMenu_Model, MF_STRING, 2105, LocalizationManager::get()->getTranslatedTextW("Menu_ExtractDVCAndNVColoursIntoDFFs").c_str());
	//AppendMenu(hMenu_Model, MF_STRING, 2106, LocalizationManager::get()->getTranslatedTextW("Menu_Extract2dEffectsIntoDFFs").c_str());
	AppendMenu(hMenu_Model, MF_SEPARATOR, 2052, _T(""));
	AppendMenu(hMenu_Model, MF_STRING | MF_POPUP, (UINT_PTR)hMenu_Model_Convert, LocalizationManager::get()->getTranslatedTextW("Convert").c_str());
	AppendMenu(hMenu_Model_Convert, MF_STRING | MF_POPUP, (UINT_PTR)hMenu_Model_Convert_DFFRWVersion, LocalizationManager::get()->getTranslatedTextW("DFFRWVersion").c_str());
	AppendMenu(hMenu_Model, MF_STRING, 2081, LocalizationManager::get()->getTranslatedTextW("Menu_Model_RemoveOrphanTextures").c_str());

	i = 0;
	for (auto pRWVersion : RWManager::get()->getVersionManager()->getEntries())
	{
		if (pRWVersion->getFileType() != TYPE_MODEL)
		{
			continue;
		}

		getIMGF()->m_umapMenuItemMapping_ConvertDFFtoRWVersion[1590 + i] = pRWVersion;
		string strMenuText = "Convert DFF to " + String::escapeMenuText((pRWVersion->getVersionText() + " (" + LocalizationManager::get()->getTranslatedText(pRWVersion->getLocalizationKey()) + ")").substr(0, 2)) + "&" + String::escapeMenuText((pRWVersion->getVersionText() + " (" + LocalizationManager::get()->getTranslatedText(pRWVersion->getLocalizationKey()) + ")").substr(2));
		AppendMenu(hMenu_Model_Convert_DFFRWVersion, MF_STRING, 1590 + i, String::convertStdStringToStdWString(strMenuText).c_str());
		i++;
	}

	//AppendMenu(hMenu_Model_Convert, MF_STRING | MF_POPUP, (UINT_PTR)hMenu_Model_Convert_FileFormat, LocalizationManager::get()->getTranslatedTextW("Menu_Convert_FileFormat").c_str());
	//AppendMenu(hMenu_Model_Convert_FileFormat, MF_STRING, 1840, _T("Convert DFF to WDR"));

	AppendMenu(hMenu_Texture, MF_STRING, 1154, LocalizationManager::get()->getTranslatedTextW("Dump").c_str());
	AppendMenu(hMenu_Texture, MF_STRING, 2051, LocalizationManager::get()->getTranslatedTextW("BuildTXD").c_str());
	AppendMenu(hMenu_Texture, MF_STRING, 2055, LocalizationManager::get()->getTranslatedTextW("Menu_TXDOrganizer").c_str());
	AppendMenu(hMenu_Texture, MF_SEPARATOR, 2080, _T(""));

	AppendMenu(hMenu_Texture, MF_STRING | MF_POPUP, (UINT_PTR)hMenu_Texture_Convert, LocalizationManager::get()->getTranslatedTextW("Convert").c_str());

	AppendMenu(hMenu_Texture_Convert, MF_STRING | MF_POPUP, (UINT_PTR)hMenu_Texture_Convert_TXDGame, LocalizationManager::get()->getTranslatedTextW("Menu_Convert_TXD_Game").c_str());
	AppendMenu(hMenu_Texture_Convert_TXDGame, MF_STRING, 1650, LocalizationManager::get()->getTranslatedFormattedTextW("Menu_Convert_TXD_To", LocalizationManager::get()->getTranslatedFormattedText("PlatformedGame_PC_GTA_III").c_str()).c_str());
	AppendMenu(hMenu_Texture_Convert_TXDGame, MF_STRING, 1651, LocalizationManager::get()->getTranslatedFormattedTextW("Menu_Convert_TXD_To", LocalizationManager::get()->getTranslatedFormattedText("PlatformedGame_PC_GTA_VC").c_str()).c_str());
	AppendMenu(hMenu_Texture_Convert_TXDGame, MF_STRING, 1652, LocalizationManager::get()->getTranslatedFormattedTextW("Menu_Convert_TXD_To", LocalizationManager::get()->getTranslatedFormattedText("PlatformedGame_PC_GTA_SA").c_str()).c_str());
	AppendMenu(hMenu_Texture_Convert_TXDGame, MF_STRING, 1653, LocalizationManager::get()->getTranslatedFormattedTextW("Menu_Convert_TXD_To", LocalizationManager::get()->getTranslatedFormattedText("PlatformedGame_Android_GTA").c_str()).c_str());
	AppendMenu(hMenu_Texture_Convert_TXDGame, MF_STRING, 1654, LocalizationManager::get()->getTranslatedFormattedTextW("Menu_Convert_TXD_To", LocalizationManager::get()->getTranslatedFormattedText("PlatformedGame_XBOX_GTA").c_str()).c_str());

	AppendMenu(hMenu_Texture_Convert, MF_STRING | MF_POPUP, (UINT_PTR)hMenu_Texture_Convert_TXDRWVersion, LocalizationManager::get()->getTranslatedTextW("TXDRWVersion").c_str());
	i = 0;
	for (auto pRWVersion : RWManager::get()->getVersionManager()->getEntries())
	{
		if (pRWVersion->getFileType() != TYPE_MODEL)
		{
			continue;
		}

		getIMGF()->m_umapMenuItemMapping_ConvertTXDtoRWVersion[1660 + i] = pRWVersion;
		string strString1 = String::escapeMenuText((pRWVersion->getVersionText() + " (" + LocalizationManager::get()->getTranslatedText(pRWVersion->getLocalizationKey()) + ")").substr(0, 2)) + "&" + String::escapeMenuText((pRWVersion->getVersionText() + " (" + LocalizationManager::get()->getTranslatedText(pRWVersion->getLocalizationKey()) + ")").substr(2));
		string strMenuText = LocalizationManager::get()->getTranslatedFormattedText("Menu_Convert_TXD_To", strString1.c_str());
		AppendMenu(hMenu_Texture_Convert_TXDRWVersion, MF_STRING, 1660 + i, String::convertStdStringToStdWString(strMenuText).c_str());
		i++;
	}

	AppendMenu(hMenu_Texture_Convert, MF_STRING | MF_POPUP, (UINT_PTR)hMenu_Texture_Convert_TXDTextureFormat, LocalizationManager::get()->getTranslatedTextW("Menu_Convert_TXD_RasterFormat").c_str());
	i = 0;
	for (auto pRasterDataFormat : ImageManager::get()->getRasterDataFormatManager()->getEntries())
	{
		getIMGF()->m_umapMenuItemMapping_ConvertTXDtoTextureFormat[2100 + i] = pRasterDataFormat;
		AppendMenu(hMenu_Texture_Convert_TXDTextureFormat, MF_STRING, 2100 + i, LocalizationManager::get()->getTranslatedFormattedTextW("Menu_Convert_TXD_To", pRasterDataFormat->getTextForMenu().c_str()).c_str());
		i++;
	}

	//AppendMenu(hMenu_Texture_Convert, MF_STRING | MF_POPUP, (UINT_PTR)hMenu_Texture_Convert_WTDFileFormat, LocalizationManager::get()->getTranslatedTextW("Menu_Convert_WTDFileFormat").c_str());
	//AppendMenu(hMenu_Texture_Convert_WTDFileFormat, MF_STRING, 2500, LocalizationManager::get()->getTranslatedTextW("Menu_Convert_WTD_TXD").c_str());

	AppendMenu(hMenu_Texture, MF_STRING, 1150, LocalizationManager::get()->getTranslatedTextW("Menu_TextureList").c_str());
	AppendMenu(hMenu_Texture, MF_STRING, 1620, LocalizationManager::get()->getTranslatedTextW("Menu_MissingTexture").c_str());

	AppendMenu(hMenu_Collision, MF_STRING, 1681, LocalizationManager::get()->getTranslatedTextW("Menu_AlignMeshes_COL_DFF").c_str());
	AppendMenu(hMenu_Collision, MF_SEPARATOR, 1702, _T(""));

	AppendMenu(hMenu_Collision, MF_STRING | MF_POPUP, (UINT_PTR)hMenu_Collision_Convert, LocalizationManager::get()->getTranslatedTextW("Convert").c_str());

	i = 0;
	for (auto pCOLVersion : COLManager::get()->getVersionManager()->getEntries())
	{
		getIMGF()->m_umapMenuItemMapping_ConvertCOLtoCOLVersion[2400 + i] = pCOLVersion;
		AppendMenu(hMenu_Collision_Convert, MF_STRING, 2400 + i, LocalizationManager::get()->getTranslatedFormattedTextW("Menu_Convert_COL_COL", pCOLVersion->getText().c_str()).c_str());
		i++;
	}

	AppendMenu(hMenu_Collision, MF_STRING, 1680, LocalizationManager::get()->getTranslatedTextW("Menu_CenterCOLMeshes").c_str());

	AppendMenu(hMenu_ItemDefinition, MF_STRING | MF_POPUP, (UINT_PTR)hMenu_ItemDefinition_FindOrphanEntries, LocalizationManager::get()->getTranslatedTextW("Menu_FindOrphanEntries").c_str());
	AppendMenu(hMenu_ItemDefinition_FindOrphanEntries, MF_STRING, 2091, LocalizationManager::get()->getTranslatedTextW("Menu_OrphanEntries_IDE_COL").c_str());
	AppendMenu(hMenu_ItemDefinition_FindOrphanEntries, MF_STRING, 2092, LocalizationManager::get()->getTranslatedTextW("Menu_OrphanEntries_IDE_DFF").c_str());
	AppendMenu(hMenu_ItemDefinition_FindOrphanEntries, MF_STRING, 2093, LocalizationManager::get()->getTranslatedTextW("Menu_OrphanEntries_IDE_IMG").c_str());
	AppendMenu(hMenu_ItemDefinition_FindOrphanEntries, MF_STRING, 2094, LocalizationManager::get()->getTranslatedTextW("Menu_OrphanEntries_IDE_IPL").c_str());
	AppendMenu(hMenu_ItemDefinition_FindOrphanEntries, MF_STRING, 2095, LocalizationManager::get()->getTranslatedTextW("Menu_OrphanEntries_IDE_TXD").c_str());
	AppendMenu(hMenu_ItemDefinition, MF_STRING | MF_POPUP, (UINT_PTR)hMenu_ItemDefinition_FindMissing, LocalizationManager::get()->getTranslatedTextW("Menu_FindMissingEntries").c_str());
	AppendMenu(hMenu_ItemDefinition_FindMissing, MF_STRING, 2059, LocalizationManager::get()->getTranslatedTextW("Menu_MissingEntries_IDE_IMG_TXD").c_str());
	AppendMenu(hMenu_ItemDefinition_FindMissing, MF_STRING, 2060, LocalizationManager::get()->getTranslatedTextW("Menu_MissingEntries_IDE_COL_COL").c_str());
	AppendMenu(hMenu_ItemDefinition_FindMissing, MF_STRING, 2061, LocalizationManager::get()->getTranslatedTextW("Menu_MissingEntries_IDE_IMG_DFF").c_str());
	AppendMenu(hMenu_ItemDefinition, MF_STRING, 2062, LocalizationManager::get()->getTranslatedTextW("Menu_SortDATIDEAndIPL_ByObjectId").c_str());

	AppendMenu(hMenu_ItemPlacement, MF_STRING | MF_POPUP, (UINT_PTR)hMenu_ItemPlacement_FindMissing, LocalizationManager::get()->getTranslatedTextW("Menu_FindMissingEntries").c_str());
	AppendMenu(hMenu_ItemPlacement_FindMissing, MF_STRING, 2097, LocalizationManager::get()->getTranslatedTextW("Menu_MissingEntries_IPL_IDE_DFF").c_str());

	AppendMenu(hMenu_ItemPlacement, MF_STRING, 2058, LocalizationManager::get()->getTranslatedTextW("Menu_MapMoverAndIDShifter").c_str());

	AppendMenu(hMenu_Entry, MF_STRING | MF_POPUP, (UINT_PTR)hMenu_Entry_Import, LocalizationManager::get()->getTranslatedTextW("Menu_Import").c_str());
	AppendMenu(hMenu_Entry_Import, MF_STRING, 1160, LocalizationManager::get()->getTranslatedTextW("Menu_Import_Files").c_str());
	AppendMenu(hMenu_Entry_Import, MF_STRING, 1161, LocalizationManager::get()->getTranslatedTextW("Menu_Import_IDE").c_str());
	AppendMenu(hMenu_Entry_Import, MF_STRING, 1169, LocalizationManager::get()->getTranslatedTextW("Menu_Import_TextLines").c_str());
	AppendMenu(hMenu_Entry_Import, MF_STRING, 1170, LocalizationManager::get()->getTranslatedTextW("Menu_Import_Folder").c_str());
	AppendMenu(hMenu_Entry, MF_STRING | MF_POPUP, (UINT_PTR)hMenu_Entry_Export, LocalizationManager::get()->getTranslatedTextW("Menu_Export").c_str());
	AppendMenu(hMenu_Entry_Export, MF_STRING, 1162, LocalizationManager::get()->getTranslatedTextW("Menu_Export_Selected").c_str());
	AppendMenu(hMenu_Entry_Export, MF_STRING, 1163, LocalizationManager::get()->getTranslatedTextW("Menu_Export_IDE").c_str());
	AppendMenu(hMenu_Entry_Export, MF_STRING, 1350, LocalizationManager::get()->getTranslatedTextW("Menu_Export_IPL").c_str());
	AppendMenu(hMenu_Entry_Export, MF_STRING, 1164, LocalizationManager::get()->getTranslatedTextW("Menu_Export_TextLines").c_str());
	AppendMenu(hMenu_Entry_Export, MF_STRING, 1192, LocalizationManager::get()->getTranslatedTextW("Menu_Export_DAT").c_str());
	AppendMenu(hMenu_Entry_Export, MF_SEPARATOR, 1710, _T(""));
	AppendMenu(hMenu_Entry_Export, MF_STRING, 1550, LocalizationManager::get()->getTranslatedTextW("QuickExport").c_str());
	AppendMenu(hMenu_Entry_Export, MF_SEPARATOR, 1711, _T(""));
	AppendMenu(hMenu_Entry_Export, MF_STRING, 1551, LocalizationManager::get()->getTranslatedTextW("Menu_Export_AllTabs").c_str());
	AppendMenu(hMenu_Entry_Export, MF_STRING, 1554, LocalizationManager::get()->getTranslatedTextW("Menu_Export_AllTabsIntoFolders").c_str());
	AppendMenu(hMenu_Entry_Export, MF_SEPARATOR, 1712, _T(""));
	AppendMenu(hMenu_Entry_Export, MF_STRING, 1552, LocalizationManager::get()->getTranslatedTextW("Menu_Export_AllTabsIDE").c_str());
	AppendMenu(hMenu_Entry_Export, MF_STRING, 1553, LocalizationManager::get()->getTranslatedTextW("Menu_Export_AllTabsTextLines").c_str());
	AppendMenu(hMenu_Entry, MF_STRING | MF_POPUP, (UINT_PTR)hMenu_Entry_Remove, LocalizationManager::get()->getTranslatedTextW("Menu_Remove").c_str());
	AppendMenu(hMenu_Entry_Remove, MF_STRING, 1165, LocalizationManager::get()->getTranslatedTextW("Menu_Remove_Selected").c_str());
	AppendMenu(hMenu_Entry_Remove, MF_STRING, 1177, LocalizationManager::get()->getTranslatedTextW("Menu_Remove_IDE").c_str());
	AppendMenu(hMenu_Entry_Remove, MF_STRING, 1178, LocalizationManager::get()->getTranslatedTextW("Menu_Remove_TextLines").c_str());
	AppendMenu(hMenu_Entry, MF_STRING | MF_POPUP, (UINT_PTR)hMenu_Entry_Replace, LocalizationManager::get()->getTranslatedTextW("Menu_Replace").c_str());
	AppendMenu(hMenu_Entry_Replace, MF_STRING, 1176, LocalizationManager::get()->getTranslatedTextW("Menu_Replace_Selected").c_str());
	AppendMenu(hMenu_Entry_Replace, MF_STRING, 1621, LocalizationManager::get()->getTranslatedTextW("Menu_Replace_Folder").c_str());
	AppendMenu(hMenu_Entry, MF_SEPARATOR, 1700, _T(""));

	AppendMenu(hMenu_Entry, MF_STRING | MF_POPUP, (UINT_PTR)hMenu_Entry_Shift, LocalizationManager::get()->getTranslatedTextW("Menu_Shift").c_str());
	AppendMenu(hMenu_Entry_Shift, MF_STRING, 1540, LocalizationManager::get()->getTranslatedTextW("Menu_Shift_Up").c_str());
	AppendMenu(hMenu_Entry_Shift, MF_STRING, 1541, LocalizationManager::get()->getTranslatedTextW("Menu_Shift_Down").c_str());
	AppendMenu(hMenu_Entry, MF_STRING, 1166, LocalizationManager::get()->getTranslatedTextW("Menu_Rename").c_str());
	AppendMenu(hMenu_Entry, MF_STRING | MF_POPUP, (UINT_PTR)hMenu_Entry_Case, LocalizationManager::get()->getTranslatedTextW("Menu_NameCase").c_str());
	AppendMenu(hMenu_Entry_Case, MF_STRING | MF_POPUP, (UINT_PTR)hMenu_Entry_LowerCase, LocalizationManager::get()->getTranslatedTextW("Menu_NameCase_Lowercase").c_str());
	AppendMenu(hMenu_Entry_LowerCase, MF_STRING, 1500, LocalizationManager::get()->getTranslatedTextW("Menu_NameCase_NameWithExtension").c_str());
	AppendMenu(hMenu_Entry_LowerCase, MF_STRING, 1501, LocalizationManager::get()->getTranslatedTextW("Menu_NameCase_NameWithoutExtension").c_str());
	AppendMenu(hMenu_Entry_LowerCase, MF_STRING, 1502, LocalizationManager::get()->getTranslatedTextW("Menu_NameCase_Extension").c_str());
	AppendMenu(hMenu_Entry_Case, MF_STRING | MF_POPUP, (UINT_PTR)hMenu_Entry_UpperCase, LocalizationManager::get()->getTranslatedTextW("Menu_NameCase_Uppercase").c_str());
	AppendMenu(hMenu_Entry_UpperCase, MF_STRING, 1510, LocalizationManager::get()->getTranslatedTextW("Menu_NameCase_NameWithExtension").c_str());
	AppendMenu(hMenu_Entry_UpperCase, MF_STRING, 1511, LocalizationManager::get()->getTranslatedTextW("Menu_NameCase_NameWithoutExtension").c_str());
	AppendMenu(hMenu_Entry_UpperCase, MF_STRING, 1512, LocalizationManager::get()->getTranslatedTextW("Menu_NameCase_Extension").c_str());
	AppendMenu(hMenu_Entry_Case, MF_STRING | MF_POPUP, (UINT_PTR)hMenu_Entry_TitleCase, LocalizationManager::get()->getTranslatedTextW("Titlecase").c_str());
	AppendMenu(hMenu_Entry_TitleCase, MF_STRING, 1520, LocalizationManager::get()->getTranslatedTextW("Menu_NameCase_NameWithExtension").c_str());
	AppendMenu(hMenu_Entry_TitleCase, MF_STRING, 1521, LocalizationManager::get()->getTranslatedTextW("Menu_NameCase_NameWithoutExtension").c_str());
	AppendMenu(hMenu_Entry_TitleCase, MF_STRING, 1522, LocalizationManager::get()->getTranslatedTextW("Menu_NameCase_Extension").c_str());
	AppendMenu(hMenu_Entry, MF_SEPARATOR, 1701, _T(""));
	AppendMenu(hMenu_Entry, MF_STRING | MF_POPUP, (UINT_PTR)hMenu_Entry_Copy, LocalizationManager::get()->getTranslatedTextW("Menu_Copy").c_str());
	AppendMenu(hMenu_Entry_Copy, MF_STRING, 1530, LocalizationManager::get()->getTranslatedTextW("Menu_Copy_ID").c_str());
	AppendMenu(hMenu_Entry_Copy, MF_STRING, 1531, LocalizationManager::get()->getTranslatedTextW("Menu_Copy_Name").c_str());
	AppendMenu(hMenu_Entry_Copy, MF_STRING, 1532, LocalizationManager::get()->getTranslatedTextW("Offset").c_str());
	AppendMenu(hMenu_Entry_Copy, MF_STRING, 1533, LocalizationManager::get()->getTranslatedTextW("Menu_Copy_ResourceType").c_str());
	AppendMenu(hMenu_Entry_Copy, MF_STRING, 1534, LocalizationManager::get()->getTranslatedTextW("RWVersion").c_str());
	AppendMenu(hMenu_Entry_Copy, MF_STRING, 1535, LocalizationManager::get()->getTranslatedTextW("Size").c_str());
	AppendMenu(hMenu_Entry_Copy, MF_STRING, 1536, LocalizationManager::get()->getTranslatedTextW("Menu_Copy_Type").c_str());
	//AppendMenu(hMenu_Entry, MF_SEPARATOR, 1703, _T(""));

	AppendMenu(hMenu_Settings, MF_STRING, 1580, LocalizationManager::get()->getTranslatedTextW("Settings").c_str());

	AppendMenu(hMenu_Help, MF_STRING, 1570, LocalizationManager::get()->getTranslatedTextW("Version").c_str());
	AppendMenu(hMenu_Help, MF_STRING, 1572, LocalizationManager::get()->getTranslatedTextW("Menu_Update").c_str());
	AppendMenu(hMenu_Help, MF_SEPARATOR, 1574, _T(""));
	AppendMenu(hMenu_Help, MF_STRING, 1571, LocalizationManager::get()->getTranslatedTextW("Menu_Website").c_str());
	AppendMenu(hMenu_Help, MF_STRING, 1575, LocalizationManager::get()->getTranslatedTextW("Menu_ReportIssueOrIdea").c_str());
	AppendMenu(hMenu_Help, MF_SEPARATOR, 1574, _T(""));
	AppendMenu(hMenu_Help, MF_STRING, 1573, LocalizationManager::get()->getTranslatedTextW("Credits").c_str());

	::SetMenu(getIMGF()->getDialog()->GetSafeHwnd(), hMenubar);
	*/
}

void					IMGEditor::loadRightClickMenu(int xPos, int yPos)
{
	/*
	todo
	CListCtrl *pListCtrl = (CListCtrl*)getIMGF()->getDialog()->GetDlgItem(37);

	RECT rect;
	pListCtrl->GetWindowRect(&rect);
	getIMGF()->getDialog()->ScreenToClient(&rect);

	POINT point;
	point.x = xPos;
	point.y = yPos;
	ScreenToClient(getIMGF()->getDialog()->GetSafeHwnd(), &point);
	if (point.x >= rect.left &&
		point.x <= rect.right &&
		point.y >= rect.top &&
		point.y <= rect.bottom)
	{
	}
	else
	{
		// cursor right click was not in the main list view
		return;
	}

	// create menu
	HMENU hMenu = CreatePopupMenu();

	// create popup menus
	HMENU hMenu_Shift = CreatePopupMenu();
	HMENU hMenu_NameCase = CreatePopupMenu();
	HMENU hMenu_NameCase_LowerCase = CreatePopupMenu();
	HMENU hMenu_NameCase_UpperCase = CreatePopupMenu();
	HMENU hMenu_NameCase_TitleCase = CreatePopupMenu();
	HMENU hMenu_Copy = CreatePopupMenu();

	HMENU hMenu_ConvertDFF = CreatePopupMenu();
	HMENU hMenu_ConvertDFF_DFFRWVersion = CreatePopupMenu();

	HMENU hMenu_ConvertTXD = CreatePopupMenu();
	HMENU hMenu_ConvertTXD_TXDGame = CreatePopupMenu();
	HMENU hMenu_ConvertTXD_TXDRWVersion = CreatePopupMenu();
	HMENU hMenu_ConvertTXD_TXDTextureFormat = CreatePopupMenu();
	HMENU hMenu_ConvertTXD_WTDFileFormat = CreatePopupMenu();

	HMENU hMenu_ConvertCOL = CreatePopupMenu();

	// IMG Entry
	uint32 i;

	AppendMenu(hMenu, MF_STRING, 1550, LocalizationManager::get()->getTranslatedTextW("QuickExport").c_str());
	AppendMenu(hMenu, MF_STRING, 1162, LocalizationManager::get()->getTranslatedTextW("Menu_Export_Selected").c_str());
	AppendMenu(hMenu, MF_STRING, 1165, LocalizationManager::get()->getTranslatedTextW("Menu_Remove_Selected").c_str());
	AppendMenu(hMenu, MF_STRING, 1176, LocalizationManager::get()->getTranslatedTextW("Menu_Replace_Selected").c_str());
	AppendMenu(hMenu, MF_STRING | MF_POPUP, (UINT_PTR)hMenu_Shift, LocalizationManager::get()->getTranslatedTextW("Menu_Shift").c_str());
	AppendMenu(hMenu_Shift, MF_STRING, 1540, LocalizationManager::get()->getTranslatedTextW("Menu_Shift_Up").c_str());
	AppendMenu(hMenu_Shift, MF_STRING, 1541, LocalizationManager::get()->getTranslatedTextW("Menu_Shift_Down").c_str());
	AppendMenu(hMenu, MF_STRING, 1166, LocalizationManager::get()->getTranslatedTextW("Menu_Rename").c_str());
	AppendMenu(hMenu, MF_STRING | MF_POPUP, (UINT_PTR)hMenu_NameCase, LocalizationManager::get()->getTranslatedTextW("Menu_NameCase").c_str());
	AppendMenu(hMenu_NameCase, MF_STRING | MF_POPUP, (UINT_PTR)hMenu_NameCase_LowerCase, LocalizationManager::get()->getTranslatedTextW("Menu_NameCase_Lowercase").c_str());
	AppendMenu(hMenu_NameCase_LowerCase, MF_STRING, 1500, LocalizationManager::get()->getTranslatedTextW("Menu_NameCase_NameWithExtension").c_str());
	AppendMenu(hMenu_NameCase_LowerCase, MF_STRING, 1501, LocalizationManager::get()->getTranslatedTextW("Menu_NameCase_NameWithoutExtension").c_str());
	AppendMenu(hMenu_NameCase_LowerCase, MF_STRING, 1502, LocalizationManager::get()->getTranslatedTextW("Menu_NameCase_Extension").c_str());
	AppendMenu(hMenu_NameCase, MF_STRING | MF_POPUP, (UINT_PTR)hMenu_NameCase_UpperCase, LocalizationManager::get()->getTranslatedTextW("Menu_NameCase_Uppercase").c_str());
	AppendMenu(hMenu_NameCase_UpperCase, MF_STRING, 1510, LocalizationManager::get()->getTranslatedTextW("Menu_NameCase_NameWithExtension").c_str());
	AppendMenu(hMenu_NameCase_UpperCase, MF_STRING, 1511, LocalizationManager::get()->getTranslatedTextW("Menu_NameCase_NameWithoutExtension").c_str());
	AppendMenu(hMenu_NameCase_UpperCase, MF_STRING, 1512, LocalizationManager::get()->getTranslatedTextW("Menu_NameCase_Extension").c_str());
	AppendMenu(hMenu_NameCase, MF_STRING | MF_POPUP, (UINT_PTR)hMenu_NameCase_TitleCase, LocalizationManager::get()->getTranslatedTextW("Titlecase").c_str());
	AppendMenu(hMenu_NameCase_TitleCase, MF_STRING, 1520, LocalizationManager::get()->getTranslatedTextW("Menu_NameCase_NameWithExtension").c_str());
	AppendMenu(hMenu_NameCase_TitleCase, MF_STRING, 1521, LocalizationManager::get()->getTranslatedTextW("Menu_NameCase_NameWithoutExtension").c_str());
	AppendMenu(hMenu_NameCase_TitleCase, MF_STRING, 1522, LocalizationManager::get()->getTranslatedTextW("Menu_NameCase_Extension").c_str());
	AppendMenu(hMenu, MF_STRING | MF_POPUP, (UINT_PTR)hMenu_Copy, LocalizationManager::get()->getTranslatedTextW("Menu_Copy").c_str());
	AppendMenu(hMenu_Copy, MF_STRING, 1530, LocalizationManager::get()->getTranslatedTextW("Menu_Copy_ID").c_str());
	AppendMenu(hMenu_Copy, MF_STRING, 1531, LocalizationManager::get()->getTranslatedTextW("Menu_Copy_Name").c_str());
	AppendMenu(hMenu_Copy, MF_STRING, 1532, LocalizationManager::get()->getTranslatedTextW("Offset").c_str());
	AppendMenu(hMenu_Copy, MF_STRING, 1533, LocalizationManager::get()->getTranslatedTextW("Menu_Copy_ResourceType").c_str());
	AppendMenu(hMenu_Copy, MF_STRING, 1534, LocalizationManager::get()->getTranslatedTextW("RWVersion").c_str());
	AppendMenu(hMenu_Copy, MF_STRING, 1535, LocalizationManager::get()->getTranslatedTextW("Size").c_str());
	AppendMenu(hMenu_Copy, MF_STRING, 1536, LocalizationManager::get()->getTranslatedTextW("Menu_Copy_Type").c_str());

	// DFF Entry
	AppendMenu(hMenu, MF_SEPARATOR, 1701, _T(""));

	AppendMenu(hMenu, MF_STRING | MF_POPUP, (UINT_PTR)hMenu_ConvertDFF, LocalizationManager::get()->getTranslatedTextW("ConvertModel").c_str());
	AppendMenu(hMenu_ConvertDFF, MF_STRING | MF_POPUP, (UINT_PTR)hMenu_ConvertDFF_DFFRWVersion, LocalizationManager::get()->getTranslatedTextW("DFFRWVersion").c_str());
	AppendMenu(hMenu, MF_STRING, 2081, LocalizationManager::get()->getTranslatedTextW("Menu_Model_RemoveOrphanTextures").c_str());

	i = 0;
	for (auto pRWVersion : RWManager::get()->getVersionManager()->getEntries())
	{
		if (pRWVersion->getFileType() != TYPE_MODEL)
		{
			continue;
		}

		string strMenuText = "Convert DFF to " + String::escapeMenuText((pRWVersion->getVersionText() + " (" + LocalizationManager::get()->getTranslatedText(pRWVersion->getLocalizationKey()) + ")").substr(0, 2)) + "&" + String::escapeMenuText((pRWVersion->getVersionText() + " (" + LocalizationManager::get()->getTranslatedText(pRWVersion->getLocalizationKey()) + ")").substr(2));
		AppendMenu(hMenu_ConvertDFF_DFFRWVersion, MF_STRING, 1590 + i, String::convertStdStringToStdWString(strMenuText).c_str());
		i++;
	}

	// TXD Entry
	AppendMenu(hMenu, MF_SEPARATOR, 1701, _T(""));

	AppendMenu(hMenu, MF_STRING | MF_POPUP, (UINT_PTR)hMenu_ConvertTXD, LocalizationManager::get()->getTranslatedTextW("ConvertTexture").c_str());

	AppendMenu(hMenu_ConvertTXD, MF_STRING | MF_POPUP, (UINT_PTR)hMenu_ConvertTXD_TXDGame, LocalizationManager::get()->getTranslatedTextW("Menu_Convert_TXD_Game").c_str());
	AppendMenu(hMenu_ConvertTXD_TXDGame, MF_STRING, 1650, LocalizationManager::get()->getTranslatedFormattedTextW("Menu_Convert_TXD_To", LocalizationManager::get()->getTranslatedFormattedText("PlatformedGame_PC_GTA_III").c_str()).c_str());
	AppendMenu(hMenu_ConvertTXD_TXDGame, MF_STRING, 1651, LocalizationManager::get()->getTranslatedFormattedTextW("Menu_Convert_TXD_To", LocalizationManager::get()->getTranslatedFormattedText("PlatformedGame_PC_GTA_VC").c_str()).c_str());
	AppendMenu(hMenu_ConvertTXD_TXDGame, MF_STRING, 1652, LocalizationManager::get()->getTranslatedFormattedTextW("Menu_Convert_TXD_To", LocalizationManager::get()->getTranslatedFormattedText("PlatformedGame_PC_GTA_SA").c_str()).c_str());
	AppendMenu(hMenu_ConvertTXD_TXDGame, MF_STRING, 1653, LocalizationManager::get()->getTranslatedFormattedTextW("Menu_Convert_TXD_To", LocalizationManager::get()->getTranslatedFormattedText("PlatformedGame_Android_GTA").c_str()).c_str());
	AppendMenu(hMenu_ConvertTXD_TXDGame, MF_STRING, 1654, LocalizationManager::get()->getTranslatedFormattedTextW("Menu_Convert_TXD_To", LocalizationManager::get()->getTranslatedFormattedText("PlatformedGame_XBOX_GTA").c_str()).c_str());

	AppendMenu(hMenu_ConvertTXD, MF_STRING | MF_POPUP, (UINT_PTR)hMenu_ConvertTXD_TXDRWVersion, LocalizationManager::get()->getTranslatedTextW("TXDRWVersion").c_str());
	i = 0;
	for (auto pRWVersion : RWManager::get()->getVersionManager()->getEntries())
	{
		if (pRWVersion->getFileType() != TYPE_MODEL)
		{
			continue;
		}

		string strString1 = String::escapeMenuText((pRWVersion->getVersionText() + " (" + LocalizationManager::get()->getTranslatedText(pRWVersion->getLocalizationKey()) + ")").substr(0, 2)) + "&" + String::escapeMenuText((pRWVersion->getVersionText() + " (" + LocalizationManager::get()->getTranslatedText(pRWVersion->getLocalizationKey()) + ")").substr(2));
		string strMenuText = LocalizationManager::get()->getTranslatedFormattedText("Menu_Convert_TXD_To", strString1.c_str());
		AppendMenu(hMenu_ConvertTXD_TXDRWVersion, MF_STRING, 1660 + i, String::convertStdStringToStdWString(strMenuText).c_str());
		i++;
	}

	AppendMenu(hMenu_ConvertTXD, MF_STRING | MF_POPUP, (UINT_PTR)hMenu_ConvertTXD_TXDTextureFormat, LocalizationManager::get()->getTranslatedTextW("Menu_Convert_TXD_RasterFormat").c_str());
	i = 0;
	for (auto pRasterDataFormat : ImageManager::get()->getRasterDataFormatManager()->getEntries())
	{
		AppendMenu(hMenu_ConvertTXD_TXDTextureFormat, MF_STRING, 2100 + i, LocalizationManager::get()->getTranslatedFormattedTextW("Menu_Convert_TXD_To", pRasterDataFormat->getTextForMenu().c_str()).c_str());
		i++;
	}

	//AppendMenu(hMenu_ConvertTXD, MF_STRING | MF_POPUP, (UINT_PTR)hMenu_ConvertTXD_WTDFileFormat, LocalizationManager::get()->getTranslatedTextW("Menu_Convert_WTDFileFormat").c_str());
	//AppendMenu(hMenu_ConvertTXD_WTDFileFormat, MF_STRING, 2500, LocalizationManager::get()->getTranslatedTextW("Menu_Convert_WTD_TXD").c_str());

	AppendMenu(hMenu, MF_STRING, 1150, LocalizationManager::get()->getTranslatedTextW("Menu_TextureList").c_str());
	AppendMenu(hMenu, MF_STRING, 1620, LocalizationManager::get()->getTranslatedTextW("Menu_MissingTexture").c_str());

	// COL Entry
	AppendMenu(hMenu, MF_SEPARATOR, 1701, _T(""));

	AppendMenu(hMenu, MF_STRING | MF_POPUP, (UINT_PTR)hMenu_ConvertCOL, LocalizationManager::get()->getTranslatedTextW("ConvertCollision").c_str());

	i = 0;
	for (auto pCOLVersion : COLManager::get()->getVersionManager()->getEntries())
	{
		AppendMenu(hMenu_ConvertCOL, MF_STRING, 2400 + i, LocalizationManager::get()->getTranslatedFormattedTextW("Menu_Convert_COL_COL", pCOLVersion->getText().c_str()).c_str());
		i++;
	}

	AppendMenu(hMenu, MF_STRING, 1680, LocalizationManager::get()->getTranslatedTextW("Menu_CenterCOLMeshes").c_str());

	// show menu
	SetForegroundWindow(getIMGF()->getDialog()->GetSafeHwnd());
	TrackPopupMenu(hMenu, TPM_LEFTALIGN | TPM_TOPALIGN | TPM_RIGHTBUTTON, xPos, yPos, 0, getIMGF()->getDialog()->GetSafeHwnd(), NULL);
	PostMessage(getIMGF()->getDialog()->GetSafeHwnd(), WM_NULL, 0, 0);

	// clean up
	//DestroyMenu(hMenu);
	*/
}

// resolved file name
string					IMGEditor::getResolvedFilePath(string& strFilePath)
{
	return Path::replaceFileExtensionWithCase(strFilePath, "img");
}

// controls
void		IMGEditor::addControls(void)
{
	/*
	todo

	Vec2i
		point;
	Vec2u
		size;
	int32
		x, y, w, h, w2;
	uint32
		uiLogWidth;
	uint32
		uiButtonHeight = 37;
	Colour
		borderColour(50, 50, 50);
	string
		strStyleGroup;

	uiLogWidth = 335;

	// grid
	x = 139 + 139;
	y = 162 + 30;
	w = m_pWindow->getSize().x - x - uiLogWidth;
	h = m_pWindow->getSize().y - y;
	strStyleGroup = "imgEditor_grid";

	m_pEntryGrid = addGrid(x, y, w, h, strStyleGroup, IMG_GRID);

	w -= m_pEntryGrid->getScrollBarPool()->getScrollBarByOrientation(VERTICAL)->getBackgroundBarSize().x;
	h -= m_pEntryGrid->getScrollBarPool()->getScrollBarByOrientation(HORIZONTAL)->getBackgroundBarSize().y;
	m_pEntryGrid->setSize(Vec2u(w, h));

	// filter - entry type
	w = 140;
	w2 = w;
	x = m_pWindow->getSize().x - w - w2 - uiLogWidth - 10;
	y = uiButtonHeight + 82;
	h = 24;
	strStyleGroup = "filter filterDropDown";

	m_pEntryTypeFilter = addDropDown(x, y, w, h, "Entry Type", strStyleGroup + " firstItemHorizontally", -1, -100);
	m_pEntryTypeFilter->addItem("No file is open", false, false);

	// filter - entry version
	w = w2;
	x = m_pWindow->getSize().x - w - uiLogWidth - 10;

	m_pEntryVersionFilter = addDropDown(x, y, w, h, "Entry Version", strStyleGroup, -1, -100);
	m_pEntryVersionFilter->addItem("No file is open", false, false);
	*/
}

void		IMGEditor::initControls(void)
{
	// todo

	//addColumnsToMainListView(IMG_UNKNOWN);
}

// render
void		IMGEditor::render(void)
{
}