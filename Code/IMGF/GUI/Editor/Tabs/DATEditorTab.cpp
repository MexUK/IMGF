#include "DATEditorTab.h"
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

using namespace std;
using namespace bxcf;
using namespace bxgi;
using namespace bxgx;
using namespace bxgx::events;
using namespace imgf;

DATEditorTab::DATEditorTab(void) :
	m_pDATFile(nullptr),
	m_pTextBox(nullptr)
{
}

// controls
void						DATEditorTab::storeControls(void)
{
	m_pTextBox = (TextBox*)getLayer()->getItemById(1100);
}

// layer
void						DATEditorTab::initLayer(void)
{
	setLayer(m_pEditor->getMainWindow()->getLayerById(100));
}

// events
void						DATEditorTab::bindEvents(void)
{
	EditorTab::bindEvents();
}

void						DATEditorTab::unbindEvents(void)
{
	EditorTab::unbindEvents();
}

// file loading
bool						DATEditorTab::unserializeFile(void)
{
	return m_pDATFile->unserialize();
}

void						DATEditorTab::onFileLoaded(void)
{
	// update tab text
	updateTabText();

	// add file path to recently opened files list
	// todo getIMGF()->getRecentlyOpenManager()->addRecentlyOpenEntry(m_pEditor->getEditorType(), getFile()->getFilePath());

	// show file content
	m_pTextBox->getTextLines() = String::split(String::fixEOLs(File::getTextFile(getFile()->getFilePath()), "\n"), "\n");
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
void						DATEditorTab::setFileInfoText(void)
{
	m_pText_FilePath->setText(Path::getDisplayableFilePath(getDATFile()->getFilePath()));
	//m_pText_FileGame->setText(GameManager::get()->getGameName(getDATFile()->getGame()));
	//m_pText_FileVersion->setText(getDATFile()->getVersion() == -1 ? "Unknown Version" : String::toString(getDATFile()->getVersion()));

	updateEntryCountText();
}

void						DATEditorTab::updateEntryCountText(void)
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

// entry selection
void						DATEditorTab::setAllLinesSelected(bool bIsSelected)
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

vector<string>				DATEditorTab::getSelectedTextLines(void)
{
	vector<string> vecTextLines;
	for (int32 iLine = m_pTextBox->getCaretPositionStart().y, iLineEnd = m_pTextBox->getCaretPositionEnd().y; iLine <= iLineEnd; iLine++)
	{
		vecTextLines.push_back(m_pTextBox->getTextAtLine(iLine));
	}
	return vecTextLines;
}

uint32						DATEditorTab::getSelectedEntryCount(void)
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

uint32						DATEditorTab::getTotalEntryCount(void)
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

vector<string>				DATEditorTab::getTextLines(void)
{
	return m_pTextBox->getTextLines();
}

// merge
void						DATEditorTab::merge(string& strFilePath)
{
	mergeViaData(File::getTextFile(strFilePath));
}

void						DATEditorTab::mergeViaData(string& strFileData)
{
	m_pTextBox->addText("\r\n\r\n" + strFileData);
}

// split
void						DATEditorTab::split(vector<string>& vecTextLines, string& strFilePathOut, uint32 uiFileVersionOut)
{
	File::setTextFile(strFilePathOut, String::join(vecTextLines, "\n"));
}

// add entry
void*						DATEditorTab::addEntryViaFile(string& strEntryFilePath, string strEntryName)
{
	merge(strEntryFilePath);
	return nullptr;
}

void*						DATEditorTab::addEntryViaData(string strEntryName, string& strEntryData)
{
	mergeViaData(strEntryData);
	return nullptr;
}

// remove text
void						DATEditorTab::removeSelectedText(void)
{
	m_pTextBox->removeSelectedText();
}

void						DATEditorTab::removeAllText(void)
{
	m_pTextBox->removeAllText();
}

// shift entries
void						DATEditorTab::shiftSelectedEntries(int32 iRowCountOffset)
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
void						DATEditorTab::copySelectedEntryData(uint32 uiFieldId)
{
	if (uiFieldId == 6)
	{
		// copy row
		String::setClipboardText(m_pTextBox->getSelectedText());
	}
}