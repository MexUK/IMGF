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

using namespace std;
using namespace bxcf;

CIMGFWindow::CIMGFWindow(void)
{
	m_pMainLayer = new CMainLayer;
}

// main interface
void					CIMGFWindow::init(void)
{
	initWindow();
	initMainLayer();
	initEditors();
	CWindow::bindEvents();
}

// window initialization
void					CIMGFWindow::initWindow(void)
{
	CWindow::init();

	addTitleBar("IMG Factory 2.0 - Development Version");
}

void					CIMGFWindow::initMainLayer(void)
{
	m_pMainLayer->setWindow(this);
	m_pMainLayer->setIMGFWindow(this);
	m_pMainLayer->setEnabled(true);
	addEntry(m_pMainLayer);
	m_pMainLayer->init();
}

void					CIMGFWindow::initEditors(void)
{
	//addEditor(new CDATEditor);
	addEditor(new CIMGEditor);
}

// editors (layers)
void					CIMGFWindow::addEditor(CEditor *pEditor)
{
	pEditor->setWindow(this);
	pEditor->setEnabled(true);
	addEntry(pEditor);
	pEditor->init();
}