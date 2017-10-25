#pragma once

#include "nsimgf.h"
#include "GUI/Editor/Base/Editor.h"
#include <string>

class imgf::AnimationEditor : public imgf::Editor
{
public:
	EditorTab*					addEditorTab(std::string& strFilePath) { return nullptr; }
	EditorTab*					addBlankEditorTab(std::string& strFilePath) { return nullptr; }
};