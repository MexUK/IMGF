#include "AnimationEditor.h"

using namespace imgf;

void					AnimationEditor::init(void)
{
	setEditorFileFormats({ "IFP" });

	Editor::init();
}