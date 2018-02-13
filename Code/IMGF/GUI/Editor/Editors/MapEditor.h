#pragma once

#include "nsimgf.h"
#include "GUI/Editor/Base/Editor.h"
#include "GUI/Editor/Base/EditorTab.h"
#include "GUI/Editor/Tabs/MapEditorTab.h"

#include "Globals.h"
#include "IMGF.h"
#include "GUI/Window/WindowManager.h"
#include "GUI/Window/Windows/MainWindow/MainWindow.h"

#include <string>

class imgf::MapEditor : public imgf::Editor
{
public:
	MapEditor(void) : Editor(MAP_EDITOR) {}

	void								init(void);
	
	void								bindEvents(void);
	void								unbindEvents(void);

	MapEditorTab*						addEditorTab(std::string& strFilePath);
	MapEditorTab*						addBlankEditorTab(std::string& strFilePath);
};