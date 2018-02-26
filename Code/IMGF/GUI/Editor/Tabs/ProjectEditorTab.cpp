#include "ProjectEditorTab.h"
#include "Format/DAT/Loader/DATLoaderFormat.h"
#include "Window/Window.h"
#include "IMGF.h"
#include "Task/Tasks/RecentlyOpen/RecentlyOpenManager.h"
#include "Static/File.h"
#include "Control/Controls/TextBox.h"
#include "Control/Controls/Text.h"
#include "Game/GameManager.h"
#include "GUI/Editor/Base/Editor.h"
#include "GUI/Window/Windows/MainWindow/MainWindow.h"
#include "Event/EInputEvent.h"
#include "Format/IDE/IDEFormat.h"
#include "Format/IDE/IDEEntry.h"
#include "Format/IPL/IPLFormat.h"
#include "Format/IPL/IPLEntry.h"

using namespace std;
using namespace bxcf;
using namespace bxgi;
using namespace bxgx;
using namespace bxgx::events;
using namespace imgf;

ProjectEditorTab::ProjectEditorTab(void) :
	m_pDATFile(nullptr),
	m_pTextBox(nullptr)
{
}

// controls
void						ProjectEditorTab::storeControls(void)
{
	m_pTextBox = (TextBox*)getLayer()->getItemById(1100);
}

// layer
void						ProjectEditorTab::initLayer(void)
{
	setLayer(m_pEditor->getMainWindow()->getLayerById(8248));
}

// events
void						ProjectEditorTab::bindEvents(void)
{
	bindDefaultEvent(CHANGE_TEXT_BOX, &DATEditorTab::onChangeTextBox);

	EditorTab::bindEvents();
}

void						ProjectEditorTab::unbindEvents(void)
{
	unbindDefaultEvent(CHANGE_TEXT_BOX, &DATEditorTab::onChangeTextBox);

	EditorTab::unbindEvents();
}

// file loading
bool						ProjectEditorTab::unserializeFile(void)
{
	return m_pDATFile->unserialize();
}

void						ProjectEditorTab::onFileLoaded(void)
{
	// update tab text
	updateTabText();

	// show file content
	m_pTextBox->getTextLines() = String::split(String::fixEOLs(File::getTextFile(getFile()->getFilePath()), "\n"), "\n");
	if (m_pTextBox->getTextLines().size() == 0)
	{
		m_pTextBox->getTextLines().push_back("");
	}

	// display file info
	setFileInfoText();

	// start
	start();

	// render
	getLayer()->getWindow()->render();
}

// file info text
void						ProjectEditorTab::setFileInfoText(void)
{
	m_pText_FilePath->setText(Path::getDisplayableFilePath(getDATFile()->getFilePath()));
	m_pText_FileGame->setText(GameManager::get()->getGameName(getDATFile()->getGame()));
	m_pText_FileVersion->setText(getDATFile()->getVersion() == -1 ? "Unknown Version" : String::toString(getDATFile()->getVersion()));

	updateEntryCountText();
}

