#ifndef eIPLPathType_H
#define eIPLPathType_H

#include "bxcf.h"
#include "Type/Types.h"

enum bxcf::eIPLPathType : uint8
{
	IPL_PATH_UNKNOWN,
	IPL_PATH_GROUP,
	IPL_PATH_NODE
};

#endif