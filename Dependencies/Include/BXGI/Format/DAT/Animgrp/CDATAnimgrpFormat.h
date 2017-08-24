#ifndef CDATAnimgrpFormat_H
#define CDATAnimgrpFormat_H

#include "bxgi.h"
#include "Type/Types.h"
#include "Format/CFormat.h"
#include "CDATAnimgrpSection.h"

class bxgi::CDATAnimgrpFormat : public bxcf::CFormat, public bxcf::CVectorPool<bxgi::CDATAnimgrpSection*>
{
public:
	CDATAnimgrpFormat(void);
	
	void					unserialize(void);
	void					serialize(void);
};

#endif