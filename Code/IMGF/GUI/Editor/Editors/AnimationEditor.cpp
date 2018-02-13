#include "DATEditor.h"
#include "GUI/Editor/Tabs/DATEditorTab.h"
#include "Format/DAT/Loader/DATLoaderFormat.h"

using namespace std;
using namespace bxcf::fileType;
using namespace bxgx;
using namespace bxgi;
using namespace imgf;

void								AnimationEditor::init(void)
{
	setEditorFileType(ANIMATION);
	setEditorFileFormats({ "IFP" });
	setImportEditorFileFormats({ "3dmesh" });

	m_pEditorButton = (Button*)m_pMainWindow->getItemById(1011);

	Editor::init();
}

// events
void								AnimationEditor::bindEvents(void)
{
	Editor::bindEvents();

	if (m_pActiveEditorTab)
	{
		m_pActiveEditorTab->bindEvents();
	}
}

void								AnimationEditor::unbindEvents(void)
{
	Editor::unbindEvents();

	if (m_pActiveEditorTab)
	{
		m_pActiveEditorTab->unbindEvents();
	}
}

// add editor tab
AnimationEditorTab*					AnimationEditor::addEditorTab(string& strFilePath)
{
	DATLoaderFormat datLoaderFormat(strFilePath);
	if (!datLoaderFormat.readMetaData())
	{
		return nullptr;
	}

	AnimationEditorTab *pAnimationEditorTab = Editor::_addEditorTab<PLGFormat, AnimationEditorTab>(strFilePath, false);

	if (pAnimationEditorTab)
	{
		//pAnimationEditorTab->setAnimationEditor(this);
		// todo pAnimationEditorTab->setIFPFile((IFPFormat*)pAnimationEditorTab->getFile());
		if (!pAnimationEditorTab->init(false))
		{
			removeEditorTab(pAnimationEditorTab);
			return nullptr;
		}
	}
	return pAnimationEditorTab;
}

AnimationEditorTab*					AnimationEditor::addBlankEditorTab(string& strFilePath)
{
	AnimationEditorTab *pAnimationEditorTab = Editor::_addEditorTab<PLGFormat, AnimationEditorTab>(strFilePath, true);

	if (pAnimationEditorTab)
	{
		//pAnimationEditorTab->setAnimationEditor(this);
		// todo pAnimationEditorTab->setIFPFile((IFPFormat*)pAnimationEditorTab->getFile());
		pAnimationEditorTab->init(true);
	}
	return pAnimationEditorTab;
}