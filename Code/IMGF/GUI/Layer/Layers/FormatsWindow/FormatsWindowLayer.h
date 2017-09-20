#pragma once

#include "nsimgf.h"
#include "nsbxgx.h"
#include "Layer/Layer.h"

class imgf::FormatsWindowLayer : public bxgx::Layer
{
public:
	FormatsWindowLayer(void);

	void					init(void);
};