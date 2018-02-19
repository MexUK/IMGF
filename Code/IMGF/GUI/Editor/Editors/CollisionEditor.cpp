#include "CollisionEditor.h"
#include "Format/COL/COLFormat.h"
#include "Globals.h"
#include "IMGF.h"
#include "GUI/Window/WindowManager.h"
#include "GUI/Window/Windows/MainWindow/MainWindow.h"
#include "BXGX.h"

using namespace std;
using namespace bxcf::fileType;
using namespace bxgx;
using namespace bxgx::events;
using namespace bxgi;
using namespace imgf;

void					CollisionEditor::init(void)
{
	setEditorFileType(COLLISION);
	setEditorFileFormats({ "COL" });
	setImportEditorFileFormats({ "3dmesh" });

	m_pEditorButton = (Button*)m_pMainWindow->getItemById(1009);

	Editor::init();
}

// events
void							CollisionEditor::bindEvents(void)
{
	Editor::bindEvents();
}

void							CollisionEditor::unbindEvents(void)
{
	Editor::unbindEvents();
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
		if (!pCollisionEditorTab->init(false))
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
		pCollisionEditorTab->init(true);
	}
	return pCollisionEditorTab;
}