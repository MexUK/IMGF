#include "TextureEditorTab.h"
#include "nsbxgi.h"
#include "Format/TXD/TXDFormat.h"
#include "Task/Tasks/Tasks.h"
#include "Control/Controls/ProgressBar.h"
#include "IMGF.h"
#include "Task/Tasks/RecentlyOpen/RecentlyOpenManager.h"

using namespace std;
using namespace bxcf;
using namespace bxgi;
using namespace imgf;

// controls
void					TextureEditorTab::addControls(void)
{
}

void					TextureEditorTab::initControls(void)
{
}

// file unserialization
bool					TextureEditorTab::unserializeFile(void)
{
	TXDFormat *txd = new TXDFormat;

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

	if (!txd->openFile())
	{
		return false;
	}
	if (!txd->readMetaData()) // here for progress bar tick count
	{
		Tasks::showMessage(Format::getErrorReason(txd->getErrorCode()) + "\r\n\r\n" + txd->getFilePath(), "Can't Open TXD File");
		delete txd;
		return false;
	}

	uint32
		uiProgressBarMaxMultiplier = 3,
		uiProgressBarMax = txd->m_uiEntryCount * uiProgressBarMaxMultiplier;
	getProgressBar()->setMax(uiProgressBarMax);

	if (!txd->unserialize())
	{
		Tasks::showMessage(Format::getErrorReason(txd->getErrorCode()) + "\r\n\r\n" + txd->getFilePath(), "Can't Open TXD File");
		delete txd;
		return false;
	}

	return true;
}

void					TextureEditorTab::onFileLoaded(void)
{
	string strFilePath = getFile()->getFilePath();

	/*
	// update tab text
	updateTabText();

	// add file path to recently opened files list
	getIMGF()->getRecentlyOpenManager()->addRecentlyOpenEntry(strFilePath);

	// store render items
	getRenderItems().addEntry(m_pEntryGrid);
	getRenderItems().addEntry(m_pEntryTypeFilter);
	getRenderItems().addEntry(m_pEntryVersionFilter);

	addGridEntries();

	m_pEntryGrid->setActiveItem();

	loadFilter_Type();
	loadFilter_Version();

	setFileInfoText();
	*/
}