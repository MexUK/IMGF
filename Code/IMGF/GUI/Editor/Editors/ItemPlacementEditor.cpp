#include "ItemPlacementEditor.h"
#include "Format/IPL/IPLFormat.h"

using namespace std;
using namespace bxcf::fileType;
using namespace bxgx;
using namespace bxgi;
using namespace imgf;

void								ItemPlacementEditor::init(void)
{
	setEditorFileType(ITEM_PLACEMENT);
	setEditorFileFormats({ "IPL" });
	//setImportEditorFileFormats({});

	m_pEditorButton = (Button*)m_pMainWindow->getItemById(1007);

	Editor::init();
}

// events
void								ItemPlacementEditor::bindEvents(void)
{
	Editor::bindEvents();
}

void								ItemPlacementEditor::unbindEvents(void)
{
	Editor::unbindEvents();
}

// add editor tab
ItemPlacementEditorTab*				ItemPlacementEditor::addEditorTab(string& strFilePath)
{
	IPLFormat iplFormat(strFilePath);
	if (!iplFormat.readMetaData())
	{
		return nullptr;
	}

	ItemPlacementEditorTab *pItemDefinitionEditorTab = Editor::_addEditorTab<IPLFormat, ItemPlacementEditorTab>(strFilePath, false);

	if (pItemDefinitionEditorTab)
	{
		//pItemDefinitionEditorTab->setItemPlacementEditor(this);
		pItemDefinitionEditorTab->setIPLFile((IPLFormat*)pItemDefinitionEditorTab->getFile());
		if (!pItemDefinitionEditorTab->init(false))
		{
			removeEditorTab(pItemDefinitionEditorTab);
			return nullptr;
		}
	}
	return pItemDefinitionEditorTab;
}

ItemPlacementEditorTab*				ItemPlacementEditor::addBlankEditorTab(string& strFilePath)
{
	ItemPlacementEditorTab *pItemDefinitionEditorTab = Editor::_addEditorTab<IPLFormat, ItemPlacementEditorTab>(strFilePath, true);

	if (pItemDefinitionEditorTab)
	{
		//pItemDefinitionEditorTab->setItemPlacementEditor(this);
		pItemDefinitionEditorTab->setIPLFile((IPLFormat*)pItemDefinitionEditorTab->getFile());
		pItemDefinitionEditorTab->init(true);
	}
	return pItemDefinitionEditorTab;
}