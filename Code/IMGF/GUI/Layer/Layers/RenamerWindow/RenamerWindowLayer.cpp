#include "RenamerWindowLayer.h"
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

RenamerWindowLayer::RenamerWindowLayer(void)
{
	bindEvent(PRESS_BUTTON, &RenamerWindowLayer::onPressButton);
}

RenamerWindowLayer::~RenamerWindowLayer(void)
{
	unbindEvent(PRESS_BUTTON, &RenamerWindowLayer::onPressButton);
}

// initialization
void					RenamerWindowLayer::init(void)
{
	addButton(450, 520, 100, 20, "Dump", "window2_button", 200);
	addButton(570, 520, 100, 20, "Cancel", "window2_button", 210);
}

// window events
void					RenamerWindowLayer::onPressButton(Button *pButton)
{
	Window
		*pWindow1 = BXGX::get()->getEntryByIndex(0),
		*pWindow2 = BXGX::get()->getEntryByIndex(1);
}