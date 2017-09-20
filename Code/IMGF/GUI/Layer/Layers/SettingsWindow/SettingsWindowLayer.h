#pragma once

#include "nsimgf.h"
#include "nsbxgx.h"
#include "Layer/Layer.h"

class imgf::SettingsWindowLayer : public bxgx::Layer
{
public:
	SettingsWindowLayer(void);

	void					init(void);
};