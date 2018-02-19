#pragma once

#include "nsimgf.h"
#include "nsbxgi.h"
#include "Type/Types.h"
#include "GUI/Editor/Base/Editor.h"
#include "GUI/Editor/Tabs/TextureEditorTab.h"
#include "Format/TXD/TXDFormat.h"
#include <string>

class imgf::TextureEditor : public imgf::Editor
{
public:
	TextureEditor(void);

	void								init(void);
	
	void								bindEvents(void);
	void								unbindEvents(void);

	TextureEditorTab*					addEditorTab(std::string& strFilePath);
	TextureEditorTab*					addBlankEditorTab(std::string& strFilePath);

public:
	void*								m_pActiveTexture;
};