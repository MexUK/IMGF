#pragma once

#include "nsimgf.h"
#include "Type/Types.h"

enum imgf::eSortType : uint8
{
	SORT_NAME_AZ,
	SORT_NAME_ZA,
	SORT_OFFSET_LOWHIGH,
	SORT_OFFSET_HIGHLOW,
	SORT_SIZE_SMALLBIG,
	SORT_SIZE_BIGSMALL,
	SORT_IDE_FILE,
	SORT_COL_FILE,
	SORT_FILE_EXTENSIONS
};