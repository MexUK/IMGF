#include "MapEditor.h"
#include "Format/DAT/Loader/DATLoaderFormat.h"
#include "BXGX.h"

using namespace std;
using namespace bxcf::fileType;
using namespace bxgi;
using namespace bxgx;
using namespace bxgx::events;
using namespace imgf;

void									MapEditor::init(void)
{
	setEditorFileType(DAT_LOADER);
	setEditorFileFormats({ "DAT" });
	setImportEditorFileFormats({ "3dmesh" });

	Editor::init();
}

// events
void									MapEditor::bindEvents(void)
{
	bindEvent(BEFORE_RENDER, &TextureEditor::renderBefore);

	Editor::bindEvents();

	if (m_pActiveEditorTab)
	{
		m_pActiveEditorTab->bindEvents();
	}
}

void									MapEditor::unbindEvents(void)
{
	unbindEvent(BEFORE_RENDER, &TextureEditor::renderBefore);

	Editor::unbindEvents();

	if (m_pActiveEditorTab)
	{
		m_pActiveEditorTab->unbindEvents();
	}
}

// add editor tab
MapEditorTab*							MapEditor::addEditorTab(string& strFilePath)
{
	DATLoaderFormat datLoaderFile(strFilePath);
	if (!datLoaderFile.readMetaData())
	{
		return nullptr;
	}

	MapEditorTab *pMapEditorTab = Editor::_addEditorTab<DATLoaderFormat, MapEditorTab>(strFilePath, false);

	if (pMapEditorTab)
	{
		//pMapEditorTab->setCollisionEditor(this);
		pMapEditorTab->m_pDATLoaderFile = (DATLoaderFormat*)pMapEditorTab->getFile();
		if (!pMapEditorTab->init(false))
		{
			removeEditorTab(pMapEditorTab);
			return nullptr;
		}
	}
	return pMapEditorTab;
}

MapEditorTab*							MapEditor::addBlankEditorTab(string& strFilePath)
{
	MapEditorTab *pMapEditorTab = Editor::_addEditorTab<DATLoaderFormat, MapEditorTab>(strFilePath, true);

	if (pMapEditorTab)
	{
		//pMapEditorTab->setCollisionEditor(this);
		pMapEditorTab->m_pDATLoaderFile = (DATLoaderFormat*)pMapEditorTab->getFile();
		//pMapEditorTab->getDFFFile()->setRWVersion(nullptr, RW_3_4_0_3);
		pMapEditorTab->init(true);
	}
	return pMapEditorTab;
}

// render
void									MapEditor::renderBefore(void)
{
	GraphicsLibrary *pGFX = BXGX::get()->getGraphicsLibrary();

	if (m_pMainWindow->getActiveEditor() != m_pMainWindow->getTextureEditor() || BXGX::get()->getEventWindow() != m_pMainWindow)
	{
		return;
	}

	m_pWindow->resetRenderingStyleGroups();
	m_pWindow->resetRenderingControlComponent();
	m_pWindow->resetRenderingStyleFragment();
	m_pWindow->resetRenderingStyleStatus();

	if (m_pActiveEditorTab)
	{
		((MapEditorTab*)m_pActiveEditorTab)->render_Type1();
	}
}