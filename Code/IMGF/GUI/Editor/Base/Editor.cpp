#include "Editor.h"
#include "Static/Path.h"
#include "Format/Format.h"
#include "IMGF.h"
#include "Task/Tasks/RecentlyOpen/RecentlyOpenManager.h"
#include "GUI/Window/Windows/MainWindow/MainWindow.h"
#include "Static/String.h"
#include "Control/Controls/TextBox.h"
#include "Control/Controls/TabBar.h"
#include "Task/Tasks/Tasks.h"

using namespace std;
using namespace bxcf;
using namespace bxgx;
using namespace imgf;

Editor::Editor(void) :
	m_pMainWindow(nullptr),
	m_pActiveFile(nullptr),
	m_pTabBar(nullptr)
{
}

// initialization
void								Editor::init(void)
{
	int32 x, y;
	uint32 w, h, uiLogWidth;
	string strStyleGroup;

	uiLogWidth = 335;

	// files tab bar
	x = 139 + 139;
	y = 162;
	w = m_pWindow->getSize().x - x - uiLogWidth;
	h = 30;
	strStyleGroup = "fileTabBar";

	m_pTabBar = addTabBar(x, y, w, h, strStyleGroup);
	m_pTabBar->setDefaultText("No tabs to display");
}

// events
void								Editor::bindEvents(void)
{
	if (m_pTabBar)
	{
		//m_pTabBar->bindEvents();
	}
}

void								Editor::unbindEvents(void)
{
	if (m_pTabBar)
	{
		//m_pTabBar->unbindEvents();
	}
}

// controls
void								Editor::addControls(void)
{
}

void								Editor::initControls(void)
{
}

// remove editor tab
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
	todo
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
	if (m_pActiveFile)
	{
		uint32 uiTabIndex = m_pActiveFile->getTabIndex();
		mutexTabs.lock();
		Tab *pTab = m_pTabBar->getEntryByIndex(uiTabIndex);
		mutexTabs.unlock();
		m_pTabBar->setActiveTab(pTab);
	}
}

// displayed info
void								Editor::updateActiveFileDisplayedInfo(void)
{
	m_pActiveFile->setFileInfoText();
}

// file path
bool								Editor::isFilePathOpen(string& strFilePath)
{
	for (EditorTab *pEditorTab : m_vecTabs.getEntries())
	{
		if (Path::comparePaths(strFilePath, pEditorTab->getFile()->getFilePath()))
		{
			return true;
		}
	}
	return false;
}

EditorTab*							Editor::getEditorTabByFilePath(string& strFilePath)
{
	for (EditorTab *pEditorTab : m_vecTabs.getEntries())
	{
		if (Path::comparePaths(strFilePath, pEditorTab->getFile()->getFilePath()))
		{
			return pEditorTab;
		}
	}
	return nullptr;
}