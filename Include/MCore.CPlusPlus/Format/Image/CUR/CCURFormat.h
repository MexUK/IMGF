#ifndef CCURFormat_H
#define CCURFormat_H

#include "mcore.h"
#include "Type/Types.h"
#include "Format/Image/BMP/CBMPFormat.h"

class mcore::CCURFormat : public CBMPFormat
{
public:
	CCURFormat(void);
	
	void							unload(void) {}
	
private:
	void							unserialize(void);
	void							serialize(void);
};

#endif