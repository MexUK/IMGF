#include "ItemDefinitionEditor.h"
#include "Format/IDE/IDEFormat.h"
#include "GUI/Editor/Editors/Tab/ItemDefinitionEditorTab.h"

using namespace std;
using namespace bxgi;
using namespace imgf;

void									ItemDefinitionEditor::init(void)
{
	setEditorFileFormats({ "IDE" });

	Editor::init();
}

// events
void									ItemDefinitionEditor::bindEvents(void)
{
	Editor::bindEvents();

	if (m_pActiveEditorTab)
	{
		m_pActiveEditorTab->bindEvents();
	}
}

void									ItemDefinitionEditor::unbindEvents(void)
{
	Editor::unbindEvents();

	if (m_pActiveEditorTab)
	{
		m_pActiveEditorTab->unbindEvents();
	}
}

// add editor tab
ItemDefinitionEditorTab*				ItemDefinitionEditor::addEditorTab(string& strFilePath)
{
	IDEFormat ideFormat(strFilePath);
	if (!ideFormat.readMetaData())
	{
		return nullptr;
	}

	ItemDefinitionEditorTab *pItemDefinitionEditorTab = Editor::_addEditorTab<IDEFormat, ItemDefinitionEditorTab>(strFilePath, false);

	if (pItemDefinitionEditorTab)
	{
		//pItemDefinitionEditorTab->setItemDefinitionEditor(this);
		pItemDefinitionEditorTab->setIDEFile((IDEFormat*)pItemDefinitionEditorTab->getFile());
		if (!pItemDefinitionEditorTab->init())
		{
			removeEditorTab(pItemDefinitionEditorTab);
			return nullptr;
		}
	}
	return pItemDefinitionEditorTab;
}

ItemDefinitionEditorTab*				ItemDefinitionEditor::addBlankEditorTab(string& strFilePath)
{
	ItemDefinitionEditorTab *pItemDefinitionEditorTab = Editor::_addEditorTab<IDEFormat, ItemDefinitionEditorTab>(strFilePath, true);

	if (pItemDefinitionEditorTab)
	{
		//pItemDefinitionEditorTab->setItemDefinitionEditor(this);
		pItemDefinitionEditorTab->setIDEFile((IDEFormat*)pItemDefinitionEditorTab->getFile());
		pItemDefinitionEditorTab->init();
	}
	return pItemDefinitionEditorTab;
}