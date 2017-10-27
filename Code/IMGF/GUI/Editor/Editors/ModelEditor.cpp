#include "ModelEditor.h"

using namespace imgf;

void					ModelEditor::init(void)
{
	setEditorFileFormats({ "DFF" });

	Editor::init();
}