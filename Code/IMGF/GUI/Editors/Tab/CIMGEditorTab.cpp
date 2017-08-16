#pragma warning(disable : 4005)

#include "CIMGEditorTab.h"
#include "CIMGF.h"
#include "Globals.h"
#include "Type/String/CString2.h"
#include "Type/StdVector/CStdVector.h"
#include "Path/CPathManager.h"
#include "File/CFileManager.h"
#include "Format/RockstarGames/IMG/CIMGManager.h"
#include "Format/RockstarGames/IMG/CIMGFormat.h"
#include "Format/RockstarGames/IMG/CIMGEntry.h"
#include "Format/RenderWare/Helper/BinaryStream/CRWManager.h"
#include "Format/RenderWare/Helper/BinaryStream/CRWVersion.h"
#include "Format/RAGE/CRageManager.h"
#include "Tasks/Sort/CSortManager.h"
#include "Tasks/Sort/CSortPriority.h"
#include "Tasks/Sort/CSortType.h"
#include "Tasks/Sort/eSortType.h"
#include "Debug/CDebug.h"
#include "DB/CDBFormat.h"
#include "Format/RockstarGames/COL/CCOLManager.h"
#include "Tasks/Find/CSearchEntry.h"
#include "Format/RenderWare/Helper/BinaryStream/CRWVersionManager.h"
#include "Format/RockstarGames/COL/CCOLVersionManager.h"
#include "Format/RAGE/CRageResourceTypeManager.h"
#include "Localization/CLocalizationManager.h"
#include "Tasks/Sort/CSortPriorities.h"
#include "Platform/Hardware/CPlatformManager.h"
#include "Settings/CSettingsManager.h"
#include "Input/CInputManager.h"
#include "Input/CInputManager.h"
#include "DB/CDBManager.h"
#include "Tasks/RecentlyOpen/CRecentlyOpenManager.h"
#include "Controls/CGridControl.h"
#include "GUI/Editors/CIMGEditor.h"
#include "GUI/Popups/CPopupGUIManager.h"
#include "Task/CTaskManager.h"
#include "GUI/Windows/CMainWindow.h"
#include "GUI/Layers/CMainLayer.h"
#include "Controls/CTextControl.h"
#include "Controls/CTabBarControl.h"
#include "Controls/CTextBoxControl.h"
#include <algorithm>

using namespace std;
using namespace bxcf;

CIMGEditorTab::CIMGEditorTab(void) :
	m_pEditor(nullptr),
	m_pEntryGrid(nullptr),
	m_pLog(nullptr),
	m_bRestoringFilterOptions(false),
	m_bIMGModifiedSinceRebuild(false),
	m_uiOverwriteEntryOption(0)
{
}

// load/unload
void					CIMGEditorTab::unload(void)
{
	delete m_pDBFile;

	m_pIMGFile->unload();
	delete m_pIMGFile;
}

// initialization
void					CIMGEditorTab::init(void)
{
	//setFileInfoText();
	addAllEntriesToMainListView();

	m_pEntryGrid->setActiveItem();




	// add to recently open
	
	getIMGF()->getRecentlyOpenManager()->loadRecentlyOpenEntries();

	// update filename for open last
	getIMGF()->getActiveWindow()->setOpenLastFilename(CPathManager::getFileName(getIMGFile()->getFilePath()));

	// load corresponding DB file & protected entry states
	m_pDBFile = nullptr;
	string strDBFilePath = CPathManager::replaceFileExtension(getIMGFile()->getFilePath(), "db");
	if (CFileManager::doesFileExist(strDBFilePath))
	{
		m_pDBFile = CDBManager::get()->parseViaFile(strDBFilePath);

		if (m_pDBFile->doesHaveError())
		{
			m_pDBFile = nullptr;
		}
	}

	if (m_pDBFile == nullptr)
	{
		// either the db file doesn't exist or the db file is corrupt
		//pEditorTab->m_pDBFile = CDBManager::get()->createDBFileFromIMGFile(pEditorTab->getIMGFile());
		m_pDBFile = CDBManager::get()->createBlankDBFile();
	}
	loadProtectedEntryStates();

	// load filters - todo where is the other filter loading from?
	//loadFilter_Type();

	// check for unknown RW versions
	checkForUnknownRWVersionEntries();
}

// controls
void					CIMGEditorTab::addControls(void)
{
	/*
	m_pEntryGrid = m_pEditor->getEntryGrid()->clone();
	m_pEntryGrid->getLayer()->addControl();
	*/

	int32 x, y, w, h;

	// grid
	CGridControl *pBlankGrid = m_pEditor->getEntryGrid();

	x = 139 + 139;
	y = 162 + 30;
	w = m_pWindow->getSize().x - x;
	h = m_pWindow->getSize().y - y;

	m_pEntryGrid = addGrid(x, y, w, h);
	m_pEntryGrid->setStyleGroups(pBlankGrid->getStyleGroups());
	for (CGridControlHeader *pHeader : pBlankGrid->getHeaders().getEntries())
	{
		m_pEntryGrid->addHeader(pHeader->getText(), pHeader->getColumnWidth());
	}

	// log
	CTextBoxControl *pBlankLog = m_pEditor->m_pLog;

	x = pBlankLog->getPosition().x;
	y = pBlankLog->getPosition().y;
	w = pBlankLog->getSize().x;
	h = pBlankLog->getSize().y;

	m_pLog = addTextBox(x, y, w, h, "", true, "log");
	m_pLog->setReadOnly(true);
}

void					CIMGEditorTab::initControls(void)
{
	bindEvents();
}

void					CIMGEditorTab::removeControls(void)
{
	removeControl(m_pEntryGrid);
	m_pEntryGrid = nullptr;
}

// error checking
void					CIMGEditorTab::checkForUnknownRWVersionEntries(void)
{
	if (getIMGFile()->getVersion() == IMG_3)
	{
		return;
	}

	vector<CIMGEntry*> vecUnknownRWVersionEntries = getIMGFile()->getUnknownVersionEntries();
	if (vecUnknownRWVersionEntries.size() > 0)
	{
		vector<string> vecIMGEntryNames;
		for (auto pIMGEntry : vecUnknownRWVersionEntries)
		{
			vecIMGEntryNames.push_back(pIMGEntry->getEntryName());
		}

		getIMGF()->getTaskManager()->onTaskPause();
		getIMGF()->getPopupGUIManager()->showListViewDialog(
			CLocalizationManager::get()->getTranslatedText("UnknownVersions"),
			CLocalizationManager::get()->getTranslatedFormattedText("UnknownVersionsCheck", CPathManager::getFileName(getIMGFile()->getFilePath()).c_str(), vecUnknownRWVersionEntries.size()),
			CLocalizationManager::get()->getTranslatedText("Window_OrphanEntries_EntryName"),
			vecIMGEntryNames,
			CLocalizationManager::get()->getTranslatedFormattedText("SaveFilePopup_3_InitialFilename",
			CPathManager::replaceFileExtension(CPathManager::getFileName(getIMGFile()->getFilePath()), "TXT").c_str()),
			"UNKNOWNRWVERSIONS"
			);
		getIMGF()->getTaskManager()->onTaskUnpause();
	}
}

