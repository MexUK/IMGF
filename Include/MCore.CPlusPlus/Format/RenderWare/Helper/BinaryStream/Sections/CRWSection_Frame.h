#ifndef CRWSection_Frame_H
#define CRWSection_Frame_H

#include "mcore.h"
#include "Format/RenderWare/Helper/BinaryStream/CRWSection.h"
#include <string>

class mcore::CRWSection_Frame : public mcore::CRWSection
{
public:
	CRWSection_Frame(void);

	void							unserialize(void);
	void							serialize(void);

	void							setData(std::string& strData) { m_strData = strData; }
	std::string&					getData(void) { return m_strData; }

private:
	std::string						m_strData;
};

#endif