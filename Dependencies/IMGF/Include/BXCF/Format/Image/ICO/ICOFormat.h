#pragma once

#include "nsbxcf.h"
#include "Type/Types.h"
#include "Format/Image/BMP/BMPFormat.h"

class bxcf::ICOFormat : public bxcf::BMPFormat
{
public:
	ICOFormat(void);
	
	void							unload(void) {}
	
private:
	void							unserialize(void);
	void							serialize(void);
};