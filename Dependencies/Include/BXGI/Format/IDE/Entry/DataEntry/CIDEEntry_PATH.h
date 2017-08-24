#ifndef CIDEEntry_PATH_H
#define CIDEEntry_PATH_H

#include "bxgi.h"
#include "Type/Types.h"
#include "Format/IDE/Entry/CIDEEntry_Data.h"
#include "Format/IDE/eIDEPathType.h"

class bxgi::CIDEEntry_PATH_Group;

class bxgi::CIDEEntry_PATH : public bxgi::CIDEEntry_Data
{
public:
	CIDEEntry_PATH(bxgi::CIDEFormat *pIDEFormat, bxgi::eIDEPathType eIDEPathTypeValue) :
		CIDEEntry_Data(pIDEFormat, IDE_SECTION_PATH),
		m_eIDEPathType(eIDEPathTypeValue)
	{
	};

	virtual void					unserialize(void);
	virtual void					serialize(void);

	void							setIDEPathType(bxgi::eIDEPathType eIDEPathTypeValue) { m_eIDEPathType = eIDEPathTypeValue; }
	bxgi::eIDEPathType					getIDEPathType(void) { return m_eIDEPathType; }

	static void						setLatestPathGroup(bxgi::CIDEEntry_PATH_Group* pLatestPathGroup) { m_pLatestPathGroup = pLatestPathGroup; }
	static bxgi::CIDEEntry_PATH_Group*	getLatestPathGroup(void) { return m_pLatestPathGroup; }

private:
	static bxgi::CIDEEntry_PATH_Group*	m_pLatestPathGroup;

	bxgi::eIDEPathType					m_eIDEPathType;
};

#endif