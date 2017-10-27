#include "DATEditor.h"

using namespace imgf;

void					DATEditor::init(void)
{
	setEditorFileFormats({ "DAT" });

	Editor::init();
}