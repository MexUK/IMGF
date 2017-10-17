#pragma once

#include "nsimgf.h"
#include "GUI/Editor/Base/Tab/EditorTab.h"

class imgf::TextureEditorTab : public imgf::EditorTab
{
public:
	bool						unserializeFile(void);
	void						onFileLoaded(void);

protected:
	void						addControls(void);
	void						initControls(void);
};