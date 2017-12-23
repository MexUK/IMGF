#pragma once

#include "nsimgf.h"
#include "nsbxgi.h"
#include "Type/Types.h"
#include "GUI/Editor/Base/Editor.h"
#include "GUI/Editor/Editors/Tab/TextEditorTab.h"
#include "Format/TXD/TXDFormat.h"
#include <string>

class imgf::TextEditor : public imgf::Editor
{
public:
	TextEditor(void);

	void								init(void);
	
	void								bindEvents(void);
	void								unbindEvents(void);

	void								renderBefore(void);
	
	TextEditorTab*					addEditorTab(std::string& strFilePath);
	TextEditorTab*					addBlankEditorTab(std::string& strFilePath);

public:
	void*								m_pActiveTexture;
};