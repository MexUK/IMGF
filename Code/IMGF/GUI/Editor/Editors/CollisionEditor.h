#pragma once

#include "nsimgf.h"
#include "GUI/Editor/Base/Editor.h"
#include "GUI/Editor/Editors/Tab/CollisionEditorTab.h"
#include <string>

class imgf::CollisionEditor : public imgf::Editor
{
public:
	CollisionEditorTab*					addEditorTab(std::string& strFilePath);
	CollisionEditorTab*					addBlankEditorTab(std::string& strFilePath);
};