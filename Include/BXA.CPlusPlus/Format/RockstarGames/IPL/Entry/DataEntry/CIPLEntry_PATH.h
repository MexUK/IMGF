#ifndef CIPLEntry_PATH_H
#define CIPLEntry_PATH_H

#include "BXA.h"
#include "Type/Types.h"
#include "Format/RockstarGames/IPL/Entry/CIPLEntry_Data.h"
#include "Format/RockstarGames/IPL/eIPLPathType.h"

class bxa::CIPLEntry_PATH_Group;

class bxa::CIPLEntry_PATH : public bxa::CIPLEntry_Data
{
public:
	CIPLEntry_PATH(CIPLFormat *pIPLFormat, eIPLPathType eIPLPathTypeValue) :
		CIPLEntry_Data(pIPLFormat, IPL_SECTION_PATH),
		m_eIPLPathType(eIPLPathTypeValue)
	{
	};

	virtual void					unserialize(void);
	virtual void					serialize(void);

	void							setIPLPathType(eIPLPathType eIPLPathTypeValue) { m_eIPLPathType = eIPLPathTypeValue; }
	bxa::eIPLPathType					getIPLPathType(void) { return m_eIPLPathType; }

	static void						setLatestPathGroup(bxa::CIPLEntry_PATH_Group* pLatestPathGroup) { m_pLatestPathGroup = pLatestPathGroup; }
	static bxa::CIPLEntry_PATH_Group*	getLatestPathGroup(void) { return m_pLatestPathGroup; }

private:
	static bxa::CIPLEntry_PATH_Group*	m_pLatestPathGroup;

	bxa::eIPLPathType					m_eIPLPathType;
};

#endif