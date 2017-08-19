#include "CIMGEditor.h"
#include "Globals.h"
#include "CIMGF.h"
#include "Format/IMG/Regular/CIMGManager.h"
#include "Static/CString2.h"
#include "Static/CPath.h"
#include "Static/CFile.h"
#include "Localization/CLocalizationManager.h"
#include "Settings/CSettingsManager.h"
#include "Format/COL/CCOLManager.h"
#include "Format/IMG/Regular/CIMGEntry.h"
#include "Engine/RW/CRWVersion.h"
#include "Task/CTaskManager.h"
#include "Task/CTaskDispatchManager.h"
#include "GUI/Windows/CMainWindow.h"
#include "Styles/CGUIStyles.h"
#include "Type/Colour/CColour.h"
#include "CGUIManager.h"
#include "Controls/CGridControl.h"
#include "GUI/Editor/EEditorItems.h"
#include "GUI/Windows/CMainWindow.h"
#include "GUI/Layers/CMainLayer.h"
#include "Controls/CTabBarControl.h"
#include "Controls/CProgressControl.h"
#include "Controls/CTextBoxControl.h"
#include "Controls/CTextControl.h"
#include "Controls/CDropControl.h"
#include "Static/CInput.h"
#include "Control/CGUIScrollPool.h"
#include "GUI/Layers/CMainLayer.h"
#include "Event/EInputEvents.h"

// for menu start - todo
#include "Engine/RW/CRWManager.h"
#include "Engine/RW/CRWVersionManager.h"
#include "Tasks/RecentlyOpen/CRecentlyOpenManager.h"
#include "Tasks/Sort/CSortManager.h"
#include "Tasks/Sort/CSortType.h"
#include "Tasks/Sort/CSortPriority.h"
#include "Tasks/Sort/CSortTypes.h"
#include "Tasks/Sort/CSortPriorities.h"
#include "Tasks/Sort/CSortMenuItems.h"
#include "Image/CImageManager.h"
#include "Image/CRasterDataFormatManager.h"
#include "Format/COL/CCOLManager.h"
#include "Format/COL/CCOLVersionManager.h"
#include "Format/COL/CCOLVersion.h"
// for menu end

using namespace std;
using namespace bxcf;
using namespace bxgi;
using namespace imgf::editor::items;

CIMGEditor::CIMGEditor(void) :
	m_pMainWindow(nullptr),
	m_pEntryGrid(nullptr),
	m_pLog(nullptr),
	m_pEntryTypeFilter(nullptr),
	m_pEntryVersionFilter(nullptr),
	m_uiSelectedEntryCount(0),
	m_uiSearchHitCount(0), // todo - rename to SearchHitEntryCount
	m_uiSearchFileCount(0) // todo - rename to SearchHitFileCount
{
}

// editor initialization
auto fpOnTaskProgress = [](void *pData)
{
	getIMGF()->getTaskManager()->onTaskProgressTick();
};

void						CIMGEditor::init(void)
{
	CEditor::init();
	addControls();
	initControls();

	CEventManager::get()->bindEvent(EVENT_onParseIMGEntry, fpOnTaskProgress);
}

// format validation
bool						CIMGEditor::validateFile(CIMGFormat *img)
{
	if (img->getVersion() == IMG_FASTMAN92)
	{
		// check if IMG is fastman92 format and is encrypted
		if (img->isEncrypted())
		{
			CInput::showMessage(CLocalizationManager::get()->getTranslatedText("TextPopup_21"), CLocalizationManager::get()->getTranslatedText("TextPopupTitle_21"), MB_OK);
			return false;
		}

		// check if IMG is fastman92 format and has an unsupported game type
		if (img->getGameType() != 0)
		{
			CInput::showMessage(CLocalizationManager::get()->getTranslatedFormattedText("TextPopup_68", img->getGameType()), CLocalizationManager::get()->getTranslatedText("UnableToOpenIMG"), MB_OK);
			return false;
		}
	}

	// no errors occurred
	return true;
}

// add/remove file
CIMGEditorTab*				CIMGEditor::addFile(CIMGFormat *img)
{
	CIMGEditorTab *imgEditorTab = addTabObjectAndTabControl(img);

	string strFileName = CPath::getFileName(img->getFilePath());
	imgEditorTab->logf("Opened %s", strFileName);

	return imgEditorTab;
}

CIMGEditorTab*				CIMGEditor::addBlankFile(string strIMGPath, eIMGVersion eIMGVersionValue)
{
	CIMGFormat *img = new CIMGFormat;
	img->setFilePath(strIMGPath);
	img->setVersion(eIMGVersionValue);

	CIMGEditorTab *imgEditorTab = addTabObjectAndTabControl(img);

	string strFileName = CPath::getFileName(img->getFilePath());
	imgEditorTab->logf("Created %s", strFileName);

	return imgEditorTab;
}

CIMGEditorTab*				CIMGEditor::addTabObjectAndTabControl(CIMGFormat *img)
{
	CIMGEditorTab *imgEditorTab = m_pWindow->addLayer<CIMGEditorTab>(-1, true, -50);

	imgEditorTab->setIMGEditor(this);
	imgEditorTab->setIMGFile(img);
	imgEditorTab->setFile(img);
	
	if (m_pActiveFile)
	{
		m_pActiveFile->setEnabled(false);
	}
	else
	{
		setEnabled(false);
	}

	CEditor::addFile(imgEditorTab);

	imgEditorTab->init();

	return imgEditorTab;
}

void						CIMGEditor::removeFile(CIMGEditorTab *pIMGEditorFile)
{
	CEditor::removeFile(pIMGEditorFile);

	m_pWindow->removeLayer(pIMGEditorFile);

	delete pIMGEditorFile;

	if (getTabs().getEntryCount() == 0)
	{
		setEnabled(true);
	}
	else
	{
		m_pActiveFile->setEnabled(true);
	}
}

void						CIMGEditor::removeActiveFile(void)
{
	if (getTabs().getEntryCount() == 0)
	{
		return;
	}

	removeFile((CIMGEditorTab*)getActiveFile());
}

// active file
void						CIMGEditor::setFileInfoText(CEditorTab *pEditorFile)
{
	CMainLayer *pMainLayer = m_pMainWindow->getMainLayer();

	pMainLayer->m_pText_Game->setText(string("A"));
	pMainLayer->m_pText_GameValidity->setText(string("-"));
	pMainLayer->m_pText_GameLocation->setText(string("A"));
	pMainLayer->m_pText_FileGame->setText(string("A"));
	pMainLayer->m_pText_FileValidity->setText(string("-"));
	pMainLayer->m_pText_FileLocation->setText(pEditorFile->getFile()->getFilePath());
}

void						CIMGEditor::clearFileInfoText(void)
{
	CMainLayer *pMainLayer = m_pMainWindow->getMainLayer();

	pMainLayer->m_pText_Game->setText(string("No file is open"));
	pMainLayer->m_pText_GameValidity->setText(string("-"));
	pMainLayer->m_pText_GameLocation->setText(string("-"));
	pMainLayer->m_pText_FileGame->setText(string("-"));
	pMainLayer->m_pText_FileValidity->setText(string("-"));
	pMainLayer->m_pText_FileLocation->setText(string("-"));
}






void						CIMGEditor::setActiveTab(CIMGEditorTab *pEditorTab)
{
	CEditor::setActiveFile(pEditorTab);
	
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
			((CButton*)getIMGF()->getDialog()->GetDlgItem(usButtonId))->EnableWindow(0);
		}

		// IMG path
		((CEdit*)getIMGF()->getDialog()->GetDlgItem(38))->SetWindowTextW(_T(""));

		// IMG entry count
		((CStatic*)getIMGF()->getDialog()->GetDlgItem(20))->SetWindowTextW(CLocalizationManager::get()->getTranslatedFormattedTextW("Window_Main_Text_EntryCount", 0).c_str());

		// selected entry count
		((CStatic*)getIMGF()->getDialog()->GetDlgItem(51))->SetWindowTextW(CLocalizationManager::get()->getTranslatedFormattedTextW("Window_Main_Text_SelectedEntryCount", 0).c_str());

		// IMG version
		((CStatic*)getIMGF()->getDialog()->GetDlgItem(19))->SetWindowTextW(CLocalizationManager::get()->getTranslatedTextW("Window_Main_Text_IMGVersion").c_str());
		*/

		// 6th column name in main list view
		readdColumnsToMainListView(IMG_UNKNOWN);

		/*
		// search text
		((CEdit*)getIMGF()->getDialog()->GetDlgItem(24))->SetWindowTextW(_T(""));
		((CStatic*)getIMGF()->getDialog()->GetDlgItem(0))->SetWindowTextW(CLocalizationManager::get()->getTranslatedFormattedTextW("Window_Main_Text_SearchResult_ActiveTab", 0).c_str());
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
			((CButton*)getIMGF()->getDialog()->GetDlgItem(usButtonId))->EnableWindow(1);
		}

		// tab focus
		((CTabCtrl*)getIMGF()->getDialog()->GetDlgItem(1))->SetCurFocus(pEditorTab->getIndex());

		// IMG path
		((CEdit*)getIMGF()->getDialog()->GetDlgItem(38))->SetWindowTextW(CString2::convertStdStringToStdWString(pEditorTab->getIMGFile()->getFilePath()).c_str());

		// IMG entry count
		pEditorTab->updateEntryCountText();

		// selected entry count
		m_uiSelectedEntryCount = 0;
		((CStatic*)getIMGF()->getDialog()->GetDlgItem(51))->SetWindowTextW(CLocalizationManager::get()->getTranslatedFormattedTextW("Window_Main_Text_SelectedEntryCount", 0).c_str());

		// IMG version
		pEditorTab->updateIMGText();
		*/

		// 6th column name in main list view
		readdColumnsToMainListView(pEditorTab->getIMGFile()->getVersion());

		/*
		// search text
		if (((CButton*)getIMGF()->getDialog()->GetDlgItem(46))->GetCheck() == BST_UNCHECKED)
		{
			((CEdit*)getIMGF()->getDialog()->GetDlgItem(24))->SetWindowTextW(CString2::convertStdStringToStdWString(pEditorTab->getSearchText()).c_str());
			pEditorTab->searchText();
		}

		// filter
		pEditorTab->loadFilter_Type();
		pEditorTab->loadFilter_Version();

		// log
		CEdit *pEdit = ((CEdit*)getIMGF()->getDialog()->GetDlgItem(14));
		pEdit->SetWindowTextW(CString2::convertStdStringToStdWString(CString2::join(pEditorTab->getLogLinesGUI(), "\r\n")).c_str());
		pEdit->LineScroll(pEdit->GetLineCount());

		// IMG entries
		pEditorTab->readdAllEntriesToMainListView();
		*/
	}
}

