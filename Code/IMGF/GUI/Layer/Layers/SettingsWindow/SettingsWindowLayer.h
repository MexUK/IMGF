#pragma once

#include "nsimgf.h"
#include "nsbxgx.h"
#include "Layer/Layer.h"
#include "Event/EventBindable.h"

class imgf::SettingsWindowLayer : public bxgx::Layer
{
public:
	SettingsWindowLayer(void);
	~SettingsWindowLayer(void);

	void					init(void);

	void					onPressButton(bxgx::Button *pButton);
	void					onMarkCheckBox(bxgx::CheckBox *pCheckBox);
	void					onUnmarkCheckBox(bxgx::CheckBox *pCheckBox);
	void					onSelectDropDownItem(bxgx::DropDownItem *pDropDownItem);
};