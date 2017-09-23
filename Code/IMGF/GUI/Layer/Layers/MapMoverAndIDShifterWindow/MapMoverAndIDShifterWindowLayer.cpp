#include "MapMoverAndIDShifterWindowLayer.h"
#include "Control/Controls/DropDown.h"
#include "Control/Controls/Button.h"
#include "Control/Controls/CheckBox.h"
#include "Static/Input.h"
#include "Settings/SettingsManager.h"
#include "IMGF.h"
#include "GUI/Window/WindowManager.h"

using namespace std;
using namespace bxcf;
using namespace bxgx;
using namespace bxgx::events;
using namespace imgf;

MapMoverAndIDShifterWindowLayer::MapMoverAndIDShifterWindowLayer(void)
{
	bindEvent(PRESS_BUTTON, &MapMoverAndIDShifterWindowLayer::onPressButton);
}

MapMoverAndIDShifterWindowLayer::~MapMoverAndIDShifterWindowLayer(void)
{
	unbindEvent(PRESS_BUTTON, &MapMoverAndIDShifterWindowLayer::onPressButton);
}

// initialization
void					MapMoverAndIDShifterWindowLayer::init(void)
{
	addButton(450, 520, 100, 20, "Dump", "window2_button", 200);
	addButton(570, 520, 100, 20, "Cancel", "window2_button", 210);
}

// window events
void					MapMoverAndIDShifterWindowLayer::onPressButton(Button *pButton)
{
	Window
		*pWindow1 = BXGX::get()->getEntryByIndex(0),
		*pWindow2 = BXGX::get()->getEntryByIndex(1);
}