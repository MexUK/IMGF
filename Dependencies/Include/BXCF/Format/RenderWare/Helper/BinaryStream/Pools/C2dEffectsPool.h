#ifndef C2dEffectsPool_H
#define C2dEffectsPool_H

#include "bxcf.h"
#include "Pool/CVectorPool.h"
#include "Format/RenderWare/Helper/BinaryStream/Entries/C2dEffect.h"

class bxcf::C2dEffectsPool : public bxcf::CVectorPool<bxcf::C2dEffect*>
{
};

#endif