void					CIMGEditorTab::log(string strText, bool bExtendedModeOnly)
{
	//string strLogEntryWithTimestamp = "[" + CString2::getTimestampText() + "] " + strText;
	string strLogEntryWithTimestampAndIMG = "[" + CString2::getTimestampText() + "] [" + CPathManager::getFileName(m_pIMGFile->getFilePath()) + "] " + strText;

	if (bExtendedModeOnly)
	{
		m_vecLogLinesExtended.push_back(strLogEntryWithTimestampAndIMG);

		// automatic logging to file
		if (getIMGF()->getSettingsManager()->getSettingString("AutomaticLoggingPath") != "")
		{
			// extended file
			if (getIMGF()->getSettingsManager()->getSettingBool("AutomaticLoggingExtended"))
			{
				string strExtendedLogPath = CPathManager::addSlashToEnd(getIMGF()->getSettingsManager()->getSettingString("AutomaticLoggingPath"));
				strExtendedLogPath += CString2::getDateTextForFolder() + "/" + CLocalizationManager::get()->getTranslatedText("LogFilename_Extended");
				CFileManager::storeFile(strExtendedLogPath, strLogEntryWithTimestampAndIMG + "\n", true, false);
			}
		}
	}
	else
	{
		m_vecLogLinesGUI.push_back(strText);
		m_vecLogLinesBasic.push_back(strLogEntryWithTimestampAndIMG);
		m_vecLogLinesExtended.push_back(strLogEntryWithTimestampAndIMG);

		// automatic logging to file
		if (getIMGF()->getSettingsManager()->getSettingString("AutomaticLoggingPath") != "")
		{
			// basic file
			if (getIMGF()->getSettingsManager()->getSettingBool("AutomaticLoggingBasic"))
			{
				string strExtendedLogPath = CPathManager::addSlashToEnd(getIMGF()->getSettingsManager()->getSettingString("AutomaticLoggingPath"));
				strExtendedLogPath += CString2::getDateTextForFolder() + "/" + CLocalizationManager::get()->getTranslatedText("LogFilename_Basic");
				CFileManager::storeFile(strExtendedLogPath, strLogEntryWithTimestampAndIMG + "\n", true, false);
			}
			
			// extended file
			if (getIMGF()->getSettingsManager()->getSettingBool("AutomaticLoggingExtended"))
			{
				string strExtendedLogPath = CPathManager::addSlashToEnd(getIMGF()->getSettingsManager()->getSettingString("AutomaticLoggingPath"));
				strExtendedLogPath += CString2::getDateTextForFolder() + "/" + CLocalizationManager::get()->getTranslatedText("LogFilename_Extended");
				CFileManager::storeFile(strExtendedLogPath, strLogEntryWithTimestampAndIMG + "\n", true, false);
			}
		}
	}

	if (getIMGF()->getActiveTab() == this)
	{
		/*
		todo
		CEdit *pEdit = ((CEdit*)getIMGF()->getDialog()->GetDlgItem(14));
		pEdit->SetWindowTextW(CString2::convertStdStringToStdWString(CString2::join(m_vecLogLinesGUI, "\r\n")).c_str());
		pEdit->LineScroll(pEdit->GetLineCount());
		*/
	}
}

void					CIMGEditorTab::clearLogs(void)
{
	getLogLinesGUI().clear();
	getLogLinesBasic().clear();
	getLogLinesExtended().clear();

	/*
	todo
	CEdit *pEdit = ((CEdit*)getIMGF()->getDialog()->GetDlgItem(14));
	pEdit->SetWindowTextW(L"");
	pEdit->LineScroll(0);
	*/
}

