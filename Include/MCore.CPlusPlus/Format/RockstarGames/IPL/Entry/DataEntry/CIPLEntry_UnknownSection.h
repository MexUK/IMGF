#ifndef CIPLEntry_UnknownSection_H
#define CIPLEntry_UnknownSection_H

#include "mcore.h"
#include "Type/Types.h"
#include "Format/RockstarGames/IPL/Entry/CIPLEntry_Data.h"
#include <string>

class mcore::CIPLEntry_UnknownSection : public mcore::CIPLEntry_Data
{
public:
	CIPLEntry_UnknownSection(mcore::CIPLFormat *pIPLFormat) :
		CIPLEntry_Data(pIPLFormat, IPL_SECTION_UNKNOWN)
	{
	};

	void						unserialize(void);
	void						serialize(void);

	void						setLine(std::string& strLine) { m_strLine = strLine; }
	std::string&				getLine(void) { return m_strLine; }

private:
	std::string					m_strLine;
};

#endif