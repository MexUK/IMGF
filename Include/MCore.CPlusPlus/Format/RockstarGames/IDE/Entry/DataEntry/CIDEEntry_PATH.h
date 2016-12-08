#ifndef CIDEEntry_PATH_H
#define CIDEEntry_PATH_H

#include "mcore.h"
#include "Type/Types.h"
#include "Format/RockstarGames/IDE/Entry/CIDEEntry_Data.h"
#include "Format/RockstarGames/IDE/eIDEPathType.h"

class mcore::CIDEEntry_PATH_Group;

class mcore::CIDEEntry_PATH : public mcore::CIDEEntry_Data
{
public:
	CIDEEntry_PATH(mcore::CIDEFormat *pIDEFormat, mcore::eIDEPathType eIDEPathTypeValue) :
		CIDEEntry_Data(pIDEFormat, IDE_SECTION_PATH),
		m_eIDEPathType(eIDEPathTypeValue)
	{
	};

	virtual void					unserialize(void);
	virtual void					serialize(void);

	void							setIDEPathType(mcore::eIDEPathType eIDEPathTypeValue) { m_eIDEPathType = eIDEPathTypeValue; }
	mcore::eIDEPathType					getIDEPathType(void) { return m_eIDEPathType; }

	static void						setLatestPathGroup(mcore::CIDEEntry_PATH_Group* pLatestPathGroup) { m_pLatestPathGroup = pLatestPathGroup; }
	static mcore::CIDEEntry_PATH_Group*	getLatestPathGroup(void) { return m_pLatestPathGroup; }

private:
	static mcore::CIDEEntry_PATH_Group*	m_pLatestPathGroup;

	mcore::eIDEPathType					m_eIDEPathType;
};

#endif