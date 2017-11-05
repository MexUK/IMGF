#pragma warning(disable : 4005)

#include "IMGEditorTab.h"
#include "IMGF.h"
#include "Globals.h"
#include "Static/String.h"
#include "Static/StdVector.h"
#include "Static/Path.h"
#include "Static/File.h"
#include "Format/IMG/Regular/IMGManager.h"
#include "Format/IMG/Regular/IMGFormat.h"
#include "Format/IMG/Regular/IMGEntry.h"
#include "Engine/RW/RWManager.h"
#include "Engine/RW/RWVersion.h"
#include "Engine/RAGE/RageManager.h"
#include "Task/Tasks/Sort/SortManager.h"
#include "Task/Tasks/Sort/SortPriority.h"
#include "Task/Tasks/Sort/SortType.h"
#include "Task/Tasks/Sort/ESortType.h"
#include "Task/Tasks/RecentlyOpen/RecentlyOpenManager.h"
#include "Task/Tasks/Find/SearchEntry.h"
#include "Task/Tasks/Sort/SortPriorities.h"
#include "Static/Debug.h"
#include "DB/DBFormat.h"
#include "Format/COL/COLManager.h"
#include "Engine/RW/RWVersionManager.h"
#include "Format/COL/COLVersionManager.h"
#include "Engine/RAGE/RageResourceTypeManager.h"
#include "Localization/LocalizationManager.h"
#include "Platform/Hardware/PlatformManager.h"
#include "Settings/SettingsManager.h"
#include "Static/Input.h"
#include "DB/DBManager.h"
#include "Control/Controls/Grid.h"
#include "GUI/Editor/Editors/IMGEditor.h"
#include "GUI/Window/WindowManager.h"
#include "GUI/Window/Windows/MainWindow/MainWindow.h"
#include "GUI/Layer/Layers/MainLayer/MainLayer.h"
#include "GUI/Input/EInputItem.h"
#include "Control/Controls/Text.h"
#include "Control/Controls/TabBar.h"
#include "Control/Controls/TextBox.h"
#include "Control/Controls/DropDown.h"
#include "Control/Controls/ProgressBar.h"
#include "Control/Components/ScrollBarPool.h"
#include "Format/EFileType.h"
#include "Event/EInputEvent.h"
#include "../BXGI/Event/EEvent.h"
#include "Exception/EExceptionCode.h"
#include "Task/Tasks/Tasks.h"
#include <map>
#include <algorithm>

using namespace std;
using namespace bxcf;
using namespace bxcf::fileType;
using namespace bxgx;
using namespace bxgx::events;
using namespace bxgi;
using namespace imgf;
using namespace imgf::mainLayer::input;

IMGEditorTab::IMGEditorTab(void) :
	m_pIMGEditor(nullptr),
	m_pEntryGrid(nullptr),
	m_pEntryTypeFilter(nullptr),
	m_pEntryVersionFilter(nullptr),
	m_bRestoringFilterOptions(false),
	m_uiOverwriteEntryOption(0),
	m_bTabMarkedForClose(false),
	m_bTabReadyToClose(true)
{
}

IMGEditorTab::~IMGEditorTab(void)
{
	unbindEvents();
}

// events
void					IMGEditorTab::bindEvents(void)
{
	bindEvent(RESIZE_WINDOW, &IMGEditorTab::repositionAndResizeControls);
	bindEvent(SELECT_DROP_DOWN_ITEM, &IMGEditorTab::onSelectDropEntry);
	bindEvent(CHANGE_TEXT_BOX, &IMGEditorTab::onChangeTextBox);
	bindEvent(UNSERIALIZE_IMG_ENTRY, &IMGEditorTab::onUnserializeEntry);
	bindEvent(SORT_GRID_BY_COLUMN, &IMGEditorTab::onSortGridByColumn);
	bindEvent(DOUBLE_LEFT_MOUSE_UP, &IMGEditorTab::onDoubleLeftMouseUp2);

	EditorTab::bindEvents();
}

void					IMGEditorTab::unbindEvents(void)
{
	unbindEvent(RESIZE_WINDOW, &IMGEditorTab::repositionAndResizeControls);
	unbindEvent(SELECT_DROP_DOWN_ITEM, &IMGEditorTab::onSelectDropEntry);
	unbindEvent(CHANGE_TEXT_BOX, &IMGEditorTab::onChangeTextBox);
	unbindEvent(UNSERIALIZE_IMG_ENTRY, &IMGEditorTab::onUnserializeEntry);
	unbindEvent(SORT_GRID_BY_COLUMN, &IMGEditorTab::onSortGridByColumn);
	unbindEvent(DOUBLE_LEFT_MOUSE_UP, &IMGEditorTab::onDoubleLeftMouseUp2);

	EditorTab::unbindEvents();
}

// load/unload
void					IMGEditorTab::unload(void)
{
	delete m_pDBFile;

	m_pIMGFile->unload();
	delete m_pIMGFile;
}

// on file loaded
void					IMGEditorTab::onFileLoaded(void)
{
	string strFilePath = m_pEditor->getResolvedFilePath(getFile()->getFilePath());

	// update tab text
	updateTabText();

	// add file path to recently opened files list
	getIMGF()->getRecentlyOpenManager()->addRecentlyOpenEntry(m_pEditor->getEditorType(), strFilePath);

	// store render items
	getRenderItems().addEntry(m_pEntryGrid);
	getRenderItems().addEntry(m_pEntryTypeFilter);
	getRenderItems().addEntry(m_pEntryVersionFilter);

	addGridEntries();

	/*
	todo
	if (m_bTabMarkedForClose)
	{
		return;
	}
	*/

	m_pEntryGrid->setActiveItem();

	loadFilter_Type();
	loadFilter_Version();

	setFileInfoText();





	return;

	// todo

	// add to recently open
	
	//getIMGF()->getRecentlyOpenManager()->loadRecentlyOpenEntries();

	// update filename for open last
	getIMGF()->getActiveWindow()->setOpenLastFilename(Path::getFileName(getIMGFile()->getFilePath()));

	// load corresponding DB file & protected entry states
	m_pDBFile = nullptr;
	string strDBFilePath = Path::replaceFileExtension(getIMGFile()->getFilePath(), "db");
	if (File::doesFileExist(strDBFilePath))
	{
		m_pDBFile = DBManager::get()->unserializeFile(strDBFilePath);

		if (m_pDBFile->doesHaveError())
		{
			m_pDBFile = nullptr;
		}
	}

	if (m_pDBFile == nullptr)
	{
		// either the db file doesn't exist or the db file is corrupt
		//pEditorTab->m_pDBFile = DBManager::get()->createDBFileFromIMGFile(pEditorTab->getIMGFile());
		m_pDBFile = DBManager::get()->createBlankDBFile();
	}
	loadProtectedEntryStates();

	// check for unknown RW versions
	checkForUnknownRWVersionEntries();
}

// controls
void					IMGEditorTab::addControls(void)
{
	int32 x, y, w, h, y2, w2, h2;
	uint32 uiTitleBarHeight, uiButtonHeight, uiLogWidth;
	string strStyleGroup;

	uiTitleBarHeight = m_pWindow->getTitleBarHeight();
	uiButtonHeight = 37;
	uiLogWidth = 335;

	// grid
	//Grid *pBlankGrid = m_pIMGEditor->getEntryGrid();

	x = 139 + 139;
	y = 162 + 30;
	w = m_pWindow->getSize().x - x - uiLogWidth;
	h = m_pWindow->getSize().y - y;
	strStyleGroup = "imgEditor_grid";

	m_pEntryGrid = addGrid(x, y, w, h);
	m_pEntryGrid->setStyleGroups(strStyleGroup);

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
	m_pEntryVersionFilter->addLinkedItem(m_pEntryTypeFilter);
}

void					IMGEditorTab::initControls(void)
{
	// todo bindEvents();
	addGridHeaders(getIMGFile()->getVersion());
	repositionAndResizeControls(Vec2i(0, 0));
}

void					IMGEditorTab::addGridHeaders(EIMGVersion uiIMGVersionValue)
{
	m_pEntryGrid->addHeader("Index", 50);
	m_pEntryGrid->addHeader("Type", 40);
	m_pEntryGrid->addHeader("Name", 160);
	m_pEntryGrid->addHeader("Offset", 95);
	m_pEntryGrid->addHeader("Size", 80);

	switch (uiIMGVersionValue)
	{
	case IMG_UNKNOWN:
	case IMG_1:
	case IMG_2:
		m_pEntryGrid->addHeader("Version", 170);
		break;
	case IMG_3:
		m_pEntryGrid->addHeader("Resource Type", 125);
		break;
	case IMG_FASTMAN92:
		m_pEntryGrid->addHeader("Version", 170);
		m_pEntryGrid->addHeader("Compression", 125);
		m_pEntryGrid->addHeader("Encryption", 125);
		break;
	}
}

void					IMGEditorTab::onUnserializeEntry(IMGFormat *img)
{
	if (img != m_pIMGFile)
	{
		return;
	}

	getIMGF()->getTaskManager()->onTaskProgressTick();
}

void					IMGEditorTab::removeControls(void)
{
	removeControl(m_pEntryGrid);
	m_pEntryGrid = nullptr;
}

