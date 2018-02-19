#pragma once

#include "nsimgf.h"
#include "GUI/Editor/Base/Editor.h"
#include "GUI/Editor/Base/EditorTab.h"
#include "GUI/Editor/Tabs/RadarEditorTab.h"

#include "Globals.h"
#include "IMGF.h"
#include "GUI/Window/WindowManager.h"
#include "GUI/Window/Windows/MainWindow/MainWindow.h"

#include <string>

class imgf::RadarEditor : public imgf::Editor
{
public:
	RadarEditor(void) : Editor(RADAR_EDITOR) {}

	void								init(void);

	void								bindEvents(void);
	void								unbindEvents(void);

	RadarEditorTab*						addEditorTab(std::string& strFilePath);
	RadarEditorTab*						addBlankEditorTab(std::string& strFilePath);
	RadarEditorTab*						addBlankEditorTab(std::string& strFilePath, bxgi::EIMGVersion uiIMGVersion = bxgi::EIMGVersion::IMG_1);
};