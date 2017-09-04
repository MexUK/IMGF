#ifndef CIDEEntry_PATH_H
#define CIDEEntry_PATH_H

#include "bxcf.h"
#include "Type/Types.h"
#include "Format/RockstarGames/IDE/Entry/CIDEEntry_Data.h"
#include "Format/RockstarGames/IDE/eIDEPathType.h"

class bxcf::CIDEEntry_PATH_Group;

class bxcf::CIDEEntry_PATH : public bxcf::CIDEEntry_Data
{
public:
	CIDEEntry_PATH(bxcf::CIDEFormat *pIDEFormat, bxcf::eIDEPathType eIDEPathTypeValue) :
		CIDEEntry_Data(pIDEFormat, IDE_SECTION_PATH),
		m_eIDEPathType(eIDEPathTypeValue)
	{
	};

	virtual void					unserialize(void);
	virtual void					serialize(void);

	void							setIDEPathType(bxcf::eIDEPathType eIDEPathTypeValue) { m_eIDEPathType = eIDEPathTypeValue; }
	bxcf::eIDEPathType					getIDEPathType(void) { return m_eIDEPathType; }

	static void						setLatestPathGroup(bxcf::CIDEEntry_PATH_Group* pLatestPathGroup) { m_pLatestPathGroup = pLatestPathGroup; }
	static bxcf::CIDEEntry_PATH_Group*	getLatestPathGroup(void) { return m_pLatestPathGroup; }

private:
	static bxcf::CIDEEntry_PATH_Group*	m_pLatestPathGroup;

	bxcf::eIDEPathType					m_eIDEPathType;
};

#endif