void					CIMGEditorTab::checkToApplyCompression(CIMGEntry *pIMGEntry)
{
	if (getIMGF()->getSettingsManager()->getSettingBool("AutoCompressionImportReplace"))
	{
		if (getIMGFile()->getVersion() == IMG_FASTMAN92)
		{
			//eCompressionAlgorithm eCompressionAlgorithmValue = (eCompressionAlgorithm)getIMGF()->getSettingsManager()->getSettingInt("Fastman92IMGAutoCompressionType");
			if (getIMGFile()->getEntryCount() > 1) // > 1 instead of > 0, because the entry has already been added to the pool.
			{
				eCompressionAlgorithm eCompressionAlgorithmValue;

				// check to use compression type from first entry in IMG
				eCompressionAlgorithmValue = getIMGFile()->getEntryByIndex(0)->getCompressionAlgorithmId();
				
				// if compression type is not compressed (none) or unknown, default to ZLIB compression
				if (eCompressionAlgorithmValue == COMPRESSION_NONE || eCompressionAlgorithmValue == COMPRESSION_UNKNOWN)
				{
					eCompressionAlgorithmValue = COMPRESSION_ZLIB;
				}

				// apply the compression to the IMG entry
				pIMGEntry->applyCompression(eCompressionAlgorithmValue);
			}
		}
	}
}
void					CIMGEditorTab::addEntryViaFile(string strEntryFilePath, string strEntryName)
{
	CIMGEntry *pIMGEntry = getIMGFile()->addEntryViaFile(strEntryFilePath, strEntryName);
	checkToApplyCompression(pIMGEntry);
	addEntryToMainListView(pIMGEntry);
	updateEntryCountText();
	updateIMGText();
}
void					CIMGEditorTab::addEntryViaData(string strEntryName, string strEntryData)
{
	CIMGEntry *pIMGEntry = getIMGFile()->addEntryViaData(strEntryName, strEntryData);
	checkToApplyCompression(pIMGEntry);
	addEntryToMainListView(pIMGEntry);
	updateEntryCountText();
	updateIMGText();
}
void					CIMGEditorTab::replaceEntryViaFile(string strEntryName, string strEntryFilePath, string strNewEntryName)
{
	CIMGEntry *pIMGEntry = getIMGFile()->replaceEntryViaFile(strEntryName, strEntryFilePath, strNewEntryName);
	checkToApplyCompression(pIMGEntry);
	updateEntryInMainListView(pIMGEntry);
	updateIMGText();
}
void					CIMGEditorTab::replaceEntryViaData(string strEntryName, string& strEntryData, string strNewEntryName)
{
	CIMGEntry *pIMGEntry = getIMGFile()->replaceEntryViaData(strEntryName, strEntryData, strNewEntryName);
	checkToApplyCompression(pIMGEntry);
	updateEntryInMainListView(pIMGEntry);
	updateIMGText();
}
void					CIMGEditorTab::addOrReplaceEntryViaFile(string strEntryFilePath, string strEntryName)
{
	uint32 uiIMGEntryCount = getIMGFile()->getEntryCount();
	CIMGEntry *pIMGEntry = getIMGFile()->addOrReplaceEntryViaFile(strEntryFilePath, strEntryName);
	checkToApplyCompression(pIMGEntry);
	if (uiIMGEntryCount == getIMGFile()->getEntryCount())
	{
		// entry was replaced
		updateEntryInMainListView(pIMGEntry);
	}
	else
	{
		// entry was added
		addEntryToMainListView(pIMGEntry);
		updateEntryCountText();
	}
	updateIMGText();
}
void					CIMGEditorTab::addOrReplaceEntryViaData(string strEntryName, string strEntryData)
{
	uint32 uiIMGEntryCount = getIMGFile()->getEntryCount();
	CIMGEntry *pIMGEntry = getIMGFile()->addOrReplaceEntryViaData(strEntryName, strEntryData);
	checkToApplyCompression(pIMGEntry);
	if (uiIMGEntryCount == getIMGFile()->getEntryCount())
	{
		// entry was replaced
		updateEntryInMainListView(pIMGEntry);
	}
	else
	{
		// entry was added
		addEntryToMainListView(pIMGEntry);
		updateEntryCountText();
	}
	updateIMGText();
}
void					CIMGEditorTab::addOrReplaceEntryViaFileAndSettings(string strEntryFilePath, string strEntryName)
{
	if (strEntryName == "")
	{
		strEntryName = CPathManager::getFileName(strEntryFilePath);
	}

	CIMGEntry *pIMGEntry = getIMGFile()->getEntryByName(strEntryName);
	if (pIMGEntry == nullptr)
	{
		// entry name not found in IMG
		// import the entry
		return addEntryViaFile(strEntryFilePath, strEntryName);
	}

	// entry name is found in IMG
	if (getIMGF()->getSettingsManager()->getSettingBool("AskBeforeOverwritingFiles"))
	{
		// Setting is enabled: Ask before overwriting files

		// show popup - ask to replace or import
		uint32 uiResultOption;
		if (isOverwriteEntryOptionSet())
		{
			uiResultOption = getOverwriteEntryOption();
		}
		else
		{
			COverwriteEntryDialogData *pOverwriteEntryDialogData = getIMGF()->getPopupGUIManager()->showOverwriteEntryDialog();
			if (pOverwriteEntryDialogData->m_bCancel)
			{
				// cancel
				delete pOverwriteEntryDialogData;
				return;
			}

			setOverwriteEntryOption(pOverwriteEntryDialogData->m_uiResultOption);
			uiResultOption = pOverwriteEntryDialogData->m_uiResultOption;

			delete pOverwriteEntryDialogData;
		}

		if (uiResultOption == 0) // import
		{
			return addEntryViaFile(strEntryFilePath, strEntryName);
		}
		else if (uiResultOption == 1) // replace
		{
			return replaceEntryViaFile(strEntryName, strEntryFilePath);
		}
	}

	if (pIMGEntry->isProtectedEntry())
	{
		// entry is protected

		if (getIMGF()->getSettingsManager()->getSettingBool("OverwriteProtectedFiles"))
		{
			// Setting is enabled: Overwrite protected files
			return replaceEntryViaFile(strEntryName, strEntryFilePath);
		}
		else
		{
			// Setting is disabled: Overwrite protected files
			// do nothing, don't replace the file
			return;
		}
	}

	uint32
		uiExistingEntryFileCreationDate = pIMGEntry->getFileCreationDate(),
		uiNewEntryFileCreationDate = CFileManager::getFileCreationDate(strEntryFilePath);

	if (uiExistingEntryFileCreationDate == 0 || uiNewEntryFileCreationDate == 0)
	{
		// either the file creation date is not stored for the existing entry or unable to fetch it for the new entry
		return replaceEntryViaFile(strEntryName, strEntryFilePath);
	}

	if (uiNewEntryFileCreationDate == uiExistingEntryFileCreationDate)
	{
		// file creation date is the same for both existing entry and new entry
		return replaceEntryViaFile(strEntryName, strEntryFilePath);
	}

	if (uiExistingEntryFileCreationDate < uiNewEntryFileCreationDate)
	{
		// the existing entry is older than the new entry

		if (getIMGF()->getSettingsManager()->getSettingBool("OverwriteOlderFiles"))
		{
			// Setting is enabled: Overwrite older files
			return replaceEntryViaFile(strEntryName, strEntryFilePath);
		}
		else
		{
			// Setting is disabled: Overwrite older files
			// do nothing, don't replace the file
			return;
		}
	}
	else if (uiExistingEntryFileCreationDate > uiNewEntryFileCreationDate)
	{
		// the existing entry is newer than the new entry

		if (getIMGF()->getSettingsManager()->getSettingBool("OverwriteNewerFiles"))
		{
			// Setting is enabled: Overwrite newer files
			return replaceEntryViaFile(strEntryName, strEntryFilePath);
		}
		else
		{
			// Setting is disabled: Overwrite newer files
			// do nothing, don't replace the file
			return;
		}
	}

	// replace by default. e.g. if no settings are enabled.
	return replaceEntryViaFile(strEntryName, strEntryFilePath);
}
void					CIMGEditorTab::addOrReplaceEntryViaDataAndSettings(string strEntryName, string strEntryData)
{
	CIMGEntry *pIMGEntry = getIMGFile()->getEntryByName(strEntryName);
	if (pIMGEntry == nullptr)
	{
		// entry name not found in IMG
		// import the entry
		return addEntryViaData(strEntryName, strEntryData);
	}

	// entry name is found in IMG
	if (getIMGF()->getSettingsManager()->getSettingBool("AskBeforeOverwritingFiles"))
	{
		// Setting is enabled: Ask before overwriting files

		// show popup - ask to replace or import
		COverwriteEntryDialogData *pOverwriteEntryDialogData = getIMGF()->getPopupGUIManager()->showOverwriteEntryDialog();
		if (pOverwriteEntryDialogData->m_bCancel)
		{
			// cancel
			delete pOverwriteEntryDialogData;
			return;
		}
		if (pOverwriteEntryDialogData->m_uiResultOption == 0) // import
		{
			delete pOverwriteEntryDialogData;
			return addEntryViaData(strEntryName, strEntryData);
		}
		else if (pOverwriteEntryDialogData->m_uiResultOption == 1) // replace
		{
			delete pOverwriteEntryDialogData;
			return replaceEntryViaData(strEntryName, strEntryData);
		}

		delete pOverwriteEntryDialogData;
	}

	if (pIMGEntry->isProtectedEntry())
	{
		// entry is protected

		if (getIMGF()->getSettingsManager()->getSettingBool("OverwriteProtectedFiles"))
		{
			// Setting is enabled: Overwrite protected files
			return replaceEntryViaData(strEntryName, strEntryData);
		}
		else
		{
			// Setting is disabled: Overwrite protected files
			// do nothing, don't replace the file
			return;
		}
	}
	
	return replaceEntryViaData(strEntryName, strEntryData);
}
void					CIMGEditorTab::removeEntry(CIMGEntry *pIMGEntry)
{
	getIMGFile()->removeEntry(pIMGEntry);
	updateEntryCountText();
	updateIMGText();
}

