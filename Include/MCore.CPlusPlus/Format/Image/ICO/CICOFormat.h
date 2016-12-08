#ifndef CICOFormat_H
#define CICOFormat_H

#include "mcore.h"
#include "Type/Types.h"
#include "Format/Image/BMP/CBMPFormat.h"

class mcore::CICOFormat : public mcore::CBMPFormat
{
public:
	CICOFormat(void);
	
	void							unload(void) {}
	
private:
	void							unserialize(void);
	void							serialize(void);
};

#endif