#ifndef CIPLEntry_Section_H
#define CIPLEntry_Section_H

#include "mcore.h"
#include "Format/RockstarGames/IPL/CIPLEntry.h"

class mcore::CIPLFormat;

class mcore::CIPLEntry_Section : public mcore::CIPLEntry
{
public:
	CIPLEntry_Section(mcore::CIPLFormat *pIPLFormat) :
		CIPLEntry(pIPLFormat)
	{};

	void					unserialize(void);
	void					serialize(void);
};

#endif