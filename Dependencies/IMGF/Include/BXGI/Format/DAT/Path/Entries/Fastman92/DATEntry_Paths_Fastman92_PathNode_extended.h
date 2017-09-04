#pragma once

#include "nsbxgi.h"
#include "Format/DAT/Path/Entries/Fastman92/DATEntry_Paths_Fastman92_PathNode.h"
#include "Format/DAT/Path/Entries/CompressedVector_extended.h"

struct bxgi::DATEntry_Paths_Fastman92_PathNode_extended : public DATEntry_Paths_Fastman92_PathNode
{
	CompressedVector_extended m_extended_posn;
};