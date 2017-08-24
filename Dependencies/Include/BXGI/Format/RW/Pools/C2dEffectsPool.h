#ifndef C2dEffectsPool_H
#define C2dEffectsPool_H

#include "bxgi.h"
#include "Pool/CVectorPool.h"
#include "Format/RW/Entries/C2dEffect.h"

class bxgi::C2dEffectsPool : public bxcf::CVectorPool<bxgi::C2dEffect*>
{
};

#endif