void					CIMGEditor::readdColumnsToMainListView(eIMGVersion eIMGVersionValue)
{
	removeColumnsFromMainListView();
	addColumnsToMainListView(eIMGVersionValue);
}
void					CIMGEditor::addColumnsToMainListView(eIMGVersion eIMGVersionValue)
{
	m_pEntryGrid->addHeader("Index" /* todo CLocalizationManager::get()->getTranslatedText("Window_Main_ListView_ColumnTitle_ID")*/, 45);
	m_pEntryGrid->addHeader("Type" /* CLocalizationManager::get()->getTranslatedText("Window_Main_ListView_ColumnTitle_Type")*/, 40);
	m_pEntryGrid->addHeader("Name" /* CLocalizationManager::get()->getTranslatedText("Window_Main_ListView_ColumnTitle_Name")*/, 150);
	m_pEntryGrid->addHeader("Offset" /* CLocalizationManager::get()->getTranslatedText("Offset")*/, 85);
	m_pEntryGrid->addHeader("Size" /* CLocalizationManager::get()->getTranslatedText("Size")*/, 70);

	switch (eIMGVersionValue)
	{
	case IMG_UNKNOWN:
	case IMG_1:
	case IMG_2:
		m_pEntryGrid->addHeader("Version" /* CLocalizationManager::get()->getTranslatedText("Version")*/, 125);
		break;
	case IMG_3:
		m_pEntryGrid->addHeader("Resource Type" /* CLocalizationManager::get()->getTranslatedText("ResourceType")*/, 125);
		break;
	case IMG_FASTMAN92:
		m_pEntryGrid->addHeader("Version" /* CLocalizationManager::get()->getTranslatedText("Version")*/, 125);
		m_pEntryGrid->addHeader("Compression" /* CLocalizationManager::get()->getTranslatedText("Compression")*/, 125);
		m_pEntryGrid->addHeader("Encryption" /* CLocalizationManager::get()->getTranslatedText("Encryption")*/, 125);
		break;
	}
}
void					CIMGEditor::removeColumnsFromMainListView(void)
{
	/*
	todo
	CListCtrl *pListCtrl = (CListCtrl*)getIMGF()->getDialog()->GetDlgItem(37);
	while (pListCtrl->DeleteColumn(0) != 0)
	{
	}
	*/
}
int						CIMGEditor::getMainListControlItemByEntry(CIMGEntry *pIMGEntry)
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

void					CIMGEditor::onSelectIMGEntry(bool bEntryIsSelected)
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

void					CIMGEditor::updateSelectedEntryCountText(void)
{
	// todo ((CStatic*)getIMGF()->getDialog()->GetDlgItem(51))->SetWindowTextW(CLocalizationManager::get()->getTranslatedFormattedTextW("Window_Main_Text_SelectedEntryCount", m_uiSelectedEntryCount).c_str());
}

void					CIMGEditor::logAllTabs(string strText, bool bExtendedModeOnly)
{
	for (auto pEditorTab : getTabs().getEntries())
	{
		((CIMGEditorTab*)pEditorTab)->log(strText, bExtendedModeOnly);
	}
}

void					CIMGEditor::logWithNoTabsOpen(string strText, bool bExtendedModeOnly)
{
	string strLogEntryWithTimestampAndIMG = "[" + CString2::getTimestampText() + "] [" + CLocalizationManager::get()->getTranslatedText("NoTabsOpen") + "] " + strText;

	if (bExtendedModeOnly)
	{
		//m_vecLogLinesExtended.push_back(strLogEntryWithTimestampAndIMG);

		// automatic logging to file
		if (getIMGF()->getSettingsManager()->getSettingString("AutomaticLoggingPath") != "")
		{
			// extended file
			if (getIMGF()->getSettingsManager()->getSettingBool("AutomaticLoggingExtended"))
			{
				string strExtendedLogPath = CPath::addSlashToEnd(getIMGF()->getSettingsManager()->getSettingString("AutomaticLoggingPath"));
				strExtendedLogPath += CString2::getDateTextForFolder() + "/" + CLocalizationManager::get()->getTranslatedText("LogFilename_Extended");
				CFile::storeFile(strExtendedLogPath, strLogEntryWithTimestampAndIMG + "\n", true, false);
			}
		}
	}
	else
	{
		//m_vecLogLinesGUI.push_back(strText);
		//m_vecLogLinesBasic.push_back(strLogEntryWithTimestampAndIMG);
		//m_vecLogLinesExtended.push_back(strLogEntryWithTimestampAndIMG);

		// automatic logging to file
		if (getIMGF()->getSettingsManager()->getSettingString("AutomaticLoggingPath") != "")
		{
			// basic file
			if (getIMGF()->getSettingsManager()->getSettingBool("AutomaticLoggingBasic"))
			{
				string strExtendedLogPath = CPath::addSlashToEnd(getIMGF()->getSettingsManager()->getSettingString("AutomaticLoggingPath"));
				strExtendedLogPath += CString2::getDateTextForFolder() + "/" + CLocalizationManager::get()->getTranslatedText("LogFilename_Basic");
				CFile::storeFile(strExtendedLogPath, strLogEntryWithTimestampAndIMG + "\n", true, false);
			}

			// extended file
			if (getIMGF()->getSettingsManager()->getSettingBool("AutomaticLoggingExtended"))
			{
				string strExtendedLogPath = CPath::addSlashToEnd(getIMGF()->getSettingsManager()->getSettingString("AutomaticLoggingPath"));
				strExtendedLogPath += CString2::getDateTextForFolder() + "/" + CLocalizationManager::get()->getTranslatedText("LogFilename_Extended");
				CFile::storeFile(strExtendedLogPath, strLogEntryWithTimestampAndIMG + "\n", true, false);
			}
		}
	}
}

uint32					CIMGEditor::getEntryCountForAllTabs(void)
{
	uint32 uiTotalEntryCount = 0;
	for (auto pEditorTab : getTabs().getEntries())
	{
		uiTotalEntryCount += ((CIMGEditorTab*)pEditorTab)->getIMGFile()->getEntryCount();
	}
	return uiTotalEntryCount;
}

vector<CIMGFormat*>		CIMGEditor::getAllMainWindowTabsIMGFiles(void)
{
	vector<CIMGFormat*> veCIMGFormats;
	for (auto pEditorTab : getTabs().getEntries())
	{
		veCIMGFormats.push_back(((CIMGEditorTab*)pEditorTab)->getIMGFile());
	}
	return veCIMGFormats;
}

void					CIMGEditor::refreshActiveTab(void)
{
	setActiveTab(getActiveTab());
}

