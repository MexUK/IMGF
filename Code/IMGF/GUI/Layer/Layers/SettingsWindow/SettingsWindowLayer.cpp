#include "SettingsWindowLayer.h"
#include "Control/Controls/DropDown.h"

using namespace std;
using namespace bxgx;
using namespace imgf;

SettingsWindowLayer::SettingsWindowLayer(void)
{
}

// initialization
void					SettingsWindowLayer::init(void)
{
	addButton(50, 400, 100, 20, "Close", "window2_button", 200);

	int32
		yGap1 = 30,
		yGap2 = 70;
	uint32
		y = 50;

	addText(50, y, 500, 20, "Text");
	y += yGap1;
	addText(50, y, 50, 50, "Language:");
	DropDown *pLanguageDropDown = addDropDown(135, y - 2, 150, 20, "Choose..", "window2_dropDown");
	pLanguageDropDown->addItems(vector<string>({ "English" }));
	y += yGap2;

	addText(50, y, 500, 20, "Graphics");
	y += yGap1;
	addCheckBox(50, y, 20, 20, "Window Always on Top", "window2_checkBox");
	y += yGap1;
	addText(50, y, 500, 20, "Tab Colours:");
	addButton(135, y - 2, 100, 20, "Choose..", "window2_button");
	y += yGap2;

	addText(50, y, 500, 20, "Tasks");
	y += yGap1;
	addText(50, y, 500, 20, "Quick Export Folder:");
	addButton(180, y - 2, 100, 20, "Choose..", "window2_button");
	y += yGap1;
	addText(50, y, 500, 20, "Rebuild After Feature:");
	addButton(190, y - 2, 100, 20, "Choose..", "window2_button");
	y += yGap2;
}