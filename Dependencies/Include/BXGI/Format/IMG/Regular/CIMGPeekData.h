#ifndef CIMGPeekData_H
#define CIMGPeekData_H

#include "bxgi.h"
#include "eIMGVersion.h"

class bxgi::CIMGPeekData
{
public:
	CIMGPeekData(void);

public:
	void			setVersion(eIMGVersion eIMGVersionValue) { m_eIMGVersion = eIMGVersionValue; }
	eIMGVersion		getVersion(void) { return m_eIMGVersion; }

	void			setEncrypted(bool bEncrypted) { m_bEncrypted = bEncrypted; }
	bool			isEncrypted(void) { return m_bEncrypted; }

private:
	eIMGVersion		m_eIMGVersion;
	bool			m_bEncrypted;
};

#endif