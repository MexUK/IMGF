#pragma once

#include "nsimgf.h"
#include "GUI/Editor/Base/Editor.h"
#include "GUI/Editor/Base/Tab/EditorTab.h"
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
	void								init(void);
	
	EditorTab*							addEditorTab(std::string& strFilePath) { return nullptr; }
	EditorTab*							addBlankEditorTab(std::string& strFilePath) { return nullptr; }
};