void					CIMGEditor::initMenu(void) // todo - move menu stuff to like CMenuManager
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

	AppendMenu(hMenubar, MF_POPUP, (UINT_PTR)hMenu_File, CLocalizationManager::get()->getTranslatedTextW("Menu_File").c_str());
	AppendMenu(hMenubar, MF_POPUP, (UINT_PTR)hMenu_Edit, CLocalizationManager::get()->getTranslatedTextW("Menu_Edit").c_str());
	AppendMenu(hMenubar, MF_POPUP, (UINT_PTR)hMenu_DAT, CLocalizationManager::get()->getTranslatedTextW("Menu_DAT").c_str());
	AppendMenu(hMenubar, MF_POPUP, (UINT_PTR)hMenu_IMG, CLocalizationManager::get()->getTranslatedTextW("Menu_IMG").c_str());
	AppendMenu(hMenubar, MF_POPUP, (UINT_PTR)hMenu_Model, CLocalizationManager::get()->getTranslatedTextW("Menu_Model").c_str());
	AppendMenu(hMenubar, MF_POPUP, (UINT_PTR)hMenu_Texture, CLocalizationManager::get()->getTranslatedTextW("Menu_Texture").c_str());
	AppendMenu(hMenubar, MF_POPUP, (UINT_PTR)hMenu_Collision, CLocalizationManager::get()->getTranslatedTextW("Menu_Collision").c_str());
	AppendMenu(hMenubar, MF_POPUP, (UINT_PTR)hMenu_ItemDefinition, CLocalizationManager::get()->getTranslatedTextW("Menu_ItemDefinition").c_str());
	AppendMenu(hMenubar, MF_POPUP, (UINT_PTR)hMenu_ItemPlacement, CLocalizationManager::get()->getTranslatedTextW("Menu_ItemPlacement").c_str());
	AppendMenu(hMenubar, MF_POPUP, (UINT_PTR)hMenu_Entry, CLocalizationManager::get()->getTranslatedTextW("Menu_Entry").c_str());
	AppendMenu(hMenubar, MF_POPUP, (UINT_PTR)hMenu_Settings, CLocalizationManager::get()->getTranslatedTextW("Menu_Settings").c_str());
	AppendMenu(hMenubar, MF_POPUP, (UINT_PTR)hMenu_Help, CLocalizationManager::get()->getTranslatedTextW("Menu_Help").c_str());

	//AppendMenu(hMenubar, MF_POPUP, (UINT_PTR)hMenu_File, _T("&File"));
	AppendMenu(hMenu_File, MF_STRING | MF_POPUP, (UINT_PTR)hMenu_File_New, CLocalizationManager::get()->getTranslatedTextW("Menu_NewIMG").c_str());
	AppendMenu(hMenu_File_New, MF_STRING, 1108, CLocalizationManager::get()->getTranslatedTextW("Menu_New_V1").c_str());
	AppendMenu(hMenu_File_New, MF_STRING, 1109, CLocalizationManager::get()->getTranslatedTextW("Menu_New_V2").c_str());
	AppendMenu(hMenu_File_New, MF_STRING | MF_POPUP, (UINT_PTR)hMenu_File_New_Version3, CLocalizationManager::get()->getTranslatedTextW("Menu_New_V3").c_str());
	AppendMenu(hMenu_File_New_Version3, MF_STRING, 1112, CLocalizationManager::get()->getTranslatedTextW("Menu_New_V3_Encrypted").c_str());
	AppendMenu(hMenu_File_New_Version3, MF_STRING, 1113, CLocalizationManager::get()->getTranslatedTextW("Menu_New_V3_Unencrypted").c_str());
	AppendMenu(hMenu_File_New, MF_SEPARATOR, 1942, _T(""));
	AppendMenu(hMenu_File_New, MF_STRING, 1943, CLocalizationManager::get()->getTranslatedTextW("Menu_New_VFastman92").c_str());
	AppendMenu(hMenu_File, MF_STRING, 2084, CLocalizationManager::get()->getTranslatedTextW("Menu_NewWindow").c_str());
	AppendMenu(hMenu_File, MF_SEPARATOR, 1760, _T(""));
	AppendMenu(hMenu_File, MF_STRING, 1100, CLocalizationManager::get()->getTranslatedTextW("Open").c_str());
	AppendMenu(hMenu_File, MF_STRING | MF_POPUP, (UINT_PTR)getIMGF()->m_hSubMenu_File_OpenRecent, CLocalizationManager::get()->getTranslatedTextW("Menu_OpenRecent").c_str());
	AppendMenu(hMenu_File, MF_STRING, 1117, CString2::convertStdStringToStdWString(CLocalizationManager::get()->getTranslatedText("Menu_OpenLast") + (getIMGF()->getRecentlyOpenManager()->getLastOpenEntry() == "" ? "" : " (" + CPath::getFileName(getIMGF()->getRecentlyOpenManager()->getLastOpenEntry()) + ")")).c_str());
	AppendMenu(hMenu_File, MF_STRING, 1114, CLocalizationManager::get()->getTranslatedTextW("Menu_Reopen").c_str());
	//AppendMenu(hMenu_File, MF_STRING, 1109, _T("Associate IMG extension"));
	AppendMenu(hMenu_File, MF_STRING | MF_POPUP, (UINT_PTR)hMenu_File_Sessions, CLocalizationManager::get()->getTranslatedTextW("Menu_Sessions").c_str());
	AppendMenu(hMenu_File_Sessions, MF_STRING | MF_POPUP, (UINT_PTR)getIMGF()->m_hSubMenu_File_Sessions, CLocalizationManager::get()->getTranslatedTextW("Menu_LoadSession").c_str());
	AppendMenu(hMenu_File_Sessions, MF_STRING, 1111, CLocalizationManager::get()->getTranslatedTextW("Menu_SaveSession").c_str());
	AppendMenu(hMenu_File_Sessions, MF_STRING, 1118, CLocalizationManager::get()->getTranslatedTextW("SessionManager").c_str());
	AppendMenu(hMenu_File, MF_SEPARATOR, 1761, _T(""));
	AppendMenu(hMenu_File, MF_STRING | MF_POPUP, (UINT_PTR)hMenu_File_SaveLog, CLocalizationManager::get()->getTranslatedTextW("Log").c_str());
	AppendMenu(hMenu_File_SaveLog, MF_STRING | MF_POPUP, (UINT_PTR)hMenu_File_SaveLog_ActiveTab, CLocalizationManager::get()->getTranslatedTextW("Menu_Log_ActiveTab").c_str());
	AppendMenu(hMenu_File_SaveLog, MF_STRING | MF_POPUP, (UINT_PTR)hMenu_File_SaveLog_AllTabs, CLocalizationManager::get()->getTranslatedTextW("AllTabs").c_str());
	AppendMenu(hMenu_File_SaveLog_ActiveTab, MF_STRING, 1101, CLocalizationManager::get()->getTranslatedTextW("Menu_Log_ActiveTab_SaveBasic").c_str());
	AppendMenu(hMenu_File_SaveLog_ActiveTab, MF_STRING, 1102, CLocalizationManager::get()->getTranslatedTextW("Menu_Log_ActiveTab_SaveExtended").c_str());
	AppendMenu(hMenu_File_SaveLog_ActiveTab, MF_STRING, 1121, CLocalizationManager::get()->getTranslatedTextW("Menu_Log_ActiveTab_Clear").c_str());
	AppendMenu(hMenu_File_SaveLog_ActiveTab, MF_STRING, 1103, CLocalizationManager::get()->getTranslatedTextW("Menu_Log_ActiveTab_OpenFileBasic").c_str());
	AppendMenu(hMenu_File_SaveLog_ActiveTab, MF_STRING, 1104, CLocalizationManager::get()->getTranslatedTextW("Menu_Log_ActiveTab_OpenFileExtended").c_str());
	AppendMenu(hMenu_File_SaveLog_ActiveTab, MF_STRING, 1120, CLocalizationManager::get()->getTranslatedTextW("Menu_Log_ActiveTab_OpenFolder").c_str());
	AppendMenu(hMenu_File_SaveLog_AllTabs, MF_STRING, 1115, CLocalizationManager::get()->getTranslatedTextW("Menu_Log_AllTabs_SaveBasic").c_str());
	AppendMenu(hMenu_File_SaveLog_AllTabs, MF_STRING, 1116, CLocalizationManager::get()->getTranslatedTextW("Menu_Log_AllTabs_SaveExtended").c_str());
	AppendMenu(hMenu_File_SaveLog_AllTabs, MF_STRING, 1122, CLocalizationManager::get()->getTranslatedTextW("Menu_Log_AllTabs_Clear").c_str());
	AppendMenu(hMenu_File, MF_SEPARATOR, 1762, _T(""));
	AppendMenu(hMenu_File, MF_STRING, 1926, CLocalizationManager::get()->getTranslatedTextW("Menu_RepeatLastAction").c_str());
	AppendMenu(hMenu_File, MF_STRING, 1179, CLocalizationManager::get()->getTranslatedTextW("RenameIMG").c_str());
	AppendMenu(hMenu_File, MF_STRING, 1752, CLocalizationManager::get()->getTranslatedTextW("Menu_OpenIMGFolder").c_str());
	AppendMenu(hMenu_File, MF_SEPARATOR, 1927, _T(""));
	AppendMenu(hMenu_File, MF_STRING, 1105, CLocalizationManager::get()->getTranslatedTextW("Close").c_str());
	AppendMenu(hMenu_File, MF_STRING, 1106, CLocalizationManager::get()->getTranslatedTextW("CloseAll").c_str());
	AppendMenu(hMenu_File, MF_STRING, 1107, CLocalizationManager::get()->getTranslatedTextW("Menu_ExitTool").c_str());

	AppendMenu(hMenu_Edit, MF_STRING, 1180, CLocalizationManager::get()->getTranslatedTextW("Find").c_str());
	AppendMenu(hMenu_Edit, MF_STRING, 1181, CLocalizationManager::get()->getTranslatedTextW("Menu_Find_AllTabs").c_str());
	AppendMenu(hMenu_Edit, MF_SEPARATOR, 1720, _T(""));
	AppendMenu(hMenu_Edit, MF_STRING | MF_POPUP, (UINT_PTR)hMenu_Edit_Select, CLocalizationManager::get()->getTranslatedTextW("Menu_Select").c_str());
	AppendMenu(hMenu_Edit_Select, MF_STRING, 1167, CLocalizationManager::get()->getTranslatedTextW("Select_All").c_str());
	AppendMenu(hMenu_Edit_Select, MF_STRING, 1168, CLocalizationManager::get()->getTranslatedTextW("Select_Inverse").c_str());
	AppendMenu(hMenu_Edit_Select, MF_SEPARATOR, 1730, _T(""));
	AppendMenu(hMenu_Edit_Select, MF_STRING, 1560, CLocalizationManager::get()->getTranslatedTextW("Menu_Select_Extensions").c_str());
	AppendMenu(hMenu_Edit_Select, MF_STRING | MF_POPUP, (UINT_PTR)hMenu_Edit_SelectViaRWVersion, CLocalizationManager::get()->getTranslatedTextW("Menu_Select_RWVersion").c_str());
	AppendMenu(hMenu_Edit_Select, MF_STRING, 1900, CLocalizationManager::get()->getTranslatedTextW("Menu_Select_IDE").c_str());
	uint32 i = 0;
	for (auto pRWVersion : CRWManager::get()->getVersionManager()->getEntries())
	{
		getIMGF()->m_umapMenuItemMapping_SelectRWVersion[1561 + i] = pRWVersion;
		string strMenuText = CLocalizationManager::get()->getTranslatedText("Menu_Select_RWVersion_Prefix") + " " + CString2::escapeMenuText((pRWVersion->getVersionName() + " (" + CLocalizationManager::get()->getTranslatedText(pRWVersion->getLocalizationKey()) + ")").substr(0, 2)) + "&" + CString2::escapeMenuText((pRWVersion->getVersionName() + " (" + CLocalizationManager::get()->getTranslatedText(pRWVersion->getLocalizationKey()) + ")").substr(2));
		AppendMenu(hMenu_Edit_SelectViaRWVersion, MF_STRING, 1561 + i, CString2::convertStdStringToStdWString(strMenuText).c_str());
		i++;
	}
	AppendMenu(hMenu_Edit_SelectViaRWVersion, MF_SEPARATOR, 1731, _T(""));
	AppendMenu(hMenu_Edit_SelectViaRWVersion, MF_STRING, 1568, CString2::convertStdStringToStdWString(CLocalizationManager::get()->getTranslatedText("Menu_Select_RWVersion_Prefix") + " " + CLocalizationManager::get()->getTranslatedText("Window_Main_Combo_RWVersion_Unknown")).c_str());
	AppendMenu(hMenu_Edit, MF_SEPARATOR, 1185, _T(""));
	AppendMenu(hMenu_Edit, MF_STRING, 1182, CLocalizationManager::get()->getTranslatedTextW("Menu_Import").c_str());
	AppendMenu(hMenu_Edit, MF_STRING, 1183, CLocalizationManager::get()->getTranslatedTextW("Menu_Replace").c_str());
	AppendMenu(hMenu_Edit, MF_STRING, 1184, CLocalizationManager::get()->getTranslatedTextW("Menu_Remove").c_str());

	AppendMenu(hMenu_DAT, MF_STRING, 2056, CLocalizationManager::get()->getTranslatedTextW("Menu_DATPathsMover").c_str());
	AppendMenu(hMenu_DAT, MF_STRING, 2057, CLocalizationManager::get()->getTranslatedTextW("Menu_DATModelList").c_str());

	AppendMenu(hMenu_IMG, MF_STRING, 1140, CLocalizationManager::get()->getTranslatedTextW("Rebuild").c_str());
	AppendMenu(hMenu_IMG, MF_STRING, 1141, CLocalizationManager::get()->getTranslatedTextW("Menu_RebuildAs").c_str());
	AppendMenu(hMenu_IMG, MF_STRING, 1142, CLocalizationManager::get()->getTranslatedTextW("RebuildAll").c_str());
	AppendMenu(hMenu_IMG, MF_SEPARATOR, 1740, _T(""));
	AppendMenu(hMenu_IMG, MF_STRING | MF_POPUP, (UINT_PTR)hMenu_IMG_ConvertTo, CLocalizationManager::get()->getTranslatedTextW("Menu_ConvertToVersion").c_str());
	AppendMenu(hMenu_IMG_ConvertTo, MF_STRING, 1143, CLocalizationManager::get()->getTranslatedTextW("Menu_ConvertToVersion1").c_str());
	AppendMenu(hMenu_IMG_ConvertTo, MF_STRING, 1144, CLocalizationManager::get()->getTranslatedTextW("Menu_ConvertToVersion2").c_str());
	AppendMenu(hMenu_IMG_ConvertTo, MF_STRING | MF_POPUP, (UINT_PTR)hMenu_IMG_ConvertTo_Version3, CLocalizationManager::get()->getTranslatedTextW("Menu_ConvertToVersion3").c_str());
	AppendMenu(hMenu_IMG_ConvertTo_Version3, MF_STRING, 1145, CLocalizationManager::get()->getTranslatedTextW("Menu_ConvertToVersion3Encrypted").c_str());
	AppendMenu(hMenu_IMG_ConvertTo_Version3, MF_STRING, 1146, CLocalizationManager::get()->getTranslatedTextW("Menu_ConvertToVersion3Unencrypted").c_str());
	AppendMenu(hMenu_IMG_ConvertTo, MF_SEPARATOR, 2200, _T(""));
	AppendMenu(hMenu_IMG_ConvertTo, MF_STRING, 2201, CLocalizationManager::get()->getTranslatedTextW("Menu_ConvertToVersionFastman92").c_str());
	AppendMenu(hMenu_IMG, MF_STRING, 1147, CLocalizationManager::get()->getTranslatedTextW("Merge").c_str());
	AppendMenu(hMenu_IMG, MF_STRING | MF_POPUP, (UINT_PTR)hMenu_IMG_Split, CLocalizationManager::get()->getTranslatedTextW("Split").c_str());
	AppendMenu(hMenu_IMG_Split, MF_STRING, 1156, CLocalizationManager::get()->getTranslatedTextW("Menu_SplitSelected").c_str());
	AppendMenu(hMenu_IMG_Split, MF_STRING, 1157, CLocalizationManager::get()->getTranslatedTextW("Menu_SplitIDE").c_str());
	AppendMenu(hMenu_IMG_Split, MF_STRING, 1158, CLocalizationManager::get()->getTranslatedTextW("Menu_SplitTextLines").c_str());
	AppendMenu(hMenu_IMG, MF_SEPARATOR, 1741, _T(""));

	AppendMenu(hMenu_IMG, MF_STRING | MF_POPUP, (UINT_PTR)getIMGF()->m_hMenu_Entry_Sort, CLocalizationManager::get()->getTranslatedTextW("Sort").c_str());
	for (uint32 i = 0; i < 10; i++)
	{
		AppendMenu(getIMGF()->m_hMenu_Entry_Sort, MF_STRING | MF_POPUP, (UINT_PTR)hMenu_Entry_Sort_Priorities[i], CLocalizationManager::get()->getTranslatedFormattedTextW("Sort_Priority_N", (i + 1)).c_str());
		uint32 i2 = 0;
		for (auto pSortType : getIMGF()->getSortManager()->getSortTypes()->getEntries())
		{
			CSortPriority *pSortPriority = getIMGF()->getSortManager()->getSortPriorities()->getEntryByIndex((uint16)i);

			uint32 uiMenuHandle = 1200 + (20 * i) + i2;
			AppendMenu(hMenu_Entry_Sort_Priorities[i], MF_STRING, uiMenuHandle, CLocalizationManager::get()->getTranslatedFormattedTextW("Sort_ByText", pSortType->getTextForMenu().c_str()).c_str());
			getIMGF()->getSortManager()->getSortMenuItems()->addEntry(new CSortMenuItem(uiMenuHandle, pSortPriority, pSortType));
			i2++;
		}
	}

	AppendMenu(hMenu_IMG, MF_STRING, 2050, CLocalizationManager::get()->getTranslatedTextW("Renamer").c_str());
	AppendMenu(hMenu_IMG, MF_STRING, 1155, CLocalizationManager::get()->getTranslatedTextW("UpdateLST").c_str());
	AppendMenu(hMenu_IMG, MF_SEPARATOR, 1743, _T(""));
	AppendMenu(hMenu_IMG, MF_STRING, 2090, CLocalizationManager::get()->getTranslatedTextW("CloneIMG").c_str());
	AppendMenu(hMenu_IMG, MF_STRING, 1153, CLocalizationManager::get()->getTranslatedTextW("DuplicateEntries").c_str());
	AppendMenu(hMenu_IMG, MF_STRING | MF_POPUP, (UINT_PTR)hMenu_IMG_Validation, CLocalizationManager::get()->getTranslatedTextW("Menu_Validation").c_str());
	AppendMenu(hMenu_IMG_Validation, MF_STRING, 2002, CLocalizationManager::get()->getTranslatedTextW("Menu_Validation_SaveIMGSignature").c_str());
	AppendMenu(hMenu_IMG_Validation, MF_STRING, 2003, CLocalizationManager::get()->getTranslatedTextW("Menu_Validation_VerifyIMGSignature").c_str());
	AppendMenu(hMenu_IMG_Validation, MF_STRING, 2005, CLocalizationManager::get()->getTranslatedTextW("Menu_Validation_DFF").c_str());
	AppendMenu(hMenu_IMG_Validation, MF_STRING, 2006, CLocalizationManager::get()->getTranslatedTextW("Menu_Validation_TXD").c_str());
	AppendMenu(hMenu_IMG, MF_STRING, 2004, CLocalizationManager::get()->getTranslatedTextW("Menu_Compare").c_str());
	AppendMenu(hMenu_IMG, MF_SEPARATOR, 1742, _T(""));
	AppendMenu(hMenu_IMG, MF_STRING, 1149, CLocalizationManager::get()->getTranslatedTextW("Menu_Stats").c_str());
	AppendMenu(hMenu_IMG, MF_SEPARATOR, 2052, _T(""));
	AppendMenu(hMenu_IMG, MF_STRING, 2053, CLocalizationManager::get()->getTranslatedTextW("Menu_IMGVersionSettings").c_str());

	//AppendMenu(hMenu_Model, MF_STRING, 2105, CLocalizationManager::get()->getTranslatedTextW("Menu_ExtractDVCAndNVCColoursIntoDFFs").c_str());
	//AppendMenu(hMenu_Model, MF_STRING, 2106, CLocalizationManager::get()->getTranslatedTextW("Menu_Extract2dEffectsIntoDFFs").c_str());
	AppendMenu(hMenu_Model, MF_SEPARATOR, 2052, _T(""));
	AppendMenu(hMenu_Model, MF_STRING | MF_POPUP, (UINT_PTR)hMenu_Model_Convert, CLocalizationManager::get()->getTranslatedTextW("Convert").c_str());
	AppendMenu(hMenu_Model_Convert, MF_STRING | MF_POPUP, (UINT_PTR)hMenu_Model_Convert_DFFRWVersion, CLocalizationManager::get()->getTranslatedTextW("DFFRWVersion").c_str());
	AppendMenu(hMenu_Model, MF_STRING, 2081, CLocalizationManager::get()->getTranslatedTextW("Menu_Model_RemoveOrphanTextures").c_str());

	i = 0;
	for (auto pRWVersion : CRWManager::get()->getVersionManager()->getEntries())
	{
		if (pRWVersion->getVersionType() != TYPE_MODEL)
		{
			continue;
		}

		getIMGF()->m_umapMenuItemMapping_ConvertDFFtoRWVersion[1590 + i] = pRWVersion;
		string strMenuText = "Convert DFF to " + CString2::escapeMenuText((pRWVersion->getVersionName() + " (" + CLocalizationManager::get()->getTranslatedText(pRWVersion->getLocalizationKey()) + ")").substr(0, 2)) + "&" + CString2::escapeMenuText((pRWVersion->getVersionName() + " (" + CLocalizationManager::get()->getTranslatedText(pRWVersion->getLocalizationKey()) + ")").substr(2));
		AppendMenu(hMenu_Model_Convert_DFFRWVersion, MF_STRING, 1590 + i, CString2::convertStdStringToStdWString(strMenuText).c_str());
		i++;
	}

	//AppendMenu(hMenu_Model_Convert, MF_STRING | MF_POPUP, (UINT_PTR)hMenu_Model_Convert_FileFormat, CLocalizationManager::get()->getTranslatedTextW("Menu_Convert_FileFormat").c_str());
	//AppendMenu(hMenu_Model_Convert_FileFormat, MF_STRING, 1840, _T("Convert DFF to WDR"));

	AppendMenu(hMenu_Texture, MF_STRING, 1154, CLocalizationManager::get()->getTranslatedTextW("Dump").c_str());
	AppendMenu(hMenu_Texture, MF_STRING, 2051, CLocalizationManager::get()->getTranslatedTextW("BuildTXD").c_str());
	AppendMenu(hMenu_Texture, MF_STRING, 2055, CLocalizationManager::get()->getTranslatedTextW("Menu_TXDOrganizer").c_str());
	AppendMenu(hMenu_Texture, MF_SEPARATOR, 2080, _T(""));

	AppendMenu(hMenu_Texture, MF_STRING | MF_POPUP, (UINT_PTR)hMenu_Texture_Convert, CLocalizationManager::get()->getTranslatedTextW("Convert").c_str());

	AppendMenu(hMenu_Texture_Convert, MF_STRING | MF_POPUP, (UINT_PTR)hMenu_Texture_Convert_TXDGame, CLocalizationManager::get()->getTranslatedTextW("Menu_Convert_TXD_Game").c_str());
	AppendMenu(hMenu_Texture_Convert_TXDGame, MF_STRING, 1650, CLocalizationManager::get()->getTranslatedFormattedTextW("Menu_Convert_TXD_To", CLocalizationManager::get()->getTranslatedFormattedText("PlatformedGame_PC_GTA_III").c_str()).c_str());
	AppendMenu(hMenu_Texture_Convert_TXDGame, MF_STRING, 1651, CLocalizationManager::get()->getTranslatedFormattedTextW("Menu_Convert_TXD_To", CLocalizationManager::get()->getTranslatedFormattedText("PlatformedGame_PC_GTA_VC").c_str()).c_str());
	AppendMenu(hMenu_Texture_Convert_TXDGame, MF_STRING, 1652, CLocalizationManager::get()->getTranslatedFormattedTextW("Menu_Convert_TXD_To", CLocalizationManager::get()->getTranslatedFormattedText("PlatformedGame_PC_GTA_SA").c_str()).c_str());
	AppendMenu(hMenu_Texture_Convert_TXDGame, MF_STRING, 1653, CLocalizationManager::get()->getTranslatedFormattedTextW("Menu_Convert_TXD_To", CLocalizationManager::get()->getTranslatedFormattedText("PlatformedGame_Android_GTA").c_str()).c_str());
	AppendMenu(hMenu_Texture_Convert_TXDGame, MF_STRING, 1654, CLocalizationManager::get()->getTranslatedFormattedTextW("Menu_Convert_TXD_To", CLocalizationManager::get()->getTranslatedFormattedText("PlatformedGame_XBOX_GTA").c_str()).c_str());

	AppendMenu(hMenu_Texture_Convert, MF_STRING | MF_POPUP, (UINT_PTR)hMenu_Texture_Convert_TXDRWVersion, CLocalizationManager::get()->getTranslatedTextW("TXDRWVersion").c_str());
	i = 0;
	for (auto pRWVersion : CRWManager::get()->getVersionManager()->getEntries())
	{
		if (pRWVersion->getVersionType() != TYPE_MODEL)
		{
			continue;
		}

		getIMGF()->m_umapMenuItemMapping_ConvertTXDtoRWVersion[1660 + i] = pRWVersion;
		string strString1 = CString2::escapeMenuText((pRWVersion->getVersionName() + " (" + CLocalizationManager::get()->getTranslatedText(pRWVersion->getLocalizationKey()) + ")").substr(0, 2)) + "&" + CString2::escapeMenuText((pRWVersion->getVersionName() + " (" + CLocalizationManager::get()->getTranslatedText(pRWVersion->getLocalizationKey()) + ")").substr(2));
		string strMenuText = CLocalizationManager::get()->getTranslatedFormattedText("Menu_Convert_TXD_To", strString1.c_str());
		AppendMenu(hMenu_Texture_Convert_TXDRWVersion, MF_STRING, 1660 + i, CString2::convertStdStringToStdWString(strMenuText).c_str());
		i++;
	}

	AppendMenu(hMenu_Texture_Convert, MF_STRING | MF_POPUP, (UINT_PTR)hMenu_Texture_Convert_TXDTextureFormat, CLocalizationManager::get()->getTranslatedTextW("Menu_Convert_TXD_RasterFormat").c_str());
	i = 0;
	for (auto pRasterDataFormat : CImageManager::get()->getRasterDataFormatManager()->getEntries())
	{
		getIMGF()->m_umapMenuItemMapping_ConvertTXDtoTextureFormat[2100 + i] = pRasterDataFormat;
		AppendMenu(hMenu_Texture_Convert_TXDTextureFormat, MF_STRING, 2100 + i, CLocalizationManager::get()->getTranslatedFormattedTextW("Menu_Convert_TXD_To", pRasterDataFormat->getTextForMenu().c_str()).c_str());
		i++;
	}

	//AppendMenu(hMenu_Texture_Convert, MF_STRING | MF_POPUP, (UINT_PTR)hMenu_Texture_Convert_WTDFileFormat, CLocalizationManager::get()->getTranslatedTextW("Menu_Convert_WTDFileFormat").c_str());
	//AppendMenu(hMenu_Texture_Convert_WTDFileFormat, MF_STRING, 2500, CLocalizationManager::get()->getTranslatedTextW("Menu_Convert_WTD_TXD").c_str());

	AppendMenu(hMenu_Texture, MF_STRING, 1150, CLocalizationManager::get()->getTranslatedTextW("Menu_TextureList").c_str());
	AppendMenu(hMenu_Texture, MF_STRING, 1620, CLocalizationManager::get()->getTranslatedTextW("Menu_MissingTexture").c_str());

	AppendMenu(hMenu_Collision, MF_STRING, 1681, CLocalizationManager::get()->getTranslatedTextW("Menu_AlignMeshes_COL_DFF").c_str());
	AppendMenu(hMenu_Collision, MF_SEPARATOR, 1702, _T(""));

	AppendMenu(hMenu_Collision, MF_STRING | MF_POPUP, (UINT_PTR)hMenu_Collision_Convert, CLocalizationManager::get()->getTranslatedTextW("Convert").c_str());

	i = 0;
	for (auto pCOLVersion : CCOLManager::get()->getVersionManager()->getEntries())
	{
		getIMGF()->m_umapMenuItemMapping_ConvertCOLtoCOLVersion[2400 + i] = pCOLVersion;
		AppendMenu(hMenu_Collision_Convert, MF_STRING, 2400 + i, CLocalizationManager::get()->getTranslatedFormattedTextW("Menu_Convert_COL_COL", pCOLVersion->getText().c_str()).c_str());
		i++;
	}

	AppendMenu(hMenu_Collision, MF_STRING, 1680, CLocalizationManager::get()->getTranslatedTextW("Menu_CenterCOLMeshes").c_str());

	AppendMenu(hMenu_ItemDefinition, MF_STRING | MF_POPUP, (UINT_PTR)hMenu_ItemDefinition_FindOrphanEntries, CLocalizationManager::get()->getTranslatedTextW("Menu_FindOrphanEntries").c_str());
	AppendMenu(hMenu_ItemDefinition_FindOrphanEntries, MF_STRING, 2091, CLocalizationManager::get()->getTranslatedTextW("Menu_OrphanEntries_IDE_COL").c_str());
	AppendMenu(hMenu_ItemDefinition_FindOrphanEntries, MF_STRING, 2092, CLocalizationManager::get()->getTranslatedTextW("Menu_OrphanEntries_IDE_DFF").c_str());
	AppendMenu(hMenu_ItemDefinition_FindOrphanEntries, MF_STRING, 2093, CLocalizationManager::get()->getTranslatedTextW("Menu_OrphanEntries_IDE_IMG").c_str());
	AppendMenu(hMenu_ItemDefinition_FindOrphanEntries, MF_STRING, 2094, CLocalizationManager::get()->getTranslatedTextW("Menu_OrphanEntries_IDE_IPL").c_str());
	AppendMenu(hMenu_ItemDefinition_FindOrphanEntries, MF_STRING, 2095, CLocalizationManager::get()->getTranslatedTextW("Menu_OrphanEntries_IDE_TXD").c_str());
	AppendMenu(hMenu_ItemDefinition, MF_STRING | MF_POPUP, (UINT_PTR)hMenu_ItemDefinition_FindMissing, CLocalizationManager::get()->getTranslatedTextW("Menu_FindMissingEntries").c_str());
	AppendMenu(hMenu_ItemDefinition_FindMissing, MF_STRING, 2059, CLocalizationManager::get()->getTranslatedTextW("Menu_MissingEntries_IDE_IMG_TXD").c_str());
	AppendMenu(hMenu_ItemDefinition_FindMissing, MF_STRING, 2060, CLocalizationManager::get()->getTranslatedTextW("Menu_MissingEntries_IDE_COL_COL").c_str());
	AppendMenu(hMenu_ItemDefinition_FindMissing, MF_STRING, 2061, CLocalizationManager::get()->getTranslatedTextW("Menu_MissingEntries_IDE_IMG_DFF").c_str());
	AppendMenu(hMenu_ItemDefinition, MF_STRING, 2062, CLocalizationManager::get()->getTranslatedTextW("Menu_SortDATIDEAndIPL_ByObjectId").c_str());

	AppendMenu(hMenu_ItemPlacement, MF_STRING | MF_POPUP, (UINT_PTR)hMenu_ItemPlacement_FindMissing, CLocalizationManager::get()->getTranslatedTextW("Menu_FindMissingEntries").c_str());
	AppendMenu(hMenu_ItemPlacement_FindMissing, MF_STRING, 2097, CLocalizationManager::get()->getTranslatedTextW("Menu_MissingEntries_IPL_IDE_DFF").c_str());

	AppendMenu(hMenu_ItemPlacement, MF_STRING, 2058, CLocalizationManager::get()->getTranslatedTextW("Menu_MapMoverAndIDShifter").c_str());

	AppendMenu(hMenu_Entry, MF_STRING | MF_POPUP, (UINT_PTR)hMenu_Entry_Import, CLocalizationManager::get()->getTranslatedTextW("Menu_Import").c_str());
	AppendMenu(hMenu_Entry_Import, MF_STRING, 1160, CLocalizationManager::get()->getTranslatedTextW("Menu_Import_Files").c_str());
	AppendMenu(hMenu_Entry_Import, MF_STRING, 1161, CLocalizationManager::get()->getTranslatedTextW("Menu_Import_IDE").c_str());
	AppendMenu(hMenu_Entry_Import, MF_STRING, 1169, CLocalizationManager::get()->getTranslatedTextW("Menu_Import_TextLines").c_str());
	AppendMenu(hMenu_Entry_Import, MF_STRING, 1170, CLocalizationManager::get()->getTranslatedTextW("Menu_Import_Folder").c_str());
	AppendMenu(hMenu_Entry, MF_STRING | MF_POPUP, (UINT_PTR)hMenu_Entry_Export, CLocalizationManager::get()->getTranslatedTextW("Menu_Export").c_str());
	AppendMenu(hMenu_Entry_Export, MF_STRING, 1162, CLocalizationManager::get()->getTranslatedTextW("Menu_Export_Selected").c_str());
	AppendMenu(hMenu_Entry_Export, MF_STRING, 1163, CLocalizationManager::get()->getTranslatedTextW("Menu_Export_IDE").c_str());
	AppendMenu(hMenu_Entry_Export, MF_STRING, 1350, CLocalizationManager::get()->getTranslatedTextW("Menu_Export_IPL").c_str());
	AppendMenu(hMenu_Entry_Export, MF_STRING, 1164, CLocalizationManager::get()->getTranslatedTextW("Menu_Export_TextLines").c_str());
	AppendMenu(hMenu_Entry_Export, MF_STRING, 1192, CLocalizationManager::get()->getTranslatedTextW("Menu_Export_DAT").c_str());
	AppendMenu(hMenu_Entry_Export, MF_SEPARATOR, 1710, _T(""));
	AppendMenu(hMenu_Entry_Export, MF_STRING, 1550, CLocalizationManager::get()->getTranslatedTextW("QuickExport").c_str());
	AppendMenu(hMenu_Entry_Export, MF_SEPARATOR, 1711, _T(""));
	AppendMenu(hMenu_Entry_Export, MF_STRING, 1551, CLocalizationManager::get()->getTranslatedTextW("Menu_Export_AllTabs").c_str());
	AppendMenu(hMenu_Entry_Export, MF_STRING, 1554, CLocalizationManager::get()->getTranslatedTextW("Menu_Export_AllTabsIntoFolders").c_str());
	AppendMenu(hMenu_Entry_Export, MF_SEPARATOR, 1712, _T(""));
	AppendMenu(hMenu_Entry_Export, MF_STRING, 1552, CLocalizationManager::get()->getTranslatedTextW("Menu_Export_AllTabsIDE").c_str());
	AppendMenu(hMenu_Entry_Export, MF_STRING, 1553, CLocalizationManager::get()->getTranslatedTextW("Menu_Export_AllTabsTextLines").c_str());
	AppendMenu(hMenu_Entry, MF_STRING | MF_POPUP, (UINT_PTR)hMenu_Entry_Remove, CLocalizationManager::get()->getTranslatedTextW("Menu_Remove").c_str());
	AppendMenu(hMenu_Entry_Remove, MF_STRING, 1165, CLocalizationManager::get()->getTranslatedTextW("Menu_Remove_Selected").c_str());
	AppendMenu(hMenu_Entry_Remove, MF_STRING, 1177, CLocalizationManager::get()->getTranslatedTextW("Menu_Remove_IDE").c_str());
	AppendMenu(hMenu_Entry_Remove, MF_STRING, 1178, CLocalizationManager::get()->getTranslatedTextW("Menu_Remove_TextLines").c_str());
	AppendMenu(hMenu_Entry, MF_STRING | MF_POPUP, (UINT_PTR)hMenu_Entry_Replace, CLocalizationManager::get()->getTranslatedTextW("Menu_Replace").c_str());
	AppendMenu(hMenu_Entry_Replace, MF_STRING, 1176, CLocalizationManager::get()->getTranslatedTextW("Menu_Replace_Selected").c_str());
	AppendMenu(hMenu_Entry_Replace, MF_STRING, 1621, CLocalizationManager::get()->getTranslatedTextW("Menu_Replace_Folder").c_str());
	AppendMenu(hMenu_Entry, MF_SEPARATOR, 1700, _T(""));

	AppendMenu(hMenu_Entry, MF_STRING | MF_POPUP, (UINT_PTR)hMenu_Entry_Shift, CLocalizationManager::get()->getTranslatedTextW("Menu_Shift").c_str());
	AppendMenu(hMenu_Entry_Shift, MF_STRING, 1540, CLocalizationManager::get()->getTranslatedTextW("Menu_Shift_Up").c_str());
	AppendMenu(hMenu_Entry_Shift, MF_STRING, 1541, CLocalizationManager::get()->getTranslatedTextW("Menu_Shift_Down").c_str());
	AppendMenu(hMenu_Entry, MF_STRING, 1166, CLocalizationManager::get()->getTranslatedTextW("Menu_Rename").c_str());
	AppendMenu(hMenu_Entry, MF_STRING | MF_POPUP, (UINT_PTR)hMenu_Entry_Case, CLocalizationManager::get()->getTranslatedTextW("Menu_NameCase").c_str());
	AppendMenu(hMenu_Entry_Case, MF_STRING | MF_POPUP, (UINT_PTR)hMenu_Entry_LowerCase, CLocalizationManager::get()->getTranslatedTextW("Menu_NameCase_Lowercase").c_str());
	AppendMenu(hMenu_Entry_LowerCase, MF_STRING, 1500, CLocalizationManager::get()->getTranslatedTextW("Menu_NameCase_NameWithExtension").c_str());
	AppendMenu(hMenu_Entry_LowerCase, MF_STRING, 1501, CLocalizationManager::get()->getTranslatedTextW("Menu_NameCase_NameWithoutExtension").c_str());
	AppendMenu(hMenu_Entry_LowerCase, MF_STRING, 1502, CLocalizationManager::get()->getTranslatedTextW("Menu_NameCase_Extension").c_str());
	AppendMenu(hMenu_Entry_Case, MF_STRING | MF_POPUP, (UINT_PTR)hMenu_Entry_UpperCase, CLocalizationManager::get()->getTranslatedTextW("Menu_NameCase_Uppercase").c_str());
	AppendMenu(hMenu_Entry_UpperCase, MF_STRING, 1510, CLocalizationManager::get()->getTranslatedTextW("Menu_NameCase_NameWithExtension").c_str());
	AppendMenu(hMenu_Entry_UpperCase, MF_STRING, 1511, CLocalizationManager::get()->getTranslatedTextW("Menu_NameCase_NameWithoutExtension").c_str());
	AppendMenu(hMenu_Entry_UpperCase, MF_STRING, 1512, CLocalizationManager::get()->getTranslatedTextW("Menu_NameCase_Extension").c_str());
	AppendMenu(hMenu_Entry_Case, MF_STRING | MF_POPUP, (UINT_PTR)hMenu_Entry_TitleCase, CLocalizationManager::get()->getTranslatedTextW("Titlecase").c_str());
	AppendMenu(hMenu_Entry_TitleCase, MF_STRING, 1520, CLocalizationManager::get()->getTranslatedTextW("Menu_NameCase_NameWithExtension").c_str());
	AppendMenu(hMenu_Entry_TitleCase, MF_STRING, 1521, CLocalizationManager::get()->getTranslatedTextW("Menu_NameCase_NameWithoutExtension").c_str());
	AppendMenu(hMenu_Entry_TitleCase, MF_STRING, 1522, CLocalizationManager::get()->getTranslatedTextW("Menu_NameCase_Extension").c_str());
	AppendMenu(hMenu_Entry, MF_SEPARATOR, 1701, _T(""));
	AppendMenu(hMenu_Entry, MF_STRING | MF_POPUP, (UINT_PTR)hMenu_Entry_Copy, CLocalizationManager::get()->getTranslatedTextW("Menu_Copy").c_str());
	AppendMenu(hMenu_Entry_Copy, MF_STRING, 1530, CLocalizationManager::get()->getTranslatedTextW("Menu_Copy_ID").c_str());
	AppendMenu(hMenu_Entry_Copy, MF_STRING, 1531, CLocalizationManager::get()->getTranslatedTextW("Menu_Copy_Name").c_str());
	AppendMenu(hMenu_Entry_Copy, MF_STRING, 1532, CLocalizationManager::get()->getTranslatedTextW("Offset").c_str());
	AppendMenu(hMenu_Entry_Copy, MF_STRING, 1533, CLocalizationManager::get()->getTranslatedTextW("Menu_Copy_ResourceType").c_str());
	AppendMenu(hMenu_Entry_Copy, MF_STRING, 1534, CLocalizationManager::get()->getTranslatedTextW("RWVersion").c_str());
	AppendMenu(hMenu_Entry_Copy, MF_STRING, 1535, CLocalizationManager::get()->getTranslatedTextW("Size").c_str());
	AppendMenu(hMenu_Entry_Copy, MF_STRING, 1536, CLocalizationManager::get()->getTranslatedTextW("Menu_Copy_Type").c_str());
	//AppendMenu(hMenu_Entry, MF_SEPARATOR, 1703, _T(""));

	AppendMenu(hMenu_Settings, MF_STRING, 1580, CLocalizationManager::get()->getTranslatedTextW("Settings").c_str());

	AppendMenu(hMenu_Help, MF_STRING, 1570, CLocalizationManager::get()->getTranslatedTextW("Version").c_str());
	AppendMenu(hMenu_Help, MF_STRING, 1572, CLocalizationManager::get()->getTranslatedTextW("Menu_Update").c_str());
	AppendMenu(hMenu_Help, MF_SEPARATOR, 1574, _T(""));
	AppendMenu(hMenu_Help, MF_STRING, 1571, CLocalizationManager::get()->getTranslatedTextW("Menu_Website").c_str());
	AppendMenu(hMenu_Help, MF_STRING, 1575, CLocalizationManager::get()->getTranslatedTextW("Menu_ReportIssueOrIdea").c_str());
	AppendMenu(hMenu_Help, MF_SEPARATOR, 1574, _T(""));
	AppendMenu(hMenu_Help, MF_STRING, 1573, CLocalizationManager::get()->getTranslatedTextW("Credits").c_str());

	::SetMenu(getIMGF()->getDialog()->GetSafeHwnd(), hMenubar);
	*/
}

