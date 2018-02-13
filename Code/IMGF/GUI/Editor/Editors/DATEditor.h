#pragma once

#include "nsimgf.h"
#include "GUI/Editor/Base/Editor.h"
#include "GUI/Editor/Base/EditorTab.h"
#include "GUI/Editor/Tabs/DATEditorTab.h"

#include "Globals.h"
#include "IMGF.h"
#include "GUI/Window/WindowManager.h"
#include "GUI/Window/Windows/MainWindow/MainWindow.h"

#include <string>

class imgf::MainWindow;
class imgf::SearchEntry;
class bxgx::Grid;
class bxgx::TextBox;
class bxgx::DropDown;
class bxgi::IMGEntry;
class bxgi::IMGFormat;

class imgf::DATEditor : public imgf::Editor
{
public:
	DATEditor(void) : Editor(DAT_EDITOR) {}

	void								init(void);
	
	void								bindEvents(void);
	void								unbindEvents(void);

	DATEditorTab*						addEditorTab(std::string& strFilePath);
	DATEditorTab*						addBlankEditorTab(std::string& strFilePath);
};