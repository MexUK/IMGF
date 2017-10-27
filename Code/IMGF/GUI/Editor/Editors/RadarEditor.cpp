#include "RadarEditor.h"

using namespace imgf;

void					RadarEditor::init(void)
{
	setEditorFileFormats({ "IMG", "TXD", "WTD" });

	Editor::init();
}