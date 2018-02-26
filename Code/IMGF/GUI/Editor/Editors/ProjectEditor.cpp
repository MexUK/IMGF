#include "ProjectEditor.h"
#include "GUI/Editor/Tabs/ProjectEditorTab.h"
#include "Format/DAT/Loader/DATLoaderFormat.h"

using namespace std;
using namespace bxcf::fileType;
using namespace bxgx;
using namespace bxgi;
using namespace imgf;

void							ProjectEditor::init(void)
{
	setEditorFileType(DAT_LOADER);
	setEditorFileFormats({ "DAT" });
	setImportEditorFileFormats({});

	m_pEditorButton = (Button*)m_pMainWindow->getItemById(10204);

	Editor::init();
}

// events
void							ProjectEditor::bindEvents(void)
{
	Editor::bindEvents();
}

void							ProjectEditor::unbindEvents(void)
{
	Editor::unbindEvents();
}

// add editor tab
ProjectEditorTab*				ProjectEditor::addEditorTab(string& strFilePath)
{
	DATLoaderFormat datLoaderFormat(strFilePath);
	if (!datLoaderFormat.readMetaData())
	{
		return nullptr;
	}

	ProjectEditorTab *pProjectEditorTab = Editor::_addEditorTab<DATLoaderFormat, ProjectEditorTab>(strFilePath, false);

	if (pProjectEditorTab)
	{
		//pDATEditorTab->setDATEditor(this);
		pProjectEditorTab->setDATFile((DATLoaderFormat*)pProjectEditorTab->getFile());
		if (!pProjectEditorTab->init(false))
		{
			removeEditorTab(pProjectEditorTab);
			return nullptr;
		}
	}
	return pProjectEditorTab;
}

ProjectEditorTab*				ProjectEditor::addBlankEditorTab(string& strFilePath)
{
	ProjectEditorTab *pProjectEditorTab = Editor::_addEditorTab<DATLoaderFormat, ProjectEditorTab>(strFilePath, true);

	if (pProjectEditorTab)
	{
		//pProjectEditorTab->setDATEditor(this);
		pProjectEditorTab->setDATFile((DATLoaderFormat*)pProjectEditorTab->getFile());
		pProjectEditorTab->init(true);
	}
	return pProjectEditorTab;
}