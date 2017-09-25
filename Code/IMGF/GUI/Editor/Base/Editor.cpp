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
	m_pTabBar(nullptr)
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
}

void								Editor::initControls(void)
{
}

// add/remove file
void								Editor::addFile(EditorTab *pEditorFile)
{
	// store file object
	m_vecTabs.addEntry(pEditorFile);
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
}

void								Editor::updateActiveFileDisplayedInfo(void)
{
	m_pActiveFile->setFileInfoText();
}