void					CIMGEditorTab::addColumnsToMainListView(void)
{
	getIMGF()->getIMGEditor()->addColumnsToMainListView(getIMGFile()->getVersion());
}
void					CIMGEditorTab::readdAllEntriesToMainListView(void)
{
	m_pEntryGrid->removeAllEntries();
	
	m_pEditor->setSelectedEntryCount(0);
	m_pEditor->updateSelectedEntryCountText();

	addAllEntriesToMainListView();

	m_pEntryGrid->getWindow()->markToRedraw();
}
void					CIMGEditorTab::addAllEntriesToMainListView(void)
{
	//getIMGF()->getTaskManager()->setTaskMaxProgressTickCount(getIMGFile()->m_vecEntries.size());
	// setProgressMaxTicks() is called in CIMGF::addMainWindowTab(). (as the bottom of this code contains a call to onProgressTick()).

	/*
	todo

	int iCurSel;
	::CString strText1;

	iCurSel = ((CComboBox*)getIMGF()->getDialog()->GetDlgItem(54))->GetCurSel();
	bool bFilterCheckBox_Extensions = iCurSel != 0;
	uint32 uiFilterCombo_Extensions = iCurSel;
	
	CComboBox *pComboBox1 = ((CComboBox*)getIMGF()->getDialog()->GetDlgItem(5));
	iCurSel = pComboBox1->GetCurSel();
	bool bFilterCheckBox_Version = iCurSel != 0;
	uint32 uiFilterCombo_Version = iCurSel;
	*/

	for (auto pIMGEntry : getIMGFile()->getEntries())
	{
		bool bAddEntry = true;

		// RW version
		/*
		todo

		string strEntryExtensionUpper = CString2::toUpperCase(CPathManager::getFileExtension(pIMGEntry->getEntryName()));
		if (bFilterCheckBox_Version)
		{
			if (uiFilterCombo_Version == getIMGF()->m_iFilterMapping_UnknownVersion) // Unknown Version
			{
				if (strEntryExtensionUpper == "COL")
				{
					eCOLVersion eEntryVersion = pIMGEntry->getCOLVersion() == nullptr ? COL_UNKNOWN : pIMGEntry->getCOLVersion()->getVersionId();
					if (eEntryVersion == COL_UNKNOWN)
					{
						// add the entry
					}
					else
					{
						// don't add the entry
						bAddEntry = false;
					}
				}
				else if (strEntryExtensionUpper == "DFF" || strEntryExtensionUpper == "TXD")
				{
					if (pIMGEntry->getRWVersion() == nullptr)
					{
						// add the entry
					}
					else
					{
						// don't add the entry
						bAddEntry = false;
					}
				}
				else if (strEntryExtensionUpper == "IPL")
				{
					// don't add the entry
					bAddEntry = false;
				}
				else
				{
					// add the entry
				}
			}
			else if (getIMGF()->m_umapFilterMapping_COLVersion.count(uiFilterCombo_Version) > 0)
			{
				eCOLVersion eStoredVersion = getIMGF()->m_umapFilterMapping_COLVersion[uiFilterCombo_Version];
				eCOLVersion eEntryVersion = pIMGEntry->getCOLVersion() == nullptr ? COL_UNKNOWN : pIMGEntry->getCOLVersion()->getVersionId();

				if (strEntryExtensionUpper != "COL" || eEntryVersion != eStoredVersion)
				{
					bAddEntry = false;
				}
			}
			else if (getIMGF()->m_umapFilterMapping_RWVersion.count(uiFilterCombo_Version) > 0)
			{
				eRWVersion eVersion = getIMGF()->m_umapFilterMapping_RWVersion[uiFilterCombo_Version];
				if (strEntryExtensionUpper == "DFF" || strEntryExtensionUpper == "TXD")
				{
					if (pIMGEntry->getRWVersion() == nullptr)
					{
						bAddEntry = false;
					}
					else if (pIMGEntry->getRWVersion()->getVersionId() == eVersion)
					{
						// add the entry
					}
					else
					{
						bAddEntry = false;
					}
				}
				else
				{
					bAddEntry = false;
				}
			}
		}

		// extensions
		if (bFilterCheckBox_Extensions)
		{
			vector<string> vecExtensions;
			
			// dropdown
			::CString cstrExtensionText;
			if (uiFilterCombo_Extensions != -1)
			{
				((CComboBox*)getIMGF()->getDialog()->GetDlgItem(54))->GetLBText(uiFilterCombo_Extensions, cstrExtensionText);
				vecExtensions.push_back(CString2::convertCStringToStdString(cstrExtensionText));
			}

			// test for a match
			if (std::find(vecExtensions.begin(), vecExtensions.end(), strEntryExtensionUpper) == vecExtensions.end())
			{
				bAddEntry = false;
			}
		}
		*/

		if (bAddEntry)
		{
			addEntryToMainListView(pIMGEntry);
		}

		getIMGF()->getTaskManager()->onTaskProgressTick();
	}

	// todo
	//updateEntryCountText();
	//updateIMGText();
}
void					CIMGEditorTab::addEntryToMainListView(CIMGEntry *pIMGEntry)
{
	CGridControlEntry *pRow = new CGridControlEntry;

	pRow->setGrid(m_pEntryGrid);

	uint32 uiEntryIndex = m_pEntryGrid->getEntryCount();
	string strExtensionUpper = CString2::toUpperCase(CPathManager::getFileExtension(pIMGEntry->getEntryName()));
	bool bFastman92IMGFormat = pIMGEntry->getIMGFile()->getVersion() == IMG_FASTMAN92;

	vector<string> vecText;
	vecText.resize(bFastman92IMGFormat ? 8 : 6);
	vecText[0] = CString2::addNumberGrouping(CString2::toString(uiEntryIndex + 1));
	vecText[1] = strExtensionUpper;
	vecText[2] = pIMGEntry->getEntryName();
	vecText[3] = CString2::addNumberGrouping(CString2::toString(pIMGEntry->getEntryOffset()));
	vecText[4] = CString2::addNumberGrouping(CString2::toString(pIMGEntry->getEntrySize()));
	vecText[5] = "a";// pIMGEntry->getVersionText();
	if (bFastman92IMGFormat)
	{
		vecText[6] = CIMGManager::getCompressionTypeText(pIMGEntry->getCompressionAlgorithmId());
		vecText[7] = CIMGManager::getEncryptionText(pIMGEntry->isEncrypted());
	}

	pRow->getText().push_back(vecText);
	m_pEntryGrid->addEntry(pRow);

	/*
	todo
	uint32 uiEntryIndex = getListView()->GetItemCount();
	string strExtensionUpper = CString2::toUpperCase(CPathManager::getFileExtension(pIMGEntry->getEntryName()));
	getListView()->InsertItem(LVIF_TEXT | LVIF_PARAM, uiEntryIndex, CString2::convertStdStringToStdWString(CString2::addNumberGrouping(CString2::toString(uiEntryIndex + 1))).c_str(), 0, 0, 0, (DWORD)pIMGEntry);
	getListView()->SetItem(uiEntryIndex, 1, LVIF_TEXT, CString2::convertStdStringToStdWString(strExtensionUpper).c_str(), 0, 0, 0, 0);
	getListView()->SetItem(uiEntryIndex, 2, LVIF_TEXT, CString2::convertStdStringToStdWString(pIMGEntry->getEntryName()).c_str(), 0, 0, 0, 0);
	getListView()->SetItem(uiEntryIndex, 3, LVIF_TEXT, CString2::convertStdStringToStdWString(CString2::addNumberGrouping(CString2::toString(pIMGEntry->getEntryOffset()))).c_str(), 0, 0, 0, 0);
	getListView()->SetItem(uiEntryIndex, 4, LVIF_TEXT, CString2::convertStdStringToStdWString(CString2::addNumberGrouping(CString2::toString(pIMGEntry->getEntrySize()))).c_str(), 0, 0, 0, 0);
	getIMGF()->getIMGEditor()->applyVersionAndResourceTypeColumn(uiEntryIndex, getIMGF()->getEntryListTab()->getIMGFile(), pIMGEntry);
	if (pIMGEntry->getIMGFile()->getVersion() == IMG_FASTMAN92)
	{
		getListView()->SetItem(uiEntryIndex, 6, LVIF_TEXT, CString2::convertStdStringToStdWString(CIMGManager::getCompressionTypeText(pIMGEntry->getCompressionAlgorithmId())).c_str(), 0, 0, 0, 0);
		getListView()->SetItem(uiEntryIndex, 7, LVIF_TEXT, CString2::convertStdStringToStdWString(CIMGManager::getEncryptionText(pIMGEntry->isEncrypted())).c_str(), 0, 0, 0, 0);
	}
	*/
}
void					CIMGEditorTab::updateEntryInMainListView(CIMGEntry *pIMGEntry)
{
	/*
	todo
	uint32 uiEntryIndex = getMainListViewItemIndexByItemData(pIMGEntry);
	if (uiEntryIndex == -1)
	{
		// IMG entry is not currently displayed, e.g. filter.
		return;
	}
	string strExtensionUpper = CString2::toUpperCase(CPathManager::getFileExtension(pIMGEntry->getEntryName()));
	getListView()->SetItem(uiEntryIndex, 0, LVIF_TEXT, CString2::convertStdStringToStdWString(CString2::addNumberGrouping(CString2::toString(uiEntryIndex + 1))).c_str(), 0, 0, 0, 0);
	getListView()->SetItem(uiEntryIndex, 1, LVIF_TEXT, CString2::convertStdStringToStdWString(strExtensionUpper).c_str(), 0, 0, 0, 0);
	getListView()->SetItem(uiEntryIndex, 2, LVIF_TEXT, CString2::convertStdStringToStdWString(pIMGEntry->getEntryName()).c_str(), 0, 0, 0, 0);
	getListView()->SetItem(uiEntryIndex, 3, LVIF_TEXT, CString2::convertStdStringToStdWString(CString2::addNumberGrouping(CString2::toString(pIMGEntry->getEntryOffset()))).c_str(), 0, 0, 0, 0);
	getListView()->SetItem(uiEntryIndex, 4, LVIF_TEXT, CString2::convertStdStringToStdWString(CString2::addNumberGrouping(CString2::toString(pIMGEntry->getEntrySize()))).c_str(), 0, 0, 0, 0);
	//getIMGF()->getIMGEditor()->applyVersionAndResourceTypeColumn(uiEntryIndex, getIMGF()->getEntryListTab()->getIMGFile(), pIMGEntry);
	if (pIMGEntry->getIMGFile()->getVersion() == IMG_FASTMAN92)
	{
		getListView()->SetItem(uiEntryIndex, 6, LVIF_TEXT, CString2::convertStdStringToStdWString(CIMGManager::getCompressionTypeText(pIMGEntry->getCompressionAlgorithmId())).c_str(), 0, 0, 0, 0);
		getListView()->SetItem(uiEntryIndex, 7, LVIF_TEXT, CString2::convertStdStringToStdWString(CIMGManager::getEncryptionText(pIMGEntry->isEncrypted())).c_str(), 0, 0, 0, 0);
	}
	*/
}
uint32			CIMGEditorTab::getMainListViewItemIndexByItemData(CIMGEntry *pIMGEntry)
{
	/*
	todo
	for (uint32 i = 0, j = getListView()->GetItemCount(); i < j; i++)
	{
		if ((CIMGEntry*)getListView()->GetItemData(i) == pIMGEntry)
		{
			return i;
		}
	}
	*/
	return -1;
}

