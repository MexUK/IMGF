#include "CollisionEditor.h"
#include "Format/COL/COLFormat.h"
#include "Globals.h"
#include "IMGF.h"
#include "GUI/Window/WindowManager.h"
#include "GUI/Window/Windows/MainWindow/MainWindow.h"
#include "GUI/Layer/Layers/MainLayer/MainLayerNoTabsOpen.h"

using namespace std;
using namespace bxgi;
using namespace imgf;

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
		pCollisionEditorTab->init();
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
		pCollisionEditorTab->init();
	}
	return pCollisionEditorTab;
}