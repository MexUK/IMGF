#pragma once

#include "nsimgf.h"
#include "GUI/Editor/Base/Editor.h"
#include "GUI/Editor/Editors/Tab/CollisionEditorTab.h"
#include <string>

class imgf::CollisionEditor : public imgf::Editor
{
public:
	CollisionEditor(void) : Editor(COLLISION_EDITOR) {}

	void								init(void);

	void								bindEvents(void);
	void								unbindEvents(void);

	CollisionEditorTab*					addEditorTab(std::string& strFilePath);
	CollisionEditorTab*					addBlankEditorTab(std::string& strFilePath);
};