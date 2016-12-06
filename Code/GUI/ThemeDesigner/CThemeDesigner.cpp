#include "CThemeDesigner.h"
#include "Math/CMath.h"
#include "Event/eEvent.h"
#include "Event/CEventManager.h"
#include "GUI/CGUIManager.h"
#include "Layer/CGUILayer.h"
#include "Shape/CGUIShape.h"
#include "Styles/CGUIStyles.h"
#include "Controls/CTabControl.h"
#include "GUI/ThemeDesigner/Tabs/CThemeDesignerTab_AddItem.h"
#include "GUI/ThemeDesigner/Tabs/CThemeDesignerTab_Save.h"
#include "Type/Vector/CColour.h"
#include <vector>

using namespace std;
using namespace mcore;

CThemeDesigner::CThemeDesigner(void) :
	m_bThemeDesignerModeEnabled(false),
	m_pWindow(nullptr),
	m_pTabControl(nullptr),
	m_pItemHoverRectangle(nullptr),
	m_pActiveItemRectangle(nullptr)
{
}

void					CThemeDesigner::init(void)
{
	initWindow();
	initWindowDesign();
	CEventManager::getInstance()->bindEvent(EVENT_onToolReady, [](void *pBoundArg) { ((CThemeDesigner*) pBoundArg)->bindEvents(); }, this);
}

void					CThemeDesigner::bindEvents(void)
{
	for (CThemeDesignerTab *pThemeDesignerTab : getEntries())
	{
		pThemeDesignerTab->bindEvents();
	}
}

void					CThemeDesigner::initWindow(void)
{
	CPoint2D vecWindowPosition((int32)10, 10);
	CSize2D vecWindowSize(500, 500);
	CWindow *pWindow = gui::CGUIManager::getInstance()->addWindow(vecWindowPosition, vecWindowSize);
	pWindow->getStyles()->setStyle("fill-colour", CColour(33, 78, 103));
	setWindow(pWindow);

	CGUIStyles *pStyles_TabControl = gui::CGUIManager::createStyles();
	pStyles_TabControl->setStyle("fill-colour", CColour(19, 46, 60));
	pStyles_TabControl->setStyle("text-colour", CColour(121, 180, 199));
	pStyles_TabControl->setStyle("border-colour", CColour(121, 180, 199));
	pStyles_TabControl->setStyle<string>("text-align", "center center");
	pStyles_TabControl->setStyle<uint32>("inner-spacing-x", 15);
	//pStyles_TabControl->setStyle<bool>("border-state-left", false);
	//pStyles_TabControl->setStyle<bool>("border-state-top", false);

	CGUILayer *pLayer_ThemeDesignerWindow = pWindow->addLayer(pWindow, true);
	CTabControl *pTabControl = pLayer_ThemeDesignerWindow->addTabBar(CPoint2D((int32)0, 0), CSize2D(vecWindowSize.m_x, 25), pStyles_TabControl);
	setTabControl(pTabControl);
	m_umapTabControlEntries["items"] = pTabControl->addTab("Items");
	m_umapTabControlEntries["add_item"] = pTabControl->addTab("Add Item", true);
	m_umapTabControlEntries["item"] = pTabControl->addTab("Item");
	m_umapTabControlEntries["load"] = pTabControl->addTab("Load");
	m_umapTabControlEntries["save"] = pTabControl->addTab("Save");
	m_umapTabControlEntries["download"] = pTabControl->addTab("Download");
	m_umapTabControlEntries["upload"] = pTabControl->addTab("Upload");
}

void					CThemeDesigner::initWindowDesign(void)
{
	addEntry(new CThemeDesignerTab_AddItem(this));
	addEntry(new CThemeDesignerTab_Save(this));

	for (CThemeDesignerTab *pThemeDesignerTab : getEntries())
	{
		pThemeDesignerTab->initDesign();
	}

	getWindow()->bindAllEvents();
}

// layers
CGUILayer*				CThemeDesigner::addLayer(string strLayerKey, bool bLayerIsEnabled)
{
	CGUILayer *pLayer = getWindow()->addLayer(getWindow(), bLayerIsEnabled); // todo - param same as object
	m_umapTabLayers[strLayerKey] = pLayer;
	getTabControl()->bindTabLayer(m_umapTabControlEntries[strLayerKey], pLayer);
	return pLayer;
}

// enabled status
void					CThemeDesigner::setThemeDesignerModeEnabled(bool bThemeDesignerModeEnabled)
{
	m_bThemeDesignerModeEnabled = bThemeDesignerModeEnabled;
	gui::CGUIManager::getInstance()->getEntryByIndex(1)->setEventTriggerEventTypeId(bThemeDesignerModeEnabled ? EVENT_TYPE_THEME_DESIGNER : EVENT_TYPE_WINDOW);
}