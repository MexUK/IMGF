#ifndef CDATScriptPathFormat_H
#define CDATScriptPathFormat_H

#include "mcore.h"
#include "Type/Types.h"
#include "Format/CFormat.h"
#include "Pool/CVectorPool.h"
#include "CDATScriptPathEntry.h"
#include <vector>

class mcore::CDATScriptPathFormat : public mcore::CFormat, public mcore::CVectorPool<mcore::CDATScriptPathEntry*>
{
public:
	CDATScriptPathFormat(void);
	
	void					unserialize(void);
	void					serialize(void); // todo
};

#endif