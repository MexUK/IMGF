#ifndef CIPLEntry_PATH_H
#define CIPLEntry_PATH_H

#include "bxgi.h"
#include "Type/Types.h"
#include "Format/IPL/Entry/CIPLEntry_Data.h"
#include "Format/IPL/eIPLPathType.h"

class bxgi::CIPLEntry_PATH_Group;

class bxgi::CIPLEntry_PATH : public bxgi::CIPLEntry_Data
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
	bxgi::eIPLPathType					getIPLPathType(void) { return m_eIPLPathType; }

	static void						setLatestPathGroup(bxgi::CIPLEntry_PATH_Group* pLatestPathGroup) { m_pLatestPathGroup = pLatestPathGroup; }
	static bxgi::CIPLEntry_PATH_Group*	getLatestPathGroup(void) { return m_pLatestPathGroup; }

private:
	static bxgi::CIPLEntry_PATH_Group*	m_pLatestPathGroup;

	bxgi::eIPLPathType					m_eIPLPathType;
};

#endif