void					CIMGEditorTab::updateEntryCountText(void)
{
	/*
	todo
	uint32
		uiFilteredEntryCount = getListView()->GetItemCount(),
		uiEntryCount = getIMGFile()->getEntryCount();
	if (isFilterActive())
	{
		((CStatic*)getIMGF()->getDialog()->GetDlgItem(20))->SetWindowTextW(CLocalizationManager::get()->getTranslatedFormattedTextW("Window_Main_Text_FilteredEntryCount", uiFilteredEntryCount, uiEntryCount).c_str());
	}
	else
	{
		((CStatic*)getIMGF()->getDialog()->GetDlgItem(20))->SetWindowTextW(CLocalizationManager::get()->getTranslatedFormattedTextW("Window_Main_Text_EntryCount", uiEntryCount).c_str());
	}
	*/
}
void					CIMGEditorTab::updateIMGText(void)
{
	/*
	todo
	string strPlatformName = CPlatformManager::get()->getPlatformName(getIMGFile()->getPlatform());

	if (getIMGFile()->getVersion() == IMG_FASTMAN92)
	{
		uint32 uiEntryCount = getIMGFile()->getEntryCount();
		uint32 uiUncompressedEntryCount = getIMGFile()->getEntryCountForCompressionType(COMPRESSION_NONE);
		string strVersionSuffix = "";
		if (uiEntryCount == uiUncompressedEntryCount)
		{
			strVersionSuffix = CLocalizationManager::get()->getTranslatedText("CompressionValue_Uncompressed");
		}
		else if (uiUncompressedEntryCount == 0)
		{
			strVersionSuffix = CLocalizationManager::get()->getTranslatedText("CompressionValue_Compressed");
		}
		else
		{
			strVersionSuffix = CLocalizationManager::get()->getTranslatedText("CompressionValue_PartiallyCompressed");
		}
		((CStatic*)getIMGF()->getDialog()->GetDlgItem(19))->SetWindowTextW(CLocalizationManager::get()->getTranslatedFormattedTextW("IMGVersion", CIMGManager::getVersionName(IMG_FASTMAN92, getIMGFile()->isEncrypted()).c_str(), strPlatformName.c_str(), strVersionSuffix.c_str()).c_str());
	}
	else
	{
		((CStatic*)getIMGF()->getDialog()->GetDlgItem(19))->SetWindowTextW(CLocalizationManager::get()->getTranslatedFormattedTextW("IMGVersion", CIMGManager::getVersionName(getIMGFile()->getVersion(), getIMGFile()->isEncrypted()).c_str(), strPlatformName.c_str(), CIMGManager::getVersionGames(getIMGFile()->getVersion()).c_str()).c_str());
	}
	*/
}
CIMGEntry*				CIMGEditorTab::getEntryByName(string strEntryName)
{
	for (auto pIMGEntry : getIMGFile()->getEntries())
	{
		if (strEntryName == pIMGEntry->getEntryName())
		{
			return pIMGEntry;
		}
	}
	return nullptr;
}

