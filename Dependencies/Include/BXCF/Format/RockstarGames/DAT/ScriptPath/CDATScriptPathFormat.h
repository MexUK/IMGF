#ifndef CDATScriptPathFormat_H
#define CDATScriptPathFormat_H

#include "bxcf.h"
#include "Type/Types.h"
#include "Format/CFormat.h"
#include "Pool/CVectorPool.h"
#include "CDATScriptPathEntry.h"
#include <vector>

class bxcf::CDATScriptPathFormat : public bxcf::CFormat, public bxcf::CVectorPool<bxcf::CDATScriptPathEntry*>
{
public:
	CDATScriptPathFormat(void);
	
	void					unserialize(void);
	void					serialize(void); // todo
};

#endif