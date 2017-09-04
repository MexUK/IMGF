#pragma once

#include "nsbxgi.h"
#include "Pool/VectorPool.h"
#include "Format/RW/Entries/_2dEffect.h"

class bxgi::_2dEffectsPool : public bxcf::VectorPool<bxgi::_2dEffect*>
{
};