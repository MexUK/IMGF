#ifndef C2dEffectsPool_H
#define C2dEffectsPool_H

#include "BXA.h"
#include "Pool/CVectorPool.h"
#include "Format/RenderWare/Helper/BinaryStream/Entries/C2dEffect.h"

class bxa::C2dEffectsPool : public bxa::CVectorPool<bxa::C2dEffect*>
{
};

#endif