void						ProjectEditorTab::updateEntryCountText(void)
{
	uint32
		uiDisplayedEntryCount = m_pTextBox->getTextLines().size(),
		uiTotalEntryCount = uiDisplayedEntryCount;
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

// event callbacks
void						ProjectEditorTab::onChangeTextBox(TextBox *pTextBox)
{
	if (pTextBox == m_pTextBox)
	{
		setFileUnsaved(true);
	}
}

// entry selection
void						ProjectEditorTab::setAllLinesSelected(bool bIsSelected)
{
	if (bIsSelected)
	{
		m_pTextBox->selectAllText();
	}
	else
	{
		m_pTextBox->unselectAllText();
	}
}

vector<string>				ProjectEditorTab::getSelectedTextLines(void)
{
	vector<string> vecTextLines;
	for (int32 iLine = m_pTextBox->getCaretPositionStart().y, iLineEnd = m_pTextBox->getCaretPositionEnd().y; iLine <= iLineEnd; iLine++)
	{
		vecTextLines.push_back(m_pTextBox->getTextAtLine(iLine));
	}
	return vecTextLines;
}

uint32						ProjectEditorTab::getSelectedEntryCount(void)
{
	if (m_pTextBox->getCaretPositionStart().x == m_pTextBox->getCaretPositionEnd().x && m_pTextBox->getCaretPositionStart().y == m_pTextBox->getCaretPositionEnd().y)
	{
		return 0;
	}
	else
	{
		return (m_pTextBox->getCaretPositionEnd().y - m_pTextBox->getCaretPositionStart().y) + 1;
	}
}

uint32						ProjectEditorTab::getTotalEntryCount(void)
{
	uint32 uiLineCount = m_pTextBox->getTextLines().size();
	if (uiLineCount == 1)
	{
		return m_pTextBox->getTextLines()[0] == "" ? 0 : 1;
	}
	else
	{
		return uiLineCount;
	}
}

vector<string>				ProjectEditorTab::getTextLines(void)
{
	return m_pTextBox->getTextLines();
}

// merge
void						ProjectEditorTab::merge(string& strFilePath)
{
	mergeViaData(File::getTextFile(strFilePath));
}

void						ProjectEditorTab::mergeViaData(string& strFileData)
{
	m_pTextBox->addText("\r\n\r\n" + strFileData);
}

// split
void						ProjectEditorTab::split(vector<string>& vecTextLines, string& strFilePathOut, uint32 uiFileVersionOut)
{
	File::setTextFile(strFilePathOut, String::join(vecTextLines, "\n"));
}

// add entry
void*						ProjectEditorTab::addEntryViaFile(string& strEntryFilePath, string strEntryName)
{
	merge(strEntryFilePath);
	return nullptr;
}

void*						ProjectEditorTab::addEntryViaData(string strEntryName, string& strEntryData)
{
	mergeViaData(strEntryData);
	return nullptr;
}

// remove text
void						ProjectEditorTab::removeSelectedText(void)
{
	m_pTextBox->removeSelectedText();
}

void						ProjectEditorTab::removeAllText(void)
{
	m_pTextBox->removeAllText();
}

// shift entries
void						ProjectEditorTab::shiftSelectedEntries(int32 iRowCountOffset)
{
	if (!m_pTextBox->isTextSelected())
	{
		return;
	}

	for (int32 iLine = m_pTextBox->getCaretPositionStart().y, iLineEnd = m_pTextBox->getCaretPositionEnd().y; iLine <= iLineEnd; iLine++)
	{
		int32 iEntry1Index = iLine;
		int32 iEntry2Index = Math::limit(iEntry1Index + (int32)iRowCountOffset, 0, (int32)getTotalEntryCount());
		
		string strEntry1 = m_pTextBox->getTextLines()[iEntry1Index];
		string strEntry2 = m_pTextBox->getTextLines()[iEntry2Index];

		m_pTextBox->getTextLines()[iEntry1Index] = strEntry2;
		m_pTextBox->getTextLines()[iEntry2Index] = strEntry1;
	}

	recreateEntryList();
	setFileUnsaved(true);
}

// copy data
void						ProjectEditorTab::copySelectedEntryData(uint32 uiFieldId)
{
	if (uiFieldId == 6)
	{
		// copy row
		String::setClipboardText(m_pTextBox->getSelectedText());
	}
}

// start
void						ProjectEditorTab::start(void)
{
	unordered_map<uint32, vector<uint32>> umapCorruptFileCounts;
	unordered_map<uint32, vector<uint32>> umapDuplicateEntryCounts;
	unordered_map<uint32, vector<uint32>> umapMissingEntryCounts;
	unordered_map<uint32, vector<uint32>> umapExceededLimitCounts;

	vector<IDEFormat*> vecIDEFiles;
	vector<IPLFormat*> vecIPLFiles;

	// fetch project settings
	string strGameDirectory = Path::getDirectory(m_pDATFile->getFilePath()) + "../";

	// read IDE & IPL files
	vecIDEFiles = m_pDATFile->parseIDEFiles(strGameDirectory);
	vecIPLFiles = m_pDATFile->parseIPLFiles(strGameDirectory);

	uint32 uiIDEEntryCount = 0;
	for (IDEFormat *pIDEFormat : vecIDEFiles)
	{
		for (IDEEntry *pIDEEntry : pIDEFormat->getEntries().getEntries())
		{
			if (pIDEEntry->getEntryType2() == SECTION_LINES_ENTRY_DATA)
			{
				uiIDEEntryCount++;
			}
		}
	}

	uint32 uiIPLEntryCount = 0;
	for (IPLFormat *pIPLFormat : vecIPLFiles)
	{
		for (IPLEntry *pIPLEntry : pIPLFormat->getEntries().getEntries())
		{
			if (pIPLEntry->getEntryType2() == SECTION_LINES_ENTRY_DATA)
			{
				uiIPLEntryCount++;
			}
		}
	}

	setText(502, String::toString(vecIDEFiles.size()) + " | " + String::toString(uiIDEEntryCount));
	setText(503, String::toString(vecIPLFiles.size()) + " | " + String::toString(uiIPLEntryCount));

	// read COL files

	// read TXD files

	// read DFF files

	// read WTD files

	// read IMG files
}

// text
void						ProjectEditorTab::setText(uint32 uiItemId, string strText)
{
	getLayer()->getText(uiItemId)->setText(strText);
}