void					CIMGEditor::loadRightClickMenu(int xPos, int yPos)
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

	AppendMenu(hMenu, MF_STRING, 1550, CLocalizationManager::get()->getTranslatedTextW("QuickExport").c_str());
	AppendMenu(hMenu, MF_STRING, 1162, CLocalizationManager::get()->getTranslatedTextW("Menu_Export_Selected").c_str());
	AppendMenu(hMenu, MF_STRING, 1165, CLocalizationManager::get()->getTranslatedTextW("Menu_Remove_Selected").c_str());
	AppendMenu(hMenu, MF_STRING, 1176, CLocalizationManager::get()->getTranslatedTextW("Menu_Replace_Selected").c_str());
	AppendMenu(hMenu, MF_STRING | MF_POPUP, (UINT_PTR)hMenu_Shift, CLocalizationManager::get()->getTranslatedTextW("Menu_Shift").c_str());
	AppendMenu(hMenu_Shift, MF_STRING, 1540, CLocalizationManager::get()->getTranslatedTextW("Menu_Shift_Up").c_str());
	AppendMenu(hMenu_Shift, MF_STRING, 1541, CLocalizationManager::get()->getTranslatedTextW("Menu_Shift_Down").c_str());
	AppendMenu(hMenu, MF_STRING, 1166, CLocalizationManager::get()->getTranslatedTextW("Menu_Rename").c_str());
	AppendMenu(hMenu, MF_STRING | MF_POPUP, (UINT_PTR)hMenu_NameCase, CLocalizationManager::get()->getTranslatedTextW("Menu_NameCase").c_str());
	AppendMenu(hMenu_NameCase, MF_STRING | MF_POPUP, (UINT_PTR)hMenu_NameCase_LowerCase, CLocalizationManager::get()->getTranslatedTextW("Menu_NameCase_Lowercase").c_str());
	AppendMenu(hMenu_NameCase_LowerCase, MF_STRING, 1500, CLocalizationManager::get()->getTranslatedTextW("Menu_NameCase_NameWithExtension").c_str());
	AppendMenu(hMenu_NameCase_LowerCase, MF_STRING, 1501, CLocalizationManager::get()->getTranslatedTextW("Menu_NameCase_NameWithoutExtension").c_str());
	AppendMenu(hMenu_NameCase_LowerCase, MF_STRING, 1502, CLocalizationManager::get()->getTranslatedTextW("Menu_NameCase_Extension").c_str());
	AppendMenu(hMenu_NameCase, MF_STRING | MF_POPUP, (UINT_PTR)hMenu_NameCase_UpperCase, CLocalizationManager::get()->getTranslatedTextW("Menu_NameCase_Uppercase").c_str());
	AppendMenu(hMenu_NameCase_UpperCase, MF_STRING, 1510, CLocalizationManager::get()->getTranslatedTextW("Menu_NameCase_NameWithExtension").c_str());
	AppendMenu(hMenu_NameCase_UpperCase, MF_STRING, 1511, CLocalizationManager::get()->getTranslatedTextW("Menu_NameCase_NameWithoutExtension").c_str());
	AppendMenu(hMenu_NameCase_UpperCase, MF_STRING, 1512, CLocalizationManager::get()->getTranslatedTextW("Menu_NameCase_Extension").c_str());
	AppendMenu(hMenu_NameCase, MF_STRING | MF_POPUP, (UINT_PTR)hMenu_NameCase_TitleCase, CLocalizationManager::get()->getTranslatedTextW("Titlecase").c_str());
	AppendMenu(hMenu_NameCase_TitleCase, MF_STRING, 1520, CLocalizationManager::get()->getTranslatedTextW("Menu_NameCase_NameWithExtension").c_str());
	AppendMenu(hMenu_NameCase_TitleCase, MF_STRING, 1521, CLocalizationManager::get()->getTranslatedTextW("Menu_NameCase_NameWithoutExtension").c_str());
	AppendMenu(hMenu_NameCase_TitleCase, MF_STRING, 1522, CLocalizationManager::get()->getTranslatedTextW("Menu_NameCase_Extension").c_str());
	AppendMenu(hMenu, MF_STRING | MF_POPUP, (UINT_PTR)hMenu_Copy, CLocalizationManager::get()->getTranslatedTextW("Menu_Copy").c_str());
	AppendMenu(hMenu_Copy, MF_STRING, 1530, CLocalizationManager::get()->getTranslatedTextW("Menu_Copy_ID").c_str());
	AppendMenu(hMenu_Copy, MF_STRING, 1531, CLocalizationManager::get()->getTranslatedTextW("Menu_Copy_Name").c_str());
	AppendMenu(hMenu_Copy, MF_STRING, 1532, CLocalizationManager::get()->getTranslatedTextW("Offset").c_str());
	AppendMenu(hMenu_Copy, MF_STRING, 1533, CLocalizationManager::get()->getTranslatedTextW("Menu_Copy_ResourceType").c_str());
	AppendMenu(hMenu_Copy, MF_STRING, 1534, CLocalizationManager::get()->getTranslatedTextW("RWVersion").c_str());
	AppendMenu(hMenu_Copy, MF_STRING, 1535, CLocalizationManager::get()->getTranslatedTextW("Size").c_str());
	AppendMenu(hMenu_Copy, MF_STRING, 1536, CLocalizationManager::get()->getTranslatedTextW("Menu_Copy_Type").c_str());

	// DFF Entry
	AppendMenu(hMenu, MF_SEPARATOR, 1701, _T(""));

	AppendMenu(hMenu, MF_STRING | MF_POPUP, (UINT_PTR)hMenu_ConvertDFF, CLocalizationManager::get()->getTranslatedTextW("ConvertModel").c_str());
	AppendMenu(hMenu_ConvertDFF, MF_STRING | MF_POPUP, (UINT_PTR)hMenu_ConvertDFF_DFFRWVersion, CLocalizationManager::get()->getTranslatedTextW("DFFRWVersion").c_str());
	AppendMenu(hMenu, MF_STRING, 2081, CLocalizationManager::get()->getTranslatedTextW("Menu_Model_RemoveOrphanTextures").c_str());

	i = 0;
	for (auto pRWVersion : CRWManager::get()->getVersionManager()->getEntries())
	{
		if (pRWVersion->getVersionType() != TYPE_MODEL)
		{
			continue;
		}

		string strMenuText = "Convert DFF to " + CString2::escapeMenuText((pRWVersion->getVersionName() + " (" + CLocalizationManager::get()->getTranslatedText(pRWVersion->getLocalizationKey()) + ")").substr(0, 2)) + "&" + CString2::escapeMenuText((pRWVersion->getVersionName() + " (" + CLocalizationManager::get()->getTranslatedText(pRWVersion->getLocalizationKey()) + ")").substr(2));
		AppendMenu(hMenu_ConvertDFF_DFFRWVersion, MF_STRING, 1590 + i, CString2::convertStdStringToStdWString(strMenuText).c_str());
		i++;
	}

	// TXD Entry
	AppendMenu(hMenu, MF_SEPARATOR, 1701, _T(""));

	AppendMenu(hMenu, MF_STRING | MF_POPUP, (UINT_PTR)hMenu_ConvertTXD, CLocalizationManager::get()->getTranslatedTextW("ConvertTexture").c_str());

	AppendMenu(hMenu_ConvertTXD, MF_STRING | MF_POPUP, (UINT_PTR)hMenu_ConvertTXD_TXDGame, CLocalizationManager::get()->getTranslatedTextW("Menu_Convert_TXD_Game").c_str());
	AppendMenu(hMenu_ConvertTXD_TXDGame, MF_STRING, 1650, CLocalizationManager::get()->getTranslatedFormattedTextW("Menu_Convert_TXD_To", CLocalizationManager::get()->getTranslatedFormattedText("PlatformedGame_PC_GTA_III").c_str()).c_str());
	AppendMenu(hMenu_ConvertTXD_TXDGame, MF_STRING, 1651, CLocalizationManager::get()->getTranslatedFormattedTextW("Menu_Convert_TXD_To", CLocalizationManager::get()->getTranslatedFormattedText("PlatformedGame_PC_GTA_VC").c_str()).c_str());
	AppendMenu(hMenu_ConvertTXD_TXDGame, MF_STRING, 1652, CLocalizationManager::get()->getTranslatedFormattedTextW("Menu_Convert_TXD_To", CLocalizationManager::get()->getTranslatedFormattedText("PlatformedGame_PC_GTA_SA").c_str()).c_str());
	AppendMenu(hMenu_ConvertTXD_TXDGame, MF_STRING, 1653, CLocalizationManager::get()->getTranslatedFormattedTextW("Menu_Convert_TXD_To", CLocalizationManager::get()->getTranslatedFormattedText("PlatformedGame_Android_GTA").c_str()).c_str());
	AppendMenu(hMenu_ConvertTXD_TXDGame, MF_STRING, 1654, CLocalizationManager::get()->getTranslatedFormattedTextW("Menu_Convert_TXD_To", CLocalizationManager::get()->getTranslatedFormattedText("PlatformedGame_XBOX_GTA").c_str()).c_str());

	AppendMenu(hMenu_ConvertTXD, MF_STRING | MF_POPUP, (UINT_PTR)hMenu_ConvertTXD_TXDRWVersion, CLocalizationManager::get()->getTranslatedTextW("TXDRWVersion").c_str());
	i = 0;
	for (auto pRWVersion : CRWManager::get()->getVersionManager()->getEntries())
	{
		if (pRWVersion->getVersionType() != TYPE_MODEL)
		{
			continue;
		}

		string strString1 = CString2::escapeMenuText((pRWVersion->getVersionName() + " (" + CLocalizationManager::get()->getTranslatedText(pRWVersion->getLocalizationKey()) + ")").substr(0, 2)) + "&" + CString2::escapeMenuText((pRWVersion->getVersionName() + " (" + CLocalizationManager::get()->getTranslatedText(pRWVersion->getLocalizationKey()) + ")").substr(2));
		string strMenuText = CLocalizationManager::get()->getTranslatedFormattedText("Menu_Convert_TXD_To", strString1.c_str());
		AppendMenu(hMenu_ConvertTXD_TXDRWVersion, MF_STRING, 1660 + i, CString2::convertStdStringToStdWString(strMenuText).c_str());
		i++;
	}

	AppendMenu(hMenu_ConvertTXD, MF_STRING | MF_POPUP, (UINT_PTR)hMenu_ConvertTXD_TXDTextureFormat, CLocalizationManager::get()->getTranslatedTextW("Menu_Convert_TXD_RasterFormat").c_str());
	i = 0;
	for (auto pRasterDataFormat : CImageManager::get()->getRasterDataFormatManager()->getEntries())
	{
		AppendMenu(hMenu_ConvertTXD_TXDTextureFormat, MF_STRING, 2100 + i, CLocalizationManager::get()->getTranslatedFormattedTextW("Menu_Convert_TXD_To", pRasterDataFormat->getTextForMenu().c_str()).c_str());
		i++;
	}

	//AppendMenu(hMenu_ConvertTXD, MF_STRING | MF_POPUP, (UINT_PTR)hMenu_ConvertTXD_WTDFileFormat, CLocalizationManager::get()->getTranslatedTextW("Menu_Convert_WTDFileFormat").c_str());
	//AppendMenu(hMenu_ConvertTXD_WTDFileFormat, MF_STRING, 2500, CLocalizationManager::get()->getTranslatedTextW("Menu_Convert_WTD_TXD").c_str());

	AppendMenu(hMenu, MF_STRING, 1150, CLocalizationManager::get()->getTranslatedTextW("Menu_TextureList").c_str());
	AppendMenu(hMenu, MF_STRING, 1620, CLocalizationManager::get()->getTranslatedTextW("Menu_MissingTexture").c_str());

	// COL Entry
	AppendMenu(hMenu, MF_SEPARATOR, 1701, _T(""));

	AppendMenu(hMenu, MF_STRING | MF_POPUP, (UINT_PTR)hMenu_ConvertCOL, CLocalizationManager::get()->getTranslatedTextW("ConvertCollision").c_str());

	i = 0;
	for (auto pCOLVersion : CCOLManager::get()->getVersionManager()->getEntries())
	{
		AppendMenu(hMenu_ConvertCOL, MF_STRING, 2400 + i, CLocalizationManager::get()->getTranslatedFormattedTextW("Menu_Convert_COL_COL", pCOLVersion->getText().c_str()).c_str());
		i++;
	}

	AppendMenu(hMenu, MF_STRING, 1680, CLocalizationManager::get()->getTranslatedTextW("Menu_CenterCOLMeshes").c_str());

	// show menu
	SetForegroundWindow(getIMGF()->getDialog()->GetSafeHwnd());
	TrackPopupMenu(hMenu, TPM_LEFTALIGN | TPM_TOPALIGN | TPM_RIGHTBUTTON, xPos, yPos, 0, getIMGF()->getDialog()->GetSafeHwnd(), NULL);
	PostMessage(getIMGF()->getDialog()->GetSafeHwnd(), WM_NULL, 0, 0);

	// clean up
	//DestroyMenu(hMenu);
	*/
}

