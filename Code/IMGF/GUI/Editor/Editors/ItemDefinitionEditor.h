#pragma once

#include "nsimgf.h"
#include "GUI/Editor/Base/Editor.h"
#include "GUI/Editor/Editors/Tab/ItemDefinitionEditorTab.h"

#include "Globals.h"
#include "IMGF.h"
#include "GUI/Window/WindowManager.h"
#include "GUI/Window/Windows/MainWindow/MainWindow.h"

#include <string>

class imgf::ItemDefinitionEditor : public imgf::Editor
{
public:
	ItemDefinitionEditor(void) : Editor(ITEM_DEFINITION_EDITOR) {}

	void								init(void);
	
	void								bindEvents(void);
	void								unbindEvents(void);

	ItemDefinitionEditorTab*			addEditorTab(std::string& strFilePath);
	ItemDefinitionEditorTab*			addBlankEditorTab(std::string& strFilePath);
};