#ifndef CRWSection_Light_H
#define CRWSection_Light_H

#include "mcore.h"
#include "Format/RenderWare/Helper/BinaryStream/CRWSection.h"
#include <string>

class mcore::CRWSection_Light : public mcore::CRWSection
{
public:
	CRWSection_Light(void);

	void							unserialize(void);
	void							serialize(void);

	void							setData(std::string& strData) { m_strData = strData; }
	std::string&					getData(void) { return m_strData; }

private:
	std::string						m_strData;
};

#endif