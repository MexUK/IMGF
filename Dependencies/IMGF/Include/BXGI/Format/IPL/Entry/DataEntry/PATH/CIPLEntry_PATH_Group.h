#pragma once

#include "nsbxgi.h"
#include "Type/Types.h"
#include "Format/IPL/Entry/DataEntry/CIPLEntry_PATH.h"
#include "Pool/CVectorPool.h"

class bxgi::CIPLEntry;

class bxgi::CIPLEntry_PATH_Group : public bxgi::CIPLEntry_PATH, public bxcf::CVectorPool<bxgi::CIPLEntry*>
{
public:
	CIPLEntry_PATH_Group(bxgi::CIPLFormat *pIPLFormat);

	void							unload(void);

	void							unserialize(void);
	void							serialize(void);

	void							setGroupType(std::string& strGroupType) { m_strGroupType = strGroupType; }
	std::string&					getGroupType(void) { return m_strGroupType; }

	void							setMinusOne(int32 iMinusOne) { m_iMinusOne = iMinusOne; }
	int32							getMinusOne(void) { return m_iMinusOne; }

private:
	// GTA VC only
	std::string						m_strGroupType;
	int32							m_iMinusOne;
};