#ifndef CIPLEntry_Section_H
#define CIPLEntry_Section_H

#include "bxcf.h"
#include "Format/RockstarGames/IPL/CIPLEntry.h"

class bxcf::CIPLFormat;

class bxcf::CIPLEntry_Section : public bxcf::CIPLEntry
{
public:
	CIPLEntry_Section(bxcf::CIPLFormat *pIPLFormat) :
		CIPLEntry(pIPLFormat)
	{};

	void					unserialize(void);
	void					serialize(void);
};

#endif