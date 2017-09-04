#ifndef CDATAnimgrpFormat_H
#define CDATAnimgrpFormat_H

#include "bxcf.h"
#include "Type/Types.h"
#include "Format/CFormat.h"
#include "CDATAnimgrpSection.h"
#include <vector>

class bxcf::CDATAnimgrpFormat : public bxcf::CFormat, public bxcf::CVectorPool<bxcf::CDATAnimgrpSection*>
{
public:
	CDATAnimgrpFormat(void);
	
	void					unserialize(void);
	void					serialize(void);
};

#endif