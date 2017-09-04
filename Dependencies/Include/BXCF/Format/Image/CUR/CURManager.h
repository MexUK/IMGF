#pragma once

#include "nsbxcf.h"
#include "Format/FormatManager.h"
#include "Object/Singleton.h"

class bxcf::CURFormat;
class bxcf::BMPFormat;

class bxcf::CURManager : public bxcf::FormatManager<bxcf::CURFormat>, public bxcf::Singleton<bxcf::CURManager>
{
public:
	CURManager(void);

	void						init(void);
	void						uninit(void);

	CURFormat*					createFormatFromBMP(BMPFormat *pBMPFormat);
};