// controls
void		CIMGEditor::addControls(void)
{
	Vec2i
		point;
	Vec2u
		size;
	int32
		i, i2, x, y, w, h, w2, w3, h2, h3;
	uint32
		uiButtonHeight = 37;
	CColour
		borderColour(50, 50, 50);
	string
		strStyleGroup;

	// main editor component - IMG entry list
	x = 139 + 139;
	y = 162 + 30;
	w = m_pWindow->getSize().x - x;
	h = m_pWindow->getSize().y - y;
	strStyleGroup = "imgEditor_grid";

	m_pEntryGrid = addGrid(x, y, w, h, strStyleGroup, IMG_GRID);

	w -= m_pEntryGrid->getScrolls()->getScrollBarByOrientation(_2D_MIRRORED_ORIENTATION_VERTICAL)->getBackgroundBarSize().x;
	h -= m_pEntryGrid->getScrolls()->getScrollBarByOrientation(_2D_MIRRORED_ORIENTATION_HORIZONTAL)->getBackgroundBarSize().y;
	m_pEntryGrid->setSize(Vec2u(w, h));

	// filter - entry type
	w = 140;
	w2 = w;
	x = (m_pWindow->getSize().x - w) - w2;
	y = uiButtonHeight + 72;
	h = 32;
	strStyleGroup = "filter";

	m_pEntryTypeFilter = addDrop(x, y, w, h, "Entry Type", strStyleGroup + " firstItemHorizontally", -1, -50);
	m_pEntryTypeFilter->addItem("No file is open", false, false);

	// filter - entry version
	w = w2;
	x = m_pWindow->getSize().x - w;

	m_pEntryVersionFilter = addDrop(x, y, w, h, "Entry Version", strStyleGroup, -1, -50);
	m_pEntryVersionFilter->addItem("No file is open", false, false);

	// log
	x = 0;
	y = 508;
	w = 139 + 139;
	h = 120;

	m_pLog = addTextBox(x, y, w, h, "", true, "log");
	m_pLog->setReadOnly(true);
}

