#pragma once

#include "nsimgf.h"
#include "nsbxgx.h"
#include "Layer/Layer.h"
#include "Event/EventBindable.h"

class imgf::TXDBuilderWindowLayer : public bxgx::Layer
{
public:
	TXDBuilderWindowLayer(void);
	~TXDBuilderWindowLayer(void);

	void					init(void);

	void					onPressButton(bxgx::Button *pButton);
};