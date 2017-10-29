#pragma once

#include "nsimgf.h"
#include "GUI/Editor/Base/Editor.h"
#include "GUI/Editor/Editors/Tab/AnimationEditorTab.h"

#include "Globals.h"
#include "IMGF.h"
#include "GUI/Window/WindowManager.h"
#include "GUI/Window/Windows/MainWindow/MainWindow.h"
#include "GUI/Layer/Layers/MainLayer/MainLayerNoTabsOpen.h"

#include <string>

class PLGFormat : public bxcf::Format // temp here
{
public:
	PLGFormat(void) : bxcf::Format(true) {}

	void					_readMetaData(void) {}

private:
	void					_unserialize(void) {}
	void					_serialize(void) {}
};

class imgf::AnimationEditor : public imgf::Editor
{
public:
	void								init(void);
	
	void								bindEvents(void);
	void								unbindEvents(void);

	AnimationEditorTab*					addEditorTab(std::string& strFilePath);
	AnimationEditorTab*					addBlankEditorTab(std::string& strFilePath);
};