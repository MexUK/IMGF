#ifndef CIPLEntry_Section_H
#define CIPLEntry_Section_H

#include "bxgi.h"
#include "Format/IPL/CIPLEntry.h"

class bxgi::CIPLFormat;

class bxgi::CIPLEntry_Section : public bxgi::CIPLEntry
{
public:
	CIPLEntry_Section(bxgi::CIPLFormat *pIPLFormat) :
		CIPLEntry(pIPLFormat)
	{};

	void					unserialize(void);
	void					serialize(void);
};

#endif