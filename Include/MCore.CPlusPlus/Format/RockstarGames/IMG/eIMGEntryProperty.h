#ifndef eIMGEntryProperty_H
#define eIMGEntryProperty_H

#include "mcore.h"
#include "Type/Types.h"

enum mcore::eIMGEntryProperty : uint8
{
	IMG_ENTRY_ID,
	IMG_ENTRY_NAME,
	IMG_ENTRY_OFFSET,
	IMG_ENTRY_RESOURCETYPE,
	IMG_ENTRY_RWVERSION,
	IMG_ENTRY_SIZE,
	IMG_ENTRY_TYPE
};

#endif