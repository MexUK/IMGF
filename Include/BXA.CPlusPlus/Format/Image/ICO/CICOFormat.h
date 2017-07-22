#ifndef CICOFormat_H
#define CICOFormat_H

#include "BXA.h"
#include "Type/Types.h"
#include "Format/Image/BMP/CBMPFormat.h"

class bxa::CICOFormat : public bxa::CBMPFormat
{
public:
	CICOFormat(void);
	
	void							unload(void) {}
	
private:
	void							unserialize(void);
	void							serialize(void);
};

#endif