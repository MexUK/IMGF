#pragma once

#include "nsbxgi.h"
#include "Type/Types.h"
#include "Format/IPL/Entry/IPLEntry_Data.h"
#include "Format/IPL/EIPLPathType.h"

class bxgi::IPLEntry_PATH_Group;

class bxgi::IPLEntry_PATH : public bxgi::IPLEntry_Data
{
public:
	IPLEntry_PATH(IPLFormat *pIPLFormat, EIPLPathType EIPLPathTypeValue);

	virtual void					unserialize(void);
	virtual void					serialize(void);

	void							setIPLPathType(EIPLPathType EIPLPathTypeValue) { m_EIPLPathType = EIPLPathTypeValue; }
	bxgi::EIPLPathType					getIPLPathType(void) { return m_EIPLPathType; }

	static void						setLatestPathGroup(bxgi::IPLEntry_PATH_Group* pLatestPathGroup) { m_pLatestPathGroup = pLatestPathGroup; }
	static bxgi::IPLEntry_PATH_Group*	getLatestPathGroup(void) { return m_pLatestPathGroup; }

private:
	static bxgi::IPLEntry_PATH_Group*	m_pLatestPathGroup;

	bxgi::EIPLPathType					m_EIPLPathType;
};