void					IMGEditorTab::repositionAndResizeControls(Vec2i& vecSizeDifference)
{
	Vec2i point;
	Vec2u size, newSize;
	int32 iNewX, iNewWidth, iNewHeight;
	uint32 uiLogWidth;

	uiLogWidth = 335;

	// grid
	size = m_pEntryGrid->getSize();
	iNewWidth = (int32)m_pWindow->getSize().x - m_pEntryGrid->getPosition().x - (int32)uiLogWidth;
	iNewHeight = (int32)m_pWindow->getSize().y - m_pEntryGrid->getPosition().y;
	Vec2i vecNewSize2 = Vec2i(iNewWidth, iNewHeight);
	if (vecNewSize2.x < 20)
	{
		vecNewSize2.x = 20;
	}
	else if (vecNewSize2.x >= m_pEntryGrid->getScrollBarPool()->getScrollBarByOrientation(VERTICAL)->getBackgroundBarSize().x)
	{
		vecNewSize2.x -= m_pEntryGrid->getScrollBarPool()->getScrollBarByOrientation(VERTICAL)->getBackgroundBarSize().x;
	}
	if (vecNewSize2.y < 20)
	{
		vecNewSize2.y = 20;
	}
	else if (vecNewSize2.y > m_pEntryGrid->getScrollBarPool()->getScrollBarByOrientation(HORIZONTAL)->getBackgroundBarSize().y)
	{
		vecNewSize2.y -= m_pEntryGrid->getScrollBarPool()->getScrollBarByOrientation(HORIZONTAL)->getBackgroundBarSize().y;
	}
	Vec2u vecNewSize = Vec2u(vecNewSize2.x, vecNewSize2.y);
	m_pEntryGrid->setSize(vecNewSize);

	// filter - entry type
	point = m_pEntryTypeFilter->getPosition();
	iNewX = m_pWindow->getSize().x - m_pEntryTypeFilter->getSize().x - m_pEntryVersionFilter->getSize().x - uiLogWidth - 10;
	m_pEntryTypeFilter->setPosition(Vec2i(iNewX, point.y));

	// filter - entry version
	point = m_pEntryVersionFilter->getPosition();
	iNewX = m_pWindow->getSize().x - m_pEntryVersionFilter->getSize().x - uiLogWidth - 10;
	m_pEntryVersionFilter->setPosition(Vec2i(iNewX, point.y));
}

// file unserialization
bool					IMGEditorTab::unserializeFile(void)
{
	IMGFormat *img = getIMGFile();

	/*
	progress bar: 3 stages

	[IMG versions 1, 2, and fastman92]
	- parsing header
	- parsing RW versions
	- adding entries to grid

	[IMG versions 3 (encrypted and unencrypted)]
	- parsing header
	- parsing entry names
	- adding entries to grid
	*/

	if (!img->openFile())
	{
		return false;
	}
	if (!img->readMetaData()) // here for progress bar tick count
	{
		Tasks::showMessage(Format::getErrorReason(img->getErrorCode()) + "\r\n\r\n" + img->getFilePath(), "Can't Open IMG File");
		delete img;
		return false;
	}

	uint32
		uiProgressBarMaxMultiplier = 3,
		uiProgressBarMax = img->m_uiEntryCount * uiProgressBarMaxMultiplier;
	getProgressBar()->setMax(uiProgressBarMax);

	if (!img->unserialize())
	{
		Tasks::showMessage(Format::getErrorReason(img->getErrorCode()) + "\r\n\r\n" + img->getFilePath(), "Can't Open IMG File");
		delete img;
		return false;
	}

	return true;
}

// control events
void					IMGEditorTab::onSelectDropEntry(DropDownItem *pDropEntry)
{
	if(pDropEntry->getDropControl() == m_pEntryTypeFilter || pDropEntry->getDropControl() == m_pEntryVersionFilter)
	{
		readdGridEntries();
	}
}

void					IMGEditorTab::onChangeTextBox(TextBox *pTextBox)
{
	if(pTextBox == m_pSearchBox)
	{
		readdGridEntries();
	}
}

void					IMGEditorTab::onSortGridByColumn(Grid *pGrid)
{
	if (pGrid == m_pEntryGrid)
	{
		unordered_map<GridRow*, IMGEntry*> umapGridEntries;
		for (GridRow *pRow : pGrid->getEntries())
		{
			umapGridEntries[pRow] = (IMGEntry*)pRow->getUserData();
		}
		uint32 i = 0;
		for (GridRow *pRow : pGrid->getEntries())
		{
			getIMGFile()->setEntryByIndex(i++, umapGridEntries[pRow]);
		}

		reassignEntryIds();
	}
}

void					IMGEditorTab::onDoubleLeftMouseUp2(Vec2i vecCursorPosition)
{
	GridRow *pGridRow = m_pEntryGrid->getRowFromPoint(BXGX::get()->getCursorPosition());
	if (pGridRow)
	{
		mutexControlInput.lock();
		BXGX::get()->getMenuItemsPressed().push_back((MenuItem*)m_pEditor->getMainWindow()->getItemById(RENAME));
		mutexControlInput.unlock();
	}
}

// error checking
void					IMGEditorTab::checkForUnknownRWVersionEntries(void)
{
	if (getIMGFile()->getVersion() == IMG_3)
	{
		return;
	}

	vector<IMGEntry*> vecUnknownRWVersionEntries = getIMGFile()->getUnknownVersionEntries();
	if (vecUnknownRWVersionEntries.size() > 0)
	{
		vector<string> vecIMGEntryNames;
		for (auto pIMGEntry : vecUnknownRWVersionEntries)
		{
			vecIMGEntryNames.push_back(pIMGEntry->getEntryName());
		}

		/*
		todo
		getIMGF()->getTaskManager()->onPauseTask();
		getIMGF()->getPopupGUIManager()->showListViewDialog(
			LocalizationManager::get()->getTranslatedText("UnknownVersions"),
			LocalizationManager::get()->getTranslatedFormattedText("UnknownVersionsCheck", Path::getFileName(getIMGFile()->getFilePath()).c_str(), vecUnknownRWVersionEntries.size()),
			LocalizationManager::get()->getTranslatedText("Window_OrphanEntries_EntryName"),
			vecIMGEntryNames,
			LocalizationManager::get()->getTranslatedFormattedText("SaveFilePopup_3_InitialFilename",
			Path::replaceFileExtension(Path::getFileName(getIMGFile()->getFilePath()), "TXT").c_str()),
			"UNKNOWNRWVERSIONS"
			);
		getIMGF()->getTaskManager()->onResumeTask();
		*/
	}
}

/*
void					IMGEditorTab::log(string strText, bool bExtendedModeOnly)
{
	//string strLogEntryWithTimestamp = "[" + String::getTimestampText() + "] " + strText;
	string strLogEntryWithTimestampAndIMG = "[" + String::getTimestampText() + "] [" + Path::getFileName(m_pIMGFile->getFilePath()) + "] " + strText;

	if (bExtendedModeOnly)
	{
		m_vecLogLinesExtended.push_back(strLogEntryWithTimestampAndIMG);

		// automatic logging to file
		if (getIMGF()->getSettingsManager()->getSettingString("AutomaticLoggingPath") != "")
		{
			// extended file
			if (getIMGF()->getSettingsManager()->getSettingBool("AutomaticLoggingExtended"))
			{
				string strExtendedLogPath = Path::addSlashToEnd(getIMGF()->getSettingsManager()->getSettingString("AutomaticLoggingPath"));
				strExtendedLogPath += String::getDateTextForFolder() + "/" + LocalizationManager::get()->getTranslatedText("LogFilename_Extended");
				File::storeFile(strExtendedLogPath, strLogEntryWithTimestampAndIMG + "\n", true, false);
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
				string strExtendedLogPath = Path::addSlashToEnd(getIMGF()->getSettingsManager()->getSettingString("AutomaticLoggingPath"));
				strExtendedLogPath += String::getDateTextForFolder() + "/" + LocalizationManager::get()->getTranslatedText("LogFilename_Basic");
				File::storeFile(strExtendedLogPath, strLogEntryWithTimestampAndIMG + "\n", true, false);
			}
			
			// extended file
			if (getIMGF()->getSettingsManager()->getSettingBool("AutomaticLoggingExtended"))
			{
				string strExtendedLogPath = Path::addSlashToEnd(getIMGF()->getSettingsManager()->getSettingString("AutomaticLoggingPath"));
				strExtendedLogPath += String::getDateTextForFolder() + "/" + LocalizationManager::get()->getTranslatedText("LogFilename_Extended");
				File::storeFile(strExtendedLogPath, strLogEntryWithTimestampAndIMG + "\n", true, false);
			}
		}
	}

	if (getIMGF()->getActiveTab() == this)
	{
		/////////////////////////
		todo
		CEdit *pEdit = ((CEdit*)getIMGF()->getDialog()->GetDlgItem(14));
		pEdit->SetWindowTextW(String::convertStdStringToStdWString(String::join(m_vecLogLinesGUI, "\r\n")).c_str());
		pEdit->LineScroll(pEdit->GetLineCount());
		//////////////////////
	}
}
*/

