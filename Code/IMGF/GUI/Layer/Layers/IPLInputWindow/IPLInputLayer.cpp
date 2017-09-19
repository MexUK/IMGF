#include "IPLInputLayer.h"
#include "Window/Window.h"
#include "Format/IDE/EIDESection.h"

using namespace imgf;
using namespace bxgi;

void					IPLInputLayer::init(void)
{
	int32
		x = 50,
		y = m_pWindow->getTitleBarHeight() + 50,
		x2 = 170,
		y2;
	uint32
		uiCheckBoxLength = 20,
		uiCheckBoxYGap = 25;

	m_pText = addText(x, y, 400, 20, "", "window2_text");
	y += 30;

	addButton(x, y, 100, 25, "Select All", "window2_button", 100);
	addButton(x2, y, 100, 25, "Unselect All", "window2_button", 110);
	y += 40;

	addText(x, y, 100, 20, "Models", "window2_text");
	addText(x2, y, 100, 20, "Textures", "window2_text");
	y += 20;
	y2 = y;

	addCheckBox(x, y, uiCheckBoxLength, uiCheckBoxLength, "2DFX", "window2_checkBox", 300 + IDE_SECTION_2DFX); y += uiCheckBoxYGap;
	addCheckBox(x, y, uiCheckBoxLength, uiCheckBoxLength, "ANIM", "window2_checkBox", 300 + IDE_SECTION_ANIM); y += uiCheckBoxYGap;
	addCheckBox(x, y, uiCheckBoxLength, uiCheckBoxLength, "CARS", "window2_checkBox", 300 + IDE_SECTION_CARS); y += uiCheckBoxYGap;
	addCheckBox(x, y, uiCheckBoxLength, uiCheckBoxLength, "HAND", "window2_checkBox", 300 + IDE_SECTION_HAND); y += uiCheckBoxYGap;
	addCheckBox(x, y, uiCheckBoxLength, uiCheckBoxLength, "HIER", "window2_checkBox", 300 + IDE_SECTION_HIER); y += uiCheckBoxYGap;
	addCheckBox(x, y, uiCheckBoxLength, uiCheckBoxLength, "OBJS", "window2_checkBox", 300 + IDE_SECTION_OBJS); y += uiCheckBoxYGap;
	addCheckBox(x, y, uiCheckBoxLength, uiCheckBoxLength, "PEDS", "window2_checkBox", 300 + IDE_SECTION_PEDS); y += uiCheckBoxYGap;
	addCheckBox(x, y, uiCheckBoxLength, uiCheckBoxLength, "TOBJ", "window2_checkBox", 300 + IDE_SECTION_TOBJ); y += uiCheckBoxYGap;
	addCheckBox(x, y, uiCheckBoxLength, uiCheckBoxLength, "WEAP", "window2_checkBox", 300 + IDE_SECTION_WEAP); y += uiCheckBoxYGap;
	y = y2;

	addCheckBox(x2, y, uiCheckBoxLength, uiCheckBoxLength, "ANIM", "window2_checkBox", 400 + IDE_SECTION_ANIM); y += uiCheckBoxYGap;
	addCheckBox(x2, y, uiCheckBoxLength, uiCheckBoxLength, "CARS", "window2_checkBox", 400 + IDE_SECTION_CARS); y += uiCheckBoxYGap;
	addCheckBox(x2, y, uiCheckBoxLength, uiCheckBoxLength, "HAND", "window2_checkBox", 400 + IDE_SECTION_HAND); y += uiCheckBoxYGap;
	addCheckBox(x2, y, uiCheckBoxLength, uiCheckBoxLength, "HIER", "window2_checkBox", 400 + IDE_SECTION_HIER); y += uiCheckBoxYGap;
	addCheckBox(x2, y, uiCheckBoxLength, uiCheckBoxLength, "OBJS", "window2_checkBox", 400 + IDE_SECTION_OBJS); y += uiCheckBoxYGap;
	addCheckBox(x2, y, uiCheckBoxLength, uiCheckBoxLength, "PEDS", "window2_checkBox", 400 + IDE_SECTION_PEDS); y += uiCheckBoxYGap;
	addCheckBox(x2, y, uiCheckBoxLength, uiCheckBoxLength, "TOBJ", "window2_checkBox", 400 + IDE_SECTION_TOBJ); y += uiCheckBoxYGap;
	addCheckBox(x2, y, uiCheckBoxLength, uiCheckBoxLength, "TXDP", "window2_checkBox", 400 + IDE_SECTION_TXDP); y += uiCheckBoxYGap;
	addCheckBox(x2, y, uiCheckBoxLength, uiCheckBoxLength, "WEAP", "window2_checkBox", 400 + IDE_SECTION_WEAP); y += uiCheckBoxYGap;
	y += 20;

	addButton(x, y, 100, 25, "OK", "window2_button", 200);
	addButton(x + 120, y, 100, 25, "Cancel", "window2_button", 210);
}