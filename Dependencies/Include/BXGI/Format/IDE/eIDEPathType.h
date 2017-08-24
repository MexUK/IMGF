#ifndef eIDEPathType_H
#define eIDEPathType_H

#include "bxgi.h"
#include "Type/Types.h"

enum bxgi::eIDEPathType : uint8
{
	IDE_PATH_UNKNOWN,
	IDE_PATH_GROUP,
	IDE_PATH_NODE
};

#endif