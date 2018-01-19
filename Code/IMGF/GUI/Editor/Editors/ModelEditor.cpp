#include "ModelEditor.h"
#include "Format/DFF/DFFFormat.h"
#include "BXGX.h"

using namespace std;
using namespace bxcf::fileType;
using namespace bxgi;
using namespace bxgx;
using namespace bxgx::events;
using namespace imgf;

void									ModelEditor::init(void)
{
	setEditorFileType(MODEL);
	setEditorFileFormats({ "DFF" });
	setImportEditorFileFormats({ "3dmesh" });

	m_pEditorButton = (Button*)m_pMainWindow->getItemById(1008);

	Editor::init();
}

// events
void									ModelEditor::bindEvents(void)
{
	bindEvent(BEFORE_RENDER, &TextureEditor::renderBefore);

	Editor::bindEvents();

	if (m_pActiveEditorTab)
	{
		m_pActiveEditorTab->bindEvents();
	}
}

void									ModelEditor::unbindEvents(void)
{
	unbindEvent(BEFORE_RENDER, &TextureEditor::renderBefore);

	Editor::unbindEvents();

	if (m_pActiveEditorTab)
	{
		m_pActiveEditorTab->unbindEvents();
	}
}

// add editor tab
ModelEditorTab*							ModelEditor::addEditorTab(string& strFilePath)
{
	DFFFormat dffFormat(strFilePath);
	if (!dffFormat.readMetaData())
	{
		return nullptr;
	}

	ModelEditorTab *pModelEditorTab = Editor::_addEditorTab<DFFFormat, ModelEditorTab>(strFilePath, false);

	if (pModelEditorTab)
	{
		//pCollisionEditorTab->setCollisionEditor(this);
		pModelEditorTab->setDFFFile((DFFFormat*)pModelEditorTab->getFile());
		if (!pModelEditorTab->init(false))
		{
			removeEditorTab(pModelEditorTab);
			return nullptr;
		}
	}
	return pModelEditorTab;
}

ModelEditorTab*							ModelEditor::addBlankEditorTab(string& strFilePath)
{
	ModelEditorTab *pModelEditorTab = Editor::_addEditorTab<DFFFormat, ModelEditorTab>(strFilePath, true);

	if (pModelEditorTab)
	{
		//pCollisionEditorTab->setCollisionEditor(this);
		pModelEditorTab->setDFFFile((DFFFormat*)pModelEditorTab->getFile());
		//pModelEditorTab->getDFFFile()->setRWVersion(nullptr, RW_3_4_0_3);
		pModelEditorTab->init(true);
	}
	return pModelEditorTab;
}

// render
void									ModelEditor::renderBefore(void)
{
	GraphicsLibrary *pGFX = BXGX::get()->getGraphicsLibrary();

	if (m_pMainWindow->getActiveEditor() != m_pMainWindow->getTextureEditor() || BXGX::get()->getEventWindow() != m_pMainWindow)
	{
		return;
	}

	m_pMainWindow->resetRenderingStyleGroups();
	m_pMainWindow->resetRenderingControlComponent();
	m_pMainWindow->resetRenderingStyleFragment();
	m_pMainWindow->resetRenderingStyleStatus();

	if (m_pActiveEditorTab)
	{
		((ModelEditorTab*)m_pActiveEditorTab)->render_Type1();
	}
}