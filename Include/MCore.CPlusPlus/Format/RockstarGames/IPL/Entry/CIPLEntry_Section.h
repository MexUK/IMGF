#ifndef CIPLEntry_Section_H
#define CIPLEntry_Section_H

#include "bxa.h"
#include "Format/RockstarGames/IPL/CIPLEntry.h"

class bxa::CIPLFormat;

class bxa::CIPLEntry_Section : public bxa::CIPLEntry
{
public:
	CIPLEntry_Section(bxa::CIPLFormat *pIPLFormat) :
		CIPLEntry(pIPLFormat)
	{};

	void					unserialize(void);
	void					serialize(void);
};

#endif