#include "Editor.h"
#include "Static/Path.h"
#include "Static/StdVector.h"
#include "Format/Format.h"
#include "IMGF.h"
#include "Task/Tasks/RecentlyOpen/RecentlyOpenManager.h"
#include "GUI/Window/WindowManager.h"
#include "GUI/Window/Windows/MainWindow/MainWindow.h"
#include "GUI/Layer/Layers/MainLayer/MainLayer.h"
#include "GUI/Layer/Layers/MainLayer/MainLayerNoTabsOpen.h"
#include "Static/String.h"
#include "Control/Controls/TextBox.h"
#include "Control/Controls/TabBar.h"
#include "GUI/Editor/EEditor.h"
#include "GUI/Input/EInputItem.h"
#include "Tab/EditorTab.h"
#include "Control/Controls/Text.h"

using namespace std;
using namespace bxcf;
using namespace bxgx;
using namespace bxgx::events;
using namespace imgf;
using namespace imgf::mainLayer::input;

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
	/*
	todo
	
	CoordinateSet x, y, w, h;
	x = a;
	y = a;
	w = a;
	h = a;
	uint32 uiItemId = 0;

	TabBar *pTabBar = getMainWindow()->getMainLayer()->addTabBar(x, y, w, h, "", uiItemId);
	pTabBar->setEnabled(false);
	*/

	setTabBar((TabBar*)m_pMainWindow->getItemById(90));
}

// events
void								Editor::bindEvents(void)
{
	bindEvent(RESIZE_WINDOW, &Editor::repositionAndResizeControls);
	bindEvent(DRAG_ENTRIES_OVER, &Editor::onDragEntriesOver);

	//getLayer()->bindEvents();
}

void								Editor::unbindEvents(void)
{
	unbindEvent(RESIZE_WINDOW, &Editor::repositionAndResizeControls);
	unbindEvent(DRAG_ENTRIES_OVER, &Editor::onDragEntriesOver);

	//getLayer()->unbindEvents();
}

// controls
void								Editor::addControls(void)
{
}

void								Editor::initControls(void)
{
	repositionAndResizeControls(Vec2i(0, 0));
}

// events
void								Editor::repositionAndResizeControls(Vec2i& vecSizeChange)
{
	//m_pTabBar->setSize(Vec2u(getLayer()->getWindow()->getSize().x - 335 - 139 - 139, m_pTabBar->getSize().y));
}

void								Editor::onDragEntriesOver(Vec2i vecCursorPosition)
{
	// check that this editor is the active editor
	if (this != m_pMainWindow->getActiveEditor())
	{
		return;
	}

	// convert absolute to relative coordinates
	POINT cursorPos;
	cursorPos.x = vecCursorPosition.x;
	cursorPos.y = vecCursorPosition.y;
	ScreenToClient(m_pMainWindow->getWindowHandle(), &cursorPos);
	vecCursorPosition.x = cursorPos.x;
	vecCursorPosition.y = cursorPos.y;

	// check if drag drop is occurring
	if (m_pMainWindow->m_bDragDropOutIsOccurring)
	{
		// check if cursor is over a tab
		Tab *pTab = m_pTabBar->getTabFromPosition(vecCursorPosition);
		if (pTab)
		{
			// change active tab
			uint32 uiNewActiveFileIndex = pTab->getIndex();
			EditorTab *pEditorTab = m_vecEditorTabs.getEntryByIndex(uiNewActiveFileIndex);
			setActiveEditorTab(pEditorTab);
			m_pMainWindow->renderNow();
		}
	}
}

// remove editor tab
void								Editor::removeEditorTab(EditorTab *pEditorTab)
{
	// clear texts
	pEditorTab->m_pText_FilePath->setText(string(""));
	pEditorTab->m_pText_FileEntryCount->setText(string("0"));

	// remove tab from tab bar
	m_pTabBar->removeTab(pEditorTab->getTab());

	// unmark items to render
	for (RenderItem *pRenderItem : pEditorTab->getRenderItems().getEntries())
	{
		if (getMainWindow()->isRenderItemMarkedForRender(pRenderItem))
		{
			m_pMainWindow->setRenderItemMarkedForRender(pRenderItem, false);
		}
	}

	// stop tab thread
	pEditorTab->setMarkedToClose(true);
	while (!pEditorTab->hasThreadTerminated())
	{
		Sleep(10);
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

	// update menus
	// todo getMainWindow()->getMainLayer()->setCertainMenuItemsEnabled(getEditorTabs().getEntryCount() > 0);

	// render window
	m_pMainWindow->renderNow();
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
	///*
	if (m_pActiveEditorTab)
	{
		m_pActiveEditorTab->unbindEvents();
		//m_pActiveEditorTab->unbindEvents();
	}
	else
	{
		Editor::unbindEvents();
	}
	//*/

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

		// reposition controls
		pEditorTab->repositionAndResizeControls(Vec2i(0,0));

		// hide no-tabs-open layer
		getIMGF()->getWindowManager()->getMainWindow()->getBlankLayer()->setEnabled(false);
	}
	else
	{
		// show no-tabs-open layer
		// todo getLayer()->setEnabled(true); // e.g. IMGEditor
		getIMGF()->getWindowManager()->getMainWindow()->getBlankLayer()->setEnabled(true);
	}

	///*
	if(pEditorTab)
	{
		pEditorTab->bindEvents();
	}
	//*/
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

// file extension importable
bool								Editor::isFileExtensionImportable(string& strFileExtension)
{
	return StdVector::isIn(StdVector::toUpperCase(getImportEditorFileFormats()), String::toUpperCase(strFileExtension));
}

// file formats for open/save file
vector<string>						Editor::getFileFormatsForChooseFile(void)
{
	vector<string> vecData = getEditorFileFormats();
	string strEditorFileTypeName = getEditorName(m_uiEditorType);
	vecData.insert(vecData.begin(), strEditorFileTypeName + " Files");
	return vecData;
}

// file extension task
EInputItem							Editor::getFileExtensionNewTask(string& strEditorFileExtension)
{
	string strEditorFileExtensionUpper = String::toUpperCase(strEditorFileExtension);
	if (strEditorFileExtensionUpper == "WTD")
	{
		return NEW_WTD;
	}
	return NEW_FILE;
}