void					IMGEditorTab::checkToApplyCompression(IMGEntry *pIMGEntry)
{
	if (getIMGF()->getSettingsManager()->getSettingBool("AutoCompressionImportReplace"))
	{
		if (getIMGFile()->getVersion() == IMG_FASTMAN92)
		{
			//ECompressionAlgorithm ECompressionAlgorithmValue = (ECompressionAlgorithm)getIMGF()->getSettingsManager()->getSettingInt("Fastman92IMGAutoCompressionType");
			if (getIMGFile()->getEntryCount() > 1) // > 1 instead of > 0, because the entry has already been added to the pool.
			{
				ECompressionAlgorithm ECompressionAlgorithmValue;

				// check to use compression type from first entry in IMG
				ECompressionAlgorithmValue = getIMGFile()->getEntryByIndex(0)->getCompressionAlgorithmId();
				
				// if compression type is not compressed (none) or unknown, default to ZLIB compression
				if (ECompressionAlgorithmValue == COMPRESSION_NONE || ECompressionAlgorithmValue == COMPRESSION_UNKNOWN)
				{
					ECompressionAlgorithmValue = COMPRESSION_ZLIB;
				}

				// apply the compression to the IMG entry
				pIMGEntry->applyCompression(ECompressionAlgorithmValue);
			}
		}
	}
}

// add entry
void					IMGEditorTab::addEntryAfter(FormatEntry *pEntry)
{
	IMGEntry *pIMGEntry = (IMGEntry *)pEntry;

	checkToApplyCompression(pIMGEntry);
	addGridEntry(pIMGEntry);
	updateIMGText();
}

// replace entry
void					IMGEditorTab::replaceEntryViaFile(string strEntryName, string strEntryFilePath, string strNewEntryName)
{
	IMGEntry *pIMGEntry = getIMGFile()->replaceEntryViaFile(strEntryName, strEntryFilePath, strNewEntryName);
	checkToApplyCompression(pIMGEntry);
	updateGridEntry(pIMGEntry);
	updateIMGText();
}

void					IMGEditorTab::replaceEntryViaData(string strEntryName, string& strEntryData, string strNewEntryName)
{
	IMGEntry *pIMGEntry = getIMGFile()->replaceEntryViaData(strEntryName, strEntryData, strNewEntryName);
	checkToApplyCompression(pIMGEntry);
	updateGridEntry(pIMGEntry);
	updateIMGText();
}

void					IMGEditorTab::addOrReplaceEntryViaFile(string strEntryFilePath, string strEntryName)
{
	uint32 uiIMGEntryCount = getIMGFile()->getEntryCount();
	IMGEntry *pIMGEntry = getIMGFile()->addOrReplaceEntryViaFile(strEntryFilePath, strEntryName);
	checkToApplyCompression(pIMGEntry);
	if (uiIMGEntryCount == getIMGFile()->getEntryCount())
	{
		// entry was replaced
		updateGridEntry(pIMGEntry);
	}
	else
	{
		// entry was added
		addGridEntry(pIMGEntry);
		updateEntryCountText();
	}
	updateIMGText();
}

void					IMGEditorTab::addOrReplaceEntryViaData(string strEntryName, string strEntryData)
{
	uint32 uiIMGEntryCount = getIMGFile()->getEntryCount();
	IMGEntry *pIMGEntry = getIMGFile()->addOrReplaceEntryViaData(strEntryName, strEntryData);
	checkToApplyCompression(pIMGEntry);
	if (uiIMGEntryCount == getIMGFile()->getEntryCount())
	{
		// entry was replaced
		updateGridEntry(pIMGEntry);
	}
	else
	{
		// entry was added
		addGridEntry(pIMGEntry);
		updateEntryCountText();
	}
	updateIMGText();
}

