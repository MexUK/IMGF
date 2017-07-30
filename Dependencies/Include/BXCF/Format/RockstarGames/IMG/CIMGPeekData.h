#ifndef CIMGPeekData_H
#define CIMGPeekData_H

#include "bxcf.h"
#include "eIMGVersion.h"

class bxcf::CIMGPeekData
{
public:
	CIMGPeekData(void);

public:
	void			setIMGVersion(eIMGVersion eIMGVersionValue) { m_eIMGVersion = eIMGVersionValue; }
	eIMGVersion		getIMGVersion(void) { return m_eIMGVersion; }

	void			setEncrypted(bool bEncrypted) { m_bEncrypted = bEncrypted; }
	bool			isEncrypted(void) { return m_bEncrypted; }

private:
	eIMGVersion		m_eIMGVersion;
	bool			m_bEncrypted;
};

#endif