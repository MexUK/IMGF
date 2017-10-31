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

using namespace std;
using namespace bxcf;
using namespace bxgi;
using namespace imgf;

DATEditorTab::DATEditorTab(void) :
	m_pDATFile(nullptr),
	m_pTextBox(nullptr)
{
}

// controls
void						DATEditorTab::addControls(void)
{
	m_pTextBox = addTextBox(139 + 139, 192, 600, 512, "", true, "textBasedEditorTextBox");
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
	getIMGF()->getRecentlyOpenManager()->addRecentlyOpenEntry(m_pEditor->getEditorType(), getFile()->getFilePath());

	// display file info
	setFileInfoText();

	// show file content
	m_pTextBox->setText(File::getFileContent(getFile()->getFilePath()));

	// render
	m_pWindow->render();
}

// file info text
void						DATEditorTab::setFileInfoText(void)
{
	m_pText_FilePath->setText(getDATFile()->getFilePath());
	m_pText_FileGame->setText(GameManager::get()->getGameName(getDATFile()->getGame()));
	m_pText_FileVersion->setText(String::toString(getDATFile()->getVersion()));

	updateEntryCountText();
}

void						DATEditorTab::updateEntryCountText(void)
{
	uint32
		uiDisplayedEntryCount = getDATFile()->getEntryCount(),
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