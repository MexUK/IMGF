#include "ItemDefinitionEditorTab.h"
#include "Format/IDE/IDEManager.h"
#include "Format/IDE/IDEFormat.h"
#include "Format/IDE/Entry/DataEntry/IDEEntry_OBJS.h"
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

ItemDefinitionEditorTab::ItemDefinitionEditorTab(void) :
	m_pIDEFile(nullptr),
	m_pTextBox(nullptr)
{
}

// controls
void						ItemDefinitionEditorTab::addControls(void)
{
	m_pTextBox = addTextBox(139 + 139, 192, 600, 512, "", true, "textBasedEditorTextBox");

	repositionAndResizeControls(Vec2i(0,0));
}

// events
void						ItemDefinitionEditorTab::bindEvents(void)
{
	bindEvent(RESIZE_WINDOW, &ItemDefinitionEditorTab::repositionAndResizeControls);

	EditorTab::bindEvents();
}

void						ItemDefinitionEditorTab::unbindEvents(void)
{
	unbindEvent(RESIZE_WINDOW, &ItemDefinitionEditorTab::repositionAndResizeControls);

	EditorTab::unbindEvents();
}

// file loading
bool						ItemDefinitionEditorTab::unserializeFile(void)
{
	return m_pIDEFile->unserialize();
}

void						ItemDefinitionEditorTab::onFileLoaded(void)
{
	// update tab text
	updateTabText();

	// add file path to recently opened files list
	getIMGF()->getRecentlyOpenManager()->addRecentlyOpenEntry(m_pEditor->getEditorType(), getFile()->getFilePath());

	// show file content
	m_pTextBox->getTextLines() = String::split(File::getFileContent(getFile()->getFilePath(), false), "\n");
	if (m_pTextBox->getTextLines().size() == 0)
	{
		m_pTextBox->getTextLines().push_back("");
	}

	// display file info
	setFileInfoText();

	// render
	m_pWindow->render();
}

// file info text
void						ItemDefinitionEditorTab::setFileInfoText(void)
{
	m_pText_FilePath->setText(Path::getDisplayableFilePath(getIDEFile()->getFilePath()));

	uint32 uiIDEGames = getIDEFile()->getFormatGames();
	if (uiIDEGames == 0)
	{
		m_pText_FileGame->setText(string("Unknown"));
		m_pText_FileVersion->setText(string("Unknown"));
	}
	else
	{
		m_pText_FileGame->setText(IDEManager::getFormatGamesAsString(uiIDEGames));
		m_pText_FileVersion->setText(IDEManager::getVersionText(uiIDEGames));
	}

	updateEntryCountText();
}

void						ItemDefinitionEditorTab::updateEntryCountText(void)
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

void						ItemDefinitionEditorTab::repositionAndResizeControls(Vec2i& vecSizeDifference)
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
void						ItemDefinitionEditorTab::setAllLinesSelected(bool bIsSelected)
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

vector<string>				ItemDefinitionEditorTab::getSelectedTextLines(void)
{
	vector<string> vecTextLines;
	for (int32 iLine = m_pTextBox->getCaretPositionStart().y, iLineEnd = m_pTextBox->getCaretPositionEnd().y; iLine <= iLineEnd; iLine++)
	{
		vecTextLines.push_back(m_pTextBox->getTextAtLine(iLine));
	}
	return vecTextLines;
}

uint32						ItemDefinitionEditorTab::getSelectedEntryCount(void)
{
	return (m_pTextBox->getCaretPositionEnd().y - m_pTextBox->getCaretPositionStart().y) + 1;
}

uint32						ItemDefinitionEditorTab::getTotalEntryCount(void)
{
	return m_pTextBox->getTextLines().size();
}

vector<string>				ItemDefinitionEditorTab::getTextLines(void)
{
	return m_pTextBox->getTextLines();
}

// merge
void						ItemDefinitionEditorTab::merge(string& strFilePath)
{
	mergeViaData(File::getFileContent(strFilePath));
}

void						ItemDefinitionEditorTab::mergeViaData(string& strFileData)
{
	m_pTextBox->addText("\r\n\r\n" + strFileData);

	//addEntryAfter(pResult);
	updateEntryCountText();

	m_pWindow->render();
}

// add entry
void*						ItemDefinitionEditorTab::addEntryViaFile(string& strEntryFilePath, string strEntryName)
{
	merge(strEntryFilePath);
	return nullptr;
}

void*						ItemDefinitionEditorTab::addEntryViaData(string strEntryName, string& strEntryData)
{
	mergeViaData(strEntryData);
	return nullptr;
}