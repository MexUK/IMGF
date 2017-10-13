#pragma once

#include "nsimgf.h"
#include "Type/Types.h"
#include "GUI/Editor/Base/Editor.h"

class imgf::TextureEditor : public Editor
{
public:
	TextureEditor(void);

	void						init(void);
	void						render(void);

public:
	void*						m_pActiveTexture;
};