void		CIMGEditor::initControls(void)
{
	addColumnsToMainListView(IMG_UNKNOWN);

	CEventManager::get()->bindEvent(EVENT_onResizeWindow, [](void* pArg1, void* pArg2) {
		((CIMGEditor*)pArg1)->repositionAndResizeControls();
	}, this);

	repositionAndResizeControls();
}

void		CIMGEditor::repositionAndResizeControls(void)
{
	Vec2i point;
	Vec2u size, newSize;
	int32 iNewX, iNewY, iNewWidth, iNewHeight;

	// grid
	size = m_pEntryGrid->getSize();
	iNewWidth = m_pWindow->getSize().x - m_pEntryGrid->getPosition().x;
	iNewHeight = m_pWindow->getSize().y - m_pEntryGrid->getPosition().y;
	newSize = Vec2u(iNewWidth, iNewHeight);
	newSize.x -= m_pEntryGrid->getScrolls()->getScrollBarByOrientation(_2D_MIRRORED_ORIENTATION_VERTICAL)->getBackgroundBarSize().x;
	newSize.y -= m_pEntryGrid->getScrolls()->getScrollBarByOrientation(_2D_MIRRORED_ORIENTATION_HORIZONTAL)->getBackgroundBarSize().y;
	m_pEntryGrid->setSize(newSize);

	// filter - entry type
	point = m_pEntryTypeFilter->getPosition();
	iNewX = (m_pWindow->getSize().x - m_pEntryTypeFilter->getSize().x) - m_pEntryVersionFilter->getSize().x;
	m_pEntryTypeFilter->setPosition(Vec2i(iNewX, point.y));

	// filter - entry version
	point = m_pEntryVersionFilter->getPosition();
	iNewX = m_pWindow->getSize().x - m_pEntryVersionFilter->getSize().x;
	m_pEntryVersionFilter->setPosition(Vec2i(iNewX, point.y));
}

// render
void		CIMGEditor::render(void)
{
}