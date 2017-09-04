#pragma once

#include "nsbxgi.h"
#include "Type/Types.h"
#include "Format/IDE/Entry/IDEEntry_Data.h"
#include "Format/IDE/EIDEPathType.h"

class bxgi::IDEEntry_PATH_Group;

class bxgi::IDEEntry_PATH : public bxgi::IDEEntry_Data
{
public:
	IDEEntry_PATH(bxgi::IDEFormat *pIDEFormat, bxgi::EIDEPathType EIDEPathTypeValue);

	virtual void					unserialize(void);
	virtual void					serialize(void);

	void							setIDEPathType(bxgi::EIDEPathType EIDEPathTypeValue) { m_EIDEPathType = EIDEPathTypeValue; }
	bxgi::EIDEPathType					getIDEPathType(void) { return m_EIDEPathType; }

	static void						setLatestPathGroup(bxgi::IDEEntry_PATH_Group* pLatestPathGroup) { m_pLatestPathGroup = pLatestPathGroup; }
	static bxgi::IDEEntry_PATH_Group*	getLatestPathGroup(void) { return m_pLatestPathGroup; }

private:
	static bxgi::IDEEntry_PATH_Group*	m_pLatestPathGroup;

	bxgi::EIDEPathType					m_EIDEPathType;
};