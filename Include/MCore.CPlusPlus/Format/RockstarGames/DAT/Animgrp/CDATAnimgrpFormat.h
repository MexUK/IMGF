#ifndef CDATAnimgrpFormat_H
#define CDATAnimgrpFormat_H

#include "bxa.h"
#include "Type/Types.h"
#include "Format/CFormat.h"
#include "CDATAnimgrpSection.h"
#include <vector>

class bxa::CDATAnimgrpFormat : public bxa::CFormat, public bxa::CVectorPool<bxa::CDATAnimgrpSection*>
{
public:
	CDATAnimgrpFormat(void);
	
	void					unserialize(void);
	void					serialize(void);
};

#endif