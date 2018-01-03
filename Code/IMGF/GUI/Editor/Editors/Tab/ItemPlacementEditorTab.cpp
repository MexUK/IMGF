#include "ItemPlacementEditorTab.h"
#include "Format/IDE/IDEManager.h"
#include "Format/IPL/IPLFormat.h"
#include "Format/IPL/Entry/DataEntry/IPLEntry_INST.h"
#include "Window/Window.h"
#include "IMGF.h"
#include "Task/Tasks/RecentlyOpen/RecentlyOpenManager.h"
#include "Static/File.h"
#include "Control/Controls/TextBox.h"
#include "Control/Controls/Text.h"
#include "GUI/Editor/Base/Editor.h"
#include "Event/EInputEvent.h"

using namespace std;
using namespace bxcf;
using namespace bxgi;
using namespace bxgx::events;
using namespace imgf;

ItemPlacementEditorTab::ItemPlacementEditorTab(void) :
	m_pIPLFile(nullptr),
	m_pTextBox(nullptr)
{
}

// controls
void						ItemPlacementEditorTab::addControls(void)
{
	// todo m_pTextBox = addTextBox(139 + 139, 192, 600, 512, "", true, "textBasedEditorTextBox");

	repositionAndResizeControls(Vec2i(0, 0));
}

// events
void						ItemPlacementEditorTab::bindEvents(void)
{
	bindEvent(RESIZE_WINDOW, &ItemPlacementEditorTab::repositionAndResizeControls);

	EditorTab::bindEvents();
}

void						ItemPlacementEditorTab::unbindEvents(void)
{
	unbindEvent(RESIZE_WINDOW, &ItemPlacementEditorTab::repositionAndResizeControls);

	EditorTab::unbindEvents();
}

// file loading
bool						ItemPlacementEditorTab::unserializeFile(void)
{
	return m_pIPLFile->unserialize();
}

void						ItemPlacementEditorTab::onFileLoaded(void)
{
	// update tab text
	updateTabText();

	// add file path to recently opened files list
	getIMGF()->getRecentlyOpenManager()->addRecentlyOpenEntry(m_pEditor->getEditorType(), getFile()->getFilePath());

	// show file content
	m_pTextBox->getTextLines() = String::split(String::fixEOLs(File::getFileContent(getFile()->getFilePath(), false), "\n"), "\n");
	if (m_pTextBox->getTextLines().size() == 0)
	{
		m_pTextBox->getTextLines().push_back("");
	}

	// display file info
	setFileInfoText();

	// render
	getLayer()->getWindow()->render();
}

// file info text
void						ItemPlacementEditorTab::setFileInfoText(void)
{
	m_pText_FilePath->setText(Path::getDisplayableFilePath(getIPLFile()->getFilePath()));

	if (getIPLFile()->getEntriesBySection<IPLEntry_INST>(IPL_SECTION_INST).size() == 0)
	{
		m_pText_FileGame->setText(string("Unknown"));
		m_pText_FileVersion->setText(string("Unknown"));
	}
	else
	{
		uint32 uiIPLGames = ((IPLEntry_INST*)(getIPLFile()->getEntriesBySection<IPLEntry_INST>(IPL_SECTION_INST)[0]))->getFormatGames();

		m_pText_FileGame->setText(IDEManager::getFormatGamesAsString(uiIPLGames));
		m_pText_FileVersion->setText(IDEManager::getVersionText(uiIPLGames));
	}

	updateEntryCountText();
}

void						ItemPlacementEditorTab::updateEntryCountText(void)
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

void						ItemPlacementEditorTab::repositionAndResizeControls(Vec2i& vecSizeDifference)
{
	EditorTab::repositionAndResizeControls(vecSizeDifference);

	uint32 x, y;
	uint32 uiLogWidth;

	uiLogWidth = 337;

	if (!m_pTextBox)
	{
		return;
	}

	x = m_pTextBox->getWindow()->getSize().x - uiLogWidth - 139 * 2;
	y = m_pTextBox->getWindow()->getSize().y - 200;
	m_pTextBox->setSize(Vec2u(x, y));
}

// entry selection
void						ItemPlacementEditorTab::setAllLinesSelected(bool bIsSelected)
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

vector<string>				ItemPlacementEditorTab::getSelectedTextLines(void)
{
	vector<string> vecTextLines;
	for (int32 iLine = m_pTextBox->getCaretPositionStart().y, iLineEnd = m_pTextBox->getCaretPositionEnd().y; iLine <= iLineEnd; iLine++)
	{
		vecTextLines.push_back(m_pTextBox->getTextAtLine(iLine));
	}
	return vecTextLines;
}

uint32						ItemPlacementEditorTab::getSelectedEntryCount(void)
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

uint32						ItemPlacementEditorTab::getTotalEntryCount(void)
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

vector<string>				ItemPlacementEditorTab::getTextLines(void)
{
	return m_pTextBox->getTextLines();
}

// merge
void						ItemPlacementEditorTab::merge(string& strFilePath)
{
	mergeViaData(File::getFileContent(strFilePath));
}

void						ItemPlacementEditorTab::mergeViaData(string& strFileData)
{
	m_pTextBox->addText("\r\n\r\n" + strFileData);
}

// split
void						ItemPlacementEditorTab::split(vector<string>& vecTextLines, string& strFilePathOut, uint32 uiFileVersionOut)
{
	File::setTextFile(strFilePathOut, String::join(vecTextLines, "\n"));
}

// add entry
void*						ItemPlacementEditorTab::addEntryViaFile(string& strEntryFilePath, string strEntryName)
{
	merge(strEntryFilePath);
	return nullptr;
}

void*						ItemPlacementEditorTab::addEntryViaData(string strEntryName, string& strEntryData)
{
	mergeViaData(strEntryData);
	return nullptr;
}

// remove text
void						ItemPlacementEditorTab::removeSelectedText(void)
{
	m_pTextBox->removeSelectedText();
}

void						ItemPlacementEditorTab::removeAllText(void)
{
	m_pTextBox->removeAllText();
}

// shift entries
void						ItemPlacementEditorTab::shiftSelectedEntries(int32 iRowCountOffset)
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
void						ItemPlacementEditorTab::copySelectedEntryData(uint32 uiFieldId)
{
	if (uiFieldId == 6)
	{
		// copy row
		String::setClipboardText(m_pTextBox->getSelectedText());
	}
}