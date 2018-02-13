#include "AnimationEditorTab.h"
//#include "Format/PLG/PLGFormat.h"
#include "Format/Format.h" // temp
#include "Window/Window.h"
#include "IMGF.h"
#include "Task/Tasks/RecentlyOpen/RecentlyOpenManager.h"
#include "Static/File.h"
#include "Control/Controls/TextBox.h"
#include "Control/Controls/Text.h"
#include "GUI/Editor/Base/Editor.h"

using namespace std;
using namespace bxcf;
using namespace imgf;

AnimationEditorTab::AnimationEditorTab(void)// :
	// todo m_pIFPFile(nullptr)
{
}

// controls
void						AnimationEditorTab::storeControls(void)
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
	// todo return m_pIFPFile->unserialize();
	return true;
}

void						AnimationEditorTab::onFileLoaded(void)
{
	// update tab text
	updateTabText();

	// add file path to recently opened files list
	getIMGF()->getRecentlyOpenManager()->addRecentlyOpenEntry(m_pEditor->getEditorType(), getFile()->getFilePath());

	// display file info
	setFileInfoText();

	// render
	getLayer()->getWindow()->render();
}

// file info text
void						AnimationEditorTab::setFileInfoText(void)
{
	m_pText_FilePath->setText(Path::getDisplayableFilePath(getFile()->getFilePath()));
	m_pText_FileGame->setText(string("Unknown")); // todo
	m_pText_FileVersion->setText(string("Unknown")); // todo

	updateEntryCountText();
}

void						AnimationEditorTab::updateEntryCountText(void)
{
	uint32
		uiDisplayedEntryCount = 0,
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