void					CIMGEditorTab::rebuild(string strIMGPath, bool bLog)
{
	getIMGF()->getTaskManager()->setTaskMaxProgressTickCount(getIMGFile()->getEntryCount() * 3);
	getIMGFile()->serializeViaFile(strIMGPath == "" ? getIMGFile()->getFilePath() : strIMGPath);
	setIMGModifiedSinceRebuild(false);
	if (bLog)
	{
		log(CLocalizationManager::get()->getTranslatedText("Log_127"));
	}
}
uint32			CIMGEditorTab::merge(string strPath, vector<string>& vecImportedEntryNames)
{
	return getIMGFile()->merge(strPath, vecImportedEntryNames);
}
void					CIMGEditorTab::splitSelectedEntries(string strPath, eIMGVersion eIMGVersion, bool bDeleteFromSource, vector<string>& vecSplitEntryNames)
{
	/*
	todo
	vector<CIMGEntry*> vecIMGEntries;
	CListCtrl *pListControl = ((CListCtrl*)getIMGF()->getDialog()->GetDlgItem(37));
	POSITION pos = pListControl->GetFirstSelectedItemPosition();
	CIMGEntry *pIMGEntry = nullptr;
	if (pos == NULL)
	{
		return;
	}

	getIMGF()->getTaskManager()->setTaskMaxProgressTickCount(pListControl->GetSelectedCount() * (bDeleteFromSource ? 2 : 1));

	while (pos)
	{
		int nItem = pListControl->GetNextSelectedItem(pos);
		pIMGEntry = (CIMGEntry*)pListControl->GetItemData(nItem);
		vecIMGEntries.push_back(pIMGEntry);
		vecSplitEntryNames.push_back(pIMGEntry->getEntryName());

		if (bDeleteFromSource)
		{
			pListControl->DeleteItem(nItem);

			pos = pListControl->GetFirstSelectedItemPosition();
		}

		getIMGF()->getTaskManager()->onTaskProgressTick();
	}

	getIMGFile()->split(vecIMGEntries, strPath, eIMGVersion);

	if (bDeleteFromSource)
	{
		for (auto pIMGEntry : vecIMGEntries)
		{
			removeEntry(pIMGEntry);

			getIMGF()->getTaskManager()->onTaskProgressTick();
		}
	}

	log(CLocalizationManager::get()->getTranslatedFormattedText("Log_128", vecIMGEntries.size(), CPathManager::getFileName(strPath).c_str()));
	*/
}
void					CIMGEditorTab::replace(vector<string>& vecPaths, vector<string>& vecReplacedEntryNames)
{
	vector<CIMGEntry*> vecReplacedEntries;
	uint32 uiReplaceCount = getIMGFile()->replaceEntries(vecPaths, vecReplacedEntryNames, vecReplacedEntries);

	for (auto pIMGEntry : vecReplacedEntries)
	{
		getIMGF()->getEntryListTab()->onEntryChange(pIMGEntry);
	}
}
bool					sortStdVectorAzCaseInsensitive(CSearchEntry *pSearchEntry1, CSearchEntry *pSearchEntry2)
{
	return strcmp(pSearchEntry1->getIMGEntry()->getEntryName().c_str(), pSearchEntry2->getIMGEntry()->getEntryName().c_str()) < 0;
}
void					CIMGEditorTab::searchText(void)
{
	/*
	todo

	CListCtrl
		*pListControl = (CListCtrl*)getIMGF()->getDialog()->GetDlgItem(22),
		*pListControlMain = (CListCtrl*)getIMGF()->getDialog()->GetDlgItem(37);
	pListControl->DeleteAllItems();
	for (auto pSearchEntry : getIMGF()->getIMGEditor()->getSearchEntries())
	{
		delete pSearchEntry;
	}
	getIMGF()->getIMGEditor()->getSearchEntries().clear();

	string strSearchText = CString2::toUpperCase(m_strSearchText);
	bool bAllTabs = ((CButton*)getIMGF()->getDialog()->GetDlgItem(46))->GetCheck() == BST_CHECKED;

	if (strSearchText == "")
	{
		((CStatic*)getIMGF()->getDialog()->GetDlgItem(0))->SetWindowTextW(CLocalizationManager::get()->getTranslatedFormattedTextW("Window_Main_Text_SearchResult_ActiveTab", 0).c_str());
		return;
	}

	vector<CEditorTab*> vecEditorTabs;
	uint32 uiTotalEntryCount;
	if (bAllTabs)
	{
		vecEditorTabs = getIMGF()->getIMGEditor()->getEntries();
		uiTotalEntryCount = getIMGF()->getIMGEditor()->getEntryCountForAllTabs();
	}
	else
	{
		vecEditorTabs.push_back(this);
		uiTotalEntryCount = getIMGFile()->getEntryCount();
	}
	getIMGF()->getTaskManager()->setTaskMaxProgressTickCount(uiTotalEntryCount);

	uint32
		uiMatchCount = 0,
		uiFileCountWithMatches = 0;
	for (auto pEditorTab : vecEditorTabs)
	{
		bool bMatchFoundInFile = false;
		uint32 i = 0;
		for (auto pIMGEntry : ((CIMGEditorTab*)pEditorTab)->getIMGFile()->getEntries())
		{
			string strEntryExtension = CString2::toUpperCase(CPathManager::getFileExtension(pIMGEntry->getEntryName()));
			bool bMatch = false;
			if (CString2::toUpperCase(pIMGEntry->getEntryName()).find(strSearchText) != string::npos)
			{
				bMatch = true;
			}
			else if (CString2::toString(pIMGEntry->getEntryOffsetInSectors() * 2048).find(strSearchText) != string::npos)
			{
				bMatch = true;
			}
			else if (CString2::toString(pIMGEntry->getEntrySize()).find(strSearchText) != string::npos)
			{
				bMatch = true;
			}
			else
			{
				if (strEntryExtension == "COL")
				{
					if (CString2::toUpperCase(CCOLManager::get()->getCOLVersionText(pIMGEntry->getCOLVersion())).find(strSearchText) != string::npos)
					{
						bMatch = true;
					}
				}
				else if (strEntryExtension == "TXD" || CPathManager::isModelExtension(strEntryExtension))
				{
					if (pIMGEntry->getRWVersion() == nullptr)
					{
						string strText1 = "Unknown";
						if (CString2::toUpperCase(strText1).find(strSearchText) != string::npos)
						{
							bMatch = true;
						}
					}
					else
					{
						if (CString2::toUpperCase(pIMGEntry->getRWVersion()->getVersionName() + " (" + CLocalizationManager::get()->getTranslatedText(pIMGEntry->getRWVersion()->getLocalizationKey()) + ")").find(strSearchText) != string::npos)
						{
							bMatch = true;
						}
					}
				}
			}

			if (bMatch)
			{
				pListControlMain->SetItemState(i, LVIS_SELECTED, LVIS_SELECTED);
				pListControlMain->SetSelectionMark(i);

				CSearchEntry *pSearchEntry = new CSearchEntry;
				pSearchEntry->setWindowTab((CIMGEditorTab*)pEditorTab);
				pSearchEntry->setIMGEntry(pIMGEntry);
				getIMGF()->getIMGEditor()->getSearchEntries().push_back(pSearchEntry);

				uiMatchCount++;
				bMatchFoundInFile = true;
			}
			else
			{
				pListControlMain->SetItemState(i, ~LVIS_SELECTED, LVIS_SELECTED);
			}
			i++;

			getIMGF()->getTaskManager()->onTaskProgressTick();
		}

		if (bMatchFoundInFile)
		{
			uiFileCountWithMatches++;
		}
	}

	// sort search results list view by entry name A-Z case-insensitive
	std::sort(getIMGF()->getIMGEditor()->getSearchEntries().begin(), getIMGF()->getIMGEditor()->getSearchEntries().end(), sortStdVectorAzCaseInsensitive);

	// add all entries to search results list view
	for (auto pSearchEntry : getIMGF()->getIMGEditor()->getSearchEntries())
	{
		CIMGEntry *pIMGEntry = pSearchEntry->getIMGEntry();
		uint32 uiRowIndex = pListControl->GetItemCount();
		string strEntryExtension = CString2::toUpperCase(CPathManager::getFileExtension(pIMGEntry->getEntryName()));
		string strExtraInfo;
		if (strEntryExtension == "COL")
		{
			strExtraInfo = CCOLManager::getCOLVersionText(pIMGEntry->getCOLVersion());
		}
		else if (strEntryExtension == "TXD" || CPathManager::isModelExtension(strEntryExtension))
		{
			strExtraInfo = pIMGEntry->getRWVersion() == nullptr ? CLocalizationManager::get()->getTranslatedText("Window_Main_Combo_RWVersion_Unknown") : pIMGEntry->getRWVersion()->getVersionName() + " (" + CLocalizationManager::get()->getTranslatedText(pIMGEntry->getRWVersion()->getLocalizationKey()) + ")";
		}
		pListControl->InsertItem(LVIF_TEXT | LVIF_PARAM, uiRowIndex, CString2::convertStdStringToStdWString(pIMGEntry->getEntryName()).c_str(), 0, 0, 0, (DWORD)pSearchEntry);
		pListControl->SetItem(uiRowIndex, 1, LVIF_TEXT, CString2::convertStdStringToStdWString(CPathManager::getFileName(pSearchEntry->getWindowTab()->getIMGFile()->getFilePath())).c_str(), 0, 0, 0, 0);
		pListControl->SetItem(uiRowIndex, 2, LVIF_TEXT, CString2::convertStdStringToStdWString(strExtraInfo).c_str(), 0, 0, 0, 0);
	}

	// result text
	wstring wstrSearchResultText;
	if (bAllTabs)
	{
		wstrSearchResultText = CLocalizationManager::get()->getTranslatedFormattedTextW("Window_Main_Text_SearchResult_AllTabs", uiMatchCount, uiFileCountWithMatches);
	}
	else
	{
		wstrSearchResultText = CLocalizationManager::get()->getTranslatedFormattedTextW("Window_Main_Text_SearchResult_ActiveTab", uiMatchCount);
	}

	((CStatic*)getIMGF()->getDialog()->GetDlgItem(0))->SetWindowTextW(wstrSearchResultText.c_str());
	pListControlMain->SetFocus();

	getIMGF()->getIMGEditor()->setSearchHitCount(uiMatchCount);
	getIMGF()->getIMGEditor()->setSearchFileCount(uiFileCountWithMatches);
	*/
}

