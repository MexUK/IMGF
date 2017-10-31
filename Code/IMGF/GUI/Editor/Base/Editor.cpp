#include "Editor.h"
#include "Static/Path.h"
#include "Format/Format.h"
#include "IMGF.h"
#include "Task/Tasks/RecentlyOpen/RecentlyOpenManager.h"
#include "GUI/Window/WindowManager.h"
#include "GUI/Window/Windows/MainWindow/MainWindow.h"
#include "GUI/Layer/Layers/MainLayer/MainLayerNoTabsOpen.h"
#include "Static/String.h"
#include "Control/Controls/TextBox.h"
#include "Control/Controls/TabBar.h"
#include "GUI/Editor/EEditor.h"

using namespace std;
using namespace bxcf;
using namespace bxgx;
using namespace imgf;

Editor::Editor(EEditor uiEditorType) :
	m_uiEditorType(uiEditorType),
	m_pMainWindow(nullptr),
	m_pActiveEditorTab(nullptr),
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

	// tab bar
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
	Layer::bindEvents();
}

void								Editor::unbindEvents(void)
{
	Layer::unbindEvents();
}

// controls
void								Editor::addControls(void)
{
}

void								Editor::initControls(void)
{
}

// remove editor tab
void								Editor::removeEditorTab(EditorTab *pEditorTab)
{
	// remove tab from tab bar
	m_pTabBar->removeTab(pEditorTab->getTab());

	// unmark items to render
	for (RenderItem *pRenderItem : pEditorTab->getRenderItems().getEntries())
	{
		if (m_pWindow->isRenderItemMarkedForRender(pRenderItem))
		{
			m_pWindow->setRenderItemMarkedForRender(pRenderItem, false);
		}
	}

	// remove tab object
	pEditorTab->unbindEvents();
	m_vecEditorTabs.removeEntry(pEditorTab);

	// update active file
	uint32 uiNewActiveFileIndex = m_pTabBar->getActiveIndex();
	if (uiNewActiveFileIndex == -1)
	{
		setActiveEditorTab(nullptr);
	}
	else
	{
		setActiveEditorTab(m_vecEditorTabs.getEntryByIndex(uiNewActiveFileIndex));
	}

	// render window
	m_pMainWindow->render();
}

void								Editor::removeActiveEditorTab(void)
{
	if (getEditorTabs().getEntryCount() == 0)
	{
		return;
	}

	removeEditorTab(getActiveEditorTab());
}

// set active file
void								Editor::setActiveEditorTab(EditorTab *pEditorTab)
{
	// store editor tab
	m_pActiveEditorTab = pEditorTab;
	
	if (pEditorTab)
	{
		// set active tab in tab bar
		uint32 uiTabIndex = pEditorTab->getTabIndex();
		mutexTabs.lock();
		Tab *pTab = m_pTabBar->getEntryByIndex(uiTabIndex);
		mutexTabs.unlock();
		m_pTabBar->setActiveTab(pTab);

		// hide no-tabs-open layer
		getIMGF()->getWindowManager()->getMainWindow()->getMainLayerNoTabsOpen()->setEnabled(false);
	}
	else
	{
		// show no-tabs-open layer
		getIMGF()->getWindowManager()->getMainWindow()->getMainLayerNoTabsOpen()->setEnabled(true);
	}
}

// displayed info
void								Editor::updateActiveFileDisplayedInfo(void)
{
	m_pActiveEditorTab->setFileInfoText();
}

// file path
bool								Editor::isFilePathOpen(string& strFilePath)
{
	for (EditorTab *pEditorTab : m_vecEditorTabs.getEntries())
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
	for (EditorTab *pEditorTab : m_vecEditorTabs.getEntries())
	{
		if (Path::comparePaths(strFilePath, pEditorTab->getFile()->getFilePath()))
		{
			return pEditorTab;
		}
	}
	return nullptr;
}

// editor name
string								Editor::getEditorName(EEditor uiEditor)
{
	switch (uiEditor)
	{
	case DAT_EDITOR:				return "DAT";
	case IMG_EDITOR:				return "IMG";
	case ITEM_DEFINITION_EDITOR:	return "Item Definition";
	case ITEM_PLACEMENT_EDITOR:		return "Item Placement";
	case MODEL_EDITOR:				return "Model";
	case COLLISION_EDITOR:			return "Collision";
	case TEXTURE_EDITOR:			return "Texture";
	case ANIMATION_EDITOR:			return "Animation";
	case RADAR_EDITOR:				return "Radar";
	}
	return "Unknown";
}