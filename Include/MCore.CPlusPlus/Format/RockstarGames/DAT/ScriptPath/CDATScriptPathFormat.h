#ifndef CDATScriptPathFormat_H
#define CDATScriptPathFormat_H

#include "bxa.h"
#include "Type/Types.h"
#include "Format/CFormat.h"
#include "Pool/CVectorPool.h"
#include "CDATScriptPathEntry.h"
#include <vector>

class bxa::CDATScriptPathFormat : public bxa::CFormat, public bxa::CVectorPool<bxa::CDATScriptPathEntry*>
{
public:
	CDATScriptPathFormat(void);
	
	void					unserialize(void);
	void					serialize(void); // todo
};

#endif