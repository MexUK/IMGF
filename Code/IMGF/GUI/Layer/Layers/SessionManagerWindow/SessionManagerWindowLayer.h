#pragma once

#include "nsimgf.h"
#include "nsbxgx.h"
#include "Layer/Layer.h"
#include "Event/EventBindable.h"

class imgf::SessionManagerWindowLayer : public bxgx::Layer, public bxcf::EventBindable
{
public:
	SessionManagerWindowLayer(void);
	~SessionManagerWindowLayer(void);

	void					init(void);

	void					onPressButton(bxgx::Button *pButton);
};