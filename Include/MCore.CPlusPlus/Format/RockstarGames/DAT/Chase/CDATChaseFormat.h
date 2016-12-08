#ifndef CDATChaseFormat_H
#define CDATChaseFormat_H

#include "mcore.h"
#include "Type/Types.h"
#include "Format/CFormat.h"
#include "Pool/CVectorPool.h"
#include "CDATChaseEntry.h"
#include <vector>

class mcore::CDATChaseFormat : public mcore::CFormat, public mcore::CVectorPool<mcore::CDATChaseEntry*>
{
public:
	CDATChaseFormat(void);
	
	void					unserialize(void);
	void					serialize(void);
};

#endif