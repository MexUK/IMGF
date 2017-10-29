#include "DATEditor.h"
#include "GUI/Editor/Editors/Tab/DATEditorTab.h"
#include "Format/DAT/Loader/DATLoaderFormat.h"

using namespace std;
using namespace bxgi;
using namespace imgf;

void							DATEditor::init(void)
{
	setEditorFileFormats({ "DAT" });

	Editor::init();
}

// events
void							DATEditor::bindEvents(void)
{
	Editor::bindEvents();

	if (m_pActiveEditorTab)
	{
		m_pActiveEditorTab->bindEvents();
	}
}

void							DATEditor::unbindEvents(void)
{
	Editor::unbindEvents();

	if (m_pActiveEditorTab)
	{
		m_pActiveEditorTab->unbindEvents();
	}
}

// add editor tab
DATEditorTab*					DATEditor::addEditorTab(string& strFilePath)
{
	DATLoaderFormat datLoaderFormat(strFilePath);
	if (!datLoaderFormat.readMetaData())
	{
		return nullptr;
	}

	DATEditorTab *pDATEditorTab = Editor::_addEditorTab<DATLoaderFormat, DATEditorTab>(strFilePath, false);

	if (pDATEditorTab)
	{
		//pDATEditorTab->setDATEditor(this);
		pDATEditorTab->setDATFile((DATLoaderFormat*)pDATEditorTab->getFile());
		if (!pDATEditorTab->init())
		{
			removeEditorTab(pDATEditorTab);
			return nullptr;
		}
	}
	return pDATEditorTab;
}

DATEditorTab*				DATEditor::addBlankEditorTab(string& strFilePath)
{
	DATEditorTab *pDATEditorTab = Editor::_addEditorTab<DATLoaderFormat, DATEditorTab>(strFilePath, true);

	if (pDATEditorTab)
	{
		//pDATEditorTab->setDATEditor(this);
		pDATEditorTab->setDATFile((DATLoaderFormat*)pDATEditorTab->getFile());
		pDATEditorTab->init();
	}
	return pDATEditorTab;
}