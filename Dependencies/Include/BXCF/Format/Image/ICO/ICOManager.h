#pragma once

#include "nsbxcf.h"
#include "Format/FormatManager.h"
#include "Object/Singleton.h"

class bxcf::ICOFormat;
class bxcf::BMPFormat;

class bxcf::ICOManager : public bxcf::FormatManager<bxcf::ICOFormat>, public bxcf::Singleton<bxcf::ICOManager>
{
public:
	ICOManager(void);

	void						init(void);
	void						uninit(void);

	bxcf::ICOFormat*			createFormatFromBMP(bxcf::BMPFormat *pBMPFormat);
};