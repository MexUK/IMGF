#ifndef eIPLPathType_H
#define eIPLPathType_H

#include "bxgi.h"
#include "Type/Types.h"

enum bxgi::eIPLPathType : uint8
{
	IPL_PATH_UNKNOWN,
	IPL_PATH_GROUP,
	IPL_PATH_NODE
};

#endif