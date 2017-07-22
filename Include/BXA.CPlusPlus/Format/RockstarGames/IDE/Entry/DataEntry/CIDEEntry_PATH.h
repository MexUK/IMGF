#ifndef CIDEEntry_PATH_H
#define CIDEEntry_PATH_H

#include "BXA.h"
#include "Type/Types.h"
#include "Format/RockstarGames/IDE/Entry/CIDEEntry_Data.h"
#include "Format/RockstarGames/IDE/eIDEPathType.h"

class bxa::CIDEEntry_PATH_Group;

class bxa::CIDEEntry_PATH : public bxa::CIDEEntry_Data
{
public:
	CIDEEntry_PATH(bxa::CIDEFormat *pIDEFormat, bxa::eIDEPathType eIDEPathTypeValue) :
		CIDEEntry_Data(pIDEFormat, IDE_SECTION_PATH),
		m_eIDEPathType(eIDEPathTypeValue)
	{
	};

	virtual void					unserialize(void);
	virtual void					serialize(void);

	void							setIDEPathType(bxa::eIDEPathType eIDEPathTypeValue) { m_eIDEPathType = eIDEPathTypeValue; }
	bxa::eIDEPathType					getIDEPathType(void) { return m_eIDEPathType; }

	static void						setLatestPathGroup(bxa::CIDEEntry_PATH_Group* pLatestPathGroup) { m_pLatestPathGroup = pLatestPathGroup; }
	static bxa::CIDEEntry_PATH_Group*	getLatestPathGroup(void) { return m_pLatestPathGroup; }

private:
	static bxa::CIDEEntry_PATH_Group*	m_pLatestPathGroup;

	bxa::eIDEPathType					m_eIDEPathType;
};

#endif