void					CIMGEditorTab::storeFilterOptions(void)
{
	/*
	todo
	CComboBox *pComboBox1 = (CComboBox*)getIMGF()->getDialog()->GetDlgItem(54);
	CComboBox *pComboBox2 = (CComboBox*)getIMGF()->getDialog()->GetDlgItem(5);
	::CString cstr1, cstr2;
	pComboBox1->GetWindowTextW(cstr1);
	pComboBox2->GetWindowTextW(cstr2);
	setActiveFilter("type", CString2::convertCStringToStdString(cstr1));
	setActiveFilter("version", CString2::convertCStringToStdString(cstr2));
	*/
}
void					CIMGEditorTab::restoreFilterOptions(void)
{
	/*
	todo
	m_bRestoringFilterOptions = true;
	((CButton*)getIMGF()->getDialog()->GetDlgItem(44))->SetCheck(m_filterOptions.m_bCheckboxes[0] ? BST_CHECKED : BST_UNCHECKED);
	((CButton*)getIMGF()->getDialog()->GetDlgItem(3))->SetCheck(m_filterOptions.m_bCheckboxes[1] ? BST_CHECKED : BST_UNCHECKED);
	((CButton*)getIMGF()->getDialog()->GetDlgItem(4))->SetCheck(m_filterOptions.m_bCheckboxes[2] ? BST_CHECKED : BST_UNCHECKED);
	((CButton*)getIMGF()->getDialog()->GetDlgItem(10))->SetCheck(m_filterOptions.m_bCheckboxes[3] ? BST_CHECKED : BST_UNCHECKED);
	((CComboBox*)getIMGF()->getDialog()->GetDlgItem(7))->SetCurSel(m_filterOptions.m_iComboBoxes[0]);
	((CComboBox*)getIMGF()->getDialog()->GetDlgItem(6))->SetCurSel(m_filterOptions.m_iComboBoxes[1]);
	((CComboBox*)getIMGF()->getDialog()->GetDlgItem(5))->SetCurSel(m_filterOptions.m_iComboBoxes[2]);
	((CEdit*)getIMGF()->getDialog()->GetDlgItem(9))->SetWindowTextW(CString2::convertStdStringToStdWString(m_filterOptions.m_strEditBoxes[0]).c_str());
	((CEdit*)getIMGF()->getDialog()->GetDlgItem(8))->SetWindowTextW(CString2::convertStdStringToStdWString(m_filterOptions.m_strEditBoxes[1]).c_str());
	((CEdit*)getIMGF()->getDialog()->GetDlgItem(48))->SetWindowTextW(CString2::convertStdStringToStdWString(m_filterOptions.m_strEditBoxes[2]).c_str());
	m_bRestoringFilterOptions = false;
	*/
}
bool					CIMGEditorTab::isFilterActive(void)
{
	/*
	todo
	bool bFilterCheckBox_Offset = ((CButton*)getIMGF()->getDialog()->GetDlgItem(44))->GetCheck() == BST_CHECKED;
	bool bFilterCheckBox_Size = ((CButton*)getIMGF()->getDialog()->GetDlgItem(3))->GetCheck() == BST_CHECKED;
	bool bFilterCheckBox_RWVersion = ((CButton*)getIMGF()->getDialog()->GetDlgItem(4))->GetCheck() == BST_CHECKED;
	bool bFilterCheckBox_Extensions = ((CButton*)getIMGF()->getDialog()->GetDlgItem(10))->GetCheck() == BST_CHECKED;
	
	return bFilterCheckBox_Offset || bFilterCheckBox_Size || bFilterCheckBox_RWVersion || bFilterCheckBox_Extensions;
	*/
	/*
	todo
	return
		((CComboBox*)getIMGF()->getDialog()->GetDlgItem(54))->GetCurSel() != 0
		|| ((CComboBox*)getIMGF()->getDialog()->GetDlgItem(5))->GetCurSel() != 0;
		*/
	return true;
}

