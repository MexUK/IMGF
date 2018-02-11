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

	m_pEditorButton = (Button*)m_pMainWindow->getItemById(1004);

	Editor::init();
}

// events
void									MapEditor::bindEvents(void)
{
	Editor::bindEvents();

	if (m_pActiveEditorTab)
	{
		m_pActiveEditorTab->bindEvents();
	}
}

void									MapEditor::unbindEvents(void)
{
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