#pragma once

#include "nsimgf.h"
#include "Format/CFormat.h"
#include "Pool/CVectorPool.h"
#include "CLSTSection.h"
#include <string>

class imgf::CLSTFormat : public bxcf::CFormat, public bxcf::CVectorPool<CLSTSection*>
{
public:
	CLSTFormat(void) : bxcf::CFormat(false) {}

	void								unload(void);

	CLSTSection*						getEntryByName(std::string strName);
	bool								doesEntryExistByName(std::string strName);

private:
	void								unserialize(void);
	void								serialize(void);

	void								unserializeLine(void);
};