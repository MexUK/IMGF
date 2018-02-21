#pragma once

#include "nsimgf.h"
#include "nsbxgi.h"
#include "Type/Types.h"
#include "GUI/Editor/Base/Editor.h"
#include "GUI/Editor/Tabs/CarColsDATEditorTab.h"
#include "Format/TXD/TXDFormat.h"
#include <string>

class imgf::CarColsDATEditor //: public imgf::Editor
{
public:
	CarColsDATEditor(void);

	void								init(void);

	void								bindEvents(void);
	void								unbindEvents(void);

	//CarColsDATEditorTab*				addEditorTab(std::string& strFilePath);
	//CarColsDATEditorTab*				addBlankEditorTab(std::string& strFilePath);
};