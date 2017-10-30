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

using namespace std;
using namespace bxcf;
using namespace bxgi;
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
}

// events
void						ItemDefinitionEditorTab::bindEvents(void)
{
	EditorTab::bindEvents();
}

void						ItemDefinitionEditorTab::unbindEvents(void)
{
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
	getIMGF()->getRecentlyOpenManager()->addRecentlyOpenEntry(getFile()->getFilePath());

	// display file info
	setFileInfoText();

	// show file content
	m_pTextBox->setText(File::getFileContent(getFile()->getFilePath()));

	// render
	m_pWindow->render();
}

// file info text
void						ItemDefinitionEditorTab::setFileInfoText(void)
{
	m_pText_FilePath->setText(getIDEFile()->getFilePath());

	if (getIDEFile()->getEntriesBySection<IDEEntry_OBJS>(IDE_SECTION_OBJS).size() == 0)
	{
		m_pText_FileGame->setText(string("Unknown"));
		m_pText_FileVersion->setText(string("Unknown"));
	}
	else
	{
		uint32 uiIDEGames = ((IDEEntry_OBJS*)(getIDEFile()->getEntriesBySection<IDEEntry_OBJS>(IDE_SECTION_OBJS)[0]))->getFormatGames();

		m_pText_FileGame->setText(IDEManager::getFormatGamesAsString(uiIDEGames));
		m_pText_FileVersion->setText(IDEManager::getVersionText(uiIDEGames));
	}

	updateEntryCountText();
}

void						ItemDefinitionEditorTab::updateEntryCountText(void)
{
	uint32
		uiDisplayedEntryCount = getIDEFile()->getEntryCount(),
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