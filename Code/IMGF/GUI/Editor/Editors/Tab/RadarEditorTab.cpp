#include "RadarEditorTab.h"
#include "Format/DFF/DFFFormat.h"
#include "Window/Window.h"
#include "IMGF.h"
#include "Task/Tasks/RecentlyOpen/RecentlyOpenManager.h"
#include "Static/File.h"
#include "Control/Controls/TextBox.h"
#include "Format/IMG/Regular/IMGFormat.h"
#include "Task/Tasks/Tasks.h"
#include "Control/Controls/ProgressBar.h"

using namespace bxcf;
using namespace bxgi;
using namespace imgf;

RadarEditorTab::RadarEditorTab(void) :
	m_pIMGFile(nullptr)
{
}

// controls
void						RadarEditorTab::addControls(void)
{
}

// events
void						RadarEditorTab::bindEvents(void)
{
	EditorTab::bindEvents();
}

void						RadarEditorTab::unbindEvents(void)
{
	EditorTab::unbindEvents();
}

// render
void						RadarEditorTab::render_Type1(void)
{
}

// file loading
bool						RadarEditorTab::unserializeFile(void)
{
	IMGFormat *img = getIMGFile();

	/*
	progress bar: 3 stages

	[IMG versions 1, 2, and fastman92]
	- parsing header
	- parsing RW versions
	- adding entries to grid

	[IMG versions 3 (encrypted and unencrypted)]
	- parsing header
	- parsing entry names
	- adding entries to grid
	*/

	if (!img->openFile())
	{
		return false;
	}
	if (!img->readMetaData()) // here for progress bar tick count
	{
		Tasks::showMessage(Format::getErrorReason(img->getErrorCode()) + "\r\n\r\n" + img->getFilePath(), "Can't Open IMG File");
		delete img;
		return false;
	}

	uint32
		uiProgressBarMaxMultiplier = 3,
		uiProgressBarMax = img->m_uiEntryCount * uiProgressBarMaxMultiplier;
	getProgressBar()->setMax(uiProgressBarMax);

	if (!img->unserialize())
	{
		Tasks::showMessage(Format::getErrorReason(img->getErrorCode()) + "\r\n\r\n" + img->getFilePath(), "Can't Open IMG File");
		delete img;
		return false;
	}

	return true;
}

void						RadarEditorTab::onFileLoaded(void)
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
void						RadarEditorTab::setFileInfoText(void)
{
}