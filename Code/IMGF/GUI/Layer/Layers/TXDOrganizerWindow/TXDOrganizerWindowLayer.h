#pragma once

#include "nsimgf.h"
#include "nsbxgx.h"
#include "Layer/Layer.h"
#include "Event/EventBindable.h"

class imgf::TXDOrganizerWindowLayer : public bxgx::Layer, public bxcf::EventBindable
{
public:
	TXDOrganizerWindowLayer(void);
	~TXDOrganizerWindowLayer(void);

	void					init(void);

	void					onPressButton(bxgx::Button *pButton);
};