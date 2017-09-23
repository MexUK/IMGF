#pragma once

#include "nsimgf.h"
#include "nsbxgx.h"
#include "Layer/Layer.h"
#include "Event/EventBindable.h"

class imgf::MapMoverAndIDShifterWindowLayer : public bxgx::Layer, public bxcf::EventBindable
{
public:
	MapMoverAndIDShifterWindowLayer(void);
	~MapMoverAndIDShifterWindowLayer(void);

	void					init(void);

	void					onPressButton(bxgx::Button *pButton);
};