#ifndef CDATChaseFormat_H
#define CDATChaseFormat_H

#include "BXA.h"
#include "Type/Types.h"
#include "Format/CFormat.h"
#include "Pool/CVectorPool.h"
#include "CDATChaseEntry.h"
#include <vector>

class bxa::CDATChaseFormat : public bxa::CFormat, public bxa::CVectorPool<bxa::CDATChaseEntry*>
{
public:
	CDATChaseFormat(void);
	
	void					unserialize(void);
	void					serialize(void);
};

#endif