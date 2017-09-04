#pragma once

#include "nsbxcf.h"
#include "Format/Format.h"
#include <string>

class bxcf::DDSFormat : public bxcf::Format
{
public:
	DDSFormat(void);

private:
	void								unserialize(void);
	void								serialize(void);

public:
	uint32								m_uiWidth;
	uint32								m_uiHeight;
	uint32								m_uiBPP;
	std::string							m_strRasterData;
};