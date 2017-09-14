#pragma once

#include "nsimgf.h"
#include "Format/Format.h"
#include "Pool/VectorPool.h"
#include "Format/LST/LSTSection.h"
#include <string>

class imgf::LSTFormat : public bxcf::Format, public bxcf::VectorPool<LSTSection*>
{
public:
	LSTFormat(void) : bxcf::Format(false) {}
	LSTFormat(std::string& strFilePathOrData, bool bStringIsFilePath = true) : bxcf::Format(strFilePathOrData, bStringIsFilePath, false) {}

	void								unload(void);

	LSTSection*							getEntryByName(std::string strName);
	bool								doesEntryExistByName(std::string strName);

private:
	void								_unserialize(void);
	void								_serialize(void);

	void								unserializeLine(void);
};