#pragma once

#include "nsimgf.h"
#include "GUI/Editor/Base/Editor.h"
#include "GUI/Editor/Base/Tab/EditorTab.h"
#include "GUI/Editor/Editors/Tab/ModelEditorTab.h"

#include "Globals.h"
#include "IMGF.h"
#include "GUI/Window/WindowManager.h"
#include "GUI/Window/Windows/MainWindow/MainWindow.h"
#include "GUI/Layer/Layers/MainLayer/MainLayerNoTabsOpen.h"

#include <string>

class imgf::ModelEditor : public imgf::Editor
{
public:
	ModelEditor(void) : Editor(MODEL_EDITOR) {}

	void								init(void);
	
	void								bindEvents(void);
	void								unbindEvents(void);

	void								renderBefore(void);

	ModelEditorTab*						addEditorTab(std::string& strFilePath);
	ModelEditorTab*						addBlankEditorTab(std::string& strFilePath);
};