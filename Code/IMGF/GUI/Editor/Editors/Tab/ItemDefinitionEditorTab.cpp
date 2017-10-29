#include "ItemDefinitionEditorTab.h"
#include "Format/IDE/IDEFormat.h"
#include "Window/Window.h"
#include "IMGF.h"
#include "Task/Tasks/RecentlyOpen/RecentlyOpenManager.h"
#include "Static/File.h"
#include "Control/Controls/TextBox.h"

using namespace bxcf;
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

// file info
void						ItemDefinitionEditorTab::setFileInfoText(void)
{
}