#ifndef CDATAnimgrpFormat_H
#define CDATAnimgrpFormat_H

#include "mcore.h"
#include "Type/Types.h"
#include "Format/CFormat.h"
#include "CDATAnimgrpSection.h"
#include <vector>

class mcore::CDATAnimgrpFormat : public mcore::CFormat, public mcore::CVectorPool<mcore::CDATAnimgrpSection*>
{
public:
	CDATAnimgrpFormat(void);
	
	void					unserialize(void);
	void					serialize(void);
};

#endif