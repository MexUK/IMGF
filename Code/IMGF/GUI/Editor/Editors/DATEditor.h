#pragma once

#include "nsimgf.h"
#include "GUI/Editor/Base/Editor.h"
#include "GUI/Editor/Base/Tab/EditorTab.h"
#include "GUI/Editor/Editors/Tab/DATEditorTab.h"

#include "Globals.h"
#include "IMGF.h"
#include "GUI/Window/WindowManager.h"
#include "GUI/Window/Windows/MainWindow/MainWindow.h"
#include "GUI/Layer/Layers/MainLayer/MainLayerNoTabsOpen.h"

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