#include "CollisionEditor.h"
#include "Format/COL/COLFormat.h"
#include "Globals.h"
#include "IMGF.h"
#include "GUI/Window/WindowManager.h"
#include "GUI/Window/Windows/MainWindow/MainWindow.h"
#include "GUI/Layer/Layers/MainLayer/MainLayerNoTabsOpen.h"
#include "BXGX.h"

using namespace std;
using namespace bxgx;
using namespace bxgx::events;
using namespace bxgi;
using namespace imgf;

HDC hDC; // todo - namespace

void					CollisionEditor::init(void)
{
	setEditorFileFormats({ "COL" });
	setImportEditorFileFormats({ "3dmesh" });

	Editor::init();
}

// events
void							CollisionEditor::bindEvents(void)
{
	bindEvent(BEFORE_RENDER, &CollisionEditor::renderBefore);

	Editor::bindEvents();

	if (m_pActiveEditorTab)
	{
		m_pActiveEditorTab->bindEvents();
	}
}

void							CollisionEditor::unbindEvents(void)
{
	unbindEvent(BEFORE_RENDER, &CollisionEditor::renderBefore);

	Editor::unbindEvents();

	if (m_pActiveEditorTab)
	{
		m_pActiveEditorTab->unbindEvents();
	}
}

// add editor tab
CollisionEditorTab*				CollisionEditor::addEditorTab(string& strFilePath)
{
	COLFormat colFormat(strFilePath);
	if (!colFormat.readMetaData())
	{
		return nullptr;
	}

	CollisionEditorTab *pCollisionEditorTab = Editor::_addEditorTab<COLFormat, CollisionEditorTab>(strFilePath, false);

	if (pCollisionEditorTab)
	{
		//pCollisionEditorTab->setCollisionEditor(this);
		pCollisionEditorTab->setCOLFile((COLFormat*)pCollisionEditorTab->getFile());
		if (!pCollisionEditorTab->init())
		{
			removeEditorTab(pCollisionEditorTab);
			return nullptr;
		}
	}
	return pCollisionEditorTab;
}

CollisionEditorTab*				CollisionEditor::addBlankEditorTab(string& strFilePath)
{
	CollisionEditorTab *pCollisionEditorTab = Editor::_addEditorTab<COLFormat, CollisionEditorTab>(strFilePath, true);

	if (pCollisionEditorTab)
	{
		//pCollisionEditorTab->setCollisionEditor(this);
		pCollisionEditorTab->setCOLFile((COLFormat*)pCollisionEditorTab->getFile());
		pCollisionEditorTab->getCOLFile()->setCOLVersion(COL_1);
		pCollisionEditorTab->init();
	}
	return pCollisionEditorTab;
}

// render
void							CollisionEditor::renderBefore(void)
{
	GraphicsLibrary *pGFX = BXGX::get()->getGraphicsLibrary();
	
	if (m_pMainWindow->getActiveEditor() != m_pMainWindow->getCollisionEditor() || BXGX::get()->getEventWindow() != m_pMainWindow)
	{
		return;
	}

	m_pWindow->resetRenderingStyleGroups();
	m_pWindow->resetRenderingControlComponent();
	m_pWindow->resetRenderingStyleFragment();
	m_pWindow->resetRenderingStyleStatus();

	if (m_pActiveEditorTab)
	{
		((CollisionEditorTab*)m_pActiveEditorTab)->render2D();
	}
}