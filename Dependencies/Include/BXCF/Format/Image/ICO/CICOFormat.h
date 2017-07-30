#ifndef CICOFormat_H
#define CICOFormat_H

#include "bxcf.h"
#include "Type/Types.h"
#include "Format/Image/BMP/CBMPFormat.h"

class bxcf::CICOFormat : public bxcf::CBMPFormat
{
public:
	CICOFormat(void);
	
	void							unload(void) {}
	
private:
	void							unserialize(void);
	void							serialize(void);
};

#endif