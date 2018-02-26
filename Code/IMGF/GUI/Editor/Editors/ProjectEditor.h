#pragma once

#include "nsimgf.h"
#include "GUI/Editor/Base/Editor.h"
#include "GUI/Editor/Base/EditorTab.h"
#include "GUI/Editor/Tabs/ProjectEditorTab.h"

#include "Globals.h"
#include "IMGF.h"
#include "GUI/Window/WindowManager.h"
#include "GUI/Window/Windows/MainWindow/MainWindow.h"

#include <string>

class imgf::ProjectEditor : public imgf::Editor
{
public:
	ProjectEditor(void) : Editor(PROJECT_EDITOR) {}

	void								init(void);
	
	void								bindEvents(void);
	void								unbindEvents(void);

	ProjectEditorTab*					addEditorTab(std::string& strFilePath);
	ProjectEditorTab*					addBlankEditorTab(std::string& strFilePath);
};