#pragma once

#include "nsimgf.h"
#include "nsbxgx.h"
#include "Layer/Layer.h"

class imgf::AboutWindowLayer : public bxgx::Layer
{
public:
	AboutWindowLayer(void);

	void					init(void);
};