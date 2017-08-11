#include "CIMGFWindow.h"
#include "GUI/Editors/CIMGEditor.h"
#include "Controls/CButtonControl.h"
#include "Controls/CGridControl.h"
#include "Styles/CGUIStyles.h"
#include "GUI/CWindowManager.h"
#include "GUI/CGUIManager.h"
#include "GraphicsLibrary/CGraphicsLibrary.h"
#include "Event/CEventManager.h"
#include "Event/eEvent.h"
#include "Globals.h"
#include "CIMGF.h"
#include "Task/CTaskManager.h"
#include "Task/CTaskDispatchManager.h"
#include "File/CFileManager.h"
#include "Path/CPathManager.h"
#include "Type/String/CString2.h"
#include "GUI/ThemeDesigner/CThemeDesigner.h"
#include "Type/Vector/CColour.h"
#include "GUI/Layer/CMainLayer.h"
#include "GUI/Window/EMainMenuType.h"
#include "GUI/Window/ELayers.h"

using namespace std;
using namespace bxcf;
using namespace imgf::mainLayer::mainMenuType;
using namespace imgf::layers;

CIMGFWindow::CIMGFWindow(void) :
	m_uiMainMenuType(FORMATS)
{
}

// main interface
void					CIMGFWindow::init(void)
{
	initWindow();
	initLayers();
	CWindow::bindEvents();
}

// window initialization
void					CIMGFWindow::initWindow(void)
{
	CWindow::init();

	addTitleBar("IMG Factory 2.0 - Development Version");
}

void					CIMGFWindow::initLayers(void)
{
	initMainLayer();
	initMainMenuLayers();
	initEditors();
}

// layer initialization
void					CIMGFWindow::initMainLayer(void)
{
	m_pMainLayer = addLayer<CMainLayer>(-1, true);
	m_pMainLayer->setIMGFWindow(this);
	m_pMainLayer->init();
}

void					CIMGFWindow::initMainMenuLayers(void)
{
	int32
		x, y, y2, w, h, h2;
	CButtonControl
		*pButton;
	string
		strStyleGroup;

	// formats menu
	CGUILayer *pFormatsLayer = addLayer(FORMATS_MENU, true);

	x = 0;
	y = getTitleBarHeight() + 30;
	y2 = y;
	w = 139;
	h = 40;
	h2 = h;
	strStyleGroup = "leftMenuButton";

	pButton = pFormatsLayer->addButton(x, y, w, h, "DAT", strStyleGroup);
	y += h2;
	pButton = pFormatsLayer->addButton(x, y, w, h, "IMG", strStyleGroup);
	y += h2;
	pButton = pFormatsLayer->addButton(x, y, w, h, "Item Definition", strStyleGroup);
	y += h2;
	pButton = pFormatsLayer->addButton(x, y, w, h, "Item Placement", strStyleGroup);
	y += h2;
	pButton = pFormatsLayer->addButton(x, y, w, h, "Models", strStyleGroup);
	y += h2;
	pButton = pFormatsLayer->addButton(x, y, w, h, "Collisions", strStyleGroup);
	y += h2;
	pButton = pFormatsLayer->addButton(x, y, w, h, "Textures", strStyleGroup);
	y += h2;
	pButton = pFormatsLayer->addButton(x, y, w, h, "Animations", strStyleGroup);
	y += h2;
	pButton = pFormatsLayer->addButton(x, y, w, h, "Radar", strStyleGroup);

	// utility menu
	CGUILayer *pUtilityLayer = addLayer(UTILITY_MENU, false);

	x = 0;
	y = y2;
	w = 139;
	h = 40;
	h2 = h;
	strStyleGroup = "leftMenuButton";

	pButton = pUtilityLayer->addButton(x, y, w, h, "Export Game", strStyleGroup);
	y += h2;
	pButton = pUtilityLayer->addButton(x, y, w, h, "Mod Includer", strStyleGroup);
	y += h2;
}

void					CIMGFWindow::initEditors(void)
{
	//addLayer<CDATEditor>(-1, false)->init();
	addLayer<CIMGEditor>(-1, true)->init();
}

// main menu type
void					CIMGFWindow::setMainMenuType(EMainMenuType uiMainMenuType)
{
	if (uiMainMenuType == m_uiMainMenuType)
	{
		return;
	}
	m_uiMainMenuType = uiMainMenuType;
	swapLayersEnabled(FORMATS_MENU, UTILITY_MENU);
}