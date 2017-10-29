#include "AnimationEditorTab.h"
//#include "Format/PLG/PLGFormat.h"
#include "Format/Format.h" // temp
#include "Window/Window.h"
#include "IMGF.h"
#include "Task/Tasks/RecentlyOpen/RecentlyOpenManager.h"
#include "Static/File.h"
#include "Control/Controls/TextBox.h"

using namespace bxcf;
using namespace imgf;

AnimationEditorTab::AnimationEditorTab(void)// :
	// todo m_pPLGFile(nullptr)
{
}

// controls
void						AnimationEditorTab::addControls(void)
{
}

// events
void						AnimationEditorTab::bindEvents(void)
{
	EditorTab::bindEvents();
}

void						AnimationEditorTab::unbindEvents(void)
{
	EditorTab::unbindEvents();
}

// render
void						AnimationEditorTab::render_Type1(void)
{
}

// file loading
bool						AnimationEditorTab::unserializeFile(void)
{
	// todo return m_pPLGFile->unserialize();
	return true;
}

void						AnimationEditorTab::onFileLoaded(void)
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
void						AnimationEditorTab::setFileInfoText(void)
{
}