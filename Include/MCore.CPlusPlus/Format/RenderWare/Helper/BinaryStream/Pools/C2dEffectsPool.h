#ifndef C2dEffectsPool_H
#define C2dEffectsPool_H

#include "mcore.h"
#include "Pool/CVectorPool.h"
#include "Format/RenderWare/Helper/BinaryStream/Entries/C2dEffect.h"

class mcore::C2dEffectsPool : public mcore::CVectorPool<mcore::C2dEffect*>
{
};

#endif