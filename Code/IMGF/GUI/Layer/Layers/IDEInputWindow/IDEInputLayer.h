#pragma once

#include "nsimgf.h"
#include "nsbxgx.h"
#include "Layer/Layer.h"

class bxgx::Text;

class imgf::IDEInputLayer : public bxgx::Layer
{
public:
	void				init(void);

public:
	bxgx::Text*			m_pText;
};