void					IMGEditorTab::addOrReplaceEntryViaFileAndSettings(string strEntryFilePath, string strEntryName)
{
	if (strEntryName == "")
	{
		strEntryName = Path::getFileName(strEntryFilePath);
	}

	IMGEntry *pIMGEntry = getIMGFile()->getEntryByName(strEntryName);
	if (pIMGEntry == nullptr)
	{
		// entry name not found in IMG
		// import the entry
		addEntryViaFile(strEntryFilePath, strEntryName);
		return;
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
			/*
			todo
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
			*/
		}

		if (uiResultOption == 0) // import
		{
			addEntryViaFile(strEntryFilePath, strEntryName);
			return;
		}
		else if (uiResultOption == 1) // replace
		{
			replaceEntryViaFile(strEntryName, strEntryFilePath);
			return;
		}
	}

	if (pIMGEntry->isProtectedEntry())
	{
		// entry is protected

		if (getIMGF()->getSettingsManager()->getSettingBool("OverwriteProtectedFiles"))
		{
			// Setting is enabled: Overwrite protected files
			replaceEntryViaFile(strEntryName, strEntryFilePath);
			return;
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
		uiNewEntryFileCreationDate = File::getFileCreationDate(strEntryFilePath);

	if (uiExistingEntryFileCreationDate == 0 || uiNewEntryFileCreationDate == 0)
	{
		// either the file creation date is not stored for the existing entry or unable to fetch it for the new entry
		replaceEntryViaFile(strEntryName, strEntryFilePath);
		return;
	}

	if (uiNewEntryFileCreationDate == uiExistingEntryFileCreationDate)
	{
		// file creation date is the same for both existing entry and new entry
		replaceEntryViaFile(strEntryName, strEntryFilePath);
		return;
	}

	if (uiExistingEntryFileCreationDate < uiNewEntryFileCreationDate)
	{
		// the existing entry is older than the new entry

		if (getIMGF()->getSettingsManager()->getSettingBool("OverwriteOlderFiles"))
		{
			// Setting is enabled: Overwrite older files
			replaceEntryViaFile(strEntryName, strEntryFilePath);
			return;
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
			replaceEntryViaFile(strEntryName, strEntryFilePath);
			return;
		}
		else
		{
			// Setting is disabled: Overwrite newer files
			// do nothing, don't replace the file
			return;
		}
	}

	// replace by default. e.g. if no settings are enabled.
	replaceEntryViaFile(strEntryName, strEntryFilePath);
	return;
}

void					IMGEditorTab::addOrReplaceEntryViaDataAndSettings(string strEntryName, string strEntryData)
{
	IMGEntry *pIMGEntry = getIMGFile()->getEntryByName(strEntryName);
	if (pIMGEntry == nullptr)
	{
		// entry name not found in IMG
		// import the entry
		addEntryViaData(strEntryName, strEntryData);
		return;
	}

	// entry name is found in IMG
	if (getIMGF()->getSettingsManager()->getSettingBool("AskBeforeOverwritingFiles"))
	{
		/*
		todo

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
		*/
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

void					IMGEditorTab::removeEntry(IMGEntry *pIMGEntry)
{
	getIMGFile()->removeEntry(pIMGEntry);
	updateEntryCountText();
}

void					IMGEditorTab::removeSelectedEntries(void)
{
	for (GridRow *pRow : getEntryGrid()->getSelectedRows())
	{
		IMGEntry *pIMGEntry = (IMGEntry*)pRow->getUserData();

		removeEntry(pIMGEntry);
		Events::trigger(TASK_PROGRESS);
	}

	updateEntryCountText();
}

void					IMGEditorTab::removeAllEntries(void)
{
	getIMGFile()->removeAllEntries();
	updateEntryCountText();
}

void					IMGEditorTab::readdGridEntries(void)
{
	//m_pEditor->setSelectedEntryCount(0);
	//m_pEditor->updateSelectedEntryCountText();

	m_pEntryGrid->removeAllEntries();
	addGridEntries();
}

void					IMGEditorTab::addGridEntries(void)
{
	//m_bTabReadyToClose = false;

	DropDownItem
		*pTypeFilterItem = m_pEntryTypeFilter->getActiveItem(),
		*pVersionFilterItem = m_pEntryVersionFilter->getActiveItem();
	TextBox
		*pSearchBoxFilter = m_pSearchBox;
	int32
		iTypeFilterSelectedIndex = m_pEntryTypeFilter->getSelectedItemIndex(),
		iVersionFilterSelectedIndex = m_pEntryVersionFilter->getSelectedItemIndex();
	uint32
		uiFileType,
		uiEntryIndex = 0,
		uiEntryCount = m_pIMGFile->getEntryCount(),
		uiSelectedFileType = pTypeFilterItem ? pTypeFilterItem->getUserdata() : -1,
		uiSelectedFileVersion = pVersionFilterItem ? pVersionFilterItem->getUserdata() : -1,
		uiSelectedFileVersionType = pVersionFilterItem ? pVersionFilterItem->getUserdata2() : -1;
	bool
		bAddEntry,
		bTypeFilterIsDynamicItem = iTypeFilterSelectedIndex > 0,
		bVersionFilterIsDynamicItem = iVersionFilterSelectedIndex > 0,
		bSearchFilterIsActive = pSearchBoxFilter->doesContainText();
	TaskManager
		*pTaskManager = getIMGF()->getTaskManager();
	string
		strSearchFilterText = pSearchBoxFilter->getTextAtLine(0);

	// m_pEntryGrid->getEntries().resize(m_pIMGFile->getEntryCount()); // todo - still needed?

	void **pRows = new void*[uiEntryCount];
	GridRow *pRow;
	for (uint32 i = 0; i < uiEntryCount; i++)
	{
		pRow = new GridRow;
		pRows[i] = pRow;
	}
	for (uint32 i = 0; i < uiEntryCount; i++)
	{
		((GridRow*)(pRows[i]))->setGrid(m_pEntryGrid);
	}

	for (IMGEntry *pIMGEntry : m_pIMGFile->getEntries())
	{
		bAddEntry = true;
		uiFileType = pIMGEntry->getFileType();

		if (bTypeFilterIsDynamicItem && uiFileType != uiSelectedFileType)
		{
			bAddEntry = false;
		}

		if (bVersionFilterIsDynamicItem && (uiFileType != uiSelectedFileVersionType || uiSelectedFileVersion != pIMGEntry->getRawVersion()))
		{
			bAddEntry = false;
		}

		if (bSearchFilterIsActive && !String::isIn(pIMGEntry->getEntryName(), strSearchFilterText, false))
		{
			bAddEntry = false;
		}

		if (bAddEntry)
		{
			addGridEntry(pIMGEntry, uiEntryIndex++, pRows);
		}

		pTaskManager->onTaskProgressTick();

		/*
		todo
		if (m_bTabMarkedForClose)
		{
			break;
		}
		*/
	}

	m_pEntryGrid->recalculateProgressFor1Item();
	m_pEntryGrid->render();

	updateEntryCountText();
	
	//m_bTabReadyToClose = true;
}

void					IMGEditorTab::addGridEntry(IMGEntry *pIMGEntry, uint32 uiEntryIndex, void **pRows)
{
	if (uiEntryIndex == -1)
	{
		uiEntryIndex = m_pEntryGrid->getEntryCount();
	}
	GridRow *pRow;
	if (pRows == nullptr)
	{
		pRow = new GridRow;
	}
	else
	{
		pRow = (GridRow*)(pRows[uiEntryIndex]);
	}

	bool bIsFastman92IMGFormat = m_pIMGFile->getVersion() == IMG_FASTMAN92;

	pRow->setUserData((uint32)pIMGEntry);

	vector<string> vecText;
	vecText.resize(bIsFastman92IMGFormat ? 8 : 6);
	vecText[0] = String::addNumberGrouping(String::toString(uiEntryIndex + 1));
	vecText[1] = pIMGEntry->getEntryExtension();
	vecText[2] = pIMGEntry->getEntryName();
	vecText[3] = String::addNumberGrouping(String::toString(pIMGEntry->getEntryOffset()));
	vecText[4] = String::addNumberGrouping(String::toString(pIMGEntry->getEntrySize()));
	vecText[5] = pIMGEntry->getVersionText();
	if (bIsFastman92IMGFormat)
	{
		vecText[6] = IMGManager::getCompressionTypeText(pIMGEntry->getCompressionAlgorithmId());
		vecText[7] = IMGManager::getEncryptionText(pIMGEntry->isEncrypted());
	}

	pRow->getText().assign(1, vecText);

	if (pRows == nullptr)
	{
		m_pEntryGrid->addEntry(pRow);
	}
	else
	{
		m_pEntryGrid->addEntry(pRow);
		// m_pEntryGrid->setEntryByIndex(uiEntryIndex, pRow); // todo - still needed?
	}

	pRow->setShown(true);

	/*
	// todo - keep?
	if (pRow->isRowDisplayedWithinScrollRange())
	{
		m_pEntryGrid->renderItem();
	}
	*/
}

void					IMGEditorTab::updateGridEntry(IMGEntry *pIMGEntry)
{
	GridRow *pRow = m_pEntryGrid->getRowByUserData((uint32)pIMGEntry);
	if (!pRow)
	{
		// IMG entry is not currently displayed, e.g. filter.
		return;
	}

	uint32 uiEntryIndex = m_pEntryGrid->getIndexByEntry(pRow);
	bool bIsFastman92IMGFormat = m_pIMGFile->getVersion() == IMG_FASTMAN92;

	vector<string> vecText;
	vecText.resize(bIsFastman92IMGFormat ? 8 : 6);
	vecText[0] = String::addNumberGrouping(String::toString(uiEntryIndex + 1));
	vecText[1] = pIMGEntry->getEntryExtension();
	vecText[2] = pIMGEntry->getEntryName();
	vecText[3] = String::addNumberGrouping(String::toString(pIMGEntry->getEntryOffset()));
	vecText[4] = String::addNumberGrouping(String::toString(pIMGEntry->getEntrySize()));
	vecText[5] = pIMGEntry->getVersionText();
	if (bIsFastman92IMGFormat)
	{
		vecText[6] = IMGManager::getCompressionTypeText(pIMGEntry->getCompressionAlgorithmId());
		vecText[7] = IMGManager::getEncryptionText(pIMGEntry->isEncrypted());
	}

	pRow->getText().assign(1, vecText);
	m_pEntryGrid->render();
}

uint32			IMGEditorTab::getMainListViewItemIndexByItemData(IMGEntry *pIMGEntry)
{
	/*
	todo
	for (uint32 i = 0, j = getListView()->GetItemCount(); i < j; i++)
	{
		if ((IMGEntry*)getListView()->GetItemData(i) == pIMGEntry)
		{
			return i;
		}
	}
	*/
	return -1;
}

// file info text
void					IMGEditorTab::setFileInfoText(void)
{
	m_pText_FilePath->setText(getIMGFile()->getIMGFilePath());
	m_pText_FileVersion->setText(IMGManager::getVersionText(getIMGFile()->getVersion(), getIMGFile()->isEncrypted()));
	m_pText_FileGame->setText(IMGManager::getVersionGames(getIMGFile()->getVersion()));

	updateEntryCountText();
}

void					IMGEditorTab::updateEntryCountText(void)
{
	uint32
		uiDisplayedEntryCount = getEntryGrid()->getEntryCount(),
		uiTotalEntryCount = getIMGFile()->getEntryCount();
	string
		strEntryCountText;

	if (uiDisplayedEntryCount == uiTotalEntryCount)
	{
		strEntryCountText = String::toString(uiTotalEntryCount);
	}
	else
	{
		strEntryCountText = String::toString(uiDisplayedEntryCount) + " of " + String::toString(uiTotalEntryCount);
	}

	m_pText_FileEntryCount->setText(strEntryCountText);
}

void					IMGEditorTab::updateTabText(void)
{
	string strTabText = Path::getFileName(m_pIMGFile->getIMGFilePath());
	m_pTab->setText(strTabText);
}

void					IMGEditorTab::updateIMGText(void)
{
	/*
	todo
	string strPlatformName = PlatformManager::get()->getPlatformName(getIMGFile()->getPlatform());

	if (getIMGFile()->getVersion() == IMG_FASTMAN92)
	{
		uint32 uiEntryCount = getIMGFile()->getEntryCount();
		uint32 uiUncompressedEntryCount = getIMGFile()->getEntryCountForCompressionType(COMPRESSION_NONE);
		string strVersionSuffix = "";
		if (uiEntryCount == uiUncompressedEntryCount)
		{
			strVersionSuffix = LocalizationManager::get()->getTranslatedText("CompressionValue_Uncompressed");
		}
		else if (uiUncompressedEntryCount == 0)
		{
			strVersionSuffix = LocalizationManager::get()->getTranslatedText("CompressionValue_Compressed");
		}
		else
		{
			strVersionSuffix = LocalizationManager::get()->getTranslatedText("CompressionValue_PartiallyCompressed");
		}
		((CStatic*)getIMGF()->getDialog()->GetDlgItem(19))->SetWindowTextW(LocalizationManager::get()->getTranslatedFormattedTextW("IMGVersion", IMGManager::getVersionName(IMG_FASTMAN92, getIMGFile()->isEncrypted()).c_str(), strPlatformName.c_str(), strVersionSuffix.c_str()).c_str());
	}
	else
	{
		((CStatic*)getIMGF()->getDialog()->GetDlgItem(19))->SetWindowTextW(LocalizationManager::get()->getTranslatedFormattedTextW("IMGVersion", IMGManager::getVersionName(getIMGFile()->getVersion(), getIMGFile()->isEncrypted()).c_str(), strPlatformName.c_str(), IMGManager::getVersionGames(getIMGFile()->getVersion()).c_str()).c_str());
	}
	*/
}

// entry fetching
IMGEntry*				IMGEditorTab::getEntryByName(string strEntryName)
{
	strEntryName = String::toUpperCase(strEntryName);
	for (IMGEntry *pIMGEntry : getIMGFile()->getEntries())
	{
		if (strEntryName == String::toUpperCase(pIMGEntry->getEntryName()))
		{
			return pIMGEntry;
		}
	}
	return nullptr;
}

vector<IMGEntry*>		IMGEditorTab::getEntriesByNumericMultiOptionValues(uint32 uiEntryAttribute, uint32 uiMatchType, uint32 uiValue1, uint32 uiValue2)
{
	vector<IMGEntry*> vecIMGEntries;
	switch (uiEntryAttribute)
	{
	case 0: // Index
		uiValue1--;
		uiValue2--;
		switch (uiMatchType)
		{
		case 0: // Equal to
			for (GridRow *pGridRow : m_pEntryGrid->getEntries()) {	if (pGridRow->getRowIndex() == uiValue1)	vecIMGEntries.push_back((IMGEntry*)pGridRow->getUserData());	Events::trigger(TASK_PROGRESS); }
			break;
		case 1: // Not equal to
			for (GridRow *pGridRow : m_pEntryGrid->getEntries()) {	if (pGridRow->getRowIndex() != uiValue1)	vecIMGEntries.push_back((IMGEntry*)pGridRow->getUserData());	Events::trigger(TASK_PROGRESS); }
			break;
		case 2: // Between
			for (GridRow *pGridRow : m_pEntryGrid->getEntries()) {	if (pGridRow->getRowIndex() >= uiValue1 && pGridRow->getRowIndex() <= uiValue2)	vecIMGEntries.push_back((IMGEntry*)pGridRow->getUserData());	Events::trigger(TASK_PROGRESS); }
			break;
		case 3: // Less than
			for (GridRow *pGridRow : m_pEntryGrid->getEntries()) {	if (pGridRow->getRowIndex() < uiValue1)		vecIMGEntries.push_back((IMGEntry*)pGridRow->getUserData());	Events::trigger(TASK_PROGRESS); }
			break;
		case 4: // More than
			for (GridRow *pGridRow : m_pEntryGrid->getEntries()) {	if (pGridRow->getRowIndex() > uiValue1)		vecIMGEntries.push_back((IMGEntry*)pGridRow->getUserData());	Events::trigger(TASK_PROGRESS); }
			break;
		case 5: // Less than or equal to
			for (GridRow *pGridRow : m_pEntryGrid->getEntries()) {	if (pGridRow->getRowIndex() <= uiValue1)	vecIMGEntries.push_back((IMGEntry*)pGridRow->getUserData());	Events::trigger(TASK_PROGRESS); }
			break;
		case 6: // More than or equal to
			for (GridRow *pGridRow : m_pEntryGrid->getEntries()) {	if (pGridRow->getRowIndex() >= uiValue1)	vecIMGEntries.push_back((IMGEntry*)pGridRow->getUserData());	Events::trigger(TASK_PROGRESS); }
			break;
		}
		break;
	case 1: // Name
		break;
	case 2: // Offset
		switch (uiMatchType)
		{
		case 0: // Equal to
			for (IMGEntry *pIMGEntry : m_pIMGFile->getEntries()) {	if (pIMGEntry->getEntryOffset() == uiValue1)	vecIMGEntries.push_back(pIMGEntry);		Events::trigger(TASK_PROGRESS); }
			break;
		case 1: // Not equal to
			for (IMGEntry *pIMGEntry : m_pIMGFile->getEntries()) {	if (pIMGEntry->getEntryOffset() != uiValue1)	vecIMGEntries.push_back(pIMGEntry);		Events::trigger(TASK_PROGRESS); }
			break;
		case 2: // Between
			for (IMGEntry *pIMGEntry : m_pIMGFile->getEntries()) {	if (pIMGEntry->getEntryOffset() >= uiValue1 && pIMGEntry->getEntryOffset() <= uiValue2)	vecIMGEntries.push_back(pIMGEntry);		Events::trigger(TASK_PROGRESS); }
			break;
		case 3: // Less than
			for (IMGEntry *pIMGEntry : m_pIMGFile->getEntries()) {	if (pIMGEntry->getEntryOffset() < uiValue1)		vecIMGEntries.push_back(pIMGEntry);		Events::trigger(TASK_PROGRESS); }
			break;
		case 4: // More than
			for (IMGEntry *pIMGEntry : m_pIMGFile->getEntries()) {	if (pIMGEntry->getEntryOffset() > uiValue1)		vecIMGEntries.push_back(pIMGEntry);		Events::trigger(TASK_PROGRESS); }
			break;
		case 5: // Less than or equal to
			for (IMGEntry *pIMGEntry : m_pIMGFile->getEntries()) {	if (pIMGEntry->getEntryOffset() <= uiValue1)	vecIMGEntries.push_back(pIMGEntry);		Events::trigger(TASK_PROGRESS); }
			break;
		case 6: // More than or equal to
			for (IMGEntry *pIMGEntry : m_pIMGFile->getEntries()) {	if (pIMGEntry->getEntryOffset() >= uiValue1)	vecIMGEntries.push_back(pIMGEntry);		Events::trigger(TASK_PROGRESS); }
			break;
		}
		break;
	case 3: // Size
		switch (uiMatchType)
		{
		case 0: // Equal to
			for (IMGEntry *pIMGEntry : m_pIMGFile->getEntries()) {	if (pIMGEntry->getEntrySize() == uiValue1)		vecIMGEntries.push_back(pIMGEntry);		Events::trigger(TASK_PROGRESS); }
			break;
		case 1: // Not equal to
			for (IMGEntry *pIMGEntry : m_pIMGFile->getEntries()) {	if (pIMGEntry->getEntrySize() != uiValue1)		vecIMGEntries.push_back(pIMGEntry);		Events::trigger(TASK_PROGRESS); }
			break;
		case 2: // Between
			for (IMGEntry *pIMGEntry : m_pIMGFile->getEntries()) {	if (pIMGEntry->getEntrySize() >= uiValue1 && pIMGEntry->getEntrySize() <= uiValue2)	vecIMGEntries.push_back(pIMGEntry);		Events::trigger(TASK_PROGRESS); }
			break;
		case 3: // Less than
			for (IMGEntry *pIMGEntry : m_pIMGFile->getEntries()) {	if (pIMGEntry->getEntrySize() < uiValue1)		vecIMGEntries.push_back(pIMGEntry);		Events::trigger(TASK_PROGRESS); }
			break;
		case 4: // More than
			for (IMGEntry *pIMGEntry : m_pIMGFile->getEntries()) {	if (pIMGEntry->getEntrySize() > uiValue1)		vecIMGEntries.push_back(pIMGEntry);		Events::trigger(TASK_PROGRESS); }
			break;
		case 5: // Less than or equal to
			for (IMGEntry *pIMGEntry : m_pIMGFile->getEntries()) {	if (pIMGEntry->getEntrySize() <= uiValue1)		vecIMGEntries.push_back(pIMGEntry);		Events::trigger(TASK_PROGRESS); }
			break;
		case 6: // More than or equal to
			for (IMGEntry *pIMGEntry : m_pIMGFile->getEntries()) {	if (pIMGEntry->getEntrySize() >= uiValue1)		vecIMGEntries.push_back(pIMGEntry);		Events::trigger(TASK_PROGRESS); }
			break;
		}
		break;
	case 4: // Type
		break;
	case 5: // Version
		switch (uiMatchType)
		{
		case 0: // Equal to
			for (IMGEntry *pIMGEntry : m_pIMGFile->getEntries()) {	if (pIMGEntry->getRawVersion() == uiValue1)		vecIMGEntries.push_back(pIMGEntry);		Events::trigger(TASK_PROGRESS); }
			break;
		case 1: // Not equal to
			for (IMGEntry *pIMGEntry : m_pIMGFile->getEntries()) {	if (pIMGEntry->getRawVersion() != uiValue1)		vecIMGEntries.push_back(pIMGEntry);		Events::trigger(TASK_PROGRESS); }
			break;
		case 2: // Between
			for (IMGEntry *pIMGEntry : m_pIMGFile->getEntries()) {	if (pIMGEntry->getRawVersion() >= uiValue1 && pIMGEntry->getRawVersion() <= uiValue2)	vecIMGEntries.push_back(pIMGEntry);		Events::trigger(TASK_PROGRESS); }
			break;
		case 3: // Less than
			for (IMGEntry *pIMGEntry : m_pIMGFile->getEntries()) {	if (pIMGEntry->getRawVersion() < uiValue1)		vecIMGEntries.push_back(pIMGEntry);		Events::trigger(TASK_PROGRESS); }
			break;
		case 4: // More than
			for (IMGEntry *pIMGEntry : m_pIMGFile->getEntries()) {	if (pIMGEntry->getRawVersion() > uiValue1)		vecIMGEntries.push_back(pIMGEntry);		Events::trigger(TASK_PROGRESS); }
			break;
		case 5: // Less than or equal to
			for (IMGEntry *pIMGEntry : m_pIMGFile->getEntries()) {	if (pIMGEntry->getRawVersion() <= uiValue1)		vecIMGEntries.push_back(pIMGEntry);		Events::trigger(TASK_PROGRESS); }
			break;
		case 6: // More than or equal to
			for (IMGEntry *pIMGEntry : m_pIMGFile->getEntries()) {	if (pIMGEntry->getRawVersion() >= uiValue1)		vecIMGEntries.push_back(pIMGEntry);		Events::trigger(TASK_PROGRESS); }
			break;
		}
		break;
	}
	return vecIMGEntries;
}

vector<IMGEntry*>		IMGEditorTab::getEntriesByStringMultiOptionValues(uint32 uiEntryAttribute, uint32 uiMatchType, string& strValue1, string& strValue2, bool bMatchWildcard)
{
	vector<IMGEntry*>
		vecIMGEntries;
	string
		strValue1Lower = String::toLowerCase(strValue1),
		strValue2Lower = String::toLowerCase(strValue2);
	switch (uiEntryAttribute)
	{
	case 1: // Name
		if (bMatchWildcard)
		{
			// Wildcard
			switch (uiMatchType)
			{
			case 0: // Equal to
				for (IMGEntry *pIMGEntry : m_pIMGFile->getEntries()) {	if (String::isIn(String::toLowerCase(pIMGEntry->getEntryName()), strValue1Lower))		vecIMGEntries.push_back(pIMGEntry);		Events::trigger(TASK_PROGRESS); }
				break;
			case 1: // Not equal to
				for (IMGEntry *pIMGEntry : m_pIMGFile->getEntries()) {	if (String::isIn(String::toLowerCase(pIMGEntry->getEntryName()), strValue1Lower))		vecIMGEntries.push_back(pIMGEntry);		Events::trigger(TASK_PROGRESS); }
				break;
			case 2: // Between
				for (IMGEntry *pIMGEntry : m_pIMGFile->getEntries()) {	if (String::isIn(String::toLowerCase(pIMGEntry->getEntryName()), strValue1Lower) && String::isIn(String::toLowerCase(pIMGEntry->getEntryName()), strValue2Lower))	vecIMGEntries.push_back(pIMGEntry);		Events::trigger(TASK_PROGRESS); }
				break;
			case 3: // Less than
				for (IMGEntry *pIMGEntry : m_pIMGFile->getEntries()) {	if (String::isIn(String::toLowerCase(pIMGEntry->getEntryName()), strValue1Lower))		vecIMGEntries.push_back(pIMGEntry);		Events::trigger(TASK_PROGRESS); }
				break;
			case 4: // More than
				for (IMGEntry *pIMGEntry : m_pIMGFile->getEntries()) {	if (String::isIn(String::toLowerCase(pIMGEntry->getEntryName()), strValue1Lower))		vecIMGEntries.push_back(pIMGEntry);		Events::trigger(TASK_PROGRESS); }
				break;
			case 5: // Less than or equal to
				for (IMGEntry *pIMGEntry : m_pIMGFile->getEntries()) {	if (String::isIn(String::toLowerCase(pIMGEntry->getEntryName()), strValue1Lower))		vecIMGEntries.push_back(pIMGEntry);		Events::trigger(TASK_PROGRESS); }
				break;
			case 6: // More than or equal to
				for (IMGEntry *pIMGEntry : m_pIMGFile->getEntries()) {	if (String::isIn(String::toLowerCase(pIMGEntry->getEntryName()), strValue1Lower))		vecIMGEntries.push_back(pIMGEntry);		Events::trigger(TASK_PROGRESS); }
				break;
			}
		}
		else
		{
			// Not Wildcard
			switch (uiMatchType)
			{
			case 0: // Equal to
				for (IMGEntry *pIMGEntry : m_pIMGFile->getEntries()) {	if (String::toLowerCase(pIMGEntry->getEntryName()) == strValue1Lower)		vecIMGEntries.push_back(pIMGEntry);		Events::trigger(TASK_PROGRESS); }
				break;
			case 1: // Not equal to
				for (IMGEntry *pIMGEntry : m_pIMGFile->getEntries()) {	if (String::toLowerCase(pIMGEntry->getEntryName()) != strValue1Lower)		vecIMGEntries.push_back(pIMGEntry);		Events::trigger(TASK_PROGRESS); }
				break;
			case 2: // Between
				for (IMGEntry *pIMGEntry : m_pIMGFile->getEntries()) {	if (String::toLowerCase(pIMGEntry->getEntryName()) >= strValue1Lower && String::toLowerCase(pIMGEntry->getEntryName()) <= strValue2Lower)	vecIMGEntries.push_back(pIMGEntry);		Events::trigger(TASK_PROGRESS); }
				break;
			case 3: // Less than
				for (IMGEntry *pIMGEntry : m_pIMGFile->getEntries()) {	if (String::toLowerCase(pIMGEntry->getEntryName()) < strValue1Lower)		vecIMGEntries.push_back(pIMGEntry);		Events::trigger(TASK_PROGRESS); }
				break;
			case 4: // More than
				for (IMGEntry *pIMGEntry : m_pIMGFile->getEntries()) {	if (String::toLowerCase(pIMGEntry->getEntryName()) > strValue1Lower)		vecIMGEntries.push_back(pIMGEntry);		Events::trigger(TASK_PROGRESS); }
				break;
			case 5: // Less than or equal to
				for (IMGEntry *pIMGEntry : m_pIMGFile->getEntries()) {	if (String::toLowerCase(pIMGEntry->getEntryName()) <= strValue1Lower)		vecIMGEntries.push_back(pIMGEntry);		Events::trigger(TASK_PROGRESS); }
				break;
			case 6: // More than or equal to
				for (IMGEntry *pIMGEntry : m_pIMGFile->getEntries()) {	if (String::toLowerCase(pIMGEntry->getEntryName()) >= strValue1Lower)		vecIMGEntries.push_back(pIMGEntry);		Events::trigger(TASK_PROGRESS); }
				break;
			}
		}
		break;
	case 4: // Type
		if (bMatchWildcard)
		{
			// Wildcard
			switch (uiMatchType)
			{
			case 0: // Equal to
				for (IMGEntry *pIMGEntry : m_pIMGFile->getEntries()) {	if (String::isIn(String::toLowerCase(pIMGEntry->getEntryExtension()), strValue1Lower))		vecIMGEntries.push_back(pIMGEntry);		Events::trigger(TASK_PROGRESS); }
				break;
			case 1: // Not equal to
				for (IMGEntry *pIMGEntry : m_pIMGFile->getEntries()) {	if (String::isIn(String::toLowerCase(pIMGEntry->getEntryExtension()), strValue1Lower))		vecIMGEntries.push_back(pIMGEntry);		Events::trigger(TASK_PROGRESS); }
				break;
			case 2: // Between
				for (IMGEntry *pIMGEntry : m_pIMGFile->getEntries()) {	if (String::isIn(String::toLowerCase(pIMGEntry->getEntryExtension()), strValue1Lower) && String::isIn(String::toLowerCase(pIMGEntry->getEntryExtension()), strValue2Lower))		vecIMGEntries.push_back(pIMGEntry);		Events::trigger(TASK_PROGRESS); }
				break;
			case 3: // Less than
				for (IMGEntry *pIMGEntry : m_pIMGFile->getEntries()) {	if (String::isIn(String::toLowerCase(pIMGEntry->getEntryExtension()), strValue1Lower))		vecIMGEntries.push_back(pIMGEntry);		Events::trigger(TASK_PROGRESS); }
				break;
			case 4: // More than
				for (IMGEntry *pIMGEntry : m_pIMGFile->getEntries()) {	if (String::isIn(String::toLowerCase(pIMGEntry->getEntryExtension()), strValue1Lower))		vecIMGEntries.push_back(pIMGEntry);		Events::trigger(TASK_PROGRESS); }
				break;
			case 5: // Less than or equal to
				for (IMGEntry *pIMGEntry : m_pIMGFile->getEntries()) {	if (String::isIn(String::toLowerCase(pIMGEntry->getEntryExtension()), strValue1Lower))		vecIMGEntries.push_back(pIMGEntry);		Events::trigger(TASK_PROGRESS); }
				break;
			case 6: // More than or equal to
				for (IMGEntry *pIMGEntry : m_pIMGFile->getEntries()) {	if (String::isIn(String::toLowerCase(pIMGEntry->getEntryExtension()), strValue1Lower))		vecIMGEntries.push_back(pIMGEntry);		Events::trigger(TASK_PROGRESS); }
				break;
			}
		}
		else
		{
			// Not Wildcard
			switch (uiMatchType)
			{
			case 0: // Equal to
				for (IMGEntry *pIMGEntry : m_pIMGFile->getEntries()) {	if (String::toLowerCase(pIMGEntry->getEntryExtension()) == strValue1Lower)		vecIMGEntries.push_back(pIMGEntry);		Events::trigger(TASK_PROGRESS); }
				break;
			case 1: // Not equal to
				for (IMGEntry *pIMGEntry : m_pIMGFile->getEntries()) {	if (String::toLowerCase(pIMGEntry->getEntryExtension()) != strValue1Lower)		vecIMGEntries.push_back(pIMGEntry);		Events::trigger(TASK_PROGRESS); }
				break;
			case 2: // Between
				for (IMGEntry *pIMGEntry : m_pIMGFile->getEntries()) {	if (String::toLowerCase(pIMGEntry->getEntryExtension()) >= strValue1Lower && String::toLowerCase(pIMGEntry->getEntryExtension()) <= strValue2Lower)		vecIMGEntries.push_back(pIMGEntry);		Events::trigger(TASK_PROGRESS); }
				break;
			case 3: // Less than
				for (IMGEntry *pIMGEntry : m_pIMGFile->getEntries()) {	if (String::toLowerCase(pIMGEntry->getEntryExtension()) < strValue1Lower)		vecIMGEntries.push_back(pIMGEntry);		Events::trigger(TASK_PROGRESS); }
				break;
			case 4: // More than
				for (IMGEntry *pIMGEntry : m_pIMGFile->getEntries()) {	if (String::toLowerCase(pIMGEntry->getEntryExtension()) > strValue1Lower)		vecIMGEntries.push_back(pIMGEntry);		Events::trigger(TASK_PROGRESS); }
				break;
			case 5: // Less than or equal to
				for (IMGEntry *pIMGEntry : m_pIMGFile->getEntries()) {	if (String::toLowerCase(pIMGEntry->getEntryExtension()) <= strValue1Lower)		vecIMGEntries.push_back(pIMGEntry);		Events::trigger(TASK_PROGRESS); }
				break;
			case 6: // More than or equal to
				for (IMGEntry *pIMGEntry : m_pIMGFile->getEntries()) {	if (String::toLowerCase(pIMGEntry->getEntryExtension()) >= strValue1Lower)		vecIMGEntries.push_back(pIMGEntry);		Events::trigger(TASK_PROGRESS); }
				break;
			}
		}
		break;
	}
	return vecIMGEntries;
}

// rebuild
void					IMGEditorTab::rebuild(string strIMGPath, bool bLog)
{
	getIMGF()->getTaskManager()->setTaskMaxProgressTickCount(getIMGFile()->getEntryCount() * 3);
	getIMGFile()->serialize(strIMGPath == "" ? getIMGFile()->getFilePath() : strIMGPath);
	setFileUnsaved(false);
	if (bLog)
	{
		log(LocalizationManager::get()->getTranslatedText("Log_127"));
	}
}
uint32			IMGEditorTab::merge(string strPath, vector<string>& vecImportedEntryNames)
{
	return getIMGFile()->merge(strPath, vecImportedEntryNames);
}

void					IMGEditorTab::splitSelectedEntries(string strNewFilePath, EIMGVersion uiNewIMGVersion, bool bDeleteFromSource)
{
	getIMGFile()->split((vector<IMGEntry*>&)getSelectedEntries(), strNewFilePath, uiNewIMGVersion);

	if (bDeleteFromSource)
	{
		removeSelectedEntries();
	}
}

void					IMGEditorTab::replace(vector<string>& vecPaths, vector<string>& vecReplacedEntryNames)
{
	vector<IMGEntry*> vecReplacedEntries;
	uint32 uiReplaceCount = getIMGFile()->replaceEntries(vecPaths, vecReplacedEntryNames, vecReplacedEntries);

	for (auto pIMGEntry : vecReplacedEntries)
	{
		getIMGF()->getEntryListTab()->onEntryChange(pIMGEntry);
	}
}
bool					sortStdVectorAzCaseInsensitive(SearchEntry *pSearchEntry1, SearchEntry *pSearchEntry2)
{
	return strcmp(pSearchEntry1->getIMGEntry()->getEntryName().c_str(), pSearchEntry2->getIMGEntry()->getEntryName().c_str()) < 0;
}
void					IMGEditorTab::searchText(void)
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

	string strSearchText = String::toUpperCase(m_strSearchText);
	bool bAllTabs = ((Button*)getIMGF()->getDialog()->GetDlgItem(46))->GetCheck() == BST_CHECKED;

	if (strSearchText == "")
	{
		((CStatic*)getIMGF()->getDialog()->GetDlgItem(0))->SetWindowTextW(LocalizationManager::get()->getTranslatedFormattedTextW("Window_Main_Text_SearchResult_ActiveTab", 0).c_str());
		return;
	}

	vector<EditorTab*> vecEditorTabs;
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
		for (auto pIMGEntry : ((IMGEditorTab*)pEditorTab)->getIMGFile()->getEntries())
		{
			string strEntryExtension = String::toUpperCase(Path::getFileExtension(pIMGEntry->getEntryName()));
			bool bMatch = false;
			if (String::toUpperCase(pIMGEntry->getEntryName()).find(strSearchText) != string::npos)
			{
				bMatch = true;
			}
			else if (String::toString(pIMGEntry->getEntryOffsetInSectors() * 2048).find(strSearchText) != string::npos)
			{
				bMatch = true;
			}
			else if (String::toString(pIMGEntry->getEntrySize()).find(strSearchText) != string::npos)
			{
				bMatch = true;
			}
			else
			{
				if (strEntryExtension == "COL")
				{
					if (String::toUpperCase(COLManager::get()->getCOLVersionText(pIMGEntry->getCOLVersion())).find(strSearchText) != string::npos)
					{
						bMatch = true;
					}
				}
				else if (strEntryExtension == "TXD" || Path::isModelExtension(strEntryExtension))
				{
					if (pIMGEntry->getRWVersion() == nullptr)
					{
						string strText1 = "Unknown";
						if (String::toUpperCase(strText1).find(strSearchText) != string::npos)
						{
							bMatch = true;
						}
					}
					else
					{
						if (String::toUpperCase(pIMGEntry->getRWVersion()->getVersionText() + " (" + LocalizationManager::get()->getTranslatedText(pIMGEntry->getRWVersion()->getLocalizationKey()) + ")").find(strSearchText) != string::npos)
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

				SearchEntry *pSearchEntry = new SearchEntry;
				pSearchEntry->setWindowTab((IMGEditorTab*)pEditorTab);
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
		IMGEntry *pIMGEntry = pSearchEntry->getIMGEntry();
		uint32 uiRowIndex = pListControl->GetItemCount();
		string strEntryExtension = String::toUpperCase(Path::getFileExtension(pIMGEntry->getEntryName()));
		string strExtraInfo;
		if (strEntryExtension == "COL")
		{
			strExtraInfo = COLManager::getCOLVersionText(pIMGEntry->getCOLVersion());
		}
		else if (strEntryExtension == "TXD" || Path::isModelExtension(strEntryExtension))
		{
			strExtraInfo = pIMGEntry->getRWVersion() == nullptr ? LocalizationManager::get()->getTranslatedText("Window_Main_Combo_RWVersion_Unknown") : pIMGEntry->getRWVersion()->getVersionText() + " (" + LocalizationManager::get()->getTranslatedText(pIMGEntry->getRWVersion()->getLocalizationKey()) + ")";
		}
		pListControl->InsertItem(LVIF_TEXT | LVIF_PARAM, uiRowIndex, String::convertStdStringToStdWString(pIMGEntry->getEntryName()).c_str(), 0, 0, 0, (DWORD)pSearchEntry);
		pListControl->SetItem(uiRowIndex, 1, LVIF_TEXT, String::convertStdStringToStdWString(Path::getFileName(pSearchEntry->getWindowTab()->getIMGFile()->getFilePath())).c_str(), 0, 0, 0, 0);
		pListControl->SetItem(uiRowIndex, 2, LVIF_TEXT, String::convertStdStringToStdWString(strExtraInfo).c_str(), 0, 0, 0, 0);
	}

	// result text
	wstring wstrSearchResultText;
	if (bAllTabs)
	{
		wstrSearchResultText = LocalizationManager::get()->getTranslatedFormattedTextW("Window_Main_Text_SearchResult_AllTabs", uiMatchCount, uiFileCountWithMatches);
	}
	else
	{
		wstrSearchResultText = LocalizationManager::get()->getTranslatedFormattedTextW("Window_Main_Text_SearchResult_ActiveTab", uiMatchCount);
	}

	((CStatic*)getIMGF()->getDialog()->GetDlgItem(0))->SetWindowTextW(wstrSearchResultText.c_str());
	pListControlMain->SetFocus();

	getIMGF()->getIMGEditor()->setSearchHitCount(uiMatchCount);
	getIMGF()->getIMGEditor()->setSearchFileCount(uiFileCountWithMatches);
	*/
}

void					IMGEditorTab::storeFilterOptions(void)
{
	/*
	todo
	CComboBox *pComboBox1 = (CComboBox*)getIMGF()->getDialog()->GetDlgItem(54);
	CComboBox *pComboBox2 = (CComboBox*)getIMGF()->getDialog()->GetDlgItem(5);
	::CString cstr1, cstr2;
	pComboBox1->GetWindowTextW(cstr1);
	pComboBox2->GetWindowTextW(cstr2);
	setActiveFilter("type", String::convertCStringToStdString(cstr1));
	setActiveFilter("version", String::convertCStringToStdString(cstr2));
	*/
}
void					IMGEditorTab::restoreFilterOptions(void)
{
	/*
	todo
	m_bRestoringFilterOptions = true;
	((Button*)getIMGF()->getDialog()->GetDlgItem(44))->SetCheck(m_filterOptions.m_bCheckboxes[0] ? BST_CHECKED : BST_UNCHECKED);
	((Button*)getIMGF()->getDialog()->GetDlgItem(3))->SetCheck(m_filterOptions.m_bCheckboxes[1] ? BST_CHECKED : BST_UNCHECKED);
	((Button*)getIMGF()->getDialog()->GetDlgItem(4))->SetCheck(m_filterOptions.m_bCheckboxes[2] ? BST_CHECKED : BST_UNCHECKED);
	((Button*)getIMGF()->getDialog()->GetDlgItem(10))->SetCheck(m_filterOptions.m_bCheckboxes[3] ? BST_CHECKED : BST_UNCHECKED);
	((CComboBox*)getIMGF()->getDialog()->GetDlgItem(7))->SetCurSel(m_filterOptions.m_iComboBoxes[0]);
	((CComboBox*)getIMGF()->getDialog()->GetDlgItem(6))->SetCurSel(m_filterOptions.m_iComboBoxes[1]);
	((CComboBox*)getIMGF()->getDialog()->GetDlgItem(5))->SetCurSel(m_filterOptions.m_iComboBoxes[2]);
	((CEdit*)getIMGF()->getDialog()->GetDlgItem(9))->SetWindowTextW(String::convertStdStringToStdWString(m_filterOptions.m_strEditBoxes[0]).c_str());
	((CEdit*)getIMGF()->getDialog()->GetDlgItem(8))->SetWindowTextW(String::convertStdStringToStdWString(m_filterOptions.m_strEditBoxes[1]).c_str());
	((CEdit*)getIMGF()->getDialog()->GetDlgItem(48))->SetWindowTextW(String::convertStdStringToStdWString(m_filterOptions.m_strEditBoxes[2]).c_str());
	m_bRestoringFilterOptions = false;
	*/
}
bool					IMGEditorTab::isFilterActive(void)
{
	/*
	todo
	bool bFilterCheckBox_Offset = ((Button*)getIMGF()->getDialog()->GetDlgItem(44))->GetCheck() == BST_CHECKED;
	bool bFilterCheckBox_Size = ((Button*)getIMGF()->getDialog()->GetDlgItem(3))->GetCheck() == BST_CHECKED;
	bool bFilterCheckBox_RWVersion = ((Button*)getIMGF()->getDialog()->GetDlgItem(4))->GetCheck() == BST_CHECKED;
	bool bFilterCheckBox_Extensions = ((Button*)getIMGF()->getDialog()->GetDlgItem(10))->GetCheck() == BST_CHECKED;
	
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

void					IMGEditorTab::sortEntries(void)
{
	// sort
	getIMGF()->getSortManager()->sort(getIMGFile());

	// log
	vector<string> vecExtendedLogLines;
	SortPriorities *pSortPriorities = getIMGF()->getSortManager()->getSortPriorities();
	uint32 i = 0;
	SortPriority *pSortPriority2 = nullptr;
	for (auto pSortPriority : pSortPriorities->getEntries())
	{
		if (!pSortPriority->isEnabled())
		{
			break;
		}
		vecExtendedLogLines.push_back(LocalizationManager::get()->getTranslatedFormattedText("Sort_Priority_N_WithName", (i + 1), pSortPriority->getType()->getText().c_str()));
		i++;
		pSortPriority2 = pSortPriority;
	}
	if (vecExtendedLogLines.size() == 1)
	{
		log(LocalizationManager::get()->getTranslatedFormattedText("Log_129", pSortPriority2->getType()->getText().c_str()));
	}
	else
	{
		log(LocalizationManager::get()->getTranslatedFormattedText("Log_130", vecExtendedLogLines.size()));
	}
	// todo - log(LocalizationManager::get()->getTranslatedText("Log_131"), true);
	// todo - log(String::join(vecExtendedLogLines, "\n"), true);

	// render
	readdGridEntries();

	// post
	setFileUnsaved(true);
}

void					IMGEditorTab::onEntryChange(IMGEntry *pIMGEntry)
{
	loadProtectedEntryState(pIMGEntry);
}

void					IMGEditorTab::loadProtectedEntryState(IMGEntry *pIMGEntry)
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
void				IMGEditorTab::loadProtectedEntryStates(void)
{
	for (auto pIMGEntry : getIMGFile()->getEntries())
	{
		loadProtectedEntryState(pIMGEntry);
	}
}

void				IMGEditorTab::loadFilter_Type(void)
{
	m_pEntryTypeFilter->reset();
	m_pEntryTypeFilter->addItem("All Types");

	DropDownItem *pDropEntry;
	for (auto it : m_pIMGFile->getFileTypesAsMap())
	{
		pDropEntry = m_pEntryTypeFilter->addItem(it.first); // file type text (e.g. "Animation (IFP)")
		pDropEntry->setUserdata(it.second); // file type id
	}
}
void				IMGEditorTab::loadFilter_Version(void)
{
	m_pEntryVersionFilter->reset();
	m_pEntryVersionFilter->addItem("All Versions");

	DropDownItem *pDropEntry;
	for (auto it : m_pIMGFile->getFileTypedVersionsAsMap())
	{
		pDropEntry = m_pEntryVersionFilter->addItem(it.first); // file version text
		pDropEntry->setUserdata(it.second.first); // file version id
		pDropEntry->setUserdata2(it.second.second); // file type id for file version
	}
}

void				IMGEditorTab::unloadFilter_Type(void)
{
	/*
	todo
	CComboBox *pComboBox = (CComboBox*)getIMGF()->getDialog()->GetDlgItem(54);

	for (uint32 i = 0, j = pComboBox->GetCount(); i < j; i++)
	{
		pComboBox->DeleteString(0);
	}

	pComboBox->InsertString(0, LocalizationManager::get()->getTranslatedTextW("AllTypes").c_str());

	pComboBox->SetCurSel(0);
	*/
}
void				IMGEditorTab::unloadFilter_Version(void)
{
	/*
	todo
	CComboBox *pComboBox = (CComboBox*)getIMGF()->getDialog()->GetDlgItem(5);

	for (uint32 i = 0, j = pComboBox->GetCount(); i < j; i++)
	{
		pComboBox->DeleteString(0);
	}

	pComboBox->InsertString(0, LocalizationManager::get()->getTranslatedTextW("AllVersions").c_str());

	pComboBox->SetCurSel(0);
	*/
}

void				IMGEditorTab::reassignEntryIds(void)
{
	uint32 i = 1;
	for (GridRow *pRow : m_pEntryGrid->getEntries())
	{
		pRow->getText()[0][0] = String::addNumberGrouping(String::toString(i++));
	}
}

vector<FormatEntry*>	IMGEditorTab::getSelectedEntries(void)
{
	vector<IMGEntry*> vecIMGEntries;
	for (GridRow *pGridRow : m_pEntryGrid->getEntries())
	{
		if (pGridRow->isShown() && pGridRow->isSelected())
		{
			vecIMGEntries.push_back((IMGEntry*)pGridRow->getUserData());
		}
	}
	return (vector<FormatEntry*>&)vecIMGEntries;
}

uint32				IMGEditorTab::getSelectedEntryCount(void)
{
	uint32 uiSelectedEntryCount = 0;
	for (GridRow *pGridRow : m_pEntryGrid->getEntries())
	{
		if (pGridRow->isSelected())
		{
			uiSelectedEntryCount++;
		}
	}
	return uiSelectedEntryCount;
}

void				IMGEditorTab::setSelectedEntriesNameCase(uint32 uiNameCaseType)
{
	for (GridRow *pGridRow : m_pEntryGrid->getEntries())
	{
		if (pGridRow->isSelected())
		{
			IMGEntry *pIMGEntry = (IMGEntry*)pGridRow->getUserData();
			string strNewEntryName;
			switch (uiNameCaseType)
			{
			case 0: // lower case
				strNewEntryName = String::toLowerCase(pIMGEntry->getEntryName());
				break;
			case 1: // UPPER CASE
				strNewEntryName = String::toUpperCase(pIMGEntry->getEntryName());
				break;
			case 2: // Title Case
				strNewEntryName = String::toTitleCase(pIMGEntry->getEntryName());
				break;
			}
			pIMGEntry->setEntryName(strNewEntryName);
			updateGridEntry(pIMGEntry);
		}
	}

	setFileUnsaved(true);
}

void				IMGEditorTab::copySelectedEntryData(uint32 uiColumnType)
{
	vector<string> vecCopyLines;
	for (GridRow *pGridRow : m_pEntryGrid->getEntries())
	{
		if (pGridRow->isSelected())
		{
			IMGEntry *pIMGEntry = (IMGEntry*)pGridRow->getUserData();

			switch (uiColumnType)
			{
			case 0: // Index
				vecCopyLines.push_back(String::toString(pGridRow->getRowIndex()));
				break;
			case 1: // Type
				vecCopyLines.push_back(pIMGEntry->getEntryExtension());
				break;
			case 2: // Name
				vecCopyLines.push_back(pIMGEntry->getEntryName());
				break;
			case 3: // Offset
				vecCopyLines.push_back(String::toString(pIMGEntry->getEntryOffset()));
				break;
			case 4: // Size
				vecCopyLines.push_back(String::toString(pIMGEntry->getEntrySize()));
				break;
			case 5: // Version
				vecCopyLines.push_back(pIMGEntry->getVersionText());
				break;
			case 6: // All Row Data
				vecCopyLines.push_back(
					String::toString(pGridRow->getRowIndex()) + "," +
					pIMGEntry->getEntryExtension() + "," +
					pIMGEntry->getEntryName() + "," +
					String::toString(pIMGEntry->getEntryOffset()) + "," +
					String::toString(pIMGEntry->getEntrySize()) + "," +
					pIMGEntry->getVersionText()
				);
				break;
			}
		}
	}
	String::setClipboardText(String::join(vecCopyLines, "\r\n"));
}

void				IMGEditorTab::shiftSelectedEntries(int32 uiRowCountOffset)
{
	for (GridRow *pGridRow1 : m_pEntryGrid->getSelectedRows())
	{
		int32 iEntry1Index = m_pEntryGrid->getIndexByEntry(pGridRow1);
		int32 iEntry2Index = Math::limit(iEntry1Index + (int32)uiRowCountOffset, 0, (int32)m_pEntryGrid->getEntryCount());

		GridRow *pGridRow2 = m_pEntryGrid->getEntryByIndex(iEntry2Index);

		m_pEntryGrid->swapEntries(pGridRow1, pGridRow2);
		updateGridEntry((IMGEntry*)pGridRow1->getUserData());
		updateGridEntry((IMGEntry*)pGridRow2->getUserData());
	}

	setFileUnsaved(true);
}

uint32				IMGEditorTab::getTotalEntryCount(void)
{
	return m_pIMGFile->getEntryCount();
}

void				IMGEditorTab::onEntryChange(FormatEntry *pEntry)
{
	updateGridEntry((IMGEntry*)pEntry);

	readdGridEntries(); // for search text
}