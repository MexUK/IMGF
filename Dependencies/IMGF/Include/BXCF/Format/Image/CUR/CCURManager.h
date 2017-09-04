#pragma once

#include "nsbxcf.h"
#include "Format/CFormatManager.h"
#include "Object/CSingleton.h"

class bxcf::CCURFormat;
class bxcf::CBMPFormat;

class bxcf::CCURManager : public bxcf::CFormatManager<bxcf::CCURFormat>, public bxcf::CSingleton<bxcf::CCURManager>
{
public:
	CCURManager(void);

	void						init(void);
	void						uninit(void);

	CCURFormat*					createFormatFromBMP(CBMPFormat *pBMPFormat);
};