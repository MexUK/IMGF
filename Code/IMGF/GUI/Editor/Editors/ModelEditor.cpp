#include "ModelEditor.h"
#include "Format/DFF/DFFFormat.h"
#include "BXGX.h"

using namespace std;
using namespace bxgi;
using namespace bxgx;
using namespace bxgx::events;
using namespace imgf;

void									ModelEditor::init(void)
{
	setEditorFileFormats({ "DFF" });

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

// render
void									ModelEditor::renderBefore(void)
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
		((ModelEditorTab*)m_pActiveEditorTab)->render_Type1();
	}
}

// add editor tab
ModelEditorTab*							ModelEditor::addEditorTab(string& strFilePath)
{
	DFFFormat ideFormat(strFilePath);
	if (!ideFormat.readMetaData())
	{
		return nullptr;
	}

	ModelEditorTab *pModelEditorTab = Editor::_addEditorTab<DFFFormat, ModelEditorTab>(strFilePath, false);

	if (pModelEditorTab)
	{
		//pModelEditorTab->setModelEditor(this);
		pModelEditorTab->setDFFFile((DFFFormat*)pModelEditorTab->getFile());
		if (!pModelEditorTab->init())
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
		//pModelEditorTab->setModelEditor(this);
		pModelEditorTab->setDFFFile((DFFFormat*)pModelEditorTab->getFile());
		pModelEditorTab->init();
	}
	return pModelEditorTab;
}