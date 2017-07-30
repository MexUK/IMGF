#ifndef CRWSection_Frame_H
#define CRWSection_Frame_H

#include "bxcf.h"
#include "Format/RenderWare/Helper/BinaryStream/CRWSection.h"
#include <string>

class bxcf::CRWSection_Frame : public bxcf::CRWSection
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