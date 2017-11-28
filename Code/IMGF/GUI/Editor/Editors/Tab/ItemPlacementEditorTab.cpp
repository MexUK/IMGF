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
	m_pTextBox = addTextBox(139 + 139, 192, 600, 512, "", true, "textBasedEditorTextBox");

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

	// display file info
	setFileInfoText();

	// show file content
	m_pTextBox->setText(File::getFileContent(getFile()->getFilePath()));

	// render
	m_pWindow->render();
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
		uiDisplayedEntryCount = getIPLFile()->getEntryCount(),
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

// merge
void						ItemPlacementEditorTab::merge(string& strFilePath)
{
	mergeViaData(File::getFileContent(strFilePath));
}

void						ItemPlacementEditorTab::mergeViaData(string& strFileData)
{
	m_pTextBox->addText("\r\n\r\n" + strFileData);
}