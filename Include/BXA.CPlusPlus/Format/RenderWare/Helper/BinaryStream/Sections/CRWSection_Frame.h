#ifndef CRWSection_Frame_H
#define CRWSection_Frame_H

#include "BXA.h"
#include "Format/RenderWare/Helper/BinaryStream/CRWSection.h"
#include <string>

class bxa::CRWSection_Frame : public bxa::CRWSection
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