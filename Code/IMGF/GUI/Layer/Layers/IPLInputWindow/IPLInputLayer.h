#pragma once

#include "nsimgf.h"
#include "nsbxgx.h"
#include "Layer/Layer.h"

class bxgx::Text;

class imgf::IPLInputLayer : public bxgx::Layer
{
public:
	void				init(void);

public:
	bxgx::Text*			m_pText;
};