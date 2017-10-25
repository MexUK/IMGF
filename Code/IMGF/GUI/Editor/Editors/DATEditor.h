#pragma once

#include "nsimgf.h"
#include "GUI/Editor/Base/Editor.h"

class imgf::DATEditor : public imgf::Editor
{
public:
	EditorTab*					addEditorTab(std::string& strFilePath) { return nullptr; }
	EditorTab*					addBlankEditorTab(std::string& strFilePath) { return nullptr; }
};