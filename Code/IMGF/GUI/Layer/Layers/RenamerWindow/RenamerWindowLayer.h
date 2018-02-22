#pragma once

#include "nsimgf.h"
#include "nsbxgx.h"
#include "Layer/Layer.h"
#include "Event/EventBindable.h"

class imgf::RenamerWindowLayer : public bxgx::Layer
{
public:
	RenamerWindowLayer(void);
	~RenamerWindowLayer(void);

	void					init(void);

	void					onPressButton(bxgx::Button *pButton);
};