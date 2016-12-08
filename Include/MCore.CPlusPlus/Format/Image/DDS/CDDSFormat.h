#ifndef CDDSFormat_H
#define CDDSFormat_H

#include "mcore.h"
#include "Format/CFormat.h"
#include "Unit/Byte/eEndian.h"
#include <string>

class mcore::CDDSFormat : public mcore::CFormat
{
public:
	CDDSFormat(void);

private:
	void								unserialize(void);
	void								serialize(void);

public:
	uint32								m_uiWidth;
	uint32								m_uiHeight;
	uint32								m_uiBPP;
	std::string							m_strRasterData;
};

#endif