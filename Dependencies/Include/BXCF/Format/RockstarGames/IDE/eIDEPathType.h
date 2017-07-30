#ifndef eIDEPathType_H
#define eIDEPathType_H

#include "bxcf.h"
#include "Type/Types.h"

enum bxcf::eIDEPathType : uint8
{
	IDE_PATH_UNKNOWN,
	IDE_PATH_GROUP,
	IDE_PATH_NODE
};

#endif