#pragma once

#include "nsimgf.h"
#include "nsbxgx.h"
#include "Layer/Layer.h"
#include "Event/EventBindable.h"

class imgf::DumpWindowLayer : public bxgx::Layer
{
public:
	DumpWindowLayer(void);
	~DumpWindowLayer(void);

	void					init(void);

	void					onPressButton(bxgx::Button *pButton);
};