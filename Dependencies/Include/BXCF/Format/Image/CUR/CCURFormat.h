#pragma once

#include "nsbxcf.h"
#include "Type/Types.h"
#include "Format/Image/BMP/CBMPFormat.h"

class bxcf::CCURFormat : public CBMPFormat
{
public:
	CCURFormat(void);
	
	void							unload(void) {}
	
private:
	void							unserialize(void);
	void							serialize(void);
};