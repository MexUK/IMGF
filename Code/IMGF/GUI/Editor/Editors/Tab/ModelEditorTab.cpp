#include "ModelEditorTab.h"
#include "Format/DFF/DFFFormat.h"
#include "Window/Window.h"
#include "IMGF.h"
#include "Task/Tasks/RecentlyOpen/RecentlyOpenManager.h"
#include "Static/File.h"
#include "Control/Controls/TextBox.h"

using namespace bxcf;
using namespace imgf;

ModelEditorTab::ModelEditorTab(void) :
	m_pDFFFile(nullptr)
{
}

// controls
void						ModelEditorTab::addControls(void)
{
}

// events
void						ModelEditorTab::bindEvents(void)
{
	EditorTab::bindEvents();
}

void						ModelEditorTab::unbindEvents(void)
{
	EditorTab::unbindEvents();
}

// render
void						ModelEditorTab::render_Type1(void)
{
}

// file loading
bool						ModelEditorTab::unserializeFile(void)
{
	return m_pDFFFile->unserialize();
}

void						ModelEditorTab::onFileLoaded(void)
{
	// update tab text
	updateTabText();

	// add file path to recently opened files list
	getIMGF()->getRecentlyOpenManager()->addRecentlyOpenEntry(getFile()->getFilePath());

	// display file info
	setFileInfoText();

	// render
	m_pWindow->render();
}

// file info
void						ModelEditorTab::setFileInfoText(void)
{
}