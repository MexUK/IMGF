#ifndef CDATScriptPathFormat_H
#define CDATScriptPathFormat_H

#include "bxgi.h"
#include "Type/Types.h"
#include "Format/CFormat.h"
#include "Pool/CVectorPool.h"
#include "CDATScriptPathEntry.h"

class bxgi::CDATScriptPathFormat : public bxcf::CFormat, public bxcf::CVectorPool<bxgi::CDATScriptPathEntry*>
{
public:
	CDATScriptPathFormat(void);
	
	void					unserialize(void);
	void					serialize(void); // todo
};

#endif