#pragma once

#include "nsimgf.h"
#include "Format/CFormat.h"
#include "Pool/CVectorPool.h"
#include "LSTSection.h"
#include <string>

class imgf::LSTFormat : public bxcf::CFormat, public bxcf::CVectorPool<LSTSection*>
{
public:
	LSTFormat(void) : bxcf::CFormat(false) {}

	void								unload(void);

	LSTSection*						getEntryByName(std::string strName);
	bool								doesEntryExistByName(std::string strName);

private:
	void								unserialize(void);
	void								serialize(void);

	void								unserializeLine(void);
};