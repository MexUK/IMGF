#pragma once

#include "nsimgf.h"
#include "nsbxgx.h"
#include "Layer/Layer.h"
#include "Event/EventBindable.h"

class imgf::DATPathsMoverWindowLayer : public bxgx::Layer, public bxcf::EventBindable
{
public:
	DATPathsMoverWindowLayer(void);
	~DATPathsMoverWindowLayer(void);

	void					init(void);

	void					onPressButton(bxgx::Button *pButton);
};