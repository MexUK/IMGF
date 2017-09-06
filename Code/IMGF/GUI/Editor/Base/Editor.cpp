#include "Editor.h"
#include "Static/Path.h"
#include "Format/Format.h"
#include "IMGF.h"
#include "Task/Tasks/RecentlyOpen/RecentlyOpenManager.h"
#include "GUI/Window/Windows/MainWindow/MainWindow.h"
#include "Static/String.h"
#include "Control/Controls/TextBox.h"
#include "Control/Controls/TabBar.h"

using namespace std;
using namespace bxcf;
using namespace bxgx;
using namespace imgf;

Editor::Editor(void) :
	m_pActiveFile(nullptr),
	m_pTabBar(nullptr),
	m_pLog(nullptr)
{
}

// initialization
void								Editor::init(void)
{
	m_pTabBar = ((MainWindow*)getWindow())->getTabBar();
}

// controls
void								Editor::addControls(void)
{
	int32 x, y;
	uint32 w, h;

	// log
	x = 0;
	y = 508;
	w = 139 + 139;
	h = 120;

	m_pLog = addTextBox(x, y, w, h, "", true, "log");
	m_pLog->setReadOnly(true);
}

void								Editor::initControls(void)
{
}

// add/remove file
void								Editor::addFile(EditorTab *pEditorFile)
{
	// store file object
	m_vecTabs.addEntry(pEditorFile);
	setActiveFile(pEditorFile);

	string strFilePath = getResolvedFilePath(pEditorFile->getFile()->getFilePath());

	// choose tab text
	string strTabText = Path::getFileName(strFilePath);
	if (String::toUpperCase(Path::getFileExtension(strTabText)) == "DIR")
	{
		strTabText = Path::replaceFileExtensionWithCase(strTabText, "IMG");
	}
	strTabText += " (" + String::toString(pEditorFile->getFile()->m_uiEntryCount) + ")";

	// add controls to tab layer
	pEditorFile->EditorTab::addControls();
	pEditorFile->EditorTab::initControls();

	pEditorFile->addControls();
	pEditorFile->initControls();

	// add tab to tab bar
	Tab *pTab = m_pTabBar->addTab(strTabText, true);
	m_pTabBar->bindTabLayer(pTab, pEditorFile);
	pEditorFile->setTab(pTab);

	// add file path to recently opened files list
	getIMGF()->getRecentlyOpenManager()->addRecentlyOpenEntry(strFilePath);
}

void								Editor::removeFile(EditorTab *pEditorFile)
{
	// remove tab from tab bar
	m_pTabBar->removeTab(pEditorFile->getTab());

	// unmark items to render
	for (RenderItem *pRenderItem : pEditorFile->getRenderItems().getEntries())
	{
		if (m_pWindow->isRenderItemMarkedForRender(pRenderItem))
		{
			m_pWindow->setRenderItemMarkedForRender(pRenderItem, false);
		}
	}

	// remove tab object
	m_vecTabs.removeEntry(pEditorFile);

	// update active file
	uint32 uiNewActiveFileIndex = m_pTabBar->getActiveIndex();
	if (uiNewActiveFileIndex == -1)
	{
		setActiveFile(nullptr);
	}
	else
	{
		setActiveFile(m_vecTabs.getEntryByIndex(uiNewActiveFileIndex));
	}
}

void								Editor::removeActiveFile(void)
{
	/*
	if (getTabs().getEntryCount() == 0)
	{
		return;
	}

	removeFile(getActiveFile());
	*/
}

// set active file
void								Editor::setActiveFile(EditorTab *pEditorFile)
{
	m_pActiveFile = pEditorFile;

	if (pEditorFile)
	{
		updateActiveFileDisplayedInfo();
	}
	else
	{
		clearActiveFileDisplayedInfo();
	}
}

void								Editor::updateActiveFileDisplayedInfo(void)
{
	setFileInfoText(m_pActiveFile);
}

void								Editor::clearActiveFileDisplayedInfo(void)
{
	clearFileInfoText();
}