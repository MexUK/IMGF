#include "SessionManagerWindowLayer.h"
#include "Control/Controls/DropDown.h"
#include "Control/Controls/Button.h"
#include "Control/Controls/Grid.h"
#include "Static/Input.h"
#include "Settings/SettingsManager.h"
#include "IMGF.h"
#include "GUI/Window/WindowManager.h"

using namespace std;
using namespace bxcf;
using namespace bxgx;
using namespace bxgx::events;
using namespace imgf;

SessionManagerWindowLayer::SessionManagerWindowLayer(void)
{
	bindEvent(PRESS_BUTTON, &SessionManagerWindowLayer::onPressButton);
}

SessionManagerWindowLayer::~SessionManagerWindowLayer(void)
{
	unbindEvent(PRESS_BUTTON, &SessionManagerWindowLayer::onPressButton);
}

// initialization
void					SessionManagerWindowLayer::init(void)
{
	Grid *pGrid = addGrid(50, 50, 600, 500, "window2_grid");
	vector<string> vecGridHeaders = { "Session ID", "Session Name", "File Count", "File Names" };
	pGrid->addHeaders(vecGridHeaders);
	pGrid->getHeaders().getEntryByIndex(0)->setColumnWidth(80);
	pGrid->getHeaders().getEntryByIndex(1)->setColumnWidth(170);
	pGrid->getHeaders().getEntryByIndex(2)->setColumnWidth(80);
	pGrid->getHeaders().getEntryByIndex(3)->setColumnWidth(270);

	addButton(50, 580, 100, 20, "Add Session", "window2_button", 200);
	addButton(180, 580, 100, 20, "Update Session", "window2_button", 210);
	addButton(310, 580, 100, 20, "Remove Session", "window2_button", 210);
	addButton(480, 580, 100, 20, "Close", "window2_button", 210);
}

// window events
void					SessionManagerWindowLayer::onPressButton(Button *pButton)
{
	Window
		*pWindow1 = BXGX::get()->getEntryByIndex(0),
		*pWindow2 = BXGX::get()->getEntryByIndex(1);
}