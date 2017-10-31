#include "ModelEditorTab.h"
#include "Format/DFF/DFFFormat.h"
#include "Window/Window.h"
#include "IMGF.h"
#include "Task/Tasks/RecentlyOpen/RecentlyOpenManager.h"
#include "Static/File.h"
#include "Control/Controls/TextBox.h"
#include "Control/Controls/Text.h"
#include "GUI/Editor/Base/Editor.h"

using namespace std;
using namespace bxcf;
using namespace bxgi;
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
	getIMGF()->getRecentlyOpenManager()->addRecentlyOpenEntry(m_pEditor->getEditorType(), getFile()->getFilePath());

	// display file info
	setFileInfoText();

	// render
	m_pWindow->render();
}

// file info text
void						ModelEditorTab::setFileInfoText(void)
{
	m_pText_FilePath->setText(getFile()->getFilePath());
	m_pText_FileVersion->setText(getDFFFile()->getRWVersion()->getVersionText(), false);
	m_pText_FileGame->setText(getDFFFile()->getRWVersion()->getGamesAsString());

	updateEntryCountText();
}

void						ModelEditorTab::updateEntryCountText(void)
{
	uint32
		uiDisplayedEntryCount = getDFFFile()->getSectionCountByType(RW_SECTION_GEOMETRY),
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