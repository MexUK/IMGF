#pragma once

#include "nsimgf.h"
#include "nsbxgx.h"
#include "Layer/Layer.h"

class imgf::WebsitesWindowLayer : public bxgx::Layer
{
public:
	WebsitesWindowLayer(void);

	void					init(void);
};