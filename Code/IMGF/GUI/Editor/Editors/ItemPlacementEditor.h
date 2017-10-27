#pragma once

#include "nsimgf.h"
#include "GUI/Editor/Base/Editor.h"
#include <string>

class imgf::ItemPlacementEditor : public imgf::Editor
{
public:
	void								init(void);
	
	EditorTab*							addEditorTab(std::string& strFilePath) { return nullptr; }
	EditorTab*							addBlankEditorTab(std::string& strFilePath) { return nullptr; }
};