#pragma once

#include "nsbxcf.h"
#include "Type/Types.h"
#include "Format/Image/BMP/BMPFormat.h"

class bxcf::CURFormat : public BMPFormat
{
public:
	CURFormat(void);
	
	void							unload(void) {}
	
private:
	void							unserialize(void);
	void							serialize(void);
};