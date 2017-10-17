#pragma once

#include "nsimgf.h"
#include "nsbxgi.h"
#include "Type/Types.h"
#include "GUI/Editor/Base/Editor.h"
#include "GUI/Editor/Editors/Tab/TextureEditorTab.h"
#include <string>

class imgf::TextureEditor : public imgf::Editor
{
public:
	TextureEditor(void);

	void								init(void);
	void								render(void);
	
	TextureEditorTab*					addFile(std::string& strFilePath);

private:
	TextureEditorTab*					addTabObjectAndTabControl(bxgi::TXDFormat *img, bool bNewFile);

public:
	void*								m_pActiveTexture;
};