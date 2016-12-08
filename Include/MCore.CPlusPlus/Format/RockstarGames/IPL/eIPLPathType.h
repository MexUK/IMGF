#ifndef eIPLPathType_H
#define eIPLPathType_H

#include "mcore.h"
#include "Type/Types.h"

enum mcore::eIPLPathType : uint8
{
	IPL_PATH_UNKNOWN,
	IPL_PATH_GROUP,
	IPL_PATH_NODE
};

#endif