void					CIMGEditorTab::sortEntries(void)
{
	// sort
	getIMGF()->getSortManager()->sort(getIMGFile());

	// log
	vector<string> vecExtendedLogLines;
	CSortPriorities *pSortPriorities = getIMGF()->getSortManager()->getSortPriorities();
	uint32 i = 0;
	CSortPriority *pSortPriority2 = nullptr;
	for (auto pSortPriority : pSortPriorities->getEntries())
	{
		if (!pSortPriority->isEnabled())
		{
			break;
		}
		vecExtendedLogLines.push_back(CLocalizationManager::get()->getTranslatedFormattedText("Sort_Priority_N_WithName", (i + 1), pSortPriority->getType()->getText().c_str()));
		i++;
		pSortPriority2 = pSortPriority;
	}
	if (vecExtendedLogLines.size() == 1)
	{
		log(CLocalizationManager::get()->getTranslatedFormattedText("Log_129", pSortPriority2->getType()->getText().c_str()));
	}
	else
	{
		log(CLocalizationManager::get()->getTranslatedFormattedText("Log_130", vecExtendedLogLines.size()));
	}
	log(CLocalizationManager::get()->getTranslatedText("Log_131"), true);
	log(CString2::join(vecExtendedLogLines, "\n"), true);

	// render
	readdAllEntriesToMainListView();

	// post
	setIMGModifiedSinceRebuild(true);
}

void					CIMGEditorTab::onEntryChange(CIMGEntry *pIMGEntry)
{
	loadProtectedEntryState(pIMGEntry);
}

void					CIMGEditorTab::loadProtectedEntryState(CIMGEntry *pIMGEntry)
{
	if (m_pDBFile->isIMGEntryFound(getIMGFile(), pIMGEntry))
	{
		pIMGEntry->setProtectedEntry(true);
	}
	else
	{
		pIMGEntry->setProtectedEntry(false);
	}
}
void				CIMGEditorTab::loadProtectedEntryStates(void)
{
	for (auto pIMGEntry : getIMGFile()->getEntries())
	{
		loadProtectedEntryState(pIMGEntry);
	}
}

void				CIMGEditorTab::loadFilter_Type(void)
{
	/*
	todo
	CComboBox *pComboBox = (CComboBox*)getIMGF()->getDialog()->GetDlgItem(54);
	unloadFilter_Type();
	vector<string> vecExtensions = getIMGFile()->getEntryExtensions();
	CStdVector::sortAZCaseInsensitive(vecExtensions);
	uint32
		i = 1,
		uiCurSel = 0;
	for (auto strExtension : vecExtensions)
	{
		pComboBox->InsertString(i, CString2::convertStdStringToStdWString(strExtension).c_str());
		if (getActiveFilter("type") == strExtension)
		{
			uiCurSel = i;
		}
		i++;
	}
	pComboBox->SetCurSel(uiCurSel);
	*/
}
void				CIMGEditorTab::loadFilter_Version(void)
{
	/*
	todo
	CComboBox *pComboBox = (CComboBox*)getIMGF()->getDialog()->GetDlgItem(5);
	unloadFilter_Version();

	todo
	//getIMGF()->m_umapFilterMapping_COLVersion.clear();
	//getIMGF()->m_umapFilterMapping_RWVersion.clear();
	//getIMGF()->m_iFilterMapping_UnknownVersion = 0;

	vector<eCOLVersion> vecCOLVersions;
	vector<eRWVersion> vecRWVersions;
	vector<string> vecVersions = getIMGFile()->getEntryVersions(vecCOLVersions, vecRWVersions);
	uint32
		i = 1,
		uiCurSel = 0;
	string strUnknownVersionText = CLocalizationManager::get()->getTranslatedText("UnknownVersion");
	for (auto strVersionText : vecVersions)
	{
		pComboBox->InsertString(i, CString2::convertStdStringToStdWString(strVersionText).c_str());
		if (getActiveFilter("version") == strVersionText)
		{
			uiCurSel = i;
		}

		todo
		if(strVersionText == strUnknownVersionText)
		{
			getIMGF()->m_iFilterMapping_UnknownVersion = i;
		}
		else if (i <= vecCOLVersions.size())
		{
			getIMGF()->m_umapFilterMapping_COLVersion[i] = vecCOLVersions[i - 1];
		}
		else
		{
			getIMGF()->m_umapFilterMapping_RWVersion[i] = vecRWVersions[(i - 1) - vecCOLVersions.size()];
		}

		i++;
	}
	pComboBox->SetCurSel(uiCurSel);
	*/
}

void				CIMGEditorTab::unloadFilter_Type(void)
{
	/*
	todo
	CComboBox *pComboBox = (CComboBox*)getIMGF()->getDialog()->GetDlgItem(54);

	for (uint32 i = 0, j = pComboBox->GetCount(); i < j; i++)
	{
		pComboBox->DeleteString(0);
	}

	pComboBox->InsertString(0, CLocalizationManager::get()->getTranslatedTextW("AllTypes").c_str());

	pComboBox->SetCurSel(0);
	*/
}
void				CIMGEditorTab::unloadFilter_Version(void)
{
	/*
	todo
	CComboBox *pComboBox = (CComboBox*)getIMGF()->getDialog()->GetDlgItem(5);

	for (uint32 i = 0, j = pComboBox->GetCount(); i < j; i++)
	{
		pComboBox->DeleteString(0);
	}

	pComboBox->InsertString(0, CLocalizationManager::get()->getTranslatedTextW("AllVersions").c_str());

	pComboBox->SetCurSel(0);
	*/
}

void				CIMGEditorTab::reassignEntryIds(void)
{
	/*
	todo
	CListCtrl *pListControl = (CListCtrl*)getIMGF()->getDialog()->GetDlgItem(37);
	for (uint32 i = 0, j = pListControl->GetItemCount(); i < j; i++)
	{
		pListControl->SetItem(i, 0, LVIF_TEXT, CString2::convertStdStringToStdWString(CString2::toString(i + 1)).c_str(), 0, 0, 0, 0);
	}
	*/
}

vector<CIMGEntry*>	CIMGEditorTab::getSelectedEntries(void)
{
	/*
	todo
	vector<CIMGEntry*> vecIMGEntries;

	CListCtrl *pListControl = ((CListCtrl*)getIMGF()->getDialog()->GetDlgItem(37));
	POSITION pos = pListControl->GetFirstSelectedItemPosition();
	if (pos == NULL)
	{
		return vecIMGEntries;
	}

	CIMGEntry *pIMGEntry;
	while (pos)
	{
		int nItem = pListControl->GetNextSelectedItem(pos);

		pIMGEntry = (CIMGEntry*)pListControl->GetItemData(nItem);
		vecIMGEntries.push_back(pIMGEntry);
	}

	return vecIMGEntries;
	*/
	vector<CIMGEntry*> vecIMGEntries;
	return vecIMGEntries;
}