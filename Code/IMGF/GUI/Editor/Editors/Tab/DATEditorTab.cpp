#include "DATEditorTab.h"
#include "Format/DAT/Loader/DATLoaderFormat.h"
#include "Window/Window.h"
#include "IMGF.h"
#include "Task/Tasks/RecentlyOpen/RecentlyOpenManager.h"
#include "Static/File.h"
#include "Control/Controls/TextBox.h"

using namespace bxcf;
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
	getIMGF()->getRecentlyOpenManager()->addRecentlyOpenEntry(getFile()->getFilePath());

	// display file info
	setFileInfoText();

	// show file content
	m_pTextBox->setText(File::getFileContent(getFile()->getFilePath()));

	// render
	m_pWindow->render();
}

// file info
void						DATEditorTab::setFileInfoText(void)
{
}