#pragma once

#include "nsimgf.h"
#include "GUI/Editor/Base/Editor.h"
#include "GUI/Editor/Tabs/ItemPlacementEditorTab.h"

#include "Globals.h"
#include "IMGF.h"
#include "GUI/Window/WindowManager.h"
#include "GUI/Window/Windows/MainWindow/MainWindow.h"

#include <string>

class imgf::ItemPlacementEditor : public imgf::Editor
{
public:
	ItemPlacementEditor(void) : Editor(ITEM_PLACEMENT_EDITOR) {}

	void								init(void);
	
	void								bindEvents(void);
	void								unbindEvents(void);

	ItemPlacementEditorTab*				addEditorTab(std::string& strFilePath);
	ItemPlacementEditorTab*				addBlankEditorTab(std::string& strFilePath);
};